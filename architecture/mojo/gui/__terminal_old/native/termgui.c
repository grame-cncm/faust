#if defined(__APPLE__) && !defined(_DARWIN_C_SOURCE)
#define _DARWIN_C_SOURCE
#endif
#if !defined(_WIN32) && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif
#include "termgui.h"

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#if MJ_SYSTEM_WIN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <stdatomic.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#endif

MJ_STATIC_ASSERT(MJ_GUI_CAP > 0 && MJ_GUI_CAP <= 4096, "GUI capacity: 1..4096");
MJ_STATIC_ASSERT(MJ_STR_CAP > 1 && MJ_STR_CAP <= 4096, "string capacity: 2..4096");
MJ_STATIC_ASSERT(MJ_GUI_FPS > 0 && MJ_GUI_FPS <= 1000, "GUI FPS: 1..1000");

enum { KIND_BOX = WIDGET_BARGRAPH + 1, FRAME_CAP = MJ_GUI_CAP * (MJ_STR_CAP * 2 + 128) + 256 };
enum { KEY_NONE, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_ACT, KEY_QUIT, KEY_PAGE_UP, KEY_PAGE_DOWN };
#if MJ_SYSTEM_UNIX
static int const sigs[] = { SIGWINCH, SIGINT, SIGTERM, SIGHUP, SIGTSTP, SIGQUIT };
#endif

#if MJ_SYSTEM_WIN
struct Value { volatile LONG64 bits; };
#else
struct Value { _Atomic(u64) bits; };
#endif
typedef struct Widget {
    s32 kind, par, depth;
    f64 val, min, max, step;
    char lbl[MJ_STR_CAP], unit[MJ_STR_CAP];
    Value slot;
} Widget;
typedef struct Term {
#if MJ_SYSTEM_WIN
    HANDLE in, out;
    DWORD in_mode, out_mode;
#else
    struct termios prev;
    struct sigaction acts[MJ_COUNT_OF(sigs)];
#endif
    s32 rows, cols, esc, code;
    b32 live;
} Term;
struct Gui {
    Term term;
    Widget wdgs[MJ_GUI_CAP];
    s32 len, par, focus, top, press;
    char buf[FRAME_CAP];
    usize used;
};

static Gui* owner;
#if MJ_SYSTEM_WIN
typedef LONG Flag;
#define MJ_FLAG_GET(ptr) (InterlockedCompareExchange((ptr), 0, 0) != 0)
#define MJ_FLAG_SET(ptr, val) ((void)InterlockedExchange((ptr), (LONG)(val)))
#else
typedef sig_atomic_t Flag;
#define MJ_FLAG_GET(ptr) (*(ptr) != 0)
#define MJ_FLAG_SET(ptr, val) ((void)(*(ptr) = (val)))
#endif
static volatile Flag resized;
static volatile Flag halted;

static f64 clamp(f64 val, f64 min, f64 max) {
    return val < min ? min : (val > max ? max : val);
}

cstr error_str(ErrorCode err) {
    static cstr const strs[] = {
        "ok", "invalid argument", "invalid state", "allocation failed",
        "capacity exceeded", "terminal I/O failed", "not a usable terminal",
        "lock-free controls unavailable"
    };
    return err >= 0 && (usize)err < MJ_COUNT_OF(strs) ? strs[err] : "unknown error";
}

void gui_log(cstr file, s32 line, cstr func, cstr fmt, ...) {
    va_list args;
    fprintf(stderr, "%s:%d: %s: ", file, (int)line, func);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);
}

mj_noreturn void gui_panic(cstr file, s32 line, cstr func, cstr fmt, ...) {
    va_list args;
    if (owner) (void)gui_stop(owner);
    fprintf(stderr, "%s:%d: %s: panic: ", file, (int)line, func);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);
    abort();
}

static u64 value_bits(f64 val) {
    u64 bits;
    memcpy(&bits, &val, sizeof(bits));
    return bits;
}

static f64 value_real(u64 bits) {
    f64 val;
    memcpy(&val, &bits, sizeof(val));
    return val;
}

f64 value_load(Value const* ptr) {
#if MJ_SYSTEM_WIN
    LONG64 bits = InterlockedCompareExchange64((volatile LONG64*)&ptr->bits, 0, 0);
    return value_real((u64)bits);
#else
    return value_real(atomic_load_explicit(&ptr->bits, memory_order_relaxed));
#endif
}

void value_store(Value* ptr, f64 val) {
#if MJ_SYSTEM_WIN
    (void)InterlockedExchange64(&ptr->bits, (LONG64)value_bits(val));
#else
    atomic_store_explicit(&ptr->bits, value_bits(val), memory_order_relaxed);
#endif
}

f64 value_exchange(Value* ptr, f64 val) {
#if MJ_SYSTEM_WIN
    return value_real((u64)InterlockedExchange64(&ptr->bits, (LONG64)value_bits(val)));
#else
    return value_real(atomic_exchange_explicit(&ptr->bits, value_bits(val), memory_order_relaxed));
#endif
}

ErrorCode gui_create(Gui** out) {
    if (!out) return ERROR_INVALID_ARG;
    *out = NULL;
    Gui* ui = MJ_ALLOC(sizeof(*ui));
    if (!ui) return ERROR_BAD_ALLOC;
    memset(ui, 0, sizeof(*ui));
#if MJ_SYSTEM_UNIX
    atomic_init(&ui->wdgs[0].slot.bits, 0);
    if (!atomic_is_lock_free(&ui->wdgs[0].slot.bits)) {
        MJ_FREE(ui);
        return ERROR_UNSUPPORTED;
    }
#endif
    ui->par = ui->focus = ui->press = -1;
    *out = ui;
    return ERROR_NONE;
}

void gui_destroy(Gui* ui) {
    if (!ui) return;
    (void)gui_stop(ui);
    MJ_FREE(ui);
}

static ErrorCode str_copy(char* out, cstr str) {
    if (!str) return ERROR_INVALID_ARG;
    usize len = strnlen(str, MJ_STR_CAP);
    if (len == MJ_STR_CAP) return ERROR_CAPACITY;
    memcpy(out, str, len + 1);
    return ERROR_NONE;
}

static ErrorCode gui_add(Gui* ui, s32 kind, cstr lbl, f64 init, f64 min, f64 max, f64 step, s32* out) {
    if (out) *out = -1;
    if (!ui || !out || !lbl || !isfinite(init) || !isfinite(min) || !isfinite(max) ||
        !isfinite(step) || min > max || !isfinite(max - min) || init < min || init > max || step < 0)
        return ERROR_INVALID_ARG;
    if (ui->term.live) return ERROR_INVALID_STATE;
    if (ui->len == MJ_GUI_CAP) return ERROR_CAPACITY;
    Widget* wdg = &ui->wdgs[ui->len];
    MJ_TRY(str_copy(wdg->lbl, lbl));
    wdg->kind = kind;
    wdg->par = ui->par;
    wdg->depth = ui->par < 0 ? 0 : ui->wdgs[ui->par].depth + 1;
    wdg->val = init;
    wdg->min = min;
    wdg->max = max;
    wdg->step = step;
    wdg->unit[0] = 0;
#if MJ_SYSTEM_WIN
    wdg->slot.bits = (LONG64)value_bits(init);
#else
    atomic_init(&wdg->slot.bits, value_bits(init));
#endif
    *out = ui->len++;
    if (kind < WIDGET_BARGRAPH && ui->focus < 0) ui->focus = *out;
    return ERROR_NONE;
}

ErrorCode gui_open_box(Gui* ui, BoxKind kind, cstr lbl, s32* out) {
    if (out) *out = -1;
    if (kind < BOX_TAB || kind > BOX_VERTICAL) return ERROR_INVALID_ARG;
    MJ_TRY(gui_add(ui, KIND_BOX + kind, lbl, 0, 0, 0, 0, out));
    ui->par = *out;
    return ERROR_NONE;
}

ErrorCode gui_close_box(Gui* ui) {
    if (!ui) return ERROR_INVALID_ARG;
    if (ui->term.live || ui->par < 0) return ERROR_INVALID_STATE;
    MJ_ASSERT(ui->par < ui->len && ui->wdgs[ui->par].kind >= KIND_BOX);
    ui->par = ui->wdgs[ui->par].par;
    return ERROR_NONE;
}

ErrorCode gui_add_button(Gui* ui, cstr lbl, s32* out) {
    return gui_add(ui, WIDGET_BUTTON, lbl, 0, 0, 1, 1, out);
}

ErrorCode gui_add_check_button(Gui* ui, cstr lbl, f64 init, s32* out) {
    return gui_add(ui, WIDGET_CHECK_BUTTON, lbl, init, 0, 1, 1, out);
}

ErrorCode gui_add_slider(Gui* ui, cstr lbl, f64 init, f64 min, f64 max, f64 step, s32* out) {
    return gui_add(ui, WIDGET_SLIDER, lbl, init, min, max, step, out);
}

ErrorCode gui_add_num_entry(Gui* ui, cstr lbl, f64 init, f64 min, f64 max, f64 step, s32* out) {
    return gui_add(ui, WIDGET_NUM_ENTRY, lbl, init, min, max, step, out);
}

ErrorCode gui_add_bargraph(Gui* ui, cstr lbl, f64 min, f64 max, s32* out) {
    return gui_add(ui, WIDGET_BARGRAPH, lbl, min, min, max, 0, out);
}

static b32 gui_valid(Gui const* ui, s32 id) {
    return ui && id >= 0 && id < ui->len && ui->wdgs[id].kind < KIND_BOX;
}

ErrorCode gui_set_val(Gui* ui, s32 id, f64 val) {
    if (!gui_valid(ui, id) || !isfinite(val)) return ERROR_INVALID_ARG;
    Widget* wdg = &ui->wdgs[id];
    wdg->val = wdg->kind == WIDGET_BARGRAPH ? val : clamp(val, wdg->min, wdg->max);
    return ERROR_NONE;
}

ErrorCode gui_set_unit(Gui* ui, s32 id, cstr unit) {
    if (!gui_valid(ui, id)) return ERROR_INVALID_ARG;
    return str_copy(ui->wdgs[id].unit, unit);
}

ErrorCode gui_get_value(Gui* ui, s32 id, Value** out) {
    if (out) *out = NULL;
    if (!out || !gui_valid(ui, id)) return ERROR_INVALID_ARG;
    *out = &ui->wdgs[id].slot;
    return ERROR_NONE;
}

static ErrorCode term_write(cstr buf, usize len) {
#if MJ_SYSTEM_WIN
    while (len) {
        DWORD size = len > (usize)UINT32_MAX ? UINT32_MAX : (DWORD)len;
        DWORD done = 0;
        if (!WriteFile(owner->term.out, buf, size, &done, NULL) || done == 0) return ERROR_IO;
        buf += done;
        len -= done;
    }
#else
    while (len) {
        ssize_t n = write(STDOUT_FILENO, buf, len);
        if (n < 0 && errno == EINTR && !MJ_FLAG_GET(&halted)) continue;
        if (n <= 0) return ERROR_IO;
        buf += n;
        len -= (usize)n;
    }
#endif
    return ERROR_NONE;
}

static void term_size(Term* term) {
#if MJ_SYSTEM_WIN
    CONSOLE_SCREEN_BUFFER_INFO size;
    if (GetConsoleScreenBufferInfo(term->out, &size)) {
        term->rows = (s32)size.srWindow.Bottom - (s32)size.srWindow.Top + 1;
        term->cols = (s32)size.srWindow.Right - (s32)size.srWindow.Left + 1;
    } else {
        term->rows = 24;
        term->cols = 80;
    }
#else
    struct winsize size;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == 0 && size.ws_row && size.ws_col) {
        term->rows = size.ws_row;
        term->cols = size.ws_col;
    } else {
        term->rows = 24;
        term->cols = 80;
    }
#endif
}

#if MJ_SYSTEM_WIN
static BOOL WINAPI term_control(DWORD kind) {
    if (kind == CTRL_C_EVENT || kind == CTRL_BREAK_EVENT || kind == CTRL_CLOSE_EVENT ||
        kind == CTRL_LOGOFF_EVENT || kind == CTRL_SHUTDOWN_EVENT) {
        MJ_FLAG_SET(&halted, 1);
        return TRUE;
    }
    return FALSE;
}
#else
static void term_signal(int sig) {
    if (sig == SIGWINCH) resized = 1;
    else halted = sig;
}
#endif

ErrorCode gui_stop(Gui* ui) {
    if (!ui) return ERROR_INVALID_ARG;
    if (!ui->term.live) return ERROR_NONE;
    ErrorCode err = ERROR_NONE;
#if MJ_SYSTEM_WIN
    static char const end[] = "\033[0m\033[?25h\033[?1049l";
    if (term_write(end, sizeof(end) - 1)) err = ERROR_IO;
    if (!SetConsoleMode(ui->term.in, ui->term.in_mode)) err = ERROR_TERM;
    if (!SetConsoleMode(ui->term.out, ui->term.out_mode)) err = ERROR_TERM;
    if (!SetConsoleCtrlHandler(term_control, FALSE)) err = ERROR_TERM;
#else
    /* Restore termios even when stdout has disappeared. Retry interrupted calls. */
    int res;
    do { res = tcsetattr(STDIN_FILENO, TCSANOW, &ui->term.prev); } while (res < 0 && errno == EINTR);
    if (res < 0) err = ERROR_TERM;
    static char const end[] = "\033[0m\033[?25h\033[?1049l";
    if (term_write(end, sizeof(end) - 1)) err = ERROR_IO;
    for (usize i = 0; i < MJ_COUNT_OF(sigs); ++i)
        if (sigaction(sigs[i], &ui->term.acts[i], NULL) < 0) err = ERROR_TERM;
#endif
    ui->term.live = 0;
    owner = NULL;
    return err;
}

static ErrorCode term_start(Gui* ui) {
    if (owner || ui->term.live || ui->par >= 0) return ERROR_INVALID_STATE;
#if MJ_SYSTEM_WIN
    ui->term.in = GetStdHandle(STD_INPUT_HANDLE);
    ui->term.out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!ui->term.in || ui->term.in == INVALID_HANDLE_VALUE ||
        !ui->term.out || ui->term.out == INVALID_HANDLE_VALUE ||
        !GetConsoleMode(ui->term.in, &ui->term.in_mode) ||
        !GetConsoleMode(ui->term.out, &ui->term.out_mode)) return ERROR_TERM;
    DWORD in_mode = (ui->term.in_mode | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS) &
        ~(DWORD)(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_QUICK_EDIT_MODE);
    DWORD out_mode = ui->term.out_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    MJ_FLAG_SET(&resized, 0);
    MJ_FLAG_SET(&halted, 0);
    if (!SetConsoleCtrlHandler(term_control, TRUE)) return ERROR_TERM;
    if (!SetConsoleMode(ui->term.in, in_mode) || !SetConsoleMode(ui->term.out, out_mode)) {
        (void)SetConsoleMode(ui->term.in, ui->term.in_mode);
        (void)SetConsoleMode(ui->term.out, ui->term.out_mode);
        (void)SetConsoleCtrlHandler(term_control, FALSE);
        return ERROR_TERM;
    }
#else
    cstr env = getenv("TERM");
    if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || (env && strcmp(env, "dumb") == 0))
        return ERROR_TERM;
    if (tcgetattr(STDIN_FILENO, &ui->term.prev) < 0) return ERROR_TERM;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = term_signal;
    sigemptyset(&act.sa_mask);
    resized = halted = 0;
    for (usize i = 0; i < MJ_COUNT_OF(sigs); ++i) {
        if (sigaction(sigs[i], &act, &ui->term.acts[i]) < 0) {
            while (i) { --i; (void)sigaction(sigs[i], &ui->term.acts[i], NULL); }
            return ERROR_TERM;
        }
    }
#endif
    ui->term.live = 1;
    ui->term.esc = 0;
    owner = ui;
#if MJ_SYSTEM_UNIX
    struct termios raw = ui->term.prev;
    raw.c_lflag &= (tcflag_t)~(ICANON | ECHO | IEXTEN);
    raw.c_iflag &= (tcflag_t)~(IXON | ICRNL | INLCR);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) < 0) {
        (void)gui_stop(ui);
        return ERROR_TERM;
    }
#endif
    term_size(&ui->term);
    static char const beg[] = "\033[?1049h\033[?25l\033[2J";
    return term_write(beg, sizeof(beg) - 1);
}

static void buf_put(Gui* ui, cstr str, usize len) {
    if (len > sizeof(ui->buf) - ui->used) MJ_PANIC("frame capacity exceeded");
    memcpy(ui->buf + ui->used, str, len);
    ui->used += len;
}

/* Keep complete UTF-8 sequences, suppress terminal controls. Structural graphics
 * are ASCII; wide/combining glyph column measurement is outside this first pass. */
static void buf_text(Gui* ui, cstr str, s32* left) {
    while (*str && *left > 0) {
        u8 ch = (u8)*str;
        usize len = 1;
        if (ch >= 0xc2 && ch <= 0xf4) {
            usize need = ch < 0xe0 ? 2u : (ch < 0xf0 ? 3u : 4u);
            while (len < need && str[len] && ((u8)str[len] & 0xc0u) == 0x80u) ++len;
            if (len != need) len = 1;
        }
        if (ch < 0x20 || ch == 0x7f || (ch >= 0x80 && len == 1) ||
            (ch == 0xc2 && (u8)str[1] < 0xa0)) buf_put(ui, "?", 1);
        else buf_put(ui, str, len);
        str += len;
        --*left;
    }
}

static void buf_field(Gui* ui, cstr str, s32 cols, s32* left) {
    if (cols > *left) cols = *left;
    s32 pad = cols;
    buf_text(ui, str, &pad);
    while (pad-- > 0) buf_put(ui, " ", 1);
    *left -= cols;
}

static ErrorCode gui_render(Gui* ui) {
    s32 rows = ui->term.rows > 1 ? ui->term.rows - 1 : 0;
    if (rows > 0 && ui->focus >= 0) {
        if (ui->focus < ui->top) ui->top = ui->focus;
        if (ui->focus >= ui->top + rows) ui->top = ui->focus - rows + 1;
    }
    if (ui->top > ui->len - rows) ui->top = ui->len > rows ? ui->len - rows : 0;
    ui->used = 0;
    buf_put(ui, "\033[H", 3);
    for (s32 row = 0; row < rows && ui->top + row < ui->len; ++row) {
        s32 id = ui->top + row;
        Widget const* wdg = &ui->wdgs[id];
        s32 left = ui->term.cols;
        buf_text(ui, id == ui->focus ? "> " : "  ", &left);
        /* Deep Faust nesting must not push every label off the screen. */
        s32 depth = wdg->depth < 8 ? wdg->depth : 8;
        for (s32 j = 0; j < depth && left > 16; ++j) buf_text(ui, "  ", &left);
        if (wdg->kind >= KIND_BOX) {
            buf_text(ui, wdg->lbl, &left);
        } else {
            /* Reserve room for the value: a long label must not hide editing.
             * Indentation is included in the label column, keeping bars aligned. */
            s32 cols = ui->term.cols / 3 - (ui->term.cols - left);
            if (cols < 1) cols = left / 3;
            if (cols > 32) cols = 32;
            buf_field(ui, wdg->lbl, cols, &left);
            char val[48];
            (void)snprintf(val, sizeof(val), " %.7g", wdg->val);
            s32 unit = (s32)strlen(wdg->unit);
            if (unit > 12) unit = 12;
            if (wdg->kind <= WIDGET_CHECK_BUTTON) {
                buf_text(ui, wdg->val != 0 ? " [x]" : " [ ]", &left);
            } else {
                f64 frac = wdg->max == wdg->min ? 0 :
                    clamp((wdg->val - wdg->min) / (wdg->max - wdg->min), 0, 1);
                s32 span = left - (s32)strlen(val) - (unit ? unit + 1 : 0) - 3;
                if (span > 24) span = 24;
                if (span >= 4) {
                    buf_text(ui, " [", &left);
                    for (s32 j = 0; j < span; ++j)
                        buf_text(ui, (f64)j < frac * (f64)span ?
                            (wdg->kind == WIDGET_BARGRAPH ? "#" : "=") : "-", &left);
                    buf_text(ui, "]", &left);
                }
            }
            buf_text(ui, val, &left);
            if (wdg->unit[0]) { buf_text(ui, " ", &left); buf_text(ui, wdg->unit, &left); }
        }
        buf_put(ui, "\033[K\r\n", 5);
    }
    s32 left = ui->term.cols;
    if (ui->len > rows && rows > 0) {
        char info[48];
        (void)snprintf(info, sizeof(info), "%d-%d/%d  ",
            (int)(ui->top + 1), (int)(ui->top + rows), (int)ui->len);
        buf_text(ui, info, &left);
    }
    buf_text(ui, "q quit  arrows/hjkl move/edit  space/enter act  pgup/pgdn scroll", &left);
    buf_put(ui, "\033[J", 3);
    return term_write(ui->buf, ui->used);
}

ErrorCode gui_start(Gui* ui) {
    if (!ui) return ERROR_INVALID_ARG;
    if (ui->term.live) return ERROR_INVALID_STATE;
    ErrorCode err = term_start(ui);
    if (!err) err = gui_render(ui);
    if (err && owner == ui) (void)gui_stop(ui);
    return err;
}

static s32 term_key(Term* term, u8 ch) {
    if (term->esc) {
        if (term->esc == 1 && (ch == '[' || ch == 'O')) {
            term->esc = 2; term->code = 0; return KEY_NONE;
        }
        if (term->esc == 2 && (ch == ';' || (ch >= '0' && ch <= '9'))) {
            if (!term->code) term->code = ch;
            return KEY_NONE;
        }
        s32 esc = term->esc;
        term->esc = 0;
        if (esc == 2) {
            switch (ch) {
                case 'A': return KEY_UP;
                case 'B': return KEY_DOWN;
                case 'C': return KEY_RIGHT;
                case 'D': return KEY_LEFT;
                case '~': return term->code == '5' ? KEY_PAGE_UP :
                                 (term->code == '6' ? KEY_PAGE_DOWN : KEY_NONE);
                default: return KEY_NONE;
            }
        }
    }
    switch (ch) {
        case 27: term->esc = 1; return KEY_NONE;
        case 'k': return KEY_UP;
        case 'j': return KEY_DOWN;
        case 'h': return KEY_LEFT;
        case 'l': return KEY_RIGHT;
        case ' ': case '\r': case '\n': return KEY_ACT;
        case 'q': case 3: return KEY_QUIT;
        default: return KEY_NONE;
    }
}

static ErrorCode term_read(Term* term, s32 wait_ms, s32* key) {
    *key = KEY_NONE;
#if MJ_SYSTEM_WIN
    DWORD wait = WaitForSingleObject(term->in, (DWORD)wait_ms);
    if (wait == WAIT_TIMEOUT) return ERROR_NONE;
    if (wait != WAIT_OBJECT_0) return ERROR_IO;
    for (s32 i = 0; i < 32; ++i) {
        INPUT_RECORD evt;
        DWORD done = 0;
        if (!ReadConsoleInputW(term->in, &evt, 1, &done) || done == 0) return ERROR_IO;
        if (evt.EventType == WINDOW_BUFFER_SIZE_EVENT) {
            MJ_FLAG_SET(&resized, 1);
            return ERROR_NONE;
        }
        if (evt.EventType != KEY_EVENT || !evt.Event.KeyEvent.bKeyDown) continue;
        switch (evt.Event.KeyEvent.wVirtualKeyCode) {
            case VK_UP: *key = KEY_UP; return ERROR_NONE;
            case VK_DOWN: *key = KEY_DOWN; return ERROR_NONE;
            case VK_LEFT: *key = KEY_LEFT; return ERROR_NONE;
            case VK_RIGHT: *key = KEY_RIGHT; return ERROR_NONE;
            case VK_PRIOR: *key = KEY_PAGE_UP; return ERROR_NONE;
            case VK_NEXT: *key = KEY_PAGE_DOWN; return ERROR_NONE;
            case VK_RETURN: case VK_SPACE: *key = KEY_ACT; return ERROR_NONE;
            default: break;
        }
        WCHAR ch = evt.Event.KeyEvent.uChar.UnicodeChar;
        if (ch <= UINT8_MAX) *key = term_key(term, (u8)ch);
        if (*key != KEY_NONE) return ERROR_NONE;
    }
#else
    for (s32 i = 0; i < 32; ++i) {
        if (MJ_FLAG_GET(&halted) || MJ_FLAG_GET(&resized)) return ERROR_NONE;
        struct pollfd fd = { STDIN_FILENO, POLLIN, 0 };
        int res = poll(&fd, 1, i == 0 ? wait_ms : 0);
        if (res < 0 && errno == EINTR) return ERROR_NONE;
        if (res < 0) return ERROR_IO;
        if (!res) return ERROR_NONE;
        if (fd.revents & (POLLERR | POLLNVAL)) return ERROR_IO;
        if (!(fd.revents & POLLIN) && (fd.revents & POLLHUP)) { *key = KEY_QUIT; return ERROR_NONE; }
        u8 ch;
        ssize_t n = read(STDIN_FILENO, &ch, 1);
        if (n < 0 && (errno == EINTR || errno == EAGAIN)) return ERROR_NONE;
        if (n < 0) return ERROR_IO;
        if (!n) { *key = KEY_QUIT; return ERROR_NONE; }
        *key = term_key(term, ch);
        if (*key) return ERROR_NONE;
    }
#endif
    return ERROR_NONE;
}

static void gui_focus(Gui* ui, s32 dir) {
    s32 id = ui->focus;
    if (id < 0) id = ui->top;
    for (s32 i = 0; i < ui->len; ++i) {
        id = (id + dir + ui->len) % ui->len;
        if (ui->wdgs[id].kind < WIDGET_BARGRAPH) { ui->focus = id; return; }
    }
}

static void gui_page(Gui* ui, s32 dir) {
    s32 rows = ui->term.rows > 1 ? ui->term.rows - 1 : 1;
    s32 last = ui->len > rows ? ui->len - rows : 0;
    ui->top += dir * rows;
    if (ui->top < 0) ui->top = 0;
    if (ui->top > last) ui->top = last;
    ui->focus = -1;
    for (s32 id = ui->top; id < ui->len && id < ui->top + rows; ++id) {
        if (ui->wdgs[id].kind < WIDGET_BARGRAPH) { ui->focus = id; break; }
    }
}

static void gui_edit(Gui* ui, s32 key, Event* out) {
    if (ui->focus < 0) return;
    Widget* wdg = &ui->wdgs[ui->focus];
    EventKind kind = EVENT_VALUE;
    f64 val = wdg->val;
    if (wdg->kind == WIDGET_BUTTON && key == KEY_ACT) { val = 1; kind = EVENT_BUTTON_PRESS; }
    else if (wdg->kind == WIDGET_CHECK_BUTTON && key == KEY_ACT) val = val == 0 ? 1 : 0;
    else if ((wdg->kind == WIDGET_SLIDER || wdg->kind == WIDGET_NUM_ENTRY) &&
             (key == KEY_LEFT || key == KEY_RIGHT)) {
        f64 dir = key == KEY_LEFT ? -1 : 1;
        f64 step = wdg->step != 0.0 ? wdg->step : (wdg->max - wdg->min) / 100;
        val += dir * step;
        f64 pos = step != 0.0 ? (val - wdg->min) / step : 0;
        /* Remove roundoff near the grid, without moving an off-grid init by
         * more than one step or skipping a value when leaving a clamped end. */
        if (step != 0.0 && isfinite(pos) && fabs(pos - round(pos)) < 1e-7)
            val = wdg->min + round(pos) * step;
        val = clamp(val, wdg->min, wdg->max);
    } else return;
    if (val == wdg->val) return;
    wdg->val = val;
    *out = (Event){ kind, ui->focus, val };
    if (kind == EVENT_BUTTON_PRESS) ui->press = ui->focus;
}

ErrorCode gui_step(Gui* ui, s32 wait_ms, Event* out) {
    if (out) *out = (Event){ EVENT_NONE, -1, 0 };
    ErrorCode err = ERROR_NONE;
    if (!ui || !out || wait_ms < -1 || wait_ms > 1000) err = ERROR_INVALID_ARG;
    else if (!ui->term.live) err = ERROR_INVALID_STATE;
    if (err) { if (ui && ui->term.live) (void)gui_stop(ui); return err; }
    if (wait_ms < 0) wait_ms = 1000 / MJ_GUI_FPS;
    s32 key = KEY_NONE;
    if (ui->press >= 0 && !MJ_FLAG_GET(&halted)) {
        ui->wdgs[ui->press].val = 0;
        *out = (Event){ EVENT_BUTTON_RELEASE, ui->press, 0 };
        ui->press = -1;
    } else {
        err = term_read(&ui->term, wait_ms, &key);
        if (MJ_FLAG_GET(&halted) || key == KEY_QUIT) out->kind = EVENT_QUIT;
        else if (MJ_FLAG_GET(&resized)) {
            MJ_FLAG_SET(&resized, 0);
            term_size(&ui->term);
            out->kind = EVENT_RESIZE;
        }
        else if (key == KEY_UP || key == KEY_DOWN) gui_focus(ui, key == KEY_UP ? -1 : 1);
        else if (key == KEY_PAGE_UP || key == KEY_PAGE_DOWN) gui_page(ui, key == KEY_PAGE_UP ? -1 : 1);
        else if (key) gui_edit(ui, key, out);
    }
    if (!err) err = gui_render(ui);
    if (err) (void)gui_stop(ui);
    return err;
}

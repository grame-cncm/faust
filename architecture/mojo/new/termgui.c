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

mj_static_assert(MJ_GUI_CAP > 0 && MJ_GUI_CAP <= 4096, "GUI capacity: 1..4096");
mj_static_assert(MJ_STR_CAP > 1 && MJ_STR_CAP <= 4096, "string capacity: 2..4096");
mj_static_assert(MJ_GUI_FPS > 0 && MJ_GUI_FPS <= 1000, "GUI FPS: 1..1000");

enum {
    KIND_BOX = WIDGET_BARGRAPH + 1,
    FRAME_CAP = MJ_VIEW_COLS * MJ_VIEW_ROWS * 4 + MJ_VIEW_ROWS * 8 + 64
};

typedef struct Rect {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect;

typedef struct Input {
    s32 kind;
    s32 x;
    s32 y;
} Input;

enum {
    INPUT_NONE,
    INPUT_DOWN,
    INPUT_DRAG,
    INPUT_UP,
    INPUT_CANCEL,
    INPUT_QUIT
};

#if MJ_SYSTEM_UNIX
static int const sigs[] = {
    SIGWINCH,
    SIGINT,
    SIGTERM,
    SIGHUP,
    SIGTSTP,
    SIGQUIT
};
#endif

#if MJ_SYSTEM_WIN
struct Value {
    volatile LONG64 bits;
};
#else
struct Value {
    _Atomic(u64) bits;
};
#endif

typedef struct Widget {
    s32 kind;
    s32 par;
    s32 depth;
    Rect rect;
    Rect hit;
    f64 val;
    f64 min;
    f64 max;
    f64 step;
    char lbl[MJ_STR_CAP];
    char unit[MJ_STR_CAP];
    Value slot;
} Widget;

typedef struct Term {
#if MJ_SYSTEM_WIN
    HANDLE in;
    HANDLE out;
    DWORD in_mode;
    DWORD out_mode;
    UINT out_cp;
    b32 down;
#else
    struct termios prev;
    struct sigaction acts[mj_count_of(sigs)];
#endif
    s32 rows;
    s32 cols;
    s32 esc;
    s32 code;
    s32 args[3];
    s32 arg;
    b32 mouse;
    b32 live;
} Term;

struct Gui {
    Term term;
    Widget wdgs[MJ_GUI_CAP];
    s32 len;
    s32 par;
    s32 top;
    s32 press;
    s32 height;
    s32 rows;
    s32 cols;
    u32 cells[MJ_VIEW_ROWS][MJ_VIEW_COLS];
    char buf[FRAME_CAP];
    ssize used;
};

static Gui* owner;

#if MJ_SYSTEM_WIN
typedef LONG Flag;
#define mj_flag_get(ptr) (InterlockedCompareExchange((ptr), 0, 0) != 0)
#define mj_flag_set(ptr, val) mj_unused(InterlockedExchange((ptr), cast(LONG, val)))
#else
typedef sig_atomic_t Flag;
#define mj_flag_get(ptr) (*(ptr) != 0)
#define mj_flag_set(ptr, val) mj_unused(*(ptr) = (val))
#endif

static volatile Flag resized;
static volatile Flag halted;

static f64 clamp(f64 val, f64 min, f64 max)
{
    mj_assert(min <= max);

    return val < min ? min : (val > max ? max : val);
}

cstr error_str(ErrorCode err)
{
    static cstr const strs[] = {
        "ok", "invalid argument", "invalid state", "allocation failed",
        "capacity exceeded", "terminal I/O failed", "not a usable terminal",
        "lock-free controls unavailable"
    };
    return err >= 0 && cast(ssize, err) < mj_count_of(strs) ? strs[err] : "unknown error";
}

void gui_log(cstr file, s32 line, cstr func, cstr fmt, ...)
{
    va_list args;
    fprintf(stderr, "%s:%d: %s: ", file, cast(int, line), func);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);
}

mj_noreturn void gui_fail(
    cstr kind, cstr expr, cstr file, s32 line, cstr func, cstr fmt, ...)
{
    va_list args;
    if (owner) {
        mj_unused(gui_stop(owner));
    }

    fprintf(stderr, "%s:%d: %s: %s", file, cast(int, line), func, kind);
    if (expr) {
        fprintf(stderr, " `%s`", expr);
    }
    fputs(": ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);

    abort();
}

static u64 value_bits(f64 val)
{
    u64 bits;
    memcpy(&bits, &val, sizeof(bits));
    return bits;
}

static f64 value_real(u64 bits)
{
    f64 val;
    memcpy(&val, &bits, sizeof(val));
    return val;
}

f64 value_load(Value const* ptr)
{
    mj_assert(ptr);

#if MJ_SYSTEM_WIN
    LONG64 bits = InterlockedCompareExchange64(cast(volatile LONG64*, &ptr->bits), 0, 0);
    return value_real(cast(u64, bits));
#else
    return value_real(atomic_load_explicit(&ptr->bits, memory_order_relaxed));
#endif
}

void value_store(Value* ptr, f64 val)
{
    mj_assert(ptr);
    mj_assert(isfinite(val));

#if MJ_SYSTEM_WIN
    mj_unused(InterlockedExchange64(&ptr->bits, cast(LONG64, value_bits(val))));
#else
    atomic_store_explicit(&ptr->bits, value_bits(val), memory_order_relaxed);
#endif
}

f64 value_exchange(Value* ptr, f64 val)
{
    mj_assert(ptr);
    mj_assert(isfinite(val));

#if MJ_SYSTEM_WIN
    return value_real(cast(u64, InterlockedExchange64(&ptr->bits, cast(LONG64, value_bits(val)))));
#else
    return value_real(atomic_exchange_explicit(&ptr->bits, value_bits(val), memory_order_relaxed));
#endif
}

ErrorCode gui_create(Gui** out)
{
    if (!out) {
        return ERROR_INVALID_ARG;
    }
    *out = NULL;
    Gui* ui = mj_alloc(sizeof(*ui));
    if (!ui) {
        return ERROR_BAD_ALLOC;
    }
    memset(ui, 0, sizeof(*ui));
#if MJ_SYSTEM_UNIX
    atomic_init(&ui->wdgs[0].slot.bits, 0);
    if (!atomic_is_lock_free(&ui->wdgs[0].slot.bits)) {
        mj_free(ui);
        return ERROR_UNSUPPORTED;
    }
#endif
    ui->par = ui->press = -1;
    *out = ui;
    return ERROR_NONE;
}

void gui_destroy(Gui* ui)
{
    if (!ui) {
        return;
    }
    mj_unused(gui_stop(ui));
    mj_free(ui);
}

static ErrorCode str_copy(char* out, cstr str)
{
    if (!str) {
        return ERROR_INVALID_ARG;
    }
    ssize len = cast(ssize, strnlen(str, MJ_STR_CAP));
    if (len == MJ_STR_CAP) {
        return ERROR_CAPACITY;
    }
    memcpy(out, str, cast(usize, len + 1));
    return ERROR_NONE;
}

static ErrorCode gui_add(
    Gui* ui, s32 kind, cstr lbl, f64 init, f64 min, f64 max, f64 step, s32* out)
{
    mj_assert(kind >= WIDGET_BUTTON && kind <= KIND_BOX + BOX_VERTICAL);

    if (out) {
        *out = -1;
    }
    if (!ui || !out || !lbl || !isfinite(init) || !isfinite(min) || !isfinite(max) ||
        !isfinite(step) || min > max || !isfinite(max - min) || init < min || init > max || step < 0) {
        return ERROR_INVALID_ARG;
    }
    if (ui->term.live) {
        return ERROR_INVALID_STATE;
    }
    if (ui->len == MJ_GUI_CAP || (ui->par >= 0 && ui->wdgs[ui->par].depth >= MJ_BOX_DEPTH)) {
        return ERROR_CAPACITY;
    }

    mj_assert(ui->par >= -1 && ui->par < ui->len);

    Widget* wdg = &ui->wdgs[ui->len];
    ErrorCode err = str_copy(wdg->lbl, lbl);
    if (err) {
        return err;
    }

    wdg->kind = kind;
    wdg->par = ui->par;
    wdg->depth = ui->par < 0 ? 0 : ui->wdgs[ui->par].depth + 1;
    wdg->val = init;
    wdg->min = min;
    wdg->max = max;
    wdg->step = step;
    wdg->unit[0] = 0;
#if MJ_SYSTEM_WIN
    wdg->slot.bits = cast(LONG64, value_bits(init));
#else
    atomic_init(&wdg->slot.bits, value_bits(init));
#endif
    *out = ui->len++;
    return ERROR_NONE;
}

ErrorCode gui_open_box(Gui* ui, BoxKind kind, cstr lbl, s32* out)
{
    if (out) {
        *out = -1;
    }
    if (kind < BOX_TAB || kind > BOX_VERTICAL) {
        return ERROR_INVALID_ARG;
    }
    ErrorCode err = gui_add(ui, KIND_BOX + kind, lbl, 0, 0, 0, 0, out);
    if (err) {
        return err;
    }

    ui->par = *out;
    return ERROR_NONE;
}

ErrorCode gui_close_box(Gui* ui)
{
    if (!ui) {
        return ERROR_INVALID_ARG;
    }
    if (ui->term.live || ui->par < 0) {
        return ERROR_INVALID_STATE;
    }
    mj_assert(ui->par < ui->len && ui->wdgs[ui->par].kind >= KIND_BOX);
    ui->par = ui->wdgs[ui->par].par;
    return ERROR_NONE;
}

ErrorCode gui_add_button(Gui* ui, cstr lbl, s32* out)
{
    return gui_add(ui, WIDGET_BUTTON, lbl, 0, 0, 1, 1, out);
}

ErrorCode gui_add_check_button(Gui* ui, cstr lbl, f64 init, s32* out)
{
    return gui_add(ui, WIDGET_CHECK_BUTTON, lbl, init, 0, 1, 1, out);
}

ErrorCode gui_add_slider(Gui* ui, cstr lbl, f64 init, f64 min, f64 max, f64 step, s32* out)
{
    return gui_add(ui, WIDGET_SLIDER, lbl, init, min, max, step, out);
}

ErrorCode gui_add_num_entry(Gui* ui, cstr lbl, f64 init, f64 min, f64 max, f64 step, s32* out)
{
    return gui_add(ui, WIDGET_NUM_ENTRY, lbl, init, min, max, step, out);
}

ErrorCode gui_add_bargraph(Gui* ui, cstr lbl, f64 min, f64 max, s32* out)
{
    return gui_add(ui, WIDGET_BARGRAPH, lbl, min, min, max, 0, out);
}

static b32 gui_valid(Gui const* ui, s32 id)
{
    return ui && id >= 0 && id < ui->len && ui->wdgs[id].kind < KIND_BOX;
}

ErrorCode gui_set_val(Gui* ui, s32 id, f64 val)
{
    if (!gui_valid(ui, id) || !isfinite(val)) {
        return ERROR_INVALID_ARG;
    }
    Widget* wdg = &ui->wdgs[id];
    wdg->val = wdg->kind == WIDGET_BARGRAPH ? val : clamp(val, wdg->min, wdg->max);
    return ERROR_NONE;
}

ErrorCode gui_set_unit(Gui* ui, s32 id, cstr unit)
{
    if (!gui_valid(ui, id)) {
        return ERROR_INVALID_ARG;
    }
    return str_copy(ui->wdgs[id].unit, unit);
}

ErrorCode gui_get_value(Gui* ui, s32 id, Value** out)
{
    if (out) {
        *out = NULL;
    }
    if (!out || !gui_valid(ui, id)) {
        return ERROR_INVALID_ARG;
    }
    *out = &ui->wdgs[id].slot;
    return ERROR_NONE;
}

static ErrorCode term_write(cstr buf, ssize len)
{
    mj_assert(owner);
    mj_assert(owner->term.live);
    mj_assert(buf);
    mj_assert(len >= 0);

#if MJ_SYSTEM_WIN
    while (len > 0) {
        mj_assert(cast(u64, len) <= UINT32_MAX);

        DWORD size = cast(DWORD, len);
        DWORD done = 0;
        if (!WriteFile(owner->term.out, buf, size, &done, NULL) || done == 0) {
            return ERROR_IO;
        }
        buf += done;
        len -= cast(ssize, done);
    }
#else
    while (len > 0) {
        ssize n = cast(ssize, write(STDOUT_FILENO, buf, cast(usize, len)));
        if (n < 0 && errno == EINTR && !mj_flag_get(&halted)) {
            continue;
        }
        if (n <= 0) {
            return ERROR_IO;
        }
        buf += n;
        len -= n;
    }
#endif
    return ERROR_NONE;
}

static void term_size(Term* term)
{
    mj_assert(term);

#if MJ_SYSTEM_WIN
    CONSOLE_SCREEN_BUFFER_INFO size;
    if (GetConsoleScreenBufferInfo(term->out, &size)) {
        term->rows = cast(s32, size.srWindow.Bottom) - cast(s32, size.srWindow.Top) + 1;
        term->cols = cast(s32, size.srWindow.Right) - cast(s32, size.srWindow.Left) + 1;
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
static BOOL WINAPI term_control(DWORD kind)
{
    if (kind == CTRL_C_EVENT || kind == CTRL_BREAK_EVENT || kind == CTRL_CLOSE_EVENT ||
        kind == CTRL_LOGOFF_EVENT || kind == CTRL_SHUTDOWN_EVENT) {
        mj_flag_set(&halted, 1);
        return TRUE;
    }
    return FALSE;
}
#else
static void term_signal(int sig)
{
    if (sig == SIGWINCH) {
        resized = 1;
    } else {
        halted = sig;
    }
}
#endif

ErrorCode gui_stop(Gui* ui)
{
    if (!ui) {
        return ERROR_INVALID_ARG;
    }
    if (!ui->term.live) {
        return ERROR_NONE;
    }

    mj_assert(owner == ui);

    for (s32 i = 0; i < ui->len; ++i) {
        if (ui->wdgs[i].kind == WIDGET_BUTTON) {
            ui->wdgs[i].val = 0;
            value_store(&ui->wdgs[i].slot, 0);
        }
    }
    ui->press = -1;

    ErrorCode err = ERROR_NONE;
#if MJ_SYSTEM_WIN
    static char const end[] = "\033[?1002l\033[?1004l\033[?1006l\033[?2004l\033[0m\033[?25h\033[?1049l";
    if (term_write(end, cast(ssize, sizeof(end) - 1))) {
        err = ERROR_IO;
    }
    if (!SetConsoleOutputCP(ui->term.out_cp)) {
        err = ERROR_TERM;
    }
    if (!SetConsoleMode(ui->term.in, ui->term.in_mode)) {
        err = ERROR_TERM;
    }
    if (!SetConsoleMode(ui->term.out, ui->term.out_mode)) {
        err = ERROR_TERM;
    }
    if (!SetConsoleCtrlHandler(term_control, FALSE)) {
        err = ERROR_TERM;
    }
#else
    /* Restore termios even when stdout has disappeared. Retry interrupted calls. */
    int res;
    do {
        res = tcsetattr(STDIN_FILENO, TCSANOW, &ui->term.prev);
    } while (res < 0 && errno == EINTR);
    if (res < 0) {
        err = ERROR_TERM;
    }
    static char const end[] = "\033[?1002l\033[?1004l\033[?1006l\033[?2004l\033[0m\033[?25h\033[?1049l";
    if (term_write(end, cast(ssize, sizeof(end) - 1))) {
        err = ERROR_IO;
    }
    for (ssize i = 0; i < mj_count_of(sigs); ++i) {
        if (sigaction(sigs[i], &ui->term.acts[i], NULL) < 0) {
            err = ERROR_TERM;
        }
    }
#endif
    ui->term.live = 0;
    owner = NULL;
    return err;
}

static ErrorCode term_start(Gui* ui)
{
    mj_assert(ui);

    if (owner || ui->term.live || ui->par >= 0) {
        return ERROR_INVALID_STATE;
    }
#if MJ_SYSTEM_WIN
    ui->term.in = GetStdHandle(STD_INPUT_HANDLE);
    ui->term.out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!ui->term.in || ui->term.in == INVALID_HANDLE_VALUE ||
        !ui->term.out || ui->term.out == INVALID_HANDLE_VALUE ||
        !GetConsoleMode(ui->term.in, &ui->term.in_mode) ||
        !GetConsoleMode(ui->term.out, &ui->term.out_mode)) {
        return ERROR_TERM;
    }
    ui->term.out_cp = GetConsoleOutputCP();
    ui->term.down = 0;
    DWORD in_mode = (ui->term.in_mode | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS) &
        ~cast(DWORD, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_QUICK_EDIT_MODE |
            ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_PROCESSED_INPUT);
    DWORD out_mode = ui->term.out_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    mj_flag_set(&resized, 0);
    mj_flag_set(&halted, 0);
    if (!SetConsoleCtrlHandler(term_control, TRUE)) {
        return ERROR_TERM;
    }
    if (!SetConsoleMode(ui->term.in, in_mode) || !SetConsoleMode(ui->term.out, out_mode) ||
        !SetConsoleOutputCP(CP_UTF8)) {
        mj_unused(SetConsoleOutputCP(ui->term.out_cp));
        mj_unused(SetConsoleMode(ui->term.in, ui->term.in_mode));
        mj_unused(SetConsoleMode(ui->term.out, ui->term.out_mode));
        mj_unused(SetConsoleCtrlHandler(term_control, FALSE));
        return ERROR_TERM;
    }
#else
    cstr env = getenv("TERM");
    if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || (env && strcmp(env, "dumb") == 0)) {
        return ERROR_TERM;
    }
    if (tcgetattr(STDIN_FILENO, &ui->term.prev) < 0) {
        return ERROR_TERM;
    }
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = term_signal;
    sigemptyset(&act.sa_mask);
    resized = halted = 0;
    for (ssize i = 0; i < mj_count_of(sigs); ++i) {
        if (sigaction(sigs[i], &act, &ui->term.acts[i]) < 0) {
            while (i > 0) {
                --i;
                mj_unused(sigaction(sigs[i], &ui->term.acts[i], NULL));
            }
            return ERROR_TERM;
        }
    }
#endif
    ui->term.live = 1;
    ui->term.esc = 0;
    ui->press = -1;
    owner = ui;
#if MJ_SYSTEM_UNIX
    struct termios raw = ui->term.prev;
    raw.c_lflag &= cast(tcflag_t, ~(ICANON | ECHO | IEXTEN | ISIG));
    raw.c_iflag &= cast(tcflag_t, ~(IXON | ICRNL | INLCR));
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) < 0) {
        mj_unused(gui_stop(ui));
        return ERROR_TERM;
    }
#endif
    term_size(&ui->term);
    static char const beg[] = "\033[?1049h\033[?25l\033[2J\033[?1002h\033[?1004h\033[?1006h\033[?2004h";
    return term_write(beg, cast(ssize, sizeof(beg) - 1));
}

static void buf_put(Gui* ui, cstr str, ssize len)
{
    mj_assert(ui);
    mj_assert(str);
    mj_assert(len >= 0);

    if (len > cast(ssize, sizeof(ui->buf)) - ui->used) {
        mj_panic("frame capacity exceeded");
    }
    memcpy(ui->buf + ui->used, str, cast(usize, len));
    ui->used += len;
}

static s32 min_int(s32 a, s32 b)
{
    return a < b ? a : b;
}

/* All groups retain their Faust hierarchy. Horizontal groups share a row when
 * each child has useful width; tab groups are expanded, keeping all controls visible. */
static s32 layout(Gui* ui, s32 par, s32 x, s32 y, s32 width)
{
    mj_assert(width >= 0);

    s32 count = 0;
    for (s32 i = par + 1; i < ui->len; ++i) {
        if (ui->wdgs[i].par == par) {
            ++count;
        }
    }

    b32 horiz = par >= 0 && ui->wdgs[par].kind == KIND_BOX + BOX_HORIZONTAL &&
        count > 1 && width / count >= 36;
    s32 span = horiz ? (width - (count - 1) * 2) / count : width;
    s32 row = y;
    s32 height = 0;
    s32 gap = 0;
    for (s32 i = par + 1; i < ui->len; ++i) {
        Widget* wdg = &ui->wdgs[i];
        if (wdg->par != par) {
            continue;
        }
        s32 size = 1;
        if (wdg->kind >= KIND_BOX) {
            s32 inner = span > 6 ? span - 6 : 0;
            size = 4 + layout(ui, i, x + 3, row + 2, inner);
        }
        wdg->rect = (Rect){ x, row, span, size };
        wdg->hit = (Rect){ 0, 0, 0, 0 };
        if (horiz) {
            x += span + 2;
            if (size > height) {
                height = size;
            }
        } else {
            gap = wdg->kind >= KIND_BOX ? 1 : 0;
            row += size + gap;
            height = row - y;
        }
    }
    return height - (horiz ? 0 : gap);
}

static void cell_put(Gui* ui, s32 x, s32 y, u32 ch)
{
    if (x >= 0 && x < ui->cols && y >= 0 && y < ui->rows) {
        ui->cells[y][x] = ch;
    }
}

/* Labels are sanitized and kept cell-aligned. Combining marks are skipped;
 * wide glyphs use two cells. No locale or process-wide locale mutation. */
static s32 glyph_width(u32 ch)
{
    if ((ch >= 0x300 && ch <= 0x36f) || (ch >= 0xfe00 && ch <= 0xfe0f) || ch == 0x200d) {
        return 0;
    }
    return ch >= 0x1100 && (ch <= 0x115f || ch == 0x2329 || ch == 0x232a ||
        (ch >= 0x2e80 && ch <= 0xa4cf && ch != 0x303f) ||
        (ch >= 0xac00 && ch <= 0xd7a3) || (ch >= 0xf900 && ch <= 0xfaff) ||
        (ch >= 0xfe10 && ch <= 0xfe19) || (ch >= 0xfe30 && ch <= 0xfe6f) ||
        (ch >= 0xff00 && ch <= 0xff60) || (ch >= 0xffe0 && ch <= 0xffe6) ||
        (ch >= 0x1f300 && ch <= 0x1faff) || (ch >= 0x20000 && ch <= 0x3fffd)) ? 2 : 1;
}

static s32 text_put(Gui* ui, s32 x, s32 y, s32 width, cstr str)
{
    s32 end = min_int(x + width, ui->cols);
    while (*str && x < end) {
        u32 ch = cast(u8, *str++);
        s32 need = ch >= 0xc2 && ch <= 0xdf ? 1 :
            (ch >= 0xe0 && ch <= 0xef ? 2 : (ch >= 0xf0 && ch <= 0xf4 ? 3 : 0));
        u32 low = need == 1 ? 0x80u : (need == 2 ? 0x800u : 0x10000u);
        if (need) {
            ch &= (1u << (6 - need)) - 1u;
            for (s32 i = 0; i < need; ++i) {
                if ((cast(u8, *str) & 0xc0u) != 0x80u) {
                    ch = '?';
                    break;
                }
                ch = (ch << 6) | (cast(u8, *str++) & 0x3fu);
            }
            if (ch < low || ch > 0x10ffff || (ch >= 0xd800 && ch <= 0xdfff)) {
                ch = '?';
            }
        } else if (ch >= 0x80) {
            ch = '?';
        }
        if (ch < 0x20 || (ch >= 0x7f && ch < 0xa0) ||
            (ch >= 0x200b && ch <= 0x200f) || (ch >= 0x2028 && ch <= 0x202e) ||
            (ch >= 0x2060 && ch <= 0x206f)) {
            ch = '?';
        }
        s32 span = glyph_width(ch);
        if (!span) {
            continue;
        }
        if (x + span > end) {
            break;
        }
        cell_put(ui, x, y, ch);
        if (span == 2) {
            cell_put(ui, x + 1, y, 0);
        }
        x += span;
    }
    return x;
}

static void box_put(Gui* ui, Rect rect, cstr lbl)
{
    if (rect.w < 2) {
        return;
    }
    s32 last = rect.x + rect.w - 1;
    s32 end = rect.y + rect.h - 1;
    for (s32 x = rect.x + 1; x < last && x < ui->cols; ++x) {
        cell_put(ui, x, rect.y, 0x2500);
        cell_put(ui, x, end, 0x2500);
    }
    for (s32 y = rect.y + 1; y < end && y < ui->rows; ++y) {
        if (y >= 0) {
            cell_put(ui, rect.x, y, 0x2502);
            cell_put(ui, last, y, 0x2502);
        }
    }
    cell_put(ui, rect.x, rect.y, 0x256d);
    cell_put(ui, last, rect.y, 0x256e);
    cell_put(ui, rect.x, end, 0x2570);
    cell_put(ui, last, end, 0x256f);
    if (*lbl && rect.w >= 8) {
        cell_put(ui, rect.x + 2, rect.y, ' ');
        s32 end_x = text_put(ui, rect.x + 3, rect.y, rect.w - 7, lbl);
        cell_put(ui, end_x, rect.y, ' ');
    }
}

static void widget_put(Gui* ui, Widget* wdg)
{
    Rect rect = wdg->rect;
    rect.y -= ui->top;
    if (rect.y < 0 || rect.y >= ui->rows - 1 || rect.w < 8) {
        return;
    }
    s32 label = min_int(12, rect.w / 4);
    text_put(ui, rect.x, rect.y, label, wdg->lbl);
    s32 x = rect.x + label + 1;
    s32 width = rect.w - label - 1;
    if (wdg->kind <= WIDGET_CHECK_BUTTON) {
        text_put(ui, x, rect.y, width, wdg->kind == WIDGET_BUTTON ?
            (wdg->val != 0 ? "[ ON ]" : "[    ]") : (wdg->val != 0 ? "[x]" : "[ ]"));
        wdg->hit = (Rect){ x, wdg->rect.y, min_int(width, 6), 1 };
        return;
    }

    char val[64];
    mj_unused(snprintf(val, sizeof(val), "%.6g %.32s", wdg->val, wdg->unit));
    if (wdg->kind == WIDGET_NUM_ENTRY) {
        if (width >= 9) {
            text_put(ui, x, rect.y, 3, "[-]");
            text_put(ui, x + 4, rect.y, width - 8, val);
            text_put(ui, x + width - 3, rect.y, 3, "[+]");
            wdg->hit = (Rect){ x, wdg->rect.y, width, 1 };
        } else {
            text_put(ui, x, rect.y, width, val);
        }
        return;
    }
    s32 tail = min_int(18, width / 2);
    s32 span = width - tail - 2;
    if (span < 2) {
        text_put(ui, x, rect.y, width, val);
        return;
    }
    f64 frac = wdg->max == wdg->min ? 0 :
        clamp((wdg->val - wdg->min) / (wdg->max - wdg->min), 0, 1);
    b32 meter = wdg->kind == WIDGET_BARGRAPH;
    if (meter) {
        cell_put(ui, x++, rect.y, '[');
        span -= 2;
    }
    s32 pos = cast(s32, round(frac * (span - 1)));
    for (s32 j = 0; j < span; ++j) {
        u32 ch = meter ? (cast(f64, j) < frac * span ? 0x2588u : 0x2591u) :
            (j == pos ? 0x25cfu : 0x2501u);
        cell_put(ui, x + j, rect.y, ch);
    }
    if (meter) {
        cell_put(ui, x + span, rect.y, ']');
    } else {
        wdg->hit = (Rect){ x, wdg->rect.y, span, 1 };
    }
    text_put(ui, rect.x + rect.w - tail, rect.y, tail, val);
}

static void buf_glyph(Gui* ui, u32 ch)
{
    char bytes[4];
    ssize len = 0;
    if (!ch) {
        return;
    }
    if (ch < 0x80) {
        bytes[len++] = cast(char, ch);
    } else {
        if (ch >= 0x10000) {
            bytes[len++] = cast(char, 0xf0u | (ch >> 18));
            bytes[len++] = cast(char, 0x80u | ((ch >> 12) & 0x3fu));
        } else if (ch >= 0x800) {
            bytes[len++] = cast(char, 0xe0u | (ch >> 12));
        }
        bytes[len++] = cast(char, (ch < 0x800 ? 0xc0u : 0x80u) | ((ch >> 6) & 0x3fu));
        bytes[len++] = cast(char, 0x80u | (ch & 0x3fu));
    }
    buf_put(ui, bytes, len);
}

static ErrorCode gui_render(Gui* ui)
{
    mj_assert(ui && ui->term.live);
    ui->cols = min_int(ui->term.cols > 1 ? ui->term.cols - 1 : 1, MJ_VIEW_COLS);
    ui->rows = min_int(ui->term.rows > 0 ? ui->term.rows : 1, MJ_VIEW_ROWS);
    for (s32 y = 0; y < ui->rows; ++y) {
        for (s32 x = 0; x < ui->cols; ++x) {
            ui->cells[y][x] = ' ';
        }
    }

    /* A single Faust root box is already the outer frame: do not duplicate it. */
    b32 root = ui->len > 0 && ui->wdgs[0].kind >= KIND_BOX;
    for (s32 i = 1; i < ui->len; ++i) {
        if (ui->wdgs[i].par == -1) {
            root = 0;
        }
    }
    ui->height = layout(ui, -1, root ? 0 : 3, root ? 0 : 2,
        root ? ui->cols : (ui->cols > 6 ? ui->cols - 6 : 0)) + (root ? 0 : 4);
    s32 last = ui->height > ui->rows - 1 ? ui->height - (ui->rows - 1) : 0;
    ui->top = min_int(ui->top, last);
    mj_assert(ui->top >= 0);
    if (!root) {
        box_put(ui, (Rect){ 0, -ui->top, ui->cols, ui->height }, "DSP");
    }
    for (s32 i = 0; i < ui->len; ++i) {
        Widget* wdg = &ui->wdgs[i];
        if (wdg->kind >= KIND_BOX) {
            Rect rect = wdg->rect;
            rect.y -= ui->top;
            box_put(ui, rect, wdg->lbl);
        } else {
            widget_put(ui, wdg);
        }
    }
    for (s32 x = 0; x < ui->cols; ++x) {
        ui->cells[ui->rows - 1][x] = ' ';
    }
    text_put(ui, 0, ui->rows - 1, ui->cols, "q quit");
    if (last) {
        text_put(ui, 9, ui->rows - 1, ui->cols - 9, "[prev] [next]");
    }

    ui->used = 0;
    buf_put(ui, "\033[H", 3);
    for (s32 y = 0; y < ui->rows; ++y) {
        for (s32 x = 0; x < ui->cols; ++x) {
            buf_glyph(ui, ui->cells[y][x]);
        }
        buf_put(ui, "\033[K", 3);
        if (y + 1 < ui->rows) {
            buf_put(ui, "\r\n", 2);
        }
    }
    buf_put(ui, "\033[J", 3);
    return term_write(ui->buf, ui->used);
}

ErrorCode gui_start(Gui* ui)
{
    if (!ui) {
        return ERROR_INVALID_ARG;
    }
    if (ui->term.live) {
        return ERROR_INVALID_STATE;
    }
    ErrorCode err = term_start(ui);
    if (!err) {
        err = gui_render(ui);
    }
    if (err && owner == ui) {
        mj_unused(gui_stop(ui));
    }
    return err;
}

/* Bounded streaming parser: sequences may span several gui_step calls.
 * Consume unsupported CSI/OSC and bracketed paste instead of treating payload as keys. */
static Input term_input(Term* term, u8 ch)
{
    Input out = { INPUT_NONE, 0, 0 };
    if (term->esc == 4) {
        static cstr const end = "\033[201~";
        term->code = ch == cast(u8, end[term->code]) ? term->code + 1 : (ch == 27 ? 1 : 0);
        if (term->code == 6) {
            term->esc = 0;
        }
        return out;
    }
    if (term->esc == 5 || term->esc == 6) {
        if (ch == 7 || (term->esc == 6 && ch == '\\')) {
            term->esc = 0;
        } else {
            term->esc = ch == 27 ? 6 : 5;
        }
        return out;
    }
    if (ch == 27) {
        term->esc = 1;
        return out;
    }
    if (term->esc == 1) {
        term->esc = ch == '[' || ch == 'O' ? 2 :
            (ch == ']' || ch == 'P' || ch == '_' || ch == '^' ? 5 : 0);
        term->mouse = 0;
        term->arg = term->code = 0;
        memset(term->args, 0, sizeof(term->args));
        return out;
    }
    if (term->esc == 2 || term->esc == 3) {
        if (ch >= 0x40 && ch <= 0x7e) {
            b32 valid = term->esc == 2;
            term->esc = 0;
            if (valid && !term->mouse && ch == '~' && term->args[0] == 200) {
                term->esc = 4;
                term->code = 0;
            } else if (valid && !term->mouse && ch == 'O' && term->code == 0) {
                out.kind = INPUT_CANCEL;
            } else if (valid && term->mouse && term->arg == 2 &&
                term->args[1] > 0 && term->args[2] > 0 && (ch == 'M' || ch == 'm')) {
                s32 btn = term->args[0];
                /* Ignore wheel, extra buttons and passive motion in their entirety. */
                if ((btn & (64 | 128)) == 0 && (btn & 3) == 0) {
                    out = (Input){ ch == 'm' ? INPUT_UP : ((btn & 32) ? INPUT_DRAG : INPUT_DOWN),
                        term->args[1] - 1, term->args[2] - 1 };
                }
            }
            return out;
        }
        if (term->esc == 3) {
            return out;
        }
        if (ch == '<' && term->code == 0) {
            term->mouse = 1;
        } else if (ch >= '0' && ch <= '9') {
            if (term->args[term->arg] > 100000) {
                term->esc = 3;
            } else {
                term->args[term->arg] = term->args[term->arg] * 10 + ch - '0';
            }
        } else if (ch == ';' && term->arg < 2) {
            ++term->arg;
        } else {
            term->esc = 3;
        }
        ++term->code;
        return out;
    }
    if (ch == 'q') {
        out.kind = INPUT_QUIT;
    }
    return out;
}

static ErrorCode term_read(Term* term, s32 wait_ms, Input* out)
{
    mj_assert(term && out);
    mj_assert(wait_ms >= 0 && wait_ms <= 1000);
    *out = (Input){ INPUT_NONE, 0, 0 };

#if MJ_SYSTEM_WIN
    DWORD wait = WaitForSingleObject(term->in, cast(DWORD, wait_ms));
    if (wait == WAIT_TIMEOUT) {
        return ERROR_NONE;
    }
    if (wait != WAIT_OBJECT_0) {
        return ERROR_IO;
    }
    for (s32 i = 0; i < 64; ++i) {
        INPUT_RECORD evt;
        DWORD done = 0;
        /* Ignored events must never leave ReadConsoleInputW blocking. */
        if (!GetNumberOfConsoleInputEvents(term->in, &done)) {
            return ERROR_IO;
        }
        if (!done) {
            return ERROR_NONE;
        }
        if (!ReadConsoleInputW(term->in, &evt, 1, &done) || !done) {
            return ERROR_IO;
        }
        if (evt.EventType == WINDOW_BUFFER_SIZE_EVENT) {
            mj_flag_set(&resized, 1);
            return ERROR_NONE;
        }
        if (evt.EventType == FOCUS_EVENT && !evt.Event.FocusEvent.bSetFocus) {
            term->down = 0;
            out->kind = INPUT_CANCEL;
            return ERROR_NONE;
        }
        if (evt.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD evt_mouse = evt.Event.MouseEvent;
            if (evt_mouse.dwEventFlags & (MOUSE_WHEELED | MOUSE_HWHEELED)) {
                continue;
            }
            b32 down = (evt_mouse.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) != 0;
            s32 kind = down ? (term->down ? INPUT_DRAG : INPUT_DOWN) :
                (term->down ? INPUT_UP : INPUT_NONE);
            term->down = down;
            CONSOLE_SCREEN_BUFFER_INFO info;
            if (!GetConsoleScreenBufferInfo(term->out, &info)) {
                return ERROR_IO;
            }
            *out = (Input){ kind, cast(s32, evt_mouse.dwMousePosition.X) - info.srWindow.Left,
                cast(s32, evt_mouse.dwMousePosition.Y) - info.srWindow.Top };
        } else if (evt.EventType == KEY_EVENT && evt.Event.KeyEvent.bKeyDown) {
            WCHAR ch = evt.Event.KeyEvent.uChar.UnicodeChar;
            if (ch <= UINT8_MAX) {
                *out = term_input(term, cast(u8, ch));
            }
        }
        if (out->kind != INPUT_NONE) {
            return ERROR_NONE;
        }
    }
#else
    for (s32 i = 0; i < 256; ++i) {
        if (mj_flag_get(&halted) || mj_flag_get(&resized)) {
            return ERROR_NONE;
        }
        struct pollfd fd = { STDIN_FILENO, POLLIN, 0 };
        int res = poll(&fd, 1, i == 0 ? wait_ms : 0);
        if (res < 0 && errno == EINTR) {
            return ERROR_NONE;
        }
        if (res < 0 || (fd.revents & (POLLERR | POLLNVAL))) {
            return ERROR_IO;
        }
        if (!res) {
            return ERROR_NONE;
        }
        if (!(fd.revents & POLLIN) && (fd.revents & POLLHUP)) {
            out->kind = INPUT_QUIT;
            return ERROR_NONE;
        }
        u8 ch;
        ssize n = cast(ssize, read(STDIN_FILENO, &ch, 1));
        if (n < 0 && (errno == EINTR || errno == EAGAIN)) {
            return ERROR_NONE;
        }
        if (n < 0) {
            return ERROR_IO;
        }
        if (!n) {
            out->kind = INPUT_QUIT;
            return ERROR_NONE;
        }
        *out = term_input(term, ch);
        if (out->kind != INPUT_NONE) {
            return ERROR_NONE;
        }
    }
#endif
    return ERROR_NONE;
}

static b32 contains(Rect rect, s32 x, s32 y)
{
    return x >= rect.x && x - rect.x < rect.w && y >= rect.y && y - rect.y < rect.h;
}

static void gui_release(Gui* ui, Event* out)
{
    if (ui->press < 0) {
        return;
    }
    mj_assert(ui->press < ui->len);
    Widget* wdg = &ui->wdgs[ui->press];
    if (wdg->kind == WIDGET_BUTTON) {
        wdg->val = 0;
        *out = (Event){ EVENT_BUTTON_RELEASE, ui->press, 0 };
    }
    ui->press = -1;
}

static void gui_mouse(Gui* ui, Input in, Event* out)
{
    if (in.kind == INPUT_UP || in.kind == INPUT_CANCEL) {
        gui_release(ui, out);
        return;
    }
    if (in.kind != INPUT_DOWN && in.kind != INPUT_DRAG) {
        return;
    }
    if (in.kind == INPUT_DOWN) {
        /* Capture stays with the original widget until release, even outside its box. */
        if (ui->press >= 0) {
            return;
        }
        if (in.y == ui->rows - 1) {
            s32 page = ui->rows > 2 ? ui->rows - 2 : 1;
            if (in.x >= 9 && in.x < 15) {
                ui->top = ui->top > page ? ui->top - page : 0;
            } else if (in.x >= 16 && in.x < 22) {
                ui->top += page;
            }
            return;
        }
        for (s32 i = 0; i < ui->len; ++i) {
            if (ui->wdgs[i].kind < WIDGET_BARGRAPH &&
                contains(ui->wdgs[i].hit, in.x, in.y + ui->top)) {
                ui->press = i;
                break;
            }
        }
    }
    if (ui->press < 0) {
        return;
    }

    Widget* wdg = &ui->wdgs[ui->press];
    f64 val = wdg->val;
    EventKind kind = EVENT_VALUE;
    if (wdg->kind == WIDGET_BUTTON && in.kind == INPUT_DOWN) {
        val = 1;
        kind = EVENT_BUTTON_PRESS;
    } else if (wdg->kind == WIDGET_CHECK_BUTTON && in.kind == INPUT_DOWN) {
        val = val == 0 ? 1 : 0;
    } else if (wdg->kind == WIDGET_NUM_ENTRY && in.kind == INPUT_DOWN) {
        f64 step = wdg->step > 0 ? wdg->step : (wdg->max - wdg->min) / 100;
        if (in.x < wdg->hit.x + 3) {
            val -= step;
        } else if (in.x >= wdg->hit.x + wdg->hit.w - 3) {
            val += step;
        }
        val = clamp(val, wdg->min, wdg->max);
    } else if (wdg->kind == WIDGET_SLIDER) {
        mj_assert(wdg->hit.w >= 2);
        f64 frac = clamp(cast(f64, in.x - wdg->hit.x) / (wdg->hit.w - 1), 0, 1);
        val = wdg->min + frac * (wdg->max - wdg->min);
        if (wdg->step > 0 && frac > 0 && frac < 1) {
            f64 pos = (val - wdg->min) / wdg->step;
            if (isfinite(pos)) {
                val = wdg->min + round(pos) * wdg->step;
            }
        }
        val = clamp(val, wdg->min, wdg->max);
    }
    if (val != wdg->val) {
        wdg->val = val;
        *out = (Event){ kind, ui->press, val };
    }
}

ErrorCode gui_step(Gui* ui, s32 wait_ms, Event* out)
{
    if (out) {
        *out = (Event){ EVENT_NONE, -1, 0 };
    }
    ErrorCode err = ERROR_NONE;
    if (!ui || !out || wait_ms < -1 || wait_ms > 1000) {
        err = ERROR_INVALID_ARG;
    } else if (!ui->term.live) {
        err = ERROR_INVALID_STATE;
    }
    if (err) {
        if (ui && ui->term.live) {
            mj_unused(gui_stop(ui));
        }
        return err;
    }

    Input in;
    err = term_read(&ui->term, wait_ms < 0 ? 1000 / MJ_GUI_FPS : wait_ms, &in);
    if (mj_flag_get(&halted) || in.kind == INPUT_QUIT) {
        gui_release(ui, out);
        out->kind = EVENT_QUIT;
    } else if (mj_flag_get(&resized)) {
        mj_flag_set(&resized, 0);
        term_size(&ui->term);
        gui_release(ui, out);
        if (out->kind == EVENT_NONE) {
            out->kind = EVENT_RESIZE;
        }
    } else if (!err) {
        gui_mouse(ui, in, out);
    }
    if (!err) {
        err = gui_render(ui);
    }
    if (err) {
        mj_unused(gui_stop(ui));
    }
    return err;
}

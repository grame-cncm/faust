#ifndef MJ_TERMGUI_H
#define MJ_TERMGUI_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef uint64_t u64;
typedef int32_t s32;
typedef size_t usize;
typedef float f32;
typedef double f64;
typedef s32 b32;
typedef char const* cstr;

#if defined(_WIN32)
#define MJ_SYSTEM_WIN 1
#else
#define MJ_SYSTEM_WIN 0
#endif
#if defined(__APPLE__) && defined(__MACH__)
#define MJ_SYSTEM_OSX 1
#else
#define MJ_SYSTEM_OSX 0
#endif
#if defined(__linux__)
#define MJ_SYSTEM_LINUX 1
#else
#define MJ_SYSTEM_LINUX 0
#endif
#define MJ_SYSTEM_UNIX (MJ_SYSTEM_OSX || MJ_SYSTEM_LINUX)

#ifndef mj_noreturn
#if defined(__clang__) || defined(__GNUC__)
#define mj_noreturn __attribute__((noreturn))
#elif defined(_MSC_VER)
#define mj_noreturn __declspec(noreturn)
#else
#define mj_noreturn
#endif
#endif
#ifndef MJ_PRINTF_ARGS
#if defined(__clang__) || defined(__GNUC__)
#define MJ_PRINTF_ARGS(fmt, args) __attribute__((format(printf, fmt, args)))
#else
#define MJ_PRINTF_ARGS(fmt, args)
#endif
#endif

#ifdef __cplusplus
#define MJ_STATIC_ASSERT(expr, msg) static_assert(expr, msg)
extern "C" {
#else
#define MJ_STATIC_ASSERT(expr, msg) _Static_assert(expr, msg)
#endif

MJ_STATIC_ASSERT(sizeof(s32) == 4, "s32 ABI");
MJ_STATIC_ASSERT(sizeof(u64) == 8, "u64 ABI");
MJ_STATIC_ASSERT(sizeof(f32) == 4, "f32 ABI");
MJ_STATIC_ASSERT(sizeof(f64) == 8, "f64 ABI");

#ifndef MJ_DEBUG
#ifdef NDEBUG
#define MJ_DEBUG 0
#else
#define MJ_DEBUG 1
#endif
#endif
#ifndef MJ_ALLOC
#define MJ_ALLOC(size) malloc(size)
#endif
#ifndef MJ_FREE
#define MJ_FREE(ptr) free(ptr)
#endif
#ifndef MJ_GUI_CAP
#define MJ_GUI_CAP 256
#endif
#ifndef MJ_STR_CAP
#define MJ_STR_CAP 256
#endif
#ifndef MJ_GUI_FPS
#define MJ_GUI_FPS 30
#endif

void gui_log(cstr file, s32 line, cstr func, cstr fmt, ...) MJ_PRINTF_ARGS(4, 5);
mj_noreturn void gui_panic(cstr file, s32 line, cstr func, cstr fmt, ...) MJ_PRINTF_ARGS(4, 5);

#ifndef MJ_PANIC
#define MJ_PANIC(...) gui_panic(__FILE__, __LINE__, __func__, __VA_ARGS__)
#endif
#ifndef MJ_DEBUG_LOG
#if MJ_DEBUG
#define MJ_DEBUG_LOG(...) gui_log(__FILE__, __LINE__, __func__, __VA_ARGS__)
#else
#define MJ_DEBUG_LOG(...) ((void)0)
#endif
#endif
#ifndef MJ_ASSERT_MSG
#if MJ_DEBUG
#define MJ_ASSERT_MSG(expr, ...) do { if (!(expr)) { \
    gui_log(__FILE__, __LINE__, __func__, "assertion failed: %s", #expr); \
    MJ_PANIC(__VA_ARGS__); \
} } while (0)
#else
#define MJ_ASSERT_MSG(expr, ...) ((void)0)
#endif
#endif
#ifndef MJ_ASSERT
#if MJ_DEBUG
#define MJ_ASSERT(expr) do { if (!(expr)) MJ_PANIC("assertion failed: %s", #expr); } while (0)
#else
#define MJ_ASSERT(expr) ((void)0)
#endif
#endif
#define MJ_UNUSED(val) ((void)(val))
#define MJ_COUNT_OF(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MJ_TRY(expr) do { ErrorCode mj_err_ = (expr); if (mj_err_) return mj_err_; } while (0)

typedef s32 ErrorCode;
enum {
    ERROR_NONE, ERROR_INVALID_ARG, ERROR_INVALID_STATE, ERROR_BAD_ALLOC,
    ERROR_CAPACITY, ERROR_IO, ERROR_TERM, ERROR_UNSUPPORTED
};
typedef s32 BoxKind;
enum { BOX_TAB, BOX_HORIZONTAL, BOX_VERTICAL };
typedef s32 WidgetKind;
enum { WIDGET_BUTTON, WIDGET_CHECK_BUTTON, WIDGET_SLIDER, WIDGET_NUM_ENTRY, WIDGET_BARGRAPH };
typedef s32 EventKind;
enum { EVENT_NONE, EVENT_VALUE, EVENT_BUTTON_PRESS, EVENT_BUTTON_RELEASE, EVENT_QUIT, EVENT_RESIZE };

typedef struct Gui Gui;
typedef struct Value Value;
typedef struct Event {
    EventKind kind;
    s32 id;
    f64 val;
} Event;

MJ_STATIC_ASSERT(sizeof(Event) == 16, "Event ABI size");
MJ_STATIC_ASSERT(offsetof(Event, id) == 4, "Event ABI id");
MJ_STATIC_ASSERT(offsetof(Event, val) == 8, "Event ABI val");

/* Except value_*, every operation belongs to the main thread. Only one GUI may
 * own stdin/stdout at a time. Strings are copied; IDs include boxes and widgets.
 * Build before start. Failed additions leave the model unchanged and *out = -1. */
cstr error_str(ErrorCode err);
ErrorCode gui_create(Gui** out);
void gui_destroy(Gui* ui);
ErrorCode gui_start(Gui* ui);
/* wait_ms: -1 uses MJ_GUI_FPS; otherwise 0..1000. Always initializes *out.
 * Errors restore the terminal. QUIT requires stop/destroy (both idempotent). */
ErrorCode gui_step(Gui* ui, s32 wait_ms, Event* out);
ErrorCode gui_stop(Gui* ui);

ErrorCode gui_open_box(Gui* ui, BoxKind kind, cstr lbl, s32* out);
ErrorCode gui_close_box(Gui* ui);
ErrorCode gui_add_button(Gui* ui, cstr lbl, s32* out);
ErrorCode gui_add_check_button(Gui* ui, cstr lbl, f64 init, s32* out);
ErrorCode gui_add_slider(Gui* ui, cstr lbl, f64 init, f64 min, f64 max, f64 step, s32* out);
ErrorCode gui_add_num_entry(Gui* ui, cstr lbl, f64 init, f64 min, f64 max, f64 step, s32* out);
ErrorCode gui_add_bargraph(Gui* ui, cstr lbl, f64 min, f64 max, s32* out);
ErrorCode gui_set_val(Gui* ui, s32 id, f64 val);
ErrorCode gui_set_unit(Gui* ui, s32 id, cstr unit);

/* Optional scalar mailbox for the CPU adapter, NOT a DSP address. Pointer is
 * stable until gui_destroy; stop the audio stream before destroying the GUI.
 * These three value_* operations are lock-free, allocation-free and RT-safe.
 * Independent relaxed scalars: no multi-control transaction or ordering.
 * The library refuses creation on platforms without lock-free u64 atomics. */
ErrorCode gui_get_value(Gui* ui, s32 id, Value** out);
f64 value_load(Value const* ptr);
void value_store(Value* ptr, f64 val);
f64 value_exchange(Value* ptr, f64 val);

#ifdef __cplusplus
}
#endif
#endif

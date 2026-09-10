#ifndef MJ_TERMGUI_H
#define MJ_TERMGUI_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t s32;
typedef size_t usize;
typedef ptrdiff_t ssize;
typedef float f32;
typedef double f64;
typedef s32 b32;
typedef char const* cstr;

#if !defined(MJ_SYSTEM)
#define MJ_SYSTEM 0
#define MJ_SYSTEM_WIN 0
#define MJ_SYSTEM_OSX 0
#define MJ_SYSTEM_LINUX 0
#define MJ_SYSTEM_UNIX 0
#endif

#if defined(_WIN32) || defined(_WIN64)
#undef MJ_SYSTEM_WIN
#define MJ_SYSTEM_WIN 1
#elif defined(__APPLE__) && defined(__MACH__)
#undef MJ_SYSTEM_OSX
#define MJ_SYSTEM_OSX 1
#undef MJ_SYSTEM_UNIX
#define MJ_SYSTEM_UNIX 1
#elif defined(__linux__)
#undef MJ_SYSTEM_LINUX
#define MJ_SYSTEM_LINUX 1
#undef MJ_SYSTEM_UNIX
#define MJ_SYSTEM_UNIX 1
#else
#error "termgui supports Windows, macOS and Linux"
#endif

#if !defined(MJ_COMPILER)
#define MJ_COMPILER 0
#define MJ_COMPILER_MSVC 0
#define MJ_COMPILER_CLANG 0
#define MJ_COMPILER_GCC 0
#define MJ_COMPILER_APPLE 0
#endif

#if defined(_MSC_VER)
#undef MJ_COMPILER_MSVC
#define MJ_COMPILER_MSVC 1
#elif defined(__clang__)
#undef MJ_COMPILER_CLANG
#define MJ_COMPILER_CLANG 1
#if defined(__apple_build_version__)
#undef MJ_COMPILER_APPLE
#define MJ_COMPILER_APPLE 1
#endif
#elif defined(__GNUC__)
#undef MJ_COMPILER_GCC
#define MJ_COMPILER_GCC 1
#else
#error "termgui supports MSVC, Clang and GCC"
#endif

#if MJ_COMPILER_MSVC
#include <intrin.h>
#endif

#ifndef mj_noreturn
#if MJ_COMPILER_MSVC
#define mj_noreturn __declspec(noreturn)
#else
#define mj_noreturn __attribute__((noreturn))
#endif
#endif

#ifndef mj_printf_args
#if MJ_COMPILER_CLANG || MJ_COMPILER_GCC
#define mj_printf_args(fmt, args) __attribute__((format(printf, fmt, args)))
#else
#define mj_printf_args(fmt, args)
#endif
#endif

#ifdef __cplusplus
#define mj_static_assert(expr, msg) static_assert(expr, msg)
extern "C" {
#else
#define mj_static_assert(expr, msg) _Static_assert(expr, msg)
#endif

#define cast(T, val) ((T)(val))
#define mj_unused(val) ((void)(val))
#define mj_count_of(arr) cast(ssize, sizeof(arr) / sizeof((arr)[0]))

mj_static_assert(sizeof(s32) == 4, "s32 ABI");
mj_static_assert(sizeof(u64) == 8, "u64 ABI");
mj_static_assert(sizeof(f32) == 4, "f32 ABI");
mj_static_assert(sizeof(f64) == 8, "f64 ABI");

#ifndef MJ_DEBUG
#ifdef NDEBUG
#define MJ_DEBUG 0
#else
#define MJ_DEBUG 1
#endif
#endif

#ifndef mj_alloc
#define mj_alloc(size) malloc(size)
#endif

#ifndef mj_free
#define mj_free(ptr) free(ptr)
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

/* Bounded presentation storage, independent of DSP/audio buffer sizes. */
#define MJ_VIEW_COLS 256
#define MJ_VIEW_ROWS 128
#define MJ_BOX_DEPTH 64

void gui_log(cstr file, s32 line, cstr func, cstr fmt, ...) mj_printf_args(4, 5);
mj_noreturn void gui_fail(
    cstr kind, cstr expr, cstr file, s32 line, cstr func, cstr fmt, ...) mj_printf_args(6, 7);

#ifndef mj_debug_trap
#if MJ_COMPILER_MSVC
#define mj_debug_trap() __debugbreak()
#elif MJ_COMPILER_CLANG
#define mj_debug_trap() __builtin_debugtrap()
#else
#define mj_debug_trap() __builtin_trap()
#endif
#endif

#ifndef mj_unreachable
#if MJ_COMPILER_MSVC
#define mj_unreachable() do { \
    mj_debug_trap(); \
    __assume(0); \
} while (0)
#else
#define mj_unreachable() do { \
    mj_debug_trap(); \
    __builtin_unreachable(); \
} while (0)
#endif
#endif

#ifndef mj_panic
#define mj_panic(...) gui_fail("panic", NULL, __FILE__, __LINE__, __func__, __VA_ARGS__)
#endif

#ifndef mj_debug
#if MJ_DEBUG
#define mj_debug(...) gui_log(__FILE__, __LINE__, __func__, __VA_ARGS__)
#else
#define mj_debug(...) mj_unused(0)
#endif
#endif

#ifndef mj_assert_msg
#if MJ_DEBUG
#define mj_assert_msg(cond, ...) do { \
    if (!(cond)) { \
        gui_fail("assertion failure", #cond, __FILE__, __LINE__, __func__, __VA_ARGS__); \
    } \
} while (0)
#else
#define mj_assert_msg(cond, ...) mj_unused(0)
#endif
#endif

#ifndef mj_assert
#if MJ_DEBUG
#define mj_assert(cond) mj_assert_msg(cond, "no message")
#else
#define mj_assert(cond) mj_unused(0)
#endif
#endif

typedef s32 ErrorCode;
enum {
    ERROR_NONE,
    ERROR_INVALID_ARG,
    ERROR_INVALID_STATE,
    ERROR_BAD_ALLOC,
    ERROR_CAPACITY,
    ERROR_IO,
    ERROR_TERM,
    ERROR_UNSUPPORTED
};

typedef s32 BoxKind;
enum {
    BOX_TAB,
    BOX_HORIZONTAL,
    BOX_VERTICAL
};

typedef s32 WidgetKind;
enum {
    WIDGET_BUTTON,
    WIDGET_CHECK_BUTTON,
    WIDGET_SLIDER,
    WIDGET_NUM_ENTRY,
    WIDGET_BARGRAPH
};

typedef s32 EventKind;
enum {
    EVENT_NONE,
    EVENT_VALUE,
    EVENT_BUTTON_PRESS,
    EVENT_BUTTON_RELEASE,
    EVENT_QUIT,
    EVENT_RESIZE
};

typedef struct Gui Gui;
typedef struct Value Value;

typedef struct Event {
    EventKind kind;
    s32 id;
    f64 val;
} Event;

mj_static_assert(sizeof(Event) == 16, "Event ABI size");
mj_static_assert(offsetof(Event, id) == 4, "Event ABI id");
mj_static_assert(offsetof(Event, val) == 8, "Event ABI val");

/* Except value_*, every operation belongs to the main thread. Only one GUI may
 * own stdin/stdout at a time. Strings are copied; IDs include boxes and widgets.
 * Build before start. Failed additions leave the model unchanged and *out = -1. */
cstr error_str(ErrorCode err);
ErrorCode gui_create(Gui** out);
void gui_destroy(Gui* ui);
ErrorCode gui_start(Gui* ui);
/* wait_ms: -1 uses MJ_GUI_FPS; otherwise 0..1000. Always initializes *out.
 * Left click/drag edits controls, release ends capture. Wheel and keys other
 * than q are ignored. Buttons stay pressed until release, focus loss or resize.
 * Errors restore the terminal. QUIT requires stop/destroy (both idempotent). */
ErrorCode gui_step(Gui* ui, s32 wait_ms, Event* out);
ErrorCode gui_stop(Gui* ui);

ErrorCode gui_open_box(Gui* ui, BoxKind kind, cstr lbl, s32* out);
ErrorCode gui_close_box(Gui* ui);
ErrorCode gui_add_button(Gui* ui, cstr lbl, s32* out);
ErrorCode gui_add_check_button(Gui* ui, cstr lbl, f64 init, s32* out);
ErrorCode gui_add_slider(
    Gui* ui, cstr lbl, f64 init, f64 min, f64 max, f64 step, s32* out);
ErrorCode gui_add_num_entry(
    Gui* ui, cstr lbl, f64 init, f64 min, f64 max, f64 step, s32* out);
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

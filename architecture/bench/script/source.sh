# Optional Bash/Zsh aliases. All configuration and work live in Python.
# Usage: source script/source.sh

if [ -n "${ZSH_VERSION:-}" ]; then
    _bench_script="${(%):-%x}"
elif [ -n "${BASH_VERSION:-}" ]; then
    _bench_script="${BASH_SOURCE[0]}"
else
    echo "source.sh supports Bash and Zsh; use python3 script/bench.py directly."
    return 1
fi
_bench_python="$(cd "$(dirname "${_bench_script}")" && pwd)/bench.py"
unset _bench_script

bench()                   { python3 "${_bench_python}" "$@"; }
bench_run()               { bench run "$@"; }
bench_run_transpiled()     { bench run-transpiled "$@"; }
bench_clean()             { bench clean "$@"; }
bench_plot() {
    if [ "$#" -eq 2 ]; then
        if [ "$2" = all ]; then
            bench plot "$1"
        else
            bench plot "$1" --case "$2"
        fi
    else
        bench plot "$@"
    fi
}
bench_snapshot()          { bench snapshot "$@"; }
inspect_llvm()            { bench inspect llvm "$@"; }
inspect_asm()             { bench inspect asm "$@"; }
inspect_llvm_gen()         { inspect_llvm "$@"; }
inspect_asm_gen()          { inspect_asm "$@"; }
inspect_llvm_transpiled()  { bench inspect-transpiled llvm "$@"; }
inspect_asm_transpiled()   { bench inspect-transpiled asm "$@"; }

bench_help() {
    cat <<'HELP'

Faust benchmark framework
Fixed setup: 48000 Hz / 128 frames; internal f64, I/O f32.

Commands:
  bench_run <modes> <langs> <sources...>
  bench_run_transpiled <mode> <lang> <path>
  inspect_llvm <modes> <langs> <sources...>
  inspect_asm <modes> <langs> <sources...>
  inspect_llvm_transpiled <mode> <lang> <path>
  inspect_asm_transpiled <mode> <lang> <path>
  bench_plot <name> [case]
  bench_snapshot <name>
  bench_clean [--artifacts-only] [--snapshots]
  bench_help

Selections:
  modes:   scalar, vec, comma-separated values, or all
  langs:   cpp, mojo, cpp,mojo, or all
  sources: DSP names, paths, globs, or all

Examples:
  bench_run all all all
  bench_run scalar mojo bargraph
  bench --jobs 4 --keep-tmp run vec mojo bells
  bench --dry-run run vec mojo bells

Command-specific help: bench_run --help, inspect_asm --help, etc.
HELP
}

bench_help

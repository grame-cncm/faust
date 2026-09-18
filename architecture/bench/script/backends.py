"""C++ and Mojo command construction; no processes or filesystem mutations here."""

import json
from dataclasses import dataclass
from pathlib import Path

from config import BUFF_SIZE, SAMP_RATE, Config


@dataclass(frozen=True)
class Source:
    path: Path
    dsp: str
    lang: str
    mode: str
    purpose: str = "bench"
    transpiled: bool = False


@dataclass(frozen=True)
class Case:
    source: Source
    name: str = "run"

    @property
    def stem(self) -> str:
        s = self.source
        return f"{s.dsp}_{self.name}_{s.mode}_{SAMP_RATE}_{BUFF_SIZE}"


def optimization(config: Config, lang: str) -> str:
    options = config.cpp_options if lang == "cpp" else config.mojo_options
    return " ".join(options).removeprefix("-") or "default"


def generate(config: Config, source: Source, output: Path) -> list[str]:
    options = config.vec_options if source.mode == "vec" else config.scalar_options
    architecture = config.arch(source.lang) / f"{source.purpose}.{source.lang}"
    return [*config.faust, *config.faust_options, *options, "-double",
            "-lang", source.lang, "-I", str(source.path.parent),
            "-a", str(architecture), str(source.path), "-o", str(output)]


def compile_source(config: Config, case: Case, source: Path, output: Path,
                   csv_path: Path | None = None, emit: str | None = None) -> list[str]:
    lang = case.source.lang
    definitions: dict[str, str | int | float | bool] = {
        "SAMP_RATE": SAMP_RATE,
        "BUFF_SIZE": BUFF_SIZE,
        "COMPUTE_ITERS": config.inspect_compute_iters if emit else config.compute_iters,
    }
    if csv_path is not None:
        definitions.update({
            "BENCH_LANG": lang,
            "BENCH_DSP": case.source.dsp,
            "BENCH_CASE": case.name,
            "BENCH_MODE": case.source.mode,
            "BENCH_OPTIM": optimization(config, lang),
            "PRECISION": "double",  # Report label only; Faust chose compute precision.
            "WRITE_CSV": True,
            "CSV_PATH": str(csv_path),
            "FILL_INPUTS": config.fill_inputs,
            "WARMUP_ITERS": config.warmup_iters,
            "MIN_RUNTIME_SECS": config.min_runtime_secs,
            "MAX_RUNTIME_SECS": config.max_runtime_secs,
            "MAX_BATCH_SIZE": config.max_batch_size,
        })
    if lang == "cpp":
        command = [*config.cpp, "-std=gnu++23", *config.cpp_options,
                   "-I", str(config.arch(lang)), "-I", str(case.source.path.parent),
                   "-Wall", "-Wextra", "-Wno-unused-parameter", "-pedantic",
                   "-DFAUSTFLOAT=float"]
        for key, value in definitions.items():
            if isinstance(value, str):
                value = json.dumps(value)  # A C++ string literal, not shell quoting.
            elif isinstance(value, bool):
                value = int(value)
            command.append(f"-D{key}={value}")
        if emit:
            command += ["-S"] + (["-emit-llvm"] if emit == "llvm" else [])
    else:
        command = [*config.mojo, "build", *config.mojo_options,
                   "-I", str(config.arch(lang)), "-I", str(case.source.path.parent),
                   "-D", "DFAUST=DType.float32"]
        for key, value in definitions.items():
            command += ["-D", f"{key}={value}"]
        if emit:
            command += ["--emit", emit]
    return [*command, str(source), "-o", str(output)]

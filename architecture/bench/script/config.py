"""Benchmark defaults. Commands and options are argument tuples, never shell strings."""

from dataclasses import dataclass
from pathlib import Path


SAMP_RATE = 48_000
BUFF_SIZE = 128


@dataclass(frozen=True)
class Config:
    root: Path = Path(__file__).resolve().parents[1]
    faust: tuple[str, ...] = ("../../build/bin/faust",)
    cpp: tuple[str, ...] = ("clang++",)
    mojo: tuple[str, ...] = ("pixi", "run", "mojo")

    modes: tuple[str, ...] = ("scalar", "vec")
    langs: tuple[str, ...] = ("cpp", "mojo")
    jobs: int = 10
    keep_tmp: bool = False

    faust_options: tuple[str, ...] = ()
    scalar_options: tuple[str, ...] = ()
    vec_options: tuple[str, ...] = ("-vec", "-vs", "4", "-dfs", "-mcd", "4")
    cpp_options: tuple[str, ...] = ("-O3",)
    mojo_options: tuple[str, ...] = ("-O3",)

    warmup_iters: int = 50
    compute_iters: int = 1_000_000
    min_runtime_secs: float = 1
    max_runtime_secs: float = 60
    max_batch_size: int = 10_000
    fill_inputs: bool = True
    inspect_compute_iters: int = 1

    generate_timeout: float = 120
    build_timeout: float = 600
    run_timeout: float = 120

    @property
    def report(self) -> Path:
        return self.root / "report"

    def arch(self, lang: str) -> Path:
        if lang == "mojo":
            return self.root.parent / "mojo"
        return self.root / "arch" / lang

    def validate(self) -> None:
        for name in ("jobs", "compute_iters", "max_batch_size", "inspect_compute_iters"):
            value = getattr(self, name)
            if type(value) is not int or value <= 0:
                raise ValueError(f"{name} must be a positive integer")
        if type(self.warmup_iters) is not int or self.warmup_iters < 0:
            raise ValueError("warmup_iters must be a nonnegative integer")
        import math

        for name in ("min_runtime_secs", "max_runtime_secs", "generate_timeout",
                     "build_timeout", "run_timeout"):
            value = getattr(self, name)
            if not math.isfinite(value) or value <= 0:
                raise ValueError(f"{name} must be finite and positive")
        if self.min_runtime_secs > self.max_runtime_secs:
            raise ValueError("min_runtime_secs cannot exceed max_runtime_secs")
        for name in ("faust", "cpp", "mojo"):
            if not getattr(self, name):
                raise ValueError(f"{name} command is empty")
        for option in self.faust_options + self.scalar_options + self.vec_options:
            if option in ("-single", "-double", "-quad", "-fx", "-fixed"):
                raise ValueError("remove precision options; Faust always receives -double")

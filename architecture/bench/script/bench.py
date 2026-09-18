#!/usr/bin/env python3
"""Generate, build, benchmark, inspect, and collect Faust backend results."""

import argparse
import fcntl
import glob
import itertools
import os
import platform
import re
import shlex
import shutil
import signal
import subprocess
import sys
import threading
import time
import uuid
from concurrent.futures import ThreadPoolExecutor, as_completed
from contextlib import contextmanager
from dataclasses import asdict, replace
from datetime import datetime, timezone
from pathlib import Path

import backends
import report
from backends import Case, Source
from config import BUFF_SIZE, SAMP_RATE, Config


def safe_name(value: str) -> str:
    if not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9_.-]*", value) or value in (".", ".."):
        raise ValueError(f"invalid name {value!r}; use letters, digits, underscores, dots or dashes")
    return value


def choices(value: str, available: tuple[str, ...]) -> list[str]:
    values = list(available) if value == "all" else value.split(",")
    if not values or any(item not in available for item in values):
        raise ValueError(f"expected all or comma-separated values from {', '.join(available)}")
    return list(dict.fromkeys(values))


def source_paths(config: Config, items: list[str]) -> list[Path]:
    found: dict[str, Path] = {}
    for item in items:
        if item == "all":
            matches = sorted((config.root / "src").glob("*.dsp"))
        elif Path(item).is_file():
            matches = [Path(item)]
        elif glob.has_magic(item):
            matches = [Path(path) for path in sorted(glob.glob(item))]
            if not matches:
                matches = sorted((config.root / "src").glob(item))
        else:
            matches = [config.root / "src" / (item if item.endswith(".dsp") else item + ".dsp")]
        if not matches:
            raise ValueError(f"no DSP sources matched {item!r}")
        for path in matches:
            path = path.resolve()
            if not path.is_file() or path.suffix != ".dsp":
                raise ValueError(f"DSP source does not exist or is not .dsp: {path}")
            name = safe_name(path.stem)
            if name in found and found[name] != path:
                raise ValueError(f"two DSPs share report name {name!r}: {found[name]} and {path}")
            found[name] = path
    return list(found.values())


def resolve_cases(config: Config, args) -> list[Case]:
    purpose = "inspect" if args.command.startswith("inspect") else "bench"
    if args.command.endswith("transpiled"):
        path = Path(args.path).resolve()
        mode = choices(args.mode, config.modes)
        lang = choices(args.lang, config.langs)
        if len(mode) != 1 or len(lang) != 1:
            raise ValueError("transpiled commands require one mode and one language")
        if not path.is_file() or path.suffix != f".{lang[0]}":
            raise ValueError(f"expected an existing .{lang[0]} source: {path}")
        source = Source(path, safe_name(path.stem), lang[0], mode[0], purpose, True)
        return [Case(source, safe_name(args.case or path.stem))]
    modes = choices(args.modes, config.modes)
    langs = choices(args.langs, config.langs)
    paths = source_paths(config, args.sources)
    return [Case(Source(path, path.stem, lang, mode, purpose), safe_name(args.case or "run"))
            for path, lang, mode in itertools.product(paths, langs, modes)]


def check_architectures(config: Config, sources: list[Source]) -> None:
    for source in sources:
        if not config.arch(source.lang).is_dir():
            raise ValueError(f"architecture directory not found: {config.arch(source.lang)}")
        if not source.transpiled:
            path = config.arch(source.lang) / f"{source.purpose}.{source.lang}"
            if not path.is_file():
                raise ValueError(f"architecture not found: {path}")


@contextmanager
def workspace_lock(config: Config):
    config.report.mkdir(parents=True, exist_ok=True)
    with (config.report / ".bench.lock").open("a") as stream:
        try:
            fcntl.flock(stream, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError as error:
            raise ValueError("another benchmark command is using this report directory") from error
        yield


def kill_process(process: subprocess.Popen) -> None:
    try:
        os.killpg(process.pid, signal.SIGKILL)
    except ProcessLookupError:
        pass
    process.wait()


class Runner:
    def __init__(self, config: Config, dry_run: bool):
        self.config = config
        self.dry_run = dry_run
        self.run_id = "dry-run" if dry_run else uuid.uuid4().hex[:12]
        self.work = config.report / "tmp" / self.run_id
        self.cancel = threading.Event()
        self.owned: list[Path] = []
        self.commands: list[dict] = []
        self.failures: list[str] = []

    def own(self, path: Path) -> Path:
        self.owned.append(path)
        return path

    def command(self, argv: list[str], log: Path, timeout: float,
                cwd: Path | None = None) -> None:
        if self.dry_run:
            print(f"cwd: {cwd or self.config.root}")
            print(shlex.join(argv))
            return
        if self.cancel.is_set():
            raise RuntimeError("cancelled")
        log.parent.mkdir(parents=True, exist_ok=True)
        with log.open("w", encoding="utf-8") as stream:
            stream.write(f"cwd: {cwd or self.config.root}\n" + shlex.join(argv) + "\n\n")
            stream.flush()
            with subprocess.Popen(argv, cwd=cwd or self.config.root, stdout=stream,
                                  stderr=subprocess.STDOUT, start_new_session=True) as process:
                deadline = time.monotonic() + timeout
                try:
                    while process.poll() is None:
                        if self.cancel.is_set():
                            raise RuntimeError("cancelled")
                        if time.monotonic() >= deadline:
                            raise RuntimeError(f"timed out after {timeout:g}s; log: {log}")
                        self.cancel.wait(0.05)
                    if process.returncode:
                        raise RuntimeError(f"exit {process.returncode}; log: {log}")
                except BaseException:
                    kill_process(process)
                    raise

    def task(self, stage: str, label: str, argv: list[str], log: Path,
             output: Path, timeout: float, cwd: Path | None = None) -> dict:
        task = {"stage": stage, "label": label, "argv": argv, "log": log,
                "output": output, "timeout": timeout, "cwd": cwd or self.config.root}
        self.commands.append(task)
        return task

    def execute(self, task: dict) -> None:
        if not self.dry_run:
            task["output"].parent.mkdir(parents=True, exist_ok=True)
            task["output"].unlink(missing_ok=True)
        self.command(task["argv"], task["log"], task["timeout"], task["cwd"])
        if not self.dry_run and (not task["output"].is_file()
                                 or task["output"].stat().st_size == 0):
            raise RuntimeError(f"no output produced; log: {task['log']}")

    def failed(self, label: str, error: Exception) -> None:
        message = f"{label}: {error}"
        self.failures.append(message)
        print(f"FAILED {message}", file=sys.stderr, flush=True)

    def parallel(self, tasks: dict) -> set:
        if self.dry_run:
            for task in tasks.values():
                self.execute(task)
            return set(tasks)
        good = set()
        pool = ThreadPoolExecutor(max_workers=self.config.jobs)
        try:
            futures = {pool.submit(self.execute, task): key for key, task in tasks.items()}
            for future in as_completed(futures):
                key = futures[future]
                label = f"{tasks[key]['stage']} {tasks[key]['label']}"
                try:
                    future.result()
                    good.add(key)
                    print(f"OK {label}", flush=True)
                except (OSError, RuntimeError, ValueError) as error:
                    self.failed(label, error)
        except BaseException:
            self.cancel.set()
            raise
        finally:
            pool.shutdown(wait=True, cancel_futures=True)
        return good

    def metadata(self, status: str) -> None:
        if self.dry_run:
            return
        context = {"run_id": self.run_id, "status": status,
                   "timestamp": datetime.now(timezone.utc).isoformat(),
                   "command": sys.argv, "platform": platform.platform(),
                   "python": platform.python_version(), "config": asdict(self.config),
                   "sample_rate": SAMP_RATE, "buffer_size": BUFF_SIZE,
                   "commands": self.commands, "failures": self.failures,
                   "owned": self.owned}
        report.write_json(self.work / "context.json", context)
        report.write_json(self.config.report / "context.json", context)

    def run(self, cases: list[Case], emit: str | None) -> int:
        config = self.config
        sources = list(dict.fromkeys(case.source for case in cases))
        check_architectures(config, sources)

        # Reject an incompatible report before spending time compiling.
        if emit is None:
            report.read_csv(config.report / "report.csv")

        print(f"{'Inspecting' if emit else 'Benchmarking'} {len(cases)} cases "
              f"at {SAMP_RATE} Hz / {BUFF_SIZE} frames "
              f"({config.jobs} build jobs; serial measurements)", flush=True)

        generated: dict[Source, Path] = {}
        generation = {}
        builds = {}
        fragments = {}
        inspection_outputs = {}

        for source in sources:
            if source.transpiled:
                generated[source] = source.path
                continue

            name = f"_bench_{self.run_id}_{source.dsp}_{source.mode}_{source.purpose}"
            output = self.own(self.work / f"{name}.{source.lang}")
            generated[source] = output

            generation[source] = self.task(
                "generate", f"{source.lang}/{source.dsp}/{source.mode}",
                backends.generate(config, source, output),
                self.work / f"{name}.{source.lang}.generate.log", output,
                config.generate_timeout)

        for case in cases:
            lang = case.source.lang
            stem = f"{lang}_{case.stem}"
            fragment = self.own(self.work / f"{stem}.csv") if emit is None else None
            fragments[case] = fragment

            if emit:
                suffix = ".ll" if emit == "llvm" else ".s"
                output = self.own(self.work / f"{stem}{suffix}")
                inspection_outputs[case] = config.report / emit / lang / f"{case.stem}{suffix}"
            else:
                output = self.own(config.report / "bin" / lang / f"{stem}_{self.run_id}")

            builds[case] = self.task(
                emit or "build", f"{lang}/{case.stem}",
                backends.compile_source(config, case, generated[case.source], output,
                                        fragment, emit),
                self.work / f"{stem}.{emit or 'build'}.log", output,
                config.build_timeout)

        self.metadata("running")
        status = "interrupted"

        try:
            good_sources = self.parallel(generation)
            good_sources.update(source for source in sources if source.transpiled)

            ready = {case: task for case, task in builds.items() if case.source in good_sources}
            built = self.parallel(ready)

            if emit:
                for case in cases:
                    if case in built:
                        destination = inspection_outputs[case]
                        try:
                            if not self.dry_run:
                                destination.parent.mkdir(parents=True, exist_ok=True)
                                os.replace(builds[case]["output"], destination)
                            print(f"wrote {destination}")
                        except OSError as error:
                            self.failed(f"save {destination}", error)
            else:
                # Both worker pools have joined before the first measured executable starts.
                for case in cases:
                    if case not in built:
                        continue

                    fragment = fragments[case]
                    label = f"{case.source.lang}/{case.stem}"
                    tab = config.report / "tab" / case.source.lang / f"{case.stem}.tab"
                    temporary_tab = self.work / f"{case.source.lang}_{case.stem}.run.log"

                    try:
                        if not self.dry_run:
                            fragment.unlink(missing_ok=True)

                        print(f"RUN {label}", flush=True)
                        self.command([str(builds[case]["output"])], temporary_tab,
                                     config.run_timeout)

                        if not self.dry_run:
                            row = report.read_fragment(fragment, config, case)
                            report.merge_row(config.report / "report.csv", row)
                            tab.parent.mkdir(parents=True, exist_ok=True)
                            shutil.copyfile(temporary_tab, tab)
                            print(f"OK {label}: {float(row['ns_per_compute']):.3f} ns/compute",
                                  flush=True)

                    except (OSError, RuntimeError, ValueError) as error:
                        self.failed(f"run {label}", error)

            status = "failed" if self.failures else "complete"

        finally:
            self.cancel.set()

            if not self.dry_run and not config.keep_tmp:
                for path in self.owned:
                    path.unlink(missing_ok=True)

            self.metadata(status)

        print(f"{status}: {len(self.failures)} failure(s)", flush=True)
        return int(bool(self.failures))

def remove(path: Path) -> None:
    if path.is_symlink() or path.is_file():
        path.unlink()
    elif path.is_dir():
        shutil.rmtree(path)

def clean(config: Config, artifacts_only: bool, snapshots: bool) -> None:
    directories = ["tmp", "bin"]
    if not artifacts_only:
        directories += ["tab", "plot", "llvm", "asm", "report.csv", "context.json"]
    if snapshots:
        directories += ["snap"]
    for name in directories:
        remove(config.report / name)
    print("cleaned generated artifacts" if artifacts_only
          else "cleaned current reports and artifacts")


def snapshot(config: Config, name: str) -> None:
    stamp = datetime.now(timezone.utc).strftime("%Y-%m-%d_%H%M%S_%f")
    destination = config.report / "snap" / f"{stamp}_{safe_name(name)}"
    if not (config.report / "report.csv").is_file():
        raise ValueError("no report.csv to snapshot")
    destination.mkdir(parents=True)
    for name in ("report.csv", "context.json", "tab", "plot", "llvm", "asm"):
        source = config.report / name
        if source.is_dir():
            shutil.copytree(source, destination / name)
        elif source.is_file():
            shutil.copy2(source, destination / name)
    print(f"wrote {destination}")


def parser() -> argparse.ArgumentParser:
    cli = argparse.ArgumentParser(description=__doc__)
    cli.add_argument("--root", type=Path, help="Benchmark root (default: this script's parent).")
    cli.add_argument("--jobs", type=int, help="Maximum simultaneous generation/build processes.")
    cli.add_argument("--keep-tmp", action="store_true", default=None)
    cli.add_argument("--dry-run", action="store_true", help="Print commands without writing files.")
    sub = cli.add_subparsers(dest="command", required=True)
    run = sub.add_parser("run", help="Generate, build, and benchmark a DSP matrix.")
    inspect = sub.add_parser("inspect", help="Generate LLVM IR or assembly using inspect architectures.")
    inspect.add_argument("emit", choices=("llvm", "asm"))
    for command in (run, inspect):
        command.add_argument("modes", help="scalar, vec, a comma list, or all")
        command.add_argument("langs", help="cpp, mojo, cpp,mojo, or all")
        command.add_argument("sources", nargs="+", help="all, DSP names, paths, or globs")
        command.add_argument("--case", help="Report case name (default: run)")
    for name in ("run-transpiled", "inspect-transpiled"):
        command = sub.add_parser(name, help="Use an existing C++ or Mojo program.")
        if name.startswith("inspect"):
            command.add_argument("emit", choices=("llvm", "asm"))
        command.add_argument("mode")
        command.add_argument("lang")
        command.add_argument("path")
        command.add_argument("--case", help="Report case name (default: filename stem)")
    command = sub.add_parser("clean", help="Remove current reports and generated artifacts.")
    command.add_argument("--artifacts-only", action="store_true", help="Preserve reports and plots.")
    command.add_argument("--snapshots", action="store_true", help="Also delete saved snapshots.")
    sub.add_parser("snapshot", help="Copy the current report state.").add_argument("name")
    command = sub.add_parser("plot", help="Generate a normalized throughput SVG.")
    command.add_argument("name")
    command.add_argument("--case")
    return cli


def main(argv: list[str] | None = None) -> int:
    args = parser().parse_args(argv)
    config = Config()
    overrides = {name: getattr(args, name) for name in ("root", "jobs", "keep_tmp")
                 if getattr(args, name) is not None}
    config = replace(config, **overrides)
    config = replace(config, root=config.root.resolve())
    try:
        config.validate()
        if not config.root.is_dir():
            raise ValueError(f"benchmark root does not exist: {config.root}")
        if config.report.is_symlink():
            raise ValueError("report must be a local directory under the benchmark root")
        if args.command in ("run", "inspect", "run-transpiled", "inspect-transpiled"):
            cases = resolve_cases(config, args)
            runner = Runner(config, args.dry_run)
            if args.dry_run:
                return runner.run(cases, getattr(args, "emit", None))
            with workspace_lock(config):
                return runner.run(cases, getattr(args, "emit", None))
        if args.dry_run:
            raise ValueError("--dry-run applies to run and inspect commands")
        with workspace_lock(config):
            if args.command == "clean":
                clean(config, args.artifacts_only, args.snapshots)
            elif args.command == "snapshot":
                snapshot(config, args.name)
            else:
                from plot import plot

                destination = config.report / "plot" / (safe_name(args.name.removesuffix(".svg")) + ".svg")
                plot(config.report / "report.csv", destination, args.case)
        return 0
    except KeyboardInterrupt:
        print("interrupted", file=sys.stderr)
        return 130
    except (OSError, ValueError, RuntimeError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())

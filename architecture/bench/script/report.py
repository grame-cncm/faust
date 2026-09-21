"""Existing CSV contract, strict fragment validation, and atomic identity replacement."""

import csv
import json
import math
import os
import tempfile
from pathlib import Path

from backends import Case, optimization
from config import BUFF_SIZE, SAMP_RATE, Config


TMP_COLUMNS = (
    "language", "bench_case", "mode", "precision", "opt", "samp_rate", "buff_size",
    "inputs", "outputs", "warmup_iters", "run_iters", "batches", "elapsed_s",
    "ns_per_compute", "fast_ns_per_compute", "slow_ns_per_compute",
    "spread_ns_per_compute", "spread_percent", "ns_per_frame", "ns_per_out_samp",
    "frames_per_s", "fast_frames_per_s", "slow_frames_per_s", "out_samp_per_s",
    "fast_out_samp_per_s", "slow_out_samp_per_s", "checksum",
)
CSV_COLUMNS = ("language", "dsp", *TMP_COLUMNS[1:])
IDENTITY_COLUMNS = CSV_COLUMNS[:8]


def atomic_text(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, name = tempfile.mkstemp(prefix=f".{path.name}.", dir=path.parent)
    try:
        with os.fdopen(fd, "w", encoding="utf-8", newline="") as stream:
            stream.write(text)
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(name, path)
    finally:
        Path(name).unlink(missing_ok=True)


def write_json(path: Path, value: object) -> None:
    atomic_text(path, json.dumps(value, indent=2, default=str) + "\n")


def identity(row: dict[str, str]) -> tuple[str, ...]:
    return tuple(str(int(row[key])) if key in ("samp_rate", "buff_size") else row[key]
                 for key in IDENTITY_COLUMNS)


def read_csv(path: Path) -> list[dict[str, str]]:
    if not path.exists() or path.stat().st_size == 0:
        return []
    with path.open(encoding="utf-8", newline="") as stream:
        reader = csv.DictReader(stream)
        if reader.fieldnames != list(CSV_COLUMNS):
            raise ValueError(f"unexpected CSV header: {path}")
        rows = list(reader)
    seen = set()
    for row in rows:
        if None in row or any(value is None for value in row.values()):
            raise ValueError(f"malformed CSV row: {path}")
        key = identity(row)
        if key in seen:
            raise ValueError(f"duplicate CSV identity: {key}")
        seen.add(key)
    return rows


def read_fragment(path: Path, config: Config, case: Case) -> dict[str, str]:
    with path.open(encoding="utf-8", newline="") as stream:
        rows = list(csv.reader(stream))
    if len(rows) != 1 or len(rows[0]) != len(TMP_COLUMNS):
        raise ValueError(f"expected one {len(TMP_COLUMNS)}-field CSV row: {path}")
    row = dict(zip(TMP_COLUMNS, rows[0]))
    row["dsp"] = case.source.dsp
    expected = {
        "language": case.source.lang, "bench_case": case.name,
        "mode": case.source.mode, "precision": "double",
        "opt": optimization(config, case.source.lang),
        "samp_rate": str(SAMP_RATE), "buff_size": str(BUFF_SIZE),
    }
    for key, value in expected.items():
        if row[key] != value:
            raise ValueError(f"CSV {key}: expected {value!r}, got {row[key]!r}")
    for key in TMP_COLUMNS[5:12]:
        value = int(row[key])
        if value < 0 or (key in ("samp_rate", "buff_size", "run_iters", "batches")
                         and value == 0):
            raise ValueError(f"invalid CSV {key}: {row[key]}")
    # Preserve non-finite checksums as a DSP diagnostic; reject unusable timings.
    float(row["checksum"])
    for key in TMP_COLUMNS[12:-1]:
        value = float(row[key])
        if not math.isfinite(value) or value < 0:
            raise ValueError(f"invalid CSV {key}: {row[key]}")
    if float(row["ns_per_compute"]) <= 0 or float(row["elapsed_s"]) <= 0:
        raise ValueError("CSV contains no measured compute time")
    return row


def merge_row(path: Path, row: dict[str, str]) -> None:
    import io

    rows = {identity(item): item for item in read_csv(path)}
    rows[identity(row)] = row
    output = io.StringIO(newline="")
    writer = csv.DictWriter(output, fieldnames=CSV_COLUMNS)
    writer.writeheader()
    writer.writerows(sorted(rows.values(), key=lambda item: (
        item["dsp"], item["language"], item["bench_case"], item["mode"],
        item["precision"], item["opt"], int(item["samp_rate"]), int(item["buff_size"]),
    )))
    atomic_text(path, output.getvalue())

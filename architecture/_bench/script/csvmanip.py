#!/usr/bin/env python3

import argparse
from pathlib import Path

import pandas as pd


TMP_COLUMNS = [
    "language",
    "bench_case",
    "precision",
    "opt",
    "samp_rate",
    "buff_size",
    "n_ins",
    "n_outs",
    "warmup_iters",
    "compute_iters",
    "elapsed_s",
    "ns_per_compute",
    "ns_per_frame",
    "ns_per_output_sample",
    "frames_per_s",
    "output_samples_per_s",
    "checksum",
]

CSV_COLUMNS = [
    "language",
    "dsp",
    "bench_case",
    "precision",
    "opt",
    "samp_rate",
    "buff_size",
    "n_ins",
    "n_outs",
    "warmup_iters",
    "compute_iters",
    "elapsed_s",
    "ns_per_compute",
    "ns_per_frame",
    "ns_per_output_sample",
    "frames_per_s",
    "output_samples_per_s",
    "checksum",
]


def read_main_csv(path: Path) -> pd.DataFrame:
    if not path.exists() or path.stat().st_size == 0:
        return pd.DataFrame(columns=CSV_COLUMNS)

    df = pd.read_csv(path)

    missing = [col for col in CSV_COLUMNS if col not in df.columns]
    if missing:
        raise SystemExit(f"main CSV is missing columns: {missing}")

    return df[CSV_COLUMNS]


def read_tmp_csv(path: Path, dsp: str) -> pd.DataFrame:
    if not path.exists():
        raise SystemExit(f"temporary CSV does not exist: {path}")

    if path.stat().st_size == 0:
        raise SystemExit(f"temporary CSV is empty: {path}")

    df = pd.read_csv(path, header=None, names=TMP_COLUMNS)

    if df.empty:
        raise SystemExit(f"temporary CSV has no rows: {path}")

    df.insert(1, "dsp", dsp)

    return df[CSV_COLUMNS]


def merge_csv(main_path: Path, tmp_path: Path, language: str, dsp: str, bench_case: str) -> None:
    main_df = read_main_csv(main_path)
    tmp_df = read_tmp_csv(tmp_path, dsp)

    expected = {
        "language": language,
        "dsp": dsp,
        "bench_case": bench_case,
    }

    for col, value in expected.items():
        values = set(str(x) for x in tmp_df[col].unique())
        if values != {value}:
            raise SystemExit(
                f"temporary CSV does not match expected {col}={value}: found {sorted(values)}"
            )

    keep_mask = ~(
        (main_df["language"].astype(str) == language)
        & (main_df["dsp"].astype(str) == dsp)
        & (main_df["bench_case"].astype(str) == bench_case)
    )

    out_df = pd.concat(
        [
            main_df[keep_mask],
            tmp_df[CSV_COLUMNS],
        ],
        ignore_index=True,
    )

    sort_cols = [
        "dsp",
        "language",
        "bench_case",
        "precision",
        "opt",
        "samp_rate",
        "buff_size",
    ]

    out_df = out_df.sort_values(sort_cols, kind="stable")
    main_path.parent.mkdir(parents=True, exist_ok=True)
    out_df.to_csv(main_path, index=False)

    print(
        f"merged {tmp_path} into {main_path} "
        f"for language={language}, dsp={dsp}, bench_case={bench_case}"
    )


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Manage Faust benchmark CSV files."
    )

    sub = parser.add_subparsers(dest="command", required=True)

    merge = sub.add_parser(
        "merge",
        help="Replace one sweep in the global CSV with rows from a temporary CSV fragment.",
    )
    merge.add_argument("--main", required=True, help="Global benchmark CSV path.")
    merge.add_argument("--tmp", required=True, help="Temporary headerless CSV fragment.")
    merge.add_argument("--language", required=True, help="Benchmark language.")
    merge.add_argument("--dsp", required=True, help="DSP benchmark name.")
    merge.add_argument("--case", required=True, help="Benchmark case.")

    args = parser.parse_args()

    if args.command == "merge":
        merge_csv(
            main_path=Path(args.main),
            tmp_path=Path(args.tmp),
            language=args.language,
            dsp=args.dsp,
            bench_case=args.case,
        )


if __name__ == "__main__":
    main()

#!/usr/bin/env python3

import argparse
from pathlib import Path

import pandas as pd


TMP_COLUMNS = [
    "language",
    "bench_case",
    "mode",
    "precision",
    "opt",
    "samp_rate",
    "buff_size",
    "inputs",
    "outputs",
    "warmup_iters",
    "run_iters",
    "batches",
    "elapsed_s",
    "ns_per_compute",
    "fast_ns_per_compute",
    "slow_ns_per_compute",
    "spread_ns_per_compute",
    "spread_percent",
    "ns_per_frame",
    "ns_per_out_samp",
    "frames_per_s",
    "fast_frames_per_s",
    "slow_frames_per_s",
    "out_samp_per_s",
    "fast_out_samp_per_s",
    "slow_out_samp_per_s",
    "checksum",
]

CSV_COLUMNS = [
    "language",
    "dsp",
    "bench_case",
    "mode",
    "precision",
    "opt",
    "samp_rate",
    "buff_size",
    "inputs",
    "outputs",
    "warmup_iters",
    "run_iters",
    "batches",
    "elapsed_s",
    "ns_per_compute",
    "fast_ns_per_compute",
    "slow_ns_per_compute",
    "spread_ns_per_compute",
    "spread_percent",
    "ns_per_frame",
    "ns_per_out_samp",
    "frames_per_s",
    "fast_frames_per_s",
    "slow_frames_per_s",
    "out_samp_per_s",
    "fast_out_samp_per_s",
    "slow_out_samp_per_s",
    "checksum",
]

IDENTITY_COLUMNS = [
    "language",
    "dsp",
    "bench_case",
    "mode",
    "precision",
    "opt",
    "samp_rate",
    "buff_size",
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


def require_single_value(df: pd.DataFrame, col: str, value: str) -> None:
    values = set(str(x) for x in df[col].unique())
    if values != {value}:
        raise SystemExit(
            f"temporary CSV does not match expected {col}={value}: found {sorted(values)}"
        )


def identity_tuples(df: pd.DataFrame) -> list[tuple[str, ...]]:
    key_df = df[IDENTITY_COLUMNS].astype(str)
    return list(key_df.itertuples(index=False, name=None))


def require_unique_identities(df: pd.DataFrame, what: str) -> None:
    duplicated = df.duplicated(subset=IDENTITY_COLUMNS, keep=False)
    if duplicated.any():
        duplicates = df.loc[duplicated, IDENTITY_COLUMNS].drop_duplicates()
        raise SystemExit(
            f"{what} contains duplicate benchmark identities:\n"
            f"{duplicates.to_string(index=False)}"
        )


def merge_csv(
    main_path: Path,
    tmp_path: Path,
    language: str,
    dsp: str,
    bench_case: str,
    mode: str,
) -> None:
    main_df = read_main_csv(main_path)
    tmp_df = read_tmp_csv(tmp_path, dsp)

    require_single_value(tmp_df, "language", language)
    require_single_value(tmp_df, "dsp", dsp)
    require_single_value(tmp_df, "bench_case", bench_case)
    require_single_value(tmp_df, "mode", mode)

    require_unique_identities(tmp_df, "temporary CSV")

    tmp_keys = set(identity_tuples(tmp_df))

    if main_df.empty:
        keep_mask = pd.Series([], dtype=bool)
    else:
        main_keys = identity_tuples(main_df)
        keep_mask = pd.Series(
            [key not in tmp_keys for key in main_keys],
            index=main_df.index,
        )

    out_df = pd.concat(
        [
            main_df[keep_mask],
            tmp_df[CSV_COLUMNS],
        ],
        ignore_index=True,
    )

    require_unique_identities(out_df, "merged CSV")

    sort_cols = [
        "dsp",
        "language",
        "bench_case",
        "mode",
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
        f"for language={language}, dsp={dsp}, bench_case={bench_case}, mode={mode}"
    )


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Manage Faust benchmark CSV files."
    )

    sub = parser.add_subparsers(dest="command", required=True)

    merge = sub.add_parser(
        "merge",
        help="Replace matching benchmark identities in the global CSV with rows from a temporary CSV fragment.",
    )
    merge.add_argument("--main", required=True, help="Global benchmark CSV path.")
    merge.add_argument("--tmp", required=True, help="Temporary headerless CSV fragment.")
    merge.add_argument("--language", required=True, help="Benchmark language.")
    merge.add_argument("--dsp", required=True, help="DSP benchmark name.")
    merge.add_argument("--case", required=True, help="Benchmark case.")
    merge.add_argument("--mode", required=True, help="Benchmark mode.")

    args = parser.parse_args()

    if args.command == "merge":
        merge_csv(
            main_path=Path(args.main),
            tmp_path=Path(args.tmp),
            language=args.language,
            dsp=args.dsp,
            bench_case=args.case,
            mode=args.mode,
        )


if __name__ == "__main__":
    main()

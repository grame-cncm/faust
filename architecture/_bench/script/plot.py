#!/usr/bin/env python3

import argparse
from pathlib import Path

import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd


def format_rate(value) -> str:
    value = int(value)
    if value % 1000 == 0:
        return f"{value // 1000}k"
    return str(value)


def make_combo_column(df: pd.DataFrame) -> pd.DataFrame:
    required = ["samp_rate", "buff_size"]
    missing = [col for col in required if col not in df.columns]
    if missing:
        raise SystemExit(f"cannot build combo x axis, missing CSV columns: {missing}")

    df = df.copy()
    df["combo"] = [
        f"{format_rate(sr)} / {int(bs)}"
        for sr, bs in zip(df["samp_rate"], df["buff_size"])
    ]
    return df


def format_x_label(col: str, value) -> str:
    if col == "samp_rate":
        return format_rate(value)

    if col == "buff_size":
        return str(int(value))

    return str(value)


def format_y_value(value: float) -> str:
    # Use millions but keep enough precision to make small differences visible.
    return f"{value / 1_000_000:.2f}M"


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Generate SVG plots from Faust benchmark CSV reports."
    )

    parser.add_argument("csv", help="Input CSV file.")
    parser.add_argument("--case", default=None, help="Optional bench_case filter.")
    parser.add_argument("--x", default="combo", help="Column to use as x axis.")
    parser.add_argument(
        "--y",
        default="output_samples_per_s",
        help="Column to use as y axis.",
    )
    parser.add_argument(
        "--series",
        default="language,precision",
        help="Comma-separated columns used to split series.",
    )
    parser.add_argument(
        "--out",
        default="report/plots/tput_full.svg",
        help="Output SVG path.",
    )
    parser.add_argument(
        "--title",
        default="Faust Benchmark",
        help="Plot title.",
    )

    args = parser.parse_args()

    mpl.rcParams["svg.fonttype"] = "none"

    csv_path = Path(args.csv)
    out_path = Path(args.out)
    out_path.parent.mkdir(parents=True, exist_ok=True)

    df = pd.read_csv(csv_path)

    if args.case is not None:
        if "bench_case" not in df.columns:
            raise SystemExit("missing CSV column: bench_case")

        df = df[df["bench_case"] == args.case]

        if df.empty:
            raise SystemExit(f"no rows found for bench_case={args.case}")

    if args.x == "combo":
        df = make_combo_column(df)

    series_cols = [col.strip() for col in args.series.split(",") if col.strip()]

    required_cols = [args.x, args.y] + series_cols
    missing = [col for col in required_cols if col not in df.columns]
    if missing:
        raise SystemExit(f"missing CSV columns: {missing}")

    if args.x == "combo":
        df = df.sort_values(["samp_rate", "buff_size"] + series_cols)
    else:
        df = df.sort_values([args.x] + series_cols)

    fig, ax = plt.subplots(figsize=(13, 7.5))

    style_map = {
        ("mojo", "single"): {"color": "red", "alpha": 1.0},
        ("mojo", "double"): {"color": "blue", "alpha": 1.0},
        ("cpp", "single"): {"color": "darkred", "alpha": 1.0},
        ("cpp", "double"): {"color": "navy", "alpha": 1.0},
    }

    x_values = list(pd.unique(df[args.x]))
    x_labels = [format_x_label(args.x, value) for value in x_values]
    x_positions = list(range(len(x_values)))

    series_groups = list(df.groupby(series_cols))
    n_series = len(series_groups)

    if n_series == 0:
        raise SystemExit("no series found")

    total_width = 0.82
    bar_width = total_width / n_series
    first_offset = -total_width / 2 + bar_width / 2

    all_bars = []

    for index, (key, group) in enumerate(series_groups):
        if not isinstance(key, tuple):
            key = (key,)

        label = " / ".join(str(x) for x in key)
        style = style_map.get(tuple(key), {})

        if not style:
            print(f"warning: no style for series {key}")

        values_by_x = {
            row[args.x]: row[args.y]
            for _, row in group.iterrows()
        }

        y_values = [values_by_x.get(value, float("nan")) for value in x_values]
        bar_positions = [
            pos + first_offset + index * bar_width
            for pos in x_positions
        ]

        bars = ax.bar(
            bar_positions,
            y_values,
            width=bar_width,
            label=label,
            **style,
        )
        all_bars.extend(bars)

    y_min = df[args.y].min()
    y_max = df[args.y].max()
    y_pad = (y_max - y_min) * 0.22

    if y_pad == 0:
        y_pad = max(abs(y_min) * 0.05, 1e-9)

    ax.set_ylim(y_min - y_pad, y_max + y_pad)

    for bar in all_bars:
        height = bar.get_height()
        ax.text(
            bar.get_x() + bar.get_width() / 2,
            height + y_pad * 0.08,
            format_y_value(height),
            ha="center",
            va="bottom",
            rotation=90,
            fontsize=8,
        )

    ax.set_title(args.title)
    ax.set_xlabel(args.x)
    ax.set_ylabel("out_samp/s")

    ax.set_xticks(x_positions)
    ax.set_xticklabels(x_labels)

    ax.yaxis.set_major_formatter(
        mpl.ticker.FuncFormatter(lambda value, _: format_y_value(value))
    )

    ax.grid(True, axis="y", linewidth=0.4)
    ax.legend()

    fig.subplots_adjust(left=0.12)
    fig.tight_layout()
    fig.savefig(out_path, format="svg", bbox_inches="tight")

    print(f"wrote {out_path}")


if __name__ == "__main__":
    main()

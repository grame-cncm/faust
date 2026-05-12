#!/usr/bin/env python3

import argparse
from pathlib import Path

import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd


MAX_COLUMNS_PER_ROW = 40


def format_rate(value) -> str:
    value = int(value)
    if value % 1000 == 0:
        return f"{value // 1000}k"
    return str(value)


def make_combo_column(df: pd.DataFrame) -> pd.DataFrame:
    required = ["dsp", "samp_rate", "buff_size"]
    missing = [col for col in required if col not in df.columns]
    if missing:
        raise SystemExit(f"cannot build combo x axis, missing CSV columns: {missing}")

    df = df.copy()
    df["combo"] = [
        f"{format_rate(sr)} / {int(bs)}"
        for sr, bs in zip(df["samp_rate"], df["buff_size"])
    ]
    return df


def add_normalized_y_column(df: pd.DataFrame, x_col: str, y_col: str) -> pd.DataFrame:
    df = df.copy()
    group_cols = ["dsp", x_col]
    max_values = df.groupby(group_cols, observed=True)[y_col].transform("max")
    df["plot_y"] = df[y_col] / max_values * 100.0
    return df


def format_x_label(col: str, value) -> str:
    if col == "samp_rate":
        return format_rate(value)

    if col == "buff_size":
        return str(int(value))

    return str(value)


def format_rel_value(value: float) -> str:
    return f"{value:.1f}%"


def format_tput_value(value: float) -> str:
    return f"{value / 1_000_000:.1f}M"


def split_dsp_rows(df: pd.DataFrame, x_col: str, max_cases_per_row: int) -> list[list[str]]:
    rows = []
    row = []
    row_cases = 0

    for dsp_name, dsp_df in df.groupby("dsp", sort=False):
        dsp_cases = len(pd.unique(dsp_df[x_col]))

        if dsp_cases > max_cases_per_row:
            raise SystemExit(
                f"DSP '{dsp_name}' has {dsp_cases} cases, "
                f"but the maximum per row is {max_cases_per_row}"
            )

        if row and row_cases + dsp_cases > max_cases_per_row:
            rows.append(row)
            row = []
            row_cases = 0

        row.append(dsp_name)
        row_cases += dsp_cases

    if row:
        rows.append(row)

    return rows


def build_axis_data(row_df: pd.DataFrame, x_col: str):
    x_values = []
    x_labels = []
    x_positions = []
    dsp_centers = []
    dsp_labels = []

    dsp_gap = 0.15
    pos = 0.0

    for dsp_name, dsp_df in row_df.groupby("dsp", sort=False, observed=True):
        local_values = list(pd.unique(dsp_df[x_col]))
        start_pos = pos

        for value in local_values:
            x_values.append((dsp_name, value))
            x_labels.append(format_x_label(x_col, value))
            x_positions.append(pos)
            pos += 1.0

        end_pos = pos - 1.0
        dsp_centers.append((start_pos + end_pos) / 2)
        dsp_labels.append(dsp_name)

        pos += dsp_gap

    return x_values, x_labels, x_positions, dsp_centers, dsp_labels


def draw_row(
    ax,
    row_df: pd.DataFrame,
    x_col: str,
    y_col: str,
    raw_y_col: str,
    series_cols: list[str],
    y_min: float,
    y_max: float,
    y_pad: float,
    show_legend: bool,
) -> int:
    style_map = {
        ("mojo", "single"): {"color": "darkorange", "alpha": 1.0},
        ("mojo", "double"): {"color": "darkred", "alpha": 1.0},
        ("cpp", "single"): {"color": "green", "alpha": 1.0},
        ("cpp", "double"): {"color": "navy", "alpha": 1.0},
    }

    x_values, x_labels, x_positions, dsp_centers, dsp_labels = build_axis_data(
        row_df, x_col
    )

    series_groups = list(row_df.groupby(series_cols, sort=False, observed=True))
    n_series = len(series_groups)

    if n_series == 0:
        raise SystemExit("no series found")

    total_width = 0.98
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
            (row["dsp"], row[x_col]): row[y_col]
            for _, row in group.iterrows()
        }

        raw_values_by_x = {
            (row["dsp"], row[x_col]): row[raw_y_col]
            for _, row in group.iterrows()
        }

        y_values = [values_by_x.get(value, float("nan")) for value in x_values]
        raw_values = [raw_values_by_x.get(value, float("nan")) for value in x_values]

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

        for bar, raw_value in zip(bars, raw_values):
            bar.raw_value = raw_value

        all_bars.extend(bars)

    ax.set_ylim(y_min - y_pad * 0.20, y_max + y_pad)

    if x_positions:
        left_edge = min(x_positions) - total_width / 2
        right_edge = max(x_positions) + total_width / 2
        ax.set_xlim(left_edge - 0.12, right_edge + 0.12)

    for bar in all_bars:
        height = bar.get_height()
        ax.text(
            bar.get_x() + bar.get_width() / 2,
            height + y_pad * 0.08,
            format_tput_value(bar.raw_value),
            ha="center",
            va="bottom",
            rotation=0,
            fontsize=5.5,
        )

    ax.set_xlabel("")
    ax.set_ylabel("rel_tput (%)", fontweight="bold")

    ax.set_xticks(x_positions)
    ax.set_xticklabels(x_labels, fontsize=8)

    ax.tick_params(axis="y", labelsize=7)
    ax.yaxis.label.set_size(8)

    for center, label in zip(dsp_centers, dsp_labels):
        ax.text(
            center,
            -0.05,
            label,
            ha="center",
            va="top",
            transform=ax.get_xaxis_transform(),
            fontsize=8,
            fontweight="bold",
            clip_on=False,
        )

    ax.yaxis.set_major_formatter(
        mpl.ticker.FuncFormatter(lambda value, _: format_rel_value(value))
    )

    ax.grid(True, axis="y", linewidth=0.25)

    if show_legend:
        ax.legend(loc="upper left", fontsize=8, framealpha=0.7)

    return len(x_values)


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

    required_cols = ["dsp", args.x, args.y] + series_cols
    missing = [col for col in required_cols if col not in df.columns]
    if missing:
        raise SystemExit(f"missing CSV columns: {missing}")

    df["language"] = pd.Categorical(
        df["language"],
        categories=["cpp", "mojo"],
        ordered=True,
    )

    df["precision"] = pd.Categorical(
        df["precision"],
        categories=["single", "double"],
        ordered=True,
    )

    df = add_normalized_y_column(df, args.x, args.y)

    if args.x == "combo":
        df = df.sort_values(["dsp", "samp_rate", "buff_size"] + series_cols)
    else:
        df = df.sort_values(["dsp", args.x] + series_cols)

    n_series = len(list(df.groupby(series_cols, sort=False, observed=True)))
    if n_series == 0:
        raise SystemExit("no series found")

    max_cases_per_row = max(1, MAX_COLUMNS_PER_ROW // n_series)
    row_dsps = split_dsp_rows(df, args.x, max_cases_per_row)
    n_rows = len(row_dsps)

    y_min = df["plot_y"].min()
    y_max = df["plot_y"].max()
    y_pad = (y_max - y_min) * 0.32

    if y_pad == 0:
        y_pad = max(abs(y_min) * 0.05, 1e-9)

    max_row_cases = 0
    for dsps in row_dsps:
        row_df = df[df["dsp"].isin(dsps)]
        row_cases = sum(
            len(pd.unique(dsp_df[args.x]))
            for _, dsp_df in row_df.groupby("dsp", sort=False, observed=True)
        )
        max_row_cases = max(max_row_cases, row_cases)

    fig_width = max(18, max_row_cases * 2.1)
    fig_height = 7 * n_rows

    fig, axes = plt.subplots(
        n_rows,
        1,
        figsize=(fig_width, fig_height),
        squeeze=False,
    )

    fig.suptitle(args.title, fontsize=12)

    for row_index, dsps in enumerate(row_dsps):
        ax = axes[row_index][0]
        row_df = df[df["dsp"].isin(dsps)]

        draw_row(
            ax=ax,
            row_df=row_df,
            x_col=args.x,
            y_col="plot_y",
            raw_y_col=args.y,
            series_cols=series_cols,
            y_min=y_min,
            y_max=y_max,
            y_pad=y_pad,
            show_legend=(row_index == 0),
        )

    fig.subplots_adjust(left=0.16, bottom=0.18, top=0.94, hspace=0.2)
    fig.savefig(out_path, format="svg", bbox_inches="tight", pad_inches=0.4)

    print(f"wrote {out_path}")


if __name__ == "__main__":
    main()

"""Plot accumulated throughput without merging distinct benchmark identities."""

import math
from pathlib import Path

from report import read_csv


def plot(csv_path: Path, destination: Path, case: str | None = None) -> None:
    try:
        import matplotlib

        matplotlib.use("Agg")
        import matplotlib.pyplot as plt
    except ImportError as error:
        raise RuntimeError("plot requires matplotlib in the active Python environment") from error

    rows = [row for row in read_csv(csv_path) if case is None or row["bench_case"] == case]
    if not rows:
        raise ValueError("no benchmark rows match the plot selection")

    groups = sorted({(r["dsp"], int(r["samp_rate"]), int(r["buff_size"])) for r in rows})
    series_keys = ("language", "mode", "bench_case", "precision", "opt")
    series = sorted({tuple(r[key] for key in series_keys) for r in rows})
    data = {
        (r["dsp"], int(r["samp_rate"]), int(r["buff_size"]), tuple(r[key] for key in series_keys)): r
        for r in rows
    }

    metric = "frames_per_s"
    per_row = max(1, 36 // len(series))
    panels = [groups[start:start + per_row] for start in range(0, len(groups), per_row)]

    fig, axes = plt.subplots(
        len(panels),
        1,
        squeeze=False,
        figsize=(max(10, min(len(groups), per_row) * 1.8), 4.5 * len(panels)),
    )

    colors = {
        ("cpp", "scalar"): "#2563eb",
        ("cpp", "vec"): "#60a5fa",
        ("mojo", "scalar"): "#c2410c",
        ("mojo", "vec"): "#fb923c",
    }

    for panel, ax in zip(panels, axes[:, 0]):
        width = 0.85 / len(series)
        maxima = [
            max(float(data[(*group, key)][metric]) for key in series if (*group, key) in data)
            for group in panel
        ]

        if any(not math.isfinite(value) or value <= 0 for value in maxima):
            raise ValueError("plot requires finite, positive throughput")

        for index, key in enumerate(series):
            label = " / ".join(
                value for i, value in enumerate(key)
                if i < 2 or len({item[i] for item in series}) > 1
            )

            for position, (group, maximum) in enumerate(zip(panel, maxima)):
                row = data.get((*group, key))
                if row is None:
                    continue

                raw_value = float(row[metric])
                value = 100 * raw_value / maximum
                slow = 100 * float(row[f"slow_{metric}"]) / maximum
                fast = 100 * float(row[f"fast_{metric}"]) / maximum
                x = position - 0.425 + width * (index + 0.5)

                ax.bar(
                    x,
                    value,
                    width,
                    color=colors.get(key[:2]),
                    label=label if position == next(
                        i for i, g in enumerate(panel) if (*g, key) in data
                    ) else None,
                    hatch=("", "//", "..", "xx")[index // 4 % 4],
                )

                ax.vlines(x, slow, fast, color="#222222", linewidth=0.7)
                ax.hlines(
                    [slow, fast],
                    x - width / 5,
                    x + width / 5,
                    color="#222222",
                    linewidth=0.7,
                )

                ax.annotate(
                    f"{raw_value / 1_000_000:.1f}M",
                    (x, value),
                    xytext=(0, 3),
                    textcoords="offset points",
                    ha="center",
                    va="bottom",
                    fontsize=5,
                )

        ax.set_xticks(range(len(panel)), [dsp for dsp, _, _ in panel])
        ax.tick_params(axis="x", labelsize=8)
        ax.set_ylabel("Throughput / best in group [%]", fontsize=8)
        ax.set_ylim(bottom=0)
        ax.grid(axis="y", alpha=0.2)
        ax.set_axisbelow(True)
        ax.legend(fontsize=8, ncols=min(4, len(series)))

    fig.suptitle(f"{metric}", fontsize=8)
    fig.tight_layout()

    destination.parent.mkdir(parents=True, exist_ok=True)
    with matplotlib.rc_context({"svg.fonttype": "none"}):
        fig.savefig(destination)

    plt.close(fig)
    print(f"wrote {destination}")

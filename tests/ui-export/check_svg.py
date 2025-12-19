#!/usr/bin/env python3
"""
Simple SVG sanity check:
- Ensures presence of key widget classes and data attributes.
- Checks tab headers/contents existence.
"""

import sys
import re
from pathlib import Path


EXPECTED = {
    "layoutui-simple.svg": {
        "classes": ["button", "checkbutton", "knob"],
        "labels": [],
    },
    "layoutui-medium.svg": {
        "classes": ["button", "checkbutton", "vslider", "numentry", "hbargraph", "knob"],
        "labels": [],
    },
    "layoutui-complex.svg": {
        "classes": ["button", "checkbutton", "hslider", "vslider", "numentry", "hbargraph", "tab-header", "tab-content", "knob", "radio", "menu"],
        "labels": ["Off", "On", "Auto", "Sine", "Square", "Saw"],
    },
    "layoutui-vertical.svg": {
        "classes": ["vslider", "vbargraph", "menu"],
        "labels": ["Slow", "Medium", "Fast"],
    },
    "layoutui-horizontal.svg": {
        "classes": ["button", "checkbutton", "hbargraph", "radio"],
        "labels": ["A", "B", "C"],
    },
    "layoutui-tabs.svg": {
        "classes": ["tab-header", "tab-content", "hslider", "button"],
        "labels": [],
    },
}


def main():
    files = list(EXPECTED.keys())
    if len(sys.argv) > 1:
        files = sys.argv[1:]

    for svg_file in files:
        svg_path = Path(svg_file)
        if not svg_path.exists():
            print(f"file not found: {svg_path}", file=sys.stderr)
            return 1
        content = svg_path.read_text(encoding="utf-8")

        expectations = EXPECTED.get(svg_path.name, EXPECTED["layoutui-complex.svg"])
        required_classes = expectations["classes"]
        expected_labels = expectations["labels"]

        missing = []
        for cls in required_classes:
            pattern = rf'class="[^"]*\b{re.escape(cls)}\b'
            if not re.search(pattern, content):
                missing.append(cls)
        if missing:
            print(f"{svg_file}: missing classes: {missing}", file=sys.stderr)
            return 1

        if not re.search(r'data-path=', content):
            print(f"{svg_file}: missing data-path attributes", file=sys.stderr)
            return 1
        if not re.search(r'data-scale=\"(lin|log|exp)\"', content):
            print(f"{svg_file}: missing data-scale attributes", file=sys.stderr)
            return 1

        for label in expected_labels:
            if label not in content:
                print(f"{svg_file}: missing expected option label: {label}", file=sys.stderr)
                return 1

        if "tab-content" in required_classes and content.count("tab-content") < 2:
            print(f"{svg_file}: expected at least two tab-content groups", file=sys.stderr)
            return 1

        print(f"{svg_file}: SVG checks passed")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())

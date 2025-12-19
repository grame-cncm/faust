#!/usr/bin/env python3
"""
Simple HTML sanity check:
- Ensures presence of key widget classes and data attributes.
- Checks tab headers/contents existence where applicable.
"""

import sys
import re
from pathlib import Path

EXPECTED = {
    "layoutui-simple.html": {
        "classes": ["button", "checkbutton", "knob"],
        "labels": [],
    },
    "layoutui-medium.html": {
        "classes": ["button", "checkbutton", "vslider", "numentry", "bargraph", "knob"],
        "labels": [],
    },
    "layoutui-complex.html": {
        "classes": ["button", "checkbutton", "hslider", "vslider", "numentry", "bargraph", "tab-header", "tab-content", "knob", "radio", "menu"],
        "labels": [],
    },
    "layoutui-vertical.html": {
        "classes": ["vslider", "bargraph", "menu"],
        "labels": ["Slow", "Medium", "Fast"],
    },
    "layoutui-horizontal.html": {
        "classes": ["button", "checkbutton", "bargraph", "radio"],
        "labels": ["A", "B", "C"],
    },
    "layoutui-tabs.html": {
        "classes": ["tab-header", "tab-content", "hslider", "button"],
        "labels": [],
    },
}


def main():
    files = list(EXPECTED.keys())
    if len(sys.argv) > 1:
        files = sys.argv[1:]

    for html_file in files:
        html_path = Path(html_file)
        if not html_path.exists():
            print(f"file not found: {html_path}", file=sys.stderr)
            return 1
        content = html_path.read_text(encoding="utf-8")
        expectations = EXPECTED.get(html_path.name, EXPECTED["layoutui-complex.html"])
        required_classes = expectations["classes"]
        expected_labels = expectations["labels"]

        missing = []
        for cls in required_classes:
            pattern = rf'class="[^"]*\b{re.escape(cls)}\b'
            if not re.search(pattern, content):
                missing.append(cls)
        if missing:
            print(f"{html_file}: missing classes: {missing}", file=sys.stderr)
            return 1

        if 'data-path' not in content:
            print(f"{html_file}: missing data-path attributes", file=sys.stderr)
            return 1
        if not re.search(r'data-scale=\"(lin|log|exp)\"', content):
            print(f"{html_file}: missing data-scale attributes", file=sys.stderr)
            return 1

        for label in expected_labels:
            if label not in content:
                print(f"{html_file}: missing expected option label: {label}", file=sys.stderr)
                return 1

        if "tab-content" in required_classes and content.count("tab-content") < 2:
            print(f"{html_file}: expected at least two tab-content groups", file=sys.stderr)
            return 1

        print(f"{html_file}: HTML checks passed")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())

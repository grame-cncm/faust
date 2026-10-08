#!/usr/bin/env python3
"""Generate a relocation for every exported free-function declaration in an API header."""

import argparse
import re
from pathlib import Path


def generate(header):
    text = re.sub(r"/\*.*?\*/|//[^\n]*", "", header.read_text(), flags=re.S)
    # Opaque CTree has no public methods; dsp_factory_base defines its methods inline.
    text = re.sub(r"\b(class|struct)\s+LIBFAUST_API\b", r"\1", text)
    declarations = re.findall(r"\bLIBFAUST_API\b\s+([^;{}]+);", text)
    if not declarations or len(declarations) != len(re.findall(r"\bLIBFAUST_API\b", text)):
        raise ValueError("unrecognised export declaration in " + str(header))
    lines = ["// Generated from " + header.name + "; do not commit this file.",
             "static std::size_t checkApiLinks()", "{"]
    for index, declaration in enumerate(declarations):
        declaration = " ".join(declaration.split())
        match = re.fullmatch(r"(.+?)\s+(\w+)\s*\((.*)\)", declaration)
        if not match or "=" in match.group(3):
            raise ValueError("unsupported declaration: " + declaration)
        result, name, parameters = match.groups()
        # Volatile stores/loads keep every relocation even under optimisation/LTO.
        lines += ["    " + result + " (* volatile api_" + str(index) + ")(" + parameters + ") = &" + name + ";",
                  "    if (api_" + str(index) + " == nullptr) return 0;"]
    lines += ["    return " + str(len(declarations)) + ";", "}", ""]
    return "\n".join(lines)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("header", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()
    args.output.write_text(generate(args.header))

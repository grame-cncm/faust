"""Shared utilities for JAX test scripts."""

import importlib.util
import sys


def load_module(python_file, module_name="compiled_dsp"):
    """Load a Python module from a file path.

    Args:
        python_file: Path to the generated Python file.
        module_name: Name to register in sys.modules (default: "compiled_dsp").

    Returns:
        The loaded module.
    """
    spec = importlib.util.spec_from_file_location(module_name, python_file)
    if spec is None or spec.loader is None:
        raise ImportError(f"Could not load spec from {python_file}")

    module = importlib.util.module_from_spec(spec)
    sys.modules[module_name] = module
    spec.loader.exec_module(module)

    return module

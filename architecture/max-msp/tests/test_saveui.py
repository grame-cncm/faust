"""Compile-and-run regression test for SaveUI zone rebinding.

The Max external rebuilds its DSP when the polyphony count changes.  This test
models that lifetime without depending on Max: old zones are saved, unbound,
destroyed, and replaced by a new user interface before state is loaded again.
"""

from __future__ import annotations

import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]
ARCHITECTURE = ROOT / "architecture"


# A small derived class exposes only read-only map queries.  The assertions in
# C++ are intentionally performed after deleting the old zones: any accidental
# dereference in load/reset would therefore reproduce the stale-pointer bug.
SOURCE = r"""
#include <cmath>
#include <cstddef>
#include <string>

#include "faust/gui/SaveUI.h"

class SaveLabelUIProbe : public SaveLabelUI {
   public:
    std::size_t size() const { return fName2Zone.size(); }
    bool contains(const std::string& label) const
    {
        return fName2Zone.find(label) != fName2Zone.end();
    }
};

int main()
{
    SaveLabelUIProbe ui;
    FAUSTFLOAT* old_gain = new FAUSTFLOAT(0.25);
    FAUSTFLOAT* removed = new FAUSTFLOAT(0.0);
    ui.addHorizontalSlider("gain", old_gain, 0.25, 0.0, 1.0, 0.01);
    ui.addButton("removed", removed);

    *old_gain = FAUSTFLOAT(0.75);
    *removed = FAUSTFLOAT(1.0);
    ui.save();
    ui.unbind();
    delete old_gain;
    delete removed;

    FAUSTFLOAT new_gain = FAUSTFLOAT(0.0);
    ui.addHorizontalSlider("gain", &new_gain, 0.25, 0.0, 1.0, 0.01);
    if (std::fabs(new_gain - FAUSTFLOAT(0.75)) > 0.0001) return 1;

    ui.removeUnbound();
    if (ui.size() != 1 || !ui.contains("gain") || ui.contains("removed")) return 2;

    new_gain = FAUSTFLOAT(0.0);
    ui.load();
    if (std::fabs(new_gain - FAUSTFLOAT(0.75)) > 0.0001) return 3;

    ui.reset();
    if (std::fabs(new_gain - FAUSTFLOAT(0.25)) > 0.0001) return 4;
    return 0;
}
"""


@unittest.skipUnless(shutil.which("c++"), "requires a C++ compiler")
class SaveUIRebindingTests(unittest.TestCase):
    """Verify state restoration and removal of controls absent after rebuild."""

    def test_saved_zones_can_be_destroyed_and_rebound(self):
        """Never dereference old zones and restore values into matching new zones."""

        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            source = directory / "saveui_rebind.cpp"
            executable = directory / "saveui_rebind"
            source.write_text(SOURCE, encoding="utf-8")

            compile_result = subprocess.run(
                [
                    "c++",
                    "-std=c++11",
                    "-I",
                    str(ARCHITECTURE),
                    str(source),
                    "-o",
                    str(executable),
                ],
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
            )
            self.assertEqual(compile_result.returncode, 0, compile_result.stdout)

            run_result = subprocess.run(
                [str(executable)],
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
            )
            self.assertEqual(run_result.returncode, 0, run_result.stdout)


if __name__ == "__main__":
    unittest.main()

import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

import numpy as np
from scipy.io.wavfile import write


SCRIPTS = {
    "ir2dsp.py": ([], "modeFrequencies = (440.0);"),
    "ir2dspoly.py": (["440"], "modeFrequencies = (1.0);"),
}


class MonoImpulseResponseTest(unittest.TestCase):
    def test_mono_matches_stereo_first_channel(self):
        sample_rate = 8000
        time = np.arange(sample_rate) / sample_rate
        samples = np.rint(
            12000 * np.exp(-3 * time) * np.sin(2 * np.pi * 440 * time)
        ).astype(np.int16)

        with tempfile.TemporaryDirectory() as directory:
            directory = Path(directory)
            mono = directory / "mono.wav"
            stereo = directory / "stereo.wav"
            write(mono, sample_rate, samples)
            write(stereo, sample_rate, np.column_stack((samples, samples)))

            for script, (extra_args, expected_frequency) in SCRIPTS.items():
                for input_file in (mono, stereo):
                    with self.subTest(script=script, input_file=input_file.name):
                        model = f"{Path(script).stem}_{input_file.stem}"
                        command = [
                            sys.executable,
                            str(Path(__file__).with_name(script)),
                            str(input_file),
                            model,
                            "-40",
                            "50",
                            *extra_args,
                        ]
                        result = subprocess.run(
                            command, cwd=directory, capture_output=True, text=True
                        )
                        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                        output = (directory / f"{model}.dsp").read_text()
                        self.assertIn("nModes = 1;", output)
                        self.assertIn(expected_frequency, output)


if __name__ == "__main__":
    unittest.main()

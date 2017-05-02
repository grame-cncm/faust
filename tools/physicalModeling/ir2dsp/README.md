# `ir2dsp.py`

`ir2dsp.py` takes an audio file containing an impulse response as its main
argument. After performing the Fast Fourier Transform (FFT) on it, modes
information is extracted by carrying out peaks detection. The T60 of each mode
is computed by measuring its bandwidth at -3 dB.
Modes information is formatted by `ir2dsp.py` to be plugged to a generic
modal Faust physical model similar to the one described in §2. The output of
the Python program is a ready-to-use Faust file implementing the model.
The goal of this tool is not to create very accurate models but rather to be
able to strike any object (e.g., a glass, a metal bar, etc.), record the
resulting sound, and turn it into a playable digital musical instrument.

More information can be found in the related lac paper: `lacPaper2017.pdf`.

`ir2dsp.py` was written by Pierre-Amaury Grumiaux during an internship at the
Centre de Recherche en Informatique (CRI) at Paris' Mines School in the summer
of 2016.

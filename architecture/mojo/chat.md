```
.
├── audio
│   ├── __init__.mojo
│   ├── audio.mojo
│   └── portaudio
│       ├── __init__.mojo
│       ├── ffi.mojo
│       ├── gpu.mojo
│       └── portaudio.mojo
├── bench
│   ├── __init__.mojo
│   └── bench.mojo
├── bench.mojo
├── conf
│   ├── __init__.mojo
│   └── prelude.mojo
├── dsp
│   ├── __init__.mojo
│   ├── dsp.mojo
│   ├── gpu.mojo
│   └── proto.mojo
├── gpu
│   ├── __init__.mojo
│   └── device.mojo
├── gui
│   ├── __init__.mojo
│   ├── bridge.mojo
│   ├── control.mojo
│   ├── gui.mojo
│   ├── proto.mojo
│   └── terminal/
├── help
│   ├── __init__.mojo
│   ├── math.mojo
│   ├── misc.mojo
│   └── utils.mojo
├── impulse.mojo
├── inspect.mojo
├── mem
│   ├── __init__.mojo
│   └── memory.mojo
├── meta
│   ├── __init__.mojo
│   └── meta.mojo
├── pixi.lock
├── pixi.toml
├── portaudio-gpu.mojo
├── portaudio-proto-gpu.mojo
├── portaudio-proto.mojo
├── portaudio.mojo
├── proto__10000osc.mojo
├── proto__100osc.mojo
├── proto__10k_stress.mojo
├── proto__beats.mojo
├── proto__parallel_noise.mojo
├── proto__strange_noise.mojo
├── README_IT.md
├── README.md
├── src
│   ├── APF.dsp
│   ├── bargraph.dsp
│   ├── bells.dsp
│   ├── comb_delay1.dsp
│   ├── cubic_distortion.dsp
│   ├── custom_bargraph.dsp
│   ├── gate_compressor.dsp
│   ├── thru_zero_flanger.dsp
│   └── virtual_analog_oscillators.dsp
└── test
    ├── __init__.mojo
    └── impulse.mojo
```

```
├── terminal
│   └── mojo
│       ├── audio
│       │   ├── __init__.mojo
│       │   ├── audio.mojo
│       │   └── portaudio
│       │       ├── __init__.mojo
│       │       ├── ffi.mojo
│       │       └── portaudio.mojo
│       ├── conf
│       │   ├── __init__.mojo
│       │   └── prelude.mojo
│       ├── doc
│       │   └── terminal_gui_spec_def.md
│       ├── dsp
│       │   ├── __init__.mojo
│       │   └── dsp.mojo
│       ├── gui
│       │   ├── __init__.mojo
│       │   ├── gui.mojo
│       │   └── terminal
│       │       ├── __init__.mojo
│       │       ├── examples
│       │       │   └── osc.dsp
│       │       ├── ffi.mojo
│       │       ├── native
│       │       │   ├── Makefile
│       │       │   ├── termgui.c
│       │       │   ├── termgui.h
│       │       │   ├── test_alloc.c
│       │       │   ├── test_pty.py
│       │       │   └── test.c
│       │       ├── smoke.dsp
│       │       ├── smoke.mojo
│       │       └── terminal.mojo
│       └── portaudio-terminal.mojo
├── Makefile
└── terminal_gui.patch
```

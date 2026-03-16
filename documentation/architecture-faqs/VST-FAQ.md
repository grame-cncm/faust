# VST Plugin Development FAQ

## Setup & Installation

**Q: What versions of VST are supported?**
A: Faust supports VST 2.x and VST 3.x. Use `faust2vst` for VST2 development. For VST3, use the `-vst3` flag with newer versions of the tools.

**Q: What SDKs do I need?**
A: You need the VST SDK from Steinberg. For VST2, download from the official Steinberg website. For VST3, use the open-source VST3 SDK.

**Q: Is Windows development supported?**
A: Yes. On Windows, use MinGW, Visual Studio, or WSL. The recommended approach is using the faust2vst tool in a Linux/macOS environment or the online compiler.

## Compilation & Building

**Q: How do I generate a VST plugin from a Faust DSP file?**
A: Use the command: `faust -a vst.cpp myfile.dsp -o vst-output.cpp`. Then compile using your build system.

**Q: What are common compiler errors?**
A: - Missing VST SDK headers → ensure VSTSDK path is set correctly
- Symbol conflicts → use namespaces
- Linking errors → verify VST libraries are linked

## Audio I/O & Latency

**Q: What buffer sizes are recommended?**
A: VST plugins should work with variable buffer sizes (64-2048 samples). Test with small buffers (64-256) for latency-sensitive applications.

**Q: How do I handle sample rate changes?**
A: Implement proper `setSampleRate()` calls. Faust automatically handles this, but verify your DSP logic doesn't assume fixed sample rates.

**Q: What about latency compensation?**
A: Report plugin latency to the host using `reportLatency()`. This is critical for effects with processing delays.

## Feature Support

**Q: Does my plugin support polyphony?**
A: Build polyphonic plugins using `nvoices` parameter with `faust2api`. For VST, combine with synth architecture flags.

**Q: Can I use MIDI?**
A: Yes. Use the `[midi:on]` metadata or include MIDI handlers in your DSP. Test with common DAWs (Reaper, Ableton, Cubase).

**Q: Does automation work?**
A: Most DAWs support automation if you properly declare parameters. Use labels like `hslider(...)` for automatable controls.

## Known Limitations

**Q: Which features are NOT supported in VST plugins?**
A: - File I/O operations
- Network access
- Unbounded processing delays (keeps latency at 0)
- Non-real-time operations

**Q: Why is my plugin mono when I expected stereo?**
A: Check your DSP file declaration—it should have 2 inputs/outputs. Use `_ , _` syntax for stereo routing.

## Troubleshooting

**Q: The plugin produces no sound**
A: 1. Check DSP logic with `faust -eval` first
2. Verify I/O channels match expected count
3. Test with a simple `process = _` (passthrough)
4. Check gain levels—DAW may have muted it

**Q: Audio is crackling/glitching**
A: - Buffer underruns → reduce plugin complexity
- Denormal numbers → add anti-denormal code
- Wrong sample rate → verify `setSampleRate()` calls

**Q: Plugin fails to load in DAW**
A: - Incorrect VST version mismatch
- Missing dependencies (libstdc++, libgcc on Linux)
- Plugin name conflicts with existing plugins
- Architecture mismatch (x86 vs x64)

## Resources

- [Steinberg VST Documentation](https://www.steinberg.net/developers/)
- [Faust VST Architecture Files](../../architecture/VST/)
- [faust2vst Tool Examples](../../tools/faust2appls/)

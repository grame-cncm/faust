# JUCE Framework Integration FAQ

## Setup & Installation

**Q: What is JUCE?**
A: JUCE is a cross-platform C++ framework for audio plugin and application development. It handles UI, audio I/O, and plugin hosting.

**Q: Can I use Faust with JUCE?**
A: Yes. Use `faust2api` with JUCE backend, or manually integrate Faust-generated C++ code into a JUCE project.

**Q: Which platforms does JUCE support?**
A: Windows, macOS, Linux, iOS, Android. Excellent cross-platform coverage.

**Q: Do I need JUCE Pro license?**
A: JUCE is dual-licensed: GPL (free) or commercial. GPL requires open-sourcing your plugin; commercial license required otherwise.

## Compilation & Building

**Q: How do I generate a JUCE plugin from Faust?**
A: Use `faust2api -juce myfile.dsp`. This generates a complete JUCE project with Faust DSP integrated.

**Q: Can I manually integrate Faust code into JUCE?**
A: Yes. Generate C++ with `faust -o myfile.cpp myfile.dsp`, then include it in your JUCE plugin's audio processor.

**Q: What's the typical project structure?**
A: Faust `.dsp` file → Generate C++ → Include in JUCE AudioProcessor → Build with Projucer or CMake.

**Q: Should I use Projucer or CMake?**
A: Projucer is traditional JUCE workflow. CMake is more modern and flexible. Both work with Faust.

## Audio I/O & Latency

**Q: What latency can JUCE achieve?**
A: Usually 10-50ms depending on DAW buffer size. JUCE abstracts this—your plugin adapts to host's latency.

**Q: How do I report plugin latency to the host?**
A: Set `totalNumInputChannels` request and report latency samples. JUCE provides helper methods.

**Q: Does JUCE handle sample rate negotiation?**
A: Yes automatically. JUCE calls your `prepareToPlay()` with the host's sample rate. Adapt Faust DSP accordingly.

## Feature Support

**Q: Can I create a polyphonic JUCE synthesizer with Faust?**
A: Yes. Use `faust2api` with `-nvoices` parameter to generate polyphonic processor.

**Q: Does JUCE support MIDI?**
A: Yes, fully. MIDI messages routed to your AudioProcessor. Access via `processMidiBuffer()`.

**Q: Can I add custom UI with JUCE?**
A: Yes, extensively. JUCE provides UI framework (sliders, knobs, labels, etc.). Integrate Faust parameters with JUCE Components.

**Q: Does JUCE support parameter automation?**
A: Yes. Register parameters with JUCE AudioProcessorValueTreeState (APVTS) for full automation support.

**Q: Can I add real-time visualization?**
A: Yes. Use JUCE's Graphics API to draw waveforms, spectrums, etc. Note: Keep it real-time safe.

## Known Limitations

**Q: What features DON'T work with JUCE integration?**
A: - Direct hardware access (JUCE abstracts this)
- Platform-specific features require separate handling
- Some Faust libraries with heavy I/O

**Q: Why is my JUCE plugin bigger than VST?**
A: JUCE includes framework overhead. Typical sizes: 500KB-2MB. Uses static linking and template code generation.

**Q: Can I make money with JUCE plugins?**
A: Yes, but respect the license. GPL → open-source. Commercial license → proprietary code allowed.

## Troubleshooting

**Q: Plugin compiles but produces no sound**
A: 1. Verify Faust DSP logic (`faust -eval`)
2. Check I/O channel configuration in APVTS
3. Ensure `processBlock()` is calling Faust DSP
4. Test with simple passthrough first

**Q: MIDI input not working**
A: - Verify MIDI port registered in APVTS
- Check `processMidiBuffer()` receives events
- Ensure DSP file has MIDI input declarations

**Q: Parameter changes are jerky/laggy**
A: - Enable parameter smoothing in JUCE
- Check UI update frequency isn't excessive
- Profile CPU usage

**Q: Plugin UI is sluggish**
A: - Reduce timer callback frequency
- Off-load heavy computation to background thread
- Optimize custom painting code
- Profile with Xcode/Visual Studio profiler

**Q: Cross-platform build fails**
A: - Different C++ standards per platform
- Path separator issues (use File API, not string concatenation)
- Compiler flags differ → test on each platform
- Dependencies missing on one platform

## Resources

- [JUCE Documentation](https://docs.juce.com/)
- [JUCE Audio Plugin Format](https://docs.juce.com/master/tutorial_audio_plugin_client.html)
- [Faust JUCE Integration](../../architecture/juce/)
- [JUCE Forum](https://forum.juce.com/)
- [faust2api JUCE Backend](../../architecture/api/)

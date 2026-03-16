# Real-Time Synthesis FAQ (JACK, ALSA, PortAudio)

## Setup & Installation

**Q: What's the difference between JACK, ALSA, and PortAudio?**
A: 
- **JACK**: Professional audio server (Linux/macOS). Low latency, multi-client routing.
- **ALSA**: Linux audio subsystem. Lower-level, used by JACK. Direct hardware access.
- **PortAudio**: Cross-platform audio abstraction layer. Works on Windows, macOS, Linux.

**Q: Which should I use?**
A: JACK for pro Linux audio work, PortAudio for cross-platform apps, ALSA for embedded systems.

**Q: Do I need to install JACK?**
A: Yes, on Linux/macOS. Windows uses different audio backends (ASIO, DirectSound, WASAPI).

**Q: How do I set up JACK on Linux?**
A: 1. Install: `sudo apt install jack-tools jackd`
2. Configure: Use QJackCtl to set sample rate, buffer size
3. Start: `jackd -d alsa` or via QJackCtl GUI

## Compilation & Building

**Q: How do I compile a Faust program for JACK?**
A: Use `faust2jack myfile.dsp`. This generates a standalone JACK client application.

**Q: What about ALSA?**
A: Use `faust2alsa myfile.dsp` for direct ALSA output (no JACK dependency).

**Q: How do I create a PortAudio application?**
A: Use `faust2api` with `-portaudio` flag, or use `faust2caqt` / `faust2paqt` for GUI versions.

**Q: Can I compile with GUI?**
A: Yes. Use `faust2jgtk` (JACK + GTK UI), `faust2jqt` (JACK + Qt UI), etc.

## Audio I/O & Latency

**Q: What buffer sizes should I use?**
A: 256, 512, or 1024 samples at 48kHz. Smaller = lower latency but higher CPU/dropout risk.

**Q: How do I achieve low latency?**
A: 1. Set small buffer size (256 samples)
2. Use realtime priority (run with `-r` flag or set thread priority)
3. Tune CPU governor to performance mode
4. Minimize system load
5. Test with `jack_delay` tool

**Q: Why am I getting JACK xruns (buffer underruns)?**
A: - Buffer size too small for your DSP complexity
- System load too high (background processes)
- CPU frequency scaling → disable it for realtime
- Thread priority not set → run with realtime priority

**Q: How do I monitor latency?**
A: Use `jack_delay` tool: `jack_delay`. JACK also reports xruns when they occur.

## Feature Support

**Q: Can I use MIDI over JACK?**
A: Yes. JACK transports MIDI events. Connect your MIDI controller to your JACK app in QJackCtl.

**Q: Does my app support multiple channels?**
A: Yes, if your DSP declares them. Route channels in QJackCtl or using `jack_connect` command.

**Q: Can I record output?**
A: Yes. Use `faust2rec` or connect to JACK recording tools like Ardour.

## Known Limitations

**Q: Why does my JACK app disconnect unexpectedly?**
A: - DSP took too long to process (xrun) → reduce complexity
- JACK server stopped → restart it
- Port name conflict → rename ports

**Q: Why is there no sound?**
A: - Audio not routed correctly in QJackCtl
- JACK server not running
- No input source selected
- Volume at zero

**Q: Can I use JACK on macOS?**
A: Yes, but CoreAudio is usually better. Use JACK for professional routing scenarios.

**Q: Does PortAudio work on all platforms?**
A: Yes, but uses native backends: WASAPI (Windows), Core Audio (macOS), ALSA/JACK (Linux).

## Troubleshooting

**Q: JACK won't start with my audio interface**
A: 1. Check interface is recognized: `aplay -l`
2. Try different driver: `jackd -d alsa -d hw:0`
3. Verify sample rate matches audio interface
4. Check for permission issues: `groups $USER | grep audio`

**Q: Constant crackling/glitching even at high buffer sizes**
A: - Check CPU temperature (thermal throttling?)
- Verify no kernel module conflicts
- Try different JACK driver/settings
- Profile DSP with flamegraph

**Q: App crashes on startup**
A: - Verify JACK is running and configured
- Check for missing libraries: `ldd ./myapp`
- Run with debug info: `gdb ./myapp`
- Check audio interface is compatible

**Q: MIDI input not working**
A: - Verify MIDI connections in QJackCtl
- Test: `arecordmidi -p system:announce -`
- Check DSP file contains MIDI input port definitions

## Resources

- [JACK Documentation](https://jackaudio.org/)
- [QJackCtl](https://qjackctl.sourceforge.io/)
- [PortAudio Documentation](http://www.portaudio.com/)
- [ALSA Project](https://www.alsa-project.org/)
- [Faust JACK/ALSA Architecture](../../architecture/)

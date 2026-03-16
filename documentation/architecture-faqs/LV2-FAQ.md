# LV2 Plugin Development FAQ

## Setup & Installation

**Q: What's LV2?**
A: LV2 (LADSPA Version 2) is an open-source plugin standard used primarily on Linux. It's more feature-rich than LADSPA and widely supported by Linux audio applications.

**Q: Which DAWs support LV2?**
A: Ardour, Reaper, Cakewalk, Qtractor, Carla, and many others. Linux is the primary platform.

**Q: Do I need special SDKs for LV2?**
A: No. LV2 is header-only. Just ensure the LV2 development headers are installed (`lv2-dev` on Ubuntu/Debian).

## Compilation & Building

**Q: How do I generate an LV2 plugin from Faust?**
A: Use `faust2lv2 myfile.dsp`. This generates a complete LV2 plugin ready to use.

**Q: Where should LV2 plugins be installed?**
A: Typical locations: `~/.lv2/` (user) or `/usr/lib/lv2/` (system). Most hosts search both.

**Q: What build errors are common?**
A: - Missing LV2 headers → install `lv2-dev`
- Wrong URI format → use reverse domain notation (e.g., `http://example.com/myplug`)
- Missing manifest.ttl → `faust2lv2` generates this

## Audio I/O & Latency

**Q: What buffer sizes does LV2 support?**
A: Varies by host. Most support 64-8192 samples. Always handle variable buffer sizes in your DSP.

**Q: How do I report latency?**
A: Use the LV2 latency port. Faust automatically reports delay introduced by your DSP.

**Q: Does sample rate negotiation work?**
A: Yes. The host provides the sample rate during initialization. Faust adapts automatically.

## Feature Support

**Q: Does LV2 support MIDI?**
A: Yes, via MIDI event ports. Declare MIDI inputs in the manifest for pitch/velocity control.

**Q: Can I create polyphonic LV2 plugins?**
A: Yes, but it requires manual polyphony management in the LV2 API layer. Use voice allocation strategies.

**Q: Does LV2 support parameter automation?**
A: Yes. LV2 ports are automatable. The host handles automation recording and playback.

**Q: Can I add a UI to my LV2 plugin?**
A: Yes. LV2 supports GTK, Qt, and other UI kits. `faust2lv2` generates a basic GTK UI automatically.

## Known Limitations

**Q: Which features DON'T work with LV2?**
A: - Complex file I/O (sandboxing limits access)
- Network operations
- Platform-specific features
- Some advanced UI elements

**Q: Why does my plugin work in one host but not another?**
A: LV2 hosts interpret the spec differently. Test with multiple hosts (Ardour, Carla, Cakewalk).

## Troubleshooting

**Q: My LV2 plugin isn't detected by the host**
A: 1. Check plugin installed in correct LV2 directory
2. Verify manifest.ttl is valid (use `lv2-validate`)
3. Check URI uniqueness—no conflicts with other plugins
4. Run `lv2ls` to list available plugins

**Q: Plugin loads but produces no sound**
A: 1. Verify DSP logic with `faust -eval`
2. Check I/O channel count matches expectations
3. Test with passthrough: `process = _`
4. Verify port connections in host

**Q: Audio has glitches or dropouts**
A: - Reduce DSP complexity
- Profile CPU usage
- Increase buffer size in host settings
- Check for denormal numbers

**Q: Plugin crashes or freezes**
A: - Use host's built-in debugger or GDB
- Comment out DSP sections to isolate issues
- Check for infinite loops or recursion
- Verify memory allocation doesn't fail

## Resources

- [LV2 Specification](http://lv2plug.in/)
- [LV2 Development Guide](http://lv2plug.in/book/)
- [faust2lv2 Documentation](../../tools/faust2appls/)
- [Linux Audio Wiki](https://wiki.linuxaudio.org/)

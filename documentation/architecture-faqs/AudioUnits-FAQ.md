# Audio Units (AU) FAQ

## Setup & Installation

**Q: What's the difference between AU and AudioUnit?**
A: They're the same thing. "AU" is the common abbreviation for Apple's Audio Unit plugin format.

**Q: Which Apple platforms support AU?**
A: macOS, iOS, and tvOS. AU is Apple's native plugin standard.

**Q: What versions of AU exist?**
A: AU v2 (older, macOS only) and AU v3 (newer, macOS 10.13+, iOS 11+). Faust supports both, but v3 is recommended for new projects.

**Q: Do I need Xcode?**
A: Yes. AU development on Apple platforms requires Xcode and the macOS/iOS SDK.

## Compilation & Building

**Q: How do I create an AU plugin with Faust?**
A: Use the AU architecture files in Faust. Compile with `faust -a au.cpp myfile.dsp -o au.cpp`, then build in Xcode.

**Q: Can I generate AU plugins from the command line?**
A: Not directly. Use the online compiler or build Xcode projects. Some tools like `faust2api` can help automate AU package generation.

**Q: What's the bundle structure for AU?**
A: AU bundles follow: `MyPlugin.component/Contents/MacOS/MyPlugin` (v2) or `MyPlugin.auextension` (v3).

## Audio I/O & Latency

**Q: What latency should I expect?**
A: macOS: 10-30ms. iOS: 20-100ms (device-dependent, usually lower on iPad Pro models).

**Q: Does AU support variable buffer sizes?**
A: Yes. AU must handle any buffer size the host provides (typically 128-4096 samples).

**Q: How do I report processing latency?**
A: Set the `kAudioUnitProperty_Latency` property to report delay in samples.

## Feature Support

**Q: Does AU support MIDI?**
A: Yes. Use `kAudioUnitType_MIDISynth` or `kAudioUnitType_MIDIProcessor` for MIDI inputs.

**Q: Can I build a polyphonic synthesizer?**
A: Yes. Define multiple MIDI voice handlers or use AU with built-in polyphony support.

**Q: Does AU support real-time parameter automation?**
A: Yes. All AU parameters are automatable by default. The host handles automation data.

**Q: Can I add a custom UI?**
A: Yes. AU v2 uses separate UI bundles (Carbon/Cocoa). AU v3 uses SwiftUI or AppKit directly.

## Known Limitations

**Q: What features DON'T work with AU?**
A: - Heavy file I/O (sandboxed environment)
- Direct hardware access
- Some cross-platform features
- Network operations in sandboxed DAWs

**Q: Why is AU different from VST?**
A: Apple's ecosystem is different—AU is optimized for macOS/iOS workflows. VST is cross-platform. They have different APIs and limitations.

**Q: Can I use the same AU on macOS and iOS?**
A: Partially. The core DSP can be shared, but AU wrapping differs. Use AU v3 for better cross-platform support.

## Troubleshooting

**Q: My AU plugin isn't recognized by Logic Pro or Final Cut Pro**
A: 1. Verify AU bundle structure is correct
2. Check bundle identifier matches your AU code
3. AU must be in `/Library/Audio/Plug-Ins/Components/` (system) or `~/Library/Audio/Plug-Ins/Components/` (user)
4. Restart the host application
5. Use `auval` tool to validate AU integrity

**Q: AU plugin operates silently (no sound output)**
A: 1. Check audio routing in host
2. Verify I/O bus count matches DSP expectations
3. Test with passthrough: `process = _`
4. Check gain and volume levels
5. Verify AU is receiving audio input (for effects)

**Q: Real-time safety warnings in Xcode**
A: AU runs in a real-time thread. Avoid: malloc/free, file I/O, network operations, locks. Use only real-time safe operations.

**Q: Large file size or slow loading**
A: - Strip debug symbols for distribution
- Optimize code compilation flags
- Check for unnecessary dependencies

**Q: Parameter changes don't take effect immediately**
A: - Verify parameter range configuration
- Check parameter smoothing isn't too aggressive
- Ensure `parameterTreeBlock` is properly set up (AU v3)

## Resources

- [Apple Audio Unit Documentation](https://developer.apple.com/documentation/audiounit)
- [AU v2 vs v3 Migration Guide](https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/AU_MigrationGuide/)
- [Faust AU Architecture Files](../../architecture/AU/)
- [Xcode Audio Plugin Template](https://developer.apple.com/documentation/audiotoolbox)

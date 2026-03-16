# Mobile Development FAQ (iOS & Android)

## Setup & Installation

**Q: What tools do I need for iOS development?**
A: Xcode (Mac only), iOS SDK, and Faust installed. Development requires a macOS machine.

**Q: What tools do I need for Android development?**
A: Android Studio, NDK, SDK, Java/Kotlin, and Faust. Linux, macOS, and Windows are all supported.

**Q: Can I develop on Windows for iOS?**
A: No. iOS development requires macOS. Use the [online compiler](http://faust.grame.fr/onlinecompiler/) if you don't have a Mac.

**Q: Can I test without real hardware?**
A: Yes. Use iOS Simulator and Android Emulator during development. Test on real devices before release.

## Compilation & Building

**Q: How do I generate an Android app?**
A: Use `faust2android myfile.dsp`. This generates a ready-to-install APK with a functional UI.

**Q: How do I generate an iOS app?**
A: Use Swift or Objective-C with the Faust C++ API. Build using Xcode with the iOS architecture files.

**Q: What Java version is required for Android?**
A: Java 8+ is recommended. Some older projects use Java 7, but 8 is the standard now.

**Q: Do I need to write custom code?**
A: For basic apps, `faust2android` generates everything. For custom layouts or advanced features, you'll edit the generated Xcode/Android Studio project.

## Audio I/O & Latency

**Q: What audio latency should I expect on mobile?**
A: Android: 20-100ms (varies by device). iOS: 10-30ms (better optimized). Use buffer sizes 256-512 for low latency.

**Q: How do I get low-latency audio on Android?**
A: - Use `AudioTrack` or preferably OpenSL/ES backend
- Request low-latency mode during AudioContext setup
- Test on target devices—this is critical
- Reduce buffer size incrementally—too small causes glitches

**Q: Does iOS Core Audio provide low latency?**
A: Yes, iOS is optimized for real-time audio. Most instruments/effects work with low latency out of the box.

## Feature Support

**Q: Can I use device sensors (accelerometer, gyroscope)?**
A: Yes, especially on Android via `faust2android`. iOS requires custom Swift/Objective-C integration with sensor APIs.

**Q: Does MIDI work on mobile?**
A: iOS: Yes, via Core MIDI. Android: Limited—requires Bluetooth MIDI adapters or inter-app MIDI APIs.

**Q: Can I build polyphonic synthesizers?**
A: Yes. Use `-nvoices` parameter. Test on target devices—mobile CPU is more limited than desktop.

**Q: Does OSC (Open Sound Control) work?**
A: Yes, for network control. Use the [osclib](../../architecture/osclib/) in your project.

## Known Limitations

**Q: What features DON'T work on mobile?**
A: - Unlimited polyphony (CPU constraints)
- Complex real-time file I/O
- Some Faust libraries with heavy computations
- Network streaming (limited bandwidth)
- Unbounded latency effects

**Q: Why is my app draining battery quickly?**
A: - High polyphony count
- Complex DSP algorithms
- Excessive sensor polling
- Audio running continuously at high gain
→ Optimize DSP and reduce CPU load

**Q: Why does audio work on my test device but not others?**
A: Different devices have different audio hardware and drivers. Always test on multiple target devices.

## Troubleshooting

**Q: Android app force closes on startup**
A: 1. Check Android Studio logcat for crash logs
2. Verify NDK version compatibility
3. Check that audio permissions are granted
4. Ensure DSP file has no syntax errors

**Q: iOS app silently fails to start audio**
A: 1. Verify app has audio permission
2. Check console output in Xcode
3. Ensure AudioSession is configured correctly
4. Test with a simple sine wave DSP

**Q: Audio is crackling/glitching**
A: - Reduce DSP complexity or polyphony
- Increase buffer size
- Profile CPU usage in profiler tools
- Check thermal throttling (device too hot)

**Q: GUI is unresponsive or slow**
A: - Reduce UI update frequency
- Off-load heavy computations to threads
- Profile rendering in profiler tools

**Q: Sensors aren't working**
A: - Verify app has sensor permissions (Android)
- Check CoreMotion setup (iOS)
- Test with native sensor apps first

## Resources

- [faust2android Documentation](../../architecture/android/README.md)
- [Faust iOS Architecture](../../architecture/iOS/)
- [Android Studio Documentation](https://developer.android.com/studio)
- [iOS Development Guide](https://developer.apple.com/ios/)
- [Faust Mobile Tutorials](https://ccrma.stanford.edu/~rmichon/faustTutorials/)

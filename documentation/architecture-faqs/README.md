# Architecture-Specific FAQ Index

Welcome to the Faust Architecture FAQ documentation. This directory contains platform-specific Frequently Asked Questions to help you get the most out of Faust on your chosen audio platform.

## Quick Links

### **Plugin Standards & Desktop**
- [**VST Plugin Development**](VST-FAQ.md) - VST 2.x and 3.x plugin creation for DAWs
- [**Audio Units (AU)**](AudioUnits-FAQ.md) - Apple's plugin format for macOS/iOS
- [**LV2 Plugin Development**](LV2-FAQ.md) - Open-source Linux plugin standard
- [**JUCE Framework Integration**](JUCE-FAQ.md) - Cross-platform plugin framework

### **Web & Cross-Platform**
- [**WebAudio & WebAssembly**](WebAudio-FAQ.md) - Deploy Faust on the web with WASM
- [**Real-Time Synthesis**](RealTime-FAQ.md) - JACK, ALSA, PortAudio for Linux/macOS/Windows

### **Mobile & Embedded**
- [**Mobile Development (iOS & Android)**](Mobile-FAQ.md) - Deploy to phones and tablets
- [**Embedded Platforms**](Embedded-FAQ.md) - Bela, Teensy, ESP32, Daisy, Arduino

---

## Choosing Your Platform

### **I want to create a DAW plugin**
→ Start with [VST-FAQ.md](VST-FAQ.md) (most common)  
→ Also consider: [Audio Units (AU)](AudioUnits-FAQ.md) for macOS, [LV2-FAQ.md](LV2-FAQ.md) for Linux

### **I want to deploy on the web**
→ Use [WebAudio-FAQ.md](WebAudio-FAQ.md) and [faustwasm](https://github.com/grame-cncm/faustwasm)

### **I want to create a mobile app**
→ Check [Mobile-FAQ.md](Mobile-FAQ.md) for iOS/Android guidance

### **I want to build a standalone application**
→ Use [Real-Time Synthesis FAQ](RealTime-FAQ.md) for JACK/ALSA/PortAudio standalone apps

### **I want to create embedded audio hardware**
→ See [Embedded-FAQ.md](Embedded-FAQ.md) for Bela, Teensy, ESP32, Daisy, etc.

### **I want maximum cross-platform support**
→ Use [JUCE-FAQ.md](JUCE-FAQ.md) - supports Windows, macOS, Linux, iOS, Android

---

## FAQ Structure

Each FAQ document is organized into these sections:

### **Setup & Installation**
General prerequisites, SDKs, tools, and getting started information.

### **Compilation & Building**
How to compile Faust for this platform, build tools, common build errors.

### **Audio I/O & Latency**
Buffer sizes, sample rate handling, latency optimization.

### **Feature Support**
What Faust features work on this platform: polyphony, MIDI, UI, automation, etc.

### **Known Limitations**
Features that DON'T work or are limited on this platform.

### **Troubleshooting**
Solutions to common problems: silence, crackling, crashes, loading issues.

### **Resources**
Links to official documentation, tools, examples, and communities.

---

## Platform Comparison Matrix

| Feature | VST | AU | LV2 | WebAudio | Mobile | Embedded | JUCE |
|---------|-----|----|----|----------|--------|----------|------|
| **Cross-Platform** | Yes | No (Apple only) | No (Linux) | Yes | Yes | Limited | Yes |
| **Latency** | Low (10-30ms) | Very Low (10-30ms) | Low (10-30ms) | Medium (20-50ms) | Medium-High | Very Low (1-50ms) | Low (10-30ms) |
| **MIDI Support** | Yes | Yes | Yes | Yes (Web MIDI) | Yes | Yes | Yes |
| **Polyphony** | Full | Full | Full | Full | Limited | Limited | Full |
| **Automation** | Yes | Yes | Yes | N/A | Yes | N/A | Yes |
| **Learning Curve** | Steep | Steep | Moderate | Easy | Easy | Moderate | Moderate-High |
| **Free to Deploy** | Yes (many free hosts) | Yes (system-bundled) | Yes | Yes | Yes | Yes | GPL or Commercial |
| **Most Used** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ (Mac only) | ⭐⭐ (Linux) | ⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐ | ⭐⭐⭐ |

---

## Faust Tools for Each Platform

- **VST**: `faust2vst` (command-line tool)
- **AU**: Faust AU architecture files + Xcode
- **LV2**: `faust2lv2` (command-line tool)
- **WebAudio**: [faustwasm](https://github.com/grame-cncm/faustwasm) project
- **Mobile**: `faust2android`, `faust2api` (iOS)
- **Embedded**: Bela IDE, Arduino IDE, PlatformIO
- **JUCE**: `faust2api -juce`
- **All Platforms**: `faust2api` (flexible API generator)

---

## Getting Help

1. **Check the relevant FAQ** for your platform above
2. **Search [GitHub Issues](https://github.com/grame-cncm/faust/issues)** for similar problems
3. **Ask in [Faust Community Discussions](https://github.com/grame-cncm/faust/discussions)**
4. **Visit [Faust Documentation](https://faustdoc.grame.fr/)**

---

## Contributing to These FAQs

Have a question not covered? Found an error? Want to improve these docs?

1. [Open a GitHub issue](https://github.com/grame-cncm/faust/issues/new) with your question/suggestion
2. [Submit a pull request](https://github.com/grame-cncm/faust/pulls) with improvements
3. Share your experience in [Discussions](https://github.com/grame-cncm/faust/discussions)

---

**Last Updated**: March 2026  
**Maintained by**: Faust Community  

For more information about Faust, visit [faust.grame.fr](https://faust.grame.fr)

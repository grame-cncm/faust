# Embedded Platforms FAQ (Bela, Teensy, ESP32, Daisy)

## Setup & Installation

**Q: What embedded platforms does Faust support?**
A: Bela, Teensy, ESP32, Daisy Seed, Arduino, and others. Each has specific toolchains and constraints.

**Q: Do I need special compilers for each platform?**
A: Yes. Bela uses Bela IDE, Teensy uses Arduino IDE + Teensyduino, ESP32 uses Arduino IDE + ESP32 board support.

**Q: Which is the easiest to get started with?**
A: Bela (most Faust-friendly, specialized tools). Teensy is also good with Arduino IDE.

**Q: Do I need to buy expensive hardware?**
A: No. Bela (~$200), Teensy (~$75), ESP32 (~$30), Daisy (~$150). Very affordable for audio.

## Compilation & Building

**Q: How do I generate code for Bela?**
A: Use the [Bela IDE](https://bela.io/code). Upload .dsp and the IDE compiles and deploys automatically.

**Q: Can I compile Teensy code outside the IDE?**
A: Yes, but Arduino IDE is simpler. Use PlatformIO for CLI-based workflow.

**Q: How do I use ESP32 with Faust?**
A: Use Arduino IDE or PlatformIO with Faust2API. Generate C++ API, integrate into your Arduino sketch.

**Q: Is source code size a concern?**
A: Yes. Teensy and ESP32 have limited memory. Keep DSP simple; avoid large lookup tables.

## Audio I/O & Latency

**Q: What latency can I achieve on embedded boards?**
A: Bela: 2-5ms. Teensy: 5-15ms. ESP32: 20-50ms (limited CPU). Daisy: 1-10ms.

**Q: What buffer sizes are typical?**
A: Bela: 16-64 samples. Teensy: 64-128. ESP32: 256-1024. Small buffers for low latency.

**Q: Do embedded systems handle variable buffer sizes?**
A: No, usually fixed. Design your DSP for specific buffer and sample-rate constraints.

**Q: How do I optimize for low latency?**
A: - Use smallest buffer size stable on your platform
- Reduce DSP complexity
- Profile CPU usage with platform tools
- Disable unnecessary features

## Feature Support

**Q: Can I use MIDI on embedded boards?**
A: Yes. Teensy has MIDI I/O. Bela supports USB MIDI. ESP32 via serial or Bluetooth.

**Q: Does polyphony work?**
A: Limited by CPU. Bela: 8-16 voices typical. Teensy: 4-8. ESP32: 2-4. Test on your board.

**Q: Can I add sensors (accelerometer, buttons)?**
A: Yes. All platforms support GPIO and I2C/SPI sensors. Use platform-specific libraries (Wire for Arduino).

**Q: Can I use WiFi/Bluetooth?**
A: ESP32 has built-in WiFi and Bluetooth. Teensy and Bela require external modules.

## Known Limitations

**Q: What features DON'T work embedded?**
A: - Very high polyphony (CPU limited)
- Heavy DSP algorithms
- File I/O (very limited filesystem)
- Network operations (power/latency constraints)
- Float precision (some platforms use fixed-point)

**Q: Why is my audio noisy on ESP32?**
A: - Power supply quality issues → use good USB cable
- WiFi interference → disable WiFi or isolate audio
- Inadequate heat sinking → add cooling if hot
- Clock instability → verify oscillator

**Q: Why is my app using too much CPU?**
A: - Polyphony too high → reduce voices
- DSP too complex → simplify algorithms
- Inefficient code → profile with platform tools
- Real-time pressure → increase buffer size

## Troubleshooting

**Q: Audio is silent on my board**
A: 1. Check audio output is enabled and not muted
2. Test with `process = 0.1` (constant signal) to verify output path
3. Verify audio codec is properly initialized (board-specific)
4. Check connections (headphone jack, speakers)

**Q: Frequent audio dropouts/crackling**
A: - Increase buffer size
- Reduce DSP complexity or polyphony
- Check power supply voltage stability
- Profile CPU usage
- Run on stable power (not sketchy USB)

**Q: Board reboots unexpectedly**
A: - Stack overflow (DSP too complex) → simplify
- Watchdog timer (code too slow) → optimize
- Brownout (power dip) → better power supply
- Memory leak → check for allocations in audio callback

**Q: Sensors not responding**
A: - Verify I2C/SPI pins correct for your board
- Check I2C pullup resistors present
- Use board-specific pin definitions (not generic)
- Test with simple sensor read sketch first

**Q: Can't upload/deploy code**
A: - Board not recognized → check USB cable/driver
- Wrong board selected in IDE
- Firmware corrupted → use board reset/bootloader
- Serial port permissions (Linux) → add user to dialout group

## Resources

- [Bela Documentation](https://learn.bela.io/)
- [Teensy Audio Library](https://www.pjrc.com/teensy/td_libs_Audio.html)
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
- [Faust Embedded Architecture Files](../../architecture/)
- Daisy Seed: https://electro-smith.com/products/daisy
- [PlatformIO](https://platformio.org/) - Alternative IDE for embedded

# WebAudio & WebAssembly FAQ

## Setup & Installation

**Q: What's the difference between Web Audio and faustwasm?**
A: Web Audio is deprecated in Faust. Use [faustwasm](https://github.com/grame-cncm/faustwasm) for new WebAssembly projects—it's more modern and feature-complete.

**Q: Do I need Node.js to use Faust on the web?**
A: For development, yes. For deployment, no—only a web browser is required. Users need a modern browser supporting WebAssembly.

**Q: Which browsers support WebAssembly?**
A: All modern browsers (Chrome, Firefox, Safari, Edge). Minimum versions: Chrome 57+, Firefox 52+, Safari 11+, Edge 79+.

## Compilation & Building

**Q: How do I compile a Faust program to WebAssembly?**
A: Use faustwasm or the [online compiler](https://faustide.grame.fr/). For CLI: `faust2wasm myfile.dsp -o output`.

**Q: Can I use the online compiler for production?**
A: No—it's for learning. For production, compile locally or use faustwasm in your build pipeline.

**Q: What build tools are recommended?**
A: Webpack, Vite, or Rollup. faustwasm includes examples for each.

## Audio I/O & Latency

**Q: What's the typical latency on the web?**
A: 10-50ms depending on buffer size (512-4096 samples) and browser. Requires `AudioWorklet` for low latency.

**Q: Do I need AudioWorklet or ScriptProcessor?**
A: Use `AudioWorklet` (new standard). `ScriptProcessor` is deprecated and has higher latency.

**Q: How do I handle varying sample rates?**
A: The browser's AudioContext has a fixed sample rate. Faust automatically adapts, but specify it during compilation if needed.

## Feature Support

**Q: Can I use all Faust libraries on the web?**
A: Most work, but file I/O and some native APIs don't. Test complex libraries before deployment.

**Q: Does MIDI work in the browser?**
A: Yes, via the Web MIDI API. Requires HTTPS and user permission. Not all browsers support it equally.

**Q: Can I create polyphonic synthesizers?**
A: Yes. Use `-nvoices` parameter during compilation. Test with many voices—browser performance varies.

**Q: Does automation/parameter changes work smoothly?**
A: Yes. Parameter changes are real-time. Smooth parameter interpolation is handled by Faust.

## Known Limitations

**Q: Which features DON'T work on the web?**
A: - File I/O (no access to local filesystem)
- Network requests (limited to CORS-allowed domains)
- System calls and platform-specific operations
- Real-time constraints are looser than native

**Q: Why is my WASM file so large?**
A: Faust generates optimized code but includes runtime overhead. Typical: 50KB-200KB for simple DSPs. Use `brotli` or `gzip` compression.

## Troubleshooting

**Q: Audio is silent in my web app**
A: 1. Check browser console for errors
2. Verify AudioContext is running (not suspended)
3. Test with a simple passthrough (`process = _`)
4. Check volume levels and gain parameters
5. Verify WASM file loaded correctly (network tab)

**Q: My parameters don't change the sound**
A: - Verify parameter names with `getParamDef()`
- Check you're calling `setParamValue()` correctly
- Some parameters may require `begin()` / `end()` calls

**Q: WASM module fails to load**
A: - HTTPS required (not http://localhost:something with certain browsers)
- CORS issues → ensure proper headers
- Browser/version incompatible with WebAssembly
- WASM file path incorrect

**Q: Performance is poor in the browser**
A: - Reduce polyphony voices
- Simplify DSP code
- Off-load non-real-time tasks to Web Workers
- Profile with browser DevTools

## Resources

- [faustwasm GitHub](https://github.com/grame-cncm/faustwasm)
- [Web Audio API Docs](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API)
- [WebAssembly Documentation](https://webassembly.org/)
- [Faust Online Compiler](https://faustide.grame.fr/)

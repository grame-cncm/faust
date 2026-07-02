# faust2daisy — code diagnostic

Review of the faust2daisy toolchain: `tools/faust2appls/faust2daisy`,
`architecture/daisy/{faust_daisy_parser.py, daisy_soundfile_gen.py,
daisy_sd_soundfile.hpp, sd_uploader.cpp, sd_upload.py, generate_config.py,
ex_faust.cpp, Makefile, Makefile.sd_uploader}` and
`architecture/faust/gui/DaisyControlUI.h`.

Line numbers are as of this review and may drift as the files are edited.

---

## Is `architecture/daisy/soundfile.hpp` still used?

**No — it is dead code.** It has zero references anywhere in the repo
(`grep -rn soundfile.hpp` finds only `daisy_soundfile.hpp` /
`daisy_sd_soundfile.hpp`). It is the early FatFS `wav_player` draft
(`#ifndef SOUNDFILE`, `struct wav_player`, a bump allocator into
`DSY_SDRAM_BSS`). It was superseded by:
- `daisy_soundfile_gen.py` → generated `daisy_soundfile.hpp` (QSPI inlining), and
- `daisy_sd_soundfile.hpp` (runtime SD loading).

**Recommendation:** delete `architecture/daisy/soundfile.hpp` (it also contains a
non-working `_sdram_alloc` stub and would mislead readers).

---

## Confirmed bugs (will break build or codegen)

### 0. `chip` used while undefined (NameError) — FIXED
`faust_daisy_parser.py`: `chip` was only assigned inside
`if config_file.isdigit() == False:` (the config-file branch), but `write()`
references it unconditionally (lines ~706, 656, 756, …). When the parser is
invoked with `config_file == "0"` (no config actually passed to it — e.g. a
build with no board flag where `generate_config.py` did not set `JSON_CONFIG`),
`write()` raises `NameError: name 'chip' is not defined`.
**Fix applied:** default `chip = "seed"` before the config block (the config
overrides it when present). Note: a no-config invocation still won't emit
`SEED=true`, so the architecture's `#ifdef SEED/PATCHSM` may leave `hw`
undefined — pass a board flag (`-seed`/`-patch`/…) or ensure `generate_config.py`
runs.

### 1. MIDI `keyoff` → wrong array name → C++ compile error
`faust_daisy_parser.py:560`
```python
midistr += f"... scale::scale_t::{elem.scale}, &(midi_keyoffs[{ref_idx}])), \n"
```
The array is declared as `midi_keyoff` (line 527), but the generated code
references `midi_keyoffs` (extra `s`). Any DSP with a `[midi:keyoff …]` control
generates code that won't compile (`midi_keyoffs` undeclared). The `keyon`
case (line 557) is correct; only `keyoff` has the typo.
**Fix:** `midi_keyoffs` → `midi_keyoff`.

### 2. Polyphonic + digital GPIO output is broken (two faults)
- **Codegen:** `faust_daisy_parser.py:812`
  ```python
  controlstr += f"\tshared_digi_output<{nvoices}>({prefix}{elem.pin_index}, digi_output::pwm_t::{pwm}), \n"
  ```
  `pwm` is undefined (the non-poly branch at line 810 correctly uses
  `elem.pwm`). With `nvoices>1` **and** a GPIO output this raises a Python
  `NameError` at generation time.
- **Architecture:** `ex_faust.cpp` `shared_digi_output` (≈741)
  ```cpp
  shared_digi_output(daisy::Pin pin_, float min_ = 0.0f, float max_ = 1.0f)
      : digi_output::digi_output(pin_, min_, max_)   // base ctor is (pin_, pwm_t, min_, max_)
  ```
  passes a `float` where the base `digi_output(daisy::Pin, pwm_t, float, float)`
  expects a `pwm_t` → C++ compile error (no implicit `float`→enum). So even
  with the codegen fixed, the type won’t compile.
**Net:** `nvoices>1` together with any `[gpio:…]` output (LED / PWM bargraph)
cannot build. **Fix:** give `shared_digi_output` a `pwm_t` parameter and forward
it to the base; emit `elem.pwm` (not `pwm`) in the parser.

### 3. Parser requires Python ≥ 3.12 (nested-quote f-strings)
`faust_daisy_parser.py:507,509`
```python
controlstr += f"#define RX_PIN {config_midi["rx_pin"]} \n"
```
Re-using `"` inside a `"…"` f-string is only legal since Python 3.12 (PEP 701).
On Python 3.8–3.11 the **whole module fails to import with a SyntaxError**, so
faust2daisy is unusable there (this path is hit by `-midi-uart`, and the
SyntaxError prevents the parser from running at all). Many distros still ship
3.10/3.11.
**Fix:** use single quotes inside: `{config_midi['rx_pin']}`.

---

## Robustness / correctness risks

### 4. Parser failures are swallowed by `eval "$(…)"`
`faust2daisy:264,269`
```bash
eval "$(python3 "$FAUSTARCH/daisy/faust_daisy_parser.py" … )"
```
`eval "$(…)"` discards the Python exit status, so `set -e` cannot catch a parser
crash/`sys.exit(1)` (e.g. a missing soundfile, or bugs #1–#3 above). The build
proceeds with a missing/stale `daisy_arch.cpp` and only fails later at the
second `faust` call — a confusing failure mode. **Fix:** capture stdout to a
temp file, check `$?`, then `eval` the file (or have the script abort if
`daisy_arch.cpp` wasn’t produced).

### 5. `value_ptr` is uninitialized in `control`
`ex_faust.cpp:184` (`float *value_ptr;` with no initializer; `control()` leaves
it indeterminate). Correctness depends on `buildUserInterface` calling
`set_value_ptr` for exactly the controls in `input_list`, in order. The
commented-out `//*value_ptr = init;` (≈393) suggests a prior null-deref. If the
zone/`input_list` counts ever diverge, `input_list[control_counter]` (DaisyControlUI
`addADCEntry`) goes out of bounds, or `update()` dereferences garbage.
**Fix:** initialize `value_ptr = nullptr;` and guard `update()`/`setup()` against
null; assert `control_counter < input_list.size()`.

### 6. Only the first top-level UI group is scanned
`faust_daisy_parser.py:829`
```python
scan.recursive_lookup(dsp_layout["ui"][0], config_ui)
```
Only `ui[0]` is traversed. Faust normally emits a single root group, but a DSP
that produces multiple top-level UI entries would silently lose controls.
**Fix:** iterate all of `dsp_layout["ui"]`.

### 7. DAC channel fallbacks
`faust_daisy_parser.py:751–797`
- If a DAC’s `channel` is not `A7/A8` (seed) or `C1/C10` (patchsm), `last_chn`
  stays `None` → emits `dac(None, …)` → compile error.
- With exactly two DACs, `dac_chnls` is forced to `BOTH` regardless of which two
  channels were actually requested (and each `dac_list` entry uses whatever
  `last_chn` was on its iteration). Mismatch possible for unusual mappings.
**Fix:** validate the channel and default/`#error` clearly; derive `dac_chnls`
from the set of channels actually used.

### 8. `patchsm_pin_map[elem.pin_index]` can `KeyError`
`faust_daisy_parser.py:659,664,710` index `patchsm_pin_map` directly; an ADC/GPIO
pin not present in the map crashes the parser. **Fix:** `.get()` with a clear
error message listing valid pins.

---

## Minor / cleanup

### 9. `export $APP_TYPE` is wrong/dead
`faust2daisy:366` — `export BOOT_NONE` (etc.) exports a variable *named*
`BOOT_NONE` with empty value, not `APP_TYPE`. Harmless (the value is passed to
make via `make APP_TYPE=$APP_TYPE`), but misleading. Remove or use `export APP_TYPE`.

### 10. `temp` file created in CWD for every `#define` prepend
`faust2daisy:275+` repeatedly does `… > temp && mv temp <out>` in the *current*
directory. This pollutes the user’s cwd, is not concurrency-safe, and fails if
cwd is read-only. **Fix:** write into `$SRCDIR/$dspName/` or use `mktemp`. (Also,
~15 separate rewrite passes of the file could be a single prepend.)

### 11. `-upload-sd` JSON generation
`faust2daisy:220` runs `faust "$p" -json -o …/ex_faust.cpp` without `$OPTIONS`
or `-a`. It writes a throwaway `ex_faust.cpp` and, if the DSP needs extra options
to compile (imports, etc.), JSON generation could fail. Use `-o /dev/null`-style
or pass `$OPTIONS`.

### 12. Unquoted `$1`/`$p` in arg parsing
`faust2daisy:85,89,…` (`while [ $1 ]`, `if [ $p = … ]`) break on empty args or
paths with spaces. Quote them (`while [ -n "$1" ]`, `[ "$p" = … ]`).

### 13. `-sd` arena vs `-sdram`
Both place data in SDRAM (`faust_sd_arena` default 32 MB + the DSP’s
`FAUST_SDRAM_SIZE_BYTES`). Combined with large delay tables this can overflow
64 MB. Build-time sizing (`SD_SOUNDFILE_BYTES`) mitigates it when the WAVs are
present at build time, but the 32 MB default applies otherwise. Worth a note/guard.

---

## Things that look correct (verified, for reference)
- `daisy_sd_soundfile.hpp`: sector-aligned SD reads + AXI-SRAM buffer/`FIL`,
  basename lookup, `SCB_*DCache` around the load — sound.
- `DaisyControlUI::setup_controls` platform-channel ordering (Patch) — sound;
  Seed/no-config falls back to identity.
- `gpio_method` polarity (`> noise_threshold`) — correct.
- WAV decode (16/24/32-bit + float32) in both the Python generator and the
  on-device reader — byte-exact (checked against reference).

---

## Suggested priority
1. #1 `midi_keyoff` typo (silent compile break for keyoff controls).
2. #3 Python 3.12-only f-strings (blocks the tool on common Python versions).
3. #2 poly + GPIO-out (compile break for a documented feature combo).
4. #4 parser-error propagation in the shell script.
5. Delete dead `soundfile.hpp` (#0).
6. The rest as cleanup.

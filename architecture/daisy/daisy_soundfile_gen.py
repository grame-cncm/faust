#!/usr/bin/env python3
# ---------------------------------------------------------------------
# faust2daisy : compile-time Soundfile support
#
# This module parses the WAV files referenced by a Faust DSP (through the
# "soundfile" primitive) and generates a self-contained C++ header
# (daisy_soundfile.hpp) in which all the audio data is inlined as
# 'const float' arrays. No dependency on libsndfile, no runtime file I/O
# and no dynamic allocation : everything is resolved at build time.
#
# The generated header provides :
#   - a minimal 'Soundfile' struct (same field layout as
#     architecture/faust/gui/Soundfile.h) ;
#   - one prebuilt 'Soundfile' instance per distinct soundfile URL ;
#   - a 'defaultsound' empty soundfile (used by the DSP before
#     buildUserInterface, and as a fallback) ;
#   - 'daisy_lookup_soundfile(url)' used by DaisyControlUI::addSoundfile.
#
# The big sample buffers are emitted as 'const' so that, in QSPI flash
# mode (-qspi), they live in QSPI and are read directly (memory-mapped),
# without being copied into RAM/SDRAM.
#
# Supported WAV formats : PCM 16/24/32 bit and IEEE float 32 bit.
# ---------------------------------------------------------------------

import os
import re
import sys
import struct
from array import array

# Mirror of the constants used in architecture/faust/gui/Soundfile.h.
# The Faust C++ backend clamps the (signal) "part" index to
# [0, MAX_SOUNDFILE_PARTS-1], so these arrays must always have 256 slots.
MAX_SOUNDFILE_PARTS = 256
MAX_CHAN = 64
BUFFER_SIZE = 1024      # length of an empty/silent part
SAMPLE_RATE = 44100     # sample rate reported for empty parts

# WAV format tags
WAVE_FORMAT_PCM = 0x0001
WAVE_FORMAT_FLOAT = 0x0003
WAVE_FORMAT_EXTENSIBLE = 0xFFFE


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


# ---------------------------------------------------------------------
# WAV parsing (no external dependency)
# ---------------------------------------------------------------------

class WavError(Exception):
    pass


def parse_wav(path):
    """Parse a WAV file and return a dict :
        { 'channels', 'sample_rate', 'bits', 'frames', 'data' }
    where 'data' is a list of per-channel lists of floats in [-1, 1].
    """
    with open(path, 'rb') as f:
        raw = f.read()

    if len(raw) < 12 or raw[0:4] != b'RIFF' or raw[8:12] != b'WAVE':
        raise WavError("'%s' is not a valid RIFF/WAVE file" % path)

    fmt_tag = None
    num_channels = None
    sample_rate = None
    bits = None
    data_bytes = None

    pos = 12
    n = len(raw)
    while pos + 8 <= n:
        chunk_id = raw[pos:pos + 4]
        chunk_size = struct.unpack_from('<I', raw, pos + 4)[0]
        body = pos + 8

        if chunk_id == b'fmt ':
            fmt_tag, num_channels, sample_rate, _byte_rate, _block_align, bits = \
                struct.unpack_from('<HHIIHH', raw, body)
            # Extensible format : the real tag is the first 2 bytes of the
            # SubFormat GUID, located 8 bytes into the extension block.
            if fmt_tag == WAVE_FORMAT_EXTENSIBLE and chunk_size >= 26:
                fmt_tag = struct.unpack_from('<H', raw, body + 24)[0]
        elif chunk_id == b'data':
            data_bytes = raw[body:body + chunk_size]

        # Chunks are word-aligned : skip the padding byte for odd sizes.
        pos = body + chunk_size + (chunk_size & 1)

    if fmt_tag is None:
        raise WavError("'%s' : missing 'fmt ' chunk" % path)
    if data_bytes is None:
        raise WavError("'%s' : missing 'data' chunk" % path)

    if fmt_tag == WAVE_FORMAT_FLOAT:
        if bits != 32:
            raise WavError("'%s' : unsupported float format (%d bits, only 32 supported)" % (path, bits))
    elif fmt_tag == WAVE_FORMAT_PCM:
        if bits not in (16, 24, 32):
            raise WavError("'%s' : unsupported PCM format (%d bits, only 16/24/32 supported)" % (path, bits))
    else:
        raise WavError("'%s' : unsupported WAV format tag 0x%04X" % (path, fmt_tag))

    interleaved = _decode_samples(data_bytes, fmt_tag, bits)

    # De-interleave into per-channel buffers.
    channels = [interleaved[c::num_channels] for c in range(num_channels)]
    frames = len(channels[0]) if num_channels > 0 else 0

    return {
        'channels': num_channels,
        'sample_rate': sample_rate,
        'bits': bits,
        'frames': frames,
        'data': channels,
    }


def _decode_samples(data, fmt_tag, bits):
    """Decode the raw 'data' chunk into a flat list of floats in [-1, 1]."""
    little_endian = (sys.byteorder == 'little')

    if fmt_tag == WAVE_FORMAT_FLOAT:
        arr = array('f')
        arr.frombytes(data[:len(data) - (len(data) % 4)])
        if not little_endian:
            arr.byteswap()
        return list(arr)

    if bits == 16:
        arr = array('h')
        arr.frombytes(data[:len(data) - (len(data) % 2)])
        if not little_endian:
            arr.byteswap()
        scale = 1.0 / 32768.0
        return [s * scale for s in arr]

    if bits == 32:
        arr = array('i')
        arr.frombytes(data[:len(data) - (len(data) % 4)])
        if not little_endian:
            arr.byteswap()
        scale = 1.0 / 2147483648.0
        return [s * scale for s in arr]

    if bits == 24:
        scale = 1.0 / 8388608.0
        out = []
        count = len(data) // 3
        for i in range(count):
            b = i * 3
            v = data[b] | (data[b + 1] << 8) | (data[b + 2] << 16)
            if v & 0x800000:
                v -= 0x1000000
            out.append(v * scale)
        return out

    raise WavError("unsupported sample format")


# ---------------------------------------------------------------------
# Soundfile detection in the Faust JSON UI
# ---------------------------------------------------------------------

def scan_soundfiles(dsp_layout):
    """Return a de-duplicated list of (label, url) soundfile widgets found
    in the DSP JSON UI, preserving first-seen order."""
    found = []
    seen = set()

    def recurse(node):
        if isinstance(node, dict):
            if node.get('type') == 'soundfile':
                url = node.get('url', '')
                if url not in seen:
                    seen.add(url)
                    found.append((node.get('label', ''), url))
            for item in node.get('items', []):
                recurse(item)

    for top in dsp_layout.get('ui', []):
        recurse(top)
    return found


def parse_url(url):
    """Extract the list of file names from a Faust soundfile URL.
    Handles "{'a.wav';'b.wav'}" lists as well as a bare file name."""
    names = re.findall(r"'([^']*)'", url)
    if names:
        return names
    cleaned = url.strip().strip('{}').strip()
    return [cleaned] if cleaned else []


def resolve_file(name, search_dirs):
    """Resolve 'name' against the search directories. Return the absolute
    path or None if not found."""
    if os.path.isabs(name) and os.path.isfile(name):
        return name
    for d in search_dirs:
        candidate = os.path.join(d, name)
        if os.path.isfile(candidate):
            return candidate
    return None


# ---------------------------------------------------------------------
# C++ header generation
# ---------------------------------------------------------------------

def _fmt_float(v):
    """Format a float as a valid C++ 'float' literal (with 'f' suffix)."""
    s = format(float(v), '.7g')
    if 'e' not in s and 'E' not in s and '.' not in s and 'inf' not in s and 'nan' not in s:
        s += '.0'
    return s + 'f'


def _emit_float_array(out, name, values):
    out.append("static const float %s[%d] = {\n" % (name, len(values)))
    chunk = []
    line = []
    for i, v in enumerate(values):
        line.append(_fmt_float(v))
        if len(line) == 12:
            chunk.append("    " + ", ".join(line) + ",")
            line = []
    if line:
        chunk.append("    " + ", ".join(line) + ",")
    out.append("\n".join(chunk))
    out.append("\n};\n")


def _emit_int_array(out, name, values):
    out.append("static int %s[%d] = {\n" % (name, len(values)))
    line = []
    chunk = []
    for v in values:
        line.append(str(int(v)))
        if len(line) == 16:
            chunk.append("    " + ", ".join(line) + ",")
            line = []
    if line:
        chunk.append("    " + ", ".join(line) + ",")
    out.append("\n".join(chunk))
    out.append("\n};\n")


def _build_soundfile(out, prefix, parts):
    """Emit the C++ data for one soundfile made of 'parts' (each a parsed
    WAV dict). Returns the C++ identifier of the generated Soundfile.

    Arrays are sized to the actual number of parts (files in the URL), not the
    generic MAX_SOUNDFILE_PARTS=256. The Faust soundfile part index is expected
    to stay within [0, nparts-1] (the number of files actually loaded)."""
    cur_chan = max((p['channels'] for p in parts), default=1)
    cur_chan = max(cur_chan, 1)
    nparts = len(parts)

    # One concatenated buffer per channel (the QSPI data). No empty-part
    # padding: every part is a real file, so reads (clamped by the DSP to
    # [0, fLength[p]-1]) always stay inside the part's own region.
    for c in range(cur_chan):
        buf = []
        for p in parts:
            if c < p['channels']:
                buf.extend(p['data'][c])
            else:
                buf.extend([0.0] * p['frames'])
        _emit_float_array(out, "%s_ch%d" % (prefix, c), buf)

    # fBuffers : cur_chan distinct pointers, then aliased up to MAX_CHAN so any
    # requested channel index < MAX_CHAN resolves (mirrors Soundfile::shareBuffers).
    out.append("static const float* const %s_buffers[%d] = {\n" % (prefix, MAX_CHAN))
    line = []
    chunk = []
    for c in range(MAX_CHAN):
        line.append("%s_ch%d" % (prefix, c % cur_chan))
        if len(line) == 4:
            chunk.append("    " + ", ".join(line) + ",")
            line = []
    if line:
        chunk.append("    " + ", ".join(line) + ",")
    out.append("\n".join(chunk))
    out.append("\n};\n")

    # fLength / fSR / fOffset : one entry per (real) part.
    lengths = []
    srs = []
    offsets = []
    offset = 0
    for p in parts:
        lengths.append(p['frames'])
        srs.append(p['sample_rate'])
        offsets.append(offset)
        offset += p['frames']

    _emit_int_array(out, "%s_length" % prefix, lengths)
    _emit_int_array(out, "%s_sr" % prefix, srs)
    _emit_int_array(out, "%s_offset" % prefix, offsets)

    out.append(
        "static Soundfile %s = { (void*)%s_buffers, %s_length, %s_sr, %s_offset, %d, %d, false };\n\n"
        % (prefix, prefix, prefix, prefix, prefix, cur_chan, nparts)
    )
    return prefix


def _emit_empty_soundfile(out, nparts):
    """Emit the 'defaultsound' empty soundfile (1 channel, all parts silent).
    'nparts' is sized to the max part count of the real soundfiles so the
    fallback can stand in for any of them. All parts share one silent block."""
    nparts = max(nparts, 1)
    out.append("static const float sf_empty_zero[%d] = { 0.0f };\n" % BUFFER_SIZE)
    out.append("static const float* const sf_empty_buffers[%d] = {\n" % MAX_CHAN)
    out.append("    " + ", ".join(["sf_empty_zero"] * MAX_CHAN) + "\n};\n")
    _emit_int_array(out, "sf_empty_length", [BUFFER_SIZE] * nparts)
    _emit_int_array(out, "sf_empty_sr", [SAMPLE_RATE] * nparts)
    _emit_int_array(out, "sf_empty_offset", [0] * nparts)
    out.append(
        "static Soundfile sf_empty = { (void*)sf_empty_buffers, "
        "sf_empty_length, sf_empty_sr, sf_empty_offset, 1, 0, false };\n"
    )
    out.append("static Soundfile* defaultsound = &sf_empty;\n\n")


def generate_header(soundfiles, search_dirs, out_path):
    """Resolve, parse and inline all referenced WAV files into 'out_path'.
    'soundfiles' is a list of (label, url). Returns True if at least one
    soundfile was generated. Exits the process on a missing/invalid file."""
    out = []
    out.append("// Generated by faust2daisy (daisy_soundfile_gen.py) - do not edit.\n")
    out.append("#ifndef __daisy_soundfile__\n#define __daisy_soundfile__\n\n")
    out.append("#include <cstdint>\n#include <cstring>\n\n")
    out.append("#ifndef FAUSTFLOAT\n#define FAUSTFLOAT float\n#endif\n\n")
    out.append(
        "// Sample data is emitted as 'const' (read-only .rodata). Built with\n"
        "// faust2daisy -qspi, it is placed in QSPI flash and read memory-mapped,\n"
        "// never copied to RAM. Soundfiles too large for the 128 KB internal\n"
        "// flash therefore require the -qspi build mode.\n\n"
    )
    out.append("#define MAX_SOUNDFILE_PARTS %d\n" % MAX_SOUNDFILE_PARTS)
    out.append("#define MAX_CHAN %d\n" % MAX_CHAN)
    out.append("#define BUFFER_SIZE %d\n" % BUFFER_SIZE)
    out.append("#define SAMPLE_RATE %d\n\n" % SAMPLE_RATE)
    out.append(
        "// Same field layout as architecture/faust/gui/Soundfile.h.\n"
        "struct Soundfile {\n"
        "    void* fBuffers;  // float** : MAX_CHAN non-interleaved buffers\n"
        "    int* fLength;    // frames of each part\n"
        "    int* fSR;        // sample rate of each part\n"
        "    int* fOffset;    // frame offset of each part in the buffer\n"
        "    int fChannels;   // max channels of all parts\n"
        "    int fParts;      // number of loaded parts\n"
        "    bool fIsDouble;  // sample format (always float here)\n"
        "} __attribute__((packed));\n\n"
    )

    # Resolve and parse all files first, so the empty soundfile can be sized to
    # the largest part count (and we fail fast before emitting anything).
    parsed = []  # (index, url, parts)
    for index, (label, url) in enumerate(soundfiles):
        names = parse_url(url)
        parts = []
        for name in names:
            resolved = resolve_file(name, search_dirs)
            if resolved is None:
                eprint("faust2daisy soundfile error : file '%s' (from soundfile '%s') "
                       "not found in: %s" % (name, label, ", ".join(search_dirs)))
                sys.exit(1)
            try:
                parts.append(parse_wav(resolved))
            except WavError as e:
                eprint("faust2daisy soundfile error : %s" % e)
                sys.exit(1)
        parsed.append((index, url, parts))

    max_parts = max((len(p) for _, _, p in parsed), default=1)
    _emit_empty_soundfile(out, max_parts)

    entries = []  # (url, identifier)
    for index, url, parts in parsed:
        if not parts:
            # Empty URL : map to the default (silent) soundfile.
            entries.append((url, "sf_empty"))
            continue
        prefix = "sf%d" % index
        ident = _build_soundfile(out, prefix, parts)
        entries.append((url, ident))

    # Lookup used by DaisyControlUI::addSoundfile.
    out.append("Soundfile* daisy_lookup_soundfile(const char* url)\n{\n")
    for url, ident in entries:
        escaped = url.replace('\\', '\\\\').replace('"', '\\"')
        out.append('    if (std::strcmp(url, "%s") == 0) return &%s;\n' % (escaped, ident))
    out.append("    return defaultsound;\n}\n\n")

    out.append("#endif // __daisy_soundfile__\n")

    with open(out_path, 'w') as f:
        f.write("".join(out))

    return len(entries) > 0

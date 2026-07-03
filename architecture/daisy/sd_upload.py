#!/usr/bin/env python3
# ---------------------------------------------------------------------
# faust2daisy : host-side soundfile uploader
#
# Streams the WAV files referenced by a Faust DSP to the Daisy SD card, into a
# "/soundfiles" folder, talking to the sd_uploader firmware over USB-serial
# (CDC). Standard library only (no pyserial dependency): the serial port is
# driven directly through termios in raw mode.
#
# Usage:
#   sd_upload.py <dsp.json> <search_dir>[,<search_dir>...] [--port /dev/ttyACMx] [--no-clear]
# ---------------------------------------------------------------------

import os
import sys
import glob
import time
import select
import termios

# Allow importing the sibling module regardless of the invocation cwd.
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import daisy_soundfile_gen as sfgen

CHUNK = 32768            # must match CHUNK in sd_uploader.cpp
ACK_TIMEOUT = 15.0       # seconds to wait for a device reply


def eprint(*args):
    print(*args, file=sys.stderr)


def fail(msg):
    eprint("faust2daisy sd-upload error : %s" % msg)
    sys.exit(1)


# ---------------------------------------------------------------------
# Serial port (raw termios, no pyserial)
# ---------------------------------------------------------------------

def find_port():
    for pattern in ("/dev/ttyACM*", "/dev/cu.usbmodem*", "/dev/tty.usbmodem*"):
        matches = sorted(glob.glob(pattern))
        if matches:
            return matches[0]
    return None


def open_port(dev):
    fd = os.open(dev, os.O_RDWR | os.O_NOCTTY)
    attrs = termios.tcgetattr(fd)
    iflag, oflag, cflag, lflag, ispeed, ospeed, cc = attrs
    # Raw mode: no input/output processing, no echo, no canonical line handling.
    iflag = 0
    oflag = 0
    lflag = 0
    cflag = (cflag | termios.CLOCAL | termios.CREAD | termios.CS8) & ~termios.CSIZE | termios.CS8
    cc = list(cc)
    cc[termios.VMIN] = 0
    cc[termios.VTIME] = 0
    termios.tcsetattr(fd, termios.TCSANOW, [iflag, oflag, cflag, lflag, ispeed, ospeed, cc])
    termios.tcflush(fd, termios.TCIOFLUSH)
    return fd


def write_all(fd, data):
    mv = memoryview(data)
    while mv:
        n = os.write(fd, mv[:65536])
        if n <= 0:
            fail("serial write failed")
        mv = mv[n:]


def read_line(fd, timeout=ACK_TIMEOUT):
    buf = bytearray()
    deadline = time.time() + timeout
    while time.time() < deadline:
        remaining = deadline - time.time()
        r, _, _ = select.select([fd], [], [], max(0.0, remaining))
        if not r:
            continue
        b = os.read(fd, 1)
        if not b:
            continue
        if b == b'\n':
            return buf.decode(errors='replace').strip()
        if b != b'\r':
            buf += b
    return None


def expect_ok(fd, context):
    line = read_line(fd)
    if line is None:
        fail("timed out waiting for device reply (%s)" % context)
    if not line.startswith("OK"):
        fail("device reported '%s' (%s)" % (line, context))


# ---------------------------------------------------------------------
# Resolve the WAV files referenced by the DSP
# ---------------------------------------------------------------------

def collect_files(json_path, search_dirs):
    with open(json_path) as f:
        import json
        layout = json.load(f)
    soundfiles = sfgen.scan_soundfiles(layout)
    files = []
    seen = set()
    for label, url in soundfiles:
        for name in sfgen.parse_url(url):
            resolved = sfgen.resolve_file(name, search_dirs)
            if resolved is None:
                fail("file '%s' (from soundfile '%s') not found in: %s"
                     % (name, label, ", ".join(search_dirs)))
            key = os.path.basename(resolved)
            if key not in seen:
                seen.add(key)
                files.append((key, resolved))
    return files


def main():
    args = sys.argv[1:]
    port = None
    do_clear = True
    positional = []
    i = 0
    while i < len(args):
        a = args[i]
        if a == "--port":
            i += 1
            port = args[i]
        elif a == "--no-clear":
            do_clear = False
        else:
            positional.append(a)
        i += 1

    if len(positional) < 2:
        fail("usage: sd_upload.py <dsp.json> <search_dir>[,<dir>...] [--port DEV] [--no-clear]")

    json_path = positional[0]
    search_dirs = positional[1].split(",")

    files = collect_files(json_path, search_dirs)
    if not files:
        print("No soundfiles referenced by the DSP, nothing to upload.")
        return

    if port is None:
        port = find_port()
        if port is None:
            fail("no serial port found (looked for /dev/ttyACM*, /dev/cu.usbmodem*). "
                 "Is the SD uploader firmware running and the Daisy connected?")

    print("Uploading %d soundfile(s) to /soundfiles via %s" % (len(files), port))
    fd = open_port(port)
    try:
        # Handshake with retries (the device may still be re-enumerating right
        # after the uploader firmware was flashed). Also confirms the SD mount.
        acked = False
        for _ in range(10):
            termios.tcflush(fd, termios.TCIFLUSH)
            write_all(fd, b"PING\n")
            line = read_line(fd, timeout=1.5)
            if line is not None:
                if not line.startswith("OK"):
                    fail("device reported '%s' (ping / SD mount). "
                         "Is an SD card inserted?" % line)
                acked = True
                break
        if not acked:
            fail("no response from device on %s. Is the SD uploader firmware "
                 "running?" % port)

        if do_clear:
            write_all(fd, b"CLEAR\n")
            expect_ok(fd, "clear /soundfiles")
            print("  cleared /soundfiles")

        for name, path in files:
            data = open(path, "rb").read()
            write_all(fd, ("FILE %d %s\n" % (len(data), name)).encode())
            expect_ok(fd, "open %s" % name)
            offset = 0
            while offset < len(data):
                chunk = data[offset:offset + CHUNK]
                write_all(fd, chunk)
                expect_ok(fd, "%s @%d" % (name, offset))
                offset += len(chunk)
            print("  uploaded %s (%d bytes)" % (name, len(data)))

        write_all(fd, b"DONE\n")
        expect_ok(fd, "done")
    finally:
        os.close(fd)
    print("SD upload complete.")


if __name__ == "__main__":
    main()

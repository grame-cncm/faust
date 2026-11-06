#!/bin/bash
# Signs the content of a macOS Faust package (Faust-<version>-<arch>.dmg or
# faustgen-<version>-<arch>.dmg, made by 'make release' or by the CI) with a Developer ID
# and the hardened runtime, rebuilds and signs the dmg, then notarizes and staples it when
# a notarytool keychain profile is given. Without that, macOS 15 and later (Gatekeeper)
# refuses the downloaded executables, libraries and the faustgen~ Max external.
#
# usage: macos-sign-dmg.sh <input.dmg> <output.dmg> <identity> [notarytool profile]
#   identity : e.g. "Developer ID Application: GRAME (XN9RP996NW)" (in the keychain)
#   profile  : created once with
#              xcrun notarytool store-credentials <profile> --apple-id <id> --team-id <team>
#              (the password is asked and kept in the keychain), or with an App Store Connect
#              API key: --key <AuthKey.p8> --key-id <id> --issuer <uuid>
#
# What is signed, from the inside out:
#   - every Mach-O executable, dylib and loadable bundle binary (static .a archives are not code),
#     the executables of JIT_TOOLS with build/package/macos-jit.entitlements (LLVM JIT),
#   - then the bundles (.mxo, .app, .framework, .bundle...), the deepest first; with a profile,
#     the bundles are notarized (zip) and stapled before the dmg is made, so that a copy taken
#     out of the dmg (faustgen~.mxo in the Max packages) also passes Gatekeeper offline.
# The notarization logs are written beside the output: <output.dmg>.notary-log.json (and
# <output.dmg>.bundles.notary-log.json).
# Environment:
#   JIT_TOOLS : executables that get the JIT entitlements (default: "faustbench-llvm dynamic-faust")

set -euo pipefail

if [ $# -lt 3 ]; then
    echo "usage: $0 <input.dmg> <output.dmg> <identity> [notarytool profile]" >&2
    exit 2
fi
IN=$1
OUT=$2
IDENTITY=$3
PROFILE=${4:-}
ENTITLEMENTS="$(cd "$(dirname "$0")" && pwd)/package/macos-jit.entitlements"
JIT_TOOLS=${JIT_TOOLS:-"faustbench-llvm dynamic-faust"}

[ -f "$IN" ] || { echo "no such file: $IN" >&2; exit 1; }
[ -f "$ENTITLEMENTS" ] || { echo "no such file: $ENTITLEMENTS" >&2; exit 1; }
case "$OUT" in /*) ;; *) OUT="$PWD/$OUT" ;; esac

WORK=$(mktemp -d -t faust-sign)
trap 'hdiutil detach -quiet -force "$WORK/in" 2>/dev/null || true; rm -rf "$WORK"' EXIT

# copy the content of the input dmg, keep its volume name
hdiutil attach -nobrowse -noautoopen -readonly -mountpoint "$WORK/in" "$IN" > /dev/null
VOLNAME=$(diskutil info -plist "$WORK/in" | plutil -extract VolumeName raw -)
ROOT="$WORK/root"
ditto "$WORK/in" "$ROOT"
hdiutil detach -quiet "$WORK/in"
echo "Volume: $VOLNAME"

is_macho() {
    # executables, dylibs and bundles, thin or universal; not static archives
    file -b "$1" | grep -qE 'Mach-O.*(executable|shared library|bundle)'
}
is_jit_tool() {
    local name
    name=$(basename "$1")
    for t in $JIT_TOOLS; do [ "$name" = "$t" ] && return 0; done
    return 1
}
by_depth() {
    # deepest paths first
    awk -F/ '{ print NF "\t" $0 }' | sort -rn | cut -f2-
}

SIGN=(codesign --force --timestamp --options runtime --prefix com.grame. --sign "$IDENTITY")
BUNDLES='.*\.(mxo|app|framework|bundle|plugin|component|vst|vst3|appex)$'

# 1. the Mach-O files (symbolic links are not followed: find -type f)
find "$ROOT" -type f | by_depth > "$WORK/files"
NSIGNED=0
while IFS= read -r f; do
    is_macho "$f" || continue
    if is_jit_tool "$f" && [ -x "$f" ]; then
        echo "sign (JIT entitlements): ${f#$ROOT/}"
        "${SIGN[@]}" --entitlements "$ENTITLEMENTS" "$f"
    else
        echo "sign: ${f#$ROOT/}"
        "${SIGN[@]}" "$f"
    fi
    NSIGNED=$((NSIGNED + 1))
done < "$WORK/files"

# 2. the bundles, the inner ones first (signing a bundle seals its resources and signs
#    its main executable again)
find -E "$ROOT" -type d -regex "$BUNDLES" | by_depth > "$WORK/bundles"
while IFS= read -r b; do
    echo "sign bundle: ${b#$ROOT/}"
    "${SIGN[@]}" "$b"
    NSIGNED=$((NSIGNED + 1))
done < "$WORK/bundles"
[ "$NSIGNED" -gt 0 ] || { echo "nothing to sign in $IN" >&2; exit 1; }

# 3. check every signature, and the entitlements of the JIT tools
while IFS= read -r f; do
    is_macho "$f" || continue
    codesign --verify --strict "$f"
    if is_jit_tool "$f" && [ -x "$f" ]; then
        codesign -d --entitlements - "$f" 2>/dev/null | grep -q allow-unsigned-executable-memory
    fi
done < "$WORK/files"
while IFS= read -r b; do
    codesign --verify --deep --strict --verbose=2 "$b"
done < "$WORK/bundles"
echo "$NSIGNED signatures checked"

# notarize <file> <log.json> : submit to the notary service, wait (again after a network
# error), keep the log (issues, warnings too) and fail unless the status is Accepted
notarize() {
    local file=$1 log=$2 id status i
    xcrun notarytool submit "$file" --keychain-profile "$PROFILE" --wait 2>&1 | tee "$WORK/notary.txt" || true
    id=$(awk '$1 == "id:" { print $2; exit }' "$WORK/notary.txt")
    [ -n "$id" ] || { echo "notarytool submit $file failed" >&2; return 1; }
    status=$(awk '$1 == "status:" { s = $2 } END { print s }' "$WORK/notary.txt")
    for i in 1 2 3 4 5; do
        [ -n "$status" ] && [ "$status" != "In" ] && break
        echo "waiting again for submission $id (attempt $i)" >&2
        sleep 30
        xcrun notarytool wait "$id" --keychain-profile "$PROFILE" 2>&1 | tee "$WORK/notary.txt" || true
        status=$(awk '$1 == "status:" { s = $2 } END { print s }' "$WORK/notary.txt")
    done
    xcrun notarytool log "$id" --keychain-profile "$PROFILE" "$log" > /dev/null || true
    NOTARY_IDS="$NOTARY_IDS $(basename "$file"):$id"
    if [ "$status" != "Accepted" ]; then
        echo "notarization of $file failed (status: ${status:-unknown}, id: $id), see $log" >&2
        return 1
    fi
}
NOTARY_IDS=""

# 4. bundles (faustgen~.mxo...): notarize them first and staple them, so that the copies that
#    users put elsewhere (the Max packages folder) pass the Gatekeeper check without network
if [ -n "$PROFILE" ] && [ -s "$WORK/bundles" ]; then
    mkdir "$WORK/zip"
    while IFS= read -r b; do
        ditto "$b" "$WORK/zip/$(basename "$b")"
    done < "$WORK/bundles"
    ditto -c -k --keepParent "$WORK/zip" "$WORK/bundles.zip"
    notarize "$WORK/bundles.zip" "$OUT.bundles.notary-log.json"
    while IFS= read -r b; do
        xcrun stapler staple "$b"
        codesign --verify --deep --strict "$b"
    done < "$WORK/bundles"
fi

# 5. new dmg, signed (hdiutil fails now and then with 'Resource busy': try again)
rm -f "$OUT"
for i in 1 2 3 4 5 6 7 8 9 10; do
    hdiutil create "$OUT" -volname "$VOLNAME" -fs HFS+ -srcfolder "$ROOT" -format UDBZ -ov -quiet && break
    echo "hdiutil create failed (attempt $i), retrying" >&2
    sleep 5
done
[ -f "$OUT" ] || { echo "hdiutil create $OUT failed" >&2; exit 1; }
codesign --force --timestamp --sign "$IDENTITY" "$OUT"
codesign --verify --strict --verbose=2 "$OUT"

# 6. notarize and staple the dmg
if [ -n "$PROFILE" ]; then
    notarize "$OUT" "$OUT.notary-log.json"
    xcrun stapler staple "$OUT"
    xcrun stapler validate "$OUT"
    spctl -a -t open --context context:primary-signature -vv "$OUT"
    echo "Notarized: $OUT (submissions:$NOTARY_IDS)"
else
    echo "not notarized (no notarytool profile given)"
fi
echo "Signed: $OUT"

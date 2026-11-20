/************************** BEGIN RemoteHost.h *****************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __RemoteHost__
#define __RemoteHost__

/*
 The host side of the remote control protocol of faustwasm (protocol v1),
 in C++: a phone running faustwasm's remote control (a PWA) drives a Faust
 DSP through it. This file has no network and no Faust UI in it, so that it
 can be tested alone: RemoteUI.h connects it to a DSP and to the relay of
 faust-remote-server.

 It is a port of `src/remote/protocol.ts` and `src/remote/FaustRemoteHost.ts`
 of faustwasm (https://github.com/grame-cncm/faustwasm), which stay the
 reference: the same messages, the same validation in the same order, the
 same rules. A change to either side of the protocol has to be made on both;
 the conformance test of faustwasm (`test/cli/remote-native.test.mjs`) plays
 the same sessions against both hosts.

 Phase 1 of the plan: the `shared` policy, the `shared` sensor policy, no
 playout delay. What it does:

 - accepts remote controls with the room's token, at most `maxClients`;
 - applies their writes, held to each control's range, refusing controls
   marked `[remote:off]` (the real value is sent back);
 - passes their accelerometer and gyroscope readings to the DSP's own
   `[acc:]`/`[gyr:]` mappings, and their MIDI channel messages to it;
 - sends back bargraphs (`out`), parameter changes made elsewhere (`sync`,
   never a writer's own echo while it may still be moving the control), the
   number of active voices, and answers pings;
 - when a remote control goes, releases the buttons and the notes it held,
   so that a lost phone never leaves a note sounding.

 Transport: the relay's framing, as `acceptRelayed` in `src/remote/relay.ts`
 reads it. Each message from the relay is a remote control's relay id, a
 newline, then `c` or `s` (its channel) and the message, or a lone `!` when
 that remote control is gone; the host answers the same way.

 Threads: none of its own. Everything (`receive`, `tick`, `close`) is to be
 called from one thread.
*/

#include <stdint.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <functional>
#include <sstream>
#include <locale>
#include <chrono>
#include <algorithm>

#include "faust/gui/RemoteSocket.h"

// ------------------------------------------------------------------- JSON

/**
 * A JSON value, as much of it as the protocol's messages need. Numbers are
 * doubles, as in JavaScript; in objects, the last of two equal keys wins, as
 * with JSON.parse.
 */
struct RemoteJSON {

    enum Kind { kNull, kBool, kNumber, kString, kArray, kObject };

    Kind fKind;
    bool fBool;
    double fNumber;
    std::string fString;
    std::vector<RemoteJSON> fArray;
    std::vector<std::pair<std::string, RemoteJSON> > fObject;

    RemoteJSON():fKind(kNull), fBool(false), fNumber(0) {}

    const RemoteJSON* get(const std::string& key) const
    {
        for (size_t i = fObject.size(); i > 0; i--) {
            if (fObject[i - 1].first == key) return &fObject[i - 1].second;
        }
        return nullptr;
    }

    /** Parse a whole text; false if it is not JSON. */
    static bool parse(const std::string& text, RemoteJSON& value)
    {
        const char* p = text.c_str();
        const char* end = p + text.size();
        if (!parseValue(p, end, value, 0)) return false;
        skip(p, end);
        return p == end;
    }

    // ---- writing

    /** A string as a JSON literal: quotes, backslashes and control characters escaped, UTF-8 kept. */
    static std::string quote(const std::string& text)
    {
        std::string res = "\"";
        for (unsigned char c : text) {
            switch (c) {
                case '"': res += "\\\""; break;
                case '\\': res += "\\\\"; break;
                case '\b': res += "\\b"; break;
                case '\f': res += "\\f"; break;
                case '\n': res += "\\n"; break;
                case '\r': res += "\\r"; break;
                case '\t': res += "\\t"; break;
                default:
                    if (c < 0x20) {
                        static const char* digits = "0123456789abcdef";
                        res += "\\u00";
                        res.push_back(digits[c >> 4]);
                        res.push_back(digits[c & 15]);
                    } else {
                        res.push_back(char(c));
                    }
            }
        }
        return res + "\"";
    }

    /**
     * A number as JSON.stringify writes it: the shortest text that reads
     * back as the same double (as the same float, with `asFloat`, for
     * values that live in float zones: 0.1f is then written 0.1, as the DSP
     * declared it, not 0.10000000149011612). Never locale dependent: a Qt
     * application may have set LC_NUMERIC to a decimal comma.
     */
    static std::string number(double value, bool asFloat = false)
    {
        if (!std::isfinite(value)) return "null";
        if (value == 0) return "0";
        std::string sign = value < 0 ? "-" : "";
        double magnitude = fabs(value);
        // The fewest significant digits that read back as the same value
        std::string digits;
        int exponent = 0;
        for (int precision = 1; precision <= 17; precision++) {
            std::ostringstream out;
            out.imbue(std::locale::classic());
            out << std::scientific;
            out.precision(precision - 1);
            out << magnitude;
            std::string text = out.str();
            double back = read(text);
            if (precision == 17 || (asFloat ? (float(back) == float(magnitude)) : (back == magnitude))) {
                size_t e = text.find('e');
                exponent = atoi(text.c_str() + e + 1);
                for (size_t i = 0; i < e; i++) {
                    if (text[i] != '.') digits.push_back(text[i]);
                }
                break;
            }
        }
        while (digits.size() > 1 && digits[digits.size() - 1] == '0') digits.erase(digits.size() - 1);
        // Laid out as Number.prototype.toString does
        int k = int(digits.size());
        int n = exponent + 1;
        if (k <= n && n <= 21) return sign + digits + std::string(size_t(n - k), '0');
        if (0 < n && n <= 21) return sign + digits.substr(0, size_t(n)) + "." + digits.substr(size_t(n));
        if (-6 < n && n <= 0) return sign + "0." + std::string(size_t(-n), '0') + digits;
        std::string mantissa = digits.substr(0, 1) + (k > 1 ? "." + digits.substr(1) : "");
        return sign + mantissa + "e" + (n - 1 >= 0 ? "+" : "-") + std::to_string(abs(n - 1));
    }

    static double read(const std::string& text)
    {
        std::istringstream in(text);
        in.imbue(std::locale::classic());
        double value = 0;
        in >> value;
        return value;
    }

  private:

    static void skip(const char*& p, const char* end)
    {
        while (p < end && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')) p++;
    }

    static void appendUTF8(std::string& out, uint32_t code)
    {
        if (code < 0x80) {
            out.push_back(char(code));
        } else if (code < 0x800) {
            out.push_back(char(0xC0 | (code >> 6)));
            out.push_back(char(0x80 | (code & 0x3F)));
        } else if (code < 0x10000) {
            out.push_back(char(0xE0 | (code >> 12)));
            out.push_back(char(0x80 | ((code >> 6) & 0x3F)));
            out.push_back(char(0x80 | (code & 0x3F)));
        } else {
            out.push_back(char(0xF0 | (code >> 18)));
            out.push_back(char(0x80 | ((code >> 12) & 0x3F)));
            out.push_back(char(0x80 | ((code >> 6) & 0x3F)));
            out.push_back(char(0x80 | (code & 0x3F)));
        }
    }

    static bool hex4(const char*& p, const char* end, uint32_t& code)
    {
        if (end - p < 4) return false;
        code = 0;
        for (int i = 0; i < 4; i++, p++) {
            char c = *p;
            code <<= 4;
            if (c >= '0' && c <= '9') code |= uint32_t(c - '0');
            else if (c >= 'a' && c <= 'f') code |= uint32_t(c - 'a' + 10);
            else if (c >= 'A' && c <= 'F') code |= uint32_t(c - 'A' + 10);
            else return false;
        }
        return true;
    }

    static bool parseString(const char*& p, const char* end, std::string& out)
    {
        if (p >= end || *p != '"') return false;
        p++;
        while (p < end) {
            unsigned char c = (unsigned char)*p++;
            if (c == '"') return true;
            if (c < 0x20) return false;
            if (c != '\\') {
                out.push_back(char(c));
                continue;
            }
            if (p >= end) return false;
            char e = *p++;
            switch (e) {
                case '"': out.push_back('"'); break;
                case '\\': out.push_back('\\'); break;
                case '/': out.push_back('/'); break;
                case 'b': out.push_back('\b'); break;
                case 'f': out.push_back('\f'); break;
                case 'n': out.push_back('\n'); break;
                case 'r': out.push_back('\r'); break;
                case 't': out.push_back('\t'); break;
                case 'u': {
                    uint32_t code;
                    if (!hex4(p, end, code)) return false;
                    if (code >= 0xD800 && code < 0xDC00) {
                        // A surrogate pair; a lone half becomes U+FFFD, as a browser decodes it
                        uint32_t low;
                        const char* q = p;
                        if (end - q >= 6 && q[0] == '\\' && q[1] == 'u' && (q += 2, hex4(q, end, low)) && low >= 0xDC00 && low < 0xE000) {
                            p = q;
                            code = 0x10000 + ((code - 0xD800) << 10) + (low - 0xDC00);
                        } else {
                            code = 0xFFFD;
                        }
                    } else if (code >= 0xDC00 && code < 0xE000) {
                        code = 0xFFFD;
                    }
                    appendUTF8(out, code);
                    break;
                }
                default:
                    return false;
            }
        }
        return false;
    }

    // The grammar of JSON numbers, strictly; the value read without the locale
    static bool parseNumber(const char*& p, const char* end, double& value)
    {
        const char* start = p;
        if (p < end && *p == '-') p++;
        if (p >= end) return false;
        if (*p == '0') {
            p++;
        } else if (*p >= '1' && *p <= '9') {
            while (p < end && isdigit((unsigned char)*p)) p++;
        } else {
            return false;
        }
        if (p < end && *p == '.') {
            p++;
            if (p >= end || !isdigit((unsigned char)*p)) return false;
            while (p < end && isdigit((unsigned char)*p)) p++;
        }
        bool negativeExponent = false;
        if (p < end && (*p == 'e' || *p == 'E')) {
            p++;
            if (p < end && (*p == '+' || *p == '-')) negativeExponent = (*p++ == '-');
            if (p >= end || !isdigit((unsigned char)*p)) return false;
            while (p < end && isdigit((unsigned char)*p)) p++;
        }
        std::istringstream in(std::string(start, p));
        in.imbue(std::locale::classic());
        in >> value;
        if (in.fail()) {
            // Out of range: JSON.parse gives Infinity, or 0 for an underflow
            value = negativeExponent ? 0.0 : (*start == '-' ? -INFINITY : INFINITY);
        }
        return true;
    }

    static bool parseLiteral(const char*& p, const char* end, const char* word)
    {
        size_t n = strlen(word);
        if (size_t(end - p) < n || strncmp(p, word, n) != 0) return false;
        p += n;
        return true;
    }

    static bool parseValue(const char*& p, const char* end, RemoteJSON& value, int depth)
    {
        if (depth > 64) return false;
        skip(p, end);
        if (p >= end) return false;
        switch (*p) {
            case '{': {
                p++;
                value.fKind = kObject;
                skip(p, end);
                if (p < end && *p == '}') {
                    p++;
                    return true;
                }
                while (true) {
                    skip(p, end);
                    std::string key;
                    if (!parseString(p, end, key)) return false;
                    skip(p, end);
                    if (p >= end || *p != ':') return false;
                    p++;
                    RemoteJSON item;
                    if (!parseValue(p, end, item, depth + 1)) return false;
                    value.fObject.push_back(std::make_pair(key, item));
                    skip(p, end);
                    if (p < end && *p == ',') {
                        p++;
                        continue;
                    }
                    if (p < end && *p == '}') {
                        p++;
                        return true;
                    }
                    return false;
                }
            }
            case '[': {
                p++;
                value.fKind = kArray;
                skip(p, end);
                if (p < end && *p == ']') {
                    p++;
                    return true;
                }
                while (true) {
                    RemoteJSON item;
                    if (!parseValue(p, end, item, depth + 1)) return false;
                    value.fArray.push_back(item);
                    skip(p, end);
                    if (p < end && *p == ',') {
                        p++;
                        continue;
                    }
                    if (p < end && *p == ']') {
                        p++;
                        return true;
                    }
                    return false;
                }
            }
            case '"':
                value.fKind = kString;
                return parseString(p, end, value.fString);
            case 't':
                value.fKind = kBool;
                value.fBool = true;
                return parseLiteral(p, end, "true");
            case 'f':
                value.fKind = kBool;
                value.fBool = false;
                return parseLiteral(p, end, "false");
            case 'n':
                value.fKind = kNull;
                return parseLiteral(p, end, "null");
            default:
                value.fKind = kNumber;
                return parseNumber(p, end, value.fNumber);
        }
    }
};

// --------------------------------------------------------------- messages

/**
 * A message from a remote control, checked for shape as `parseClientMessage`
 * of protocol.ts checks it: fields present and of the right kind, numbers
 * finite. Ranges, and whether a control may be written, are the host's.
 */
struct RemoteClientMessage {

    enum Type { kHello, kParam, kAcc, kGyr, kMidi, kPing, kBye };

    Type fType;
    // hello
    double fVersion;
    std::string fId, fToken, fMode, fHash;
    bool fHasToken, fHasHash;
    // param
    double fIndex, fValue;
    // param, acc, gyr
    bool fHasSeq;
    double fSeq;
    // param, acc, gyr, midi
    bool fHasTime;
    double fTime;
    // acc, gyr
    double fAxes[3];
    bool fInvert;
    // midi
    std::vector<int> fData;
    // ping
    double fS, fT0;
    // bye
    bool fHasReason;
    std::string fReason;

    RemoteClientMessage()
    :fType(kBye), fVersion(0), fHasToken(false), fHasHash(false), fIndex(0), fValue(0),
    fHasSeq(false), fSeq(0), fHasTime(false), fTime(0), fInvert(false), fS(0), fT0(0), fHasReason(false)
    {
        fAxes[0] = fAxes[1] = fAxes[2] = 0;
    }

    static bool isNumber(const RemoteJSON* v) { return v && v->fKind == RemoteJSON::kNumber && std::isfinite(v->fNumber); }
    static bool isIndex(const RemoteJSON* v) { return isNumber(v) && v->fNumber >= 0 && floor(v->fNumber) == v->fNumber; }
    static bool isString(const RemoteJSON* v) { return v && v->fKind == RemoteJSON::kString; }

    static bool number(const RemoteJSON& m, const char* key, double& out)
    {
        const RemoteJSON* v = m.get(key);
        if (!isNumber(v)) return false;
        out = v->fNumber;
        return true;
    }

    // An optional field: absent, or of its kind
    static bool optionalIndex(const RemoteJSON& m, const char* key, bool& has, double& out)
    {
        const RemoteJSON* v = m.get(key);
        has = (v != nullptr);
        if (!has) return true;
        if (!isIndex(v)) return false;
        out = v->fNumber;
        return true;
    }

    static bool optionalNumber(const RemoteJSON& m, const char* key, bool& has, double& out)
    {
        const RemoteJSON* v = m.get(key);
        has = (v != nullptr);
        if (!has) return true;
        if (!isNumber(v)) return false;
        out = v->fNumber;
        return true;
    }

    static bool optionalString(const RemoteJSON& m, const char* key, bool& has, std::string& out)
    {
        const RemoteJSON* v = m.get(key);
        has = (v != nullptr);
        if (!has) return true;
        if (!isString(v)) return false;
        out = v->fString;
        return true;
    }

    /**
     * Whether bytes are one MIDI channel voice message: note off and on,
     * polyphonic pressure, control change, program change, channel pressure
     * or pitch bend. System messages, SysEx included, are not.
     */
    static bool channelVoice(const RemoteJSON* v, std::vector<int>& data)
    {
        if (!v || v->fKind != RemoteJSON::kArray || v->fArray.empty()) return false;
        data.clear();
        for (const RemoteJSON& b : v->fArray) {
            if (!isIndex(&b)) return false;
            data.push_back(b.fNumber > 255 ? 256 : int(b.fNumber));
        }
        int status = data[0];
        if (status < 0x80 || status > 0xEF) return false;
        int kind = status & 0xF0;
        size_t length = (kind == 0xC0 || kind == 0xD0) ? 1 : 2;
        if (data.size() != length + 1) return false;
        for (size_t i = 1; i < data.size(); i++) {
            if (data[i] >= 0x80) return false;
        }
        return true;
    }

    /** A message from a remote control, or false if the text is not one. */
    static bool parse(const std::string& text, RemoteClientMessage& msg)
    {
        RemoteJSON m;
        if (!RemoteJSON::parse(text, m) || m.fKind != RemoteJSON::kObject) return false;
        const RemoteJSON* type = m.get("type");
        if (!isString(type)) return false;
        const std::string& t = type->fString;
        if (t == "hello") {
            msg.fType = kHello;
            const RemoteJSON* id = m.get("id");
            const RemoteJSON* mode = m.get("mode");
            if (!number(m, "v", msg.fVersion) || !isString(id)) return false;
            msg.fId = id->fString;
            if (!optionalString(m, "token", msg.fHasToken, msg.fToken)) return false;
            if (!isString(mode) || (mode->fString != "bi" && mode->fString != "uni")) return false;
            msg.fMode = mode->fString;
            return optionalString(m, "hash", msg.fHasHash, msg.fHash);
        } else if (t == "param") {
            msg.fType = kParam;
            const RemoteJSON* i = m.get("i");
            if (!isIndex(i)) return false;
            msg.fIndex = i->fNumber;
            return number(m, "value", msg.fValue)
                && optionalIndex(m, "seq", msg.fHasSeq, msg.fSeq)
                && optionalNumber(m, "time", msg.fHasTime, msg.fTime);
        } else if (t == "acc") {
            msg.fType = kAcc;
            const RemoteJSON* invert = m.get("invert");
            if (!number(m, "x", msg.fAxes[0]) || !number(m, "y", msg.fAxes[1]) || !number(m, "z", msg.fAxes[2])) return false;
            if (!invert || invert->fKind != RemoteJSON::kBool) return false;
            msg.fInvert = invert->fBool;
            return optionalIndex(m, "seq", msg.fHasSeq, msg.fSeq)
                && optionalNumber(m, "time", msg.fHasTime, msg.fTime);
        } else if (t == "gyr") {
            msg.fType = kGyr;
            if (!number(m, "alpha", msg.fAxes[0]) || !number(m, "beta", msg.fAxes[1]) || !number(m, "gamma", msg.fAxes[2])) return false;
            return optionalIndex(m, "seq", msg.fHasSeq, msg.fSeq)
                && optionalNumber(m, "time", msg.fHasTime, msg.fTime);
        } else if (t == "midi") {
            msg.fType = kMidi;
            return channelVoice(m.get("data"), msg.fData)
                && optionalNumber(m, "time", msg.fHasTime, msg.fTime);
        } else if (t == "ping") {
            msg.fType = kPing;
            return number(m, "s", msg.fS) && number(m, "t0", msg.fT0);
        } else if (t == "bye") {
            msg.fType = kBye;
            return optionalString(m, "reason", msg.fHasReason, msg.fReason);
        }
        return false;
    }
};

// ----------------------------------------------------------------- target

/** An input control, as the host sees it (the order of `getParams()`, that is of the UI). */
struct RemoteInput {
    std::string fAddress;
    bool fButton;           // a button: held while non-zero, released when its writer goes
    double fMin, fMax;      // the range writes are held to ([0, 1] for buttons and checkboxes)
    bool fRemoteOff;        // [remote:off]: remote controls follow it but cannot change it
    bool fAcc, fGyr;        // has [acc:] / [gyr:] metadata
};

/** An output control: a bargraph. */
struct RemoteOutput {
    std::string fAddress;
    double fMin, fMax;
};

/** What the host drives: in RemoteUI, the zones of a DSP. */
class RemoteTarget {

    public:

        virtual ~RemoteTarget() {}

        /** The DSP's JSON, sent to remote controls in `welcome`. */
        virtual std::string getRemoteJSON() = 0;
        virtual const std::vector<RemoteInput>& getRemoteInputs() = 0;
        virtual const std::vector<RemoteOutput>& getRemoteOutputs() = 0;
        virtual double getRemoteInput(int i) = 0;
        virtual void setRemoteInput(int i, double value) = 0;
        virtual double getRemoteOutput(int k) = 0;
        /** Whether the DSP maps the accelerometer, the gyroscope, to any control. */
        virtual bool hasRemoteAcc() = 0;
        virtual bool hasRemoteGyr() = 0;
        /** Through the DSP's own `[acc:]` / `[gyr:]` mappings, all at once (sign already corrected). */
        virtual void propagateRemoteAcc(double x, double y, double z) = 0;
        virtual void propagateRemoteGyr(double alpha, double beta, double gamma) = 0;
        /** One MIDI channel voice message. */
        virtual void remoteMidi(const std::vector<int>& data) = 0;
        /** Active voices of a polyphonic DSP; negative for a monophonic one. */
        virtual int getRemoteVoices() { return -1; }
        /** Whether values live in float zones (FAUSTFLOAT is float): they are then written as floats. */
        virtual bool remoteFloatValues() { return false; }
};

// ------------------------------------------------------------------- host

struct RemoteHostOptions {
    /** Required in `hello` when not empty. */
    std::string fToken;
    /** `uni` imposes the unidirectional mode on every remote control. */
    std::string fMode;
    int fMaxClients;
    /** Most bargraph and parameter updates per second to one remote control (and the tick rate). */
    double fOutputRate;
    /** Change below which a bargraph is not resent, as a fraction of its range. */
    double fOutputDeadband;
    /** Milliseconds without a message after which a remote control is dropped. */
    double fLivenessTimeout;
    /** Most messages per second accepted from one remote control. */
    double fMaxMessageRate;
    /** Milliseconds during which a write is not echoed to its writer. */
    double fEchoWindow;

    RemoteHostOptions()
    :fMode("bi"), fMaxClients(16), fOutputRate(30), fOutputDeadband(0.001),
    fLivenessTimeout(3000), fMaxMessageRate(200), fEchoWindow(500)
    {}
};

class RemoteHost {

    public:

        static const int kProtocolVersion = 1;
        /** What one relay message may carry (RELAY_MESSAGE_SIZE of relay.ts). */
        static const size_t kRelayMessageSize = 512 * 1024;

        typedef std::function<void(const std::string&)> Sender;
        typedef std::function<double()> Clock;

    private:

        struct Client {
            std::string fPeer;                  // its relay id
            std::string fId;                    // from hello: stable across reconnections
            std::string fMode;
            bool fOpen;
            bool fClosing;
            std::map<std::string, double> fSeqs;    // last sequence number applied, per key
            std::map<int, std::pair<double, double> > fWritten;  // input -> (value asked, when)
            std::set<int> fHeld;                // buttons it holds down
            std::set<int> fNotes;               // notes it holds, channel << 8 | pitch
            std::vector<double> fOutSent;       // bargraphs as it last received them
            double fLastMessageAt;
            double fWindowStart;
            double fWindowCount;
            Client():fOpen(false), fClosing(false), fLastMessageAt(0), fWindowStart(0), fWindowCount(0) {}
        };

        RemoteTarget* fTarget;
        RemoteHostOptions fOptions;
        Sender fSend;
        Clock fNow;
        std::string fSession;
        std::string fJSON;
        std::string fHash;                      // SHA-256 of the JSON, in hex, computed when first asked
        bool fRemoteAcc, fRemoteGyr;            // whether remote sensor readings may drive anything
        std::vector<double> fOutputThreshold;
        std::vector<double> fOutValues;
        std::vector<double> fSeen;              // inputs as last polled: a change is a `sync`
        int fVoices;
        std::vector<std::unique_ptr<Client> > fClients;     // in the order they came
        int fChunkId;
        bool fClosed;
        bool fRelayGone;                        // nothing can be sent until the relay is back

        static double steadyMs()
        {
            return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now().time_since_epoch()).count();
        }

        Client* find(const std::string& peer)
        {
            for (auto& c : fClients) {
                if (c->fPeer == peer) return c.get();
            }
            return nullptr;
        }

        std::vector<Client*> open()
        {
            std::vector<Client*> res;
            for (auto& c : fClients) {
                if (c->fOpen) res.push_back(c.get());
            }
            return res;
        }

        std::string num(double value) { return RemoteJSON::number(value); }
        std::string val(double value) { return RemoteJSON::number(std::isfinite(value) ? value : 0, fTarget->remoteFloatValues()); }

        void relay(Client* c, const std::string& payload) { fSend(c->fPeer + "\n" + payload); }

        /*
         A message to a remote control. On `ctl`, a message larger than a
         relay message is split into chunks (splitMessage of protocol.ts), cut
         between UTF-8 characters so that each chunk stays valid text.
        */
        void send(Client* c, const std::string& text, bool stream = false)
        {
            if (c->fClosing) return;
            if (stream) {
                relay(c, "s" + text);
                return;
            }
            fChunkId++;
            if (text.size() <= kRelayMessageSize) {
                relay(c, "c" + text);
                return;
            }
            size_t size = std::max<size_t>(1, (kRelayMessageSize - 128) / 6);
            std::vector<std::string> parts;
            for (size_t start = 0; start < text.size();) {
                size_t stop = std::min(text.size(), start + size);
                while (stop < text.size() && (uint8_t(text[stop]) & 0xC0) == 0x80) stop--;
                if (stop <= start) stop = std::min(text.size(), start + size);
                parts.push_back(text.substr(start, stop - start));
                start = stop;
            }
            for (size_t part = 0; part < parts.size(); part++) {
                relay(c, "c{\"type\":\"chunk\",\"id\":" + num(fChunkId) + ",\"part\":" + num(double(part))
                      + ",\"of\":" + num(double(parts.size())) + ",\"data\":" + RemoteJSON::quote(parts[part]) + "}");
            }
        }

        void sendSync(Client* c, int i, double value)
        {
            send(c, "{\"type\":\"sync\",\"i\":" + num(i) + ",\"value\":" + val(value) + "}");
        }

        void error(const std::string& message) { if (fOnError) fOnError(message); }

        /** The rate limit: whether one more message fits in this second. */
        bool admit(Client* c, double t)
        {
            if (t - c->fWindowStart >= 1000) {
                c->fWindowStart = t;
                c->fWindowCount = 0;
            }
            c->fWindowCount += 1;
            return c->fWindowCount <= fOptions.fMaxMessageRate;
        }

        /**
         * Whether a message is newer than the last one applied for its key.
         * Equal is fresh: the last value of a gesture is sent again on the
         * reliable channel under the sequence number it had on the other one.
         */
        bool fresh(Client* c, const std::string& key, const RemoteClientMessage& m)
        {
            if (!m.fHasSeq) return true;
            auto it = c->fSeqs.find(key);
            if (it != c->fSeqs.end() && m.fSeq < it->second) return false;
            c->fSeqs[key] = m.fSeq;
            return true;
        }

        void reject(Client* c, const std::string& code, const std::string& reason)
        {
            send(c, "{\"type\":\"reject\",\"code\":" + RemoteJSON::quote(code) + ",\"reason\":" + RemoteJSON::quote(reason) + "}");
            drop(c, reason, false);
        }

        void hello(Client* c, const RemoteClientMessage& m)
        {
            if (m.fVersion != kProtocolVersion) return reject(c, "version", "protocol 1 expected");
            if (!fOptions.fToken.empty() && (!m.fHasToken || m.fToken != fOptions.fToken)) return reject(c, "token", "invalid token");
            if (m.fHasHash) {
                if (fHash.empty()) fHash = RemoteHash::hex(RemoteHash::sha256(fJSON));
                if (m.fHash != fHash) return reject(c, "dsp-mismatch", "not the DSP this host runs");
            }
            // A remote control coming back replaces its previous session
            for (Client* other : open()) {
                if (other->fId == m.fId) drop(other, "replaced", true);
            }
            if (int(open().size()) >= fOptions.fMaxClients) return reject(c, "full", "too many remote controls");

            c->fId = m.fId;
            c->fMode = (fOptions.fMode == "uni") ? "uni" : m.fMode;
            // The bargraphs as they are now, not at the last tick: a node reports
            // them at every block, so a Web Audio host's welcome has them fresh
            readOutputs();
            c->fOutSent = fOutValues;
            c->fOpen = true;

            const std::vector<RemoteInput>& inputs = fTarget->getRemoteInputs();
            const std::vector<RemoteOutput>& outputs = fTarget->getRemoteOutputs();
            std::string w = "{\"type\":\"welcome\",\"v\":1,\"session\":" + RemoteJSON::quote(fSession)
                + ",\"mode\":" + RemoteJSON::quote(c->fMode);
            if (c->fMode == "bi") w += ",\"json\":" + RemoteJSON::quote(fJSON);
            w += ",\"inputs\":[";
            for (size_t i = 0; i < inputs.size(); i++) w += (i ? "," : "") + RemoteJSON::quote(inputs[i].fAddress);
            w += "],\"outputs\":[";
            for (size_t k = 0; k < outputs.size(); k++) w += (k ? "," : "") + RemoteJSON::quote(outputs[k].fAddress);
            w += "],\"values\":[";
            for (size_t i = 0; i < inputs.size(); i++) w += (i ? "," : "") + val(fTarget->getRemoteInput(int(i)));
            w += "],\"outputValues\":[";
            for (size_t k = 0; k < fOutValues.size(); k++) w += (k ? "," : "") + val(fOutValues[k]);
            w += "],\"voices\":" + num(fVoices) + ",\"rates\":{\"out\":" + num(fOptions.fOutputRate) + "},\"sensors\":\"shared\"}";
            send(c, w);
            if (fOnJoin) fOnJoin(c->fId);
        }

        void handle(Client* c, const RemoteClientMessage& m, double t)
        {
            const std::vector<RemoteInput>& inputs = fTarget->getRemoteInputs();
            switch (m.fType) {
                case RemoteClientMessage::kParam: {
                    if (m.fIndex >= double(inputs.size())) return;
                    int i = int(m.fIndex);
                    const RemoteInput& item = inputs[i];
                    if (item.fRemoteOff) {
                        // Kept from remote controls by the DSP: refused, and the
                        // real value sent back so the writer's control returns
                        sendSync(c, i, fTarget->getRemoteInput(i));
                        return;
                    }
                    if (!fresh(c, "p" + std::to_string(i), m)) return;
                    double value = std::min(item.fMax, std::max(item.fMin, m.fValue));
                    // The value asked for, not the one applied: if the two differ,
                    // the echo is not filtered and corrects the writer's control
                    c->fWritten[i] = std::make_pair(m.fValue, t);
                    if (item.fButton) {
                        if (value != 0) c->fHeld.insert(i);
                        else c->fHeld.erase(i);
                    }
                    fTarget->setRemoteInput(i, value);
                    return;
                }
                case RemoteClientMessage::kAcc: {
                    if (!fRemoteAcc) return;
                    if (!fresh(c, "acc", m)) return;
                    if (!fTarget->hasRemoteAcc()) return;
                    // Android reports the opposite sign: corrected here, once
                    double sign = m.fInvert ? -1 : 1;
                    fTarget->propagateRemoteAcc(sign * m.fAxes[0], sign * m.fAxes[1], sign * m.fAxes[2]);
                    return;
                }
                case RemoteClientMessage::kGyr: {
                    if (!fRemoteGyr) return;
                    if (!fresh(c, "gyr", m)) return;
                    if (!fTarget->hasRemoteGyr()) return;
                    fTarget->propagateRemoteGyr(m.fAxes[0], m.fAxes[1], m.fAxes[2]);
                    return;
                }
                case RemoteClientMessage::kMidi:
                    trackNotes(c->fNotes, m.fData);
                    fTarget->remoteMidi(m.fData);
                    return;
                case RemoteClientMessage::kPing:
                    send(c, "{\"type\":\"pong\",\"s\":" + num(m.fS) + ",\"t0\":" + num(m.fT0)
                         + ",\"t1\":" + num(t) + ",\"t2\":" + num(fNow()) + "}");
                    return;
                case RemoteClientMessage::kBye:
                    drop(c, m.fHasReason ? m.fReason : "bye", false);
                    return;
                case RemoteClientMessage::kHello:
                    // Already open: a second hello changes nothing
                    return;
            }
        }

        /** Keep the set of notes a remote control holds in step with its MIDI. */
        static void trackNotes(std::set<int>& notes, const std::vector<int>& data)
        {
            int kind = data[0] & 0xF0;
            int channel = data[0] & 0x0F;
            int a = data.size() > 1 ? data[1] : 0;
            int b = data.size() > 2 ? data[2] : 0;
            if (kind == 0x90 && b > 0) {
                notes.insert((channel << 8) | a);
            } else if (kind == 0x80 || kind == 0x90) {
                notes.erase((channel << 8) | a);
            } else if (kind == 0xB0 && (a == 120 || a == 123)) {
                for (auto it = notes.begin(); it != notes.end();) {
                    if ((*it >> 8) == channel) it = notes.erase(it);
                    else ++it;
                }
            }
        }

        /*
         Release what a remote control held, then forget it: a button goes
         back to 0 unless another remote control holds it too, and every note
         it started and did not end is ended.
        */
        void drop(Client* c, const std::string& reason, bool sayBye)
        {
            if (c->fClosing) return;
            if (c->fOpen) {
                for (int i : c->fHeld) {
                    bool heldElsewhere = false;
                    for (Client* other : open()) {
                        if (other != c && other->fHeld.count(i)) heldElsewhere = true;
                    }
                    if (!heldElsewhere) fTarget->setRemoteInput(i, 0);
                }
                for (int note : c->fNotes) {
                    std::vector<int> off = {0x80 | (note >> 8), note & 0x7F, 0};
                    fTarget->remoteMidi(off);
                }
                c->fHeld.clear();
                c->fNotes.clear();
            }
            if (sayBye) send(c, "{\"type\":\"bye\",\"reason\":" + RemoteJSON::quote(reason) + "}");
            bool wasOpen = c->fOpen;
            std::string id = c->fId;
            // The end of its relayed connection, unless the relay itself is gone
            if (!fRelayGone) relay(c, "!");
            c->fClosing = true;
            c->fOpen = false;
            for (auto it = fClients.begin(); it != fClients.end(); ++it) {
                if (it->get() == c) {
                    fClients.erase(it);
                    break;
                }
            }
            if (wasOpen && fOnLeave) fOnLeave(id);
        }

        void readOutputs()
        {
            for (size_t k = 0; k < fOutValues.size(); k++) {
                double v = fTarget->getRemoteOutput(int(k));
                if (std::isfinite(v)) fOutValues[k] = v;
            }
        }

        void flushOutputs(Client* c)
        {
            std::vector<size_t> changed;
            for (size_t k = 0; k < fOutValues.size(); k++) {
                // Written so that a NaN never compares as "unchanged"
                if (!(fabs(fOutValues[k] - c->fOutSent[k]) <= fOutputThreshold[k])) changed.push_back(k);
            }
            if (changed.empty()) return;
            for (size_t k : changed) c->fOutSent[k] = fOutValues[k];
            std::string values, indices;
            for (size_t n = 0; n < changed.size(); n++) {
                values += (n ? "," : "") + val(fOutValues[changed[n]]);
                indices += (n ? "," : "") + num(double(changed[n]));
            }
            if (changed.size() == fOutValues.size()) {
                send(c, "{\"type\":\"out\",\"values\":[" + values + "]}", true);
            } else {
                send(c, "{\"type\":\"out\",\"i\":[" + indices + "],\"values\":[" + values + "]}", true);
            }
        }

    public:

        /** Called with a remote control's id when it joins, when it leaves; and with errors. */
        std::function<void(const std::string&)> fOnJoin, fOnLeave, fOnError;

        /**
         * @param target the DSP
         * @param options as FaustRemoteHostOptions
         * @param send called with each message for the relay, in its framing
         * @param now milliseconds of a monotonic clock (pongs carry it)
         */
        RemoteHost(RemoteTarget* target, const RemoteHostOptions& options, Sender send, Clock now = Clock())
        :fTarget(target), fOptions(options), fSend(send), fNow(now ? now : Clock(steadyMs)),
        fVoices(0), fChunkId(0), fClosed(false), fRelayGone(false)
        {
            fSession = RemoteHash::randomHex(4);
            fJSON = target->getRemoteJSON();
            fRemoteAcc = fRemoteGyr = false;
            for (const RemoteInput& input : target->getRemoteInputs()) {
                // A control kept from remote controls is not theirs to drive by their sensors either
                if (input.fRemoteOff) continue;
                fRemoteAcc |= input.fAcc;
                fRemoteGyr |= input.fGyr;
            }
            for (const RemoteOutput& output : target->getRemoteOutputs()) {
                double range = output.fMax - output.fMin;
                fOutputThreshold.push_back(std::isfinite(range) ? fabs(range) * fOptions.fOutputDeadband : 0);
                double v = target->getRemoteOutput(int(fOutValues.size()));
                fOutValues.push_back(std::isfinite(v) ? v : 0);
            }
            for (size_t i = 0; i < target->getRemoteInputs().size(); i++) fSeen.push_back(target->getRemoteInput(int(i)));
            int voices = target->getRemoteVoices();
            fVoices = voices < 0 ? 0 : voices;
        }

        virtual ~RemoteHost() {}

        /** The remote controls past their handshake, by their ids, in the order they joined. */
        std::vector<std::string> getClients()
        {
            std::vector<std::string> res;
            for (Client* c : open()) res.push_back(c->fId);
            return res;
        }

        /** The relay is (again) connected: messages can go out. */
        void relayOpened() { fRelayGone = false; }

        /** A message from the relay. */
        void receive(const std::string& text)
        {
            if (fClosed) return;
            size_t cut = text.find('\n');
            if (cut == std::string::npos || cut == 0) return;
            std::string peer = text.substr(0, cut);
            std::string payload = text.substr(cut + 1);
            Client* c = find(peer);
            if (payload == "!") {
                if (c) drop(c, "remote closed", false);
                return;
            }
            if (payload.empty() || (payload[0] != 'c' && payload[0] != 's')) return;
            if (!c) {
                std::unique_ptr<Client> client(new Client());
                client->fPeer = peer;
                client->fLastMessageAt = client->fWindowStart = fNow();
                client->fOutSent = fOutValues;
                c = client.get();
                fClients.push_back(std::move(client));
            }
            if (c->fClosing) return;
            RemoteClientMessage m;
            if (!RemoteClientMessage::parse(payload.substr(1), m)) return;
            double t = fNow();
            c->fLastMessageAt = t;
            if (m.fType != RemoteClientMessage::kBye && !admit(c, t)) return;
            if (!c->fOpen) {
                if (m.fType == RemoteClientMessage::kHello) hello(c, m);
                else if (m.fType == RemoteClientMessage::kBye) drop(c, "bye", false);
                return;
            }
            handle(c, m, t);
        }

        /**
         * The relay connection is gone: so are the remote controls it relayed.
         * What they held is released; nothing can be said to them any more.
         */
        void relayClosed()
        {
            fRelayGone = true;
            while (!fClients.empty()) drop(fClients.front().get(), "relay closed", false);
        }

        /**
         * Housekeeping, `fOutputRate` times a second: drop the silent remote
         * controls, send parameter changes made elsewhere (`sync`), bargraphs
         * (`out`) and the number of active voices.
         */
        void tick()
        {
            if (fClosed) return;
            double t = fNow();
            std::vector<Client*> all;
            for (auto& c : fClients) all.push_back(c.get());
            for (Client* c : all) {
                if (t - c->fLastMessageAt > fOptions.fLivenessTimeout) drop(c, "timeout", true);
            }

            // Parameter changes, from any source, the remote controls' own included
            std::vector<std::pair<int, double> > pending;
            for (size_t i = 0; i < fSeen.size(); i++) {
                double v = fTarget->getRemoteInput(int(i));
                if (std::isfinite(v) && v != fSeen[i]) pending.push_back(std::make_pair(int(i), v));
                fSeen[i] = v;
            }
            readOutputs();
            int voices = fTarget->getRemoteVoices();
            bool voicesChanged = voices >= 0 && voices != fVoices;
            if (voicesChanged) fVoices = voices;

            for (Client* c : open()) {
                if (c->fMode != "bi") continue;
                for (const auto& p : pending) {
                    // Do not send a writer its own write back while it may still
                    // be moving the control: its slider would jump backwards
                    auto w = c->fWritten.find(p.first);
                    if (w != c->fWritten.end() && t - w->second.second < fOptions.fEchoWindow
                        && float(w->second.first) == float(p.second)) continue;
                    sendSync(c, p.first, p.second);
                }
                flushOutputs(c);
                if (voicesChanged) send(c, "{\"type\":\"voices\",\"count\":" + num(fVoices) + "}");
            }
        }

        /** Say goodbye to every remote control, and release what they held. */
        void close(const std::string& reason = "host closed")
        {
            if (fClosed) return;
            while (!fClients.empty()) drop(fClients.front().get(), reason, true);
            fClosed = true;
        }
};

#endif
/**************************  END  RemoteHost.h **************************/

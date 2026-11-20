/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

// The host of the remote control protocol (architecture/faust/gui/RemoteHost.h)
// without network and without DSP: a fake target records what the host does
// to the DSP, a fake relay what it sends, and the clock is the test's.
//
// The cases follow the host's rules as faustwasm's FaustRemoteHost applies
// them (src/remote/FaustRemoteHost.ts and its tests): the C++ host is a port
// of it, and the conformance test of faustwasm compares the two on the wire.

#include <cstdio>
#include <cstring>
#include <clocale>
#include <string>
#include <vector>

#include "faust/gui/RemoteHost.h"

static int gChecks = 0;
static int gErrors = 0;

#define CHECK(cond) check((cond), #cond, __LINE__)

static void check(bool cond, const char* what, int line)
{
    gChecks++;
    if (!cond) {
        gErrors++;
        printf("FAILED line %d: %s\n", line, what);
    }
}

// ------------------------------------------------------------------ fakes

struct FakeTarget : public RemoteTarget {

    std::vector<RemoteInput> fInputs;
    std::vector<RemoteOutput> fOutputs;
    std::vector<double> fValues;
    std::vector<double> fOutValues;
    std::vector<std::pair<int, double> > fWrites;
    std::vector<std::vector<int> > fMidi;
    std::vector<double> fAcc, fGyr;
    int fVoices;
    std::string fJSON;

    FakeTarget():fVoices(-1), fJSON("{\"name\":\"t\",\"ui\":[]}")
    {
        // 0 /t/freq [20, 2000], 1 /t/gate button, 2 /t/locked [remote:off], 3 /t/tilt [acc:]
        addInput("/t/freq", false, 20, 2000, 440);
        addInput("/t/gate", true, 0, 1, 0);
        addInput("/t/locked", false, 0, 1, 0.5);
        fInputs.back().fRemoteOff = true;
        addInput("/t/tilt", false, 0, 1, 0);
        fInputs.back().fAcc = true;
        RemoteOutput out;
        out.fAddress = "/t/level";
        out.fMin = 0;
        out.fMax = 1;
        fOutputs.push_back(out);
        fOutValues.push_back(0);
    }

    void addInput(const char* address, bool button, double min, double max, double init)
    {
        RemoteInput input;
        input.fAddress = address;
        input.fButton = button;
        input.fMin = min;
        input.fMax = max;
        input.fRemoteOff = false;
        input.fAcc = input.fGyr = false;
        fInputs.push_back(input);
        fValues.push_back(init);
    }

    std::string getRemoteJSON() { return fJSON; }
    const std::vector<RemoteInput>& getRemoteInputs() { return fInputs; }
    const std::vector<RemoteOutput>& getRemoteOutputs() { return fOutputs; }
    double getRemoteInput(int i) { return fValues[i]; }
    void setRemoteInput(int i, double value)
    {
        fValues[i] = value;
        fWrites.push_back(std::make_pair(i, value));
    }
    double getRemoteOutput(int k) { return fOutValues[k]; }
    bool hasRemoteAcc() { return true; }
    bool hasRemoteGyr() { return false; }
    void propagateRemoteAcc(double x, double y, double z) { fAcc = {x, y, z}; }
    void propagateRemoteGyr(double a, double b, double g) { fGyr = {a, b, g}; }
    void remoteMidi(const std::vector<int>& data) { fMidi.push_back(data); }
    int getRemoteVoices() { return fVoices; }
};

/** A host with its relay and clock: `say` speaks for a remote control, `heard` reads what it got. */
struct Bench {

    FakeTarget fTarget;
    std::vector<std::string> fSent;
    double fTime;
    RemoteHost fHost;
    std::vector<std::string> fJoined, fLeft;

    Bench(RemoteHostOptions options = defaults())
    :fTime(1000), fHost(&fTarget, options, [this](const std::string& text) { fSent.push_back(text); }, [this]() { return fTime; })
    {
        fHost.fOnJoin = [this](const std::string& id) { fJoined.push_back(id); };
        fHost.fOnLeave = [this](const std::string& id) { fLeft.push_back(id); };
    }

    static RemoteHostOptions defaults()
    {
        RemoteHostOptions options;
        options.fToken = "secret";
        return options;
    }

    void say(const std::string& peer, const std::string& message, char channel = 'c')
    {
        fHost.receive(peer + "\n" + channel + message);
    }

    void join(const std::string& peer, const std::string& id)
    {
        say(peer, "{\"type\":\"hello\",\"v\":1,\"id\":\"" + id + "\",\"token\":\"secret\",\"mode\":\"bi\"}");
    }

    // The messages sent to `peer` since the last call, parsed; `!` for the end of its connection
    std::vector<RemoteJSON> heard(const std::string& peer, bool* ended = nullptr)
    {
        std::vector<RemoteJSON> res;
        std::vector<std::string> rest;
        if (ended) *ended = false;
        for (const std::string& text : fSent) {
            size_t cut = text.find('\n');
            if (text.substr(0, cut) != peer) {
                rest.push_back(text);
                continue;
            }
            std::string payload = text.substr(cut + 1);
            if (payload == "!") {
                if (ended) *ended = true;
                continue;
            }
            RemoteJSON m;
            check(RemoteJSON::parse(payload.substr(1), m), "a message the host sent is JSON", __LINE__);
            res.push_back(m);
        }
        fSent = rest;
        return res;
    }

    static std::string type(const RemoteJSON& m)
    {
        const RemoteJSON* t = m.get("type");
        return t ? t->fString : "";
    }

    static double number(const RemoteJSON& m, const char* key)
    {
        const RemoteJSON* v = m.get(key);
        return v ? v->fNumber : -12345;
    }
};

// ------------------------------------------------------------------ cases

static void testHashes()
{
    CHECK(RemoteHash::hex(RemoteHash::sha1("abc")) == "a9993e364706816aba3e25717850c26c9cd0d89d");
    CHECK(RemoteHash::hex(RemoteHash::sha1("")) == "da39a3ee5e6b4b0d3255bfef95601890afd80709");
    CHECK(RemoteHash::hex(RemoteHash::sha256("abc")) == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    // Two blocks
    CHECK(RemoteHash::hex(RemoteHash::sha256("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"))
          == "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
    // RFC 6455's own example of the handshake
    CHECK(RemoteHash::base64(RemoteHash::sha1("dGhlIHNhbXBsZSBub25jZQ==258EAFA5-E914-47DA-95CA-C5AB0DC85B11"))
          == "s3pPLMBiTxaQ9kYGzzhZRbK+xOo=");
    CHECK(RemoteHash::base64("f") == "Zg==" && RemoteHash::base64("fo") == "Zm8=" && RemoteHash::base64("foo") == "Zm9v");
    std::string a = RemoteHash::randomHex(16), b = RemoteHash::randomHex(16);
    CHECK(a.size() == 32 && a != b);
}

static void testJSON()
{
    RemoteJSON v;
    CHECK(RemoteJSON::parse("{\"a\":1,\"b\":[1,2.5,-3e2],\"c\":\"x\\u00e9\\n\",\"d\":true,\"e\":null,\"f\":{\"g\":[]}}", v));
    CHECK(v.get("a")->fNumber == 1);
    CHECK(v.get("b")->fArray.size() == 3 && v.get("b")->fArray[2].fNumber == -300);
    CHECK(v.get("c")->fString == "x\xc3\xa9\n");
    CHECK(v.get("d")->fBool && v.get("e")->fKind == RemoteJSON::kNull);
    // The last of two equal keys wins, as with JSON.parse
    CHECK(RemoteJSON::parse("{\"a\":1,\"a\":2}", v) && v.get("a")->fNumber == 2);
    // A surrogate pair, and a lone half
    CHECK(RemoteJSON::parse("\"\\ud83c\\udfb9\\ud800\"", v) && v.fString == "\xf0\x9f\x8e\xb9\xef\xbf\xbd");
    for (const char* bad : {"", "{", "{\"a\":}", "[1,]", "01", "1.", ".5", "+1", "\"a", "{\"a\":1} x", "tru", "\"\x01\"", "NaN"}) {
        RemoteJSON w;
        if (RemoteJSON::parse(bad, w)) printf("accepted: %s\n", bad);
        CHECK(!RemoteJSON::parse(bad, w));
    }
    // Out of range, as JSON.parse reads it
    CHECK(RemoteJSON::parse("1e400", v) && std::isinf(v.fNumber));
    CHECK(RemoteJSON::parse("1e-400", v) && v.fNumber == 0);

    CHECK(RemoteJSON::number(440) == "440");
    CHECK(RemoteJSON::number(1e21) == "1e+21" && RemoteJSON::number(1e20) == "100000000000000000000");
    CHECK(RemoteJSON::number(1e-7) == "1e-7" && RemoteJSON::number(0.000001) == "0.000001");
    CHECK(RemoteJSON::number(123.456) == "123.456" && RemoteJSON::number(-1.5e-10) == "-1.5e-10");
    CHECK(RemoteJSON::number(5e-324) == "5e-324" && RemoteJSON::number(1.7976931348623157e308) == "1.7976931348623157e+308");
    CHECK(RemoteJSON::number(0.5) == "0.5");
    CHECK(RemoteJSON::number(-0.25) == "-0.25");
    CHECK(RemoteJSON::number(0.1) == "0.1");
    CHECK(RemoteJSON::number(double(0.1f), true) == "0.1");
    CHECK(RemoteJSON::number(double(0.1f)) != "0.1");
    CHECK(RemoteJSON::read(RemoteJSON::number(1.0 / 3)) == 1.0 / 3);
    CHECK(RemoteJSON::quote("a\"b\\c\n\x01") == "\"a\\\"b\\\\c\\n\\u0001\"");
    // A decimal comma in the C locale changes nothing
    if (setlocale(LC_NUMERIC, "fr_FR.UTF-8") || setlocale(LC_NUMERIC, "de_DE.UTF-8")) {
        CHECK(RemoteJSON::number(0.5) == "0.5");
        CHECK(RemoteJSON::parse("0.5", v) && v.fNumber == 0.5);
        setlocale(LC_NUMERIC, "C");
    }
}

static void testMessages()
{
    RemoteClientMessage m;
    for (const char* good : {
             "{\"type\":\"hello\",\"v\":1,\"id\":\"a\",\"mode\":\"bi\"}",
             "{\"type\":\"hello\",\"v\":1,\"id\":\"a\",\"mode\":\"uni\",\"token\":\"t\",\"hash\":\"h\"}",
             "{\"type\":\"param\",\"i\":0,\"value\":0.5}",
             "{\"type\":\"param\",\"i\":3,\"value\":-2,\"seq\":7}",
             "{\"type\":\"acc\",\"x\":0,\"y\":-9.8,\"z\":0.1,\"invert\":false,\"seq\":1}",
             "{\"type\":\"gyr\",\"alpha\":10,\"beta\":20,\"gamma\":30}",
             "{\"type\":\"midi\",\"data\":[144,60,100]}",
             "{\"type\":\"ping\",\"s\":1,\"t0\":12.5}",
             "{\"type\":\"bye\"}",
             "{\"type\":\"param\",\"i\":1e0,\"value\":0,\"extra\":{\"x\":[1]}}"}) {
        if (!RemoteClientMessage::parse(good, m)) printf("refused: %s\n", good);
        CHECK(RemoteClientMessage::parse(good, m));
    }
    for (const char* bad : {
             "not json", "42", "null", "[]",
             "{\"type\":\"unknown\"}",
             "{\"type\":\"hello\",\"v\":1,\"id\":\"a\",\"mode\":\"both\"}",
             "{\"type\":\"hello\",\"v\":1,\"mode\":\"bi\"}",
             "{\"type\":\"param\",\"i\":1.5,\"value\":0}",
             "{\"type\":\"param\",\"i\":-1,\"value\":0}",
             "{\"type\":\"param\",\"i\":0}",
             "{\"type\":\"param\",\"i\":0,\"value\":\"1\"}",
             "{\"type\":\"param\",\"i\":0,\"value\":null}",
             "{\"type\":\"param\",\"i\":0,\"value\":1e400}",
             "{\"type\":\"param\",\"i\":0,\"value\":1,\"seq\":-1}",
             "{\"type\":\"acc\",\"x\":0,\"y\":0,\"z\":0}",
             "{\"type\":\"acc\",\"x\":0,\"y\":0,\"z\":null,\"invert\":true}",
             "{\"type\":\"gyr\",\"alpha\":0,\"beta\":0}",
             "{\"type\":\"ping\",\"s\":1}",
             "{\"type\":\"welcome\"}"}) {
        if (RemoteClientMessage::parse(bad, m)) printf("accepted: %s\n", bad);
        CHECK(!RemoteClientMessage::parse(bad, m));
    }
    const char* accepted[] = {"[128,60,0]", "[159,127,127]", "[160,60,10]", "[179,7,100]", "[192,5]", "[208,64]", "[224,0,64]"};
    const char* refused[] = {"[]", "[60,100]", "[240,126,247]", "[248]", "[144,60]", "[144,60,100,1]", "[192,5,1]",
                             "[144,128,1]", "[144,60,-1]", "[144,60.5,1]", "\"string\""};
    for (const char* data : accepted) CHECK(RemoteClientMessage::parse(std::string("{\"type\":\"midi\",\"data\":") + data + "}", m));
    for (const char* data : refused) CHECK(!RemoteClientMessage::parse(std::string("{\"type\":\"midi\",\"data\":") + data + "}", m));
}

static void testHandshake()
{
    Bench bench;
    bool ended;
    // Wrong token: rejected, and the connection ended
    bench.say("p1", "{\"type\":\"hello\",\"v\":1,\"id\":\"a\",\"token\":\"guess\",\"mode\":\"bi\"}");
    std::vector<RemoteJSON> got = bench.heard("p1", &ended);
    CHECK(got.size() == 1 && Bench::type(got[0]) == "reject" && got[0].get("code")->fString == "token");
    CHECK(ended);
    // No token at all
    bench.say("p0", "{\"type\":\"hello\",\"v\":1,\"id\":\"a\",\"mode\":\"bi\"}");
    got = bench.heard("p0");
    CHECK(got.size() == 1 && got[0].get("code")->fString == "token");
    // Another version
    bench.say("p2", "{\"type\":\"hello\",\"v\":2,\"id\":\"a\",\"token\":\"secret\",\"mode\":\"bi\"}");
    got = bench.heard("p2");
    CHECK(got.size() == 1 && got[0].get("code")->fString == "version");
    // Before the handshake, nothing else is taken
    bench.say("p3", "{\"type\":\"param\",\"i\":0,\"value\":100}");
    CHECK(bench.fTarget.fWrites.empty());
    // The right one: welcome
    bench.join("p3", "a");
    got = bench.heard("p3", &ended);
    CHECK(!ended && got.size() == 1 && Bench::type(got[0]) == "welcome");
    const RemoteJSON& w = got[0];
    CHECK(Bench::number(w, "v") == 1 && w.get("mode")->fString == "bi" && w.get("json")->fString == bench.fTarget.fJSON);
    CHECK(w.get("inputs")->fArray.size() == 4 && w.get("inputs")->fArray[1].fString == "/t/gate");
    CHECK(w.get("outputs")->fArray.size() == 1 && w.get("outputs")->fArray[0].fString == "/t/level");
    CHECK(w.get("values")->fArray[0].fNumber == 440 && w.get("values")->fArray[2].fNumber == 0.5);
    CHECK(w.get("outputValues")->fArray.size() == 1 && Bench::number(w, "voices") == 0);
    CHECK(w.get("rates")->get("out")->fNumber == 30 && w.get("sensors")->fString == "shared");
    CHECK(!w.get("delay") && !w.get("group"));
    CHECK(bench.fJoined.size() == 1 && bench.fJoined[0] == "a");
    CHECK(bench.fHost.getClients().size() == 1);
    // A second hello changes nothing
    bench.join("p3", "a");
    CHECK(bench.heard("p3").empty());

    // A unidirectional remote control gets no JSON
    bench.say("p4", "{\"type\":\"hello\",\"v\":1,\"id\":\"u\",\"token\":\"secret\",\"mode\":\"uni\"}");
    got = bench.heard("p4");
    CHECK(got.size() == 1 && got[0].get("mode")->fString == "uni" && !got[0].get("json"));
    // The hash of the JSON the remote control holds: SHA-256, in hex
    std::string hash = RemoteHash::hex(RemoteHash::sha256(bench.fTarget.fJSON));
    bench.say("p5", "{\"type\":\"hello\",\"v\":1,\"id\":\"h\",\"token\":\"secret\",\"mode\":\"uni\",\"hash\":\"" + hash + "\"}");
    got = bench.heard("p5");
    CHECK(got.size() == 1 && Bench::type(got[0]) == "welcome");
    bench.say("p6", "{\"type\":\"hello\",\"v\":1,\"id\":\"h2\",\"token\":\"secret\",\"mode\":\"uni\",\"hash\":\"00\"}");
    got = bench.heard("p6");
    CHECK(got.size() == 1 && got[0].get("code")->fString == "dsp-mismatch");
}

static void testFullAndReplaced()
{
    RemoteHostOptions options = Bench::defaults();
    options.fMaxClients = 1;
    Bench bench(options);
    bench.join("p1", "a");
    bench.heard("p1");
    bench.join("p2", "b");
    std::vector<RemoteJSON> got = bench.heard("p2");
    CHECK(got.size() == 1 && got[0].get("code")->fString == "full");
    // The same remote control, on a new connection, replaces the old one
    bench.join("p3", "a");
    bool ended;
    got = bench.heard("p1", &ended);
    CHECK(got.size() == 1 && Bench::type(got[0]) == "bye" && got[0].get("reason")->fString == "replaced" && ended);
    got = bench.heard("p3");
    CHECK(got.size() == 1 && Bench::type(got[0]) == "welcome");

    // A unidirectional host imposes its mode
    RemoteHostOptions uni = Bench::defaults();
    uni.fMode = "uni";
    Bench other(uni);
    other.join("p1", "a");
    got = other.heard("p1");
    CHECK(got.size() == 1 && got[0].get("mode")->fString == "uni" && !got[0].get("json"));
}

static void testWrites()
{
    Bench bench;
    bench.join("p1", "a");
    bench.join("p2", "b");
    bench.heard("p1");
    bench.heard("p2");
    FakeTarget& t = bench.fTarget;

    // Held to the range
    bench.say("p1", "{\"type\":\"param\",\"i\":0,\"value\":5000}");
    CHECK(t.fValues[0] == 2000);
    bench.say("p1", "{\"type\":\"param\",\"i\":0,\"value\":-5}");
    CHECK(t.fValues[0] == 20);
    // Out of range index: nothing
    size_t writes = t.fWrites.size();
    bench.say("p1", "{\"type\":\"param\",\"i\":9,\"value\":1}");
    CHECK(t.fWrites.size() == writes);
    // [remote:off]: refused, the real value sent back
    bench.say("p1", "{\"type\":\"param\",\"i\":2,\"value\":1}");
    std::vector<RemoteJSON> got = bench.heard("p1");
    CHECK(t.fValues[2] == 0.5);
    CHECK(got.size() == 1 && Bench::type(got[0]) == "sync" && Bench::number(got[0], "i") == 2 && Bench::number(got[0], "value") == 0.5);
    // Sequence numbers: an older one is dropped, an equal one taken
    bench.say("p1", "{\"type\":\"param\",\"i\":0,\"value\":300,\"seq\":10}", 's');
    bench.say("p1", "{\"type\":\"param\",\"i\":0,\"value\":200,\"seq\":9}", 's');
    CHECK(t.fValues[0] == 300);
    bench.say("p1", "{\"type\":\"param\",\"i\":0,\"value\":310,\"seq\":10}");
    CHECK(t.fValues[0] == 310);

    // At the tick: the change goes to the other remote control, not back to its writer
    bench.fTime += 40;
    bench.fHost.tick();
    std::vector<RemoteJSON> toWriter = bench.heard("p1");
    std::vector<RemoteJSON> toOther = bench.heard("p2");
    bool writerSynced = false;
    for (const RemoteJSON& m : toWriter) writerSynced |= Bench::type(m) == "sync";
    CHECK(!writerSynced);
    CHECK(toOther.size() == 1 && Bench::type(toOther[0]) == "sync" && Bench::number(toOther[0], "i") == 0 && Bench::number(toOther[0], "value") == 310);

    // A value that was clamped is echoed: the writer's slider is corrected
    bench.say("p1", "{\"type\":\"param\",\"i\":0,\"value\":9000}");
    bench.fTime += 40;
    bench.fHost.tick();
    got = bench.heard("p1");
    CHECK(got.size() == 1 && Bench::type(got[0]) == "sync" && Bench::number(got[0], "value") == 2000);
    bench.heard("p2");

    // A change made elsewhere reaches everyone; after the echo window, the writer too
    bench.say("p1", "{\"type\":\"param\",\"i\":0,\"value\":1000}");
    bench.fTime += 600;
    bench.fHost.tick();
    bench.heard("p1");
    bench.heard("p2");
    t.fValues[0] = 1000;  // no change: nothing
    bench.fTime += 40;
    bench.fHost.tick();
    CHECK(bench.heard("p1").empty() && bench.heard("p2").empty());
    t.fValues[0] = 880;
    bench.fTime += 40;
    bench.fHost.tick();
    CHECK(bench.heard("p1").size() == 1 && bench.heard("p2").size() == 1);
}

static void testOutputsAndVoices()
{
    Bench bench;
    bench.join("p1", "a");
    bench.heard("p1");
    bench.fTarget.fOutValues[0] = 0.5;
    bench.fHost.tick();
    std::vector<RemoteJSON> got = bench.heard("p1");
    CHECK(got.size() == 1 && Bench::type(got[0]) == "out" && got[0].get("values")->fArray[0].fNumber == 0.5 && !got[0].get("i"));
    // Within the deadband (0.001 of the range): not resent
    bench.fTarget.fOutValues[0] = 0.5005;
    bench.fHost.tick();
    CHECK(bench.heard("p1").empty());
    bench.fTarget.fOutValues[0] = 0.6;
    bench.fHost.tick();
    CHECK(bench.heard("p1").size() == 1);
    // On the stream channel
    bench.fTarget.fOutValues[0] = 0.7;
    bench.fHost.tick();
    CHECK(bench.fSent.size() == 1 && bench.fSent[0].compare(0, 4, "p1\ns") == 0);
    bench.heard("p1");
    // Not to a unidirectional remote control
    bench.say("p2", "{\"type\":\"hello\",\"v\":1,\"id\":\"u\",\"token\":\"secret\",\"mode\":\"uni\"}");
    bench.heard("p2");
    bench.fTarget.fOutValues[0] = 0.9;
    bench.fHost.tick();
    CHECK(bench.heard("p2").empty() && bench.heard("p1").size() == 1);

    // Voices of a polyphonic DSP
    Bench poly;
    poly.fTarget.fVoices = 0;
    poly.join("p1", "a");
    poly.heard("p1");
    poly.fTarget.fVoices = 2;
    poly.fHost.tick();
    got = poly.heard("p1");
    CHECK(got.size() == 1 && Bench::type(got[0]) == "voices" && Bench::number(got[0], "count") == 2);
}

static void testSensorsMidiPing()
{
    Bench bench;
    bench.join("p1", "a");
    bench.heard("p1");
    FakeTarget& t = bench.fTarget;
    bench.say("p1", "{\"type\":\"acc\",\"x\":1,\"y\":2,\"z\":3,\"invert\":true,\"seq\":1}", 's');
    CHECK(t.fAcc.size() == 3 && t.fAcc[0] == -1 && t.fAcc[2] == -3);
    bench.say("p1", "{\"type\":\"acc\",\"x\":5,\"y\":5,\"z\":5,\"invert\":false,\"seq\":0}", 's');
    CHECK(t.fAcc[0] == -1);
    // No control mapped to the gyroscope: dropped
    bench.say("p1", "{\"type\":\"gyr\",\"alpha\":1,\"beta\":2,\"gamma\":3}", 's');
    CHECK(t.fGyr.empty());

    bench.say("p1", "{\"type\":\"midi\",\"data\":[145,60,100]}");
    bench.say("p1", "{\"type\":\"midi\",\"data\":[145,62,100]}");
    bench.say("p1", "{\"type\":\"midi\",\"data\":[129,62,0]}");
    CHECK(t.fMidi.size() == 3);

    bench.say("p1", "{\"type\":\"ping\",\"s\":7,\"t0\":12.5}");
    std::vector<RemoteJSON> got = bench.heard("p1");
    CHECK(got.size() == 1 && Bench::type(got[0]) == "pong" && Bench::number(got[0], "s") == 7
          && Bench::number(got[0], "t0") == 12.5 && Bench::number(got[0], "t1") == bench.fTime);

    // A button held, then the remote control goes: released, and its note ended
    bench.say("p1", "{\"type\":\"param\",\"i\":1,\"value\":1}");
    CHECK(t.fValues[1] == 1);
    t.fMidi.clear();
    bench.fHost.receive("p1\n!");
    CHECK(t.fValues[1] == 0);
    CHECK(t.fMidi.size() == 1 && t.fMidi[0][0] == 0x81 && t.fMidi[0][1] == 60 && t.fMidi[0][2] == 0);
    CHECK(bench.fLeft.size() == 1 && bench.fHost.getClients().empty());
}

static void testHeldElsewhereAndAllNotesOff()
{
    Bench bench;
    bench.join("p1", "a");
    bench.join("p2", "b");
    FakeTarget& t = bench.fTarget;
    bench.say("p1", "{\"type\":\"param\",\"i\":1,\"value\":1}");
    bench.say("p2", "{\"type\":\"param\",\"i\":1,\"value\":1}");
    bench.fHost.receive("p1\n!");
    CHECK(t.fValues[1] == 1);
    bench.fHost.receive("p2\n!");
    CHECK(t.fValues[1] == 0);

    Bench notes;
    notes.join("p1", "a");
    notes.say("p1", "{\"type\":\"midi\",\"data\":[144,60,100]}");
    notes.say("p1", "{\"type\":\"midi\",\"data\":[176,123,0]}");
    notes.fTarget.fMidi.clear();
    notes.say("p1", "{\"type\":\"bye\"}");
    CHECK(notes.fTarget.fMidi.empty());
}

static void testLimits()
{
    Bench bench;
    bench.join("p1", "a");
    bench.heard("p1");
    FakeTarget& t = bench.fTarget;
    // 200 messages a second: the 200th passes (the hello was the first), the next does not
    size_t writes = t.fWrites.size();
    for (int n = 0; n < 205; n++) bench.say("p1", "{\"type\":\"param\",\"i\":0,\"value\":" + std::to_string(100 + n) + "}");
    CHECK(t.fWrites.size() - writes == 199);
    bench.fTime += 1000;
    bench.say("p1", "{\"type\":\"param\",\"i\":0,\"value\":999}");
    CHECK(t.fValues[0] == 999);

    // Silent for more than 3 s: dropped with a goodbye
    bench.say("p1", "{\"type\":\"param\",\"i\":1,\"value\":1}");
    bench.heard("p1");
    bench.fTime += 3001;
    bench.fHost.tick();
    bool ended;
    std::vector<RemoteJSON> got = bench.heard("p1", &ended);
    CHECK(!got.empty() && Bench::type(got.back()) == "bye" && got.back().get("reason")->fString == "timeout" && ended);
    CHECK(t.fValues[1] == 0);

    // The relay goes: so do its remote controls, without a word
    Bench relay;
    relay.join("p1", "a");
    relay.say("p1", "{\"type\":\"param\",\"i\":1,\"value\":1}");
    relay.fSent.clear();
    relay.fHost.relayClosed();
    CHECK(relay.fSent.empty() && relay.fTarget.fValues[1] == 0 && relay.fHost.getClients().empty());

    // Closing the host says goodbye
    Bench closing;
    closing.join("p1", "a");
    closing.heard("p1");
    closing.fHost.close("dsp-changed");
    got = closing.heard("p1", &ended);
    CHECK(got.size() == 1 && got[0].get("reason")->fString == "dsp-changed" && ended);
    closing.join("p2", "b");
    CHECK(closing.fSent.empty());
}

static void testChunks()
{
    Bench bench;
    // A JSON larger than a relay message, with multibyte characters around the cuts
    std::string big = "{\"name\":\"";
    while (big.size() < 1200 * 1024) big += "\xc3\xa9t\xc3\xa9 ";
    big += "\"}";
    bench.fTarget.fJSON = big;
    RemoteHost host(&bench.fTarget, Bench::defaults(), [&bench](const std::string& text) { bench.fSent.push_back(text); });
    host.receive("p1\nc{\"type\":\"hello\",\"v\":1,\"id\":\"a\",\"token\":\"secret\",\"mode\":\"bi\"}");
    for (const std::string& text : bench.fSent) CHECK(text.size() <= RemoteHost::kRelayMessageSize + 16);
    std::vector<RemoteJSON> got = bench.heard("p1");
    CHECK(got.size() > 1);
    std::string whole;
    bool ok = true;
    for (size_t n = 0; n < got.size(); n++) {
        ok &= Bench::type(got[n]) == "chunk" && Bench::number(got[n], "part") == double(n) && Bench::number(got[n], "of") == double(got.size());
        whole += got[n].get("data")->fString;
    }
    CHECK(ok);
    RemoteJSON w;
    CHECK(RemoteJSON::parse(whole, w) && Bench::type(w) == "welcome" && w.get("json")->fString == big);
}

int main()
{
    testHashes();
    testJSON();
    testMessages();
    testHandshake();
    testFullAndReplaced();
    testWrites();
    testOutputsAndVoices();
    testSensorsMidiPing();
    testHeldElsewhereAndAllNotesOff();
    testLimits();
    testChunks();
    printf("%d checks, %d failed\n", gChecks, gErrors);
    return gErrors ? 1 : 0;
}

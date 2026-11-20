/************************** BEGIN RemoteUI.h *******************************
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

#ifndef __RemoteUI__
#define __RemoteUI__

/*
 RemoteUI: phones drive a native Faust application with the remote control
 of faustwasm (https://github.com/grame-cncm/faustwasm), a PWA: sliders,
 buttons, accelerometer and gyroscope through the DSP's [acc:]/[gyr:]
 metadata, MIDI, bargraphs shown on the phone, several phones at once.

 The phones reach faust-remote-server (the Node server of faustwasm), which
 serves them the PWA over HTTPS and relays their messages; RemoteUI connects
 to that relay as the room's host, through the plain port the server opens
 on 127.0.0.1 with -host-port:

     node scripts/faust-remote-server.js <dir with remote/> -cert cert.pem -key key.pem -host-port 8444
     ./mydsp -remote ws://127.0.0.1:8444 -remote-origin https://192.168.1.20:8443

 The application prints the pairing link (and its QR code) for the phones.

 In an architecture file, like the other controllers:

     RemoteUI remoteinterface(name, DSP, argc, argv);
     DSP->buildUserInterface(&remoteinterface);
     remoteinterface.setMidiHandler(&midi_handler);    // optional, for MIDI and polyphony
     remoteinterface.run();
     ...
     remoteinterface.stop();

 Command line (nothing happens without -remote):

     -remote <ws://host:port>    the server's host port (-host-port), plain ws:// only
     -remote-origin <url>        what phones open (the server's HTTPS origin), for the link;
                                 by default the -remote address itself
     -remote-room <name>         the room; random by default
     -remote-token <token>       the pairing token; random (128 bits) by default

 The protocol and the host's rules are those of RemoteHost.h, a port of
 faustwasm's host. A network thread of its own reads the relay, writes the
 zones (plain FAUSTFLOAT stores, as OSC does), and 30 times a second sends
 back bargraphs and the changes made elsewhere. The audio thread is never
 touched.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <iostream>

#include "faust/dsp/dsp.h"
#include "faust/gui/APIUI.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/RemoteHost.h"
#include "faust/gui/qrcodegen.h"

class RemoteUI : public APIUI, public RemoteTarget {

    private:

        std::string fName;
        std::string fJSON;
        std::string fServer;            // ws://host:port of the relay
        std::string fOrigin;            // what phones open
        std::string fRoom;
        std::string fToken;
        RemoteHostOptions fOptions;

        std::vector<RemoteInput> fInputs;
        std::vector<RemoteOutput> fOutputs;
        std::vector<int> fInputItems;   // index in fItems of each input
        std::vector<int> fOutputItems;  // of each output
        bool fHasAcc, fHasGyr;

        std::function<void(const std::vector<int>&)> fMidi;
        std::function<int()> fVoices;

        std::thread fThread;
        std::atomic<bool> fRunning;
        std::string fLastStatus;        // printed once per change, not at every retry

        static std::string option(int argc, char* argv[], const char* name, const std::string& def)
        {
            for (int i = 1; i + 1 < argc; i++) {
                if (strcmp(argv[i], name) == 0) return argv[i + 1];
            }
            return def;
        }

        static std::string encode(const std::string& text)
        {
            static const char* digits = "0123456789ABCDEF";
            std::string res;
            for (unsigned char c : text) {
                if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                    res.push_back(char(c));
                } else {
                    res.push_back('%');
                    res.push_back(digits[c >> 4]);
                    res.push_back(digits[c & 15]);
                }
            }
            return res;
        }

        static std::string httpOrigin(const std::string& url)
        {
            std::string res = url;
            if (res.compare(0, 5, "ws://") == 0) res = "http://" + res.substr(5);
            else if (res.compare(0, 6, "wss://") == 0) res = "https://" + res.substr(6);
            while (!res.empty() && res[res.size() - 1] == '/') res.erase(res.size() - 1);
            return res;
        }

        void status(const std::string& text)
        {
            if (text == fLastStatus) return;
            fLastStatus = text;
            std::cerr << "RemoteUI: " << text << std::endl;
        }

        // The inputs and outputs, in UI order, from what APIUI collected
        void collect()
        {
            fInputs.clear();
            fOutputs.clear();
            fInputItems.clear();
            fOutputItems.clear();
            for (int p = 0; p < getParamsCount(); p++) {
                ItemType type = getParamItemType(p);
                if (type == kHBargraph || type == kVBargraph) {
                    RemoteOutput output;
                    output.fAddress = getParamAddress(p);
                    output.fMin = getParamMin(p);
                    output.fMax = getParamMax(p);
                    fOutputs.push_back(output);
                    fOutputItems.push_back(p);
                } else {
                    RemoteInput input;
                    input.fAddress = getParamAddress(p);
                    input.fButton = (type == kButton);
                    if (type == kButton || type == kCheckButton) {
                        input.fMin = 0;
                        input.fMax = 1;
                    } else {
                        input.fMin = getParamMin(p);
                        input.fMax = getParamMax(p);
                    }
                    const char* remote = getMetadata(p, "remote");
                    std::string off = remote ? remote : "";
                    off.erase(0, off.find_first_not_of(" \t"));
                    off.erase(off.find_last_not_of(" \t") + 1);
                    for (size_t i = 0; i < off.size(); i++) off[i] = char(tolower((unsigned char)off[i]));
                    input.fRemoteOff = (off == "off");
                    input.fAcc = getMetadata(p, "acc") != nullptr;
                    input.fGyr = getMetadata(p, "gyr") != nullptr;
                    fInputs.push_back(input);
                    fInputItems.push_back(p);
                }
            }
            fHasAcc = getAccCount(0) + getAccCount(1) + getAccCount(2) > 0;
            fHasGyr = getGyrCount(0) + getGyrCount(1) + getGyrCount(2) > 0;
        }

        void printQRCode(const std::string& text)
        {
        // Absent if an architecture inlined qrcodegen.h (faust -i) under a condition that excluded it
        #ifdef qrcodegen_h
            uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
            uint8_t buffer[qrcodegen_BUFFER_LEN_MAX];
            if (!qrcodegen_encodeText(text.c_str(), buffer, qrcode, qrcodegen_Ecc_LOW,
                                      qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true)) return;
            int size = qrcodegen_getSize(qrcode);
            // Two modules per character (upper and lower half blocks), a quiet zone of 2
            for (int y = -2; y < size + 2; y += 2) {
                std::string line;
                for (int x = -2; x < size + 2; x++) {
                    bool top = qrcodegen_getModule(qrcode, x, y);
                    bool bottom = qrcodegen_getModule(qrcode, x, y + 1);
                    // Dark modules drawn as spaces on a light block: reads on dark and light terminals
                    if (top && bottom) line += " ";
                    else if (top) line += "▄";
                    else if (bottom) line += "▀";
                    else line += "█";
                }
                std::cout << line << std::endl;
            }
        #endif
        }

        // Connect to the relay and announce the room; false (and a reason) if refused
        bool connectRelay(RemoteSocket& socket, std::string& error)
        {
            std::string host, port, prefix;
            if (!RemoteSocket::parseURL(fServer, host, port, prefix, error)) return false;
            if (!socket.connect(host, port, prefix + "/relay/" + encode(fRoom), error)) return false;
            socket.sendText("{\"token\":" + RemoteJSON::quote(fToken) + ",\"role\":\"host\",\"id\":\"host\"}");
            std::string answer;
            if (socket.receive(answer, 10000) != RemoteSocket::kMessage || answer != "ok") {
                error = "the relay refused the room (taken with another token?)";
                socket.close();
                return false;
            }
            return true;
        }

        void loop()
        {
            RemoteSocket socket;
            RemoteHost host(this, fOptions, [&socket](const std::string& text) { socket.sendText(text); });
            host.fOnJoin = [](const std::string& id) { std::cerr << "RemoteUI: remote control " << id << " joined" << std::endl; };
            host.fOnLeave = [](const std::string& id) { std::cerr << "RemoteUI: remote control " << id << " left" << std::endl; };
            const double period = 1000.0 / fOptions.fOutputRate;
            auto now = []() {
                return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now().time_since_epoch()).count();
            };
            double nextTick = now() + period;
            double nextAttempt = 0;
            while (fRunning) {
                if (!socket.isOpen()) {
                    if (now() < nextAttempt) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(50));
                        continue;
                    }
                    std::string error;
                    if (connectRelay(socket, error)) {
                        host.relayOpened();
                        status("connected to " + fServer + ", room " + fRoom);
                    } else {
                        status(error + "; trying again");
                        nextAttempt = now() + 1000;
                        continue;
                    }
                }
                std::string text;
                int timeout = int(std::max(0.0, std::min(nextTick - now(), 50.0)));
                RemoteSocket::Result res = socket.receive(text, timeout);
                if (res == RemoteSocket::kMessage) {
                    host.receive(text);
                } else if (res == RemoteSocket::kClosed) {
                    host.relayClosed();
                    status("the relay connection closed; trying again");
                    nextAttempt = now() + 1000;
                    continue;
                }
                double t = now();
                if (t >= nextTick) {
                    host.tick();
                    nextTick += period;
                    if (nextTick < t) nextTick = t + period;
                }
            }
            if (socket.isOpen()) host.close("host closed");
            socket.close();
        }

    public:

        /**
         * @param name the application's name
         * @param dsp the DSP, whose JSON the phones receive (build this UI with
         *        the same DSP afterwards)
         */
        RemoteUI(const char* name, ::dsp* dsp, int argc, char* argv[])
        :fName(name), fHasAcc(false), fHasGyr(false), fRunning(false)
        {
            JSONUI json(name, "", dsp->getNumInputs(), dsp->getNumOutputs());
            dsp->buildUserInterface(&json);
            dsp->metadata(&json);
            fJSON = json.JSON(true);
            fServer = option(argc, argv, "-remote", "");
            fOrigin = option(argc, argv, "-remote-origin", httpOrigin(fServer));
            fRoom = option(argc, argv, "-remote-room", RemoteHash::randomHex(8));
            fToken = option(argc, argv, "-remote-token", RemoteHash::randomHex(16));
            fOptions.fToken = fToken;
        }

        virtual ~RemoteUI() { stop(); }

        /** Where a polyphonic DSP and MidiUI take their MIDI from: the phones' MIDI goes there too. */
        template <typename MIDI_HANDLER>
        void setMidiHandler(MIDI_HANDLER* handler)
        {
            fMidi = [handler](const std::vector<int>& data) {
                int type = data[0] & 0xF0;
                int channel = data[0] & 0x0F;
                if (data.size() == 2) handler->handleData1(0.0, type, channel, data[1]);
                else handler->handleData2(0.0, type, channel, data[1], data[2]);
            };
        }

        /** Or any function that takes a MIDI channel message. */
        void setMidiFunction(std::function<void(const std::vector<int>&)> midi) { fMidi = midi; }

        /** The number of active voices of a polyphonic DSP, shown on the phones. */
        void setVoiceCounter(std::function<int()> voices) { fVoices = voices; }

        /** The link phones open, with the room and the token in its fragment (never sent to a server). */
        std::string getLink() const
        {
            return fOrigin + "/remote/index.html#room=" + encode(fRoom) + "&token=" + encode(fToken);
        }

        /** Start the network thread; false without -remote, or with an address that cannot work. */
        bool run()
        {
            if (fServer.empty()) return false;
            std::string host, port, prefix, error;
            if (!RemoteSocket::parseURL(fServer, host, port, prefix, error)) {
                std::cerr << "RemoteUI: " << error << std::endl;
                return false;
            }
            if (fRunning) return true;
            collect();
            std::cout << "Remote control: " << getLink() << std::endl;
            printQRCode(getLink());
            fRunning = true;
            fThread = std::thread([this]() { loop(); });
            return true;
        }

        /** Say goodbye to the phones, release what they held, and stop. */
        void stop()
        {
            if (!fRunning) return;
            fRunning = false;
            if (fThread.joinable()) fThread.join();
        }

        // ---- RemoteTarget, called from the network thread

        std::string getRemoteJSON() { return fJSON; }
        const std::vector<RemoteInput>& getRemoteInputs() { return fInputs; }
        const std::vector<RemoteOutput>& getRemoteOutputs() { return fOutputs; }
        double getRemoteInput(int i) { return getParamValue(fInputItems[i]); }
        void setRemoteInput(int i, double value) { setParamValue(fInputItems[i], FAUSTFLOAT(value)); }
        double getRemoteOutput(int k) { return getParamValue(fOutputItems[k]); }
        bool hasRemoteAcc() { return fHasAcc; }
        bool hasRemoteGyr() { return fHasGyr; }
        void propagateRemoteAcc(double x, double y, double z)
        {
            propagateAcc(0, x);
            propagateAcc(1, y);
            propagateAcc(2, z);
        }
        void propagateRemoteGyr(double alpha, double beta, double gamma)
        {
            propagateGyr(0, alpha);
            propagateGyr(1, beta);
            propagateGyr(2, gamma);
        }
        void remoteMidi(const std::vector<int>& data) { if (fMidi) fMidi(data); }
        int getRemoteVoices() { return fVoices ? fVoices() : -1; }
        bool remoteFloatValues() { return sizeof(FAUSTFLOAT) == sizeof(float); }
};

#endif
/**************************  END  RemoteUI.h **************************/

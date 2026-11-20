/************************** BEGIN RemoteSocket.h ***************************
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

#ifndef __RemoteSocket__
#define __RemoteSocket__

/*
 What RemoteUI needs from the network, with no dependency: a minimal
 WebSocket client (RFC 6455) on plain sockets, and the hashes and encodings
 around it (SHA-1 and base64 for the handshake, SHA-256 for the `hash` of the
 remote control protocol, random identifiers).

 Plain `ws://` only: RemoteUI reaches the relay of faust-remote-server
 through its `-host-port`, a plain listener on 127.0.0.1, so that no TLS
 library is needed. Blocking sockets, used from a single thread.
*/

#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <vector>
#include <random>
#include <chrono>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#ifdef _MSC_VER
#pragma comment(lib, "ws2_32.lib")
#endif
typedef SOCKET remote_socket_t;
#define REMOTE_INVALID_SOCKET INVALID_SOCKET
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <unistd.h>
typedef int remote_socket_t;
#define REMOTE_INVALID_SOCKET (-1)
#endif

// ------------------------------------------------------------------ hashes

struct RemoteHash {

    static uint32_t rotl(uint32_t x, int n) { return (x << n) | (x >> (32 - n)); }
    static uint32_t rotr(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }

    // Message padded to a multiple of 64 bytes, its length in bits at the end (big endian)
    static std::vector<uint8_t> pad(const std::string& data)
    {
        std::vector<uint8_t> bytes(data.begin(), data.end());
        uint64_t bits = uint64_t(data.size()) * 8;
        bytes.push_back(0x80);
        while (bytes.size() % 64 != 56) bytes.push_back(0);
        for (int i = 7; i >= 0; i--) bytes.push_back(uint8_t(bits >> (8 * i)));
        return bytes;
    }

    static std::string sha1(const std::string& data)
    {
        uint32_t h[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
        std::vector<uint8_t> bytes = pad(data);
        for (size_t chunk = 0; chunk < bytes.size(); chunk += 64) {
            uint32_t w[80];
            for (int i = 0; i < 16; i++) {
                const uint8_t* b = &bytes[chunk + 4 * i];
                w[i] = (uint32_t(b[0]) << 24) | (uint32_t(b[1]) << 16) | (uint32_t(b[2]) << 8) | b[3];
            }
            for (int i = 16; i < 80; i++) w[i] = rotl(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
            uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4];
            for (int i = 0; i < 80; i++) {
                uint32_t f, k;
                if (i < 20) {
                    f = (b & c) | (~b & d);
                    k = 0x5A827999;
                } else if (i < 40) {
                    f = b ^ c ^ d;
                    k = 0x6ED9EBA1;
                } else if (i < 60) {
                    f = (b & c) | (b & d) | (c & d);
                    k = 0x8F1BBCDC;
                } else {
                    f = b ^ c ^ d;
                    k = 0xCA62C1D6;
                }
                uint32_t t = rotl(a, 5) + f + e + k + w[i];
                e = d;
                d = c;
                c = rotl(b, 30);
                b = a;
                a = t;
            }
            h[0] += a; h[1] += b; h[2] += c; h[3] += d; h[4] += e;
        }
        std::string digest;
        for (int i = 0; i < 5; i++) {
            for (int j = 3; j >= 0; j--) digest.push_back(char(h[i] >> (8 * j)));
        }
        return digest;
    }

    static std::string sha256(const std::string& data)
    {
        static const uint32_t k[64] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
        uint32_t h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                         0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
        std::vector<uint8_t> bytes = pad(data);
        for (size_t chunk = 0; chunk < bytes.size(); chunk += 64) {
            uint32_t w[64];
            for (int i = 0; i < 16; i++) {
                const uint8_t* b = &bytes[chunk + 4 * i];
                w[i] = (uint32_t(b[0]) << 24) | (uint32_t(b[1]) << 16) | (uint32_t(b[2]) << 8) | b[3];
            }
            for (int i = 16; i < 64; i++) {
                uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
                uint32_t s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
                w[i] = w[i - 16] + s0 + w[i - 7] + s1;
            }
            uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], hh = h[7];
            for (int i = 0; i < 64; i++) {
                uint32_t s1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
                uint32_t ch = (e & f) ^ (~e & g);
                uint32_t t1 = hh + s1 + ch + k[i] + w[i];
                uint32_t s0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
                uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
                uint32_t t2 = s0 + maj;
                hh = g; g = f; f = e; e = d + t1;
                d = c; c = b; b = a; a = t1 + t2;
            }
            h[0] += a; h[1] += b; h[2] += c; h[3] += d;
            h[4] += e; h[5] += f; h[6] += g; h[7] += hh;
        }
        std::string digest;
        for (int i = 0; i < 8; i++) {
            for (int j = 3; j >= 0; j--) digest.push_back(char(h[i] >> (8 * j)));
        }
        return digest;
    }

    static std::string hex(const std::string& bytes)
    {
        static const char* digits = "0123456789abcdef";
        std::string res;
        for (unsigned char c : bytes) {
            res.push_back(digits[c >> 4]);
            res.push_back(digits[c & 15]);
        }
        return res;
    }

    static std::string base64(const std::string& bytes)
    {
        static const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string res;
        size_t i = 0;
        for (; i + 2 < bytes.size(); i += 3) {
            uint32_t n = (uint32_t(uint8_t(bytes[i])) << 16) | (uint32_t(uint8_t(bytes[i + 1])) << 8) | uint8_t(bytes[i + 2]);
            res.push_back(table[(n >> 18) & 63]);
            res.push_back(table[(n >> 12) & 63]);
            res.push_back(table[(n >> 6) & 63]);
            res.push_back(table[n & 63]);
        }
        if (i + 1 == bytes.size()) {
            uint32_t n = uint32_t(uint8_t(bytes[i])) << 16;
            res.push_back(table[(n >> 18) & 63]);
            res.push_back(table[(n >> 12) & 63]);
            res += "==";
        } else if (i + 2 == bytes.size()) {
            uint32_t n = (uint32_t(uint8_t(bytes[i])) << 16) | (uint32_t(uint8_t(bytes[i + 1])) << 8);
            res.push_back(table[(n >> 18) & 63]);
            res.push_back(table[(n >> 12) & 63]);
            res.push_back(table[(n >> 6) & 63]);
            res.push_back('=');
        }
        return res;
    }

    /**
     * Random bytes from std::random_device, which reads the system's
     * source (/dev/urandom, arc4random, RtlGenRandom) on the platforms
     * Faust targets. Used for the pairing token: it must not be guessable.
     */
    static std::string randomBytes(size_t count)
    {
        std::random_device device;
        std::string res;
        while (res.size() < count) {
            uint32_t r = device();
            for (int i = 0; i < 4 && res.size() < count; i++) res.push_back(char(r >> (8 * i)));
        }
        return res;
    }

    static std::string randomHex(size_t bytes) { return hex(randomBytes(bytes)); }
};

// --------------------------------------------------------------- WebSocket

/**
 * A WebSocket client on a blocking socket, for one thread: `connect`, then
 * `sendText` and `receive` (which waits at most the given time). Text
 * messages only; pings are answered, binary messages ignored.
 */
class RemoteSocket {

    public:

        enum Result { kMessage, kTimeout, kClosed };

    private:

        remote_socket_t fSocket;
        std::string fBuffer;            // bytes received, not yet parsed
        std::string fFragments;         // a fragmented message being assembled
        int fFragmentOpcode;
        bool fCloseSent;
        std::mt19937 fMask;             // mask keys: not a secret, the protocol needs no more

        static const size_t kMaxMessage = 16 * 1024 * 1024;

        static double nowMs()
        {
            return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now().time_since_epoch()).count();
        }

        static void closeSocket(remote_socket_t s)
        {
        #ifdef _WIN32
            closesocket(s);
        #else
            ::close(s);
        #endif
        }

        // Wait for data at most `timeout` ms: 1 readable, 0 timeout, -1 error
        int wait(int timeout)
        {
        #ifdef _WIN32
            WSAPOLLFD pfd;
            pfd.fd = fSocket;
            pfd.events = POLLRDNORM;
            pfd.revents = 0;
            int res = WSAPoll(&pfd, 1, timeout);
        #else
            struct pollfd pfd;
            pfd.fd = fSocket;
            pfd.events = POLLIN;
            pfd.revents = 0;
            int res = ::poll(&pfd, 1, timeout);
        #endif
            if (res < 0) return -1;
            return res > 0 ? 1 : 0;
        }

        // Read what is there into fBuffer: false when the connection ended
        bool readSome()
        {
            char chunk[16384];
        #ifdef _WIN32
            int n = ::recv(fSocket, chunk, sizeof(chunk), 0);
        #else
            ssize_t n = ::recv(fSocket, chunk, sizeof(chunk), 0);
        #endif
            if (n <= 0) return false;
            fBuffer.append(chunk, size_t(n));
            return true;
        }

        bool sendAll(const std::string& data)
        {
            size_t sent = 0;
            while (sent < data.size()) {
            #ifdef _WIN32
                int n = ::send(fSocket, data.data() + sent, int(data.size() - sent), 0);
            #elif defined(MSG_NOSIGNAL)
                ssize_t n = ::send(fSocket, data.data() + sent, data.size() - sent, MSG_NOSIGNAL);
            #else
                ssize_t n = ::send(fSocket, data.data() + sent, data.size() - sent, 0);
            #endif
                if (n <= 0) return false;
                sent += size_t(n);
            }
            return true;
        }

        // A frame from the client: always masked
        bool sendFrame(int opcode, const std::string& payload)
        {
            if (fSocket == REMOTE_INVALID_SOCKET) return false;
            std::string frame;
            frame.push_back(char(0x80 | opcode));
            uint64_t len = payload.size();
            if (len < 126) {
                frame.push_back(char(0x80 | len));
            } else if (len < 65536) {
                frame.push_back(char(0x80 | 126));
                frame.push_back(char(len >> 8));
                frame.push_back(char(len & 0xff));
            } else {
                frame.push_back(char(0x80 | 127));
                for (int i = 7; i >= 0; i--) frame.push_back(char(len >> (8 * i)));
            }
            uint32_t key = fMask();
            char mask[4] = {char(key), char(key >> 8), char(key >> 16), char(key >> 24)};
            frame.append(mask, 4);
            for (size_t i = 0; i < payload.size(); i++) frame.push_back(char(payload[i] ^ mask[i & 3]));
            return sendAll(frame);
        }

        /*
         Take one frame out of fBuffer, if a whole one is there.
         Returns 1 with a frame, 0 if more bytes are needed, -1 on a protocol error.
        */
        int takeFrame(bool& fin, int& opcode, std::string& payload)
        {
            if (fBuffer.size() < 2) return 0;
            const unsigned char* b = (const unsigned char*)fBuffer.data();
            fin = (b[0] & 0x80) != 0;
            opcode = b[0] & 0x0f;
            bool masked = (b[1] & 0x80) != 0;
            uint64_t len = b[1] & 0x7f;
            size_t header = 2;
            if (len == 126) {
                if (fBuffer.size() < 4) return 0;
                len = (uint64_t(b[2]) << 8) | b[3];
                header = 4;
            } else if (len == 127) {
                if (fBuffer.size() < 10) return 0;
                len = 0;
                for (int i = 0; i < 8; i++) len = (len << 8) | b[2 + i];
                header = 10;
            }
            // A server never masks its frames
            if (masked || len > kMaxMessage) return -1;
            if (fBuffer.size() < header + len) return 0;
            payload = fBuffer.substr(header, size_t(len));
            fBuffer.erase(0, header + size_t(len));
            return 1;
        }

        /*
         Process the frames in fBuffer until a whole text message is out.
         Returns kMessage, kTimeout (meaning: need more bytes) or kClosed.
        */
        Result process(std::string& text)
        {
            bool fin;
            int opcode;
            std::string payload;
            int res;
            while ((res = takeFrame(fin, opcode, payload)) == 1) {
                switch (opcode) {
                    case 0x0:   // continuation
                        if (fFragmentOpcode < 0 || fFragments.size() + payload.size() > kMaxMessage) {
                            close();
                            return kClosed;
                        }
                        fFragments += payload;
                        if (fin) {
                            int kind = fFragmentOpcode;
                            fFragmentOpcode = -1;
                            if (kind == 0x1) {
                                text.swap(fFragments);
                                fFragments.clear();
                                return kMessage;
                            }
                            fFragments.clear();
                        }
                        break;
                    case 0x1:   // text
                    case 0x2:   // binary, ignored once whole
                        if (fin) {
                            if (opcode == 0x1) {
                                text.swap(payload);
                                return kMessage;
                            }
                        } else {
                            fFragmentOpcode = opcode;
                            fFragments = payload;
                        }
                        break;
                    case 0x8:   // close
                        if (!fCloseSent) {
                            fCloseSent = true;
                            sendFrame(0x8, payload.substr(0, 2));
                        }
                        close();
                        return kClosed;
                    case 0x9:   // ping
                        sendFrame(0xA, payload);
                        break;
                    case 0xA:   // pong
                        break;
                    default:
                        close();
                        return kClosed;
                }
            }
            if (res < 0) {
                close();
                return kClosed;
            }
            return kTimeout;
        }

    public:

        RemoteSocket():fSocket(REMOTE_INVALID_SOCKET), fFragmentOpcode(-1), fCloseSent(false), fMask(std::random_device()())
        {
        #ifdef _WIN32
            WSADATA data;
            WSAStartup(MAKEWORD(2, 2), &data);
        #endif
        }

        virtual ~RemoteSocket()
        {
            close();
        #ifdef _WIN32
            WSACleanup();
        #endif
        }

        bool isOpen() const { return fSocket != REMOTE_INVALID_SOCKET; }

        /**
         * Split `ws://host:port/prefix` (or `http://`) into its parts. False
         * for anything else, `wss://` and `https://` included: no TLS here.
         */
        static bool parseURL(const std::string& url, std::string& host, std::string& port, std::string& prefix, std::string& error)
        {
            std::string rest;
            if (url.compare(0, 5, "ws://") == 0) {
                rest = url.substr(5);
            } else if (url.compare(0, 7, "http://") == 0) {
                rest = url.substr(7);
            } else if (url.compare(0, 6, "wss://") == 0 || url.compare(0, 8, "https://") == 0) {
                error = "no TLS here: use the plain port faust-remote-server opens with -host-port (ws://127.0.0.1:<port>)";
                return false;
            } else {
                error = "expected a ws:// URL, not " + url;
                return false;
            }
            size_t slash = rest.find('/');
            std::string authority = rest.substr(0, slash);
            prefix = (slash == std::string::npos) ? "" : rest.substr(slash);
            while (!prefix.empty() && prefix[prefix.size() - 1] == '/') prefix.erase(prefix.size() - 1);
            port = "80";
            if (!authority.empty() && authority[0] == '[') {
                size_t close = authority.find(']');
                if (close == std::string::npos) {
                    error = "bad address in " + url;
                    return false;
                }
                host = authority.substr(1, close - 1);
                if (close + 1 < authority.size() && authority[close + 1] == ':') port = authority.substr(close + 2);
            } else {
                size_t colon = authority.rfind(':');
                host = authority.substr(0, colon);
                if (colon != std::string::npos) port = authority.substr(colon + 1);
            }
            if (host.empty() || port.empty()) {
                error = "bad address in " + url;
                return false;
            }
            return true;
        }

        /**
         * Connect and do the WebSocket handshake for `path` on `host:port`.
         * No `Origin` header: this is not a browser page, and the host
         * listener of faust-remote-server refuses those that send one.
         */
        bool connect(const std::string& host, const std::string& port, const std::string& path, std::string& error, int timeout = 5000)
        {
            close();
            fBuffer.clear();
            fFragments.clear();
            fFragmentOpcode = -1;
            fCloseSent = false;

            struct addrinfo hints;
            memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_STREAM;
            struct addrinfo* list = nullptr;
            if (getaddrinfo(host.c_str(), port.c_str(), &hints, &list) != 0 || !list) {
                error = "cannot resolve " + host;
                return false;
            }
            for (struct addrinfo* ai = list; ai; ai = ai->ai_next) {
                remote_socket_t s = ::socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
                if (s == REMOTE_INVALID_SOCKET) continue;
                if (::connect(s, ai->ai_addr, (int)ai->ai_addrlen) == 0) {
                    fSocket = s;
                    break;
                }
                closeSocket(s);
            }
            freeaddrinfo(list);
            if (fSocket == REMOTE_INVALID_SOCKET) {
                error = "cannot connect to " + host + ":" + port;
                return false;
            }
            int one = 1;
            setsockopt(fSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&one, sizeof(one));
        #if !defined(_WIN32) && defined(SO_NOSIGPIPE)
            setsockopt(fSocket, SOL_SOCKET, SO_NOSIGPIPE, &one, sizeof(one));
        #endif

            std::string key = RemoteHash::base64(RemoteHash::randomBytes(16));
            std::string request =
                "GET " + path + " HTTP/1.1\r\n"
                "Host: " + (host.find(':') != std::string::npos ? "[" + host + "]" : host) + ":" + port + "\r\n"
                "Upgrade: websocket\r\n"
                "Connection: Upgrade\r\n"
                "Sec-WebSocket-Key: " + key + "\r\n"
                "Sec-WebSocket-Version: 13\r\n\r\n";
            if (!sendAll(request)) {
                error = "cannot send the handshake";
                close();
                return false;
            }
            double deadline = nowMs() + timeout;
            size_t end;
            while ((end = fBuffer.find("\r\n\r\n")) == std::string::npos) {
                int left = int(deadline - nowMs());
                if (left <= 0 || wait(left) <= 0 || !readSome() || fBuffer.size() > 16384) {
                    error = "no handshake answer";
                    close();
                    return false;
                }
            }
            std::string head = fBuffer.substr(0, end);
            fBuffer.erase(0, end + 4);
            if (head.compare(0, 12, "HTTP/1.1 101") != 0) {
                error = "refused: " + head.substr(0, head.find("\r\n"));
                close();
                return false;
            }
            // The answer must prove the server read our key
            std::string expected = RemoteHash::base64(RemoteHash::sha1(key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"));
            std::string lower = head;
            for (size_t i = 0; i < lower.size(); i++) lower[i] = char(tolower((unsigned char)lower[i]));
            size_t at = lower.find("\r\nsec-websocket-accept:");
            if (at == std::string::npos) {
                error = "handshake answer without Sec-WebSocket-Accept";
                close();
                return false;
            }
            size_t start = at + strlen("\r\nsec-websocket-accept:");
            size_t stop = head.find("\r\n", start);
            std::string accept = head.substr(start, stop == std::string::npos ? std::string::npos : stop - start);
            accept.erase(0, accept.find_first_not_of(" \t"));
            accept.erase(accept.find_last_not_of(" \t") + 1);
            if (accept != expected) {
                error = "wrong Sec-WebSocket-Accept";
                close();
                return false;
            }
            return true;
        }

        bool sendText(const std::string& text) { return sendFrame(0x1, text); }

        /**
         * The next text message, waiting at most `timeout` ms: kMessage
         * (in `text`), kTimeout, or kClosed once the connection is gone.
         */
        Result receive(std::string& text, int timeout)
        {
            if (fSocket == REMOTE_INVALID_SOCKET) return kClosed;
            double deadline = nowMs() + timeout;
            while (true) {
                Result res = process(text);
                if (res != kTimeout) return res;
                int left = int(deadline - nowMs());
                if (left < 0) left = 0;
                int ready = wait(left);
                if (ready < 0) {
                    close();
                    return kClosed;
                }
                if (ready == 0) return kTimeout;
                if (!readSome()) {
                    close();
                    return kClosed;
                }
            }
        }

        void close()
        {
            if (fSocket == REMOTE_INVALID_SOCKET) return;
            if (!fCloseSent) {
                fCloseSent = true;
                sendFrame(0x8, std::string("\x03\xe8", 2));   // 1000, normal closure
            }
            closeSocket(fSocket);
            fSocket = REMOTE_INVALID_SOCKET;
        }
};

#endif
/**************************  END  RemoteSocket.h **************************/

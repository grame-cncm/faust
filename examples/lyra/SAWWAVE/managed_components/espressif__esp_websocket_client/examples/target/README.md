# Websocket Sample application

This example will shows how to set up and communicate over a websocket.

## How to Use Example

### Hardware Required

This example can be executed on any ESP32 board, the only required interface is WiFi and connection to internet or a local server.

### Configure the project

* Open the project configuration menu (`idf.py menuconfig`)
* Configure Wi-Fi or Ethernet under "Example Connection Configuration" menu.
* Configure the websocket endpoint URI under "Example Configuration", if "WEBSOCKET_URI_FROM_STDIN" is selected then the example application will connect to the URI it reads from stdin (used for testing)
* To test a WebSocket client example over TLS, please enable one of the following configurations: `CONFIG_WS_OVER_TLS_MUTUAL_AUTH` or `CONFIG_WS_OVER_TLS_SERVER_AUTH`. See the sections below for more details.

### Server Certificate Verification

* Mutual Authentication: When `CONFIG_WS_OVER_TLS_MUTUAL_AUTH=y` is enabled, it's essential to provide valid certificates for both the server and client.
  This ensures a secure two-way verification process.
* Server-Only Authentication: To perform verification of the server's certificate only (without requiring a client certificate), set `CONFIG_WS_OVER_TLS_SERVER_AUTH=y`.
  This method skips client certificate verification.
* Example below demonstrates how to generate a new self signed certificates for the server and client using the OpenSSL command line tool

Please note: This example represents an extremely simplified approach to generating self-signed certificates/keys with a single common CA, devoid of CN checks, lacking password protection, and featuring hardcoded key sizes and types. It is intended solely for testing purposes.
In the outlined steps, we are omitting the configuration of the CN (Common Name) field due to the context of a testing environment. However, it's important to recognize that the CN field is a critical element of SSL/TLS certificates, significantly influencing the security and efficacy of HTTPS communications. This field facilitates the verification of a website's identity, enhancing trust and security in web interactions. In practical deployments beyond testing scenarios, ensuring the CN field is accurately set is paramount for maintaining the integrity and reliability of secure communications

### Generating a self signed Certificates with OpenSSL
* The example below outlines the process for creating new certificates for both the server and client using OpenSSL, a widely-used command line tool for implementing TLS protocol:

```
Generate the CA's Private Key;
openssl genrsa -out ca_key.pem 2048

Create the CA's Certificate
openssl req -new -x509 -days 3650 -key ca_key.pem -out ca_cert.pem

Generate the Server's Private Key
openssl genrsa -out server_key.pem 2048

Generate a Certificate Signing Request (CSR) for the Server
openssl req -new -key server_key.pem -out server_csr.pem

Sign the Server's CSR with the CA's Certificate
openssl x509 -req -days 3650 -in server_csr.pem -CA ca_cert.pem -CAkey ca_key.pem -CAcreateserial -out server_cert.pem

Generate the Client's Private Key
openssl genrsa -out client_key.pem 2048

Generate a Certificate Signing Request (CSR) for the Client
openssl req -new -key client_key.pem -out client_csr.pem

Sign the Client's CSR with the CA's Certificate
openssl x509 -req -days 3650 -in client_csr.pem -CA ca_cert.pem -CAkey ca_key.pem -CAcreateserial -out client_cert.pem

```

Expiry time and metadata fields can be adjusted in the invocation.

Please see the openssl man pages (man openssl) for more details.

It is **strongly recommended** to not reuse the example certificate in your application;
it is included only for demonstration.

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.

## Example Output

```
I (482) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFUSE
I (2492) example_connect: Ethernet Link Up
I (4472) tcpip_adapter: eth ip: 192.168.2.137, mask: 255.255.255.0, gw: 192.168.2.2
I (4472) example_connect: Connected to Ethernet
I (4472) example_connect: IPv4 address: 192.168.2.137
I (4472) example_connect: IPv6 address: fe80:0000:0000:0000:bedd:c2ff:fed4:a92b
I (4482) WEBSOCKET: Connecting to ws://echo.websocket.events...
I (5012) WEBSOCKET: WEBSOCKET_EVENT_CONNECTED
I (5492) WEBSOCKET: Sending hello 0000
I (6052) WEBSOCKET: WEBSOCKET_EVENT_DATA
W (6052) WEBSOCKET: Received=hello 0000

I (6492) WEBSOCKET: Sending hello 0001
I (7052) WEBSOCKET: WEBSOCKET_EVENT_DATA
W (7052) WEBSOCKET: Received=hello 0001

I (7492) WEBSOCKET: Sending hello 0002
I (8082) WEBSOCKET: WEBSOCKET_EVENT_DATA
W (8082) WEBSOCKET: Received=hello 0002

I (8492) WEBSOCKET: Sending hello 0003
I (9152) WEBSOCKET: WEBSOCKET_EVENT_DATA
W (9162) WEBSOCKET: Received=hello 0003

```


## Python Flask echo server

By default, the `ws://echo.websocket.events` endpoint is used. You can setup a Python websocket echo server locally and try the `ws://<your-ip>:5000` endpoint. To do this, install Flask-sock Python package

```
pip install flask-sock
```

and start a Flask websocket echo server locally by executing the following Python code:

```python
from flask import Flask
from flask_sock import Sock

app = Flask(__name__)
sock = Sock(app)


@sock.route('/')
def echo(ws):
    while True:
        data = ws.receive()
        ws.send(data)


if __name__ == '__main__':
    # To run your Flask + WebSocket server in production you can use Gunicorn:
    # gunicorn -b 0.0.0.0:5000 --workers 4 --threads 100 module:app
    app.run(host="0.0.0.0", debug=True)
```

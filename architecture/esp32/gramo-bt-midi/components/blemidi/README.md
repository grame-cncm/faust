# BLE MIDI DRIVER

This is a rudimentary Bluetooth Low Energy MIDI driver for the Gramophone. It implements both a GATT server and a GATT client so that the Gramophone can take these 2 different roles. It was inspired from <https://github.com/midibox/esp32-idf-blemidi> by Thorsten Klose (tk@midibox.org).

## Known Issue

* Since the connection configuration is not secured, some devices such as smartphones and boring operating systems (i.e., Windows and macOS, not Linux) will not allow to connect to the current server. Any other device will work though (e.g., MIDI keyboard, etc.).

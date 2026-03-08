import json
import sys 
import os

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

project_dir = sys.argv[1]
patchsm = sys.argv[2]
midi_uart = sys.argv[3]
rx_pin = sys.argv[4]
tx_pin = sys.argv[5]

chip = "seed"
if(patchsm == "true" ):
    chip = "patchsm"

filepath = os.path.join(project_dir, "config.json")

midi_type = "usb"
if(midi_uart == "true"):
    midi_type = "uart"

midi_entry = {
    "type": midi_type
}

if(rx_pin > "0"):
    midi_entry["rx_pin"] = rx_pin
if(tx_pin > "0"):
    midi_entry["tx_pin"] = tx_pin


data = {
    "name": "custom",
    "chip": chip,
    "midi": [midi_entry],
    "ui": [
        {
        }
    ]
}

json_str = json.dumps(data, indent=4)
with  open(filepath, "w") as fp:
    fp.write(json_str)

print(f"JSON_CONFIG={filepath}")



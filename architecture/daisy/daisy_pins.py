# daisy_pins.py
#
# Daisy pin label -> physical STM32 pin, for cross-feature pin-conflict checking.
#
# The point is to resolve ALIASES to the same physical pin so a conflict guard
# catches e.g. Seed [adc:A0] vs [pwm:D15] (both PC0), or Seed [dac:A7] vs
# [adc:D22] (both PA5). Verified against libDaisy/src/daisy_seed.h and
# daisy_patch_sm.h. Physical pins use a "P<port><idx>" string (e.g. "PB12").
#
# Patch SM PORTX pins (power / GND / audio, all Pin(PORTX,0)) are omitted: they
# are not usable GPIO and share a placeholder address that would false-collide.

# Daisy Seed: D0..D32 physical, plus the A0..A13 analog aliases (A0 == D15, ...).
_SEED = {
    "D0": "PB12",  "D1": "PC11", "D2": "PC10", "D3": "PC9",  "D4": "PC8",
    "D5": "PD2",   "D6": "PC12", "D7": "PG10", "D8": "PG11", "D9": "PB4",
    "D10": "PB5",  "D11": "PB8", "D12": "PB9", "D13": "PB6", "D14": "PB7",
    "D15": "PC0",  "D16": "PA3", "D17": "PB1", "D18": "PA7", "D19": "PA6",
    "D20": "PC1",  "D21": "PC4", "D22": "PA5", "D23": "PA4", "D24": "PA1",
    "D25": "PA0",  "D26": "PD11","D27": "PG9", "D28": "PA2", "D29": "PB14",
    "D30": "PB15", "D31": "PC2", "D32": "PC3",
    # Analog aliases (same physical pin as the D-name)
    "A0": "PC0",  "A1": "PA3",  "A2": "PB1",  "A3": "PA7",  "A4": "PA6",
    "A5": "PC1",  "A6": "PC4",  "A7": "PA5",  "A8": "PA4",  "A9": "PA1",
    "A10": "PA0", "A11": "PA2", "A12": "PC2", "A13": "PC3",
}

# Daisy Patch SM (PORTX power/audio pins omitted).
_PATCHSM = {
    "A2": "PA1",  "A3": "PA0",  "A8": "PB14", "A9": "PB15",
    "B5": "PC14", "B6": "PC13", "B7": "PB8",  "B8": "PB9",
    "B9": "PG14", "B10": "PG13",
    "C1": "PA5",  "C2": "PA7",  "C3": "PA2",  "C4": "PA6",  "C5": "PA3",
    "C6": "PB1",  "C7": "PC4",  "C8": "PC0",  "C9": "PC1",  "C10": "PA4",
    "D1": "PB4",  "D2": "PC11", "D3": "PC10", "D4": "PC9",  "D5": "PC8",
    "D6": "PC12", "D7": "PD2",  "D8": "PC2",  "D9": "PC3",  "D10": "PD3",
}

_TABLES = {"seed": _SEED, "patchsm": _PATCHSM}


def physical(chip, label):
    """Canonical physical pin ('PB12'...) for a board pin label, or None if the
    label is unknown (the caller can then fall back to comparing the label)."""
    return _TABLES.get(chip, {}).get(str(label))

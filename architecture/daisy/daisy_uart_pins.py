# daisy_uart_pins.py
#
# Authoritative Daisy pin -> UART resolution for faust2daisy.
#
# A Faust control declares its UART pin by board label, e.g. hslider("amp[rx:D14]")
# or "amp[tx:D13]" on the Seed, "amp[rx:A2]" on the Patch SM. The board silkscreen
# naming is unreliable (the Seed names the USART index; the Patch SM just says
# "UART RX/TX", and libDaisy even mislabels A2/A3 as "UART1" when they are really
# UART4). So we resolve every pin the only reliable way: board label -> physical
# MCU pin -> (USART peripheral, alternate-function, DMA request), using the
# STM32H7 alternate-function table.
#
# The values below are extracted from libDaisy (not guessed):
#   * physical pin per label : src/daisy_seed.h (daisy::seed::Dx),
#                              src/daisy_patch_sm.h (daisy::patch_sm::Ax)
#   * pin -> (peripheral, AF) : src/per/uart.cpp  (usartN_pins_tx/rx tables)
#   * peripheral -> DMA req   : src/per/uart.cpp  (SetDmaPeripheral)
#
# These feed DaisyUartListener::ChannelConfig (daisy_uart_listener.hpp), which
# takes raw HAL identifiers; the parser emits the strings below verbatim. The
# listener stays board-agnostic -- all board difference lives here.
#
# NOTE on shared pins: a few physical pins expose more than one UART function
# (e.g. Seed D2/PC10 = USART3_TX AF7 *or* UART4_TX AF8). We pick the canonical
# one (the lower-numbered AF7 USART, matching the Seed pinout) and record the
# alternate in 'alts'. If a DSP ever needs the alternate, the metadata would have
# to name the peripheral explicitly; for the standard pinout this never arises.
#
# LPUART1 is intentionally excluded: it is driven by BDMA, not DMA1/DMA2, so it
# is incompatible with DaisyUartListener's DMA1/DMA2 streams.


def _e(periph, af, port, pin_idx, dma_req, alts=None):
    """One resolution entry, holding the C++ identifiers the parser emits."""
    return {
        "periph":   periph,                  # human/diagnostic name
        "instance": periph,                  # HAL USART_TypeDef* name (== periph)
        "af":       af,                       # GPIO_AFx_xxx
        "port":     port,                     # GPIO_TypeDef* name
        "pin":      "GPIO_PIN_%d" % pin_idx,  # GPIO_PIN_n
        "dma_req":  dma_req,                  # DMA_REQUEST_xxx_RX / _TX
        "alts":     alts or [],
    }


# ----------------------------------------------------------------------------
# Daisy Seed (daisy::seed::Dx). Only pins the official Daisy Seed pinout
# documents as a UART function are listed (verified against
# libDaisy/doc/Daisy_Seed_Rev4_Pinout.csv). Pins whose only UART role is a deep
# alternate behind a non-UART primary (USB / SPI1 / SAI2 -> D0, D9, D10, D24,
# D25, D27, D28) are intentionally excluded. [brackets] note a shared function.
#
# Usable bidirectional pairs:
#   USART1: rx D14 / tx D13           (also rx D30 / tx D29 on the USB pins, AF4)
#   USART3: rx D1  / tx D2
#   UART4 : rx D11 / tx D12
#   UART5 : rx D5  / tx D6
#   USART2: rx D16                     (no tx pin documented)
# ----------------------------------------------------------------------------
SEED_UART_RX = {
    "D1":  _e("USART3", "GPIO_AF7_USART3",  "GPIOC", 11, "DMA_REQUEST_USART3_RX",  # [SDMMC1_D3]
              alts=["UART4_RX (AF8)"]),
    "D5":  _e("UART5",  "GPIO_AF8_UART5",   "GPIOD",  2, "DMA_REQUEST_UART5_RX"),  # [SDMMC1_CMD]
    "D11": _e("UART4",  "GPIO_AF8_UART4",   "GPIOB",  8, "DMA_REQUEST_UART4_RX"),  # [I2C1_SCL]
    "D14": _e("USART1", "GPIO_AF7_USART1",  "GPIOB",  7, "DMA_REQUEST_USART1_RX"), # dedicated UART Rx
    "D16": _e("USART2", "GPIO_AF7_USART2",  "GPIOA",  3, "DMA_REQUEST_USART2_RX"), # [ADC]
    "D30": _e("USART1", "GPIO_AF4_USART1",  "GPIOB", 15, "DMA_REQUEST_USART1_RX"), # [USB D+]
}

SEED_UART_TX = {
    "D2":  _e("USART3", "GPIO_AF7_USART3",  "GPIOC", 10, "DMA_REQUEST_USART3_TX",  # [SDMMC1_D2]
              alts=["UART4_TX (AF8)"]),
    "D6":  _e("UART5",  "GPIO_AF8_UART5",   "GPIOC", 12, "DMA_REQUEST_UART5_TX"),  # [SDMMC1_CK]
    "D12": _e("UART4",  "GPIO_AF8_UART4",   "GPIOB",  9, "DMA_REQUEST_UART4_TX"),  # [I2C1_SDA]
    "D13": _e("USART1", "GPIO_AF7_USART1",  "GPIOB",  6, "DMA_REQUEST_USART1_TX"), # dedicated UART Tx
    "D29": _e("USART1", "GPIO_AF4_USART1",  "GPIOB", 14, "DMA_REQUEST_USART1_TX"), # [USB D-]
}

# ----------------------------------------------------------------------------
# Daisy Patch SM (daisy::patch_sm::Ax/Bx/Dx). Only pins the official Patch SM
# pinout documents as a UART function. A2/A3 are the dedicated UART pins; B7/B8
# and D2/D3/D6/D7 expose UART alongside their primary function (noted in
# [brackets]). C3/C5 (CV In, USART2) and D1 (SPI2 CS, UART7) are NOT shown as
# UART on the official pinout and are excluded; so are A8/A9 (the USB D-/D+ pins).
#
# Usable bidirectional pairs:
#   UART4 : rx A2|B7 / tx A3|B8        (also rx D2 / tx D3 via AF8)
#   USART3: rx D2    / tx D3
#   UART5 : rx D7    / tx D6
# ----------------------------------------------------------------------------
PATCHSM_UART_RX = {
    "A2": _e("UART4",  "GPIO_AF8_UART4",  "GPIOA",  1, "DMA_REQUEST_UART4_RX"),   # dedicated UART Rx
    "B7": _e("UART4",  "GPIO_AF8_UART4",  "GPIOB",  8, "DMA_REQUEST_UART4_RX"),   # [I2C1 SCL]
    "D2": _e("USART3", "GPIO_AF7_USART3", "GPIOC", 11, "DMA_REQUEST_USART3_RX",   # [SDMMC D3]
             alts=["UART4_RX (AF8)"]),
    "D7": _e("UART5",  "GPIO_AF8_UART5",  "GPIOD",  2, "DMA_REQUEST_UART5_RX"),   # [SDMMC CMD]
}

PATCHSM_UART_TX = {
    "A3": _e("UART4",  "GPIO_AF8_UART4",  "GPIOA",  0, "DMA_REQUEST_UART4_TX"),   # dedicated UART Tx
    "B8": _e("UART4",  "GPIO_AF8_UART4",  "GPIOB",  9, "DMA_REQUEST_UART4_TX"),   # [I2C1 SDA]
    "D3": _e("USART3", "GPIO_AF7_USART3", "GPIOC", 10, "DMA_REQUEST_USART3_TX",   # [SDMMC D2]
             alts=["UART4_TX (AF8)"]),
    "D6": _e("UART5",  "GPIO_AF8_UART5",  "GPIOC", 12, "DMA_REQUEST_UART5_TX"),   # [SDMMC CK]
}

_TABLES = {
    "seed":    (SEED_UART_RX, SEED_UART_TX),
    "patchsm": (PATCHSM_UART_RX, PATCHSM_UART_TX),
}


def resolve_uart(chip, pin_label, direction):
    """Resolve (chip, pin_label, 'rx'|'tx') to a UART entry dict.

    Raises ValueError with the list of valid pins on failure, so the parser can
    surface a clear message instead of emitting a bad alternate-function.
    """
    if chip not in _TABLES:
        raise ValueError(
            "UART controls are only supported on 'seed' and 'patchsm' (got %r)"
            % chip)
    rx_tbl, tx_tbl = _TABLES[chip]
    if direction not in ("rx", "tx"):
        raise ValueError("UART direction must be 'rx' or 'tx' (got %r)" % direction)
    table = rx_tbl if direction == "rx" else tx_tbl
    if pin_label not in table:
        valid = ", ".join(sorted(table.keys()))
        raise ValueError(
            "%s is not a UART %s pin on %s. Valid %s pins: %s"
            % (pin_label, direction, chip, direction, valid))
    return table[pin_label]


def same_peripheral(rx_entry, tx_entry):
    """True if an rx/tx pair belongs to one USART (required for one channel)."""
    return rx_entry["instance"] == tx_entry["instance"]

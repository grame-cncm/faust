# daisy_pwm_pin.py
#
# Daisy pin -> hardware-PWM (timer channel) resolution for faust2daisy.
#
# Hardware PWM on the Daisy uses timers TIM3, TIM4, TIM5 (libDaisy PWMHandle),
# 4 channels each. A pin is "PWM-capable" iff its AF2 alternate function is a
# TIM3/4/5 channel -- fixed silicon, identical on Seed and Patch SM, only the
# pin labels differ. The alternate function is ALWAYS AF2 and is applied by
# libDaisy internally, so it is not stored here.
#
# Sources (not guessed):
#   * Seed pin/timer/channel table : libDaisy/src/per/pwm.h  (documents the
#     Daisy Seed D-names per channel) + STM32H7 AF2 table.
#   * Patch SM physical pins        : libDaisy/src/daisy_patch_sm.h, cross-
#     referenced with the same TIM3/4/5 AF2 channel pins.
#
# Usage: the parser resolves [pwm:<pin>] to {timer, channel} and emits a
#   PWMHandle::Config with .periph = PWMHandle::Config::Peripheral::TIM_x and
#   sets the matching channel's Channel::Config.pin to the Daisy pin constant.
#
# IMPORTANT constraints for the caller / parser:
#   * One (timer, channel) drives ONE pin -- reject two PWM controls that land
#     on the same timer+channel.
#   * All channels of a timer SHARE its prescaler/period (=> same PWM frequency
#     and resolution). Independent frequencies require different timers.
#   * Every pin here is shared with another function (noted in 'note'); the
#     parser should also reject a pin already used by ADC/DAC/serial/I2C/etc.
#   * TIM2 (System us-timer) and TIM6 (DAC in DMA mode) are used elsewhere;
#     TIM3/4/5 are otherwise free in faust2daisy.


def _e(timer, channel, phys, note=""):
    """One PWM resolution entry.

    timer   : "TIM_3" | "TIM_4" | "TIM_5"  (PWMHandle::Config::Peripheral::TIM_x)
    channel : 1..4                          (TIM channel on that timer)
    phys    : physical MCU pin, for reference
    note    : the pin's other (shared) function
    """
    return {"timer": timer, "channel": channel, "phys": phys, "note": note}


# ----------------------------------------------------------------------------
# Daisy Seed (daisy::seed::Dx). From pwm.h's documented channel pins.
# Several channels expose two pins; pick whichever is free.
#   TIM3: CH1 D19|D9   CH2 D18|D10   CH3 D4    CH4 D17|D3
#   TIM4: CH1 D13      CH2 D14       CH3 D11   CH4 D12
#   TIM5: CH1 D25      CH2 D24       CH3 D28   CH4 D16   (D16/D24/D25/D28 are the
#         analog/SAI2 pins; D24/D25/D28 are underside pads)
# ----------------------------------------------------------------------------
SEED_PWM = {
    "D3":  _e("TIM_3", 4, "PC9"),
    "D4":  _e("TIM_3", 3, "PC8"),
    "D9":  _e("TIM_3", 1, "PB4", "SPI1 MISO"),
    "D10": _e("TIM_3", 2, "PB5", "SPI1 MOSI"),
    "D11": _e("TIM_4", 3, "PB8", "I2C1 SCL"),
    "D12": _e("TIM_4", 4, "PB9", "I2C1 SDA"),
    "D13": _e("TIM_4", 1, "PB6", "USART1 TX"),
    "D14": _e("TIM_4", 2, "PB7", "USART1 RX"),
    "D16": _e("TIM_5", 4, "PA3", "ADC / USART2 RX"),
    "D17": _e("TIM_3", 4, "PB1", "ADC"),
    "D18": _e("TIM_3", 2, "PA7", "ADC / SPI1 MOSI"),
    "D19": _e("TIM_3", 1, "PA6", "ADC / SPI1 MISO"),
    "D24": _e("TIM_5", 2, "PA1", "underside pad (SAI2 / UART4)"),
    "D25": _e("TIM_5", 1, "PA0", "underside pad (SAI2 / UART4)"),
    "D28": _e("TIM_5", 3, "PA2", "underside pad (SAI2 / USART2)"),
}

# ----------------------------------------------------------------------------
# Daisy Patch SM (daisy::patch_sm::Ax/Bx/Cx/Dx). Every pin is shared.
#   TIM3: CH1 C4|D1   CH2 C2    CH3 D5    CH4 C6|D4
#   TIM4: CH1 -       CH2 -     CH3 B7    CH4 B8     (PB6/PB7 not broken out)
#   TIM5: CH1 A3      CH2 A2    CH3 C3    CH4 C5
# ----------------------------------------------------------------------------
PATCHSM_PWM = {
    "A2": _e("TIM_5", 2, "PA1", "UART Rx"),
    "A3": _e("TIM_5", 1, "PA0", "UART Tx"),
    "B7": _e("TIM_4", 3, "PB8", "I2C1 SCL"),
    "B8": _e("TIM_4", 4, "PB9", "I2C1 SDA"),
    "C2": _e("TIM_3", 2, "PA7", "CV In 4"),
    "C3": _e("TIM_5", 3, "PA2", "CV In 3"),
    "C4": _e("TIM_3", 1, "PA6", "CV In 2"),
    "C5": _e("TIM_5", 4, "PA3", "CV In 1"),
    "C6": _e("TIM_3", 4, "PB1", "CV In 5"),
    "D1": _e("TIM_3", 1, "PB4", "SPI2 CS"),
    "D4": _e("TIM_3", 4, "PC9", "SDMMC D1"),
    "D5": _e("TIM_3", 3, "PC8", "SDMMC D0"),
}

_TABLES = {
    "seed":    SEED_PWM,
    "patchsm": PATCHSM_PWM,
}


def resolve_pwm(chip, pin_label):
    """Resolve (chip, pin_label) to a PWM entry {timer, channel, phys, note}.

    Raises ValueError listing the valid pins on failure so the parser can
    surface a clear message.
    """
    if chip not in _TABLES:
        raise ValueError(
            "PWM is only supported on 'seed' and 'patchsm' (got %r)" % chip)
    table = _TABLES[chip]
    if pin_label not in table:
        valid = ", ".join(sorted(table.keys()))
        raise ValueError(
            "%s is not a hardware-PWM pin on %s. Valid PWM pins: %s"
            % (pin_label, chip, valid))
    return table[pin_label]


def timer_channel(entry):
    """(timer, channel) tuple -- handy for grouping/uniqueness checks."""
    return (entry["timer"], entry["channel"])

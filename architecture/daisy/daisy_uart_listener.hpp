#ifndef DAISY_UART_LISTENER_HPP
#define DAISY_UART_LISTENER_HPP
/************************** BEGIN daisy_uart_listener.hpp ****************
FAUST Architecture File - faust2daisy
Copyright (C) 2020-2024 GRAME, Centre National de Creation Musicale
This is free software; see the FAUST architecture license.
*************************************************************************/

// =============================================================================
// daisy_uart_listener.hpp
//
// Multi-channel, interrupt-free UART RX for Daisy, with fire-and-forget blocking
// TX. Lets several UARTs receive *concurrently* -- something libDaisy's
// UartHandler cannot do, because its DmaListenStart hardcodes DMA1_Stream5 and a
// single global "dma_active" flag (so only one circular RX at a time, shared by
// regular UART *and* UART-MIDI).
//
// HOW IT AVOIDS THAT, AND COEXISTS WITH libDaisy
// ----------------------------------------------
//   * Each channel runs its own circular DMA from the USART RDR into a ring
//     buffer, on one of the DMA streams libDaisy never uses:
//       DMA1_Stream7, DMA2_Stream5, DMA2_Stream6, DMA2_Stream7  (=> 4 channels)
//   * It is driven by NO interrupts: we start the DMA with HAL_DMA_Start (not
//     _IT) and set the USART DMAR bit by hand, then find new bytes by polling
//     the DMA's remaining-count register (NDTR) in Poll(). So there is no DMA or
//     USART NVIC use and no IRQ-handler symbols -> zero clash with libDaisy
//     (which strongly defines USARTx_IRQHandler and the stream IRQs it uses),
//     and the global dma_active_peripheral_ scheduler is never touched. libDaisy
//     MIDI-UART RX (Stream5) and all other DMA users keep running.
//
// TX
// --
// Transmit() is blocking (HAL_UART_Transmit). UART TX is fire-and-forget and
// bounded by byte-time, so blocking is safe and cannot stall on a missing
// reader. Do NOT also drive a UART this class owns with a separate libDaisy
// UartHandler -- two handles on one peripheral conflict. Use Transmit() here.
//
// RING BUFFER
// -----------
// Each channel's ring MUST live in DMA-accessible, non-cacheable memory
// (DMA_BUFFER_MEM_SECTION). DMA writes it in the background; non-cacheable means
// the CPU sees those writes without manual cache invalidation. Size the ring
// larger than the most you could receive between two Poll() calls.
//
// CONFIG
// ------
// ChannelConfig carries raw HAL identifiers (USART instance, DMA request, GPIO
// ports/pins/AF, baud). The faust2daisy generator already maps Faust pins to
// peripherals/pins, so it fills these in; for hand use, see the STM32H7
// datasheet / libDaisy's uart.cpp InitPins for the AF and DMA_REQUEST values.
//
// Requires the STM32 HAL in scope (include after daisy_seed.h) and C++17.
// =============================================================================

#include <cstddef>
#include <cstdint>

class DaisyUartListener
{
  public:
    // One free DMA stream per channel; libDaisy leaves exactly these four.
    static constexpr size_t kMaxChannels = 4;

    // Called from Poll() (main-loop context) with bytes newly arrived on a
    // channel. May be called twice in one Poll() when the ring wraps. Keep it
    // light; copy/parse, do not block.
    using RxCallback = void (*)(void* context, const uint8_t* data, size_t len);

    struct ChannelConfig
    {
        USART_TypeDef* instance     = nullptr; // USART1 .. UART8
        uint32_t       baud         = 115200;
        uint32_t       dmaRxRequest = 0;       // DMA_REQUEST_USARTx_RX

        // RX pin (required)
        GPIO_TypeDef* rxPort    = nullptr;
        uint16_t      rxPin     = 0; // GPIO_PIN_x
        uint8_t       rxAltFunc = 0; // GPIO_AFy_USARTx

        // TX pin (optional; leave txPort == nullptr for receive-only)
        GPIO_TypeDef* txPort    = nullptr;
        uint16_t      txPin     = 0;
        uint8_t       txAltFunc = 0;

        // Ring buffer in DMA_BUFFER_MEM_SECTION memory.
        uint8_t* ring     = nullptr;
        size_t   ringSize = 0;

        RxCallback onReceive = nullptr;
        void*      context   = nullptr;
    };

    // Configure a UART, start its circular RX DMA, and begin listening. Returns
    // false if all channels are in use or the config is incomplete.
    bool addChannel(const ChannelConfig& cfg)
    {
        if(channelCount_ >= kMaxChannels) return false;
        if(!cfg.instance) return false;
        const bool haveRx = (cfg.rxPort != nullptr) && (cfg.ring != nullptr)
                            && (cfg.ringSize > 0);
        if(!haveRx && cfg.txPort == nullptr) return false; // need RX and/or TX

        Channel& ch = channels_[channelCount_];
        ch.cfg      = cfg;
        ch.lastPos  = 0;

        if(haveRx) enableGpioClock(cfg.rxPort);
        if(cfg.txPort) enableGpioClock(cfg.txPort);
        enableUartClock(cfg.instance);

        // --- GPIO (push-pull AF) ---
        GPIO_InitTypeDef gpio = {};
        gpio.Mode  = GPIO_MODE_AF_PP;
        gpio.Pull  = GPIO_PULLUP;
        gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

        if(haveRx)
        {
            gpio.Pin       = cfg.rxPin;
            gpio.Alternate = cfg.rxAltFunc;
            HAL_GPIO_Init(cfg.rxPort, &gpio);
        }
        if(cfg.txPort)
        {
            gpio.Pin       = cfg.txPin;
            gpio.Alternate = cfg.txAltFunc;
            HAL_GPIO_Init(cfg.txPort, &gpio);
        }

        // --- USART (8N1) ---
        ch.huart.Instance        = cfg.instance;
        ch.huart.Init.BaudRate   = cfg.baud;
        ch.huart.Init.WordLength = UART_WORDLENGTH_8B;
        ch.huart.Init.StopBits   = UART_STOPBITS_1;
        ch.huart.Init.Parity     = UART_PARITY_NONE;
        if(haveRx && cfg.txPort) ch.huart.Init.Mode = UART_MODE_TX_RX;
        else if(haveRx)          ch.huart.Init.Mode = UART_MODE_RX;
        else                     ch.huart.Init.Mode = UART_MODE_TX;
        ch.huart.Init.HwFlowCtl      = UART_HWCONTROL_NONE;
        ch.huart.Init.OverSampling   = UART_OVERSAMPLING_16;
        ch.huart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
        ch.huart.Init.ClockPrescaler = UART_PRESCALER_DIV1;
        if(HAL_UART_Init(&ch.huart) != HAL_OK) return false;

        // --- RX: circular DMA, interrupt-free, on a libDaisy-unused stream ---
        if(haveRx)
        {
            __HAL_RCC_DMA1_CLK_ENABLE();
            __HAL_RCC_DMA2_CLK_ENABLE();
            ch.hdma.Instance                 = freeStream(channelCount_);
            ch.hdma.Init.Request             = cfg.dmaRxRequest;
            ch.hdma.Init.Direction           = DMA_PERIPH_TO_MEMORY;
            ch.hdma.Init.PeriphInc           = DMA_PINC_DISABLE;
            ch.hdma.Init.MemInc              = DMA_MINC_ENABLE;
            ch.hdma.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
            ch.hdma.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
            ch.hdma.Init.Mode                = DMA_CIRCULAR;
            ch.hdma.Init.Priority            = DMA_PRIORITY_HIGH;
            ch.hdma.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
            if(HAL_DMA_Init(&ch.hdma) != HAL_OK) return false;

            // Start the stream WITHOUT interrupts (HAL_DMA_Start, not _IT) and
            // turn on the USART's DMA-receive request by hand. From here the DMA
            // fills the ring continuously; we never get (or need) an interrupt.
            if(HAL_DMA_Start(&ch.hdma,
                             (uint32_t)&cfg.instance->RDR,
                             (uint32_t)cfg.ring,
                             (uint32_t)cfg.ringSize)
               != HAL_OK)
                return false;
            SET_BIT(cfg.instance->CR3, USART_CR3_DMAR);
        }

        ++channelCount_;
        return true;
    }

    // Drain every channel: deliver any bytes the DMA has written since the last
    // call. Call once per main-loop iteration. Cheap: one register read per
    // channel when idle.
    void poll()
    {
        for(size_t i = 0; i < channelCount_; ++i)
        {
            Channel& ch = channels_[i];
            // DMA write index = ringSize - remaining(NDTR)
            size_t pos = ch.cfg.ringSize - __HAL_DMA_GET_COUNTER(&ch.hdma);
            if(pos == ch.lastPos) continue;

            if(pos > ch.lastPos)
            {
                if(ch.cfg.onReceive)
                    ch.cfg.onReceive(ch.cfg.context,
                                     &ch.cfg.ring[ch.lastPos],
                                     pos - ch.lastPos);
            }
            else // wrapped: tail then head
            {
                if(ch.cfg.onReceive)
                {
                    ch.cfg.onReceive(ch.cfg.context,
                                     &ch.cfg.ring[ch.lastPos],
                                     ch.cfg.ringSize - ch.lastPos);
                    if(pos > 0)
                        ch.cfg.onReceive(ch.cfg.context, &ch.cfg.ring[0], pos);
                }
            }
            ch.lastPos = pos;
        }
    }

    // Blocking, fire-and-forget transmit on a channel that has a TX pin.
    bool transmit(size_t channel,
                  const uint8_t* data,
                  size_t         size,
                  uint32_t       timeoutMs = 100)
    {
        if(channel >= channelCount_ || !channels_[channel].cfg.txPort)
            return false;
        return HAL_UART_Transmit(&channels_[channel].huart,
                                 (uint8_t*)data,
                                 (uint16_t)size,
                                 timeoutMs)
               == HAL_OK;
    }

    size_t channelCount() const { return channelCount_; }

  private:
    struct Channel
    {
        ChannelConfig     cfg;
        UART_HandleTypeDef huart   = {};
        DMA_HandleTypeDef  hdma    = {};
        size_t             lastPos = 0;
    };

    Channel channels_[kMaxChannels];
    size_t  channelCount_ = 0;

    static DMA_Stream_TypeDef* freeStream(size_t idx)
    {
        switch(idx)
        {
            case 0: return DMA1_Stream7;
            case 1: return DMA2_Stream5;
            case 2: return DMA2_Stream6;
            default: return DMA2_Stream7;
        }
    }

    static void enableUartClock(USART_TypeDef* u)
    {
        if(u == USART1) __HAL_RCC_USART1_CLK_ENABLE();
        else if(u == USART2) __HAL_RCC_USART2_CLK_ENABLE();
        else if(u == USART3) __HAL_RCC_USART3_CLK_ENABLE();
        else if(u == UART4) __HAL_RCC_UART4_CLK_ENABLE();
        else if(u == UART5) __HAL_RCC_UART5_CLK_ENABLE();
        else if(u == USART6) __HAL_RCC_USART6_CLK_ENABLE();
        else if(u == UART7) __HAL_RCC_UART7_CLK_ENABLE();
        else if(u == UART8) __HAL_RCC_UART8_CLK_ENABLE();
    }

    static void enableGpioClock(GPIO_TypeDef* p)
    {
        if(p == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
        else if(p == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
        else if(p == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
        else if(p == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
        else if(p == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();
        else if(p == GPIOG) __HAL_RCC_GPIOG_CLK_ENABLE();
        else if(p == GPIOH) __HAL_RCC_GPIOH_CLK_ENABLE();
    }
};

#endif // DAISY_UART_LISTENER_HPP
/************************  END  daisy_uart_listener.hpp **********************/

/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020-2021 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

//#include "daisysp.h"

#ifdef SEED 
#include "daisy_seed.h"
using namespace daisy::seed;
static daisy::DaisySeed hw;
#elif defined PATCHSM
#include "daisy_patch_sm.h"
static daisy::DaisyPatchSM hw;
#endif

#include <functional>
#include <array>

static float normalize(float v, float min, float max)
{
    return (v - min) / (max - min);    
}

static float snap_to_step(float v, float step) 
{ 
    return std::round(v / step) * step; 
}

static float scale_from_norm(float v, float min, float max)
{
    return (max - min) * v  + min; 
}

static float limit(float v, float min, float max)
{
    if(v > max) return max;
    if(v < min) return min;   
    return v;
}

struct scale 
{
    enum scale_t {lin, log, exp};
    // Schraudolph's approximation - very fast, ~1% error
    static float fast_exp_norm(float t)
    {
        // (e^t - 1) / (e - 1), approximated
        union { float f; int32_t i; } u;
        u.i = (int32_t)(t * 8388608.0f) + 1065353216;
        return (u.f - 1.0f) * 0.58198f; // scale to [0,1]
    }

    // Polynomial approximation - good balance
    static float exp_norm(float t)
    {
        // e^(t*1) approximated, then normalized
        float x = 1.0f + t + t*t*0.5f + t*t*t*0.1667f;
        return (x - 1.0f) / (M_E - 1.0f);
    }
    // Bit trick approximation
    static float fast_log_norm(float t)
    {
        union { float f; uint32_t i; } u;
        u.f = t + 1.0f;
        float approx = (float)(u.i - 1065353216) * 1.1920929e-7f;
        return approx / 1.0f; // already ~[0,1] for input [0,1]
    }

    // Polynomial - more accurate
    static float log_norm(float t)
    {
        // log(1 + t*(e-1)) / 1, polynomial approximation
        float x = t * (M_E - 1.0f); // remap to [0, e-1]
        // log(1+x) ≈ x - x²/2 + x³/3 for small x
        return (x - x*x*0.5f + x*x*x*0.333f) / 1.0f;
    }

    static float process(scale_t s, float val)
    {
        switch(s)
        {
            case scale_t::lin:
                return val;
            case scale_t::log:
                return log_norm(val);
            case scale_t::exp:
                return exp_norm(val);
            default: 
                return val;
        }
        return val;
    }
};

#ifdef MIDICTRL

struct midi_t
{
    enum type_t 
    {
        keyon, keyoff, key, cc
    };
    type_t type;
    // Channel 0 means all 
    uint8_t index, channel, value;

    midi_t() = default;
    midi_t(type_t t, uint8_t id, uint8_t chan)
        : type(t)
        , index(id)
        , channel(chan)
    {}
};

template<size_t N>
midi_t* midi_find(std::array<midi_t, N>& arr, uint8_t index)
{
    for(auto & it : arr) 
    {
        if(it.index == index)
            return &it; 
    }
    return nullptr;
}

#endif

struct control 
{
    enum scale_t {
        lin, log, exp
    };
    control::scale_t scale; // To implement in update methods
    const char *label; // Might be useless‘

    float *value_ptr;

    scale::scale_t scale_type = scale::scale_t::lin;
    /*                           
        control methods          
    */                           
                                 
    using update_method_t = void(*)(float, float*, float, float, float, float&, scale::scale_t);
    update_method_t update_method = nullptr;


    control() {}
    control(scale::scale_t scale_)
        : scale_type(scale_)
    {}

    virtual void setup() {}
    virtual void update() {}
    virtual void set_value_ptr(float *zone) {value_ptr = zone;}
};

#ifdef SEED
    constexpr static const daisy::Pin DEFAULT_PIN = daisy::seed::A1;
#elif defined PATCHSM 
    constexpr static const daisy::Pin DEFAULT_PIN = daisy::patch_sm::A1;
#endif

/*
    A bit misnamed : it is used as ADC class & base class for other inputs (digital, MIDI)
*/
struct adc : public control
{
    enum type_t {
        slider, 
        button, 
        checkbox, 
    };

    adc::type_t type;
    float init, min, max, step, previous_state;  // Init might be useless

    daisy::Pin pin;
    uint8_t channel; // index in used ADC list 

    
    adc() = default;
    adc(adc::type_t t, float init_, float min_, float max_, float step_, 
        scale::scale_t scale_ = scale::scale_t::lin, daisy::Pin pin_ = DEFAULT_PIN)
        : control::control(scale_)
        , type(t)
        , init(init_)
        , min(min_)
        , max(max_)
        , step(step_)
        , previous_state(init_)
        , pin(pin_)
    {}


    /*
        For Buttons and checkboxes 0.05f we need a threshold to eliminate potential DC or noise 
    */

    static void slider_method(float value, float *fZone, 
        float min, float max, float step, float &prev, scale::scale_t scale_type)
    {
        *fZone = snap_to_step(scale_from_norm(scale::process(scale_type, value), min, max), step);
    }
    
    constexpr static float noise_threshold = 0.05f;
    static void button_method(float value, float *fZone, 
        float min, float max, float step, float &prev, scale::scale_t scale_type)
    {
        *fZone = (value > noise_threshold) ? 1.0f : 0.0f;
    }

    static void checkbox_method(float value, float *fZone, 
        float min, float max, float step, float &prev, scale::scale_t scale_type)
    {
        if(value > noise_threshold && value > prev && (value - prev) > noise_threshold)
        {
            *fZone = 1.0f - (*fZone);
        }
        prev = value;
    }

    void setup() override 
    {
        //float _min = min, _max = max, _step = step;
        switch(type)
        {
        case type_t::slider:
            update_method = slider_method;
            break;
        case type_t::button:
            update_method = button_method;
            break;
        case type_t::checkbox:
            update_method = checkbox_method;
            break;
        default:
            break;
        }
    }

    void update() override
    {
        update_method(hw.adc.GetFloat(channel), value_ptr, 
            min, max, step, previous_state, scale_type);
    }
};

#ifdef POLY
template<uint8_t N> 
struct shared_adc : public adc 
{
    std::array<float *, N> targets; 
    std::array<float, N> prev_states {}; 
    uint8_t counter = 0;
    float val = 0.0f;
    shared_adc() = default;
    shared_adc(adc::type_t t, float init_, float min_, float max_, float step_,
        scale::scale_t scale_ = scale::scale_t::lin, daisy::Pin pin_ = DEFAULT_PIN)
        : adc(t, init_, min_, max_, step_, scale_, pin_)
        , val(init)
    {}
    // Called once per voice during buildUserInterface
    void set_value_ptr(float *zone) override 
    {
        if(counter < N)
            targets[counter] = zone;
        
        counter = counter % N;
    }

    void setup() override 
    {
        if(counter == 0)
            adc::setup();
        *targets[counter] = init;
        counter = (counter + 1) % N;
    }

    void update() override {
        if(counter == 0)
            val = hw.adc.GetFloat(channel);
        update_method(val, targets[counter], min, max, step, prev_states[counter], scale_type);
        counter = (counter + 1) % N;
    }
};
#endif

struct digi_input : public adc
{
    daisy::GPIO gpio;

    digi_input() = default;
    digi_input(adc::type_t t, float init_, float min_, float max_, float step_, 
        daisy::Pin pin_ = DEFAULT_PIN)
        : adc::adc(t, init_, min_, max_, step_, scale::scale_t::lin, pin_)
    {}

    uint32_t passed_samples; 
    constexpr static const uint32_t time_threshold = MY_SAMPLE_RATE / 100;

    void setup() override 
    {
        adc::setup();
        gpio.Init(pin, daisy::GPIO::Mode::INPUT, daisy::GPIO::Pull::PULLUP, 
            daisy::GPIO::Speed::VERY_HIGH);
        passed_samples =  0; 
        *value_ptr = init;
    }

    void update() override 
    {
        if(passed_samples == 0)
        {
            update_method(!gpio.Read(), value_ptr, min, max, step, previous_state, scale_type);
        }
        passed_samples += MY_BUFFER_SIZE;
        if(passed_samples >= time_threshold)
            passed_samples = 0;

    }
};

#ifdef POLY
template<uint8_t N>
struct shared_digi_input : public digi_input 
{
    std::array<float *, N> targets; 
    std::array<float, N> prev_states = {};
    uint8_t counter = 0;
    bool val = false; 

    shared_digi_input() = default; 
    shared_digi_input(adc::type_t t, float init_, float min_, float max_, float step_, 
        daisy::Pin pin_ = DEFAULT_PIN)
        : digi_input::digi_input(t, init_, min_, max_, step_, pin_)
        , val(init > 0.05f ? true : false)
    {}

    void set_value_ptr(float * zone) override
    {
        if(counter < N)
            targets[counter] = zone;
    }

    void setup() override 
    {
        counter, update_method);
        if(counter == 0)
        {
            adc::setup();
            gpio.Init(pin, daisy::GPIO::Mode::INPUT, daisy::GPIO::Pull::PULLUP,
                daisy::GPIO::Speed::VERY_HIGH);
            passed_samples = 0;
        }
        *targets[counter] = init;
        counter = (counter + 1) % N;
    }

    void update() override 
    {
        if(counter == 0)
            val = !gpio.Read();

        update_method(val, targets[counter], min, max, step, prev_states[counter], scale_type);
        counter = (counter + 1) % N;
    }


};
#endif

#ifdef MIDICTRL

// Not really an ADC, but shared logic 
struct midi_input : public adc
{
    midi_t *m;
    midi_input() = default;
    midi_input(adc::type_t t, float init_, float min_, float max_, float step_, 
            scale::scale_t scale_ = scale::scale_t::lin, midi_t *midiptr = nullptr)
        : adc::adc(t, init_, min_, max_, step_, scale_)
        , m(midiptr)
    {}

    void update() override 
    {
        update_method(float(m->value) / 127.0f, value_ptr, 
            min, max, step, previous_state, scale_type);
    }
};

#ifdef POLY 

struct poly_input : public midi_input 
{
    enum type_t 
    {
        key, freq, gain, vel, gate
    };
    type_t poly_type;

    static float mtof(int note)
    {
         return 440.0 * std::pow(2.0, (note - 69) / 12.0);
    }

    // For freq : midi to frequency, limiting and snapping 
    static void freq_slider_method(float value, float *fZone, 
        float min, float max, float step, float &prev, scale::scale_t scale_type)
    {
        
        *fZone = snap_to_step(limit(mtof(value), min, max), step);
    }

    // Used for vel as well.
    // No normalization, no mapping, no scaling. Just limiting and snapping to integer. 
    static void key_slider_method(float value, float *fZone, 
        float min, float max, float step, float &prev, scale::scale_t scale_type)
    {
        *fZone = snap_to_step(limit(value, min, max), int(step) );
    }

    
    // Normalizing the value from MIDI, scaling, snapping 
    static void gain_slider_method(float value, float *fZone, 
        float min, float max, float step, float &prev, scale::scale_t scale_type)
    {
        *fZone = snap_to_step(scale_from_norm(
            scale::process(scale_type, value / 127.0f), min, max), step);
    }

    
    poly_input() = default;
    poly_input(adc::type_t t, float init_, float min_, float max_, float step_, 
            scale::scale_t scale_ = scale::scale_t::lin, midi_t *midiptr = nullptr, 
            poly_input::type_t poly_type_ = poly_input::type_t::key)
        : midi_input::midi_input(t, init_, min_, max_, step_, scale_, midiptr)
        , poly_type(poly_type_)
    {}

    void setup() override
    {
        midi_input::setup();
        switch(poly_type)
        {
            case type_t::key:
            {
                update_method = key_slider_method;
                break;
            }
            case type_t::freq:
            {
                update_method = freq_slider_method;
                break;
            }
            case type_t::vel:
            {
                update_method = key_slider_method; // same as velocity, 0-127 
                break;
            }
            case type_t::gain:
            {
                if(this->type == adc::type_t::slider) {
                    update_method = gain_slider_method;
                } // else, button or checkbox, should be ok with adc implementation
                break;
            }
            default: break;
        };
    }


    void update() override 
    {
        update_method(float(m->value), value_ptr, min, max, step, 
            previous_state, scale_type);

    }
};

// Abstract class for polyphonic contexts
struct poly_control_base
{
    virtual poly_input* get_key() {return nullptr;}
    virtual poly_input* get_freq() {return nullptr;}
    virtual poly_input* get_vel() {return nullptr;}
    virtual poly_input* get_gain() {return nullptr;}
    virtual poly_input* get_gate() {return nullptr;}
};

#endif

#endif

struct dac : public control
{
    float min, max; 
    const char *label;

    daisy::DacHandle::Channel channel; // index in used ADC list 

    dac(daisy::DacHandle::Channel chn, float min_, float max_, 
            scale::scale_t scale_ = scale::scale_t::lin)
        : control::control(scale_)
        , min(min_)
        , max(max_)
        , channel(chn)
    {}

    void update() override
    {
        hw.dac.WriteValue(channel, uint16_t(scale::process(scale_type, 
            normalize(*value_ptr, min, max)) * 4095.0f));
    }
};

#ifdef POLY
template<uint8_t N> 
struct shared_dac : public dac 
{
    uint8_t counter = 0;

    shared_dac() = default; 
    shared_dac(daisy::DacHandle::Channel chn, float min_, float max_, 
            scale::scale_t scale_ = scale::scale_t::lin)
        : dac::dac(chn, min_, max_, scale_)
    {}

    void set_value_ptr(float *zone)
    {
        if(counter == 0) 
            value_ptr = zone;
        counter = (counter + 1) % N;
    }

    void update() override 
    {
        if(counter == 0)
        {
            dac::update();
        }
        counter = (counter + 1) % N;
        
    }
};
#endif

struct digi_output : public control 
{
    enum pwm_t 
    {
        off, 
        on,
        inv 
    };

    daisy::Pin pin;
    float min, max;
    daisy::GPIO gpio;
    daisy::Led led;

    using digi_out_method_t = void(*)(float*, daisy::GPIO* gpio, daisy::Led* led);
    digi_out_method_t digi_out_method = nullptr;

    static void gpio_method(float *val, daisy::GPIO* gpio, daisy::Led* led)
    {
        gpio->Write( (*val) < adc::noise_threshold );
    }

    static void led_method(float *val, daisy::GPIO* gpio, daisy::Led* led)
    {
        led->Set(*val);
        led->Update();
    }

    digi_output() = default;
    digi_output(daisy::Pin pin_, pwm_t pwm, float min_ = 0.0f, float max_ = 1.0f)
        : pin(pin_)
        , min(min_)
        , max(max_)
    {
        if(pwm != pwm_t::off) 
        {
            led.Init(pin, pwm == pwm_t::inv, 1000.0f /*MY_SAMPLE_RATE / MY_BUFFER_SIZE*/ );
            digi_out_method = led_method;

        } else 
        {
            gpio.Init(pin, daisy::GPIO::Mode::OUTPUT);
            digi_out_method = led_method;
        }
        *value_ptr = min;
    }


    void update() override 
    {
        digi_out_method(value_ptr, &gpio, &led);
    }
};

#ifdef POLY
template<uint8_t N> 
struct shared_digi_output : public digi_output
{
    uint8_t counter = 0;

    shared_digi_output() = default; 
    shared_digi_output(daisy::Pin pin_, float min_ = 0.0f, float max_ = 1.0f)
        : digi_output::digi_output(pin_, min_, max_)
    {}
    
    void set_value_ptr(float *zone)
    {
        if(counter == 0) 
            value_ptr = zone;
        counter = (counter + 1) % N;
    }

    void update() override 
    {
        if(counter == 0)
        {
            digi_output::update();
        }
        counter = (counter + 1) % N;
        
    }
};
#endif


// Do not remove following tag, as it is used by python to inline code
/*<UI CONTROL TAG>*/

#include "faust/gui/meta.h"
#include "faust/gui/UI.h"
#include "faust/gui/DaisyControlUI.h"
#include "faust/dsp/dsp.h"

#ifdef MIDICTRL
#include "faust/midi/daisy-midi.h"
#endif

//using namespace daisysp;
using namespace std;                    

#ifdef USE_SDRAM
    // Do not remove following tag as it is used by python to inline code
    /*<SDRAM TAG>*/
    #if FAUST_SDRAM_SIZE_BYTES == 0
        #undef USE_SDRAM
    #else 
        uint8_t DSY_SDRAM_BSS faust_sdram_mem[ FAUST_SDRAM_SIZE_BYTES ];
        struct faustdaisy_dsp_memory_manager : public dsp_memory_manager
        {
            struct mem_info_t
            {
                const char *name;
                MemType type;
                size_t size;
                size_t size_bytes; 
                size_t reads;
                size_t writes;
                void *ptr = nullptr; // pointeur to location in memory
            };

            faustdaisy_dsp_memory_manager() {
            }

            void init() {
                std::fill(faust_sdram_mem, faust_sdram_mem + FAUST_SDRAM_SIZE_BYTES, 0);
                offset = 0;
            }

            void begin(size_t count) {}
            

            void info(const char * name, MemType type, 
                size_t size, size_t size_bytes, size_t reads, size_t writes) {}

            void end() {}
        
            void *allocate(size_t size_bytes) 
            {
                void *ptr = faust_sdram_mem + offset; 
                offset += size_bytes;
                return ptr;
            }

            void destroy(void *ptr) { ptr = nullptr; }

            size_t offset;
        };
    #endif
#endif

#include <string>
#include <type_traits>
#include <utility>


/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

#ifdef POLY
#include "faust/dsp/daisy-poly.h"
#endif

static DaisyControlUI control_UI;

#ifdef POLY
    static mydsp_poly<NVOICES> DSP;
#else 
    static mydsp DSP;
#endif

#ifdef USE_SDRAM 
    static faustdaisy_dsp_memory_manager memory_manager; 
#endif

static void AudioCallback(daisy::AudioHandle::InputBuffer in, 
    daisy::AudioHandle::OutputBuffer out, size_t count)
{
    // Update control inputs
    control_UI.update_adcs();
    
    // DSP processing
    DSP.compute(count, const_cast<float**>(in), out);

    // Update control outputs 
    control_UI.update_dacs();
}

int main(void)
{

    // Initialize Daisy 
    hw.Init();
    hw.SetAudioBlockSize(MY_BUFFER_SIZE);
    hw.SetAudioSampleRate(DAISY_SAMPLE_RATE);

#ifdef MIDICTRL
    daisy_midi midi_handler;
#endif

    // For debug only
    //daisy::System::Delay(500);
    //hw.StartLog();
    daisy::System::Delay(500);
    
/*
    DSP Initialization
*/
#ifdef USE_SDRAM 
    memory_manager.init();
    mydsp::fManager = &memory_manager;
    DSP.memoryCreate();
    mydsp::classInit(MY_SAMPLE_RATE);
    DSP.instanceInit(MY_SAMPLE_RATE);
#else 
    DSP.init(MY_SAMPLE_RATE);
#endif

/*
    Controllers setup 
*/
    DSP.buildUserInterface(&control_UI);
    control_UI.setup_controls();

    if(adc_list.size() > 0)
        hw.adc.Start();
    hw.StartAudio(AudioCallback);

    // MIDI handling loop
    while(1) {
        #ifdef MIDICTRL
            midi_handler.processMidi();
        #endif
    }
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

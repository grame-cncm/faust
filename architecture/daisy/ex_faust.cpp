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

<<<<<<< HEAD
<<<<<<< HEAD
#include <functional>
#include <array>

static float normalize(float v, float min, float max)
=======
#ifdef MIDICTRL
#include<unordered_map>
#endif
#include <functional>
#include <array>

inline static float normalize(float v, float min, float max)
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
#include <functional>
#include <array>

static float normalize(float v, float min, float max)
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
{
    return (v - min) / (max - min);    
}

<<<<<<< HEAD
<<<<<<< HEAD
static float snap_to_step(float v, float step) 
=======
inline static float snap_to_step(float v, float step) 
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
static float snap_to_step(float v, float step) 
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
{ 
    return std::round(v / step) * step; 
}

<<<<<<< HEAD
<<<<<<< HEAD
static float scale_from_norm(float v, float min, float max)
=======
inline static float scale_from_norm(float v, float min, float max)
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
static float scale_from_norm(float v, float min, float max)
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
{
    return (max - min) * v  + min; 
}

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
static float limit(float v, float min, float max)
{
    if(v > max) return max;
    if(v < min) return min;   
    return v;
}

<<<<<<< HEAD
=======
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
struct scale 
{
    enum scale_t {lin, log, exp};
    // Schraudolph's approximation - very fast, ~1% error
<<<<<<< HEAD
<<<<<<< HEAD
    static float fast_exp_norm(float t)
=======
    static inline float fast_exp_norm(float t)
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
    static float fast_exp_norm(float t)
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
    {
        // (e^t - 1) / (e - 1), approximated
        union { float f; int32_t i; } u;
        u.i = (int32_t)(t * 8388608.0f) + 1065353216;
        return (u.f - 1.0f) * 0.58198f; // scale to [0,1]
    }

    // Polynomial approximation - good balance
<<<<<<< HEAD
<<<<<<< HEAD
    static float exp_norm(float t)
=======
    static inline float exp_norm(float t)
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
    static float exp_norm(float t)
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
    {
        // e^(t*1) approximated, then normalized
        float x = 1.0f + t + t*t*0.5f + t*t*t*0.1667f;
        return (x - 1.0f) / (M_E - 1.0f);
    }
    // Bit trick approximation
<<<<<<< HEAD
<<<<<<< HEAD
    static float fast_log_norm(float t)
=======
    static inline float fast_log_norm(float t)
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
    static float fast_log_norm(float t)
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
    {
        union { float f; uint32_t i; } u;
        u.f = t + 1.0f;
        float approx = (float)(u.i - 1065353216) * 1.1920929e-7f;
        return approx / 1.0f; // already ~[0,1] for input [0,1]
    }

    // Polynomial - more accurate
<<<<<<< HEAD
<<<<<<< HEAD
    static float log_norm(float t)
=======
    static inline float log_norm(float t)
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
    static float log_norm(float t)
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
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

<<<<<<< HEAD
=======
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
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

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
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

<<<<<<< HEAD
=======
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
#endif

struct control 
{
    enum scale_t {
        lin, log, exp
    };
    control::scale_t scale; // To implement in update methods
    const char *label; // Might be useless‘

<<<<<<< HEAD
<<<<<<< HEAD
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
=======
    control() {}

    virtual void setup();
    virtual void update();
    virtual void set_value_ptr(float *zone);
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
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
<<<<<<< HEAD
    void set_value_ptr(float *zone) {value_ptr = zone;}
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
    virtual void set_value_ptr(float *zone) {value_ptr = zone;}
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
};

#ifdef SEED
    constexpr static const daisy::Pin DEFAULT_PIN = daisy::seed::A1;
#elif defined PATCHSM 
    constexpr static const daisy::Pin DEFAULT_PIN = daisy::patch_sm::A1;
#endif

<<<<<<< HEAD
<<<<<<< HEAD
/*
    A bit misnamed : it is used as ADC class & base class for other inputs (digital, MIDI)
*/
=======
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
/*
    A bit misnamed : it is used as ADC class & base class for other inputs (digital, MIDI)
*/
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
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
<<<<<<< HEAD
<<<<<<< HEAD

    
    adc() = default;
    adc(adc::type_t t, float init_, float min_, float max_, float step_, 
        scale::scale_t scale_ = scale::scale_t::lin, daisy::Pin pin_ = DEFAULT_PIN)
        : control::control(scale_)
        , type(t)
=======
    float *value_ptr;

    
    adc() = default;
    adc(adc::type_t t, float init_, float min_, float max_, float step_, daisy::Pin pin_ = DEFAULT_PIN)
        : type(t)
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======

    
    adc() = default;
    adc(adc::type_t t, float init_, float min_, float max_, float step_, 
        scale::scale_t scale_ = scale::scale_t::lin, daisy::Pin pin_ = DEFAULT_PIN)
        : control::control(scale_)
        , type(t)
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
        , init(init_)
        , min(min_)
        , max(max_)
        , step(step_)
        , previous_state(init_)
        , pin(pin_)
    {}

<<<<<<< HEAD
<<<<<<< HEAD
=======
    /*
        ADC control methods    
    */

<<<<<<< HEAD
    using adc_method = std::function<void(float, float *)>;
    adc_method slider_method = [&](float value, float *fZone)
    {
        *fZone = snap_to_step(scale_from_norm(value, min, max), step);
    };
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
    using adc_method = void(*)(float, float*, float, float, float, float&, scale::scale_t);
    adc_method update_method = nullptr;
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)

    /*
        For Buttons and checkboxes 0.05f we need a threshold to eliminate potential DC or noise 
    */
<<<<<<< HEAD
<<<<<<< HEAD

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
=======
    constexpr static float noise_threshold = 0.05f;
    adc_method button_method = [&](float value, float *fZone)
=======

<<<<<<< HEAD
    static void slider_method(float value, float *fZone, float min, float max, float step, float &prev, scale::scale_t scale_type)
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
    static void slider_method(float value, float *fZone, 
        float min, float max, float step, float &prev, scale::scale_t scale_type)
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
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
<<<<<<< HEAD
        previous_state = value;
    };

    adc_method update_method;

    void set_value_ptr(float *zone) override 
    {
        value_ptr = zone;
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
        prev = value;
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
    }

    void setup() override 
    {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        //float _min = min, _max = max, _step = step;
=======
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
        float _min = min, _max = max, _step = step;
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
        //float _min = min, _max = max, _step = step;
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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

=======
        update_method(hw.adc.GetFloat(channel), value_ptr, min, max, step, previous_state, scale_type);
    }
};

>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
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

>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
struct digi_input : public adc
{
    daisy::GPIO gpio;

    digi_input() = default;
<<<<<<< HEAD
<<<<<<< HEAD
    digi_input(adc::type_t t, float init_, float min_, float max_, float step_, 
        daisy::Pin pin_ = DEFAULT_PIN)
=======
    digi_input(adc::type_t t, float init_, float min_, float max_, float step_, daisy::Pin pin_ = DEFAULT_PIN)
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
    digi_input(adc::type_t t, float init_, float min_, float max_, float step_, 
        daisy::Pin pin_ = DEFAULT_PIN)
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
        : adc::adc(t, init_, min_, max_, step_, scale::scale_t::lin, pin_)
    {}

    uint32_t passed_samples; 
    constexpr static const uint32_t time_threshold = MY_SAMPLE_RATE / 100;

    void setup() override 
    {
        adc::setup();
<<<<<<< HEAD
<<<<<<< HEAD
        gpio.Init(pin, daisy::GPIO::Mode::INPUT, daisy::GPIO::Pull::PULLUP, 
            daisy::GPIO::Speed::VERY_HIGH);
=======
        gpio.Init(pin, daisy::GPIO::Mode::INPUT, daisy::GPIO::Pull::PULLUP, daisy::GPIO::Speed::VERY_HIGH);
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
        gpio.Init(pin, daisy::GPIO::Mode::INPUT, daisy::GPIO::Pull::PULLUP, 
            daisy::GPIO::Speed::VERY_HIGH);
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
        passed_samples =  0; 
        *value_ptr = init;
    }

    void update() override 
    {
        if(passed_samples == 0)
        {
<<<<<<< HEAD
<<<<<<< HEAD
            update_method(!gpio.Read(), value_ptr, min, max, step, previous_state, scale_type);
=======
            update_method(gpio.Read(), value_ptr, min, max, step, previous_state, scale_type);
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
=======
            update_method(!gpio.Read(), value_ptr, min, max, step, previous_state, scale_type);
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
        }
        passed_samples += MY_BUFFER_SIZE;
        if(passed_samples >= time_threshold)
            passed_samples = 0;

<<<<<<< HEAD
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
<<<<<<< HEAD
=======
        hw.PrintLine("shared_digi setup counter=%d upd=%p", 
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
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

<<<<<<< HEAD
=======
        update_method(hw.adc.GetFloat(channel), value_ptr);
=======
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
    }
};

>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
#ifdef MIDICTRL

// Not really an ADC, but shared logic 
struct midi_input : public adc
{
    midi_t *m;
<<<<<<< HEAD
<<<<<<< HEAD
    midi_input() = default;
    midi_input(adc::type_t t, float init_, float min_, float max_, float step_, 
            scale::scale_t scale_ = scale::scale_t::lin, midi_t *midiptr = nullptr)
<<<<<<< HEAD
        : adc::adc(t, init_, min_, max_, step_, scale_)
=======
    midi_input(adc::type_t t, float init_, float min_, float max_, float step_, midi_t *midiptr)
=======
    midi_input() = default;
<<<<<<< HEAD
    midi_input(adc::type_t t, float init_, float min_, float max_, float step_, midi_t *midiptr = nullptr)
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
        : adc::adc(t, init_, min_, max_, step_)
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
    midi_input(adc::type_t t, float init_, float min_, float max_, float step_, scale::scale_t scale_ = scale::scale_t::lin, midi_t *midiptr = nullptr)
=======
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
        : adc::adc(t, init_, min_, max_, step_, scale_)
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
        , m(midiptr)
    {}

    void update() override 
    {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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

=======
        update_method(float(m->value) / 128.0, value_ptr);
    }
};

>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
        update_method(float(m->value) / 127.0, value_ptr, min, max, step, previous_state, scale_type);
=======
        update_method(float(m->value) / 127.0f, value_ptr, 
            min, max, step, previous_state, scale_type);
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
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
        /*static int fcnt = 0;
        if(++fcnt > 1000) {
            fcnt = 0;
            hw.PrintLine("Freq value : %d", int(*fZone));
        }*/
    }

    // Used for vel as well.
    // No normalization, no mapping, no scaling. Just limiting and snapping to integer. 
    static void key_slider_method(float value, float *fZone, 
        float min, float max, float step, float &prev, scale::scale_t scale_type)
    {
        *fZone = snap_to_step(limit(value, min, max), int(step) );
        /*static int kcnt = 0;
        if(++kcnt > 1000) {
            kcnt = 0;
            hw.PrintLine("Key value : %d", int(*fZone));
        }*/

    }

    
    // Normalizing the value from MIDI, scaling, snapping 
    static void gain_slider_method(float value, float *fZone, 
        float min, float max, float step, float &prev, scale::scale_t scale_type)
    {
        *fZone = snap_to_step(scale_from_norm(
            scale::process(scale_type, value / 127.0f), min, max), step);
        //hw.PrintLine("Gain value : %.2f", *fZone);
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

>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
#endif

struct dac : public control
{
    float min, max; 
    const char *label;

    daisy::DacHandle::Channel channel; // index in used ADC list 
<<<<<<< HEAD
<<<<<<< HEAD

    dac(daisy::DacHandle::Channel chn, float min_, float max_, 
            scale::scale_t scale_ = scale::scale_t::lin)
        : control::control(scale_)
        , min(min_)
=======
    float *value_ptr;

    dac(daisy::DacHandle::Channel chn, float min_, float max_)
        : min(min_)
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======

    dac(daisy::DacHandle::Channel chn, float min_, float max_, 
            scale::scale_t scale_ = scale::scale_t::lin)
        : control::control(scale_)
        , min(min_)
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
        , max(max_)
        , channel(chn)
    {}

    void update() override
    {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
        hw.dac.WriteValue(channel, uint16_t(scale::process(scale_type, normalize(*value_ptr, min, max)) * 4095.0f));
=======
        hw.dac.WriteValue(channel, uint16_t(scale::process(scale_type, 
            normalize(*value_ptr, min, max)) * 4095.0f));
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
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
    daisy::Pin pin;
    daisy::GPIO gpio;
    float min, max;

    digi_output() = default;
    digi_output(daisy::Pin pin_, float min_ = 0.0f, float max_ = 1.0f)
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
        : pin(pin_)
        , min(min_)
        , max(max_)
    {
<<<<<<< HEAD
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


=======
        hw.dac.WriteValue(channel, uint16_t(normalize(*value_ptr, min, max) * 4095.0f));
=======
        gpio.Init(pin, daisy::GPIO::Mode::OUTPUT);
        *value_ptr = min;
    }

    void update() override 
    {
<<<<<<< HEAD
        gpio.Write( (*value_ptr) > adc::noise_threshold );
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
    }
};

>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
        gpio.Write( (*value_ptr) < adc::noise_threshold );
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


>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
// Do not remove following tag, as it is used by python to inline code
/*<UI CONTROL TAG>*/

#include "faust/gui/meta.h"
#include "faust/gui/UI.h"
#include "faust/gui/DaisyControlUI.h"
#include "faust/dsp/dsp.h"

#ifdef MIDICTRL
#include "faust/midi/daisy-midi.h"
#endif

<<<<<<< HEAD
<<<<<<< HEAD
//using namespace daisysp;
=======
using namespace daisysp;
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
//using namespace daisysp;
>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
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
<<<<<<< HEAD
<<<<<<< HEAD
            }

            void init() {
=======
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
            }

            void init() {
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
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
<<<<<<< HEAD
<<<<<<< HEAD
    // Update control inputs
=======
    #ifdef MIDICTRL 
        //midi_handler.processMidi();
    #endif 
=======
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
    // Update controllers
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
    control_UI.update_adcs();
    
    // DSP processing
    DSP.compute(count, const_cast<float**>(in), out);

<<<<<<< HEAD
    // Update control outputs 
=======
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
    control_UI.update_dacs();

    /*
    static int n = 0;
    if(++n > 1000) {
        n = 0;
        float *ptr = input_list[0]->value_ptr;
        hw.PrintLine("ptr=%p val=%.2f midi_raw=%d", ptr, *ptr, (int)poly_midi_values[0].value);
    }
    */
    

}

int main(void)
{

    // Initialize Daisy 
    hw.Init();
    hw.SetAudioBlockSize(MY_BUFFER_SIZE);
<<<<<<< HEAD
<<<<<<< HEAD
    hw.SetAudioSampleRate(DAISY_SAMPLE_RATE);

#ifdef MIDICTRL
    daisy_midi midi_handler;
=======
=======
    hw.SetAudioSampleRate(DAISY_SAMPLE_RATE);
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)

#ifdef MIDICTRL
    daisy_midi midi_handler;
#endif

    // For debug only
    //daisy::System::Delay(500);
    //hw.StartLog();
    daisy::System::Delay(500);
<<<<<<< HEAD
/*
    Memory Manager Creation 
*/
#ifdef USE_SDRAM 
    mydsp::fManager = &memory_manager;
    mydsp::classInit(MY_SAMPLE_RATE);
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
#endif
    

<<<<<<< HEAD
    // For debug only
    //daisy::System::Delay(500);
    //hw.StartLog();
    daisy::System::Delay(500);
    
=======
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
    
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
/*
    DSP Initialization
*/
#ifdef USE_SDRAM 
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
    memory_manager.init();
    mydsp::fManager = &memory_manager;
    DSP.memoryCreate();
    mydsp::classInit(MY_SAMPLE_RATE);
<<<<<<< HEAD
=======
    DSP::classInit(MY_SAMPLE_RATE);
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
>>>>>>> 23c140053 (polyphony still not fully operational, mono MIDI & ADC & DAC working on Seed with Flash, SRAM or QSPIFLASH)
    DSP.instanceInit(MY_SAMPLE_RATE);
#else 
    DSP.init(MY_SAMPLE_RATE);
#endif

/*
    Controllers setup 
*/
    DSP.buildUserInterface(&control_UI);
    control_UI.setup_controls();

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
    /*for(size_t i = 0; i < input_list.size(); i++) {
        hw.PrintLine("input[%d] vptr=%p mptr=%p upd=%p", 
            i,
            input_list[i]->value_ptr,
            ((poly_input*)input_list[i])->m,
            input_list[i]->update_method);
    }
    daisy::System::Delay(5000);
    */

>>>>>>> e0acbeb33 (almost full feature for daisy seed, added configuration files for platforms (pod, patch) and proper mapping of these, cut dependency between hothouse & daisy, fixed polyphony in daisy, digital gpio available)
    if(adc_list.size() > 0)
        hw.adc.Start();
=======
    hw.adc.Start();
>>>>>>> 499e9e8f7 (fixed memory (seed), mono midi)
=======
    if(adc_list.size() > 0)
        hw.adc.Start();
>>>>>>> fb8a200e6 (Polyphony working, digital pins (in out) implemented, UART MIDI ok for Pod, several controls on same MIDI input working, samplerate specification, scale implementation)
    hw.StartAudio(AudioCallback);

    // MIDI handling loop
    while(1) {
        #ifdef MIDICTRL
            midi_handler.processMidi();
        #endif
    }
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

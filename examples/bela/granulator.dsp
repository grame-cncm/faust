// FROM FAUST DEMO
// Designed to use the Analog Input for parameter controls.
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// ANALOG IN:
// ANALOG 0	: Grain Size
// ANALOG 1	: Speed
// ANALOG 2	: Probability
// (others analog inputs are not used)
//
///////////////////////////////////////////////////////////////////////////////////////////////////

process = vgroup("Granulator", environment {
    declare name "Granulator";
    declare author "Adapted from sfIter by Christophe Lebreton";

    /* =========== DESCRIPTION =============

    - The granulator takes very small parts of a sound, called GRAINS, and plays them at a varying speed
    - Front = Medium size grains
    - Back = short grains
    - Left Slow rhythm
    - Right = Fast rhythm
    - Bottom = Regular occurrences
    - Head = Irregular occurrences 
    */

    import("stdfaust.lib");

    process = hgroup("Granulator", *(excitation : ampf));

    excitation = noiseburst(gate,P) * (gain);
    ampf = an.amp_follower_ud(duree_env,duree_env);

    //----------------------- NOISEBURST ------------------------- 

    noiseburst(gate,P) = no.noise : *(gate : trigger(P))
        with { 
            upfront(x) = (x-x') > 0;
            decay(n,x) = x - (x>0)/n; 
            release(n) = + ~ decay(n); 
            trigger(n) = upfront : release(n) : > (0.0);
        };

    //-------------------------------------------------------------

    P = freq; // fundamental period in samples
    freq = hslider("[1]GrainSize[BELA: ANALOG_0]", 200,5,2205,1);
    // the frequency gives the white noise band width
    Pmax = 4096; // maximum P (for de.delay-line allocation)

    // PHASOR_BIN //////////////////////////////
    phasor_bin(init) = (+(float(speed)/float(ma.SR)) : fmod(_,1.0)) ~ *(init);
    gate = phasor_bin(1) :-(0.001):pulsar;
    gain = 1;
                            
    // PULSAR //////////////////////////////
    // Pulsar allows to create a more or less random 'pulse'(proba).

    pulsar = _<:((_<(ratio_env)):@(100))*(proba>(_,abs(no.noise):ba.latch)); 
    speed = hslider("[2]Speed[BELA: ANALOG_1]", 10,1,20,0.0001):fi.lowpass(1,1);

    ratio_env = 0.5;
    fade = (0.5); // min > 0 to avoid division by 0

    proba = hslider("[3]Probability[BELA: ANALOG_2]", 70,50,100,1) * (0.01):fi.lowpass(1,1);
    duree_env = 1/(speed: /(ratio_env*(0.25)*fade));
}.process);

import("stdfaust.lib");

//------------------------`rain_on_window`--------------------
// rain_on_window : produces a sound of raindrops on a glass
//                  window, based on examples
//                          from the book "Designing Sound"
//                               by Andy Farnell
//
// #### Usage
//
// ```
// rain_on_window : _
// ```
//
// #### Examples
//
// ```
// rain_on_window <: (_, _);
// ```
//
//------------------------------------------------------------

//------------------------`ambient_rain`----------------------
// ambient_rain(freq) : produces a ambient rain sound,
//                         based on examples
//                         from the book "Designing Sound"
//                               by Andy Farnell
//
// #### Usage
//
// ```
// ambient_rain(freq) : _
// ```
//
// Where:
//
// * `freq`: general frequency of the raindrops, best results
//               in the range 5-50
//
// #### Examples
//
// ```
// ambient_rain(10) <: (_, _);
// ```
//
//------------------------------------------------------------

path(d, g, f1, f2, f1o, f2o, q, s) = (+(s) : de.delay(300, ds) : *(g) <:
             (flt(f2, f2o), flt(f1, f1o), _)) ~ (_) : (si.block(1), _, _)
    with {
        ds = ba.sec2samp(d / 1000);
        flt(f, fo) = fi.resonbp(f, q, 1) * os.osc(fo);
    };

glasswindow = (reroutei : (path1, path2) : rerouteo) ~ (_, _) : (si.block(2), _)
    with {
        path1 = path(3.7, 0.61, 2007, 1994, 254, 669, 2.3);
        path2 = path(4.2, 0.61, 1986, 1969, 443, 551, 2.3);
        reroutei(i1, i2, i3) = (i3 + i2, i3 + i1);
        rerouteo(p1a, p1b, p2a, p2b) = (p1a, p2a, p1b + p2b);
    };

drops = out
    with {
        normcos(s) = cos(2 * ma.PI * s);
        noise = no.gnoise(10) : fi.resonbp(50, 1, 2) : fi.lowpass(1, 500);
        right = noise * noise : *(10);
        left = (noise * 80) + 40 : os.phasor(1): -(0.25) : normcos;
        hip = fi.highpass(1, 500);
        out = left * right : max(0.35) : -(0.35) : *(0.5) : hip : hip;
    };

rain_on_window = drops : fi.highpass(1, 9000) : *(15) : glasswindow;

ambient_rain(f) = drops2(f, 0.013, 0.05, 0.1)
    with {
        drops2(f, q, t, a) = no.noise : fi.resonbp(f, q, 200) : aa.clip(0, 1) :
                    max(t) : -(t) : sq : sq : *(a) : fi.highpass(1, 2000);
        sq(x) = x * x;
    };

process = rain_on_window + ambient_rain(10) : sp.spat(2, 0.1, 1);


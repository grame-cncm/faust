# Compiling for the Bela card
Here are some examples of commands you can use to compile Faust codes for the Bela card:  
- `faust2bela sinus.dsp`
- `faust2bela -midi sinusMIDI.dsp`
- `faust2bela -midi -nvoices 8 instru3FX.dsp`
- `faust2bela -midi -nvoices 8 -effect auto instruFXIntern.dsp`
- `faust2bela -midi -nvoices 8 -effect effect-echo.dsp instruFX.dsp`
- `faust2bela -osc sinusOSC.dsp`

Each command generates a C++ file called `render.cpp` (and optionally an `effect.cpp` file) that you can directly incorporate into a Bela project:
- Open the Bela environment
- Click on 'new project' → choose 'C++', a name for the project, and click on 'create'.
- Click on 'upload file':
- Select render.cpp and all others files (like effect.cpp) if exist.
- Click on RUN.
  
That's all!
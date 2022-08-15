%USERPROFILE%\GitHub\faust-jax-backend\build\bin\Debug\faust -lang jax -I %USERPROFILE%\GitHub\faustlibraries -cn MyDSP -A %USERPROFILE%/GitHub/faust-jax-backend/architecture/jax -a minimal.py faust_code.dsp -o model_faust_dsp.py
sed 's/\t/    /g' model_faust_dsp.py > model_faust_dsp1.py
rm model_faust_dsp.py
mv model_faust_dsp1.py model_faust_dsp.py
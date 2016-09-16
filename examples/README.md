# Faust Examples

This folder contains a series of example Faust codes organized in different sections. 

## Compiling the Examples

You can use any of the `faust2...` script installed on your system (go in `/tools/faust2appls` to get an exhaustive list) to compile the Faust codes available in this folder. For example, if you're a Mac user and you want to turn `filtering/vcfWahLab.dsp` into a standalone CoreAudio application with a Qt interface, just run:

```
faust2caqt filtering/vcfWahLab.dsp
``` 

Alternatively, you can use FaustLive, it's all pretty open ;)...
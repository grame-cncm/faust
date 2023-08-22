# faust2svgplot
## tool to create a svg of plotted values.

### usage
```
./faust2svgplot <your compilation parameters> <myamazingdsp.dsp> 

./myamazingdsp <-n (nb_samples)[default:4096]> <-bs (buffer_size)[default:1]> <-r (sample_rate)[default:44100]> <-s (start_at_sample)[default:0]> <-sp (split)[default:0]>
```
### basic example 
dsp code :
```
import("stdfaust.lib");
process = 
(
    (
        os.osc(100),
        os.square(100)*0.15,
        os.triangle(400)*0.15
    )
);
```
![example](/example.png)

#### notes
* in usage, insert in <myamazingdsp.dsp> your favourite faust dsp file


###  the probe metadata 
You can use the probe metadata in bargraph in order to plot at a different node of the dsp program.
dsp code example :
```cpp
import("stdfaust.lib");

SendtoOut(n) = vbargraph("[probe:%n]label%n",0,1);

process = 
(
    (
        ((os.osc(100):SendtoOut(1)),
        (os.square(100)*0.15:SendtoOut(2)),
        (os.triangle(400)*0.15:SendtoOut(3)))
        :>_
    )
);
```
![probe example](/probeexample.png)

### the split option
You can split your graph in multiples graph.svg for every probe and every channel.
* usage : `./myamazingdsp -sp 1`

![example](/splitexample.png)


#### notes
* The probes are evaluated at every buffer size end. 
If you want the maximum precision, you will need to have a buffer size of 1 sample (set to 1 by default)

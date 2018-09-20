# OSC Support

## Overview

Most Faust architectures provide 
[Open Sound Control (OSC)](http://opensoundcontrol.org/) support (the 
implementation is based internally on the *oscpack* library by Ross Bencina). 
This allows applications to be remotely controlled from any OSC-capable 
application, programming language, or hardware device. 

OSC support can be added to any Faust program (as long as the target 
architecture supports it: see tables below) simply by adding the `[osc:on]` 
metadata to the [standard `option` metadata](#standard-metadata):

```
declare options "[osc:on]";
```

The following tables provides a list of Faust architectures providing OSC support. 

| Audio System | Environment |
| --- | --- |
| Alsa | GTK, Qt, Console |
| Jack | GTK, Qt, Console |
| Netjack | GTK, Qt, Console |
| PortAudio | GTK, Qt |

<div style="text-align: center;">
**_Linux Faust Architectures with OSC Support_**
</div>

---

| Audio System | Environment |
| --- | --- |
| CoreAudio | Qt |
| Jack | Qt, Console |
| Netjack | Qt, Console |
| PortAudio | Qt |

<div style="text-align: center;">
**_OSX Faust Architectures with OSC Support_**
</div>

---

| Audio System | Environment |
| --- | --- |
| Jack | Qt, Console |
| PortAudio | Qt |

<div style="text-align: center;">
**_Windows Faust Architectures with OSC Support_**
</div>

---

| Environment |
| --- |
| Android |
| iOS | 
| JUCE | 
| Bela |

<div style="text-align: center;">
**_Other Faust Architectures with OSC Support_**
</div>

---

## Simple Example

<!-- TODO: check that we explain that some of these features are built-in in
stuff like the online editor. -->

To illustrate how OSC support works let's define a very simple noise generator 
with a level control (we'll call it `noise.dsp`):

<!-- faust-run -->
```
import("stdfaust.lib");
process = no.noise*hslider("level",0,0,1,0.01);
```
<!-- /faust-run -->

This example can be compiled as a standalone Jack Qt application with OSC 
support simply by running the following command:
	
```
faust2jaqt -osc noise.dsp
```

When the generated application is ran from the command line:

```
./noise 
```

various information is printed in the standard output, including:

```
Faust OSC version 0.93 application 'noise' is running on UDP ports 5510, 5511, 5512
```

Hence, the OSC module makes use of three different UDP ports:

* `5510` is the listening port number: control messages should be addressed to 
this port.
* `5511` is the output port number: control messages sent by the application 
and answers to query messages are sent to this port.
* `5512` is the error port number: used for asynchronous error notifications.

These OSC parameters can be changed from the command line using one of the 
following options:

* `-port number` sets the port number used by the application to receive 
messages.
* `-outport number` sets the port number used by the application to transmit 
messages.
* `-errport number` sets the port number used by the application to transmit 
error messages.
* `-desthost host` sets the destination host for the messages sent by the 
application.
* `-xmit 0|1|2` turns transmission OFF, ALL, or ALIAS (default OFF). When 
transmission is OFF, input elements can be controlled using their addresses or 
aliases (if present). When transmission is ALL, input elements can be controlled 
using their addresses or aliases (if present), user's actions and output 
elements (i.e., `bargraph`, etc.) are transmitted as OSC messages as well as 
aliases (if present). When transmission is ALIAS, input elements can only be 
controlled using their aliases, user's actions and output elements are 
transmitted as aliases only.
* `-xmitfilter path` allows to filter output messages. Note that `path` can be 
a regular expression (like `/freeverb/Reverb1/*`).

For example:

```
./noise -xmit 1 -desthost 192.168.1.104 -outport 6000
```

will run `noise` with transmission mode ON, using `192.168.1.104` on port `6000`
as destination.

## Automatic Port Allocation

In order to address each application individually, only one application can be 
listening on a single port at one time. Therefore when the default incoming port 
5510 is already opened by some other application, an application will 
automatically try increasing port numbers until it finds an available port. 
Let say that we start `noise` and `mixer` (two Faust-generated applications 
with OSC support) on the same machine, we'll get the following:

```
$ ./noise &
...
Faust OSC version 0.93 application 'noise' is running on UDP ports 5510, 5511, 5512
$ ./mixer
...
Faust OSC version 0.93 application 'mixer' is running on UDP ports 5513, 5511, 5512
```

The `mixer` application fails to open the default incoming port `5510` because 
it is already opened by `noise`. Therefore it tries to find an available port 
starting from `5513` and opens it. Please note that the two outcoming ports 
`5511` and `5512` are shared by all running applications.

## Discovering OSC Applications

The commands `oscsend` and `oscdump` from the liblo package provide a 
convenient mean to experiment with OSC control and potentially debug 
applications with OSC support. 

> `oscsend [hostname] [port] [address] [types] [values]`: sends OSC messages 
via UDP. `[types]` is a string, the letters indicates the type of the following 
values: `i=integer`, `f=float`, `s=string`, etc.

> `oscdump [port]`: receives OSC messages via UDP and dump to standard output

> Note that OSC messages can be sent from any OSC-compatible applications
(e.g., PureData, Max/MSP, etc.).

In the following examples, we'll use two separate terminal windows. The first 
one will be used to send OSC messages to the `noise` application using 
`oscsend`. The second terminal will be used to monitor the messages sent by the 
application using `oscdump`. Commands executed on terminal 1 will be preceded 
by `T1$`. Messages received on terminal 2 will be preceded by `T2:`. To monitor 
on terminal T2 the OSC messages received on UDP port 5511, `oscdump` will be 
used:

```
T2$ oscdump 5511
```

Once set we can use the `hello` message to scan UDP ports for Faust 
applications. For example:

```
T1$ oscsend localhost 5510 "/*" s hello
```

gives us the root message address, the network and the UDP ports used by the 
noise application:

```
T2: /noise siii "192.168.1.102" 5510 5511 5512
```

## Discovering the OSC Interface of an Application

The OSC interface of an application (the set of OSC messages we can use to 
control it) can be discovered by sending the `get` message to the root:

```
T1$ oscsend localhost 5510 /noise s get 
```

As an answer to this OSC message, a full description is printed in terminal T2:

```
T2: /noise sF "xmit" #F
T2: /noise ss "desthost" "127.0.0.1"
T2: /noise si "outport" 5511
T2: /noise si "errport" 5512
T2: /noise/level fff 0.000000 0.000000 1.000000
```

The root of the OSC interface is `/noise`. Transmission is OFF, `xmit` is set 
to false. The destination host for sending messages is `127.0.0.1`, the output 
port is `5511` and the error port is `5512`. The application has only one user 
interface element: `/noise/level` with current value `0.0`, minimal value `0.0` 
and maximal value `1.0`.

## Widget's OSC Address

Each widget of an application has a unique OSC address obtained by 
concatenating the labels of it's surrounding groups with its own label. 

> There are potential conflicts between widget's labels and the OSC address 
space. An OSC symbolic name is an ASCII string consisting of a restricted set 
of printable characters. Therefore to ensure compatibility spaces are replaced 
by underscores and some other characters (asterisk, comma, forward, question 
mark, open bracket, close bracket, open curly brace, close curly brace) are 
replaced by hyphens.

Here is as an example [`mix4.dsp`](misc/mix4.dsp), a very simplified 
monophonic audio mixer with 4 inputs and one output. For each input we have a 
mute button and a level slider:

<!-- faust-run -->
```
input(v) = vgroup("input %v", *(1-checkbox("mute")) : *(vslider("level", 0, 0, 1, 0.01)));
process = hgroup("mixer", par(i, 4, input(i)) :> _);
```
<!-- /faust-run -->  
  
If we query this application:

```
T1$ oscsend localhost 5510 "/*" s get 
```

We get a full description of its OSC interface on terminal T2:

```
T2: /mixer sF "xmit" #F
T2: /mixer ss "desthost" "127.0.0.1"
T2: /mixer si "outport" 5511
T2: /mixer si "errport" 5512
T2: /mixer/input_0/level fff 0.0000 0.0000 1.0000
T2: /mixer/input_0/mute  fff 0.0000 0.0000 1.0000
T2: /mixer/input_1/level fff 0.0000 0.0000 1.0000
T2: /mixer/input_1/mute  fff 0.0000 0.0000 1.0000
T2: /mixer/input_2/level fff 0.0000 0.0000 1.0000
T2: /mixer/input_2/mute  fff 0.0000 0.0000 1.0000
T2: /mixer/input_3/level fff 0.0000 0.0000 1.0000
T2: /mixer/input_3/mute  fff 0.0000 0.0000 1.0000
```

As we can see, each widget has a unique OSC address obtained by concatenating 
the top level group label "mixer," with the "input" group label and the widget 
label (see the [Labels as Pathnames Section](labels-as-pathnames)). Please, note 
that blank spaces are replaced by underscores and metadata are removed during
this operation. 

All addresses must have a common root. This is the case in our example because 
there is a unique horizontal group `mixer` containing all widgets. If a common 
root is missing as in the following code:

```
input(v) = vgroup("input %v", *(1-checkbox("mute")) : *(vslider("level", 0, 0, 1, 0.01)));
process = par(i, 4, input(i)) :> _;
```

then a default vertical group is automatically create by the Faust compiler 
using the name of the file `mix4` as label:

<!-- TODO: is this still true? -->

```
T2: /mix4 sF "xmit" #F
T2: /mix4 ss "desthost" "127.0.0.1"
T2: /mix4 si "outport" 5511
T2: /mix4 si "errport" 5512
T2: /mix4/input_0/level fff 0.0000 0.0000 1.0000
T2: /mix4/input_0/mute  fff 0.0000 0.0000 1.0000
T2: /mix4/input_1/level fff 0.0000 0.0000 1.0000
T2: /mix4/input_1/mute  fff 0.0000 0.0000 1.0000
T2: /mix4/input_2/level fff 0.0000 0.0000 1.0000
T2: /mix4/input_2/mute  fff 0.0000 0.0000 1.0000
T2: /mix4/input_3/level fff 0.0000 0.0000 1.0000
T2: /mix4/input_3/mute  fff 0.0000 0.0000 1.0000
```

## Controlling the Application Via OSC

Any user interface element of the application can be controlled by sending one 
of the previously discovered messages/addresses. For example, to set the noise 
level of the application to `0.2` the following message can be sent:

```
T1$ oscsend localhost 5510 /noise/level f 0.2
```
	
If we now query `/noise/level` we get, as expected, the value `0.2`:

```
T1$ oscsend localhost 5510 /noise/level s get
T2: /noise/level fff 0.2000 0.0000 1.0000
```

## Turning Transmission ON

The `xmit` message at the root level is used to control the realtime 
transmission of OSC messages corresponding to user interface's actions. For 
example:

```
T1$ oscsend localhost 5510 /noise si xmit 1
```

turns transmission in `ALL` mode. Now if we move the level slider we get a 
bunch of messages:

```
T2: /noise/level f 0.024000
T2: /noise/level f 0.032000
T2: /noise/level f 0.105000
T2: /noise/level f 0.250000
T2: /noise/level f 0.258000
T2: /noise/level f 0.185000
T2: /noise/level f 0.145000
T2: /noise/level f 0.121000
T2: /noise/level f 0.105000
T2: /noise/level f 0.008000
T2: /noise/level f 0.000000
```

This feature can be typically used for automation to record and replay actions 
on the user interface, or to remote control from one application to another. 
It can be turned OFF any time using:

```
T1$ oscsend localhost 5510 /noise si xmit 0
```

Use the ALIAS (`xmit = 2`) mode if you need to restrict the access to your 
program: when the ALIAS mode is used, only aliases of input elements (sliders, 
buttons...) can be used to control them, and output elements (bargraph) will 
only emit on their aliases.

## Filtering OSC Messages

When the transmission of OSC messages is ON, all the user interface elements 
are sent through the OSC connection.  

```
T2: /harpe/level f 0.024000
T2: /harpe/hand f 0.1
T2: /harpe/level f 0.024000
T2: /harpe/hand f 0.25
T2: /harpe/level f 0.024000
T2: /harpe/hand f 0.44
T2: /noise/level f 0.145000
T2: /harpe/hand f 0.78
T2: /noise/level f 0.145000
T2: /harpe/hand f 0.99
```

We can choose to filter unwanted parameters (or group of parameters).  For 
example:

```
T1$ oscsend localhost 5510 /harpe si xmit 1 xmitfilter /harpe/level
```

As a result, we will receive:

```
T2: /harpe/hand f 0.1
T2: /harpe/hand f 0.25
T2: /harpe/hand f 0.44
T2: /harpe/hand f 0.78
```

To reset the filter, send:

```
T1$ oscsend localhost 5510 /harpe si xmit 1 xmitfilter
```

## Using OSC Aliases

Aliases are a convenient mechanism to control a Faust application from a 
preexisting set of OSC messages. 

Let's say we want to control our previous noise example with 
[TouchOSC](https://hexler.net/software/touchosc-android) on Android. The first 
step is to configure the TouchOSC host to `192.168.1.102` (the host running our 
noise application) and outgoing port to `5510`. 

Then we can use `oscdump 5510` (after quitting the noise application in order 
to free port `5510`) to visualize the OSC messages sent by TouchOSC. Let's use 
for that the left slider of "simple layout". Here is what we get:

<!-- TODO: not sure about all this: at least we could add a figure with the 
interface but do we even want to use TouchOSC at all? -->

```
T2: /1/fader1 f 0.000000
T2: /1/fader1 f 0.004975
T2: /1/fader1 f 0.004975
T2: /1/fader1 f 0.008125
T2: /1/fader1 f 0.017473
T2: /1/fader1 f 0.032499
T2: /1/fader1 f 0.051032
T2: ...
T2: /1/fader1 f 0.993289
T2: /1/fader1 f 1.000000
```

We can associate this OSC message to the noise level slider by inserting the 
metadata `[osc:/1/fader1 0 1]` into the slider's label:

> Several osc aliases can be inserted into a single label allowing the same 
widget to be controlled by several OSC messages

```
import("stdfaust.lib");
process = no.noise*hslider("level[osc:/1/fader1 0 1]",0,0,1,0.01);
```
	
Because the range of `/1/fader1` is 0 to 1 (like the level slider), we can 
remove the range mapping information and write simply :

```
import("stdfaust.lib");
process = no.noise*hslider("level[osc:/1/fader1]",0,0,1,0.01);
```
	
TouchOSC can also send accelerometer data by enabling 
`Settings/Options/Accelerometer`. Using again `oscdump 5510` we can visualize 
the messages sent by TouchOSC:

```
T2: ...
T2: /accxyz fff -0.147842 0.019752 9.694721
T2: /accxyz fff -0.157419 0.016161 9.686341
T2: /accxyz fff -0.167594 0.012570 9.683948
T2: ...
```

As we can see, TouchOSC sends the x, y and z accelerometers in a single message, 
as a triplet of values ranging approximately from -9.81 to 9.81. In order to 
select the appropriate accelerometer, we need to concatenate to `/accxyz` a 
suffix `/0`, `/1` or `/2`. For example `/accxyz/0` will correspond to x, 
`/accxyz/1` to y, etc. We also need to define a mapping because the ranges are 
different:

```
import("stdfaust.lib");
process = no.noise * hslider("level[osc:/accxyz/0 0 9.81]",0,0,1,0.01);
```

| **alias** | **description** |
| --- | --- |
| `[osc:/1/rotary1 0 1]` | top left rotary knob |
| `[osc:/1/rotary2 0 1]` | middle left rotary knob |
| `[osc:/1/rotary3 0 1]` | bottom left rotary knob |
| `[osc:/1/push1 0 1]` | bottom left push button |
| `[osc:/1/push2 0 1]` | bottom center left push button |
| `[osc:/1/toggle1 0 1]` | top center left toggle button |
| `[osc:/1/toggle2 0 1]` | middle center left toggle button |
| `[osc:/1/fader1 0 1]` | center left vertical fader |
| `[osc:/1/toggle3 0 1]` | top center right toggle button |
| `[osc:/1/toggle4 0 1]` | middle center right toggle button |
| `[osc:/1/fader2 0 1]` | center right vertical toggle button |
| `[osc:/1/rotary4 0 1]` | top right rotary knob |
| `[osc:/1/rotary5 0 1]` | middle right rotary knob |
| `[osc:/1/rotary6 0 1]` | bottom right rotary knob |
| `[osc:/1/push3 0 1]` | bottom center right push button |
| `[osc:/1/push4 0 1]` | bottom right push button |
| `[osc:/1/fader3 0 1]` | bottom horizontal fader |
| `[osc:/accxyz/0 -10 10]` |  $x$ accelerometer |
| `[osc:/accxyz/1 -10 10]` |  $y$ accelerometer |
| `[osc:/accxyz/2 -10 10]` |  $z$ accelerometer |

<div style="text-align: center;">
**_Examples of OSC Message Aliases for TouchOSC (Layout Mix2)._**
</div>

## OSC Cheat Sheet

### Default Ports

| Port | Description |
| --- | --- |
| `5510` | default listening port |
| `5511` | default transmission port |
| `5512` | default error port |
| `5513` | alternative listening ports |

### Command Line Options

| Option | Description |
| --- | --- |
| `-port n` | set the port number used by the application to receive messages |
| `-outport n` | set the port number used by the application to transmit messages |
| `-errport n` | set the port number used by the application to transmit error messages |
| `-desthost h` | set the destination host for the messages sent by the application |
| `-xmit 0|1|2` | turn transmission OFF, ALL or ALIAS (default OFF) |
| `-xmitfilter s` | filter the Faust paths at emission time |

### Discovery Messages

| Message | Description |
| --- | --- |
| `oscsend host port "/*" s hello` | discover if any OSC application is listening on port *p* |
| `oscsend host port "/*" s get` | query OSC interface of application listening on port *p* |

### Control Messages

| Message | Description |
| --- | --- |
| `oscsend host port "/*" si xmit 0|1|2` | set transmission mode |
| `oscsend host port widget s get` | get widget's value |
| `oscsend host port widget f v` | set widget's value |

### Alias

| Alias | Description |
| --- | --- |
| `"...[osc: address lo  hi ]..."` | alias with $lo \rightarrow min$, $hi \rightarrow max$ mapping |
| `"...[osc:' address]..."` | alias with *min*, *max* clipping |


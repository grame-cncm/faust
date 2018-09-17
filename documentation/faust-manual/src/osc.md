# OSC Support

## Overview

Most Faust architectures provide 
[Open Sound Control (OSC)](http://opensoundcontrol.org/) support (the 
implementation is based internally on the *oscpack* library by Ross Bencina). 
This allows applications to be remotely controlled from any OSC-capable 
application, programming language, or hardware device. OSC support can be 
activated using the `-osc` option when building the application with the 
appropriate [`faust2xxx` command](TODO). The following table provides a list of 
Faust architectures providing OSC support. 

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

In the following example, we'll use two separate terminal windows. The first 
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

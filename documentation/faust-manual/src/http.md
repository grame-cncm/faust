# HTTP Support

Similarly to OSC, several Faust architectures also provide HTTP support. This 
allows Faust applications to be remotely controlled from any Web browser using 
specific URLs. Moreover OSC and HTTPD can be freely combined.

While OSC support is installed by default when Faust is built, this is not the 
case for HTTP. That's because it depends on the GNU *libmicrohttpd* library 
which is usually not installed by default on the system. An additional 
`make httpd` step is therefore required when compiling and installing Faust:

```
make httpd
make
sudo make install
```

Note that `make httpd` will fail if *libmicrohttpd* is not available on the 
system.

HTTP support can be added to any Faust program (as long as the target 
architecture supports it: see tables below) simply by adding the `[http:on]` 
metadata to the [standard `option` metadata](#standard-metadata):

```
declare options "[http:on]";
```

The following tables lists Faust's architectures providing HTTP support: 

| Audio System | Environment |
| --- | --- |
| Alsa | GTK, Qt, Console |
| Jack | GTK, Qt, Console |
| Netjack | GTK, Qt, Console |
| PortAudio | GTK, Qt |

<div style="text-align: center;">
**_Linux Faust Architectures with HTTP Support_**
</div>

---

| Audio System | Environment |
| --- | --- |
| CoreAudio | Qt |
| Jack | Qt, Console |
| Netjack | Qt, Console |
| PortAudio | Qt |

<div style="text-align: center;">
**_OSX Faust Architectures with HTTP Support_**
</div>

---

| Audio System | Environment |
| --- | --- |
| Jack | Qt, Console |
| PortAudio | Qt |

<div style="text-align: center;">
**_Windows Faust Architectures with HTTP Support_**
</div>

---

## A Simple Example

To illustrate how HTTP support works, let's reuse our previous 
[`mix4.dsp`](misc/mix4.dsp) example, a simple monophonic audio mixer with 4 
inputs and one output. For each input we have a mute button and a level slider:

<!-- faust-run -->
```
input(v) = vgroup("input %v", *(1-checkbox("mute")) : *(vslider("level", 0, 0, 1, 0.01)));
process  = hgroup("mixer", par(i, 4, input(i)) :> _);
```
<!-- /faust-run -->

This example can be compiled as a standalone Jack QT application with HTTP 
support using the command:

```
faust2jaqt -httpd mix4.dsp
```

The `-httpd` option embeds a small Web server into the generated application. 
Its purpose is to serve an HTML page implementing the interface of the app. 
This page makes use of JavaScript and SVG, and is quite similar to the native 
QT interface.

When the application is started from the command line:

```
./mix4 
```

various information are printed on the standard output, including:

```
Faust httpd server version 0.73 is running on TCP port 5510
```

As we can see, the embedded Web server is running by default on TCP port 5510. 
The entry point is <http://localhost:5510>. It can be open from any recent 
browser and it produces the page presented in the figure below:

<img src="img/mix4-http.png" class="mx-auto d-block" width="70%">

## JSON Description of the User Interface

The communication between the application and the Web browser is based on 
several underlying URLs. The first one is <http://localhost:5510/JSON> that 
returns a JSON description of the user interface of the application. This 
JSON description is used internally by the JavaScript code to build the 
graphical user interface. Here is (part of) the json returned by `mix4`:

```
{
  "name": "mix4",
  "address": "YannAir.local",
  "port": "5511",
  "ui": [
    {
      "type": "hgroup",
      "label": "mixer",
      "items": [
        {
          "type": "vgroup",
          "label": "input_0",
          "items": [
            {
              "type": "vslider",
              "label": "level",
              "address": "/mixer/input_0/level",
              "init": "0", "min": "0", "max": "1", 
              "step": "0.01"
            },
            {
              "type": "checkbox",
              "label": "mute",
              "address": "/mixer/input_0/mute",
              "init": "0", "min": "0", "max": "0", 
              "step": "0"
            }
          ]
        },
        
        ...
        
      ]
    }
  ]
}
```

## Querying the State of the Application

Each widget has a unique "address" field that can be used to query its value. 
In our example here the level of the input 0 has the address 
`/mixer/input_0/level`. The address can be used to forge a URL to get the 
value of the widget: <http://localhost:5510/mixer/input_0/level>, resulting in:

```
/mixer/input_0/level 0.00000  
```

Multiple widgets can be queried at once by using an address higher in the 
hierarchy. For example to get the values of the level and the mute state of 
input 0 we use <http://localhost:5510/mixer/input_0>, resulting in:

```
/mixer/input_0/level 0.00000 
/mixer/input_0/mute  0.00000 
```

To get the all the values at once we simply use <http://localhost:5510/mixer>, 
resulting in:

```
/mixer/input_0/level 0.00000 
/mixer/input_0/mute  0.00000 
/mixer/input_1/level 0.00000 
/mixer/input_1/mute  0.00000 
/mixer/input_2/level 0.00000 
/mixer/input_2/mute  0.00000 
/mixer/input_3/level 0.00000 
/mixer/input_3/mute  0.00000 
```

## Changing the Value of a Widget

<img src="img/mix4-http-mute.png" class="mx-auto d-block" width="70%">

Let's say that we want to mute input 1 of our mixer. For that purpose, we can
use the URL <http://localhost:5510/mixer/input_1/mute?value=1> obtained by 
concatenating `?value=1` at the end of the widget URL. 

All widgets can be controlled in a similar way. For example 
<http://localhost:5510/mixer/input_3/level?value=0.7> will set the input 3 
level to 0.7.

## Proxy Control Access to the Web Server

A control application may want to access and control the running DSP using 
its Web server, but without using the delivered HTML page in a browser. Since 
the complete JSON can be retrieved, control applications can be purely 
developed in C/C++. A *proxy* version of the user interface can then be built, 
and parameters can be "set and get" using HTTP requests. 

This mode can be started dynamically using the `-server URL` parameter. 
Assuming an application with HTTP support is running remotely at the given 
URL, the control application will fetch its JSON description, use it to 
dynamically build the user interface, and allow for the access of the remote 
parameters.

## HTTP Cheat Sheet

Here is a summary of the various URLs used to interact with the application's 
Web server.

### Default Ports

| Port | Description |
| --- | --- |
| `5510` | default TCP port used by the application's Web server |
| `5511...` | alternative TCP ports |

### Command Line Options

| Option | Description |
| --- | --- |
| `-port n` | set the TCP port number used by the application's Web server |
| `-server URL` | start a proxy control application accessing the remote application running on the given URL |

### URLs

| URL | Description |
| --- | --- |
| `http://host:port` | the base URL to be used in proxy control access mode |
| `http://host:port/JSON` | get a json description of the user interface |
| `http://host:port/address` | get the value of a widget or a group of widgets |
| `http://host:port/address?value=v` | set the value of a widget to `v`


### JSON

**Top Level**

The JSON describes the name, host, and port of the application and a hierarchy 
of user interface items:

```
{
  "name": <name>,
  "address": <host>,
  "port": <port>,
  "ui": [ <item> ]
}
```

An `<item>` is either a group (of items) or a widget.

**Groups**

A group is essentially a list of items with a specific layout: 

```
{
	"type": <type>,
	"label": <label>,
	"items": [ <item>, <item>,...]
}
```

The `<type>` defines the layout. It can be either `"vgroup"`, `"hgroup"` or 
`"tgroup"`

**Widgets**

```
{
	"type": <type>,
	"label": <label>,
	"address": <address>,
	"meta": [ { "key": "value"},... ],
	"init": <num>,
	"min": <num>,
	"max": <num>,
	"step": <num>
},
```

Widgets are the basic items of the user interface. They can be of different 
`<type>`: `"button"`,  `"checkbox"`, `"nentry"`, `"vslider"`, `"hslider"`, 
`"vbargraph"` or `"hbargraph"`.


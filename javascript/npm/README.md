# Faust Web Audio Library

The Faust Web Audio library provides a high level Javascript API over the [Faust](https://faust.grame.fr) compiler. The interface is designed to be used with [TypeScript](https://www.typescriptlang.org/), but describes and documents the API for pure Javascript as well. This document provides an overview of the differents levels of the API. Examples of use are also provided in the `exemples`folder.


## Table of Content

-  [Organisation of the API](#org)

  - [Faust Compiler WebAssembly module](#module)
  - [Faust Compiler Javascript Interface](#compiler)
  - [Faust Wasm Instance](#wasm)
  - [Faust Audio Nodes Instances and Offline Processor ](#audio)
  - [High-level API](#high)
  - [How to use with typescript](#tsuse)
- [Dynamic and Static Instances](#ds)
- [Misc. services](#misc)
- [Important note](#note)


## Organisation of the API <a name="org"></a>

The API is organised from low to high level as illustrated by the figure below.

![Overview](https://github.com/grame-cncm/faust/raw/wasm2/javascript/npm/imgs/overview.png)

### Faust Compiler WebAssembly module <a name="module"></a>

The first level is the Faust compiler compiled as a wasm library named `libfaust-wasm`.
It consists in 3 different files:

- `libfaust-wasm.wasm` : the Faust compiler provided as a WebAssembly module 
- `libfaust-wasm.js` : a javascript loader of the WebAssembly module
- `libfaust-wasm.data` : a virtual file system containing the Faust libraries.

You must include `libfaust-wasm.js` in your html page. The loader will take care of providing an instance of the Faust WebAssembly module and of the associated virtual file system (libfaust-wasm.data). Note that depending on the relative location of `libfaust-wasm.js`, the loader may fail to find  `libfaust-wasm.data`; in this case, the simple solution consists in copying  `libfaust-wasm.data` aside the refering web page.


### Faust Compiler Javascript Interface <a name="compiler"></a>

The Faust Compiler Javascript interface is described in `FaustCompiler.d.ts`.   
It provides *classic* Faust compilation services, which output is a raw WebAssembly module with an associated JSON description of the module.


### Faust Wasm Instance <a name="wasm"></a>

This level takes a WebAssembly module produced by the Faust compiler or a precompiled module loaded from a file, and builds an instance of this module with the proper Wasm memory layout, ready to run, but not yet connected to any audio node. It is described in `FaustGenerator.d.ts`.   


### Faust Audio Nodes Instances and Offline Processor <a name="audio"></a>

This level takes a Faust Wasm instance to build an audio node. [AudioWorklet](https://developer.mozilla.org/fr/docs/Web/API/AudioWorklet) and [ScriptProcessor](https://developer.mozilla.org/en-US/docs/Web/API/ScriptProcessorNode) nodes are supported.  

Note that ScriptProcessor is marked as [deprecated](https://developer.mozilla.org/en-US/docs/Web/API/ScriptProcessorNode) but it's the only audio architecture available on Safari. Both monophonic (generators, effects...) or polyphonic (instruments) nodes can be created.

By default, and to save CPU, created audio nodes are not processing audio buffers. They have to be explicitely started with the `start` method (and possibly stopped if needed using the `stop`method).

**Warning**: AudioWorklet is a recent technology and may not be supported by all the browsers. Check the [compatibility](https://developer.mozilla.org/fr/docs/Web/API/AudioWorklet) chart.

An offline processor to render a DSP in a non real-time context and get the computed frames is available. It is described in `FaustWebAudio.d.ts`. It will automatically use the `start` and `stop` methods internally to activate actual rendering in its `plot` method. 


### High-level API <a name="high"></a>

A high-level API is available to compile a DSP program and create the audio node, either monophonic or polyphonic. It is described in `index.d.ts`. More generally, the `Faustxxx.d.ts`files describe interfaces and `index.d.ts` describes functions and includes the interface files.

### How to use with typescript <a name="tsuse"></a>

Simply include the following to get access to types and functions:
~~~~~~~~~~~~~~~
///<reference types="@grame/libfaust"/>
~~~~~~~~~~~~~~~

## Dynamic and Static Instances <a name="ds"></a>

The Faust Wasm and Audio Node levels make it possible to generate instances from Faust dsp code as well as from pre-compiled WebAssembly modules.
In the latter case, it is not necessary to include the `libfaust-wasm.js` library, `FaustLibrary.js` is sufficient to provide the required services.
This allows to generate lighter and faster-loading HTML pages.

**Note**: to create a polyphonic instance from a pre-compiled WebAssembly module, an additional `mixer32.wasm` file (or `mixer64.wasm`  when compiled in `-double` ) is required and must be present at the same level as the referring HTML page. This module is part of the `dist` folder.


## Misc. services <a name="misc"></a>

- `FaustUtilities.d.ts`: provides facilities to browse Faust generated SVG diagrams
- `FaustWAP.d.ts`: provides [Web Audio Plugins](https://hal.univ-cotedazur.fr/hal-01893660/document) API support.


## Important note <a name="note"></a>

Html pages embedding the Faust compiler must be served using https, unless using http://localhost.

----
<a href="http://faust.grame.fr"><img src=https://faust.grame.fr/community/logos/img/LOGO_FAUST_COMPLET_ORANGE.png width=200 /></a>






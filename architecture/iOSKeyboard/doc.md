# Faust iOS Keyboard Documentation
Faust iOS Keyboard (`SmartKeyboard`) is a special version of the Faust iOS architecture whose goal is to create Faust smartphone applications with a touch screen interface better adapted to musical performance. Indeed, while "traditional" Faust iOS applications build the user interface based on the description provided in the Faust code with sliders, knobs, buttons, etc., the iOS Keyboard architecture replaces this interface by a highly configurable keyboard that can easily be turned into a drum pad, an isomorphic keyboard keyboard, an X/Y control interface, etc. 

## Configuration

By default, a `SmartKeyboard` has 4 keyboards in parallel and each of them has 13 keys. All of them are chromatic keyboards and the lowest MIDI note of each one are respectively (from top to bottom): 48, 60, 72, 84. The name of the notes are diplayed and when a key is pressed its color changes. 

Any Faust code compiled with `faust2iosKeyboard` will have this interface by default instead of the usual sliders, knobs, etc.

`SmartKeyboard` can be used to control a Faust audio process by declaring a set of standard parameters in it. It takes care of turning the Faust audio process into a polyphonic object. The rule is that for each finger on the screen, a new voice of polyphony is created. If the keyboard is in quantized mode "0" (see *Confuration Keys*), voices are terminated and allocated everytime a finger slides to a new key. 

We'll see later in the *Confuration Keys* section that the maximum number of voices of polyphony can be given in the `SmartKeyboard` configuration in the Faust code.

### `SmartKeyboard` Standard Parameters

`SmartKeyboard` standard parameters can be declared using any continuous Faust UI element (`hslider`, `vslider` and `nentry`). For example, if the goal is to control the frequency of a Faust object, a `frequency` variable could be declared as such:

```
frequency = hslider("freq",200,100,1000,0.1);
```

By using `freq` as the name of the slider, `frequency` is now controlled by the `SmartKeyboard` interface.

The standard parameters of `SmartKeyboard` are: 

* `freq`: the frequency of key of the current keyboard. If the keyboard is not quantized mode 0, frequency will be continuous or rounded.
* `gate`: the trigger signal sent when a finger touches the screen (1) or when it stops touching it (0). In quantized mode "0", "0" and "1" are sent everytime a finger slides to a new key (a new voice is allocated everytime).
* `keyboard`: the keyboard ID of the current keyboard. The top keyboard has always ID number 0, etc.
* `key`: the key ID in the current keyboard. The first key on the left has always ID number 0, etc.
* `x`: the normalized (0-1) X position of the finger in the current key.
* `y`: the normalized (0-1) Y position of the finger in the current key.

All these parameters don't have to always be declared: it's the programmer's choice to choose which one is needed for his application. 

### Confuguration Keys

To configure the `SmartKeyboard` interface, it has to be declared as such anywhere in the Faust code:

```
declare interface "SmartKeyboard{}";
```

An unlimited number of pairs of keys and values can be given between the curly brackets of `SmartKeyboard{}`.  For example, a `SmartKeyboard` with 2 keyboards where the top keyboard has 6 keys and the bottom one has 7 keys would be declared as such:

```
declare interface "SmartKeyboard{
	'nKeyb':'2',
	'keyb0_nKeys':'6',
	'keyb1_nKeys':'7'
}";
```

The following keys can be used to configure a `SmartKeyboard` interface:

* `nKeyb`: the number of keyboards (default: 4)
* `maxFingers`: the maximum number of fingers allowed on the interface in general. This also configures the maximum number of voices of polyphony. (default: 10)
* `maxKeybPoly`: the maximum number of voices of polyphony for each keyboard (default: 10)
* `monoMode`: configures the way the case when the number of fingers present on a specific keyboard is greater than `maxKebPoly` is handled:
	* `monoMode = 0`: priority goes to fingers already present on the keyboard
	* `monoMode = 1`: priority comes to new fingers entering the keyboard
	* `other modes`: more modes (priority to lowest keys, priority to highest keys, etc.) are currently being implemented but are not available yet.
* `quantizationMode`: controls the way the `freq` parameter is quantized:
	* `quantizationMode = 0`: keys are fully quantized (frequencies are quantized to the nearest corresponding integer MIDI number).
	* `quantizationMode = 1`: continuous mode: no quantization mode at all - the position of the finger on the keyboard is fully continuous.
	* `quantizationMode = 2`: "pitch-rounding" mode: pitches are quantized when a finger is not moving and are continuous when a finger is moving.
* `interKeybSlideAllowed`: when 0, fingers can't slide from one keyboard to another.
* `keybN_nKeys`: the number of keys of a specific keyboard where `N` is the keyboard ID.
* `keybN_lowestKey`: the lowest key as a MIDI number of a specific keyboard where `N` is the keyboard ID.
* `keybN_scale`: the scale of a specific keyboard where `N` is the keyboard ID:
	* `keybN_scale = 0`: chromatic scale
	* `keybN_scale = 1`: major scale
* `keybN_showNotesName`: when 0, hides the name of the notes on the keys. `N` is the keyboard ID.
* `keybN_rootPos`: shifts the position of the fundamental relatively to the lowest key on the keyboard. This is useful when `keybN_scale != 0`. `N` is the keyboard ID.
* `keybN_orientation`: when `>0`, reverses the orientation of the keyboard (right to left instead of left to right). `N` is the keyboard ID.
* `keybN_keybMode`: when `>0`, "keyboard mode" is activated which means that pitch names are displayed and keys change colors when they are touched. The whole point of having this functionality is that it allows to configure a `SmartKeyboard` as a drum pad for example by having 2 keyboards of 2 keys each (see example section below). `N` is the keyboard ID. 

## Usage

A Faust code can be compiled as an iOS keyboard application simply by using the `faust2iosKeybaord` compilation script:

```
faust2iosKeyboard yourFaustCode.dsp
```

To see all the options, just run:

```
faust2iosKeyboard -h
```

WARNING: In order for compilation to be successful, you need to have a valid iOS signing identity. To see how to solve this problem, just run something like:

```
faust2iosKeyboard -xcode yourFaustCode.dsp
```

and open the generated xcode project. Run it and try to fix the app signing issue. It should be pretty straight forward...

## Examples

See the examples folder...
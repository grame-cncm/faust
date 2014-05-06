/*
faust2webaudio

Primarily written by Myles Borins
During the Spring 2013 offering of Music 420b with Julius Smith
A bit during the Summer of 2013 with the help of Joshua Kit Clayton
And finally a sprint during the late fall of 2013 to get everything working
A Special thanks to Yann Orlarey and Stéphane Letz

faust2webaudio is distributed under the terms the MIT or GPL2 Licenses.
Choose the license that best suits your project. The text of the MIT and GPL
licenses are at the root directory.

Additional code : GRAME 2014
 
*/

/*global webkitAudioContext, Module, HEAPF32, HEAP32, Pointer_stringify, ALLOC_STACK, intArrayFromString, allocate*/

var faust = faust || {};

// Shim AudioContext on webkit
window.AudioContext = window.AudioContext || window.webkitAudioContext || undefined;

(function () {


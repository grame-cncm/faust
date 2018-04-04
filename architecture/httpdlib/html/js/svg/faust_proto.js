/**
This module provides classes for the parsing of a JSON describing
a faust interface and the realization of that interface in SVG.

It also allows for interaction between this interface and a server.

@module Faust Web UI
@main Faust Web UI
**/

/**
Extension of the JavaScript String class.

@class String
@for
@constructor
**/

/**
Formats a string in a pythonic way.  See
http://docs.python.org/2/library/string.html.

@method format
@for String
@param {Array} args The arguments to be inserted into the string.
@return {String} The formatted string.
**/
String.prototype.format = function (args) {
  var str = this;
  return str.replace(String.prototype.format_regex, function(item) {
    var intVal = parseInt(item.substring(1, item.length - 1));
    var replace;
    if (intVal >= 0) {
      replace = args[intVal];
    }
    else if (intVal === -1) {
      replace = "{";
    }
    else if (intVal === -2) {
      replace = "}";
    }
    else {
      replace = "";
    }
    return replace;
  });
}

/**
The regular expression used to find the insertion points
in a string that needs formatting.

@property format_regex
@for String
@type RegExp
**/
String.prototype.format_regex = new RegExp("{-?[0-9]+}", "g");

/**
Extension of the JavaScript Array class.

@class Array
@for
@constructor
**/

/**
Finds the maximum of a numerical array.

@method max
@for Array
@return {Number} The maximum of the array.
**/
Array.prototype.max = function() {
  var max = this[0];
  var len = this.length;
  for (var i = 1; i < len; i++) {
    if (this[i] > max) {
      max = this[i];
    }
  }
  return max;
}

/**
Finds the minimum of a numerical array.

@method min
@for Array
@return {Number} The minimum of the array.
**/
Array.prototype.min = function() {
  var min = this[0];
  var len = this.length;
  for (var i = 1; i < len; i++) {
    if (this[i] < min) {
      min = this[i];
    }
  }
  return min;
}

/**
Finds the sum of a numerical array.

@method sum
@for Array
@return {Number} The sum of the array.
**/
Array.prototype.sum = function() {
  var sum = 0;
  for (var i = 0; i < this.length; i++) {
    sum += this[i];
  }
  return sum;
}

/**
Provides the base class for the creation of a _f4u$t UI.
It functions more like a namespace than an object, so it
does not have a constructer and only contains classes and
static methods.

@class _f4u$t
@static
**/
var _f4u$t = {};

/**
Estimation of text height in layout computations.

@property TEXT_HEIGHT
@for _f4u$t
@type Number
@default 20
**/
_f4u$t.TEXT_HEIGHT = 20;

/**
Padding between text and other objects.

@property TEXT_PADDING
@for _f4u$t
@type Number
@default 10
**/
_f4u$t.TEXT_PADDING = 10;

/**
Width of value boxes.

@property VALUE_BOX_W
@for _f4u$t
@type Number
@default 60
**/
_f4u$t.VALUE_BOX_W = 60;

/**
Height of value boxes.

@property VALUE_BOX_H
@for _f4u$t
@type Number
@default 20
**/
_f4u$t.VALUE_BOX_H = _f4u$t.TEXT_HEIGHT;

/**
Padding between the bottom of the space an object occupies
and its text-box.

@property TEXT_BOX_PADDING
@for _f4u$t
@type Number
@default 3
**/
_f4u$t.TEXT_BOX_PADDING = 3;

// some convenience methods for inheritence

/**
Used as a placeholder to define constructors via
_f4u$t.extend

@method surrogateCtor
@for _f4u$t
@static
**/
_f4u$t.surrogateCtor = function() {}

/**
Used to make one class inherit from another.

@method extend
@for _f4u$t
@static
@param {Object} base The base class to be inherited from.
@param {Object} sub The class doing the inheriting.
**/
_f4u$t.extend = function(base, sub) {
  // Copy the prototype from the base to setup inheritance
  _f4u$t.surrogateCtor.prototype = base.prototype;
  sub.prototype = new _f4u$t.surrogateCtor();
  // Remember the constructor property was set wrong, let's fix it
  sub.prototype.constructor = sub;
}

/**
Identity function.

@method identity
@for _f4u$t
@static
@param {Object} value The value to return
@return {Object} The input value
**/
_f4u$t.identity = function(value) {
  return value;
}

/**
Enum-like constant for the X axis.

@property X_AXIS
@for _f4u$t
@type Number
@default 0
**/
_f4u$t.X_AXIS = 0;

/**
Enum-like constant for the Y axis.

@property Y_AXIS
@for _f4u$t
@type Number
@default 1
**/
_f4u$t.Y_AXIS = 1;

/**
Enum-like constant for no axes left to consult,
used in iterating.

@property NO_AXES
@for _f4u$t
@type Number
@default 2
**/
_f4u$t.NO_AXES = 2;

/**
Enum-like constant for the left side.

@property LEFT
@for _f4u$t
@type Number
@default -1
**/
_f4u$t.LEFT = -1;

/**
Enum-like constant for the right side.

@property RIGHT
@for _f4u$t
@type Number
@default 1
**/
_f4u$t.RIGHT = 1;

/**
Enum-like constant for the up side.

@property UP
@for _f4u$t
@type Number
@default -1
**/
_f4u$t.UP = -1;

/**
Enum-like constant for the down side.

@property DOWN
@for _f4u$t
@type Number
@default 1
**/
_f4u$t.DOWN = 1;
_f4u$t.CENTER = 0;

/**
Representation of none, null, the abyss, the ether, etc..

@property NULL
@for _f4u$t
@default null
**/
_f4u$t.NONE = null;

/**
RGB value of the color black in an array.

@for _f4u$t
@property BLACK
@type Array
@default [0,0,0]
**/
_f4u$t.BLACK = [0,0,0];

/**
RGB value of the color white in an array.

@property WHITE
@for _f4u$t
@type Array
@default [255,255,255]
**/
_f4u$t.WHITE = [255,255,255];

/**
RGB value of the color cyan in an array.

@property CYAN
@for _f4u$t
@type Array
@default [0,255,255]
**/
_f4u$t.CYAN = [0,255,255];

/**
RGB value of the color cyan in an array.

/**
RGB value of the color grey in an array.

@property GREY
@for _f4u$t
@type Array
@default [100,100,100]
**/
_f4u$t.GREY = [100,100,100];

/**
RGB value of the color pink in an array.

@property PINK
@for _f4u$t
@type Array
@default [233,150,122]
**/
_f4u$t.PINK = [233,150,122];

/**
RGB value of the color green in an array.

@property GREEN
@for _f4u$t
@type Array
@default [173,255,47]
**/
_f4u$t.GREEN = [173,255,47];

/**
RGB value of the color kermit in an array.

@property KERMIT
@for _f4u$t
@type Array
@default [47,243,160]
**/
_f4u$t.KERMIT = [47,243,160];

/**
RGB value of the color pale green in an array.

@property PALEGREEN
@for _f4u$t
@type Array
@default [152,251,152]
**/
_f4u$t.PALEGREEN = [152,251,152];

// INTERACTION WITH THE UI

/**
Information about the current objects being
interacted with.  Holds subproperties id, moved
and value.

@property _I
@for _f4u$t
@type Object
@default {}
**/
_f4u$t._I = {};

/**
Id of the current value box interacted with.

@property _N
@for _f4u$t
@type String
@default ""
**/
_f4u$t._N = "";

/*
 * SERVER INTERACTION
 */

/**
Object that pairs paths of objects on the server
with DOM ids.

@property PATHS_TO_IDS
@for _f4u$t
@type Object
@default {}
**/
_f4u$t.PATHS_TO_IDS = {};

_f4u$t.path_to_id = function (path, id) {
  _f4u$t.PATHS_TO_IDS[path] = id;
}

/**
 Rather than using lots of global variables (clutters namespace)
 or using this.attribute (dangerous depending on browser and libraries),
 we use _f4u$t.IDS_TO_ATTRIBUTES to hold all information for faust UI objects.
 That way, the impact on the namespace of the global session as well
 as the objects is minimal.

@property IDS_TO_ATTRIBUTES
@for _f4u$t
@type Object
@default {}
**/
_f4u$t.IDS_TO_ATTRIBUTES = {};

/**
Returns a random, soft, pretty color, represented
as 0-255 RGB values in an array, to act as a background
for layout managers.

@method magic_color
@for _f4u$t
@static
@return {Array} An array of three values, 0-255 for RGB.
**/
_f4u$t.magic_color = function() {
  var r = Math.floor(Math.random() * 100) + 156;
  var g = Math.floor(Math.random() * 100) + 156;
  var b = 530 - r - g;
  var v = [r,g,b];
  v.sort(function() {return 0.5 - Math.random()}) // shuffles
  return v;
}

/**
Returns a random string.

@method rand_string
@for _f4u$t
@static
@param {Number} n (optional) the length of the string to return
@return {String} a random string
**/
_f4u$t.rand_string = function(n)
{
  var text = "";
  var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  if (!n) {
    n = 8;
  }

  for (var i = 0; i < n; i++ ) {
    text += possible.charAt(Math.floor(Math.random() * possible.length));
  }
  return text;
}

/**
Returns true if needle is the first part of haystack

@method first_part_matches
@for _f4u$t
@static
@param {String} haystack the string to search
@param {String} needle the search query
@return {Boolean} true if needle is the first part of the haystack
**/
_f4u$t.first_part_matches = function(haystack, needle) {
  return haystack.indexOf(needle) == 0;
}

/**
Removes needle from the head of haystack.

@method remove_from_head_of_string
@for _f4u$t
@static
@param {String} haystack the string to operate on
@param {String} needle remove
@return {String} the modified string without needle
**/
_f4u$t.remove_from_head_of_string = function(haystack, needle) {
  if (_f4u$t.first_part_matches(haystack, needle)) {
    return haystack.substr(needle.length);
  }
}

/**
The bounds for an accelerometer orientation.

@property orientation_bounds
@for _f4u$t
@type Object
@default {}
**/
_f4u$t.orientation_bounds = {
  alpha : [0, 360],
  beta : [-90, 90],
  gamma : [-90, 90]
};

/**
Parses a string into an orientation

@method parse_orientation
@for _f4u$t
@static
@return {Object}
**/
_f4u$t.parse_orientation = function(s) {
  var split = s.toString().split(" ");
  while (split.indexOf("") >= 0) {
    split.splce(split.indexOf(""), 1);
  }
  if (split.length == 0) {
    return {};
  }
  if (['alpha','beta','gamma'].indexOf(split[0]) < 0) {
    return {};
  }
  var itor = {1 : _f4u$t.orientation_bounds[split[0]][0], 2 : _f4u$t.orientation_bounds[split[0]][1] };

  // this loop creates the rest of the array
  for (var i in itor) {
    if (split.length == i) {
      split.push(itor[i]);
    }
    else {
      split[i] = parseFloat(split[i]);
      if (isNaN(split[i])) {
        split[i] = itor[i];
      }
    }
  }

  return {angle : split[0], low : split[1], high : split[2]};
}

/**
Taking an axis _f4u$t.X_AXIS or _f4u$t.Y_AXIS, returns
the opposite axis.

@method other_axis
@for _f4u$t
@static
@param {Number} axis An axis, either _f4u$t.X_AXIS or _f4u$t.Y_AXIS.
@return {Number} The opposite axis.
**/
_f4u$t.other_axis = function(axis) {
  return (axis + 1) % _f4u$t.NO_AXES;
}

/**
Remaps a value in a range to another range.

@method remap
@for _f4u$t
@static
@param {Number} v The value to remap.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum of the new range.
@param {Number} mx1 The maximum of the new range.
@return {Number} The value v remapped to the new range.
**/
_f4u$t.remap = function(v, mn0, mx0, mn1, mx1) {
  var p = 1.0 * (v - mn0) / (mx0 - mn0);
  return p * (mx1 - mn1) + mn1;
}

/**
Bounds a value between two numbers.

@method bound
@for _f4u$t
@static
@param {Number} v The value to bound.
@param {Number} m One side of the bound (either the min or max).
@param {Number} n The other side of the bound (either min or max).
@return {Number} Bounded value, meaning either unchanged or cropped at the min/max.
**/
_f4u$t.bound = function(v,m,n) {
  var mn = Math.min(m,n);
  var mx = Math.max(m,n);
  if (v < mn) { return mn; }
  if (v > mx) { return mx; }
  return v;
}

/**
Bounds a value between two numbers, avoiding large leaps
from a previous value

@method bound
@for _f4u$t
@static
@param {Number} aval The value to bound.
@param {Number} pval The previous value
@param {Number} l The lower bound
@param {Number} h The upper bound
@return {Number} The value bounded. If the previous value was the upper
bound, we remain on this to avoid large leaps.
**/
_f4u$t.bound_and_avoid_large_leaps = function(aval, pval, l, h, epsilon) {
  if (!epsilon) {
    epsilon = 0;
  }
  if (l > aval) {
    if (Math.abs(pval - h) <= epsilon) {
      return l;
    }
  }

  else if (aval > h) {
    if (Math.abs(pval - l) <= epsilon) {
      return h;
    }
  }

  // if neither of the above are true, free to move by the difference
  else {
    return aval;
  }

  // corner case - we avoid large leaps
  return pval;
}

/**
Quantizes a value between two numbers at a given step.

@method quantize
@for _f4u$t
@static
@param {Number} v The value to quantize.
@param {Number} m One side of the quantizing range (either the min or max).
@param {Number} n The other side of the quantizing range (either min or max).
@param {Number} s The step value to which the number must be quantized.
@return {Number} ov quantized (and bounded if necessary)
**/
_f4u$t.quantize = function(ov,m,n,s) {
  var v = _f4u$t.bound(ov, m, n);
  var mn = Math.min(m,n);
  var mx = Math.max(m,n);
  out = Math.floor((v - mn) / s + 0.5) * s + mn;
  return _f4u$t.bound(out, m, n);
}

/**
Flips a value at the center of a range.

@method flip
@for _f4u$t
@static
@param {Number} v The value to flip.
@param {Number} m One side of the range (either the min or max).
@param {Number} n The other side of the range (either min or max).
@return {Number} v flipped over the axis at the middle of the given range.
**/
_f4u$t.flip = function(v,m,n) {
  var mn = Math.min(m,n);
  var mx = Math.max(m,n);
  var offset = (mx - mn) / 2.0 + mn;
  return -1.0 * (v - offset) + offset;
}

/**
Remaps a value via _f4u$t.remap and then bounds it in the new
range via _f4u$t.bound.

@method remap_and_bound
@for _f4u$t
@static
@param {Number} v The value to remap and bound.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum and bound of the new range.
@param {Number} mx1 The maximum and bound of the new range.
@return {Number} The value v remapped and bounded to the new range.
**/
_f4u$t.remap_and_bound = function(v, mn0, mx0, mn1, mx1) {
  return _f4u$t.bound(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1);
}

/**
Remaps a value via _f4u$t.remap and then quantizes it in the new
range via _f4u$t.quantize.

@method remap_and_quantize
@for _f4u$t
@static
@param {Number} v The value to remap and quantize.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum and bound of the new range.
@param {Number} mx1 The maximum and bound of the new range.
@param {Number} s The step value to which the number must be quantized.
@return {Number} The value v remapped and quantizeed to the new range.
**/
_f4u$t.remap_and_quantize = function(v, mn0, mx0, mn1, mx1, s) {
  return _f4u$t.quantize(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1, s);
}

/**
Remaps a value via _f4u$t.remap and then bounds it in the new
range via _f4u$t.bound and then flips it via _f4u$t.flip.

@method remap_and_bound_and_flip
@for _f4u$t
@static
@param {Number} v The value to remap and bound and flip.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum and bound of the new range.
@param {Number} mx1 The maximum and bound of the new range.
@return {Number} The value v remapped and bounded and flipped to the new range.
**/
_f4u$t.remap_and_bound_and_flip = function(v, mn0, mx0, mn1, mx1) {
  return _f4u$t.flip(_f4u$t.bound(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1), mn1, mx1);
}

/**
Remaps a value via _f4u$t.remap and then quantizes it in the new
range via _f4u$t.quantize and then flips it via _f4u$t.flip.

@method remap_and_quantize_and_flip
@for _f4u$t
@static
@param {Number} v The value to remap and quantize and flip.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum and bound of the new range.
@param {Number} mx1 The maximum and bound of the new range.
@return {Number} The value v remapped and quantized and flipped to the new range.
**/
_f4u$t.remap_and_quantize_and_flip = function(v, mn0, mx0, mn1, mx1, s) {
  return _f4u$t.flip(_f4u$t.quantize(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1, s), mn1, mx1);
}

/**
Remaps a value via _f4u$t.remap and then flips it via _f4u$t.flip.

@method remap_and_flip
@for _f4u$t
@static
@param {Number} v The value to remap and flip.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum of the new range.
@param {Number} mx1 The maximum of the new range.
@return {Number} The value v remapped and flipped to the new range.
**/
_f4u$t.remap_and_flip = function(v, mn0, mx0, mn1, mx1) {
  return _f4u$t.flip(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1);
}

/**
Bounds a value via _f4u$t.bound and then flips it via _f4u$t.flip.

@method bound_and_flip
@for _f4u$t
@static
@param {Number} v The value to bound and flip.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum and bound of the new range.
@param {Number} mx1 The maximum and bound of the new range.
@return {Number} The value v bounded and and flipped to the new range.
**/
_f4u$t.bound_and_flip = function(v, mn1, mx1) {
  return _f4u$t.flip(_f4u$t.bound(v, mn1, mx1), mn1, mx1);
}

/**
Finds the sign of a number.

@method sign
@for _f4u$t
@static
@param {Number} x The number whose sign we want.
@return {Number} The sign, either -1, 1 or 0.
**/
_f4u$t.sign = function(x) {
  return (x == 0 ? x : Math.floor(Math.abs(x) / x));
}

/**
Chooses left, right, or center of range.

@method linear_combinatin
@for _f4u$t
@static
@param {Number} dir The direction indicating which number to use (left/right/center). Note that up is the same as left and down is the same as right.
@param {Number} v1 The first value of the range.
@param {Number} v2 The second value of the range.
@return {Number} The first value if left, the second value if right, or the center if center.
**/
_f4u$t.linear_combination = function(dir, v1, v2) {
  if (dir == _f4u$t.LEFT) {
    return v1;
  }
  if (dir == _f4u$t.RIGHT) {
    return v2;
  }
  return (v1 + v2) / 2.0;
}

/**
Chooses one of two values depending on the axis.

@method xy
@for _f4u$t
@static
@param {Number} a The axis, _f4u$t.X_AXIS or _f4u$t.Y_AXIS.
@param {Number} x The value to return if a is equal to _f4u$t.X_AXIS.
@param {Number} y The value to return if a is equal to _f4u$t.X_AXIS.
@return {Number} x or y, depending on what a is.
**/
_f4u$t.xy = function(a,x,y) {
  return (a == _f4u$t.X_AXIS ? x : y);
}

/**
Returns the trailing part of an id.  The faust naming convention gives
all DOM ids a unique identifier at the end, called the trailing part, and
this function returns it.

@method unique
@for _f4u$t
@static
@param {String} s An ID string
@return {String} The unique trailing part, if one exists.
**/
_f4u$t.unique = function(s) {
  var spl = s.toString().split("_");
  if (spl.length == 0) {
    return s;
  }
  return spl[spl.length - 1];
}

/**
Returns the type part of an id. The faust naming convention gives
all DOM ids a type as the second entry. Examples are vslider, hslider,
rbutton.

@method unique
@for _f4u$t
@static
@param {String} s An ID string
@return {String} The unique type, if one exists.
**/
_f4u$t.type = function(s) {
  var spl = s.toString().split("_");
  if (spl.length == 0) {
    console.log("incorrect naming of faust object");
    return s;
  }
  return spl[1];
}

/**
Takes an array of three values (R, G, and B) and returns a color
useable by CSS.

@method color_to_css
@for _f4u$t
@static
@param {Array, String} rgb An array with three values for
R, G, and B or a CSS string to bypass the conversion.
@return {String} An RGB value useable by CSS.
**/
_f4u$t.color_to_rgb = function(rgb) {
  if (typeof rgb == 'string')
    return rgb;
  return (rgb ? "rgb("+rgb[0]+","+rgb[1]+","+rgb[2]+")" : 'none');
}

/**
A function that generates a random 7-letter string.

@method randString
@for _f4u$t
@static
@return {String} A random 7-letter string.
**/
_f4u$t.randString = function() {
  var result = '';
  var length = 7;
  var chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (var i = length; i > 0; --i) {
    result += chars[Math.round(Math.random() * (chars.length - 1))];
  }
  return result;
}

/**
A function that returns either a given value or a default if
the given is null

@method initifnull
@for _f4u$t
@static
@param {any} v The value to use.
@param {any} d The default to return if v is null.
@return {any} Either v or d.
**/
_f4u$t.initifnull = function(v,d) {
  return (v == null ? d : v);
}

// TRIGONOMETRIC FUNCTIONS

/**
In a range, find all angles that fall at a multiple of 90 degrees.

@method find_all_90s
@for _f4u$t
@static
@param {Number} a0 The initial angle in degrees.
@param {Number} sweep The angle to sweep from the initial in degrees.
@return {Array} All multiples of 90 between a0 and a0 + sweep inclusive.
**/
_f4u$t.find_all_90s = function(a0, sweep) {
  var total = 0;
  var out = [];
  while (a0 > total) {
    total += 90;
  }
  while (total <= a0 + sweep) {
    out.push(total);
    total += 90;
  }
  return out;
}

/**
Given a polar coordiante, find the cartesian point

@method point_from_polar
@for _f4u$t
@static
@param {Number} r Radius.
@param {Number} a Angle in radians.
@return {Array} The cartesian coordinate as [x,y].
**/
_f4u$t.point_from_polar = function(r, a) {
  return [r * Math.cos(a), r * Math.sin(a)];
}

/**
Adds two coordinates in the form [x0,y0] and [x1,y1].

@method coord_sub
@for _f4u$t
@static
@param {Array} c0 First cartesian coordinate.
@param {Array} c1 Second cartesian coordinate.
@return {Array} The sum of the two coordinates.
**/
_f4u$t.coord_add = function(c0, c1) {
  return [c0[0] + c1[0], c0[1] + c1[1]];
}

/**
Subtracts two coordinates in the form [x0,y0] and [x1,y1].

@method coord_sub
@for _f4u$t
@static
@param {Array} c0 First cartesian coordinate.
@param {Array} c1 Second cartesian coordinate, subtracted from first.
@return {Array} The difference of the two coordinates.
**/
_f4u$t.coord_sub = function(c0, c1) {
  return [c0[0] - c1[0], c0[1] - c1[1]];
}

/**
Converts radians to degrees.

@method r2d
@for _f4u$t
@static
@param {Number} Angle in radians.
@return {Number} Angle in degrees.
**/
_f4u$t.r2d = function(a) {
  return a * 180 / Math.PI;
}

/**
Converts degrees to radians.

@method r2d
@for _f4u$t
@static
@param {Number} Angle in degrees.
@return {Number} Angle in radians.
**/
_f4u$t.d2r = function(a) {
  return a * Math.PI / 180.;
}

/**
Ajax queue.

@property ajax_queue
@for _f4u$t
@type Object
@default {}
**/
_f4u$t.ajax_queue = {};

/**
Is the ajax queue busy?

@property ajax_queue_busy
@for _f4u$t
@type Boolean
@default false
**/
_f4u$t.ajax_queue_busy = false;

/**
Active addresses being sent to server.

@property active_addresses
@for _f4u$t
@type Array
@default []
**/
_f4u$t.active_addresses = [];

/**
A box class.

@class Box
@namespace _f4u$t
@constructor
**/

_f4u$t.Box = function() {
  /**
  Resets the x and y of a box to their defaults
  
  @method clear
  @for _f4u$t.Box
  **/
  this.clear = function() {
    /**
    x range of a Box.
    
    @property x
    @for _f4u$t.Box
    @type Array
    @default [Number.POSITIVE_INFINITY, Number.NEGATIVE_INFINITY]
    **/
    this.x = [Number.POSITIVE_INFINITY, Number.NEGATIVE_INFINITY];
    /**
    y range of a Box.
    
    @property y
    @for _f4u$t.Box
    @type Array
    @default [Number.POSITIVE_INFINITY, Number.NEGATIVE_INFINITY]
    **/
    this.y = [Number.POSITIVE_INFINITY, Number.NEGATIVE_INFINITY];
  }
  this.clear();
}

/**
Adds an array of points, with each point in the form [x,y], to the
interior of the box.

@method add_points
@for _f4u$t.Box
@param {Array} pts An array of points.
**/
_f4u$t.Box.prototype.add_points = function(pts) {
  for (var i = 0; i < pts.length; i++) {
    this.add_point(pts[i]);
  }
}

/**
Adds a point in the form [x,y] to the
interior of the box.

@method add_points
@for _f4u$t.Box
@param {Array} pt A point to add.
**/
_f4u$t.Box.prototype.add_point = function(pt) {
  this.x = [Math.min(this.x[0], pt[0]), Math.max(this.x[1], pt[0])];
  this.y = [Math.min(this.y[0], pt[1]), Math.max(this.y[1], pt[1])];
}

/**
Returns the length of the box along the x and y axes.

@method lens
@for _f4u$t.Box
@return {Array} The length of the box along the x and y axes.
**/
_f4u$t.Box.prototype.lens = function(pt) {
  return [this.x[1] - this.x[0], this.y[1] - this.y[0]];
}

/**
Returns the corner points (minima and maxima) of the Box.

@method corners
@for _f4u$t.Box
@return {Array} The corner points of the box.
**/
_f4u$t.Box.prototype.corners = function(pt) {
  return [[this.x[0], this.y[0]], [this.x[1], this.y[1]]];
}

/**
Finds the bounding box of a text node in an svg.

@method get_text_bbox
@for _f4u$t
@param {Object} svg The svg node.
@param {Object} text The text node.
@return {Object} The bounding rectangle of the text node.
**/
_f4u$t.get_text_bbox = function(svg, text, kls) {
  if (!kls) {
    kls = 'faust-label';
  }
  var dummy = _f4u$t.make_text(svg,null,0,0,text, {'class' : kls});
  var bbox = dummy.getBBox();
  _f4u$t.svg_remove(svg, dummy);
  return bbox;
}

_f4u$t.make_rectangle_via_path = function(svg, parent, rf, x, y, w, h, ops) {
  var d = "M{0} {7}L{1} {7}C{2} {7} {2} {7} {2} {3}L{2} {4}C{2} {5} {2} {5} {1} {5}L{0} {5}C{6} {5} {6} {5} {6} {4}L{6} {3}C{6} {7} {6} {7} {0} {7}";
  d = d.format([rf + x, w - rf + x, w + x, rf + y, h - rf + y, h + y, x, y]);
  var rect = _f4u$t.make_path(
    parent,
    d,
    ops
  );

  return rect;
}

/**
Makes the UI for the faust application.

@method make_ui
@for _f4u$t
@param {Object} svg The root SVG node.
@param {Object} raw_json The raw JSON describing the UI to build.
**/
_f4u$t.make_ui = function(svg, raw_json, width, height, hash) {
  var json = eval ("(" + raw_json + ")");
  var faust_svg = new _f4u$t.SVG(
    svg,
    width,
    height,
    {
      constrain : false,
      title : json["ui"][0].label,
      lm : _f4u$t.json_to_ui(json, hash)
    }
  );

  faust_svg.defs();
  faust_svg.lm.mom = faust_svg;
  faust_svg.make();
}

_f4u$t.assign_parameters_to_values = function(URLParams) {
  for (var index in URLParams) {
    var split_index = index.toString().split('.');
    if (split_index.length != 2) {
      continue;
    }
    if (_f4u$t[split_index[0]]) {
      if (_f4u$t[split_index[0]][split_index[1]]) {
        _f4u$t[split_index[0]][split_index[1]] = eval(URLParams[index][URLParams[index].length - 1]);
      }
    }
  }
}

/**
The main function called to build the faust UI.
Parses the URL to include any new documents and then builds the UI.

@method main
@for _f4u$t
@param {Object} raw_json A raw JSON object describing the UI to build.
@param {Object} div (optional) The div to place the object in.
**/
_f4u$t.main = function(raw_json, div, callback) {
    
    if (!div) {
        div = $( "<div />" );
        $("body").append(div);
    }
    // we create a hash for the object
    var hash = $(div).attr('id') ? $(div).attr('id') :  _f4u$t.rand_string(8);
    
    // keep it in the div
    $(div).attr('id', hash);  
    
    // first, we parse URL parameters to change UIs' style if necessary
    var URLParams = _f4u$t.parseURLParams(document.URL);
    // then we assign parameters
    _f4u$t.assign_parameters_to_values(URLParams);
    // we make sure all JS and CSS is loaded before we build the UI
    _f4u$t.load_css_and_then_js(URLParams.css, URLParams.js);
    
    var width = $(div).width();
    if (width == 0) {
        // HUOM: this "- 15" is a kludge and should dealt with more elegantly
        width = $(window).width() - 15;
    }
    var height = $(div).height();
    if (height == 0) {
        // HUOM: this "- 17" is a kludge and should dealt with more elegantly
        height = $(window).height() - 17;
    }
    if (callback) {
        _f4u$t.HANDLER_CALLBACKS.push(function(address, value) {
                                      if (_f4u$t.first_part_matches(address, hash)) {
                                      return callback(_f4u$t.remove_from_head_of_string(address, hash), value);
                                      }
                                      });
    }

    _f4u$t.add_svg_and_onload_to_div(div, raw_json, width, height, hash);

    return function(address, value) {
        return _f4u$t.update_value_at_address(hash+address, value);
    }
}

/**
  Deletes all references to this div in internal data structures, including
  all bindings.  Note that this does NOT delete the div from the page, nor
  does it delete the div's contents.  This is in case the div contains
  other information that the person wants to complete.
  
  To delete the UI in the div, call _f4u$t.hard_delete()
**/
_f4u$t.delete = function(div) {
  var id = $(div).attr('id');
  if (!id) {
    console.log("Can't delete because obj does not exist in the system.");
    return;
  }
  var ids_to_delete = [];
  var keys_to_delete = []
  for (var key in _f4u$t.PATHS_TO_IDS) {
    if (_f4u$t.first_part_matches(key, id)) {
      ids_to_delete.push(_f4u$t.PATHS_TO_IDS[key]);
      keys_to_delete.push(key);
    }
  }
  for (var key_to_delete in keys_to_delete) {
    delete _f4u$t.PATHS_TO_IDS[key_to_delete];
  }
  for (var id_to_delete in ids_to_delete) {
    var slim = _f4u$t.unique(id_to_delete);
    delete _f4u$t.IDS_TO_ATTRIBUTES[slim];
  }
}

_f4u$t.hard_delete = function(div) {
  _f4u$t.delete(div);
  $(div).empty();
}

/**
  To be called when used with the C++/LLVM libfaust based FaustNode.
**/
_f4u$t.make_audio_ui = function(dsp, svg) {
  var json = eval("(" + dsp.json() + ")");
  var faust_svg = new _f4u$t.SVG(
    svg,
    // kludge to prevent scroll bars...
    $(window).width() - 15,
    // kludge to prevent scroll bars...
    $(window).height() - 17,
    {
      constrain : false,
      title : json["ui"][0].label,
      lm : _f4u$t.json_to_ui(json)
    }
  );
  
  // Keep audio params in a table 
  _f4u$t.controls = new Array();
  for (var i = 0; i < dsp.numberOfAudioParams(); i++) {
    var ctrl = dsp.getAudioParam(i);
    _f4u$t.controls[ctrl.name] = ctrl;
  }
  
  _f4u$t.fausthandler = function(dest, value) {
    _f4u$t.controls[dest].value = value; 
  }
    
  _f4u$t.main_loop = function() {}

  faust_svg.defs();
  faust_svg.lm.mom = faust_svg;
  faust_svg.make();
}


// we want to stay in the faust namespace, so...
var _f4u$t = {};

_f4u$t.TEXT_HEIGHT = 20;
_f4u$t.TEXT_PADDING = 10;
_f4u$t.VALUE_BOX_W = 60;
_f4u$t.VALUE_BOX_H = _f4u$t.TEXT_HEIGHT;
_f4u$t.TEXT_BOX_PADDING = 3;

// some convenience methods for inheritence

_f4u$t.surrogateCtor = function() {}

_f4u$t.extend = function(base, sub) {
  // Copy the prototype from the base to setup inheritance
  _f4u$t.surrogateCtor.prototype = base.prototype;
  sub.prototype = new _f4u$t.surrogateCtor();
  // Remember the constructor property was set wrong, let's fix it
  sub.prototype.constructor = sub;
}

_f4u$t.X_AXIS = 0;
_f4u$t.Y_AXIS = 1;
_f4u$t.NO_AXES = 2;

_f4u$t.LEFT = -1;
_f4u$t.RIGHT = 1;
_f4u$t.UP = -1;
_f4u$t.DOWN = 1;
_f4u$t.CENTER = 0;

_f4u$t.BLACK = [0,0,0];
_f4u$t.CYAN = [0,255,255];
_f4u$t.GREY = [100,100,100];
_f4u$t.PINK = [233,150,122];
_f4u$t.GREEN = [173,255,47];
_f4u$t.KERMIT = [47,243,160];
_f4u$t.PALEGREEN = [152,251,152];

_f4u$t.magic_color = function() {
  var r = Math.floor(Math.random() * 100) + 156;
  var g = Math.floor(Math.random() * 100) + 156;
  var b = 530 - r - g;
  var v = [r,g,b];
  v.sort(function() {return 0.5 - Math.random()}) // shuffles
  return v;
}

_f4u$t.other_axis = function(axis) {
  return (axis + 1) % _f4u$t.NO_AXES;
}

_f4u$t.remap = function(v, mn0, mx0, mn1, mx1) {
  var p = 1.0 * (v - mn0) / (mx0 - mn0);
  return p * (mx1 - mn1) + mn1;
}

_f4u$t.bound = function(v,m,n) {
  var mn = Math.min(m,n);
  var mx = Math.max(m,n);
  if (v < mn) { return mn; }
  if (v > mx) { return mx; }
  return v;
}

_f4u$t.flip = function(v,m,n) {
  var mn = Math.min(m,n);
  var mx = Math.max(m,n);
  var offset = (mx - mn) / 2.0 + mn;
  return -1.0 * (v - offset) + offset;
}

_f4u$t.remap_and_bound = function(v, mn0, mx0, mn1, mx1) {
  return _f4u$t.bound(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1);
}

_f4u$t.remap_and_bound_and_flip = function(v, mn0, mx0, mn1, mx1) {
  return _f4u$t.flip(_f4u$t.bound(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1), mn1, mx1);
}

_f4u$t.remap_and_flip = function(v, mn0, mx0, mn1, mx1) {
  return _f4u$t.flip(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1);
}

_f4u$t.bound_and_flip = function(v, mn1, mx1) {
  return _f4u$t.flip(_f4u$t.bound(v, mn1, mx1), mn1, mx1);
}

_f4u$t.sign = function(x) {
  return (x == 0 ? x : Math.floor(Math.abs(x) / x));
}

_f4u$t.linear_combination = function(dir, v1, v2) {
  if (dir == _f4u$t.LEFT) {
    return v1;
  }
  if (dir == _f4u$t.RIGHT) {
    return v2;
  }
  return (v1 + v2) / 2.0;
}

_f4u$t.xy = function(a,x,y) {
  return (a == _f4u$t.X_AXIS ? x : y);
}

_f4u$t.unique = function(s) {
  var spl = s.split("_");
  if (spl.length == 0) {
    return s;
  }
  return spl[spl.length - 1];
}

_f4u$t.color_to_rgb = function(rgb) {
  return (rgb ? "rgb("+rgb[0]+","+rgb[1]+","+rgb[2]+")" : 'none');
}

_f4u$t.randString = function() {
  var result = '';
  var length = 7;
  var chars = "'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (var i = length; i > 0; --i) {
    result += chars[Math.round(Math.random() * (chars.length - 1))];
  }
  return result;
}

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

// takes radians!!
_f4u$t.point_from_polar = function(r, a) {
  return [r * Math.cos(a), r * Math.sin(a)];
}

_f4u$t.coord_add = function(c0, c1) {
  return [c0[0] + c1[0], c0[1] + c1[1]];
}

_f4u$t.coord_sub = function(c0, c1) {
  return [c0[0] - c1[0], c0[1] - c1[1]];
}

_f4u$t.r2d = function(a) {
  return a * 180 / Math.PI;
}

_f4u$t.d2r = function(a) {
  return a * Math.PI / 180.;
}

// a Box class

_f4u$t.Box = function() {
  this.clear = function() {
    this.x = [Number.POSITIVE_INFINITY, Number.NEGATIVE_INFINITY];
    this.y = [Number.POSITIVE_INFINITY, Number.NEGATIVE_INFINITY];
  }
  this.clear();
}

_f4u$t.Box.prototype.add_points = function(pts) {
  for (var i = 0; i < pts.length; i++) {
    this.add_point(pts[i]);
  }
}

_f4u$t.Box.prototype.add_point = function(pt) {
  this.x = [Math.min(this.x[0], pt[0]), Math.max(this.x[1], pt[0])];
  this.y = [Math.min(this.y[0], pt[1]), Math.max(this.y[1], pt[1])];
}

_f4u$t.Box.prototype.lens = function(pt) {
  return [this.x[1] - this.x[0], this.y[1] - this.y[0]];
}

_f4u$t.Box.prototype.corners = function(pt) {
  return [[this.x[0], this.y[0]], [this.x[1], this.y[1]]];
}


// a python-like string formatter

String.prototype.format = function (args) {
  var str = this;
  return str.replace(String.prototype.format.regex, function(item) {
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

String.prototype.format.regex = new RegExp("{-?[0-9]+}", "g");

// array min and max
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

Array.prototype.sum = function() {
  var sum = 0;
  for(var i = 0; i < this.length; i++) {
    sum += this[i];
  }
  return sum;
}

_f4u$t.get_text_bbox = function(svg, text) {
  var dummy = svg.text(0,0,text);
  var bbox = dummy.getBBox();
  svg.remove(dummy);
  return bbox;
}

// main
_f4u$t.make_ui = function(svg, raw_json) {
  var json = eval ("(" + raw_json + ")");
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

  faust_svg.lm.mom = faust_svg;
  faust_svg.make();
}

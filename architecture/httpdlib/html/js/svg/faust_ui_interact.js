/*
 * look for the phrase
 * UI2DSP to see where the UI sends messages to DSP
 * obviously, the goal is to separate the two as much as possible
 */

_f4u$t.NETHERWORLD = -100000;

_f4u$t._I = 0; // id
_f4u$t._N = 0; // id of the key sink

/*
 * SERVER INTERACTION
 */

_f4u$t.PATHS_TO_IDS = {};

/*
 * OBJECT ORIENTED PROGRAMMING
 * Rather than using lots of global variables (clutters namespace)
 * or using this.attribute (dangerous depending on browser and libraries),
 * we use _f4u$t.IDS_TO_ATTRIBUTES to hold all information for faust UI objects.
 * That way, the impact on the namespace of the global session as well
 * as the objects is minimal.
 */

_f4u$t.IDS_TO_ATTRIBUTES = {};

_f4u$t.PREV = new Array();
_f4u$t.PREV[_f4u$t.X_AXIS] = _f4u$t.NETHERWORLD;
_f4u$t.PREV[_f4u$t.Y_AXIS] = _f4u$t.NETHERWORLD;

_f4u$t.getClientX = function(e) {
  return e.clientX / _f4u$t.VIEWPORT_SCALE;
}

_f4u$t.getClientY = function(e) {
  return e.clientY / _f4u$t.VIEWPORT_SCALE;
}

// parser of an object's transform

_f4u$t.transformToArray = function(transform) {
  var out = [];
  var flre = "[-+]?[0-9]*\\.?[0-9]*(?:[eE][-+]?[0-9]+)?";
  var matrix = new RegExp("^\\s*matrix\\s*\\(\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*\\)");
  var translate = new RegExp("^\\s*translate\\s*\\(\\s*("+flre+")\\s*(?:[,]\\s*("+flre+")\\s*)?\\)");
  var scale = new RegExp("^\\s*scale\\s*\\(\\s*("+flre+")\\s*(?:[,]\\s*("+flre+")\\s*)?\\)");
  var rotate = new RegExp("^\\s*rotate\\s*\\(\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*\\)");
  var skewX = new RegExp("^\\s*skewX\\s*\\(\\s*("+flre+")\\s*\\)");
  var skewY = new RegExp("^\\s*skewY\\s*\\(\\s*("+flre+")\\s*\\)");
  while(true) {
    var match = matrix.exec(transform);
    if (match != null) {
      out.push(["matrix",parseFloat(match[1]), parseFloat(match[2]), parseFloat(match[3]), parseFloat(match[4]), parseFloat(match[5]), parseFloat(match[6])]);
      transform = transform.substr(match[0].length,transform.length-match[0].length);
      continue;
    }
    match = translate.exec(transform);
    if (match != null) {
      var second = 0.0;
      if (match[2] != undefined) { second = parseFloat(match[2]); }
      out.push(["translate",parseFloat(match[1]),second]);
      transform = transform.substr(match[0].length,transform.length-match[0].length);
      continue;
    }
    match = scale.exec(transform);
    if (match != null) {
      var second = 0.0;
      if (match[2] != undefined) { second = parseFloat(match[2]); }
      out.push(["scale",parseFloat(match[1]), second]);
      transform = transform.substr(match[0].length,transform.length-match[0].length);
      continue;
    }
    match = rotate.exec(transform);
    if (match != null) {
      var second = 0.0;
      if (match[2] != undefined) { second = parseFloat(match[2]); }
      var third = 0.0;
      if (match[2] != undefined) { third = parseFloat(match[2]); }
      out.push(["rotate",parseFloat(match[1]), second, third]);
      transform = transform.substr(match[0].length,transform.length-match[0].length);
      continue;
    }
    match = skewX.exec(transform);
    if (match != null) {
      out.push(["skewX", parseFloat(match[1])]);
      transform = transform.substr(match[0].length,transform.length-match[0].length);
      continue;
    }
    match = skewY.exec(transform);
    if (match != null) {
      out.push(["skewY", parseFloat(match[1])]);
      transform = transform.substr(match[0].length,transform.length-match[0].length);
      continue;
    }
    break;
  }
  return out;
}

// takes an array, turns it to a transform

_f4u$t.arrayToTransform = function(array) {
  var out = "";
  while (array.length > 0)
  {
    out = out.concat(array[0][0]);
    out = out.concat("(");
    var i=1;
    var arlen = array[0].length;
    while(arlen > i) {
      out = out.concat(array[0][i]+",");
      i++;
    }
    out = out.substr(0,out.length-1);
    out = out.concat(") ");
    array.shift();
  }
  if (out.length > 0) { out = out.substr(0,out.length-1); }
  return out;
}

_f4u$t.updateXY = function(e) {
  _f4u$t.PREV[_f4u$t.X_AXIS] = _f4u$t.getClientX(e);
  _f4u$t.PREV[_f4u$t.Y_AXIS] = _f4u$t.getClientY(e);
}

// main function to move currently-selected slider
_f4u$t.moveActiveObject = function(e) {
  if (_f4u$t._I == 0) {
    _f4u$t.updateXY(e);
    _f4u$t.BUSY = false;
    return true;
  }

  _f4u$t.clog_key_sink();
  _f4u$t.BUSY = true;

  var hslider_token = "faust_hslider_knob";
  var vslider_token = "faust_vslider_knob";
  var rotating_button_token = "faust_rbutton_knob"
  var now = null;
  if (_f4u$t._I.substring(0, hslider_token.length) == hslider_token) {
    now = _f4u$t.moveActiveSlider(e);
  }
  else if (_f4u$t._I.substring(0, vslider_token.length) == vslider_token) {
    now = _f4u$t.moveActiveSlider(e);
  }
  else if (_f4u$t._I.substring(0, rotating_button_token.length) == rotating_button_token) {
    now = _f4u$t.moveActiveRotatingButton(e);
  }

  // UI2DSP
  if (now != null) {
    var id = _f4u$t.unique(_f4u$t._I);
    _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["AD"], now);
  }

  // soemthing like a numerical entry...so just return 0
  return 0;
}

_f4u$t.genericMovingPartUpdate = function(aval, pval, l, h) {
  if (l > aval) {
    if (pval != h) {
      return l;
    }
  }

  else if (aval > h) {
    if (pval != l) {
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

_f4u$t.moveActiveSlider = function(e)
{
  var sliding_part = document.getElementById(_f4u$t._I);
  var id = _f4u$t.unique(_f4u$t._I);
  var A = _f4u$t.IDS_TO_ATTRIBUTES[id]["A"];
  var P = _f4u$t.IDS_TO_ATTRIBUTES[id]["P"];
  var T = _f4u$t.IDS_TO_ATTRIBUTES[id]["T"];
  var pos = -1;
  // we only care about the axis of the slider
  if (A == _f4u$t.X_AXIS) {
    pos = _f4u$t.getClientX(e);
  }
  else {
    pos = _f4u$t.getClientY(e);
  }

  var diff = pos - _f4u$t.PREV[A];
  var transform = _f4u$t.transformToArray(sliding_part.getAttribute("transform"));
  // we assume that there is only one element and that it is a transform
  // make sure to change this if things get more complicated
  // actually, just make sure not to make things more complicated...

  var aval = transform[0][A + 1] + diff;

  // minimum of the slider is to the bottom / left
  transform[0][A + 1] = _f4u$t.genericMovingPartUpdate(aval, transform[0][A + 1], 0, T - (T * P));
  var now = _f4u$t[_f4u$t.xy(A, "generic_label_update", "generic_flipped_label_update")](id, aval, 0, T - (T * P));
  var movetothis = _f4u$t.arrayToTransform(transform);
  sliding_part.setAttribute("transform", movetothis);
  _f4u$t.updateXY(e);
  return now;
}

_f4u$t.moveActiveRotatingButton = function(e)
{
  var sliding_part = document.getElementById(_f4u$t._I);
  var anchor = document.getElementById('faust_rbutton_anchor_'+_f4u$t.unique(_f4u$t._I));
  var id = _f4u$t.unique(_f4u$t._I);
  var A0 = _f4u$t.IDS_TO_ATTRIBUTES[id]["A0"];
  var SW = _f4u$t.IDS_TO_ATTRIBUTES[id]["SW"];
  var P = _f4u$t.IDS_TO_ATTRIBUTES[id]["P"];
  //var os = $(sliding_part).offset();
  var os = $(anchor).offset();
  var my_y = os['top'] / _f4u$t.VIEWPORT_SCALE;
  var my_x = os['left'] / _f4u$t.VIEWPORT_SCALE;

  var diff = 180. * (Math.atan2(_f4u$t.getClientY(e) - my_y, _f4u$t.getClientX(e) - my_x) - Math.atan2(_f4u$t.PREV[_f4u$t.Y_AXIS] - my_y, _f4u$t.PREV[_f4u$t.X_AXIS] - my_x)) / Math.PI;
  // if diff is to great, the browser is going berzerk...
  if (-180 > diff) {
    diff += 360;
  }
  else if (diff > 180) {
    diff -= 360;
  }

  var transform = _f4u$t.transformToArray(sliding_part.getAttribute("transform"));
  // we assume that there is only one element and that it is a transform
  // make sure to change this if things get more complicated
  // actually, just make sure not to make things more complicated...

  var aval = transform[2][1] + diff;

  transform[2][1] = _f4u$t.genericMovingPartUpdate(aval, transform[2][1], A0, A0 + SW - (SW * P));
  var now = _f4u$t.generic_label_update(_f4u$t.unique(_f4u$t._I), aval, A0, A0 + SW - (SW * P));
  var movetothis = _f4u$t.arrayToTransform(transform);
  sliding_part.setAttribute("transform", movetothis);
  _f4u$t.updateXY(e);
  return now;
}

_f4u$t.generic_label_update = function(id, c, l, h) {
  var now = _f4u$t.remap_and_bound(c, l, h, _f4u$t.IDS_TO_ATTRIBUTES[id]["MN"], _f4u$t.IDS_TO_ATTRIBUTES[id]["MX"]);
  return _f4u$t.dumb_label_update(id, now);
}

_f4u$t.generic_flipped_label_update = function(id, c, l, h) {
  var now = _f4u$t.remap_and_bound_and_flip(c, l, h, _f4u$t.IDS_TO_ATTRIBUTES[id]["MN"], _f4u$t.IDS_TO_ATTRIBUTES[id]["MX"]);
  return _f4u$t.dumb_label_update(id, now);
}

_f4u$t.dumb_label_update = function(id, c) {
  var label = document.getElementById("faust_value_value_"+id);
  label.textContent = c.toFixed(3);
  _f4u$t.IDS_TO_ATTRIBUTES[id]["B"] = c;
  return c;
}

// gets rid of the current thing being dragged
_f4u$t.clearIdCache = function() {
  // we only clear the id and let other variables hold cruft
  // that means that if someone forgets to set a setter, it will
  // point to its old value
  _f4u$t._I = 0;
  _f4u$t.BUSY = false;
}

_f4u$t.initiate_slider = function(A, I, T, P, MN, MX, S, L, AD) {
  // in case we haven't initialized things yet
  /*
  if (_f4u$t.PREV[_f4u$t.X_AXIS] == _f4u$t.NETHERWORLD) {
    _f4u$t.updateXY(e);
  }
  */
  var id = _f4u$t.unique(I);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = (A == _f4u$t.X_AXIS ? "hslider" : "vslider");
  _f4u$t.IDS_TO_ATTRIBUTES[id]["A"] = A;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["T"] = T;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["P"] = P;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["MN"] = MN;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["MX"] = MX;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["S"] = S;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["L"] = L;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["AD"] = AD;
  _f4u$t.path_to_id(AD, I);
}

_f4u$t.initiate_nentry = function(I, MN, MX, S, D, L, AD) {
  // in case we haven't initialized things yet
  /*
  if (_f4u$t.PREV[_f4u$t.X_AXIS] == _f4u$t.NETHERWORLD) {
    _f4u$t.updateXY(e);
  }
  */
  var id = _f4u$t.unique(I);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "nentry";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["MN"] = MN;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["MX"] = MX;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["S"] = S;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["B"] = D;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["L"] = L;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["AD"] = AD;
  _f4u$t.path_to_id(AD, I);
}

_f4u$t.initiate_hslider = function(I, T, P, MN, MX, S, L, AD) {
  _f4u$t.initiate_slider(_f4u$t.X_AXIS, I, T, P, MN, MX, S, L, AD);
}

_f4u$t.initiate_vslider = function(I, T, P, MN, MX, S, L, AD) {
  _f4u$t.initiate_slider(_f4u$t.Y_AXIS, I, T, P,MN, MX, S, L, AD);
}

_f4u$t.initiate_bargraph = function(A, I, WA, SA, MN, MX, S, L, AD) {
  // in case we haven't initialized things yet
  /*
  if (_f4u$t.PREV[_f4u$t.X_AXIS] == _f4u$t.NETHERWORLD) {
    _f4u$t.updateXY(e);
  }
  */
  var id = _f4u$t.unique(I);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = (A == _f4u$t.X_AXIS ? "hbargraph" : "vbargraph");
  _f4u$t.IDS_TO_ATTRIBUTES[id]["A"] = A;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["WA"] = WA;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["SA"] = SA;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["MN"] = MN;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["MX"] = MX;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["S"] = S;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["L"] = L;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["AD"] = AD;
  _f4u$t.path_to_id(AD, I);
}

_f4u$t.initiate_hbargraph = function(I, WA, SA, MN, MX, S, L, AD) {
  _f4u$t.initiate_bargraph(_f4u$t.X_AXIS, I, WA, SA, MN, MX, S, L, AD);
}

_f4u$t.initiate_vbargraph = function(I, WA, SA, MN, MX, S, L, AD) {
  _f4u$t.initiate_bargraph(_f4u$t.Y_AXIS, I, WA, SA, MN, MX, S, L, AD);
}

_f4u$t.activate_slider = function(I) {
  // in case we haven't initialized things yet
  /*
  if (_f4u$t.PREV[_f4u$t.X_AXIS] == _f4u$t.NETHERWORLD) {
    _f4u$t.updateXY(e);
  }
  */
  _f4u$t._I = I;

}

_f4u$t.activate_nentry = function(I,dir) {
  // in case we haven't initialized things yet
  /*
  if (_f4u$t.PREV[_f4u$t.X_AXIS] == _f4u$t.NETHERWORLD) {
    _f4u$t.updateXY(e);
  }
  */

  _f4u$t._I = I;
  var id = _f4u$t.unique(_f4u$t._I);

  var now = parseFloat(_f4u$t.IDS_TO_ATTRIBUTES[id]["B"]);
  if (dir == 1) {
    now += _f4u$t.IDS_TO_ATTRIBUTES[id]["S"];
  }
  else {
    now -= _f4u$t.IDS_TO_ATTRIBUTES[id]["S"];
  }

  now = _f4u$t.bound(now, _f4u$t.IDS_TO_ATTRIBUTES[id]["MN"], _f4u$t.IDS_TO_ATTRIBUTES[id]["MX"]);
  now = _f4u$t.dumb_label_update(_f4u$t.unique(_f4u$t._I), now);
  return now;
}

_f4u$t.activate_hslider = function(I) {
  _f4u$t.activate_slider(I);
}

_f4u$t.activate_vslider = function(I) {
  _f4u$t.activate_slider(I);
}

_f4u$t.initiate_rbutton = function(I,A0,SW,P,MN,MX,S,L,AD) {
  /*
  if (_f4u$t.PREV[_f4u$t.X_AXIS] == _f4u$t.NETHERWORLD) {
    _f4u$t.updateXY(e);
  }
  */
  var id = _f4u$t.unique(I);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "rbutton";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["A0"] = A0;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["SW"] = SW;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["P"] = P;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["L"] = L;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["MN"] = MN;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["MX"] = MX;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["S"] = S;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["AD"] = AD;
  _f4u$t.path_to_id(AD, I);
}

_f4u$t.activate_rbutton = function(I) {
  _f4u$t._I = I;
}

// BROKEN...
_f4u$t.button_class_changer = function(I, down) {
  if (down) {
    $('#faust_button_box_'+_f4u$t.unique(I)).removeClass('faust-button-up').addClass('faust-button-down');
  }
  else {
    $('#faust_button_box_'+_f4u$t.unique(I)).removeClass('faust-button-down').addClass('faust-button-up');
  }
}

_f4u$t.button_up = function(I) {
  var id = _f4u$t.unique(I);
  _f4u$t.button_class_changer(I, false);
  _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["AD"], 0);
  _f4u$t.clearIdCache();
}

_f4u$t.button_down = function(I) {
  var id = _f4u$t.unique(I);
  _f4u$t.clog_key_sink();
  _f4u$t.button_class_changer(I, true);
  // UI2DSP
  _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["AD"], 1);
}

_f4u$t.initiate_button = function(I, UF, DF, AD) {
  var id = _f4u$t.unique(I);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "button";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["UF"] = UF;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["DF"] = DF;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["AD"] = AD;
  _f4u$t.path_to_id(AD, I);
}

_f4u$t.change_checkbox = function(I) {
  _f4u$t.clog_key_sink();
  var AD = _f4u$t.IDS_TO_ATTRIBUTES[_f4u$t.unique(I)]["AD"];
  var box = document.getElementById('faust_checkbox_check_'+_f4u$t.unique(I));
  var opacity = 0;
  if (box.style.opacity == 1.0) {
    opacity = 0;
  }
  else if (box.style.opacity == 0.0) {
    opacity = 1;
  }
  else {
    alert("malfunctional checkbox");
  }
  box.style.opacity = opacity;
  // UI2DSP
  _f4u$t.fausthandler(AD, opacity);
}

_f4u$t.initiate_checkbox = function(I, AD) {
  var id = _f4u$t.unique(I);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "checkbox";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["AD"] = AD;
  _f4u$t.path_to_id(AD, I);
}

_f4u$t.clog_key_sink = function() {
  if (_f4u$t._N != 0) {
    var box = document.getElementById("faust_value_box_"+_f4u$t.unique(_f4u$t._N));
    box.style.stroke = "black";
  }
  _f4u$t._N = 0;
}

// if a numerical entry is linked to an incremental object,
// actualize it

_f4u$t.actualize_incremental_object = function(id) {
  var hslider_id = "faust_hslider_knob_"+id;
  var vslider_id = "faust_vslider_knob_"+id;
  var rotating_button_id = "faust_rbutton_knob_"+id;
  var hbargraph_id = "faust_hbargraph_meter_"+id;
  var vbargraph_id = "faust_vbargraph_meter_"+id;
  var val = parseFloat(_f4u$t.IDS_TO_ATTRIBUTES[id]["B"]);
  var maybe_slider = document.getElementById(hslider_id);
  if (maybe_slider == null) {
    maybe_slider = document.getElementById(vslider_id);
  }
  var maybe_button = document.getElementById(rotating_button_id);
  var maybe_bargraph = document.getElementById(hbargraph_id);
  if (maybe_bargraph == null) {
    maybe_bargraph = document.getElementById(vbargraph_id);
  }
  if (maybe_slider != null) {
    // ugh...code dups
    var MN = _f4u$t.IDS_TO_ATTRIBUTES[id]["MN"];
    var MX = _f4u$t.IDS_TO_ATTRIBUTES[id]["MX"];
    var T = _f4u$t.IDS_TO_ATTRIBUTES[id]["T"];
    var P = _f4u$t.IDS_TO_ATTRIBUTES[id]["P"];
    var A = _f4u$t.IDS_TO_ATTRIBUTES[id]["A"];
    val = _f4u$t[_f4u$t.xy(A, "remap", "remap_and_flip")](val, MN, MX, 0, T - (T * P));
    var transform = _f4u$t.transformToArray(maybe_slider.getAttribute("transform"));
    transform[0][A + 1] = val;
    var movetothis = _f4u$t.arrayToTransform(transform);
    maybe_slider.setAttribute("transform", movetothis);
    return 0;
  }
  else if (maybe_button != null) {
    var MN = _f4u$t.IDS_TO_ATTRIBUTES[id]["MN"];
    var MX = _f4u$t.IDS_TO_ATTRIBUTES[id]["MX"];
    var A0 = _f4u$t.IDS_TO_ATTRIBUTES[id]["A0"];
    var P = _f4u$t.IDS_TO_ATTRIBUTES[id]["P"];
    var SW = _f4u$t.IDS_TO_ATTRIBUTES[id]["SW"];
    val = _f4u$t.remap(val, MN, MX, A0, A0 + SW - (SW * P));
    var transform = _f4u$t.transformToArray(maybe_button.getAttribute("transform"));
    transform[2][1] = val;
    var movetothis = _f4u$t.arrayToTransform(transform);
    maybe_button.setAttribute("transform", movetothis);
    return 0;
  }
  else if (maybe_bargraph != null) {
    // ugh...code dups
    var MN = _f4u$t.IDS_TO_ATTRIBUTES[id]["MN"];
    var MX = _f4u$t.IDS_TO_ATTRIBUTES[id]["MX"];
    var A = _f4u$t.IDS_TO_ATTRIBUTES[id]["A"];
    var WA = _f4u$t.IDS_TO_ATTRIBUTES[id]["WA"];
    var SA = _f4u$t.IDS_TO_ATTRIBUTES[id]["SA"];
    val = _f4u$t[_f4u$t.xy(A, "remap", "remap_and_flip")](val, MN, MX, 0, SA);
    var newd = _f4u$t.xy(
      A,
      'M 0 0L'+val+' 0L'+val+' '+WA+'L0 '+WA+'L0 0',
      'M 0 '+SA+'L'+WA+' '+SA+'L'+WA+' '+val+'L0 '+val+'L0 '+SA
    );
    maybe_bargraph.setAttribute("d", newd);
    return 0;
  }
  // no corresponding incremental object
  return 0;
}

_f4u$t.actualize_buffer = function() {
  // get a valid number in there...
  var id = _f4u$t.unique(_f4u$t._N);

  var MN = _f4u$t.IDS_TO_ATTRIBUTES[id]["MN"];
  var MX = _f4u$t.IDS_TO_ATTRIBUTES[id]["MX"];
  var AD = _f4u$t.IDS_TO_ATTRIBUTES[id]["AD"];

  if (isNaN(_f4u$t.IDS_TO_ATTRIBUTES[id]["B"])) {
    _f4u$t.IDS_TO_ATTRIBUTES[id]["B"] = ""+_f4u$t.IDS_TO_ATTRIBUTES[id]["D"];
  }
  var c = parseFloat(_f4u$t.IDS_TO_ATTRIBUTES[id]["B"]);
  var label = document.getElementById(_f4u$t._N);
  var now = _f4u$t.bound(c, MN, MX);
  _f4u$t.IDS_TO_ATTRIBUTES[id]["B"] = ""+now;
  label.textContent = _f4u$t.IDS_TO_ATTRIBUTES[id]["B"];
  _f4u$t.IDS_TO_ATTRIBUTES[id]["D"] = _f4u$t.IDS_TO_ATTRIBUTES[id]["B"]; // prevents bad snaps of values

  // UI2DSP
  _f4u$t.fausthandler(AD, now);

  _f4u$t.actualize_incremental_object(id);
}

_f4u$t.buffer_backspace = function() {
  var id = _f4u$t.unique(_f4u$t._N);
  if (_f4u$t.IDS_TO_ATTRIBUTES[id]["B"].length == 0) {
    return 0;
  }
  _f4u$t.IDS_TO_ATTRIBUTES[id]["B"] = _f4u$t.IDS_TO_ATTRIBUTES[id]["B"].substring(0, _f4u$t.IDS_TO_ATTRIBUTES[id]["B"].length - 1);
  var label = document.getElementById(_f4u$t._N);
  label.textContent = _f4u$t.IDS_TO_ATTRIBUTES[id]["B"];
}

_f4u$t.make_delete_key_work = function(e) {
  if (e.keyCode == 8) {
    _f4u$t.buffer_backspace();
  }
}

_f4u$t.keys_to_sink = function(e) {
  if (_f4u$t._N == 0) {
    return 0;
  }
  var id = _f4u$t.unique(_f4u$t._N);
  if (e.keyCode == 13) {
    _f4u$t.actualize_buffer();
  }
  else {
    var key = e.keyCode;
    var str = String.fromCharCode(key)
    _f4u$t.IDS_TO_ATTRIBUTES[id]["B"] += str;
  }
  var label = document.getElementById(_f4u$t._N);
  label.textContent = _f4u$t.IDS_TO_ATTRIBUTES[id]["B"];
}

_f4u$t.make_key_sink = function(I) {
  _f4u$t._N = 'faust_value_value_'+I;
  _f4u$t.IDS_TO_ATTRIBUTES[I]["B"] = "";
  var box = document.getElementById("faust_value_box_"+I);
  box.style.stroke = "red";
}

_f4u$t.generic_key_sink = function(I) {
  var id = _f4u$t.unique(I);
  _f4u$t.make_key_sink(id);
  _f4u$t._I = 0;
}

_f4u$t.hslider_key_sink = function(I) {
  _f4u$t.generic_key_sink(I);
}

_f4u$t.vslider_key_sink = function(I) {
  _f4u$t.generic_key_sink(I);
}

_f4u$t.rotating_button_key_sink = function(I) {
  _f4u$t.generic_key_sink(I);
}

_f4u$t.move_to_ridiculous_negative = function(id) {
  _f4u$t.generic_translate(id, _f4u$t.NETHERWORLD, _f4u$t.NETHERWORLD);
}

_f4u$t.generic_translate = function(id, x, y) {
  var elt = document.getElementById(id);
  var transform = _f4u$t.transformToArray(elt.getAttribute("transform"));
  // we assume that there is only one element and that it is a transform
  // make sure to change this if things get more complicated
  // actually, just make sure not to make things more complicated...

  transform[0][1] = x;
  transform[0][2] = y;
  var movetothis = _f4u$t.arrayToTransform(transform);
  elt.setAttribute("transform", movetothis);
}

_f4u$t.initiate_tab_group = function(index, ids) {
  var strar = ids.split('#');
  // boo svg...tags
  for (var i = 0; strar.length > i; i++) {
    if (i != index) {
      _f4u$t.move_to_ridiculous_negative(strar[i]);
    }
  }
}

_f4u$t.shuffletabs = function(x, y, goodid, badids) {
  var strar = badids.split('#');
  for (var i = 0; strar.length > i; i++) {
    _f4u$t.move_to_ridiculous_negative(strar[i]);
  }
  _f4u$t.generic_translate(goodid, x, y);
}

_f4u$t.path_to_id = function (path, id) {
  _f4u$t.PATHS_TO_IDS[path] = id;
}

_f4u$t.devnull = function devnull() { }

document.onkeypress = _f4u$t.keys_to_sink;
document.onkeydown = _f4u$t.make_delete_key_work;
document.onmouseup = _f4u$t.clearIdCache;
document.onmousemove = _f4u$t.moveActiveObject;

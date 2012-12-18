/*
 * look for the phrase
 * UI2DSP to see where the UI sends messages to DSP
 * obviously, the goal is to separate the two as much as possible
 */


/*
  UTILITY FUNCTIONS
*/
_f4u$t.getClientX = function(e) {
  return e.clientX / _f4u$t.VIEWPORT_SCALE;
}

_f4u$t.getClientY = function(e) {
  return e.clientY / _f4u$t.VIEWPORT_SCALE;
}

_f4u$t.move_to_ridiculous_negative = function(id) {
  _f4u$t.generic_translate(id, -100000, -100000);
}

_f4u$t.path_to_id = function (path, id) {
  _f4u$t.PATHS_TO_IDS[path] = id;
}

_f4u$t.devnull = function devnull() { }

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

_f4u$t.updateXY = function(ee) {
  for (var i = 0; i < ee.length; i++) {
    _f4u$t.PREV[_f4u$t.X_AXIS][ee[i].identifier || 0] = _f4u$t.getClientX(ee[i]);
    _f4u$t.PREV[_f4u$t.Y_AXIS][ee[i].identifier || 0] = _f4u$t.getClientY(ee[i]);
  }
}

/*
  INITIALIZATION FUNCTIONS
*/

_f4u$t.initiate_nentry = function(fullid, minval, maxval, step, init, integer, ndec, label, address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "nentry";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"] = minval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"] = maxval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["step"] = step;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["init"] = init;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["integer"] = integer;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["ndec"] = ndec;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] = init;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["label"] = label;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_slider = function(axis, fullid, length, pctsliding, minval, maxval, step, init, integer, ndec, label, address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = (axis == _f4u$t.X_AXIS ? "hslider" : "vslider");
  _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"] = axis;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["length"] = length;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["pctsliding"] = pctsliding;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"] = minval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"] = maxval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["step"] = step;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["init"] = init;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["integer"] = integer;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["ndec"] = ndec;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["label"] = label;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_hslider = function(fullid, weakaxis, strongaxis, minval, maxval, step, init, integer, ndec, label, address) {
  _f4u$t.initiate_slider(_f4u$t.X_AXIS, fullid, weakaxis, strongaxis, minval, maxval, step, init, integer, ndec, label, address);
}

_f4u$t.initiate_vslider = function(fullid, weakaxis, strongaxis, minval, maxval, step, init, integer, ndec, label, address) {
  _f4u$t.initiate_slider(_f4u$t.Y_AXIS, fullid, weakaxis, strongaxis, minval, maxval, step, init, integer, ndec, label, address);
}

_f4u$t.initiate_bargraph = function(axis, fullid, weakaxis, strongaxis, minval, maxval, step, init, label, address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = (axis == _f4u$t.X_AXIS ? "hbargraph" : "vbargraph");
  _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"] = axis;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["weakaxis"] = weakaxis;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["strongaxis"] = strongaxis;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"] = minval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"] = maxval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["step"] = step;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["init"] = init;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["label"] = label;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_hbargraph = function(fullid, weakaxis, strongaxis, minval, maxval, step, init, label, address) {
  _f4u$t.initiate_bargraph(_f4u$t.X_AXIS, fullid, weakaxis, strongaxis, minval, maxval, step, init, label, address);
}

_f4u$t.initiate_vbargraph = function(fullid, weakaxis, strongaxis, minval, maxval, step, init, label, address) {
  _f4u$t.initiate_bargraph(_f4u$t.Y_AXIS, fullid, weakaxis, strongaxis, minval, maxval, step, init, label, address);
}

_f4u$t.initiate_rbutton = function(fullid,initangle,sweepangle,pctsliding,minval,maxval,step,init,integer,ndec,label,address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "rbutton";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["initangle"] = initangle;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["sweepangle"] = sweepangle;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["pctsliding"] = pctsliding;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["label"] = label;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"] = minval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"] = maxval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["step"] = step;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["init"] = init;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["integer"] = integer;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["ndec"] = ndec;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_checkbox = function(fullid, address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "checkbox";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_button = function(fullid, upfill, downfill, address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "button";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["upfill"] = upfill;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["downfill"] = downfill;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
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

/*
  ACTIVATION FUNCTIONS
  Activates UI objects as being in focus
*/

_f4u$t.activate_nentryminus = function(ee) {
  _f4u$t.activate_nentry(ee, -1);
}

_f4u$t.activate_nentryplus = function(ee) {
  _f4u$t.activate_nentry(ee, 1);
}

_f4u$t.activate_nentry = function(ee, dir) {
  // it is possible that an object is touched by multiple fingers at the
  // same time
  // if the id is already being used, we ignore
  // otherwise, use the first in the array...
  var identifier = ee.originalEvent.changedTouches ? ee.originalEvent.changedTouches[0].identifier : 0;
  _f4u$t._I[identifier] = {id : ee.target.id, moved : false};
  var id = _f4u$t.unique(_f4u$t._I[identifier].id);
  _f4u$t.updateXY(ee.originalEvent.changedTouches ? ee.originalEvent.changedTouches : [ee]);

  var now = parseFloat(_f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"]);
  if (dir == 1) {
    now += _f4u$t.IDS_TO_ATTRIBUTES[id]["step"];
  }
  else {
    now -= _f4u$t.IDS_TO_ATTRIBUTES[id]["step"];
  }

  now = _f4u$t.quantize(now, _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"], _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"], _f4u$t.IDS_TO_ATTRIBUTES[id]["step"]);
  now = _f4u$t.dumb_label_update(_f4u$t.unique(_f4u$t._I[identifier].id), now);
  return now;
}

_f4u$t.activate_hslider = function(ee) {
  _f4u$t.activate_slider(ee);
}

_f4u$t.activate_vslider = function(ee) {
  _f4u$t.activate_slider(ee);
}

_f4u$t.activate_slider = function(ee) {
  _f4u$t.activate_moving_object(ee);
}

_f4u$t.activate_rbutton = function(ee) {
  _f4u$t.activate_moving_object(ee);
}

_f4u$t.activate_moving_object = function(ee) {
  var touches = ee.changedTouches || [ee];
  if (ee.originalEvent) {
    touches = ee.originalEvent.changedTouches || [ee];
  }
  var identifier = touches[0].identifier || 0;
  _f4u$t._I[identifier] = {id : touches[0].target.id, moved : false};
  _f4u$t.updateXY(touches);
  // turns off zoom for mobile devices
  $('body').bind('touchmove', function(event) { event.preventDefault() });
}

_f4u$t.activate_tgroup = function(x, y, goodid, badids) {
  var strar = badids.split('#');
  for (var i = 0; strar.length > i; i++) {
    _f4u$t.move_to_ridiculous_negative(strar[i]);
  }
  _f4u$t.generic_translate(goodid, x, y);
}

/*
  MOVING FUNCTIONS.
  Functions that take care of moving the active object on the screen.
*/

// main function to move currently-selected slider
_f4u$t.moveActiveObject = function(ee) {
  for (var elt in _f4u$t._I) {
    if (_f4u$t._I[elt]) {
      var touches = ee.touches || [ee];
      if (ee.originalEvent) {
        touches = ee.originalEvent.touches || [ee];
      }
      for (var i = 0; i < touches.length; i++) {
        _f4u$t.internalMoveActiveObject(touches[i], ee.touches ? touches[i].identifier : 0);
      }
      // breaks loop, as we just need one active element for this to work
      return true;
    }
  }
  _f4u$t.updateXY(ee.touches ? ee.touches[0] : [ee]);
  return true;
}

_f4u$t.internalMoveActiveObject = function(e, identifier) {
  _f4u$t.clog_key_sink();
  _f4u$t.BUSY = true;

  var hslider_token = "faust_hslider_knob";
  var vslider_token = "faust_vslider_knob";
  var rotating_button_token = "faust_rbutton_knob"
  var now = null;
  if (_f4u$t._I[identifier]['id'].substring(0, hslider_token.length) == hslider_token) {
    now = _f4u$t.moveActiveSlider(e, identifier);
  }
  else if (_f4u$t._I[identifier]['id'].substring(0, vslider_token.length) == vslider_token) {
    now = _f4u$t.moveActiveSlider(e, identifier);
  }
  else if (_f4u$t._I[identifier]['id'].substring(0, rotating_button_token.length) == rotating_button_token) {
    now = _f4u$t.moveActiveRotatingButton(e, identifier);
  }

  // UI2DSP
  if (now != null) {
    var id = _f4u$t.unique(_f4u$t._I[identifier]['id']);
    _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"], now);
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

_f4u$t.moveActiveSlider = function(e,identifier)
{
  var sliding_part = document.getElementById(_f4u$t._I[identifier].id);
  var id = _f4u$t.unique(_f4u$t._I[identifier].id);
  var axis = _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"];
  var pctsliding = _f4u$t.IDS_TO_ATTRIBUTES[id]["pctsliding"];
  var length = _f4u$t.IDS_TO_ATTRIBUTES[id]["length"];
  var pos = -1;
  // we only care about the axis of the slider
  if (axis == _f4u$t.X_AXIS) {
    pos = _f4u$t.getClientX(e);
  }
  else {
    pos = _f4u$t.getClientY(e);
  }

  var diff = pos - _f4u$t.PREV[axis][identifier];
  var transform = _f4u$t.transformToArray(sliding_part.getAttribute("transform"));
  // we assume that there is only one element and that it is a transform
  // make sure to change this if things get more complicated
  // actually, just make sure not to make things more complicated...

  var aval = transform[0][axis + 1] + diff;

  // minimum of the slider is to the bottom / left
  transform[0][axis + 1] = _f4u$t.genericMovingPartUpdate(aval, transform[0][axis + 1], 0, length - (length * pctsliding));
  var now = _f4u$t[_f4u$t.xy(axis, "generic_label_update", "generic_flipped_label_update")](id, aval, 0, length - (length * pctsliding));
  var movetothis = _f4u$t.arrayToTransform(transform);
  sliding_part.setAttribute("transform", movetothis);
  _f4u$t.updateXY([e]);
  return now;
}

_f4u$t.moveActiveRotatingButton = function(e, identifier)
{
  var sliding_part = document.getElementById(_f4u$t._I[identifier].id);
  var anchor = document.getElementById('faust_rbutton_anchor_'+_f4u$t.unique(_f4u$t._I[identifier].id));
  var id = _f4u$t.unique(_f4u$t._I[identifier].id);
  var initangle = _f4u$t.IDS_TO_ATTRIBUTES[id]["initangle"];
  var sweepangle = _f4u$t.IDS_TO_ATTRIBUTES[id]["sweepangle"];
  var pctsliding = _f4u$t.IDS_TO_ATTRIBUTES[id]["pctsliding"];
  var os = $(anchor).offset();
  //console.log(anchor.getBoundingClientRect());
  var my_y = os['top'] / _f4u$t.VIEWPORT_SCALE;
  var my_x = os['left'] / _f4u$t.VIEWPORT_SCALE;

  var diff = 180. * (Math.atan2(_f4u$t.getClientY(e) - my_y, _f4u$t.getClientX(e) - my_x) - Math.atan2(_f4u$t.PREV[_f4u$t.Y_AXIS][identifier] - my_y, _f4u$t.PREV[_f4u$t.X_AXIS][identifier] - my_x)) / Math.PI;
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

  transform[2][1] = _f4u$t.genericMovingPartUpdate(aval, transform[2][1], initangle, initangle + sweepangle - (sweepangle * pctsliding));
  var now = _f4u$t.generic_label_update(_f4u$t.unique(_f4u$t._I[identifier].id), aval, initangle, initangle + sweepangle - (sweepangle * pctsliding));
  var movetothis = _f4u$t.arrayToTransform(transform);
  sliding_part.setAttribute("transform", movetothis);
  _f4u$t.updateXY([e]);
  return now;
}

// gets rid of the current thing being dragged
_f4u$t.clearIdCache = function(ee) {
  if (ee) {
    // sometimes, there will be no event passed in (i.e. a button)
    // if so, we can skip everything below
    var touches = ee.changedTouches || [ee];
    if (ee.originalEvent) {
      touches = ee.originalEvent.changedTouches || ee;
    }
    for (var i = 0; i < touches.length; i++) {
      delete _f4u$t._I[touches[i].identifier || 0];
    }
    if (!_f4u$t._N) {
      _f4u$t.BUSY = false;
    }
    // exit function before unbinding if there are still active elements
    for (var elt in _f4u$t._I) {
      if (_f4u$t._I[elt]) {
        return true;
      }
    }
  }
  // clear gunk out of cache
  _f4u$t._I = {};
  _f4u$t.PREV[_f4u$t.X_AXIS] = {};
  _f4u$t.PREV[_f4u$t.Y_AXIS] = {};
  $('body').unbind('touchmove'); // turns on zooming for mobile devices
}

_f4u$t.button_class_changer = function(id, down) {
  var mybutton = document.getElementById('faust_button_box_'+_f4u$t.unique(id));
  if (down) {
    //$('#faust_button_box_'+_f4u$t.unique(I)).removeClass('faust-button-up').addClass('faust-button-down');
    mybutton.style.fill = _f4u$t.IDS_TO_ATTRIBUTES[id].downfill;
  }
  else {
    //$('#faust_button_box_'+_f4u$t.unique(I)).removeClass('faust-button-down').addClass('faust-button-up');
    mybutton.style.fill = _f4u$t.IDS_TO_ATTRIBUTES[id].upfill;
  }
}

_f4u$t.button_up = function(I) {
  var id = _f4u$t.unique(I);
  _f4u$t.button_class_changer(id, false);
  _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"], 0);
  _f4u$t.clearIdCache();
}

_f4u$t.button_down = function(I) {
  var id = _f4u$t.unique(I);
  _f4u$t.clog_key_sink();
  _f4u$t.button_class_changer(id, true);
  // UI2DSP
  _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"], 1);
}

_f4u$t.change_checkbox = function(I) {
  _f4u$t.clog_key_sink();
  var address = _f4u$t.IDS_TO_ATTRIBUTES[_f4u$t.unique(I)]["address"];
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
  _f4u$t.fausthandler(address, opacity);
}

/*
  TEXT UPDATES
  Functions that take care of updating text based either on
  keyboard input or objects' moving.
*/

_f4u$t.generic_label_update = function(id, c, l, h) {
  var now = _f4u$t.remap_and_quantize(c, l, h, _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"], _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"], _f4u$t.IDS_TO_ATTRIBUTES[id]["step"]);
  return _f4u$t.dumb_label_update(id, now);
}

_f4u$t.generic_flipped_label_update = function(id, c, l, h) {
  var now = _f4u$t.remap_and_quantize_and_flip(c, l, h, _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"], _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"], _f4u$t.IDS_TO_ATTRIBUTES[id]["step"]);
  return _f4u$t.dumb_label_update(id, now);
}

_f4u$t.dumb_label_update = function(id, c) {
  var label = document.getElementById("faust_value_value_"+id);
  var integer = _f4u$t.IDS_TO_ATTRIBUTES[id]["integer"];
  if (integer) {
    c = (c + 0.49999).toString().parseInt();
  }
  else {
    c = c.toFixed(_f4u$t.IDS_TO_ATTRIBUTES[id]["ndec"]);
  }
  label.textContent = c;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] = c;
  return c;
}

_f4u$t.clog_key_sink = function() {
  if (_f4u$t._N != 0) {
    var box = document.getElementById("faust_value_box_"+_f4u$t.unique(_f4u$t._N));
    box.style.stroke = "black";
    _f4u$t.BUSY = false;
  }
  _f4u$t._N = 0;
}

_f4u$t.actualize_buffer = function() {
  // get a valid number in there...
  var id = _f4u$t.unique(_f4u$t._N);

  var minval = _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"];
  var maxval = _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"];
  var address = _f4u$t.IDS_TO_ATTRIBUTES[id]["address"];

  if (isNaN(_f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"])) {
    _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] = ""+_f4u$t.IDS_TO_ATTRIBUTES[id]["init"];
  }
  var c = parseFloat(_f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"]);
  var label = document.getElementById(_f4u$t._N);
  var now = _f4u$t.bound(c, minval, maxval);
  _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] = ""+now;
  label.textContent = _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"];
  _f4u$t.IDS_TO_ATTRIBUTES[id]["init"] = _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"]; // prevents bad snaps of values

  // UI2DSP
  _f4u$t.fausthandler(address, now);

  _f4u$t.actualize_incremental_object(id);
}

_f4u$t.buffer_backspace = function() {
  var id = _f4u$t.unique(_f4u$t._N);
  if (_f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"].length == 0) {
    return 0;
  }
  _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] = _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"].substring(0, _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"].length - 1);
  var label = document.getElementById(_f4u$t._N);
  label.textContent = _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"];
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
    _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] += str;
  }
  var label = document.getElementById(_f4u$t._N);
  label.textContent = _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"];
}

_f4u$t.make_key_sink = function(I) {
  if (_f4u$t.BUSY) {
    return false;
  }
  _f4u$t._N = 'faust_value_value_'+I;
  _f4u$t.IDS_TO_ATTRIBUTES[I]["buffer"] = "";
  var box = document.getElementById("faust_value_box_"+I);
  box.style.stroke = "red";
  _f4u$t.BUSY = true;
  // below is a hack for text inputs that should only be activated
  // after some work is done to figure out how to prevent auto zooming
  // in mobile devices
  //document.getElementById('faust-text-input-dummy').focus();
}

_f4u$t.generic_key_sink = function(I) {
  var id = _f4u$t.unique(I);
  _f4u$t.make_key_sink(id);
  _f4u$t._I = {};
  _f4u$t.PREV[_f4u$t.X_AXIS] = {};
  _f4u$t.PREV[_f4u$t.Y_AXIS] = {};
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

// if a numerical entry is linked to an incremental object,
// actualize it

_f4u$t.actualize_incremental_object = function(id) {
  var hslider_id = "faust_hslider_knob_"+id;
  var vslider_id = "faust_vslider_knob_"+id;
  var rotating_button_id = "faust_rbutton_knob_"+id;
  var hbargraph_id = "faust_hbargraph_meter_"+id;
  var vbargraph_id = "faust_vbargraph_meter_"+id;
  var val = parseFloat(_f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"]);
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
    var minval = _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"];
    var maxval = _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"];
    var length = _f4u$t.IDS_TO_ATTRIBUTES[id]["length"];
    var pctsliding = _f4u$t.IDS_TO_ATTRIBUTES[id]["pctsliding"];
    var axis = _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"];
    val = _f4u$t[_f4u$t.xy(axis, "remap", "remap_and_flip")](val, minval, maxval, 0, length - (length * pctsliding));
    var transform = _f4u$t.transformToArray(maybe_slider.getAttribute("transform"));
    transform[0][axis + 1] = val;
    var movetothis = _f4u$t.arrayToTransform(transform);
    maybe_slider.setAttribute("transform", movetothis);
    return 0;
  }
  else if (maybe_button != null) {
    var minval = _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"];
    var maxval = _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"];
    var initangle = _f4u$t.IDS_TO_ATTRIBUTES[id]["initangle"];
    var pctsliding = _f4u$t.IDS_TO_ATTRIBUTES[id]["pctsliding"];
    var sweepangle = _f4u$t.IDS_TO_ATTRIBUTES[id]["sweepangle"];
    val = _f4u$t.remap(val, minval, maxval, initangle, initangle + sweepangle - (sweepangle * pctsliding));
    var transform = _f4u$t.transformToArray(maybe_button.getAttribute("transform"));
    transform[2][1] = val;
    var movetothis = _f4u$t.arrayToTransform(transform);
    maybe_button.setAttribute("transform", movetothis);
    return 0;
  }
  else if (maybe_bargraph != null) {
    // ugh...code dups
    var minval = _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"];
    var maxval = _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"];
    var axis = _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"];
    var weakaxis = _f4u$t.IDS_TO_ATTRIBUTES[id]["weakaxis"];
    var strongaxis = _f4u$t.IDS_TO_ATTRIBUTES[id]["strongaxis"];
    val = _f4u$t[_f4u$t.xy(axis, "remap", "remap_and_flip")](val, minval, maxval, 0, strongaxis);
    var newd = _f4u$t.xy(
      axis,
      'M 0 0L'+val+' 0L'+val+' '+weakaxis+'L0 '+weakaxis+'L0 0',
      'M 0 '+strongaxis+'L'+weakaxis+' '+strongaxis+'L'+weakaxis+' '+val+'L0 '+val+'L0 '+strongaxis
    );
    maybe_bargraph.setAttribute("d", newd);
    return 0;
  }
  // no corresponding incremental object
  return 0;
}


/*
 DOCUMENT-WIDE DECLARATIONS
*/
_f4u$t.alert = function () { alert("moved"); }
document.onkeypress = _f4u$t.keys_to_sink;
document.onkeydown = _f4u$t.make_delete_key_work;
document.onmouseup = _f4u$t.clearIdCache;
document.onmousemove = _f4u$t.moveActiveObject;
document.ontouchend = _f4u$t.clearIdCache;
document.ontouchmove = _f4u$t.moveActiveObject;
// make the entire document clickable for mobile devices
document.onclick = _f4u$t.devnull;
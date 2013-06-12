/*
 * look for the phrase
 * UI2DSP to see where the UI sends messages to DSP
 * obviously, the goal is to separate the two as much as possible
 */


/*
  UTILITY FUNCTIONS
*/
_f4u$t.getOperativeX = function(e) {
  return (e.clientX + $(document).scrollLeft()) / _f4u$t.VIEWPORT_SCALE;
}

_f4u$t.getOperativeY = function(e) {
  return (e.clientY + $(document).scrollTop()) / _f4u$t.VIEWPORT_SCALE;
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
  var transform = _f4u$t.transform_to_array(elt.getAttribute("transform"));
  // we assume that there is only one element and that it is a transform
  // make sure to change this if things get more complicated
  // actually, just make sure not to make things more complicated...

  transform[0][1] = x;
  transform[0][2] = y;
  var movetothis = _f4u$t.array_to_transform(transform);
  elt.setAttribute("transform", movetothis);
}

// parser of an object's transform

_f4u$t.transform_to_array = function(transform) {
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

_f4u$t.array_to_transform = function(array) {
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

// all this PREV stuff can likely be deprecated
_f4u$t.updateXY = function(ee, initialize) {
  for (var i = 0; i < ee.length; i++) {
    _f4u$t.PREV[_f4u$t.X_AXIS][ee[i].identifier || 0] = initialize ? null : _f4u$t.getOperativeX(ee[i]);
    _f4u$t.PREV[_f4u$t.Y_AXIS][ee[i].identifier || 0] = initialize ? null : _f4u$t.getOperativeY(ee[i]);
  }
}

/*
  INITIALIZATION FUNCTIONS
*/

_f4u$t.initiate_nentry = function(fullid, minval, maxval, step, init, integer, ndec, label, unit, address) {
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
  _f4u$t.IDS_TO_ATTRIBUTES[id]["unit"] = unit;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["label"] = label;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_slider = function(axis, fullid, length, pctsliding, minval, maxval, step, init, integer, ndec, label, unit, orientation, address) {
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
  _f4u$t.IDS_TO_ATTRIBUTES[id]["unit"] = unit;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["orientation"] = orientation;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["integer"] = integer;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["ndec"] = ndec;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["label"] = label;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_hslider = function(fullid, weakaxis, strongaxis, minval, maxval, step, init, integer, ndec, label, unit, orientation, address) {
  _f4u$t.initiate_slider(_f4u$t.X_AXIS, fullid, weakaxis, strongaxis, minval, maxval, step, init, integer, ndec, label, unit, orientation, address);
}

_f4u$t.initiate_vslider = function(fullid, weakaxis, strongaxis, minval, maxval, step, init, integer, ndec, label, unit, orientation, address) {
  _f4u$t.initiate_slider(_f4u$t.Y_AXIS, fullid, weakaxis, strongaxis, minval, maxval, step, init, integer, ndec, label, unit, orientation, address);
}

_f4u$t.initiate_bargraph = function(axis, fullid, weakaxis, strongaxis, minval, maxval, step, init, label, unit, address) {
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
  _f4u$t.IDS_TO_ATTRIBUTES[id]["unit"] = unit;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["label"] = label;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_hbargraph = function(fullid, weakaxis, strongaxis, minval, maxval, step, init, label, unit, address) {
  _f4u$t.initiate_bargraph(_f4u$t.X_AXIS, fullid, weakaxis, strongaxis, minval, maxval, step, init, label, unit, address);
}

_f4u$t.initiate_vbargraph = function(fullid, weakaxis, strongaxis, minval, maxval, step, init, label, unit, address) {
  _f4u$t.initiate_bargraph(_f4u$t.Y_AXIS, fullid, weakaxis, strongaxis, minval, maxval, step, init, label, unit, address);
}

_f4u$t.initiate_rbutton = function(fullid,initangle,sweepangle,radius,knobpercentage,minval,maxval,step,init,integer,ndec,label,unit,orientation,address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "rbutton";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["initangle"] = initangle;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["sweepangle"] = sweepangle;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["radius"] = radius;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["knobpercentage"] = knobpercentage;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["label"] = label;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"] = minval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"] = maxval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["step"] = step;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["init"] = init;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["unit"] = unit;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["orientation"] = orientation;
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
  _f4u$t.IDS_TO_ATTRIBUTES[id]["time"] = 0;new Date().getTime();
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

_f4u$t.nentry_down_minus = function(ee) {
  _f4u$t.activate_nentry(ee, -1);
}

_f4u$t.nentry_down_plus = function(ee) {
  _f4u$t.activate_nentry(ee, 1);
}

_f4u$t.nentry_up_minus = function(ee) {
  _f4u$t.disactivate_nentry(ee, -1);
}

_f4u$t.nentry_up_plus = function(ee) {
  _f4u$t.disactivate_nentry(ee, 1);
}

_f4u$t.disactivate_nentry = function(ee, dir) {
  // it is possible that an object is touched by multiple fingers at the
  // same time
  // if the id is already being used, we ignore
  // otherwise, use the first in the array...
  var identifier = ee.originalEvent.changedTouches ? ee.originalEvent.changedTouches[0].identifier : 0;
  var longid = ee.target.id;
  var id = _f4u$t.unique(longid);
  _f4u$t.nentry_class_changer(id, false, dir);
}

_f4u$t.activate_nentry = function(ee, dir) {
  // it is possible that an object is touched by multiple fingers at the
  // same time
  // if the id is already being used, we ignore
  // otherwise, use the first in the array...
  var identifier = ee.originalEvent.changedTouches ? ee.originalEvent.changedTouches[0].identifier : 0;
  var longid = ee.target.id;
  var id = _f4u$t.unique(longid);
  _f4u$t.nentry_class_changer(id, true, dir);
  _f4u$t._I[identifier] = {id : longid, moved : false, value : null, address : _f4u$t.IDS_TO_ATTRIBUTES[id]["address"]};
  _f4u$t.active_addresses.push(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"]);
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
  _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"], now);
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
  var longid = touches[0].target.id;
  var id = _f4u$t.unique(longid);
  _f4u$t._I[identifier] = {id : longid, moved : false, value : null, address : _f4u$t.IDS_TO_ATTRIBUTES[id]["address"]};
  _f4u$t.active_addresses.push(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"]);
  _f4u$t.updateXY(touches, true);
  // turns off zoom for mobile devices
  $('body').bind('touchmove', function(event) { event.preventDefault() });
  // if we touch a groove, we want the object to snap to the correct position, so
  // we need to call the move function.
  _f4u$t.move_active_object(ee);
}

_f4u$t.activate_tgroup = function(x, y, goodid, badids) {
  var strar = badids.split('#');
  for (var i = 0; strar.length > i; i++) {
    _f4u$t.move_to_ridiculous_negative(strar[i]);
    _f4u$t.tgroup_class_changer(_f4u$t.unique(strar[i]), false);
  }
  _f4u$t.generic_translate(goodid, x, y);
  _f4u$t.tgroup_class_changer(_f4u$t.unique(goodid), true);
}

/*
  MOVING FUNCTIONS.
  Functions that take care of moving the active object on the screen.
*/

// ugh, interactivity should maybe go in ui_interact?
_f4u$t.tooltip_mouseover = function(e) {
  var id = _f4u$t.unique(e.target.id);
  var full_id = 'faust_tooltip_'+id
  document.getElementById(full_id).setAttribute("style","opacity:1.0");
  setTimeout(function () {
    _f4u$t.generic_translate(full_id, 0, 0);
    var os = $(document.getElementById(id)).offset();
    var my_x = os['left'] / _f4u$t.VIEWPORT_SCALE;
    var my_y = os['top'] / _f4u$t.VIEWPORT_SCALE;
    _f4u$t.generic_translate(full_id, _f4u$t.getOperativeX(e) - my_x, _f4u$t.getOperativeY(e) - my_y);
  }, 500);
}

_f4u$t.tooltip_mouseout = function(e) {
  var id = _f4u$t.unique(e.target.id);
  var full_id = 'faust_tooltip_'+id
  _f4u$t.move_to_ridiculous_negative(full_id);
  document.getElementById(full_id).setAttribute("style","opacity:0.0");
}

// main function to move currently-selected slider
_f4u$t.move_active_object = function(ee) {
  for (var elt in _f4u$t._I) {
    if (_f4u$t._I[elt] && (elt.indexOf('orientation') == -1)) {
      var touches = ee.touches || [ee];
      if (ee.originalEvent) {
        touches = ee.originalEvent.touches || [ee];
      }
      for (var i = 0; i < touches.length; i++) {
        _f4u$t.internal_move_active_object(touches[i], touches[0] == ee ? 0 : touches[i].identifier);
      }
      // breaks loop, as we just need one active element for this to work
      return true;
    }
  }
  _f4u$t.updateXY(ee.touches ? ee.touches[0] : [ee]);
  return true;
}

// TODO
// Does this really need to be a separate function.
// Helps for readability, but not necessary
_f4u$t.internal_move_active_object = function(e, identifier) {
  _f4u$t.clog_key_sink();
  var now = _f4u$t['move_active_'+_f4u$t.type(_f4u$t._I[identifier]['id'])](e, identifier);

  // UI2DSP
  if (now != null && now != _f4u$t._I[identifier]['value']) {
    var id = _f4u$t.unique(_f4u$t._I[identifier]['id']);
    _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"], now);
    _f4u$t._I[identifier]['value'] = now;
  }

  return now;
}

_f4u$t.redraw_slider_groove = function(id, axis, length, perc) {
  perc = _f4u$t.bound(perc, 0, 1); // to avoid mouse spillover on either side of slider
  var groove = document.getElementById('faust_'+(_f4u$t.xy(axis,'hslider','vslider'))+'_groove_'+id);
  if (axis == _f4u$t.X_AXIS) {
    groove.setAttribute('x', length * perc)
    groove.setAttribute('width', length * (1 - perc));
  }
  if (axis == _f4u$t.Y_AXIS) {
    groove.setAttribute('height', length * perc);
  }
}

_f4u$t.move_active_slider = function(e,identifier)
{
  var id = _f4u$t.unique(_f4u$t._I[identifier].id);
  var axis = _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"];
  var sliding_part = document.getElementById(_f4u$t.xy(axis, 'faust_hslider_handle_', 'faust_vslider_handle_')+id);
  var anchor = document.getElementById(_f4u$t.xy(axis, 'faust_hslider_meter_', 'faust_vslider_meter_')+id);
  var pctsliding = _f4u$t.IDS_TO_ATTRIBUTES[id]["pctsliding"];
  var length = _f4u$t.IDS_TO_ATTRIBUTES[id]["length"];
  var pos = -1;
  var os = $(anchor).offset();
  //console.log(os, anchor.getBoundingClientRect(), $(document).scrollTop());
  var my_x = os['left'] / _f4u$t.VIEWPORT_SCALE;
  var my_y = os['top'] / _f4u$t.VIEWPORT_SCALE;
  // we only care about the axis of the slider
  if (axis == _f4u$t.X_AXIS) {
    pos = _f4u$t.getOperativeX(e) - my_x;
  }
  else {
    pos = _f4u$t.getOperativeY(e) - my_y;
  }

  pos -= (length * pctsliding / 2.0);
  //var diff = pos - _f4u$t.PREV[axis][identifier];
  var transform = _f4u$t.transform_to_array(sliding_part.getAttribute("transform"));
  // we assume that there is only one element and that it is a transform
  // make sure to change this if things get more complicated
  // actually, just make sure not to make things more complicated...

  var aval = pos;//transform[0][axis + 1] + diff;
  // minimum of the slider is to the bottom / left
  transform[0][axis + 1] = _f4u$t.bound_and_avoid_large_leaps(aval, transform[0][axis + 1], 0, length - (length * pctsliding));
  _f4u$t.redraw_slider_groove(
    id,
    axis,
    length,
    aval / length
  );
  var now = _f4u$t[_f4u$t.xy(axis, "generic_label_update", "generic_flipped_label_update")](id, aval, 0, length - (length * pctsliding));
  var movetothis = _f4u$t.array_to_transform(transform);
  sliding_part.setAttribute("transform", movetothis);
  _f4u$t.updateXY([e]);
  return now;
}

_f4u$t.move_active_vslider = _f4u$t.move_active_slider;
_f4u$t.move_active_hslider = _f4u$t.move_active_slider;

_f4u$t.respondToOrientationChange = function(e) {
  for (var id in _f4u$t.IDS_TO_ATTRIBUTES) {
    if (_f4u$t.IDS_TO_ATTRIBUTES[id].orientation &&
        _f4u$t.IDS_TO_ATTRIBUTES[id].orientation.angle)
      {
        if (!_f4u$t._I['orientation'+id]) {
          _f4u$t._I['orientation'+id] = {id : id, moved : false, value : null, address : _f4u$t.IDS_TO_ATTRIBUTES[id]["address"]};
        }
        var now = null;
        if ((_f4u$t.IDS_TO_ATTRIBUTES[id]["type"] == 'hslider')
            || (_f4u$t.IDS_TO_ATTRIBUTES[id]["type"] == 'vslider')) {
           // ugh...this means that they will not be disactivated...
           _f4u$t.active_addresses.push(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"]);
          now = _f4u$t.moveSliderViaAccelerometer(e, id);
        }
        // UI2DSP
        if (now != null && now != _f4u$t._I['orientation'+id]['value']) {
          _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"], now);
          _f4u$t._I['orientation'+id]['value'] = now;
        }
      }
  }
}

// TODO...combine this with above...
// simplified version, so shouldn't be too hard
_f4u$t.moveSliderViaAccelerometer = function(e, longid) {
  var id = _f4u$t.unique(longid);
  var axis = _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"];
  var sliding_part = document.getElementById(_f4u$t.xy(axis, 'faust_hslider_handle_', 'faust_vslider_handle_')+id);
  var pctsliding = _f4u$t.IDS_TO_ATTRIBUTES[id]["pctsliding"];
  var length = _f4u$t.IDS_TO_ATTRIBUTES[id]["length"];
  var pos = _f4u$t.remap(e[_f4u$t.IDS_TO_ATTRIBUTES[id].orientation.angle],
                         _f4u$t.IDS_TO_ATTRIBUTES[id].orientation.low,
                         _f4u$t.IDS_TO_ATTRIBUTES[id].orientation.high,
                         0,
                         length - (length * pctsliding));
  var transform = _f4u$t.transform_to_array(sliding_part.getAttribute("transform"));
  // we assume that there is only one element and that it is a transform
  // make sure to change this if things get more complicated
  // actually, just make sure not to make things more complicated...

  var aval = pos;
  // minimum of the slider is to the bottom / left
  transform[0][axis + 1] = _f4u$t.bound_and_avoid_large_leaps(aval, transform[0][axis + 1], 0, length - (length * pctsliding));
  _f4u$t.redraw_slider_groove(
    id,
    axis,
    length,
    aval / length
  );
  var now = _f4u$t[_f4u$t.xy(axis, "generic_label_update", "generic_flipped_label_update")](id, aval, 0, length - (length * pctsliding));
  var movetothis = _f4u$t.array_to_transform(transform);
  sliding_part.setAttribute("transform", movetothis);
  // no updating XY as there is no event specific to this object
  //_f4u$t.updateXY([e]);
  return now;
}

_f4u$t.redrawRotatingButtonMeter = function(id, initangle, sweepangle, radius, knobpercentage, startp) {
  var meter = document.getElementById('faust_rbutton_meter_'+id);
  var xo = radius;
  var yo = radius;

  var d = "M{0} {1}A{2} {3} 0 {4} {5} {6} {7}L{8} {9}A{10} {11} 0 {12} {13} {14} {15}L{16} {17}";
  d = d.format([
    radius * Math.cos(_f4u$t.d2r(startp)) + xo, // outside X
    radius * Math.sin(_f4u$t.d2r(startp)) + yo, // outside Y
    radius, // radius X
    radius, // radius Y
    initangle + sweepangle - startp <= 180 ? 0 : 1, // large arc flag
    1, // draw positive
    radius * Math.cos(_f4u$t.d2r(initangle + sweepangle)) + xo, // endpoint X
    radius * Math.sin(_f4u$t.d2r(initangle + sweepangle)) + yo, // endpoint Y
    radius * knobpercentage * Math.cos(_f4u$t.d2r(initangle + sweepangle)) + xo, // inside endpoint X
    radius * knobpercentage * Math.sin(_f4u$t.d2r(initangle + sweepangle)) + yo, // inside endpoint Y
    radius * knobpercentage, // inside radiux X
    radius * knobpercentage, // inside radiux Y
    initangle + sweepangle - startp <= 180 ? 0 : 1, // large arc flag
    0, // draw negative
    radius * knobpercentage * Math.cos(_f4u$t.d2r(startp)) + xo, // inside X
    radius * knobpercentage * Math.sin(_f4u$t.d2r(startp)) + yo, // inside Y
    radius * Math.cos(_f4u$t.d2r(startp)) + xo, // outside X
    radius * Math.sin(_f4u$t.d2r(startp)) + yo// outside Y
  ]);

  meter.setAttribute("d", d);
}

_f4u$t.move_active_rbutton = function(e, identifier)
{
  var id = _f4u$t.unique(_f4u$t._I[identifier].id);
  var sliding_part = document.getElementById('faust_rbutton_handle_'+id);
  var anchor = document.getElementById('faust_rbutton_anchor_'+id);
  var initangle = _f4u$t.IDS_TO_ATTRIBUTES[id]["initangle"];
  var sweepangle = _f4u$t.IDS_TO_ATTRIBUTES[id]["sweepangle"];
  var os = $(anchor).offset();
  var my_x = os['left'] / _f4u$t.VIEWPORT_SCALE;
  var my_y = os['top'] / _f4u$t.VIEWPORT_SCALE;
  var transform = _f4u$t.transform_to_array(sliding_part.getAttribute("transform"));

  var diff = 180. * Math.atan2(_f4u$t.getOperativeY(e) - my_y, _f4u$t.getOperativeX(e) - my_x) / Math.PI;
  while (diff < 0) {
    diff += 360;
  }
  diff = diff % 360;
  // put it between the values if necessary
  if (((360 + diff) >= initangle) && ((360 + diff) <= (initangle + sweepangle))) {
    diff += 360;
  }

  if (e.target.id.indexOf('dot') != -1) {
    // if it is a panoramic dot, snap to the multiple of 45
    diff = parseInt((diff / 45) + 0.5) * 45;
  }
  // we assume that there is only one element and that it is a transform
  // make sure to change this if things get more complicated
  // actually, just make sure not to make things more complicated...

  var aval = diff;
  var rotation = transform[2][1];
  // always change rotation if we're starting with a click
  if (_f4u$t.PREV[_f4u$t.X_AXIS][identifier] == null) {
    rotation = _f4u$t.bound_and_avoid_large_leaps(aval, transform[2][1], initangle, initangle + sweepangle);
  } else if (((aval >= initangle) && (aval <= (initangle + sweepangle)))
             && ((Math.abs(aval - rotation) < 35)
                 || (Math.abs (360 - Math.abs(aval - rotation)) < 35))) {
    // only change rotation if we're in bounds and the difference is small
    rotation = _f4u$t.bound_and_avoid_large_leaps(aval, transform[2][1], initangle, initangle + sweepangle);
  }
  transform[2][1] = rotation;
  if (sweepangle != 360) {
    _f4u$t.redrawRotatingButtonMeter(
      id,
      initangle,
      sweepangle,
      _f4u$t.IDS_TO_ATTRIBUTES[id]["radius"],
      _f4u$t.IDS_TO_ATTRIBUTES[id]["knobpercentage"],
      transform[2][1]
    );
  }
  var now = _f4u$t.generic_label_update(id, rotation, initangle, initangle + sweepangle);
  var movetothis = _f4u$t.array_to_transform(transform);
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
      if (_f4u$t._I[touches[i].identifier || 0]) {
        var addr = _f4u$t._I[touches[i].identifier || 0].address;
        while (_f4u$t.active_addresses.indexOf(addr) !== -1) {
          _f4u$t.active_addresses.splice(_f4u$t.active_addresses.indexOf(addr), 1);
        }
        delete _f4u$t._I[touches[i].identifier || 0];
      }
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
  _f4u$t.active_addresses = [];
  _f4u$t.PREV[_f4u$t.X_AXIS] = {};
  _f4u$t.PREV[_f4u$t.Y_AXIS] = {};
  $('body').unbind('touchmove'); // turns on zooming for mobile devices
}

_f4u$t.button_class_changer = function(id, down) {
  if (down) {
    $('#faust_button_box_'+_f4u$t.unique(id)).removeClass('faust-button-up').addClass('faust-button-down');
  }
  else {
    $('#faust_button_box_'+_f4u$t.unique(id)).removeClass('faust-button-down').addClass('faust-button-up');
  }
}

// TODO : this is just a copy and paste of the above
// if we need more of these, consolidate
_f4u$t.tgroup_class_changer = function(id, down) {
  if (down) {
    $('#faust_tab_'+_f4u$t.unique(id)).removeClass('faust-tgroup-up').addClass('faust-tgroup-down');
  }
  else {
    $('#faust_tab_'+_f4u$t.unique(id)).removeClass('faust-tgroup-down').addClass('faust-tgroup-up');
  }
}

// DITTO - slight variation on function above
_f4u$t.nentry_class_changer = function(id, down, dir) {
  var dirtext = dir == -1 ? 'minus' : 'plus';
  if (down) {
    $('#faust_nentry_button_'+dirtext+'_'+_f4u$t.unique(id)).removeClass('faust-nentry-up').addClass('faust-nentry-down');
  }
  else {
    $('#faust_nentry_button_'+dirtext+'_'+_f4u$t.unique(id)).removeClass('faust-nentry-down').addClass('faust-nentry-up');
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
  _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"], 1);
}

_f4u$t.click_checkbox = function(I) {
  _f4u$t.change_checkbox(I, false);
}
_f4u$t.touch_checkbox = function(I) {
  _f4u$t.change_checkbox(I, true);
}

_f4u$t.change_checkbox = function(I, touch) {
  var id = _f4u$t.unique(I)
  var now = new Date().getTime();
  if (touch && ((now - _f4u$t.IDS_TO_ATTRIBUTES[id]["time"]) < 1000)) {
    return;
  }
  _f4u$t.IDS_TO_ATTRIBUTES[id]["time"] = now;
  _f4u$t.clog_key_sink();
  var address = _f4u$t.IDS_TO_ATTRIBUTES[id]["address"];
  var box = document.getElementById('faust_checkbox_check_'+id);
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

_f4u$t.change_label_text = function(label, id)
{
  label.textContent = _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] + _f4u$t.IDS_TO_ATTRIBUTES[id]["unit"];
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
  _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] = c;
  _f4u$t.change_label_text(label, id);;
  return c;
}

_f4u$t.clog_key_sink = function() {
  if (_f4u$t._N != 0) {
    var box = document.getElementById("faust_value_box_"+_f4u$t.unique(_f4u$t._N));
    box.style.stroke = "black";
    _f4u$t.ajax_queue_busy = false;
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
  _f4u$t.change_label_text(label, id);
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
  _f4u$t.change_label_text(label, id);;
}

_f4u$t.make_delete_key_work = function(e) {
  if (e.keyCode == 8) {
    _f4u$t.buffer_backspace();
  }
}

_f4u$t.keys_to_sink = function(e) {
  if (_f4u$t._N == "") {
    return 0;
  }
  var id = _f4u$t.unique(_f4u$t._N);
  if (e.keyCode == 13) {
    _f4u$t.actualize_buffer();
    _f4u$t.clog_key_sink();
    return;
  }
  else {
    var key = e.keyCode;
    var str = String.fromCharCode(key)
    _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] += str;
  }
  var label = document.getElementById(_f4u$t._N);
  _f4u$t.change_label_text(label, id);;
}

_f4u$t.make_key_sink = function(I) {
  if (_f4u$t.ajax_queue_busy) {
    return false;
  }
  _f4u$t._N = 'faust_value_value_'+I;
  _f4u$t.IDS_TO_ATTRIBUTES[I]["buffer"] = "";
  var box = document.getElementById("faust_value_box_"+I);
  box.style.stroke = "red";
  _f4u$t.ajax_queue_busy = true;
  // below is a hack for text inputs that should only be activated
  // after some work is done to figure out how to prevent auto zooming
  // in mobile devices
  //document.getElementById('faust-text-input-dummy').focus();
}

_f4u$t.generic_key_sink = function(I) {
  var id = _f4u$t.unique(I);
  _f4u$t.make_key_sink(id);
  _f4u$t._I = {};
  _f4u$t.active_addresses = [];
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

_f4u$t.nentry_key_sink = function(I) {
  _f4u$t.generic_key_sink(I);
}

// if a numerical entry is linked to an incremental object,
// actualize it

_f4u$t.actualize_incremental_object = function(id) {
  var hslider_id = "faust_hslider_handle_"+id;
  var vslider_id = "faust_vslider_handle_"+id;
  var rotating_button_id = "faust_rbutton_handle_"+id;
  var hbargraph_id = "faust_hbargraph_curtain_"+id;
  var vbargraph_id = "faust_vbargraph_curtain_"+id;
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
    var transform = _f4u$t.transform_to_array(maybe_slider.getAttribute("transform"));
    transform[0][axis + 1] = val;
    _f4u$t.redraw_slider_groove(
      id,
      axis,
      length,
      val / length
    );
    var movetothis = _f4u$t.array_to_transform(transform);
    maybe_slider.setAttribute("transform", movetothis);
    return 0;
  }
  else if (maybe_button != null) {
    var minval = _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"];
    var maxval = _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"];
    var initangle = _f4u$t.IDS_TO_ATTRIBUTES[id]["initangle"];
    var sweepangle = _f4u$t.IDS_TO_ATTRIBUTES[id]["sweepangle"];
    val = _f4u$t.remap(val, minval, maxval, initangle, initangle + sweepangle);
    var transform = _f4u$t.transform_to_array(maybe_button.getAttribute("transform"));
    transform[2][1] = val;
    if (sweepangle != 360) {
      _f4u$t.redrawRotatingButtonMeter(
        id,
        _f4u$t.IDS_TO_ATTRIBUTES[id]["initangle"],
        _f4u$t.IDS_TO_ATTRIBUTES[id]["sweepangle"],
        _f4u$t.IDS_TO_ATTRIBUTES[id]["radius"],
        _f4u$t.IDS_TO_ATTRIBUTES[id]["knobpercentage"],
        transform[2][1]
      );
    }
    var movetothis = _f4u$t.array_to_transform(transform);
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
    val = _f4u$t.bound(val, 0, strongaxis);
    /*
    // for paths...
    var newd = _f4u$t.xy(
      axis,
      'M 0 0L'+val+' 0L'+val+' '+weakaxis+'L0 '+weakaxis+'L0 0',
      'M 0 '+strongaxis+'L'+weakaxis+' '+strongaxis+'L'+weakaxis+' '+val+'L0 '+val+'L0 '+strongaxis
    );
    maybe_bargraph.setAttribute("d", newd);
    */
    maybe_bargraph.setAttribute("width", Math.max(0,_f4u$t.xy(axis, val, weakaxis)));
    maybe_bargraph.setAttribute("height", Math.max(0, _f4u$t.xy(axis, weakaxis, val)));
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
document.onmousemove = _f4u$t.move_active_object;
document.ontouchend = _f4u$t.clearIdCache;
document.ontouchmove = _f4u$t.move_active_object;
window.ondeviceorientation = _f4u$t.respondToOrientationChange;
// make the entire document clickable for mobile devices
document.onclick = _f4u$t.devnull;
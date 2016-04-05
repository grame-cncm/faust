_f4u$t.check_label = function(label) {
  return (label.substring(0, 2) == "0x") ? "" : label;
}

_f4u$t.meta_info = function(dct, prop, def, fn) {
  if (!dct['meta']) {
    return def;
  }
  for (var i=0; i < dct['meta'].length; i++) {
    if (dct['meta'][i][prop]) {
      return fn(dct['meta'][i][prop]);
    }
  }
  return def;
}

_f4u$t.has_knob = function(dct) {
  return _f4u$t.meta_info(dct, 'style', false, function(prop) { return prop == 'knob'; });
}

_f4u$t.get_unit = function(dct) {
  return _f4u$t.meta_info(dct, 'unit', '', _f4u$t.identity);
}

_f4u$t.get_tooltip = function(dct) {
  return _f4u$t.meta_info(dct, 'tooltip', '', _f4u$t.identity);
}

_f4u$t.get_orientation_mode = function(dct) {
  return _f4u$t.meta_info(dct, 'orientation-mode', 'absolute', _f4u$t.identity);
}

_f4u$t.get_orientation = function(dct) {
  return _f4u$t.meta_info(dct, 'orientation', {}, _f4u$t.parse_orientation);
}

_f4u$t.is_panoramic = function(dct) {
  return _f4u$t.meta_info(dct, 'panoramic', false, function(prop) { return prop === 'true'; });
}

_f4u$t.get_sweep = function(dct) {
  return _f4u$t.meta_info(dct, 'sweep', _f4u$t.rbutton_inits.sweep, function(prop) { return parseFloat(prop) != null ? parseFloat(prop) : _f4u$t.rbutton_inits.sweep; });
}

_f4u$t.get_size = function(dct) {
  return _f4u$t.meta_info(dct, 'size', 1, function(prop) { return [0.5,1,2,3,4][parseInt(prop)]; });
}

_f4u$t.getnumspecs = function(dct) {
  var integer = false;
  if((parseFloat(dct["max"]) == parseInt(dct["max"]))
     && (parseFloat(dct["min"]) == parseInt(dct["min"]))
     && (parseFloat(dct["step"]) == parseInt(dct["step"]))
     && (parseFloat(dct["init"]) == parseInt(dct["init"]))
     && !isNaN(dct["max"])
     && !isNaN(dct["min"])
     && !isNaN(dct["step"])
     && !isNaN(dct["init"])) {
    integer = true;
  }

  var maxsplit = dct["max"] ? dct["max"].toString().split('.') : ['',''];
  var minsplit = dct["min"] ? dct["min"].toString().split('.') : ['',''];
  var stepsplit = dct["step"] ? dct["step"].toString().split('.') : ['',''];
  var initsplit = dct["init"] ? dct["init"].toString().split('.') : ['',''];
  maxsplit[1] = maxsplit[1] || '';
  minsplit[1] = minsplit[1] || '';
  stepsplit[1] = stepsplit[1] || '';
  initsplit[1] = initsplit[1] || '';
  parser = integer ? parseInt : parseFloat;
  return {
    min : parser(dct["min"]),
    max : parser(dct["max"]),
    step : parser(dct["step"]),
    init : parser(dct["init"]),
    isint : integer,
    ndec : Math.max(maxsplit[1].length, minsplit[1].length, stepsplit[1].length, initsplit[1].length)
  };
}

_f4u$t.make_rbutton = function(dct, hash) {
  var numspecs = _f4u$t.getnumspecs(dct);
  var id = _f4u$t.randString();
  var options = $.extend(true, {}, _f4u$t.rbutton_inits);
  options.id = id;
  options.min = numspecs["min"];
  options.max = numspecs["max"];
  options.step = numspecs["step"];
  options.init = numspecs["init"];
  options.integer = numspecs["integer"];
  options.ndec = numspecs["ndec"];
  options.address = hash+dct["address"];
  options.unit = _f4u$t.get_unit(dct);
  options.tooltip = _f4u$t.get_tooltip(dct);
  options.orientation = _f4u$t.get_orientation(dct);
  options.orientation_mode = _f4u$t.get_orientation_mode(dct);
  if (_f4u$t.is_panoramic(dct)) {
    options.a0 = 0;
    options.sweep = 360;
  }
  var size = _f4u$t.get_size(dct);
  options.ir *= size;

  var vbox_options = $.extend(true, {}, _f4u$t.vbox_inits);
  vbox_options.init = numspecs["init"];
  vbox_options.id = id;
  var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
  lm_options.axis = _f4u$t.Y_AXIS;
  lm_options.stretchable = [false, false];

  /* make faust ui objects */
  var rbutton = new _f4u$t.RotatingButton(options);
  var label = new _f4u$t.Label({label : _f4u$t.check_label(dct["label"]), id : id+"label", mom : null});
  var vbox = new _f4u$t.ValueBox(vbox_options);

  var lm = new _f4u$t.LayoutManager(lm_options);
  lm.objs.push(label);
  lm.objs.push(rbutton);
  lm.objs.push(vbox);

  return lm;
}

_f4u$t.make_hslider = function(dct, hash) {
  return _f4u$t.make_slider(_f4u$t.HorizontalSlider, dct, hash);
}

_f4u$t.make_vslider = function(dct, hash) {
  return _f4u$t.make_slider(_f4u$t.VerticalSlider, dct, hash);
}

_f4u$t.make_slider = function(kls, dct, hash) {
  if (_f4u$t.has_knob(dct)) {
    return _f4u$t.make_rbutton(dct, hash);
  }
  var numspecs = _f4u$t.getnumspecs(dct);
  var horizontal = kls == _f4u$t.HorizontalSlider;
  var id = _f4u$t.randString();
  var options = $.extend(true, {}, _f4u$t[horizontal ? 'hslider_inits' : 'vslider_inits']);
  options.id = id;
  options.min = numspecs["min"];
  options.max = numspecs["max"];
  options.step = numspecs["step"];
  options.init = numspecs["init"];
  options.integer = numspecs["integer"];
  options.ndec = numspecs["ndec"];
  options.address = hash+dct["address"];
  options.unit = _f4u$t.get_unit(dct);
  options.orientation = _f4u$t.get_orientation(dct);
  options.orientation_mode = _f4u$t.get_orientation_mode(dct);
  options.tooltip = _f4u$t.get_tooltip(dct);
  var size = _f4u$t.get_size(dct);
  options.girth *= size;
  options.length *= size;

  var vbox_options = $.extend(true, {}, _f4u$t.vbox_inits);
  vbox_options.init = numspecs["init"];
  vbox_options.id = id;

  /* make faust ui objects */
  var slider = new kls(options);
  var label = new _f4u$t.Label({label : _f4u$t.check_label(dct["label"]), id : id+"label", mom : null});
  var vbox = new _f4u$t.ValueBox(vbox_options);

  var lm = 0;
  if (horizontal) {
    var internal_lm_options = $.extend(true, {}, _f4u$t.hgroup_inits);
    internal_lm_options.axis = _f4u$t.X_AXIS
    internal_lm_options.draw_background = false;
    internal_lm_options.other_axis_padding = 0;
    var internal_lm = new _f4u$t.LayoutManager(internal_lm_options);
    internal_lm.objs.push(vbox);
    internal_lm.objs.push(slider);

    var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
    lm_options.axis = _f4u$t.Y_AXIS;
    lm_options.gravity = _f4u$t.LEFT;
    lm_options.stretchable = [true, false];
    lm = new _f4u$t.LayoutManager(lm_options);
    lm.objs.push(label);
    lm.objs.push(internal_lm);
  } else {
    var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
    lm_options.axis = _f4u$t.Y_AXIS;
    lm_options.stretchable = [false, true];
    lm = new _f4u$t.LayoutManager(lm_options);
    lm.objs.push(label);
    lm.objs.push(slider);
    lm.objs.push(vbox);
  }

  return lm;
}

_f4u$t.make_hbargraph = function(dct, hash) {
  return _f4u$t.make_bargraph(_f4u$t.HorizontalBarGraph, dct, hash);
}

_f4u$t.make_vbargraph = function(dct, hash) {
  return _f4u$t.make_bargraph(_f4u$t.VerticalBarGraph, dct, hash);
}

_f4u$t.make_bargraph = function(kls, dct, hash) {
  var horizontal = kls == _f4u$t.HorizontalBarGraph;
  var id = _f4u$t.randString();
  var options = $.extend(true, {}, _f4u$t[horizontal ? 'hbargraph_inits' : 'vbargraph_inits']);
  options.id = id;
  //var numspecs = _f4u$t.getnumspecs(dct);
  options.min = parseFloat(dct["min"]);
  options.max = parseFloat(dct["max"]);
  options.address = hash+dct["address"];
  options.unit = _f4u$t.get_unit(dct);
  var size = _f4u$t.get_size(dct);
  options.tooltip = _f4u$t.get_tooltip(dct);
  options.girth *= size;
  options.length *= size;

  var vbox_options = $.extend(true, {}, _f4u$t.vbox_inits);
  vbox_options.keysink = false;
  vbox_options.id = id;
  var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
  lm_options.axis = _f4u$t.Y_AXIS;

  /* make faust ui objects */
  var bargraph = new kls(options);
  var label = new _f4u$t.Label({label : _f4u$t.check_label(dct["label"]), id : id+"_label", mom : null});
  var vbox = new _f4u$t.ValueBox(vbox_options);

  var lm = 0;
  // ugh...code dup from slider...
  if (horizontal) {
    var internal_lm_options = $.extend(true, {}, _f4u$t.hgroup_inits);
    internal_lm_options.axis = _f4u$t.X_AXIS
    internal_lm_options.draw_background = false;
    internal_lm_options.other_axis_padding = 0;
    var internal_lm = new _f4u$t.LayoutManager(internal_lm_options);
    internal_lm.objs.push(vbox);
    internal_lm.objs.push(bargraph);

    var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
    lm_options.axis = _f4u$t.Y_AXIS;
    lm_options.gravity = _f4u$t.LEFT;
    lm_options.stretchable = [true, false];
    lm = new _f4u$t.LayoutManager(lm_options);
    lm.objs.push(label);
    lm.objs.push(internal_lm);
  } else {
    var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
    lm_options.axis = _f4u$t.Y_AXIS;
    lm_options.stretchable = [false, true];
    lm = new _f4u$t.LayoutManager(lm_options);
    lm.objs.push(label);
    lm.objs.push(bargraph);
    lm.objs.push(vbox);
  }

  return lm;
}

_f4u$t.make_button = function(dct, hash) {
  var id = _f4u$t.randString();
  var options = $.extend(true, {}, _f4u$t.button_inits);
  options.id = id;
  options.label = dct.label;
  options.address = hash+dct.address;
  options.tooltip = _f4u$t.get_tooltip(dct);
  return new _f4u$t.Button(options);
}

_f4u$t.make_checkbox = function(dct, hash) {
  var id = _f4u$t.randString();
  var options = $.extend(true, {}, _f4u$t.checkbox_inits);
  options.id = id;
  options.address = hash+dct.address;
  options.init = (dct.init == "1" ? true : false);
  var size = _f4u$t.get_size(dct);
  options.tooltip = _f4u$t.get_tooltip(dct);
  options.d *= size;

  var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
  lm_options.axis = _f4u$t.X_AXIS;
  lm_options.stretchable = [false, false];

  /* make faust ui objects */
  var checkbox = new _f4u$t.CheckBox(options);
  var label = new _f4u$t.Label({label : _f4u$t.check_label(dct["label"]), id : id+"_label", mom : null});

  var lm = new _f4u$t.LayoutManager(lm_options);
  lm.objs.push(checkbox);
  lm.objs.push(label);

  return lm;
}

_f4u$t.make_nentry = function(dct, hash) {
  if (_f4u$t.has_knob(dct)) {
    return _f4u$t.make_rbutton(dct, hash);
  }
  var numspecs = _f4u$t.getnumspecs(dct);
  var id = _f4u$t.randString();
  var options = {
    label : dct["label"],
    min : numspecs["min"],
    max : numspecs["max"],
    step : numspecs["step"],
    init : numspecs["init"],
    integer : numspecs["integer"],
    ndec : numspecs["ndec"],
    address : hash+dct["address"],
    unit : _f4u$t.get_unit(dct),
    tooltip : _f4u$t.get_tooltip(dct)
  };
  options.id = id;

  var nentry = new _f4u$t.NumericalEntry(options);

  var vbox_options = $.extend(true, {}, _f4u$t.vbox_inits);
  vbox_options.init = numspecs["init"];
  vbox_options.id = id;
  var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
  lm_options.axis = _f4u$t.Y_AXIS;
  lm_options.stretchable = [false, false];

  /* make faust ui objects */
  var label = new _f4u$t.Label({label : _f4u$t.check_label(dct["label"]), id : id+"_label", mom : null});
  var vbox = new _f4u$t.ValueBox(vbox_options);

  var lm = new _f4u$t.LayoutManager(lm_options);
  lm.objs.push(label);
  lm.objs.push(nentry);
  lm.objs.push(vbox);

  return lm;
}

_f4u$t.make_hgroup = function(dct, hash) {
  return _f4u$t.make_group(_f4u$t.X_AXIS, dct, hash);
}

_f4u$t.make_vgroup = function(dct, hash) {
  return _f4u$t.make_group(_f4u$t.Y_AXIS, dct, hash);
}

_f4u$t.make_group = function(axis, dct, hash) {
  var internal_options = $.extend(true, {}, _f4u$t.xy(axis, _f4u$t.hgroup_inits, _f4u$t.vgroup_inits));
  internal_options.axis = axis;

  internal_options.draw_background = false;
  internal_options.other_axis_padding = 0;
  var id = _f4u$t.randString();
  internal_options.id = id;

  var internal_lm = new _f4u$t.LayoutManager(internal_options);

  for (var i = 0; i < dct["items"].length; i++) {
    if (dct["items"][i]["type"] == "hgroup") {
      internal_lm.objs.push(_f4u$t.make_hgroup(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "vgroup") {
      internal_lm.objs.push(_f4u$t.make_vgroup(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "tgroup") {
      internal_lm.objs.push(_f4u$t.make_tgroup(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "hslider") {
      internal_lm.objs.push(_f4u$t.make_hslider(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "vslider") {
      internal_lm.objs.push(_f4u$t.make_vslider(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "hbargraph") {
      internal_lm.objs.push(_f4u$t.make_hbargraph(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "vbargraph") {
      internal_lm.objs.push(_f4u$t.make_vbargraph(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "button") {
      internal_lm.objs.push(_f4u$t.make_button(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "checkbox") {
      internal_lm.objs.push(_f4u$t.make_checkbox(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "nentry") {
      internal_lm.objs.push(_f4u$t.make_nentry(dct["items"][i], hash));
    }
    else {
      console.log("UFO: Unidentified Faust Object");
    }
  }

  var label = new _f4u$t.Label({label : _f4u$t.check_label(dct["label"]), id : id+"_label", mom : null});

  var options = $.extend(true, {}, _f4u$t.vgroup_inits);
  // needed for tab group
  options.label = dct["label"];
  options.axis = _f4u$t.Y_AXIS;

  var lm = new _f4u$t.LayoutManager(options);
  lm.objs.push(label);
  lm.objs.push(internal_lm);
  return lm;
}

_f4u$t.make_tgroup = function(dct, hash) {
  var options = $.extend(true, {}, _f4u$t.tgroup_inits);
  var tg = new _f4u$t.TabGroup(options);

  for (var i = 0; i < dct["items"].length; i++) {
    if (dct["items"][i]["type"] == "hgroup") {
      tg.objs.push(_f4u$t.make_hgroup(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "vgroup") {
      tg.objs.push(_f4u$t.make_vgroup(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "tgroup") {
      tg.objs.push(_f4u$t.make_tgroup(dct["items"][i], hash));
    }
    else {
      console.log("UFO: Unidentified Faust Object");
    }
  }

  return tg;
}

_f4u$t.json_to_ui = function(json, hash) {
  if (json["ui"][0]["type"] == "vgroup") {
    return _f4u$t.make_vgroup(json["ui"][0], hash);
  }
  else if (json["ui"][0]["type"] == "hgroup") {
    return _f4u$t.make_hgroup(json["ui"][0], hash);
  }
  else if (json["ui"][0]["type"] == "tgroup") {
    return _f4u$t.make_tgroup(json["ui"][0], hash);
  }
  else {
    console.log("UFO: Unidentified Faust Object");
  }
}

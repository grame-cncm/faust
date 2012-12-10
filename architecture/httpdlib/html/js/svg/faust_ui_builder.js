_f4u$t.has_knob = function(dct) {
  if (!dct['meta']) {
    return false;
  }
  for (var i=0; i < dct['meta'].length; i++) {
    if (dct['meta'][i]['style']) {
      return dct['meta'][i]['style'] == 'knob';
    }
  }
  return false;
}

_f4u$t.get_unit = function(dct) {
  if (!dct['meta']) {
    return '';
  }
  for (var i=0; i < dct['meta'].length; i++) {
    if (dct['meta'][i]['unit']) {
      return dct['meta'][i]['unit'];
    }
  }
  return '';
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

  var maxsplit = dct["max"] ? dct["max"].split('.') : ['',''];
  var minsplit = dct["min"] ? dct["min"].split('.') : ['',''];
  var stepsplit = dct["step"] ? dct["step"].split('.') : ['',''];
  var initsplit = dct["init"] ? dct["init"].split('.') : ['',''];
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

_f4u$t.make_rbutton = function(dct) {
  var numspecs = _f4u$t.getnumspecs(dct);
  return new _f4u$t.RotatingButton({
    label : dct["label"],
    min : numspecs["min"],
    max : numspecs["max"],
    step : numspecs["step"],
    init : numspecs["init"],
    integer : numspecs["integer"],
    ndec : numspecs["ndec"],
    address : dct["address"],
    unit : _f4u$t.get_unit(dct)
  });
}

_f4u$t.make_hslider = function(dct) {
  return _f4u$t.make_slider(_f4u$t.HorizontalSlider, dct);
}

_f4u$t.make_vslider = function(dct) {
  return _f4u$t.make_slider(_f4u$t.VerticalSlider, dct);
}

_f4u$t.make_slider = function(kls, dct) {
  if (_f4u$t.has_knob(dct)) {
    return _f4u$t.make_rbutton(dct);
  }
  var numspecs = _f4u$t.getnumspecs(dct);
  var options = $.extend(true, {}, _f4u$t[kls == _f4u$t.HorizontalSlider ? 'hslider_inits' : 'vslider_inits']);
  options.label = dct["label"];
  options.min = numspecs["min"];
  options.max = numspecs["max"];
  options.step = numspecs["step"];
  options.init = numspecs["init"];
  options.integer = numspecs["integer"];
  options.ndec = numspecs["ndec"];
  options.address = dct["address"];
  options.unit = _f4u$t.get_unit(dct);
  return new kls(options);
}

_f4u$t.make_hbargraph = function(dct) {
  return _f4u$t.make_bargraph(_f4u$t.HorizontalBarGraph, dct);
}

_f4u$t.make_vbargraph = function(dct) {
  return _f4u$t.make_bargraph(_f4u$t.VerticalBarGraph, dct);
}

_f4u$t.make_bargraph = function(kls, dct) {
  var options = $.extend(true, {}, _f4u$t[kls == _f4u$t.HorizontalBarGraph ? 'hbargraph_inits' : 'vbargraph_inits']);
  //var numspecs = _f4u$t.getnumspecs(dct);
  options.label = dct["label"];
  options.min = parseFloat(dct["min"]);
  options.max = parseFloat(dct["max"]);
  options.address = dct["address"];
  options.unit = _f4u$t.get_unit(dct);
  return new kls(options);
}


_f4u$t.make_button = function(dct) {
  var options = $.extend(true, {}, _f4u$t.button_inits);
  options.label = dct.label;
  options.address = dct.address;
  return new _f4u$t.Button(options);
}

_f4u$t.make_checkbox = function(dct) {
  var options = $.extend(true, {}, _f4u$t.checkbox_inits);
  options.label  = dct.label;
  options.address = dct.address;
  options.init = (dct.init == "1" ? true : false);
  return new _f4u$t.CheckBox(options);
}

_f4u$t.make_nentry = function(dct) {
  if (_f4u$t.has_knob(dct)) {
    return _f4u$t.make_rbutton(dct);
  }
  var numspecs = _f4u$t.getnumspecs(dct);
  return new _f4u$t.NumericalEntry({
    label : dct["label"],
    min : numspecs["min"],
    max : numspecs["max"],
    step : numspecs["step"],
    init : numspecs["init"],
    integer : numspecs["integer"],
    ndec : numspecs["ndec"],
    address : dct["address"],
    unit : _f4u$t.get_unit(dct)
  });
}

_f4u$t.make_hgroup = function(dct) {
  return _f4u$t.make_group(_f4u$t.X_AXIS, dct);
}

_f4u$t.make_vgroup = function(dct) {
  return _f4u$t.make_group(_f4u$t.Y_AXIS, dct);
}

_f4u$t.make_group = function(axis, dct) {

  var lm = new _f4u$t.LayoutManager({
    axis : axis,
    label : dct["label"]
  });

  for (var i = 0; i < dct["items"].length; i++) {
    if (dct["items"][i]["type"] == "hgroup") {
      lm.objs.push(_f4u$t.make_hgroup(dct["items"][i]));
    }
    else if (dct["items"][i]["type"] == "vgroup") {
      lm.objs.push(_f4u$t.make_vgroup(dct["items"][i]));
    }
    else if (dct["items"][i]["type"] == "tgroup") {
      lm.objs.push(_f4u$t.make_tgroup(dct["items"][i]));
    }
    else if (dct["items"][i]["type"] == "hslider") {
      lm.objs.push(_f4u$t.make_hslider(dct["items"][i]));
    }
    else if (dct["items"][i]["type"] == "vslider") {
      lm.objs.push(_f4u$t.make_vslider(dct["items"][i]));
    }
    else if (dct["items"][i]["type"] == "hbargraph") {
      lm.objs.push(_f4u$t.make_hbargraph(dct["items"][i]));
    }
    else if (dct["items"][i]["type"] == "vbargraph") {
      lm.objs.push(_f4u$t.make_vbargraph(dct["items"][i]));
    }
    else if (dct["items"][i]["type"] == "button") {
      lm.objs.push(_f4u$t.make_button(dct["items"][i]));
    }
    else if (dct["items"][i]["type"] == "checkbox") {
      lm.objs.push(_f4u$t.make_checkbox(dct["items"][i]));
    }
    else if (dct["items"][i]["type"] == "nentry") {
      lm.objs.push(_f4u$t.make_nentry(dct["items"][i]));
    }
    else {
      console.log("UFO: Unidentified Faust Object");
    }
  }

  return lm;
}

_f4u$t.make_tgroup = function(dct) {
  var tg = new _f4u$t.TabGroup({});

  for (var i = 0; i < dct["items"].length; i++) {
    if (dct["items"][i]["type"] == "hgroup") {
      tg.objs.push(_f4u$t.make_hgroup(dct["items"][i]));
    }
    else if (dct["items"][i]["type"] == "vgroup") {
      tg.objs.push(_f4u$t.make_vgroup(dct["items"][i]));
    }
    else if (dct["items"][i]["type"] == "tgroup") {
      tg.objs.push(_f4u$t.make_tgroup(dct["items"][i]));
    }
    else {
      console.log("UFO: Unidentified Faust Object");
    }
  }

  return tg;
}

_f4u$t.json_to_ui = function(json) {
  if (json["ui"][0]["type"] == "vgroup") {
    return _f4u$t.make_vgroup(json["ui"][0]);
  }
  else if (json["ui"][0]["type"] == "hgroup") {
    return _f4u$t.make_hgroup(json["ui"][0]);
  }
  else if (json["ui"][0]["type"] == "tgroup") {
    return _f4u$t.make_tgroup(json["ui"][0]);
  }
  else {
    console.log("UFO: Unidentified Faust Object");
  }
}

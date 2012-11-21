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

_f4u$t.make_rbutton = function(dct) {
  return new _f4u$t.RotatingButton({
    label : dct["label"],
    mn : parseFloat(dct["min"]),
    mx : parseFloat(dct["max"]),
    step : parseFloat(dct["step"]),
    address : dct["address"],
    init : parseFloat(dct["init"]),
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
  return new kls({
    label : dct["label"],
    mn : parseFloat(dct["min"]),
    mx : parseFloat(dct["max"]),
    step : parseFloat(dct["step"]),
    address : dct["address"],
    init : parseFloat(dct["init"]),
    unit : _f4u$t.get_unit(dct)
  });
}

_f4u$t.make_hbargraph = function(dct) {
  return _f4u$t.make_bargraph(_f4u$t.HorizontalBarGraph, dct);
}

_f4u$t.make_vbargraph = function(dct) {
  return _f4u$t.make_bargraph(_f4u$t.VerticalBarGraph, dct);
}

_f4u$t.make_bargraph = function(kls, dct) {
  return new kls({
    label : dct["label"],
    mn : parseFloat(dct["min"]),
    mx : parseFloat(dct["max"]),
    address : dct["address"],
    unit : _f4u$t.get_unit(dct)
  });
}


_f4u$t.make_button = function(dct) {
  return new _f4u$t.Button({
    label : dct["label"],
    address : dct["address"]
  });
}

_f4u$t.make_checkbox = function(dct) {
  return new _f4u$t.CheckBox({
    label : dct["label"],
    address : dct["address"],
    init : (dct["init"] == "1" ? true : false)
  });
}

_f4u$t.make_nentry = function(dct) {
  if (_f4u$t.has_knob(dct)) {
    return _f4u$t.make_rbutton(dct);
  }
  return new _f4u$t.NumericalEntry({
    label : dct["label"],
    mn : parseFloat(dct["min"]),
    mx : parseFloat(dct["max"]),
    step : parseFloat(dct["step"]),
    address : dct["address"],
    init : parseFloat(dct["init"]),
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
    o : axis,
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

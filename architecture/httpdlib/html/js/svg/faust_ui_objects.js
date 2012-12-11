// all onload need to be pushed to the end of the creation

/*
  DEFINES THE FAUST OBJECT CLASS.
  All graphical objects inherit from this.
*/

_f4u$t.UIObject = function() {
  this.x = 0.0;
  this.y = 0.0;
}

_f4u$t.UIObject.prototype.make_group = function(svg, parent, id) {
  var out = svg.group(
    parent,
    id,
    {
      transform: 'translate('+this.x+','+this.y+')'
    });

  return out;
}

_f4u$t.UIObject.prototype.get_x_offset = function() {
  if (!this.mom) {
    return this.x;
  }
  return this.x + this.mom.get_x_offset();
}

_f4u$t.UIObject.prototype.get_y_offset = function() {
  if (!this.mom) {
    return this.y;
  }
  return this.y + this.mom.get_y_offset();
}

_f4u$t.UIObject.prototype.setX = function(x) {
  this.x = x
}

_f4u$t.UIObject.prototype.setY = function(y) {
  this.y = y
}

_f4u$t.UIObject.prototype.do_spacing = function() { }

_f4u$t.UIObject.prototype.get_root_svg = function() {
  if (!this.mom) {
    return null;
  }
  return (this.mom.svg ? this.mom.svg : this.mom.get_root_svg());
}

/*
  DEFINES THE FAUST INCREMENTAL OBJECT CLASS.
  All objects that go up in increments inherit from this.
*/

_f4u$t.IncrementalObject = function () {}
_f4u$t.extend(_f4u$t.UIObject, _f4u$t.IncrementalObject);

_f4u$t.IncrementalObject.prototype.make_value_box = function(svg, parent, id, mousedown) {
  var dims = this.dims();
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - this.value_box_w) / 2.0 : 0.0);
  var vb = svg.path(
    parent,
    "M0 0L"+this.value_box_w+" 0L"+this.value_box_w+" "+this.value_box_h+"L0 "+this.value_box_h+"L0 0",
    {
      id: 'faust_value_box_'+id,
      fill : _f4u$t.color_to_rgb(_f4u$t.WHITE),
      stroke : _f4u$t.color_to_rgb(_f4u$t.BLACK),
      transform: 'translate('+xo+','+(this.internal_dims()[1] + this.box_padding)+')',
      'class': 'faust-vbox',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );

  return vb;
}

_f4u$t.IncrementalObject.prototype.make_value_value = function(svg, parent, id, mousedown) {
  var dims = this.dims();
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] / 2.0) : this.box_padding);
  var mymousedown = (mousedown ? mousedown : '_f4u$t.devnull()');
  var vv = svg.text(
    parent,
    0,
    0,
    this.init.toString(),
    {
      id: 'faust_value_value_'+id,
      "text-anchor" : ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? 'middle' : 'left'),
      transform: 'translate('+xo+','+(this.internal_dims()[1] + this.lpadding_y)+')',
      onmousedown : mymousedown,
      ontouchstart : mymousedown
    }
  );
  return vv;
}

_f4u$t.IncrementalObject.prototype.label_text = function() {
  var label = this.label;
  if (this.unit) {
    label += ' ('+this.unit+')';
  }
  return label;
}
_f4u$t.IncrementalObject.prototype.make_label = function(svg, parent, id) {
  var dims = this.dims();
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? dims[0] / 2.0 : 0.0);
  var label = this.label_text();
  var vl = svg.text(
    parent,
    0,
    0,
    label,
    {
      id: 'faust_label_'+id,
      "text-anchor" : ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? 'middle' : 'left'),
      transform: 'translate('+xo+','+(this.internal_dims()[1] + this.lpadding_y + this.lpadding_y)+')'
    }
  );

  return vl;
}

/*
  DEFINES A ROTATING BUTTON.
*/

_f4u$t.RotatingButton = function(options) {
  this.mom = _f4u$t.initifnull(options.mom, null);
  this.ir = _f4u$t.initifnull(options.ir, 50);
  this.mr = _f4u$t.initifnull(options.mr, 25);
  this._r = this.ir;
  var a0 = _f4u$t.initifnull(options.a0, 180);
  var sweep = _f4u$t.initifnull(options.sweep, 180);
  if (sweep < 0) {
    a0 += sweep;
    sweep = Math.abs(sweep);
  }
  sweep = sweep % 360;
  if (sweep == 0) {
    sweep = 360;
  }
  this.a0 = a0;
  this.sweep = sweep;
  this.sp = _f4u$t.initifnull(options.sp, 0.1);
  this.label = _f4u$t.initifnull(options.label, '');
  this.unit = _f4u$t.initifnull(options.unit, null);
  this.min = _f4u$t.initifnull(options.min, 0);
  this.max = _f4u$t.initifnull(options.max, 100);
  this.init = _f4u$t.bound(_f4u$t.initifnull(options.init, 50), this.min, this.max);
  this.step = _f4u$t.initifnull(options.step, 1);
  this.integer = _f4u$t.initifnull(options.integer, false);
  this.ndec = _f4u$t.initifnull(options.ndec, 0);
  this.lpadding_y = _f4u$t.initifnull(options.lpadding_y, _f4u$t.TEXT_HEIGHT);
  this.box_padding = _f4u$t.initifnull(options.box_padding, _f4u$t.TEXT_BOX_PADDING);
  this.gravity = _f4u$t.initifnull(options.gravity, [_f4u$t.CENTER, _f4u$t.CENTER]);
  this.joint_fill= _f4u$t.initifnull(options.joint_fill, _f4u$t.PALEGREEN);
  this.knob_fill= _f4u$t.initifnull(options.knob_fill, _f4u$t.GREY);
  this.joint_stroke = _f4u$t.initifnull(options.joint_stroke, _f4u$t.BLACK);
  this.knob_stroke = _f4u$t.initifnull(options.knob_stroke, _f4u$t.BLACK);
  this.value_box_w = _f4u$t.initifnull(options.value_box_w, _f4u$t.VALUE_BOX_W);
  this.value_box_h = _f4u$t.initifnull(options.value_box_h, _f4u$t.VALUE_BOX_H);
  this.address = _f4u$t.initifnull(options.address, '');
}

_f4u$t.extend(_f4u$t.IncrementalObject, _f4u$t.RotatingButton);

_f4u$t.RotatingButton.prototype.r = function() {
  return this._r;
}

_f4u$t.RotatingButton.prototype.get_maybe_extremal_coords = function() {
  var angles = _f4u$t.find_all_90s(this.a0, this.sweep);
  angles.push(this.a0);
  angles.push(this.a0 + this.sweep);
  angles.sort();
  var coords = new Array();
  for (var i = 0; i < angles.length; i++) {
    coords.push(_f4u$t.point_from_polar(this.r(), _f4u$t.d2r(angles[i])));
  }
  coords.push([0,0]);
  return coords;
}

_f4u$t.RotatingButton.prototype.internal_dims = function() {
  var coords = this.get_maybe_extremal_coords();
  var box = new _f4u$t.Box();
  for (var i = 0; i < coords.length; i++) {
    box.add_point(coords[i]);
  }
  var ugh = box.lens();
  return ugh;
}

_f4u$t.RotatingButton.prototype.dims = function() {
  var ugh = this.internal_dims();
  var text_w = _f4u$t.get_text_bbox(this.get_root_svg(), this.label_text()).width;
  return [Math.max(ugh[0], this.value_box_w, text_w), ugh[1] + (2 * this.lpadding_y)];
}

_f4u$t.RotatingButton.prototype.get_translation = function() {
  var coords = this.get_maybe_extremal_coords();
  var x = Number.POSITIVE_INFINITY;
  var y = Number.POSITIVE_INFINITY;
  for (var i = 0; i < coords.length; i++) {
    x = Math.min(x, coords[i][0]);
    y = Math.min(x, coords[i][1]);
  }
  return [x,y];
}

_f4u$t.RotatingButton.prototype.make_joint = function(svg, parent, id) {
  var trans = this.get_translation()
  var start = _f4u$t.coord_sub(_f4u$t.point_from_polar(this.r(), _f4u$t.d2r(this.a0)), trans);
  var end = _f4u$t.coord_sub(_f4u$t.point_from_polar(this.r(), _f4u$t.d2r(this.a0 + this.sweep)), trans);
  var origin = _f4u$t.coord_sub([0,0], trans);
  var small = this.sweep < 180;
  var dims = this.dims();
  var xo = (dims[0] - (this.r() * 2)) / 2.0;
  var d = "M{0} {1}L{2} {3} A{4} {4} {5} 1 {6} {7}L{0} {1}";
  d = d.format([
    origin[0], origin[1],
    start[0], start[1],
    this.r(),
    (small ? "1 0" : "0 1"),
    end[0], end[1]
  ]);

  var joint = svg.path(
    parent,
    d,
    {
      fill : _f4u$t.color_to_rgb(this.joint_fill),
      stroke : _f4u$t.color_to_rgb(this.joint_stroke),
      id : 'faust_rbutton_joint_'+id,
      'class' : 'faust-rbutton-joint',
      transform : 'translate('+xo+',0)'
    }
  );

  return joint;
}

_f4u$t.RotatingButton.prototype.make_knob = function(svg, parent, id) {
  var trans = this.get_translation();
  var slider_angle = this.sweep * this.sp;
  var half_slider_angle = slider_angle * 0.5;
  var startp = _f4u$t.remap(this.init, this.min, this.max, this.a0 + half_slider_angle, this.a0 + this.sweep - half_slider_angle)
  var start = _f4u$t.coord_sub(_f4u$t.point_from_polar(this.r(), _f4u$t.d2r(this.a0)), trans);
  var end = _f4u$t.coord_sub(_f4u$t.point_from_polar(this.r(), _f4u$t.d2r(this.a0 + slider_angle)), trans);
  var origin = _f4u$t.coord_sub([0,0], trans);
  var small = this.sweep * this.sp < 180;
  var full_id = 'faust_rbutton_knob_'+id;
  var dims = this.dims();
  var xo = (dims[0] - (this.r() * 2)) / 2.0;
  var d = "M{0} {1}L{2} {3} A{4} {4} {5} 1 {6} {7}L{0} {1}";
  d = d.format([
    origin[0], origin[1],
    start[0], start[1],
    this.r(),
    (small ? "1 0" : "0 1"),
    end[0], end[1]
  ]);


  var mousedown = '_f4u$t.activate_rbutton("'+full_id+'")';
  var knob = svg.path(
    parent,
    d,
    {
      fill : _f4u$t.color_to_rgb(this.knob_fill),
      stroke : _f4u$t.color_to_rgb(this.knob_stroke),
      'class' : 'faust-rbutton-knob',
      id : full_id,
      transform : 'translate('+xo+',0) scale(1,1) rotate('+(startp - half_slider_angle + 180)+','+origin[0]+','+origin[1]+')',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );

  return knob;
}

_f4u$t.RotatingButton.prototype.make_anchor = function(svg, parent, id) {
  var trans = this.get_translation();
  var origin = _f4u$t.coord_sub([0,0], trans);
  var full_id = 'faust_rbutton_anchor_'+id;
  var dims = this.dims();
  var xo = (dims[0] - (this.r() * 2)) / 2.0;

  var anchor = svg.path(
    parent,
    "M 0 0L0 1L1 1L1 0L0 0",
    {
      id : full_id,
      style : 'opacity:0.0;',
      transform : 'translate('+(origin[0] + xo)+','+origin[1]+')',
    }
  );

  return anchor;
}

_f4u$t.RotatingButton.prototype.make = function(svg, parent) {
  var id = _f4u$t.randString();
  var g = this.make_group(svg, parent, id);
  var trans = this.get_translation();
  var origin = _f4u$t.coord_sub([0,0], trans);
  _f4u$t.initiate_rbutton(
    id,
    this.a0 + 180,
    this.sweep,
    this.sp,
    this.min,
    this.max,
    this.step,
    this.init,
    this.integer,
    this.ndec,
    this.label,
    this.address
  );

  this.make_anchor(svg, g, id);
  this.make_joint(svg, g, id);
  this.make_knob(svg, g, id);
  this.make_value_box(svg, g, id, '_f4u$t.rotating_button_key_sink("'+id+'")');
  this.make_value_value(svg, g, id, '_f4u$t.rotating_button_key_sink("'+id+'")');
  this.make_label(svg, g, id);

  return g;
}

/*
  DEFINES A SLIDER.
*/

_f4u$t.SlidingObject = function(options, type) {
  _f4u$t.init_prop(this, options, type, 'mom');
  _f4u$t.init_prop(this, options, type, 'axis');
  _f4u$t.init_prop(this, options, type, 'girth');
  _f4u$t.init_prop(this, options, type, 'length');
  _f4u$t.init_prop(this, options, type, 'label');
  _f4u$t.init_prop(this, options, type, 'unit');
  _f4u$t.init_prop(this, options, type, 'min');
  _f4u$t.init_prop(this, options, type, 'max');
  _f4u$t.init_prop(this, options, type, 'init');
  _f4u$t.init_prop(this, options, type, 'step');
  _f4u$t.init_prop(this, options, type, 'integer');
  _f4u$t.init_prop(this, options, type, 'ndec');
  _f4u$t.init_prop(this, options, type, 'lpadding_y');
  _f4u$t.init_prop(this, options, type, 'box_padding');
  _f4u$t.init_prop(this, options, type, 'gravity');
  _f4u$t.init_prop(this, options, type, 'value_box_w');
  _f4u$t.init_prop(this, options, type, 'value_box_h');
  _f4u$t.init_prop(this, options, type, 'address');
  _f4u$t.init_prop(this, options, type, 'type');
}

_f4u$t.extend(_f4u$t.IncrementalObject, _f4u$t.SlidingObject);

_f4u$t.SlidingObject.prototype.internal_dims = function() {
  var x = _f4u$t.xy(this.axis, this.length, this.girth);
  var y = _f4u$t.xy(this.axis, this.girth, this.length);
  return [x,y];
}

_f4u$t.SlidingObject.prototype.dims = function() {
  var ugh = this.internal_dims();
  var text_w = _f4u$t.get_text_bbox(this.get_root_svg(), this.label_text()).width;
  ugh = [Math.max(ugh[0], this.value_box_w, text_w), ugh[1] + (2 * this.lpadding_y)];
  return ugh;
}

_f4u$t.Slider = function(options, type) {
  _f4u$t.SlidingObject.call(this, options, type);
  _f4u$t.init_prop(this, options, 'button','sp');
  _f4u$t.init_prop(this, options, 'button','joint_fill');
  _f4u$t.init_prop(this, options, 'button','joint_stroke');
  _f4u$t.init_prop(this, options, 'button','knob_fill');
  _f4u$t.init_prop(this, options, 'button','knob_stroke');
}

_f4u$t.extend(_f4u$t.SlidingObject, _f4u$t.Slider);

_f4u$t.Slider.prototype.make_joint = function(svg, parent, id) {
  var dims = this.dims();
  var w = _f4u$t.xy(this.axis, this.length, this.girth / 3.0);
  var h = _f4u$t.xy(this.axis, this.girth / 3.0, this.length);
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var trans = _f4u$t.xy(this.axis, 'translate(0,'+(this.girth / 3.0)+')', 'translate('+xo+',0)');
  var joint = svg.path(
    parent,
    "M0 0L"+w+" 0L"+w+" "+h+"L0 "+h+"L0 0",
    {
      fill : _f4u$t.color_to_rgb(this.joint_fill),
      stroke : _f4u$t.color_to_rgb(this.joint_stroke),
      id : 'faust_'+this.type+'_joint_'+id,
      'class' : 'faust-slider-joint',
      transform : trans
    }
  );

  return joint;
}

_f4u$t.Slider.prototype.make_knob = function(svg, parent, id) {
  var dims = this.dims();
  var slider_girth = this.length  * this.sp;
  var half_slider_girth = slider_girth * 0.5;
  var startp = _f4u$t.xy(this.axis, _f4u$t.remap, _f4u$t.remap_and_flip)(this.init, this.min, this.max, 0 + half_slider_girth, this.length - half_slider_girth);
  var bottom = startp - half_slider_girth;
  var top = startp + half_slider_girth;
  var w = _f4u$t.xy(this.axis, slider_girth, this.girth);
  var h = _f4u$t.xy(this.axis, this.girth, slider_girth);
  var xo = ((this.axis == _f4u$t.Y_AXIS) ? (dims[0] - w) / 2.0 : 0.0);
  var x = _f4u$t.xy(this.axis, bottom, xo);
  var y = _f4u$t.xy(this.axis, 0, bottom);
  var full_id = 'faust_'+this.type+'_knob_'+id;
  var activate_fn = "activate_"+this.type;
  var mousedown = '_f4u$t["'+activate_fn+'"]("'+full_id+'")';

  var knob = svg.path(
    parent,
    "M0 0L"+w+" 0L"+w+" "+h+"L0 "+h+"L0 0",
    {
      fill : _f4u$t.color_to_rgb(this.knob_fill),
      stroke : _f4u$t.color_to_rgb(this.knob_stroke),
      id : full_id,
      'class' : 'faust-slider-knob',
      transform : 'translate('+x+','+y+')',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );

  return knob;
}

_f4u$t.Slider.prototype.make = function(svg, parent) {
  var id = _f4u$t.randString();
  var g = this.make_group(svg, parent, id);

  _f4u$t["initiate_"+this.type](
    id,
    this.length,
    this.sp,
    this.min,
    this.max,
    this.step,
    this.init,
    this.integer,
    this.ndec,
    this.label,
    this.address
  );

  this.make_joint(svg, g, id);
  this.make_knob(svg, g, id);
  this.make_value_box(
    svg,
    g,
    id,
    '_f4u$t["'+this.type+'_key_sink"]("'+id+'")'
  );
  this.make_value_value(
    svg,
    g,
    id,
    '_f4u$t["'+this.type+'_key_sink"]("'+id+'")'
  );
  this.make_label(svg, g, id);
  return g;
}

/*
  DEFINES A HORIZONTAL SLIDER.
*/

_f4u$t.HorizontalSlider = function(options) {
  options = options || {};
  options["axis"] = _f4u$t.X_AXIS;
  options["type"] = 'hslider';
  _f4u$t.Slider.call(this, options, options["type"]);
}

_f4u$t.extend(_f4u$t.Slider, _f4u$t.HorizontalSlider);

/*
  DEFINES A VERTICAL SLIDER.
*/

_f4u$t.VerticalSlider = function(options) {
  options = options || {};
  options["axis"] = _f4u$t.Y_AXIS;
  options["type"] = 'vslider';
  _f4u$t.Slider.call(this, options, options["type"]);
}

_f4u$t.extend(_f4u$t.Slider, _f4u$t.VerticalSlider);

_f4u$t.BarGraph = function(options, type) {
  _f4u$t.SlidingObject.call(this, options, type);
  this.joint_fill = _f4u$t.initifnull(options.joint_fill, _f4u$t.CYAN);
  this.joint_stroke = _f4u$t.initifnull(options.joint_stroke, _f4u$t.CYAN);
  this.meter_fill = _f4u$t.initifnull(options.meter_fill, _f4u$t.CYAN);
  this.meter_stroke = _f4u$t.initifnull(options.meter_stroke, _f4u$t.CYAN);
}

_f4u$t.extend(_f4u$t.SlidingObject, _f4u$t.BarGraph);

_f4u$t.BarGraph.prototype.make_joint = function(svg, parent, id) {
  var dims = this.dims();
  var w = _f4u$t.xy(this.axis, this.length, this.girth);
  var h = _f4u$t.xy(this.axis, this.girth, this.length);
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var joint = svg.path(
    parent,
    "M0 0L"+w+" 0L"+w+" "+h+"L0 "+h+"L0 0",
    {
      fill : _f4u$t.color_to_rgb(this.joint_fill),
      stroke : _f4u$t.color_to_rgb(this.joint_stroke),
      id : 'faust_'+this.type+'_joint_'+id,
      transform : 'translate('+xo+',0)',
      'class' : 'faust-bargraph-joint'
    }
  );

  return joint;
}

_f4u$t.BarGraph.prototype.make_meter = function(svg, parent, id) {
  var full_id = 'faust_'+this.type+'_meter_'+id;
  var def = _f4u$t.xy(this.axis, _f4u$t.remap, _f4u$t.remap_and_flip)(this.init, this.min, this.max, 0, this.length);
  var dims = this.dims();
  var w = _f4u$t.xy(this.axis, def, this.girth);
  var h = _f4u$t.xy(this.axis, this.girth, def);
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var meter = svg.path(
    parent,
    _f4u$t.xy(
      this.axis,
      "M0 0L"+w+" 0L"+w+" "+h+"L0 "+h+"L0 0",
      "M0 "+this.length+"L"+w+" "+this.length+"L"+w+" "+h+"L0 "+h+"L0 "+this.length
    ),
    {
      fill : _f4u$t.color_to_rgb(this.meter_fill),
      stroke : _f4u$t.color_to_rgb(this.meter_stroke),
      id : full_id,
      transform : 'translate('+xo+',0)',
      'class' : 'faust-bargraph-meter'
    }
  );

  return meter;
}

_f4u$t.BarGraph.prototype.make = function(svg, parent) {
  var id = _f4u$t.randString();
  var g = this.make_group(svg, parent, id);
  _f4u$t['initiate_'+this.type](
    id,
    this.girth,
    this.length,
    this.min,
    this.max,
    this.step,
    this.init,
    this.label,
    this.address
  );

  this.make_joint(svg, g, id);
  this.make_meter(svg, g, id);
  this.make_value_box(svg, g, id);
  this.make_value_value(svg, g, id);
  this.make_label(svg, g, id);

  return g;
}

/*
  DEFINES A HORIZONTAL BAR GRAPH.
*/

_f4u$t.HorizontalBarGraph = function(options) {
  options = options || {};
  options["axis"] = _f4u$t.X_AXIS;
  options["type"] = 'hbargraph';
  _f4u$t.BarGraph.call(this, options, options["type"]);
}

_f4u$t.extend(_f4u$t.BarGraph, _f4u$t.HorizontalBarGraph);

/*
  DEFINES A VERTICAL BAR GRAPH.
*/

_f4u$t.VerticalBarGraph = function(options) {
  options = options || {};
  options["axis"] = _f4u$t.Y_AXIS;
  options["type"] = 'vbargraph';
  _f4u$t.BarGraph.call(this, options, options["type"]);
}

_f4u$t.extend(_f4u$t.BarGraph, _f4u$t.VerticalBarGraph);

_f4u$t.CheckBox = function(options) {
  _f4u$t.init_prop(this, options, 'checkbox','mom');
  _f4u$t.init_prop(this, options, 'checkbox','d');
  _f4u$t.init_prop(this, options, 'checkbox','label');
  _f4u$t.init_prop(this, options, 'checkbox','gravity');
  _f4u$t.init_prop(this, options, 'checkbox','check_fill');
  _f4u$t.init_prop(this, options, 'checkbox','check_stroke');
  _f4u$t.init_prop(this, options, 'checkbox','box_fill');
  _f4u$t.init_prop(this, options, 'checkbox','box_stroke');
  _f4u$t.init_prop(this, options, 'checkbox','init');
  _f4u$t.init_prop(this, options, 'checkbox','lpadding_y');
  _f4u$t.init_prop(this, options, 'checkbox','box_padding');
  _f4u$t.init_prop(this, options, 'checkbox','address');
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.CheckBox);

_f4u$t.CheckBox.prototype.internal_dims = function() {
  return [this.d, this.d];
}

_f4u$t.CheckBox.prototype.dims = function() {
  var ugh = this.internal_dims();
  var text_w = _f4u$t.get_text_bbox(this.get_root_svg(), this.label).width;
  return [Math.max(ugh[0], text_w), ugh[1] + this.lpadding_y]
}

// DON'T FORGET TO SPECIFY CHECK IN CALLBACK
_f4u$t.CheckBox.prototype.make_box = function(svg, parent, id) {
  var full_id = 'faust_checkbox_box_'+id;
  var w = this.d;
  var h = this.d;
  var dims = this.dims();
  var xo = (dims[0] - w) / 2.0;
  var mousedown = '_f4u$t.change_checkbox("'+full_id+'")';

  var box = svg.path(
    parent,
    "M0 0L"+w+" 0L"+w+" "+h+"L0 "+h+"L0 0",
    {
      fill : _f4u$t.color_to_rgb(this.box_fill),
      stroke : _f4u$t.color_to_rgb(this.box_stroke),
      id : full_id,
      'class' : 'faust-checkbox-box',
      transform : 'translate('+xo+',0)',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );

  return box;
}

_f4u$t.CheckBox.prototype.make_check = function(svg, parent, id) {
  var full_id = 'faust_checkbox_check_'+id;
  var w = this.d;
  var h = this.d;
  var dims = this.dims();
  var xo = (dims[0] - w) / 2.0;
  var mousedown = '_f4u$t.change_checkbox("'+full_id+'")';
  var box = svg.path(
    parent,
    "M0 0L"+this.d+" "+this.d+"M0 "+this.d+"L"+this.d+" 0",
    {
      id : full_id,
      fill : _f4u$t.color_to_rgb(this.check_fill),
      stroke : _f4u$t.color_to_rgb(this.check_stroke),
      style : "opacity:"+(this.init == 1 ? 1.0 : 0.0),
      onmousedown : mousedown,
      ontouchstart : mousedown,
      transform : 'translate('+xo+',0)'
    }
  );

  return box;
}

_f4u$t.CheckBox.prototype.make_label = function(svg, parent, id) {
  var vl = svg.text(
    parent,
    0,
    0,
    this.label,
    {
      id: 'faust_label_'+id,
      transform: 'translate(0,'+(this.internal_dims()[1] + this.lpadding_y)+')'
    }
  );

  return vl;
}

_f4u$t.CheckBox.prototype.make = function(svg, parent) {
  var id = _f4u$t.randString();
  var g = this.make_group(svg, parent, id);
  _f4u$t.initiate_checkbox(id, this.address);

  this.make_box(svg, g, id);
  this.make_check(svg, g, id);
  this.make_label(svg, g, id);

  return g;
}

/*
  Button in
*/

_f4u$t.Button = function(options) {
  _f4u$t.init_prop(this, options, 'button','mom');
  _f4u$t.init_prop(this, options, 'button','label');
  _f4u$t.init_prop(this, options, 'button','ideal_width');
  _f4u$t.init_prop(this, options, 'button','ideal_height');
  this._w = this.ideal_width;
  this._h = this.ideal_height;
  _f4u$t.init_prop(this, options, 'button','gravity');
  _f4u$t.init_prop(this, options, 'button','fill_on');
  _f4u$t.init_prop(this, options, 'button','fill_off');
  _f4u$t.init_prop(this, options, 'button','stroke');
  _f4u$t.init_prop(this, options, 'button','baseline_skip');
  _f4u$t.init_prop(this, options, 'button','address');
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.Button);

_f4u$t.Button.prototype.w = function() {
  return Math.max(this._w,  _f4u$t.get_text_bbox(this.get_root_svg(), this.label).width + 6);
}

_f4u$t.Button.prototype.h = function() {
  return this._h;
}

_f4u$t.Button.prototype.dims = function(coef) {
  return [this.w(), this.h()];
}

_f4u$t.Button.prototype.make_button_box = function(svg, parent, id) {
  var full_id = 'faust_button_box_'+id;
  var rf = 10;
  var d = "M{0} 0L{1} 0C{2} 0 {2} 0 {2} {3}L{2} {4}C{2} {5} {2} {5} {1} {5}L{0} {5}C0 {5} 0 {5} 0 {4}L0 {3}C0 0 0 0 {0} 0";
  d = d.format([rf, this.w() - rf, this.w(), rf, this.h() - rf, this.h()]);
  var mousedown = '_f4u$t.button_down("'+full_id+'")';
  var mouseup = '_f4u$t.button_up("'+full_id+'")';

  var button = svg.path(
    parent,
    d,
    {
      id : full_id,
      fill : _f4u$t.color_to_rgb(this.fill_off),
      stroke : _f4u$t.color_to_rgb(this.stroke),
      'class' : 'faust-button-up',
      onmousedown : mousedown,
      ontouchstart : mousedown,
      onmouseup : mouseup,
      ontouchend : mouseup
    }
  );

  return button;
}

_f4u$t.Button.prototype.make_label = function(svg, parent, id) {
  var full_id = 'faust_button_box_'+id;
  var mousedown = '_f4u$t.button_down("'+full_id+'")';
  var mouseup = '_f4u$t.button_up("'+full_id+'")';
  var vl = svg.text(
    parent,
    0,
    0,
    this.label,
    {
      "text-anchor" : 'middle',
      id: 'faust_label_'+id,
      transform: 'translate('+(this.w() / 2.0)+','+(this.h() / 2.0 + this.baseline_skip)+')',
      onmousedown : mousedown,
      ontouchstart : mousedown,
      onmouseup : mouseup,
      ontouchend : mouseup
    }
  );

  return vl;
}

_f4u$t.Button.prototype.make = function(svg, parent) {
  var id = _f4u$t.randString();
  var g = this.make_group(svg, parent, id);
  _f4u$t.initiate_button(
    id,
    _f4u$t.color_to_rgb(this.fill_off),
    _f4u$t.color_to_rgb(this.fill_on),
    this.address
  );

  this.make_button_box(svg, g, id);
  this.make_label(svg, g, id);

  return g;
}

_f4u$t.NumericalEntry = function(options) {
  this.mom = _f4u$t.initifnull(options.mom, null);
  this.ideal_width = _f4u$t.initifnull(options.ideal_width, _f4u$t.VALUE_BOX_W);
  this.ideal_height = _f4u$t.initifnull(options.ideal_height, _f4u$t.VALUE_BOX_H);
  this._w = this.ideal_width;
  this._h = this.ideal_height;
  this.label = _f4u$t.initifnull(options.label, '');
  this.unit = _f4u$t.initifnull(options.unit, null);
  this.min = _f4u$t.initifnull(options.min, 0);
  this.max = _f4u$t.initifnull(options.max, 100);
  this.init = _f4u$t.bound(_f4u$t.initifnull(options.init, 50), this.min, this.max);
  this.step = _f4u$t.initifnull(options.step, 1);
  this.integer = _f4u$t.initifnull(options.integer, false);
  this.ndec = _f4u$t.initifnull(options.ndec, 0);
  this.button_fill= _f4u$t.initifnull(options.button_fill, _f4u$t.GREY);
  this.operation_fill= _f4u$t.initifnull(options.operation_fill, _f4u$t.BLACK);
  this.button_stroke = _f4u$t.initifnull(options.button_stroke, _f4u$t.BLACK);
  this.operation_stroke = _f4u$t.initifnull(options.operation_stroke, _f4u$t.BLACK);
  this.padding = _f4u$t.initifnull(options.padding, 1);
  this.lpadding_y = _f4u$t.initifnull(options.lpadding_y, _f4u$t.TEXT_HEIGHT);
  this.box_padding = _f4u$t.initifnull(options.box_padding, _f4u$t.TEXT_BOX_PADDING);
  this.gravity = _f4u$t.initifnull(options.gravity, [_f4u$t.CENTER, _f4u$t.CENTER]);
  this.value_box_w = _f4u$t.initifnull(options.value_box_w, _f4u$t.VALUE_BOX_W);
  this.value_box_h = _f4u$t.initifnull(options.value_box_h, _f4u$t.VALUE_BOX_H);
  this.address = _f4u$t.initifnull(options.address, '');
}

_f4u$t.extend(_f4u$t.IncrementalObject, _f4u$t.NumericalEntry);

_f4u$t.NumericalEntry.prototype.w = function() {
  return this._w;
}

_f4u$t.NumericalEntry.prototype.h = function() {
  return this._h;
}

_f4u$t.NumericalEntry.prototype.internal_dims = function() {
  return [this.w(), this.h()];
}

_f4u$t.NumericalEntry.prototype.dims = function() {
  var ugh = this.internal_dims();
  var text_w = _f4u$t.get_text_bbox(this.get_root_svg(), this.label_text()).width;
  ugh = [Math.max(ugh[0], this.value_box_w, text_w), ugh[1] + (2 * this.lpadding_y)];
  return ugh;
}

_f4u$t.NumericalEntry.prototype.make_left_button = function(svg, parent, id) {
  return this.make_button(svg, parent, id, 0, false);
}

_f4u$t.NumericalEntry.prototype.make_right_button = function(svg, parent, id) {
  return this.make_button(svg, parent, id, this.w() / 2.0 + this.padding, true);
}

_f4u$t.NumericalEntry.prototype.make_button = function(svg, parent, id, xo, incr) {
  var identifier = incr ? 'rbutton' : 'lbutton';
  var full_id = 'faust_nentry_'+identifier+'_'+id;
  var w = this.w() / 2.0 - this.padding;
  var h = this.h();

  var d = "M0 0L"+w+" 0L"+w+" "+h+"L0 "+h+"L0 0";
  var mousedown = '_f4u$t.activate_nentry("'+full_id+'", '+incr+')';
  var button = svg.path(
    parent,
    d,
    {
      
      fill : _f4u$t.color_to_rgb(this.button_fill),
      stroke : _f4u$t.color_to_rgb(this.button_stroke),
      transform : 'translate('+xo+',0)',
      id : full_id,
      'class' : 'faust-nentry-button',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );

  return button;
}

_f4u$t.NumericalEntry.prototype.make_minus = function(svg, parent, id) {
  var full_id = 'faust_nentry_minus_'+id;
  var x0 = (this.w() / 2.0 - this.padding) / 4.0;
  var y = this.h() / 2.0;
  var x1 = (this.w() / 2.0 - this.padding) * 3.0 / 4.0;
  var mousedown = '_f4u$t.activate_nentry("'+full_id+'", false)';

  var d = "M"+x0+" "+y+"L"+x1+" "+y;
  var minus = svg.path(
    parent,
    d,
    {
      fill : _f4u$t.color_to_rgb(this.operation_fill),
      stroke : _f4u$t.color_to_rgb(this.operation_stroke),
      id : full_id,
      'class' : 'faust-nentry-operation',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );

  return minus;
}

_f4u$t.NumericalEntry.prototype.make_plus = function(svg, parent, id) {
  var full_id = 'faust_nentry_plus_'+id;
  var x00 = (this.w() / 2.0 - this.padding) / 4.0;
  var y0 = this.h() / 2.0;
  var x01 = (this.w() / 2.0 - this.padding) * 3.0 / 4.0;
  var x1 = (this.w() / 2.0 - this.padding) / 2.0;
  var y10 = this.h() / 4.0;
  var y11 = this.h() * 3.0 / 4.0;

  var d = "M{0} {1}L{2} {1}M{3} {4}L{3} {5}";
  d = d.format([x00, y0, x01, x1, y10, y11]);
  var mousedown = '_f4u$t.activate_nentry("'+full_id+'", true)';
  var plus = svg.path(
    parent,
    d,
    {
      fill : _f4u$t.color_to_rgb(this.operation_fill),
      stroke : _f4u$t.color_to_rgb(this.operation_stroke),
      transform : 'translate('+(this.w() / 2.0 + this.padding)+',0)',
      id : full_id,
      'class' : 'faust-nentry-operation',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );

  return plus;
}

_f4u$t.NumericalEntry.prototype.make = function(svg, parent) {
  var id = _f4u$t.randString();
  var g = this.make_group(svg, parent, id);
  _f4u$t.initiate_nentry(
    id,
    this.min,
    this.max,
    this.step,
    this.init,
    this.integer,
    this.ndec,
    this.label,
    this.address
  );

  this.make_left_button(svg, g, id);
  this.make_right_button(svg, g, id);
  this.make_minus(svg, g, id);
  this.make_plus(svg, g, id);
  this.make_value_box(svg, g, id, '_f4u$t.nentry_key_sink("'+id+'")');
  this.make_value_value(svg, g, id, '_f4u$t.nentry_key_sink("'+id+'")');
  this.make_label(svg, g, id);

  return g;
}

_f4u$t.LayoutManager = function(options) {
  this.mom = _f4u$t.initifnull(options.mom, null);
  this.axis = _f4u$t.initifnull(options.axis, _f4u$t.X_AXIS);
  this.padding = _f4u$t.initifnull(options.padding, 10);
  this.objs = _f4u$t.initifnull(options.objs, []);
  this.gravity = _f4u$t.initifnull(options.gravity, [_f4u$t.CENTER, _f4u$t.CENTER]);
  this.label = _f4u$t.initifnull(options.label, '');
  this.lpadding_y = _f4u$t.initifnull(options.lpaddiny_y, (_f4u$t.TEXT_HEIGHT * 1.5));
  this.box_padding = _f4u$t.initifnull(options.box_padding, _f4u$t.TEXT_BOX_PADDING);
  this.x = 0;
  this.y = 0;
  this.w = 0;
  this.h = 0;
  this.id = _f4u$t.randString();
  this.fill = _f4u$t.magic_color();
  this.stroke = _f4u$t.initifnull(options.stroke, _f4u$t.BLACK);
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.LayoutManager);

_f4u$t.LayoutManager.prototype.internal_dims = function() {
  var outx = [];
  var outy = [];
  for (var i = 0; i < this.objs.length; i++) {
    var dim = this.objs[i].dims();
    outx.push(dim[_f4u$t.X_AXIS]);
    outy.push(dim[_f4u$t.Y_AXIS]);
  }

  var out = [outx,outy];

  for (var i = _f4u$t.X_AXIS; i < _f4u$t.NO_AXES; i++) {
    out[i] = (i == this.axis ? out[i].sum() : out[i].max());
  }

  out[this.axis] += (this.padding * (this.objs.length - 1));
  return out;
}

_f4u$t.LayoutManager.prototype.populate_objects = function() {
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].mom = this;
    if ((this.objs[i] instanceof _f4u$t.LayoutManager)
        || (this.objs[i] instanceof _f4u$t.TabGroup)) {
      this.objs[i].populate_objects();
    }
  }
}

_f4u$t.LayoutManager.prototype.dims = function() {
  var ugh = this.internal_dims();
  var text_w = _f4u$t.get_text_bbox(this.get_root_svg(), this.label).width;
  var out = [Math.max(ugh[0], text_w) + (2 * this.padding), ugh[1] + Math.max(this.lpadding_y, this.padding) + this.padding];
  return out;
}

_f4u$t.LayoutManager.prototype.do_spacing = function() {
  var dims = this.dims();
  var x = dims[_f4u$t.X_AXIS];
  var y = dims[_f4u$t.Y_AXIS];
  this.w = x;
  this.h = y;
  // increase padding by size
  var padding = this.padding;
  // the first padding will need to account for any additional space, thus
  // use this.gravity, as object gravities will be used internally
  var running_count = padding;
  for (var i = 0; i < this.objs.length; i++) {
    var obj = this.objs[i];
    var dim = obj.dims();
    var xv1 = _f4u$t.xy(this.axis, running_count, 0);
    var xv2 = _f4u$t.xy(this.axis, running_count, x - dim[_f4u$t.X_AXIS]);
    obj.setX(_f4u$t.linear_combination(obj.gravity[_f4u$t.X_AXIS], xv1, xv2));
    var yv1 = _f4u$t.xy(this.axis, 0, running_count);
    var yv2 = _f4u$t.xy(this.axis, y - dim[_f4u$t.Y_AXIS], running_count);
    obj.setY(_f4u$t.linear_combination(obj.gravity[_f4u$t.Y_AXIS], yv1, yv2));
    obj.do_spacing();
    running_count += padding + _f4u$t.xy(this.axis, dim[_f4u$t.X_AXIS], dim[_f4u$t.Y_AXIS]);
  }
}

_f4u$t.LayoutManager.prototype.make_label = function(svg, parent) {
  var full_id = 'faust_label_'+this.id;
  var vl = svg.text(
    parent,
    0,
    0,
    this.label,
    {
      id : full_id,
      transform: 'translate(2,'+(this.dims()[1] - 3)+')'
    }
  );

  return vl;
}

_f4u$t.LayoutManager.prototype.make_background = function(svg, parent) {
  var full_id = 'faust_background_'+this.id;
  var dims = this.dims();
  var w = dims[0];
  var h = dims[1];
  var d = "M0 0L"+w+" 0L"+w+" "+h+"L0 "+h+"L0 0";
  var background = svg.path(
    parent,
    d,
    {
      fill : _f4u$t.color_to_rgb(this.fill),
      stroke : _f4u$t.color_to_rgb(this.stroke),
      id : full_id,
      style: +'fill-opacity:0.2;'
    }
  );

  return background;
}

// only for debugging
_f4u$t.LayoutManager.prototype.make_dim_cross = function(svg, parent) {
  var dims = this.dims();
  svg.path(
    parent,
    "M0 0L"+dims[0]+' '+dims[1]
  );

  //return background;
}

_f4u$t.LayoutManager.prototype.make = function(svg, parent) {
  var g = this.make_group(svg, parent, this.id);

  this.make_background(svg, g);
  this.make_label(svg, g);

  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].make(svg, g);
  }

  //this.make_dim_cross(svg, g);
  return g;
}

_f4u$t.TabGroup = function(options) {
  this.mom = _f4u$t.initifnull(options.mom, null);
  this.headroom = _f4u$t.initifnull(options.headroom, 40);
  this.headpadding = _f4u$t.initifnull(options.headroom, 10);
  this.x_padding = _f4u$t.initifnull(options.x_padding, 10);
  this.x_width = _f4u$t.initifnull(options.x_width, 80);
  this.objs= _f4u$t.initifnull(options.objs, []);
  this.init = _f4u$t.initifnull(options.init, 0);
  this.gravity = _f4u$t.initifnull(options.gravity, [_f4u$t.CENTER, _f4u$t.CENTER]);
  this.baseline_skip = _f4u$t.initifnull(options.baseline_skip, 5);
  this.x = 0;
  this.y = 0;
  this.id = _f4u$t.randString();
  this.stroke = _f4u$t.initifnull(options.stroke, _f4u$t.BLACK);
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.TabGroup);

_f4u$t.TabGroup.prototype.setX = function(x) {
  this.x = x;
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].x = x;
  }
}

_f4u$t.TabGroup.prototype.setY = function(y) {
  this.y = y;
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].y = y + this.headroom + this.headpadding;
  }
}

_f4u$t.TabGroup.prototype.populate_objects = function() {
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].mom = this;
    if ((this.objs[i] instanceof _f4u$t.LayoutManager)
        || (this.objs[i] instanceof _f4u$t.TabGroup)) {
      this.objs[i].populate_objects();
    }
  }
}

_f4u$t.TabGroup.prototype.dims = function() {
  var x = 0;
  var y = 0;
  for (var i = 0; i < this.objs.length; i++) {
    var dim = this.objs[i].dims();
    x = Math.max(x, dim[0]);
    y = Math.max(y, dim[1]);
  }
  return [Math.max(x, (this.x_width + this.x_padding) * this.objs.length - this.x_padding), y + this.headroom + this.headpadding];
}

_f4u$t.TabGroup.prototype.do_spacing = function() {
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].x = 0;
    this.objs[i].y = this.headroom + this.headpadding;
    this.objs[i].do_spacing();
  }
}

_f4u$t.TabGroup.prototype.make_label = function(svg, parent, x, y, l, goodid, badidstr) {
  var mousedown = '_f4u$t.activate_tgroup(0,'+(this.headroom + this.headpadding)+',"'+goodid+'","'+badidstr+'")'
  var vl = svg.text(
    parent,
    0,
    0,
    l,
    {
      "text-anchor" : 'middle',
      transform : 'translate('+x+','+y+')',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );

  return vl;
}

_f4u$t.TabGroup.prototype.make_tab = function(svg, parent, w, h, x, y, goodid, badidstr, fill) {
  var mousedown = '_f4u$t.activate_tgroup(0,'+(this.headroom + this.headpadding)+',"'+goodid+'","'+badidstr+'")';
  var tab = svg.path(
    parent,
    "M 0 0L"+w+" 0L"+w+" "+h+"L0 "+h+"L0 0",
    {
      transform: 'translate('+x+','+y+')',
      fill : _f4u$t.color_to_rgb(fill),
      stroke : _f4u$t.color_to_rgb(this.stroke),
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );

  return tab;
}

_f4u$t.TabGroup.prototype.make_tabs = function(svg, parent) {
  // we evenly space buttons across x axis
  var g = svg.group('faust_tabgroup_tabbar_'+this.id, parent);

  var running_count = 0;
  for (var i = 0; i < this.objs.length; i++) {
    var curobj = this.objs[i];
    var badidstr = this.objs.filter(function(obj) {return obj != curobj}).map(function(obj) {return obj.id;}).join('#');
    this.make_tab(
      svg,
      parent,
      this.x_width,
      this.headroom,
      running_count,
      0,
      curobj.id,
      badidstr,
      curobj.fill);
    this.make_label(
      svg,
      parent,
      running_count + this.x_width / 2.0,
      this.headroom / 2.0 + this.baseline_skip,
      curobj.label,
      curobj.id,
      badidstr);
    running_count += this.x_width + this.x_padding;
  }

  return g;
}

_f4u$t.TabGroup.prototype.make = function(svg, parent) {
  var g = this.make_group(svg, parent, this.id);
  this.make_tabs(svg, g);
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].make(svg, g);
  }
  // call initiate_tab_group after objects are created
  _f4u$t.initiate_tab_group(this.init, this.objs.map(function(obj) {return obj.id;}).join('#'));

  return g;
}

// rather than extending the jQuery svg object, we just create a wrapper around it
_f4u$t.SVG = function(svg, w, h, options) {
  this.svg = svg;
  this.w = w;
  this.h = h;
  this.lm = _f4u$t.initifnull(options.lm, null);
  this.title = _f4u$t.initifnull(options.title, '');
  this.lm.mom = this;
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.SVG);

_f4u$t.SVG.prototype.get_x_offset = function() {
  return 0;
}

_f4u$t.SVG.prototype.get_y_offset = function() {
  return 0;
}

_f4u$t.SVG.prototype.make = function() {
  this.svg.configure(
    {
      width : this.w+'px',
      height : this.h+'px'
    },
    true);
  _f4u$t.ROOT = this.title;
  this.lm.populate_objects();
  this.lm.do_spacing();
  this.lm.make(this.svg, this.svg);
  // if there is no constrain, the viewport needs to be scaled
  var viewport_dims = this.lm.dims();
  this.svg.configure(
    {
      viewBox: '0 0 '+viewport_dims[0]+' '+viewport_dims[1],
      width : this.w+'px',
      height: this.h+'px',
    },
    true);

  _f4u$t.VIEWPORT_SCALE = Math.min(this.w/viewport_dims[0], this.h/viewport_dims[1]);
}

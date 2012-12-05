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

_f4u$t.UIObject.prototype.compress = function() {
  // does nothing
}

/*
  DEFINES THE FAUST INCREMENTAL OBJECT CLASS.
  All objects that go up in increments inherit from this.
*/

_f4u$t.IncrementalObject = function () {}
_f4u$t.extend(_f4u$t.UIObject, _f4u$t.IncrementalObject);

_f4u$t.IncrementalObject.prototype.make_value_box = function(svg, parent, id, mousedown) {
  var dims = this.dims();
  var xo = ((this.o == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - this.value_box_w) / 2.0 : 0.0);
  var vb = svg.path(
    parent,
    "M0 0L"+this.value_box_w+" 0L"+this.value_box_w+" "+this.value_box_h+"L0 "+this.value_box_h+"L0 0",
    {
      id: 'faust_value_box_'+id,
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
  var xo = ((this.o == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] / 2.0) : this.box_padding);
  var mymousedown = (mousedown ? mousedown : '_f4u$t.devnull()');
  var vv = svg.text(
    parent,
    0,
    0,
    this.init.toString(),
    {
      id: 'faust_value_value_'+id,
      "text-anchor" : ((this.o == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? 'middle' : 'left'),
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
  var xo = ((this.o == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? dims[0] / 2.0 : 0.0);
  var label = this.label_text();
  var vl = svg.text(
    parent,
    0,
    0,
    label,
    {
      id: 'faust_label_'+id,
      "text-anchor" : ((this.o == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? 'middle' : 'left'),
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
  this.mn = _f4u$t.initifnull(options.mn, 0);
  this.mx = _f4u$t.initifnull(options.mx, 100);
  this.init = _f4u$t.bound(_f4u$t.initifnull(options.init, 50), this.mn, this.mx);
  this.step = _f4u$t.initifnull(options.step, 1);
  this.integer = _f4u$t.initifnull(options.integer, false);
  this.ndec = _f4u$t.initifnull(options.ndec, 0);
  this.lpadding_y = _f4u$t.initifnull(options.lpadding_y, _f4u$t.TEXT_HEIGHT);
  this.box_padding = _f4u$t.initifnull(options.box_padding, _f4u$t.TEXT_BOX_PADDING);
  this.gravity = _f4u$t.initifnull(options.gravity, [_f4u$t.CENTER, _f4u$t.CENTER]);
  //this.fill= _f4u$t.initifnull(options.fill, _f4u$t.PALEGREEN);
  this.value_box_w = _f4u$t.initifnull(options.value_box_w, _f4u$t.VALUE_BOX_W);
  this.value_box_h = _f4u$t.initifnull(options.value_box_h, _f4u$t.VALUE_BOX_H);
  this.address = _f4u$t.initifnull(options.address, '');
}

_f4u$t.extend(_f4u$t.IncrementalObject, _f4u$t.RotatingButton);

_f4u$t.RotatingButton.prototype.compress = function(coef) {
  this._r = Math.max(this.mr, this._r * coef);
}

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
  var startp = _f4u$t.remap(this.init, this.mn, this.mx, this.a0 + half_slider_angle, this.a0 + this.sweep - half_slider_angle)
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
    this.mn,
    this.mx,
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

_f4u$t.SlidingObject = function(options) {
  this.mom = _f4u$t.initifnull(options.mom, null);
  this.o = _f4u$t.initifnull(options.o, _f4u$t.X_AXIS);
  this.iwa = _f4u$t.initifnull(options.iwa, 40);
  this.isa = _f4u$t.initifnull(options.isa, 200);
  this._sa = this.isa;
  this._wa = this.iwa;
  this.mwa = _f4u$t.initifnull(options.mwa, 20);
  this.msa = _f4u$t.initifnull(options.msa, 100);
  this.label = _f4u$t.initifnull(options.label, '');
  this.unit = _f4u$t.initifnull(options.unit, null);
  this.mn = _f4u$t.initifnull(options.mn, 0);
  this.mx = _f4u$t.initifnull(options.mx, 100);
  this.init = _f4u$t.bound(_f4u$t.initifnull(options.init, 50), this.mn, this.mx);
  this.step = _f4u$t.initifnull(options.step, 1);
  this.integer = _f4u$t.initifnull(options.integer, false);
  this.ndec = _f4u$t.initifnull(options.ndec, 0);
  this.lpadding_y = _f4u$t.initifnull(options.lpadding_y, _f4u$t.TEXT_HEIGHT);
  this.box_padding = _f4u$t.initifnull(options.box_padding, _f4u$t.TEXT_BOX_PADDING);
  this.gravity = _f4u$t.initifnull(options.gravity, [_f4u$t.CENTER, _f4u$t.CENTER]);
  this.value_box_w = _f4u$t.initifnull(options.value_box_w, _f4u$t.VALUE_BOX_W);
  this.value_box_h = _f4u$t.initifnull(options.value_box_h, _f4u$t.VALUE_BOX_H);
  this.address = _f4u$t.initifnull(options.address, '');
  this.type = _f4u$t.initifnull(options.type, '');
}

_f4u$t.extend(_f4u$t.IncrementalObject, _f4u$t.SlidingObject);

_f4u$t.SlidingObject.prototype.compress = function(coef) {
  this._wa = Math.max(this.mwa, this._wa * coef);
  this._sa = Math.max(this.msa, this._sa * coef);
}

_f4u$t.SlidingObject.prototype.wa = function() {
  return this._wa;
}

_f4u$t.SlidingObject.prototype.sa = function() {
  return this._sa;
}

_f4u$t.SlidingObject.prototype.internal_dims = function() {
  var x = _f4u$t.xy(this.o, this.sa(), this.wa());
  var y = _f4u$t.xy(this.o, this.wa(), this.sa());
  return [x,y];
}

_f4u$t.SlidingObject.prototype.dims = function() {
  var ugh = this.internal_dims();
  var text_w = _f4u$t.get_text_bbox(this.get_root_svg(), this.label_text()).width;
  ugh = [Math.max(ugh[0], this.value_box_w, text_w), ugh[1] + (2 * this.lpadding_y)];
  return ugh;
}

_f4u$t.Slider = function(options) {
  _f4u$t.SlidingObject.call(this, options);
  this.sp = _f4u$t.initifnull(options.sp, 0.15);
  //this.fill = _f4u$t.initifnull(options.fill, _f4u$t.PINK);
}

_f4u$t.extend(_f4u$t.SlidingObject, _f4u$t.Slider);

_f4u$t.Slider.prototype.make_joint = function(svg, parent, id) {
  var dims = this.dims();
  var w = _f4u$t.xy(this.o, this.sa(), this.wa() / 3.0);
  var h = _f4u$t.xy(this.o, this.wa() / 3.0, this.sa());
  var xo = ((this.o == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var trans = _f4u$t.xy(this.o, 'translate(0,'+(this.wa() / 3.0)+')', 'translate('+xo+',0)');
  var joint = svg.path(
    parent,
    "M0 0L"+w+" 0L"+w+" "+h+"L0 "+h+"L0 0",
    {
      id : 'faust_'+this.type+'_joint_'+id,
      'class' : 'faust-slider-joint',
      transform : trans
    }
  );

  return joint;
}

_f4u$t.Slider.prototype.make_knob = function(svg, parent, id) {
  var dims = this.dims();
  var slider_girth = this.sa()  * this.sp;
  var half_slider_girth = slider_girth * 0.5;
  var startp = _f4u$t.xy(this.o, _f4u$t.remap, _f4u$t.remap_and_flip)(this.init, this.mn, this.mx, 0 + half_slider_girth, this.sa() - half_slider_girth);
  var bottom = startp - half_slider_girth;
  var top = startp + half_slider_girth;
  var w = _f4u$t.xy(this.o, slider_girth, this.wa());
  var h = _f4u$t.xy(this.o, this.wa(), slider_girth);
  var xo = ((this.o == _f4u$t.Y_AXIS) ? (dims[0] - w) / 2.0 : 0.0);
  var x = _f4u$t.xy(this.o, bottom, xo);
  var y = _f4u$t.xy(this.o, 0, bottom);
  var full_id = 'faust_'+this.type+'_knob_'+id;
  var activate_fn = "activate_"+this.type;
  var mousedown = '_f4u$t["'+activate_fn+'"]("'+full_id+'")';

  var knob = svg.path(
    parent,
    "M0 0L"+w+" 0L"+w+" "+h+"L0 "+h+"L0 0",
    {
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
    this.sa(),
    this.sp,
    this.mn,
    this.mx,
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
  options["o"] = _f4u$t.X_AXIS;
  options["type"] = 'hslider';
  _f4u$t.Slider.call(this, options);
}

_f4u$t.extend(_f4u$t.Slider, _f4u$t.HorizontalSlider);

/*
  DEFINES A VERTICAL SLIDER.
*/

_f4u$t.VerticalSlider = function(options) {
  options = options || {};
  options["o"] = _f4u$t.Y_AXIS;
  options["type"] = 'vslider';
  _f4u$t.Slider.call(this, options);
}

_f4u$t.extend(_f4u$t.Slider, _f4u$t.VerticalSlider);

_f4u$t.BarGraph = function(options) {
  _f4u$t.SlidingObject.call(this, options);
  //this.fill = _f4u$t.initifnull(options.fill, _f4u$t.CYAN);
}

_f4u$t.extend(_f4u$t.SlidingObject, _f4u$t.BarGraph);

_f4u$t.BarGraph.prototype.make_joint = function(svg, parent, id) {
  var dims = this.dims();
  var w = _f4u$t.xy(this.o, this.sa(), this.wa());
  var h = _f4u$t.xy(this.o, this.wa(), this.sa());
  var xo = ((this.o == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var joint = svg.path(
    parent,
    "M0 0L"+w+" 0L"+w+" "+h+"L0 "+h+"L0 0",
    {
      id : 'faust_'+this.type+'_joint_'+id,
      transform : 'translate('+xo+',0)',
      'class' : 'faust-bargraph-joint'
    }
  );

  return joint;
}

_f4u$t.BarGraph.prototype.make_meter = function(svg, parent, id) {
  var full_id = 'faust_'+this.type+'_meter_'+id;
  var def = _f4u$t.xy(this.o, _f4u$t.remap, _f4u$t.remap_and_flip)(this.init, this.mn, this.mx, 0, this.sa());
  var dims = this.dims();
  var w = _f4u$t.xy(this.o, def, this.wa());
  var h = _f4u$t.xy(this.o, this.wa(), def);
  var xo = ((this.o == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var meter = svg.path(
    parent,
    _f4u$t.xy(
      this.o,
      "M0 0L"+w+" 0L"+w+" "+h+"L0 "+h+"L0 0",
      "M0 "+this.sa()+"L"+w+" "+this.sa()+"L"+w+" "+h+"L0 "+h+"L0 "+this.sa()
    ),
    {
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
    this.wa(),
    this.sa(),
    this.mn,
    this.mx,
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
  options["o"] = _f4u$t.X_AXIS;
  options["type"] = 'hbargraph';
  _f4u$t.BarGraph.call(this, options);
}

_f4u$t.extend(_f4u$t.BarGraph, _f4u$t.HorizontalBarGraph);

/*
  DEFINES A VERTICAL BAR GRAPH.
*/

_f4u$t.VerticalBarGraph = function(options) {
  options = options || {};
  options["o"] = _f4u$t.Y_AXIS;
  options["type"] = 'vbargraph';
  _f4u$t.BarGraph.call(this, options);
}

_f4u$t.extend(_f4u$t.BarGraph, _f4u$t.VerticalBarGraph);

_f4u$t.CheckBox = function(options) {
  this.mom = _f4u$t.initifnull(options.mom, null);
  this.d = _f4u$t.initifnull(options.d, 19);
  this.label = _f4u$t.initifnull(options.label, '');
  this.gravity = _f4u$t.initifnull(options.gravity, [_f4u$t.CENTER, _f4u$t.CENTER]);
  //this.fill = _f4u$t.initifnull(options.fill, _f4u$t.PINK);
  this.init = _f4u$t.initifnull(options.init, false);
  this.lpadding_y = _f4u$t.initifnull(options.lpadding_y, _f4u$t.TEXT_HEIGHT);
  this.box_padding = _f4u$t.initifnull(options.box_padding, _f4u$t.TEXT_BOX_PADDING);
  this.address = _f4u$t.initifnull(options.address, '');
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.CheckBox);

_f4u$t.CheckBox.prototype.compress = function() {}

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
      // CSS here instead of in style sheet becasue it only has relevence
      // in terms of UI
      style : "opacity:"+(this.init == 1 ? 1.0 : 0.0)+";stroke:black;fill:black;",
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
  this.mom = _f4u$t.initifnull(options.mom, null);
  this.label = _f4u$t.initifnull(options.label, '');
  this.mw = _f4u$t.initifnull(options.mw, 40);
  this.mh = _f4u$t.initifnull(options.mh, 20);
  this.iw = _f4u$t.initifnull(options.iw, 80, this.mw);
  this.ih = _f4u$t.initifnull(options.ih, 40);
  this._w = this.iw;
  this._h = this.ih;
  this.gravity = _f4u$t.initifnull(options.gravity, [_f4u$t.CENTER, _f4u$t.CENTER]);
  //this.fillOn = _f4u$t.initifnull(options.fillOn, _f4u$t.PINK;
  //this.fillOff = _f4u$t.initifnull(options.fillOff, _f4u$t.GREEN;
  this.baselineSkip = _f4u$t.initifnull(options.baselineSkip, 5);
  this.address = _f4u$t.initifnull(options.address, '');
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.Button);

_f4u$t.Button.prototype.w = function() {
  return Math.max(this._w,  _f4u$t.get_text_bbox(this.get_root_svg(), this.label).width + 6);
}

_f4u$t.Button.prototype.h = function() {
  return this._h;
}

_f4u$t.Button.prototype.compress = function(coef) {
  this._w = Math.max(this.mw, this._w * coef);
  this._h = Math.max(this.mh, this._h * coef);
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
      transform: 'translate('+(this.w() / 2.0)+','+(this.h() / 2.0 + this.baselineSkip)+')',
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
    _f4u$t.color_to_rgb(this.fillOff),
    _f4u$t.color_to_rgb(this.fillOn),
    this.address
  );

  this.make_button_box(svg, g, id);
  this.make_label(svg, g, id);

  return g;
}

_f4u$t.NumericalEntry = function(options) {
  this.mom = _f4u$t.initifnull(options.mom, null);
  this.iw = _f4u$t.initifnull(options.iw, _f4u$t.VALUE_BOX_W);
  this.ih = _f4u$t.initifnull(options.ih, _f4u$t.VALUE_BOX_H);
  this.mw = _f4u$t.initifnull(options.mw, _f4u$t.VALUE_BOX_W);
  this.mh = _f4u$t.initifnull(options.mh, _f4u$t.VALUE_BOX_H);
  this._w = this.iw;
  this._h = this.ih;
  this.label = _f4u$t.initifnull(options.label, '');
  this.unit = _f4u$t.initifnull(options.unit, null);
  this.mn = _f4u$t.initifnull(options.mn, 0);
  this.mx = _f4u$t.initifnull(options.mx, 100);
  this.init = _f4u$t.bound(_f4u$t.initifnull(options.init, 50), this.mn, this.mx);
  this.step = _f4u$t.initifnull(options.step, 1);
  this.integer = _f4u$t.initifnull(options.integer, false);
  this.ndec = _f4u$t.initifnull(options.ndec, 0);
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

_f4u$t.NumericalEntry.prototype.compress = function(coef) {
  this._w = Math.max(this.mw, this._w * coef);
  this._h = Math.max(this.mh, this._h * coef);
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
    this.mn,
    this.mx,
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
  this.o = _f4u$t.initifnull(options.o, _f4u$t.X_AXIS);
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
    out[i] = (i == this.o ? out[i].sum() : out[i].max());
  }

  //out[_f4u$t.other_axis(this.o)] += this.padding * 2;
  //out[this.o] += this.padding * (this.objs.length + 1);
  out[this.o] += (this.padding * (this.objs.length - 1));
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

_f4u$t.LayoutManager.prototype.compress = function(coef) {
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].compress(coef);
  }
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
    var xv1 = _f4u$t.xy(this.o, running_count, 0);
    var xv2 = _f4u$t.xy(this.o, running_count, x - dim[_f4u$t.X_AXIS]);
    obj.setX(_f4u$t.linear_combination(obj.gravity[_f4u$t.X_AXIS], xv1, xv2));
    var yv1 = _f4u$t.xy(this.o, 0, running_count);
    var yv2 = _f4u$t.xy(this.o, y - dim[_f4u$t.Y_AXIS], running_count);
    obj.setY(_f4u$t.linear_combination(obj.gravity[_f4u$t.Y_AXIS], yv1, yv2));
    obj.do_spacing();
    running_count += padding + _f4u$t.xy(this.o, dim[_f4u$t.X_AXIS], dim[_f4u$t.Y_AXIS]);
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
      id : full_id,
      // CSS
      style: 'fill:'+_f4u$t.color_to_rgb(this.fill)+';stroke:black;fill-opacity:0.2;'
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
  this.baselineSkip = _f4u$t.initifnull(options.baselineSkip, 5);
  this.x = 0;
  this.y = 0;
  this.id = _f4u$t.randString();
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.TabGroup);

_f4u$t.TabGroup.prototype.compress = function(coef) {
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].compress(coef);
  }
}

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
      // CSS
      style: 'fill:'+_f4u$t.color_to_rgb(fill)+';stroke:black;',
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
      this.headroom / 2.0 + this.baselineSkip,
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
      height: this.h+'px'
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

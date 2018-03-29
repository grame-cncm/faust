// all onload need to be pushed to the end of the creation

/*
  DEFINES THE FAUST OBJECT CLASS.
  All graphical objects inherit from this.
*/

_f4u$t.UIObject = function() {
  this.x = 0.0;
  this.y = 0.0;
}

_f4u$t.UIObject.prototype.make_group = function(svg, parent, id, opts) {
  opts = opts ? opts : {};
  opts.transform = 'translate('+this.x+','+this.y+')';
  var out = _f4u$t.make_g(
    svg,
    parent,
    id,
    opts);

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

_f4u$t.UIObject.prototype.do_spacing = function(leaf) { }

_f4u$t.UIObject.prototype.stretch = function(x,y) {
  /*
    the whole family
    all with white hair and canes
    visiting graves
  */
}

_f4u$t.UIObject.prototype.get_root_svg = function() {
  if (!this.mom) {
    return null;
  }
  return (this.mom.svg ? this.mom.svg : this.mom.get_root_svg());
}

_f4u$t.UIObject.prototype.get_root_tooltip_group = function() {
  if (!this.mom) {
    return null;
  }
  return (this.mom.tooltip_group ? this.mom.tooltip_group : this.mom.get_root_tooltip_group());
}

_f4u$t.UIObject.prototype.get_layout_manager = function() {
  if (!this.mom) {
    return null;
  }
  return (this.mom instanceof _f4u$t.LayoutManager ? this.mom : this.mom.get_layout_manager());
}

_f4u$t.UIObject.prototype.make_delayed_tooltips = function(svg) {
  for (var i = 0; i < svg._delayed_tooltip_list.length; i++) {
    svg._delayed_tooltip_list[i][0].make_tooltip(
      svg,
      svg._delayed_tooltip_list[i][1],
      svg._delayed_tooltip_list[i][2]
    );
  }
}

_f4u$t.UIObject.prototype.tooltip_text = function() {
  return this.tooltip;
}

_f4u$t.UIObject.prototype.tooltip_text_dims = function() {
  return _f4u$t.get_text_bbox(this.get_root_svg(), this.tooltip_text());
}

_f4u$t.UIObject.prototype.make_tooltip_text = function(svg, parent, id) {
  var text = this.tooltip_text();
  var full_id = 'faust_tooltip_text_'+id;
  var tttext = _f4u$t.make_text(
    svg,
    parent,
    0,
    0,
    text,
    {
      id: full_id,
      'class': 'faust-tooltip-text'
    }
  );

  return tttext;
}

_f4u$t.UIObject.prototype.make_tooltip_box = function(svg, parent, id) {
  var full_id = 'faust_tooltip_box_'+id;
  var textdims = this.tooltip_text_dims();
  var ttbox = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    2,
    -textdims.width*0.05,
    -(textdims.height*1.1),
    textdims.width*1.1,
    textdims.height*1.3,
    {
      id: full_id,
      fill : _f4u$t.color_to_rgb(_f4u$t.WHITE),
      stroke : _f4u$t.color_to_rgb(_f4u$t.BLACK),
      'class': 'faust-tooltip-box'
    });

  return ttbox;
}

_f4u$t.UIObject.prototype.make_delayed_tooltip = function(obj, svg, linked_obj_id, id) {
  svg._delayed_tooltip_list.push([obj, linked_obj_id, id]);
}

_f4u$t.UIObject.prototype.make_tooltip = function(svg, linked_obj_id, id) {
  if (this.tooltip != "") {
    var full_id = 'faust_tooltip_'+id;
    var root = this.get_root_tooltip_group();
    var g = this.make_group(svg, root, full_id)
    var box = this.make_tooltip_box(svg, g, id);
    var text = this.make_tooltip_text(svg, g, id);
    _f4u$t.move_to_ridiculous_negative(full_id);
    $('#'+linked_obj_id).bind('mouseover', _f4u$t.tooltip_mouseover);
    $('#'+linked_obj_id).bind('mouseout', _f4u$t.tooltip_mouseout);
    return g;
  }
}

// Basic UI objects used all over the place

_f4u$t.ValueBox = function(options) {
  _f4u$t.init_prop(this, options, 'vbox', 'mom');
  _f4u$t.init_prop(this, options, 'vbox', 'init');
  _f4u$t.init_prop(this, options, 'vbox', 'width');
  _f4u$t.init_prop(this, options, 'vbox', 'height');
  _f4u$t.init_prop(this, options, 'vbox', 'keysink');
  _f4u$t.init_prop(this, options, 'vbox', 'gravity');
  _f4u$t.init_prop(this, options, 'vbox', 'id');
  _f4u$t.init_prop(this, options, 'label', 'stretchable');
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.ValueBox);

_f4u$t.ValueBox.prototype.dims = function() {
  return [this.width, this.height];
}

_f4u$t.ValueBox.prototype.make_box = function(svg, parent) {
  var id = this.id;
  var mousedown = this.keysink ? '_f4u$t.rotating_button_key_sink("'+id+'")' : '_f4u$t.devnull()';
  var vb = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    2,
    0,
    0,
    this.width,
    this.height,
    {
      id: 'faust_value_box_'+id,
      fill : _f4u$t.color_to_rgb(_f4u$t.WHITE),
      stroke : _f4u$t.color_to_rgb(_f4u$t.BLACK),
      'class': 'faust-vbox-box',
      onmousedown : mousedown,
      ontouchstart : mousedown
    });

  return vb;
}

_f4u$t.ValueBox.prototype.make_value = function(svg, parent) {
  var id = this.id;
  var mousedown = this.keysink ? '_f4u$t.rotating_button_key_sink("'+id+'")' : '_f4u$t.devnull()';
  var vv = _f4u$t.make_text(
    svg,
    parent,
    _f4u$t.xy(this.get_layout_manager().axis, 4, this.width  / 2.0),
    this.height - 4,
    this.init.toString(),
    {
      id: 'faust_value_value_'+id,
      "text-anchor" : _f4u$t.xy(this.get_layout_manager().axis, 'left', 'middle'),
      'class': 'faust-value-text',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );
  return vv;
}

_f4u$t.ValueBox.prototype.make = function(svg, parent) {
  var id = this.id;
  var g = this.make_group(svg, parent, id+"_vbox");

  this.make_box(svg, g, id);
  this.make_value(svg, g, id);

  return g;
}

_f4u$t.Label = function(options) {
  _f4u$t.init_prop(this, options, 'label', 'mom');
  _f4u$t.init_prop(this, options, 'label', 'label');
  _f4u$t.init_prop(this, options, 'label', 'id');
  _f4u$t.init_prop(this, options, 'label', 'gravity');
  _f4u$t.init_prop(this, options, 'label', 'stretchable');
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.Label);

_f4u$t.Label.prototype.dims = function() {
  var bbx = _f4u$t.get_text_bbox(this.get_root_svg(), this.label);
  return [bbx.width, bbx.height];
}

_f4u$t.Label.prototype.label_text = function() {
  var label = this.label;
  if (this.unit) {/* // deprecated
    label += this.unit;*/
  }
  return label;
}

_f4u$t.Label.prototype.make = function(svg, parent) {
  var id = this.id;

  var label = this.label_text();
  var vl = _f4u$t.make_text(
    svg,
    parent,
    0,
    this.dims()[_f4u$t.Y_AXIS],
    label,
    {
      id: 'faust_label_'+id,
      "class" : "faust-label",
    }
  );

}

/*
  DEFINES THE FAUST INCREMENTAL OBJECT CLASS.
  All objects that go up in increments inherit from this.
*/

_f4u$t.IncrementalObject = function () {}
_f4u$t.extend(_f4u$t.UIObject, _f4u$t.IncrementalObject);

/*
  DEFINES A ROTATING BUTTON.
*/

_f4u$t.RotatingButton = function(options) {
  _f4u$t.init_prop(this, options, 'rbutton', 'mom');
  _f4u$t.init_prop(this, options, 'rbutton', 'ir');
  this._r = this.ir;
  _f4u$t.init_prop(this, options, 'rbutton', 'a0');
  _f4u$t.init_prop(this, options, 'rbutton', 'sweep');
  if (this.sweep < 0) {
    this.a0 += this.sweep;
    this.sweep = Math.abs(this.sweep);
  }
  this.sweep = this.sweep % 360;
  if (this.sweep == 0) {
    this.sweep = 360;
  }
  _f4u$t.init_prop(this, options, 'rbutton', 'sp'); // percentage for white handle
  _f4u$t.init_prop(this, options, 'rbutton', 'kp'); // knob percentage
  _f4u$t.init_prop(this, options, 'rbutton', 'unit');
  _f4u$t.init_prop(this, options, 'rbutton', 'min');
  _f4u$t.init_prop(this, options, 'rbutton', 'max');
  _f4u$t.init_prop(this, options, 'rbutton', 'init');
  _f4u$t.init_prop(this, options, 'rbutton', 'step');
  _f4u$t.init_prop(this, options, 'rbutton', 'integer');
  _f4u$t.init_prop(this, options, 'rbutton', 'ndec');
  _f4u$t.init_prop(this, options, 'rbutton', 'stretchable');
  _f4u$t.init_prop(this, options, 'rbutton', 'orientation');
  _f4u$t.init_prop(this, options, 'rbutton', 'orientation_mode');
  _f4u$t.init_prop(this, options, 'rbutton', 'gravity');
  _f4u$t.init_prop(this, options, 'rbutton', 'mgroove_fill');
  _f4u$t.init_prop(this, options, 'rbutton', 'meter_fill');
  _f4u$t.init_prop(this, options, 'rbutton', 'groove_fill');
  _f4u$t.init_prop(this, options, 'rbutton', 'handle_fill');
  _f4u$t.init_prop(this, options, 'rbutton', 'groove_stroke');
  _f4u$t.init_prop(this, options, 'rbutton', 'handle_stroke');
  _f4u$t.init_prop(this, options, 'rbutton', 'mgroove_stroke');
  _f4u$t.init_prop(this, options, 'rbutton', 'meter_stroke');
  _f4u$t.init_prop(this, options, 'rbutton', 'handle_width');
  _f4u$t.init_prop(this, options, 'rbutton', 'tooltip');
  _f4u$t.init_prop(this, options, 'rbutton', 'address');
  _f4u$t.init_prop(this, options, 'rbutton', 'id');
}

_f4u$t.extend(_f4u$t.IncrementalObject, _f4u$t.RotatingButton);

_f4u$t.RotatingButton.prototype.r = function() {
  return this._r;
}

_f4u$t.RotatingButton.prototype.dims = function() {
  return [this.r() * 2, this.r() * 2];
}

_f4u$t.RotatingButton.prototype.make_mgroove = function(svg, parent, id) {
  var full_id = 'faust_rbutton_mgroove_'+id;
  var mousedown = _f4u$t.activate_rbutton;
  var xo = this.r();
  var yo = this.r();
  var d = "M{0} {1}A{2} {3} 0 {4} {5} {6} {7}L{8} {9}A{10} {11} 0 {12} {13} {14} {15}L{16} {17}";
  d = d.format([
    this.r() * Math.cos(_f4u$t.d2r(this.a0)) + xo, // outside X
    this.r() * Math.sin(_f4u$t.d2r(this.a0)) + yo, // outside Y
    this.r(), // radius X
    this.r(), // radius Y
    this.sweep <= 180 ? 0 : 1, // large arc flag
    1, // draw positive
    this.r() * Math.cos(_f4u$t.d2r(this.a0 + this.sweep)) + xo, // endpoint X
    this.r() * Math.sin(_f4u$t.d2r(this.a0 + this.sweep)) + yo, // endpoint Y
    this.r() * this.kp * Math.cos(_f4u$t.d2r(this.a0 + this.sweep)) + xo, // inside endpoint X
    this.r() * this.kp * Math.sin(_f4u$t.d2r(this.a0 + this.sweep)) + yo, // inside endpoint Y
    this.r() * this.kp, // inside radiux X
    this.r() * this.kp, // inside radiux Y
    this.sweep <= 180 ? 0 : 1, // large arc flag
    0, // draw negative
    this.r() * this.kp * Math.cos(_f4u$t.d2r(this.a0)) + xo, // inside X
    this.r() * this.kp * Math.sin(_f4u$t.d2r(this.a0)) + yo, // inside Y
    this.r() * Math.cos(_f4u$t.d2r(this.a0)) + xo, // outside X
    this.r() * Math.sin(_f4u$t.d2r(this.a0)) + yo// outside Y
  ]);
  var mgroove = _f4u$t.make_path(
    svg,
    parent,
    d,
    {
      fill : _f4u$t.color_to_rgb(this.mgroove_fill),
      stroke : _f4u$t.color_to_rgb(this.mgroove_stroke),
      id : full_id,
      'class' : 'faust-rbutton-mgroove'
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return mgroove;
}

_f4u$t.RotatingButton.prototype.make_dot = function(svg, parent, id, rot) {
  var full_id = 'faust_rbutton_dot'+(rot*45)+'_'+id;
  var mousedown = _f4u$t.activate_rbutton;
  var xo = this.r();
  var yo = this.r();
  var dot = _f4u$t.make_circle(
    svg,
    parent,
    this.r() * (this.kp + 1) * 0.5 * Math.cos(_f4u$t.d2r(rot * 45)) + xo,
    this.r() * (this.kp + 1) * 0.5 * Math.sin(_f4u$t.d2r(rot * 45)) + yo,
    this.r() * (1 - this.kp) * 0.5,
    {
      fill : _f4u$t.color_to_rgb(this.dot_fill),
      stroke : _f4u$t.color_to_rgb(this.dot_stroke),
      id : full_id,
      'class' : 'faust-rbutton-dot'
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return dot;
}

_f4u$t.RotatingButton.prototype.make_meter = function(svg, parent, id) {
  var full_id = 'faust_rbutton_meter_'+id;
  var mousedown = _f4u$t.activate_rbutton;
  var xo = this.r();
  var yo = this.r();
  var startp = _f4u$t.remap(this.init, this.min, this.max, this.a0, this.a0 + this.sweep);
  var d = "M{0} {1}A{2} {3} 0 {4} {5} {6} {7}L{8} {9}A{10} {11} 0 {12} {13} {14} {15}L{16} {17}";
  d = d.format([
    this.r() * Math.cos(_f4u$t.d2r(startp)) + xo, // outside X
    this.r() * Math.sin(_f4u$t.d2r(startp)) + yo, // outside Y
    this.r(), // radius X
    this.r(), // radius Y
    this.a0 + this.sweep - startp <= 180 ? 0 : 1, // large arc flag
    1, // draw positive
    this.r() * Math.cos(_f4u$t.d2r(this.a0 + this.sweep)) + xo, // endpoint X
    this.r() * Math.sin(_f4u$t.d2r(this.a0 + this.sweep)) + yo, // endpoint Y
    this.r() * this.kp * Math.cos(_f4u$t.d2r(this.a0 + this.sweep)) + xo, // inside endpoint X
    this.r() * this.kp * Math.sin(_f4u$t.d2r(this.a0 + this.sweep)) + yo, // inside endpoint Y
    this.r() * this.kp, // inside radiux X
    this.r() * this.kp, // inside radiux Y
    this.a0 + this.sweep - startp <= 180 ? 0 : 1, // large arc flag
    0, // draw negative
    this.r() * this.kp * Math.cos(_f4u$t.d2r(startp)) + xo, // inside X
    this.r() * this.kp * Math.sin(_f4u$t.d2r(startp)) + yo, // inside Y
    this.r() * Math.cos(_f4u$t.d2r(startp)) + xo, // outside X
    this.r() * Math.sin(_f4u$t.d2r(startp)) + yo// outside Y
  ]);
  var meter = _f4u$t.make_path(
    svg,
    parent,
    d,
    {
      fill : _f4u$t.color_to_rgb(this.meter_fill),
      stroke : _f4u$t.color_to_rgb(this.meter_stroke),
      id : full_id,
      'class' : 'faust-rbutton-meter'
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return meter;
}

_f4u$t.RotatingButton.prototype.make_groove = function(svg, parent, id) {
  var mousedown = _f4u$t.activate_rbutton;
  var full_id = 'faust_rbutton_groove_'+id;
  var groove = _f4u$t.make_circle(
    svg,
    parent,
    this.r(),
    this.r(),
    this.r() * this.kp,    
    {
      fill : _f4u$t.color_to_rgb(this.groove_fill),
      stroke : _f4u$t.color_to_rgb(this.groove_stroke),
      id : full_id,
      'class' : 'faust-rbutton-groove'
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return groove;
}

_f4u$t.RotatingButton.prototype.make_handle = function(svg, parent, id) {
  var full_id = 'faust_rbutton_handle_'+id;
  var origin = [this.r(), this.r()];
  var startp = _f4u$t.remap(this.init, this.min, this.max, this.a0, this.a0 + this.sweep);
  var mousedown = _f4u$t.activate_rbutton;
  var handle = _f4u$t.make_line(
    svg,
    parent,
    origin[0],
    origin[1],
    origin[0] + (this.r() * this.sp * this.kp) , // set at 0 degrees to start, then rotate below
    origin[1],
    {
      fill : _f4u$t.color_to_rgb(this.handle_fill),
      stroke : _f4u$t.color_to_rgb(this.handle_stroke),
      "stroke-width" : this.handle_width,
      'class' : 'faust-rbutton-handle',
      id : full_id,
      transform : 'translate(0,0) scale(1,1) rotate('+startp+','+origin[0]+','+origin[1]+')'
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return handle;
}

// anchor helps us get correct positioning for rotation
_f4u$t.RotatingButton.prototype.make_anchor = function(svg, parent, id) {
  var origin = [this.r(), this.r()];
  var full_id = 'faust_rbutton_anchor_'+id;

  var anchor = _f4u$t.make_path(
    svg,
    parent,
    "M 0 0L0 1L1 1L1 0L0 0",
    {
      id : full_id,
      style : 'opacity:0.0;',
      transform : 'translate('+origin[0]+','+origin[1]+')',
    }
  );

  return anchor;
}

_f4u$t.RotatingButton.prototype.make = function(svg, parent) {
  var id = this.id;
  var g = this.make_group(svg, parent, id);
  _f4u$t.initiate_rbutton(
    id,
    this.a0,
    this.sweep,
    this.r(),
    this.kp,
    this.min,
    this.max,
    this.step,
    this.init,
    this.integer,
    this.ndec,
    this.label,
    this.unit,
    this.orientation,
    this.orientation_mode,
    this.address
  );

  this.make_anchor(svg, g, id);
  if (this.sweep != 360) {
    this.make_mgroove(svg, g, id);
    this.make_meter(svg, g, id);
  } else {
    for (var i = 0; i < 8; i++) {
      this.make_dot(svg, g, id, i);
    }
  }
  this.make_groove(svg, g, id);
  this.make_handle(svg, g, id);
  this.make_delayed_tooltip(this, svg, id, id);

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
  _f4u$t.init_prop(this, options, type, 'unit');
  _f4u$t.init_prop(this, options, type, 'min');
  _f4u$t.init_prop(this, options, type, 'max');
  _f4u$t.init_prop(this, options, type, 'init');
  _f4u$t.init_prop(this, options, type, 'step');
  _f4u$t.init_prop(this, options, type, 'integer');
  _f4u$t.init_prop(this, options, type, 'ndec');
  _f4u$t.init_prop(this, options, type, 'stretchable');
  _f4u$t.init_prop(this, options, type, 'gravity');
  _f4u$t.init_prop(this, options, type, 'address');
  _f4u$t.init_prop(this, options, type, 'id');
  _f4u$t.init_prop(this, options, type, 'type');
  _f4u$t.init_prop(this, options, type, 'tooltip');
}

_f4u$t.extend(_f4u$t.IncrementalObject, _f4u$t.SlidingObject);

_f4u$t.SlidingObject.prototype.dims = function() {
  var x = _f4u$t.xy(this.axis, this.length, this.girth);
  var y = _f4u$t.xy(this.axis, this.girth, this.length);
  return [x,y];
}

_f4u$t.SlidingObject.prototype.stretch = function(x,y) {
  if (this.stretchable[this.axis]) {
    dims = this.dims();
    this.length = Math.max(dims[this.axis], _f4u$t.xy(this.axis, x, y));
  }
}

_f4u$t.Slider = function(options, type) {
  _f4u$t.SlidingObject.call(this, options, type);
  _f4u$t.init_prop(this, options, type,'sp');
  _f4u$t.init_prop(this, options, type, 'orientation');
  _f4u$t.init_prop(this, options, type, 'orientation_mode');
  _f4u$t.init_prop(this, options, type, 'groove_fill');
  _f4u$t.init_prop(this, options, type, 'groove_stroke');
  _f4u$t.init_prop(this, options, type, 'handle_fill');
  _f4u$t.init_prop(this, options, type, 'handle_stroke');
}

_f4u$t.extend(_f4u$t.SlidingObject, _f4u$t.Slider);

_f4u$t.Slider.prototype.skinny_girth = function() {
  return this.girth * 2.0 / 5.0;
}

_f4u$t.Slider.prototype.make_groove = function(svg, parent, id) {
  var dims = this.dims();
  var w = _f4u$t.xy(this.axis, this.length, this.skinny_girth());
  var h = _f4u$t.xy(this.axis, this.skinny_girth(), this.length);
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var slider_girth = this.sp;
  var half_slider_girth = slider_girth * 0.5;
  var startp = _f4u$t.xy(this.axis, _f4u$t.remap, _f4u$t.remap_and_flip)(this.init, this.min, this.max, 0 + half_slider_girth, this.length - half_slider_girth);
  var trans = _f4u$t.xy(this.axis, 'translate(0,'+((this.girth - this.skinny_girth()) / 2)+')', 'translate('+xo+',0)');
  var full_id = 'faust_'+this.type+'_groove_'+id;
  var activate_fn = "activate_"+this.type;
  var mousedown = _f4u$t[activate_fn];
  var groove = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    _f4u$t.xy(this.axis, startp, 0),
    0,
    _f4u$t.xy(this.axis, w - startp, w),
    _f4u$t.xy(this.axis, h, startp),
    {
      fill : _f4u$t.color_to_rgb(this.groove_fill),
      stroke : _f4u$t.color_to_rgb(this.groove_stroke),
      id : full_id,
      'class' : _f4u$t.xy(this.axis, 'faust-hslider-groove', 'faust-vslider-groove'),
      transform : trans
    });

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return groove;
}

_f4u$t.Slider.prototype.make_meter = function(svg, parent, id) {
  var dims = this.dims();
  var w = _f4u$t.xy(this.axis, this.length, this.skinny_girth());
  var h = _f4u$t.xy(this.axis, this.skinny_girth(), this.length);
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var trans = _f4u$t.xy(this.axis, 'translate(0,'+((this.girth - this.skinny_girth()) / 2)+')', 'translate('+xo+',0)');
  var full_id = 'faust_'+this.type+'_meter_'+id;
  var activate_fn = "activate_"+this.type;
  var mousedown = _f4u$t[activate_fn];
  var groove = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      fill : _f4u$t.color_to_rgb(this.groove_fill),
      stroke : _f4u$t.color_to_rgb(this.groove_stroke),
      id : full_id,
      'class' : _f4u$t.xy(this.axis, 'faust-hslider-meter', 'faust-vslider-meter'),
      transform : trans
    });

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return groove;
}

_f4u$t.Slider.prototype.make_handle = function(svg, parent, id) {
  var dims = this.dims();
  var slider_girth = this.sp;
  var half_slider_girth = slider_girth * 0.5;
  var startp = _f4u$t.xy(this.axis, _f4u$t.remap, _f4u$t.remap_and_flip)(this.init, this.min, this.max, 0 + half_slider_girth, this.length - half_slider_girth);
  var bottom = startp - half_slider_girth;
  var top = startp + half_slider_girth;
  var w = _f4u$t.xy(this.axis, slider_girth, this.girth);
  var h = _f4u$t.xy(this.axis, this.girth, slider_girth);
  var xo = ((this.axis == _f4u$t.Y_AXIS) ? (dims[0] - w) / 2.0 : 0.0);
  var x = _f4u$t.xy(this.axis, bottom, xo);
  var y = _f4u$t.xy(this.axis, 0, bottom);
  var full_id = 'faust_'+this.type+'_handle_'+id;
  var activate_fn = "activate_"+this.type;
  var mousedown = _f4u$t[activate_fn];

  var handle = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      fill : _f4u$t.color_to_rgb(this.handle_fill),
      stroke : _f4u$t.color_to_rgb(this.handle_stroke),
      id : full_id,
      'class' : _f4u$t.xy(this.axis, 'faust-hslider-handle', 'faust-vslider-handle'),
      transform : 'translate('+x+','+y+')'
    });

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return handle;
}

_f4u$t.Slider.prototype.make = function(svg, parent) {
  var id = this.id;
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
    this.unit,
    this.orientation,
    this.orientation_mode,
    this.address
  );

  this.make_meter(svg, g, id);
  this.make_groove(svg, g, id);
  this.make_handle(svg, g, id);
  this.make_delayed_tooltip(this, svg, id, id);
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
  this.curtain_fill = _f4u$t.initifnull(options.curtain_fill, _f4u$t.CYAN);
  this.curtain_stroke = _f4u$t.initifnull(options.curtain_stroke, _f4u$t.CYAN);
  this.meter_fill = _f4u$t.initifnull(options.meter_fill, _f4u$t.CYAN);
  this.meter_stroke = _f4u$t.initifnull(options.meter_stroke, _f4u$t.CYAN);
  this.init = this.init ? this.init : this.min;
}

_f4u$t.extend(_f4u$t.SlidingObject, _f4u$t.BarGraph);

_f4u$t.BarGraph.prototype.make_curtain = function(svg, parent, id) {
  var full_id = 'faust_'+this.type+'_curtain_'+id;
  var def = _f4u$t.xy(this.axis, _f4u$t.remap, _f4u$t.remap_and_flip)(this.init, this.min, this.max, 0, this.length);
  var dims = this.dims();
  var w = _f4u$t.xy(this.axis, def, this.girth);
  var h = _f4u$t.xy(this.axis, this.girth, def);
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var curtain = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      fill : _f4u$t.color_to_rgb(this.curtain_fill),
      stroke : _f4u$t.color_to_rgb(this.curtain_stroke),
      id : full_id,
      transform : _f4u$t.xy(this.axis,'translate('+(xo + this.length)+',0) scale(-1,1)', 'translate('+xo+',0)'),
      'class' : _f4u$t.xy(this.axis, 'faust-hbargraph-curtain', 'faust-vbargraph-curtain')
    });

  return curtain;
}

_f4u$t.BarGraph.prototype.make_meter = function(svg, parent, id) {
  var dims = this.dims();
  var w = _f4u$t.xy(this.axis, this.length, this.girth);
  var h = _f4u$t.xy(this.axis, this.girth, this.length);
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var meter = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      fill : _f4u$t.color_to_rgb(this.meter_fill),
      stroke : _f4u$t.color_to_rgb(this.meter_stroke),
      id : 'faust_'+this.type+'_meter_'+id,
      transform : 'translate('+xo+',0)',
      'class' : _f4u$t.xy(this.axis, 'faust-hbargraph-meter', 'faust-vbargraph-meter')
    });

  return meter;
}

_f4u$t.BarGraph.prototype.make = function(svg, parent) {
  var id = this.id;
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
    this.unit,
    this.address
  );

  this.make_meter(svg, g, id);
  this.make_curtain(svg, g, id);

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
  _f4u$t.init_prop(this, options, 'checkbox','gravity');
  _f4u$t.init_prop(this, options, 'checkbox','check_fill');
  _f4u$t.init_prop(this, options, 'checkbox','check_stroke');
  _f4u$t.init_prop(this, options, 'checkbox','box_fill');
  _f4u$t.init_prop(this, options, 'checkbox','box_stroke');
  _f4u$t.init_prop(this, options, 'checkbox','init');
  _f4u$t.init_prop(this, options, 'checkbox', 'stretchable');
  _f4u$t.init_prop(this, options, 'checkbox', 'tooltip');
  _f4u$t.init_prop(this, options, 'checkbox','address');
  _f4u$t.init_prop(this, options, 'checkbox', 'id');
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.CheckBox);

_f4u$t.CheckBox.prototype.dims = function() {
  return [this.d, this.d];
}

// DON'T FORGET TO SPECIFY CHECK IN CALLBACK
_f4u$t.CheckBox.prototype.make_box = function(svg, parent, id) {
  var full_id = 'faust_checkbox_box_'+id;
  var w = this.d;
  var h = this.d;
  var dims = this.dims();
  var xo = (dims[0] - w) / 2.0;
  var mouseup = '_f4u$t.click_checkbox("'+full_id+'")';
  var touchup = '_f4u$t.touch_checkbox("'+full_id+'")';

  var box = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      fill : _f4u$t.color_to_rgb(this.box_fill),
      stroke : _f4u$t.color_to_rgb(this.box_stroke),
      id : full_id,
      'class' : 'faust-checkbox-box',
      transform : 'translate('+xo+',0)',
      onmouseup : mouseup,
      ontouchend : touchup
    });

  return box;
}

_f4u$t.CheckBox.prototype.make_check = function(svg, parent, id) {
  var full_id = 'faust_checkbox_check_'+id;
  var w = this.d;
  var h = this.d;
  var dims = this.dims();
  var xo = (dims[0] - w) / 2.0;
  var mouseup = '_f4u$t.change_checkbox("'+full_id+'")';
  //var touchup = '_f4u$t.touch_checkbox("'+full_id+'")';
  var box = _f4u$t.make_path(
    svg,
    parent,
    "M0 0L"+this.d+" "+this.d+"M0 "+this.d+"L"+this.d+" 0",
    {
      id : full_id,
      fill : _f4u$t.color_to_rgb(this.check_fill),
      stroke : _f4u$t.color_to_rgb(this.check_stroke),
      style : "opacity:"+(this.init == 1 ? 1.0 : 0.0),
      onmouseup : mouseup,
      //ontouchend : touchup, // deactivated so that touch doesn't trigger both box and check at the same time
      'class' : 'faust-chekbox-check',
      transform : 'translate('+xo+',0)'
    }
  );

  return box;
}

_f4u$t.CheckBox.prototype.make = function(svg, parent) {
  var id = this.id;
  var g = this.make_group(svg, parent, id);

  _f4u$t.initiate_checkbox(id, this.address);

  this.make_box(svg, g, id);
  this.make_check(svg, g, id);
  //this.make_label(svg, g, id);
  this.make_delayed_tooltip(this, svg, id, id);

  return g;
}

/*
  Button in
*/

_f4u$t.Button = function(options) {
  _f4u$t.init_prop(this, options, 'button','mom');
  _f4u$t.init_prop(this, options, 'button','ideal_width');
  _f4u$t.init_prop(this, options, 'button','ideal_height');
  _f4u$t.init_prop(this, options, 'button', 'tooltip');
  _f4u$t.init_prop(this, options, 'button', 'label');
  this._w = this.ideal_width;
  this._h = this.ideal_height;
  _f4u$t.init_prop(this, options, 'button','gravity');
  _f4u$t.init_prop(this, options, 'button','fill_on');
  _f4u$t.init_prop(this, options, 'button','fill_off');
  _f4u$t.init_prop(this, options, 'button','stroke');
  _f4u$t.init_prop(this, options, 'button', 'stretchable');
  _f4u$t.init_prop(this, options, 'button','baseline_skip');
  _f4u$t.init_prop(this, options, 'button', 'id');
  _f4u$t.init_prop(this, options, 'button','address');
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.Button);

_f4u$t.Button.prototype.w = function() {
  return Math.max(this._w,  _f4u$t.get_text_bbox(this.get_root_svg(), this.label).width + 6);
}

_f4u$t.Button.prototype.h = function() {
  return this._h;
}

_f4u$t.Button.prototype.dims = function() {
  return [this.w(), this.h()];
}

_f4u$t.Button.prototype.make_button_box = function(svg, parent, id) {
  var full_id = 'faust_button_box_'+id;
  var rf = 10;
  var button = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    rf,
    0,
    0,
    this.w(),
    this.h(),
    {
      id : full_id,
      fill : _f4u$t.color_to_rgb(this.fill_off),
      stroke : _f4u$t.color_to_rgb(this.stroke),
      'class' : 'faust-button-box',
      onmouseover : '_f4u$t.button_hover("'+full_id+'")',
      onmouseout : '_f4u$t.button_unhover("'+full_id+'")'
    });

  return button;
}

_f4u$t.Button.prototype.make_label = function(svg, parent, id) {
  var vl = _f4u$t.make_text(
    svg,
    parent,
    0,
    0,
    this.label,
    {
      "text-anchor" : 'middle',
      id: 'faust_label_'+id,
      class: 'faust-button-label',
      transform: 'translate('+(this.w() / 2.0)+','+(this.h() / 2.0 + this.baseline_skip)+')',
    }
  );

  return vl;
}

_f4u$t.Button.prototype.make = function(svg, parent) {
  var id = this.id;
  var full_id = 'faust_button_box_'+id;
  var mousedown = '_f4u$t.button_down("'+full_id+'")';
  var mouseup = '_f4u$t.button_up("'+full_id+'")';
  var g = this.make_group(svg, parent, id,
    {
      onmousedown : mousedown,
      //ontouchstart : mousedown,
      onmouseup : mouseup,
      //ontouchend : mouseup
    });

  _f4u$t.initiate_button(
    id,
    _f4u$t.color_to_rgb(this.fill_off),
    _f4u$t.color_to_rgb(this.fill_on),
    this.address
  );

  this.make_button_box(svg, g, id);
  this.make_label(svg, g, id);
  this.make_delayed_tooltip(this, svg, id, id);

  return g;
}

_f4u$t.NumericalEntry = function(options) {
  _f4u$t.init_prop(this, options, 'nentry', 'mom');
  _f4u$t.init_prop(this, options, 'nentry', 'unit');
  _f4u$t.init_prop(this, options, 'nentry', 'ideal_width');
  _f4u$t.init_prop(this, options, 'nentry', 'ideal_height');
  this._w = this.ideal_width;
  this._h = this.ideal_height;
  _f4u$t.init_prop(this, options, 'nentry', 'min');
  _f4u$t.init_prop(this, options, 'nentry', 'max');
  _f4u$t.init_prop(this, options, 'nentry', 'init');
  _f4u$t.init_prop(this, options, 'nentry', 'step');
  _f4u$t.init_prop(this, options, 'nentry', 'integer');
  _f4u$t.init_prop(this, options, 'nentry', 'ndec');
  _f4u$t.init_prop(this, options, 'nentry', 'gravity');
  _f4u$t.init_prop(this, options, 'nentry', 'address');
  _f4u$t.init_prop(this, options, 'nentry', 'id');
  _f4u$t.init_prop(this, options, 'nentry', 'type');
  _f4u$t.init_prop(this, options, 'button', 'stretchable');
  _f4u$t.init_prop(this, options, 'nentry', 'button_fill');
  _f4u$t.init_prop(this, options, 'nentry', 'operation_fill');
  _f4u$t.init_prop(this, options, 'nentry', 'button_stroke');
  _f4u$t.init_prop(this, options, 'nentry', 'operation_stroke');
  _f4u$t.init_prop(this, options, 'nentry', 'padding');
  _f4u$t.init_prop(this, options, 'button', 'tooltip');
}

_f4u$t.extend(_f4u$t.IncrementalObject, _f4u$t.NumericalEntry);

_f4u$t.NumericalEntry.prototype.w = function() {
  return this._w;
}

_f4u$t.NumericalEntry.prototype.h = function() {
  return this._h;
}

_f4u$t.NumericalEntry.prototype.dims = function() {
  return [this.w(), this.h()];
}

_f4u$t.NumericalEntry.prototype.make_left_button = function(svg, parent, id) {
  return this.make_button(svg, parent, id, 0, false);
}

_f4u$t.NumericalEntry.prototype.make_right_button = function(svg, parent, id) {
  return this.make_button(svg, parent, id, this.w() / 2.0 + this.padding, true);
}

_f4u$t.NumericalEntry.prototype.make_button = function(svg, parent, id, xo, incr) {
  var identifier = incr ? 'rbutton' : 'lbutton';
  var tag = incr ? 'plus' : 'minus';
  var full_id = 'faust_nentry_button_'+tag+'_'+id;
  var w = this.w() / 2.0 - this.padding;
  var h = this.h();
  var mousedown = _f4u$t['nentry_down_'+tag]
  var mouseup = _f4u$t['nentry_up_'+tag]
  var button = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      
      fill : _f4u$t.color_to_rgb(this.button_fill),
      stroke : _f4u$t.color_to_rgb(this.button_stroke),
      transform : 'translate('+xo+',0)',
      id : full_id,
      'class' : 'faust-nentry-box'
    });

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  $('#'+full_id).bind('mouseup', mouseup);
  $('#'+full_id).bind('touchend', mouseup);
  return button;
}

_f4u$t.NumericalEntry.prototype.make_minus = function(svg, parent, id) {
  var full_id = 'faust_nentry_minus_'+id;
  var x0 = (this.w() / 2.0 - this.padding) / 4.0;
  var y = this.h() / 2.0;
  var x1 = (this.w() / 2.0 - this.padding) * 3.0 / 4.0;
  var mousedown = _f4u$t.nentry_down_minus;
  var mouseup = _f4u$t.nentry_up_minus;

  var d = "M"+x0+" "+y+"L"+x1+" "+y;
  var minus = _f4u$t.make_path(
    svg,
    parent,
    d,
    {
      fill : _f4u$t.color_to_rgb(this.operation_fill),
      stroke : _f4u$t.color_to_rgb(this.operation_stroke),
      id : full_id,
      'class' : 'faust-nentry-operation',
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  $('#'+full_id).bind('mouseup', mouseup);
  $('#'+full_id).bind('touchend', mouseup);
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
  var mousedown = _f4u$t.nentry_down_plus;
  var mouseup = _f4u$t.nentry_up_plus;

  var plus = _f4u$t.make_path(
    svg,
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

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  $('#'+full_id).bind('mouseup', mouseup);
  $('#'+full_id).bind('touchend', mouseup);
  return plus;
}

_f4u$t.NumericalEntry.prototype.make = function(svg, parent) {
  var id = this.id;
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
    this.unit,
    this.address
  );

  this.make_left_button(svg, g, id);
  this.make_right_button(svg, g, id);
  this.make_minus(svg, g, id);
  this.make_plus(svg, g, id);
  this.make_delayed_tooltip(this, svg, id, id);

  return g;
}

_f4u$t.LayoutManager = function(options) {
  var type = _f4u$t.xy(options.axis, 'hgroup','vgroup');
  _f4u$t.init_prop(this, options, type, 'mom');
  _f4u$t.init_prop(this, options, type, 'axis');
  _f4u$t.init_prop(this, options, type, 'padding');
  _f4u$t.init_prop(this, options, type, 'other_axis_padding');
  _f4u$t.init_prop(this, options, type, 'draw_background');
  _f4u$t.init_prop(this, options, type, 'label');
  _f4u$t.init_prop(this, options, type, 'objs');
  _f4u$t.init_prop(this, options, type, 'gravity');
  _f4u$t.init_prop(this, options, type, 'stretchable');
  _f4u$t.init_prop(this, options, type, 'fill');
  _f4u$t.init_prop(this, options, type, 'stroke');
  this.x = 0;
  this.y = 0;
  this.w = 0;
  this.h = 0;
  this.id = _f4u$t.randString();
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.LayoutManager);

_f4u$t.LayoutManager.prototype.dims = function() {
  var outx = [];
  var outy = [];
  for (var i = 0; i < this.objs.length; i++) {
    var dim = this.objs[i].dims();
    outx.push(dim[_f4u$t.X_AXIS]);
    outy.push(dim[_f4u$t.Y_AXIS]);
  }

  var out = [outx, outy];

  for (var i = _f4u$t.X_AXIS; i < _f4u$t.NO_AXES; i++) {
    out[i] = (i == this.axis ? out[i].sum() : out[i].max());
  }

  // this adds in between padding for all objects as well as
  // padding on the top and on the bottom
  out[this.axis] += (this.padding * (this.objs.length + 1));
  // this only adds padding on the sides
  out[_f4u$t.other_axis(this.axis)] += (2 * this.other_axis_padding);
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

_f4u$t.LayoutManager.prototype.stretch = function(x,y) {
  // This function could just do the dim change, but
  // it would leave stuff clumped in the center.  We air
  // things out if nothing stretches.
  if (this.stretchable[this.axis]) {
    var change_padding = true;
    for (var i = 0; i < this.objs.length; i++) {
      if (this.objs[i].stretchable[this.axis]) {
        // if even a single object can be stretched,
        // don't change the padding and let that object stretch
        change_padding = false;
        break;
      }
    }
    if (change_padding) {
      var dim = this.dims();
      // if not a single object can be stretched, then we
      // space objects out via the padding
      this.padding = this.padding + Math.max(0,
                      (_f4u$t.xy(this.axis,x,y)  - dim[this.axis]) / (this.objs.length + 1));
    }
  }

  var dim = this.dims();
  this.dims = function() { return [this.stretchable[_f4u$t.X_AXIS] ? x : dim[_f4u$t.X_AXIS],
                                   this.stretchable[_f4u$t.Y_AXIS] ? y : dim[_f4u$t.Y_AXIS]]; };
}

_f4u$t.LayoutManager.prototype.get_stretchable_coefficient = function(total) {
  var stretchable = 0.0;
  var unstretchable = 0.0;
  for (var i = 0; i < this.objs.length; i++) {
    if (this.objs[i].stretchable[this.axis]) {
      stretchable += this.objs[i].dims()[this.axis];
    } else {
      unstretchable += this.objs[i].dims()[this.axis];
    }
  }
  return (total - (this.padding * (this.objs.length + 1)) - unstretchable) / stretchable;
}

_f4u$t.LayoutManager.prototype.do_spacing = function(leaf) {
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
  var stretchable_coefficient = this.get_stretchable_coefficient(_f4u$t.xy(this.axis,x,y));
  for (var i = 0; i < this.objs.length; i++) {
    var obj = this.objs[i];
    // the first time we calc the dim, we do it so that we can pass
    // a proposition for stretching to the stretching algorithm
    // the is the maximum space allowable for stretching
    var dim = obj.dims();
    obj.stretch(_f4u$t.xy(this.axis, stretchable_coefficient * dim[_f4u$t.X_AXIS], x - (2 * this.other_axis_padding)), _f4u$t.xy(this.axis, y - (2 * this.other_axis_padding), stretchable_coefficient * dim[_f4u$t.Y_AXIS]));
    // we need to calculate the dimensions a second time
    // because they may have been stretched above
    dim = obj.dims();
    var xv1 = _f4u$t.xy(this.axis, running_count, 0);
    var xv2 = _f4u$t.xy(this.axis, running_count, x - dim[_f4u$t.X_AXIS]);
    obj.setX(_f4u$t.linear_combination(obj.gravity[_f4u$t.X_AXIS], xv1, xv2));
    var yv1 = _f4u$t.xy(this.axis, 0, running_count);
    var yv2 = _f4u$t.xy(this.axis, y - dim[_f4u$t.Y_AXIS], running_count);
    obj.setY(_f4u$t.linear_combination(obj.gravity[_f4u$t.Y_AXIS], yv1, yv2));
    obj.do_spacing(leaf + 1);
    running_count += padding + _f4u$t.xy(this.axis, dim[_f4u$t.X_AXIS], dim[_f4u$t.Y_AXIS]);
  }
}

_f4u$t.LayoutManager.prototype.make_background = function(svg, parent) {
  var full_id = 'faust_background_'+this.id;
  var dims = this.dims();
  var w = dims[0];
  var h = dims[1];
  var background = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      fill : _f4u$t.color_to_rgb(this.fill),
      stroke : _f4u$t.color_to_rgb(this.stroke),
      'class' : 'faust-group-background',
      id : full_id,
      style: +'fill-opacity:0.2;'
    });

  return background;
}

// only for debugging
_f4u$t.LayoutManager.prototype.make_dim_cross = function(svg, parent) {
  var dims = this.dims();
  _f4u$t.make_path(
    svg,
    parent,
    "M0 0L"+dims[0]+' '+dims[1]
  );

  //return background;
}

_f4u$t.LayoutManager.prototype.make = function(svg, parent) {
  var g = this.make_group(svg, parent, this.id);

  if (this.draw_background) {
    this.make_background(svg, g);
  }
  //this.make_label(svg, g);

  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].make(svg, g);
  }

  //this.make_dim_cross(svg, g);
  return g;
}

_f4u$t.TabGroup = function(options) {
  _f4u$t.init_prop(this, options, 'tgroup', 'mom');
  _f4u$t.init_prop(this, options, 'tgroup', 'headroom');
  _f4u$t.init_prop(this, options, 'tgroup', 'headpadding');
  _f4u$t.init_prop(this, options, 'tgroup', 'x_padding');
  _f4u$t.init_prop(this, options, 'tgroup', 'x_width');
  _f4u$t.init_prop(this, options, 'tgroup', 'objs');
  _f4u$t.init_prop(this, options, 'tgroup', 'init');
  _f4u$t.init_prop(this, options, 'tgroup', 'stretchable');
  _f4u$t.init_prop(this, options, 'tgroup', 'gravity');
  _f4u$t.init_prop(this, options, 'tgroup', 'baseline_skip');
  _f4u$t.init_prop(this, options, 'tgroup', 'fill_on');
  _f4u$t.init_prop(this, options, 'tgroup', 'fill_off');
  _f4u$t.init_prop(this, options, 'tgroup', 'stroke');
  this.x = 0;
  this.y = 0;
  this.id = _f4u$t.randString();
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

_f4u$t.TabGroup.prototype.do_spacing = function(leaf) {
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].x = 0;
    this.objs[i].y = this.headroom + this.headpadding;
    this.objs[i].do_spacing(leaf + 1);
  }
}

_f4u$t.TabGroup.prototype.make_label = function(svg, parent, x, y, l, goodid, badidstr) {
  var mousedown = '_f4u$t.activate_tgroup(0,'+(this.headroom + this.headpadding)+',"'+goodid+'","'+badidstr+'")'
  var vl = _f4u$t.make_text(
    svg,
    parent,
    0,
    0,
    l,
    {
      "text-anchor" : 'middle',
      'class' : 'faust-tgroup-label',
      transform : 'translate('+x+','+y+')',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );

  return vl;
}

_f4u$t.TabGroup.prototype.make_tab = function(svg, parent, w, h, x, y, goodid, badidstr, fill, down) {
  var mousedown = '_f4u$t.activate_tgroup(0,'+(this.headroom + this.headpadding)+',"'+goodid+'","'+badidstr+'")';
  var tab = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      transform: 'translate('+x+','+y+')',
      'class' : 'faust-tgroup-box',
      fill : _f4u$t.color_to_rgb(fill),
      stroke : _f4u$t.color_to_rgb(this.stroke),
      id : 'faust_tab_'+_f4u$t.unique(goodid),
      onmousedown : mousedown,
      ontouchstart : mousedown
    });

  return tab;
}

_f4u$t.TabGroup.prototype.make_tabs = function(svg, parent) {
  // we evenly space buttons across x axis
  // was a bug...
  var g = _f4u$t.make_g(svg, parent, 'faust_tabgroup_tabbar_'+this.id);

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
      this.fill_off,
      i==0);
    this.make_label(
      svg,
      parent,
      running_count + this.x_width / 2.0,
      this.headroom / 2.0 + this.baseline_skip,
      // a bit of a hack...
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

_f4u$t.SVG.prototype.defs = function() {
  for (var gradient in _f4u$t.linear_gradient_inits) {
    _f4u$t.make_linear_gradient(
      this.svg,
      gradient,
      _f4u$t.linear_gradient_inits[gradient]['stops'],
      _f4u$t.linear_gradient_inits[gradient]['x1'],
      _f4u$t.linear_gradient_inits[gradient]['y1'],
      _f4u$t.linear_gradient_inits[gradient]['x2'],
      _f4u$t.linear_gradient_inits[gradient]['y2'],
      _f4u$t.linear_gradient_inits[gradient]['settings']
    );
  }

  for (var gradient in _f4u$t.radial_gradient_inits) {
    _f4u$t.make_radial_gradient(
      this.svg,
      gradient,
      _f4u$t.radial_gradient_inits[gradient]['stops'],
      _f4u$t.radial_gradient_inits[gradient]['cx'],
      _f4u$t.radial_gradient_inits[gradient]['cy'],
      _f4u$t.radial_gradient_inits[gradient]['r'],
      _f4u$t.radial_gradient_inits[gradient]['fx'],
      _f4u$t.radial_gradient_inits[gradient]['fy'],
      _f4u$t.radial_gradient_inits[gradient]['settings']
    );
  }
}

_f4u$t.SVG.prototype.make = function() {
  _f4u$t.configure_svg(
    this.svg,
    {
      width : this.w+'px',
      height : this.h+'px'
    },
    true);
  _f4u$t.ROOT = this.title;
  this.svg._delayed_tooltip_list = [];
  this.lm.populate_objects();
  this.lm.do_spacing(0);
  this.lm.make(this.svg, this.svg);
  this.tooltip_group = _f4u$t.make_g(this.svg, this.svg,'faust_tooltip_group');
  this.make_delayed_tooltips(this.svg);
  // if there is no constrain, the viewport needs to be scaled
  var viewport_dims = this.lm.dims();
  _f4u$t.configure_svg(
    this.svg,
    {
      viewBox: '0 0 '+viewport_dims[0]+' '+viewport_dims[1],
      width : this.w+'px',
      height: this.h+'px',
    },
    true);

  _f4u$t.VIEWPORT_SCALE = Math.min(this.w/viewport_dims[0], this.h/viewport_dims[1]);
}

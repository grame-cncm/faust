_f4u$t.checkbox_inits = {
  mom : null,
  d : 19,
  label : '',
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  check_fill : _f4u$t.BLACK,
  check_stroke : _f4u$t.BLACK,
  box_fill : _f4u$t.WHITE,
  box_stroke : _f4u$t.BLACK,
  init : false,
  lpadding_y : _f4u$t.TEXT_HEIGHT,
  box_padding : _f4u$t.TEXT_BOX_PADDING,
  address : ''
};

_f4u$t.button_inits = {
  mom : null,
  label : '',
  ideal_width : 80,
  ideal_height : 40,
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  fill_on : _f4u$t.PINK,
  fill_off : _f4u$t.GREEN,
  stroke : _f4u$t.BLACK,
  baseline_skip : 5,
  address : ''
};

_f4u$t.rbutton_inits = {
  mom : null,
  ir : 50,
  mr : 25,
  a0 : 180,
  sweep : 180,
  sp : 0.1,
  label : '',
  unit : null,
  min : 0,
  max : 100,
  init : 50,
  step : 1,
  integer : false,
  ndec : 0,
  lpadding_y : _f4u$t.TEXT_HEIGHT,
  box_padding : _f4u$t.TEXT_BOX_PADDING,
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  joint_fill : _f4u$t.PALEGREEN,
  knob_fill : _f4u$t.GREY,
  joint_stroke : _f4u$t.BLACK,
  knob_stroke : _f4u$t.BLACK,
  value_box_w : _f4u$t.VALUE_BOX_W,
  value_box_h : _f4u$t.VALUE_BOX_H,
  address : ''
}

_f4u$t.slidingobject_inits = {
  mom : null,
  axis : _f4u$t.X_AXIS,
  girth : 40,
  length : 200,
  label : '',
  unit : null,
  min : 0,
  max : 100,
  init : 50,
  step : 1,
  integer : false,
  ndec : 0,
  lpadding_y : _f4u$t.TEXT_HEIGHT,
  box_padding : _f4u$t.TEXT_BOX_PADDING,
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  value_box_w : _f4u$t.VALUE_BOX_W,
  value_box_h : _f4u$t.VALUE_BOX_H,
  address :  '',
  type : ''
};

_f4u$t.slider_inits = $.extend(true, {}, _f4u$t.slidingobject_inits);
_f4u$t.slider_inits.sp = 0.15;
_f4u$t.slider_inits.joint_fill = _f4u$t.PINK;
_f4u$t.slider_inits.knob_fill = _f4u$t.GREY;
_f4u$t.slider_inits.joint_stroke = _f4u$t.BLACK;
_f4u$t.slider_inits.knob_stroke = _f4u$t.BLACK;

_f4u$t.hslider_inits = $.extend(true, {}, _f4u$t.slider_inits);
_f4u$t.vslider_inits = $.extend(true, {}, _f4u$t.slider_inits);

_f4u$t.bargraph_inits = $.extend(true, {}, _f4u$t.slidingobject_inits);
_f4u$t.bargraph_inits.joint_fill = _f4u$t.CYAN;
_f4u$t.bargraph_inits.meter_fill = _f4u$t.GREY;
_f4u$t.bargraph_inits.joint_stroke = _f4u$t.BLACK;
_f4u$t.bargraph_inits.meter_stroke = _f4u$t.BLACK;

_f4u$t.hbargraph_inits = $.extend(true, {}, _f4u$t.bargraph_inits);
_f4u$t.vbargraph_inits = $.extend(true, {}, _f4u$t.bargraph_inits);

_f4u$t.init_prop = function(instance, options, obj, prop) {
  instance[prop] = _f4u$t.initifnull(options[prop], _f4u$t[obj+'_inits'][prop]);
}

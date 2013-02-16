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
  fill_on : "url(#buttonDownGradient)",
  fill_off : "url(#buttonUpGradient)",
  stroke : _f4u$t.GREY,
  baseline_skip : 5,
  address : ''
};

_f4u$t.rbutton_inits = {
  mom : null,
  ir : 50,
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
  groove_fill : _f4u$t.PALEGREEN,
  handle_fill : _f4u$t.GREY,
  groove_stroke : _f4u$t.BLACK,
  handle_stroke : _f4u$t.BLACK,
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
_f4u$t.slider_inits.groove_fill = 'red';
_f4u$t.slider_inits.groove_stroke = _f4u$t.BLACK;
_f4u$t.slider_inits.handle_stroke = _f4u$t.BLACK;

_f4u$t.hslider_inits = $.extend(true, {}, _f4u$t.slider_inits);
_f4u$t.hslider_inits.handle_fill = 'url(#horizontalSliderHandleGradient)';
_f4u$t.vslider_inits = $.extend(true, {}, _f4u$t.slider_inits);
_f4u$t.vslider_inits.handle_fill = 'url(#verticalSliderHandleGradient)';

_f4u$t.bargraph_inits = $.extend(true, {}, _f4u$t.slidingobject_inits);
_f4u$t.bargraph_inits.groove_fill = _f4u$t.CYAN;
_f4u$t.bargraph_inits.meter_fill = _f4u$t.GREY;
_f4u$t.bargraph_inits.groove_stroke = _f4u$t.BLACK;
_f4u$t.bargraph_inits.meter_stroke = _f4u$t.BLACK;

_f4u$t.hbargraph_inits = $.extend(true, {}, _f4u$t.bargraph_inits);
_f4u$t.vbargraph_inits = $.extend(true, {}, _f4u$t.bargraph_inits);

_f4u$t.nentry_inits = {
  mom : null,
  ideal_width : _f4u$t.VALUE_BOX_W,
  ideal_height : _f4u$t.VALUE_BOX_H,
  label : '',
  unit : null,
  min : 0,
  max : 100,
  init : 50,
  step : 1,
  integer : false,
  ndec : 0,
  button_fill : _f4u$t.GREY,
  operation_fill : _f4u$t.BLACK,
  button_stroke : _f4u$t.BLACK,
  operation_stroke : _f4u$t.BLACK,
  padding : 1,
  lpadding_y : _f4u$t.TEXT_HEIGHT,
  box_padding : _f4u$t.TEXT_BOX_PADDING,
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  value_box_w : _f4u$t.VALUE_BOX_W,
  value_box_h : _f4u$t.VALUE_BOX_H,
  type : 'nentry',
  address : ''
}

_f4u$t.linear_gradient_inits = {
  buttonDownGradient :
    {
      stops : [['0%', '#404040', 1],['100%', '#B0B0B0', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "0%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  buttonUpGradient :
    {
      stops : [['0%', '#B0B0B0', 1],['100%', '#404040', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  groupBoxGradient :
    {
      stops : [['0%', '#A0A0A0', 1],['100%', '#202020', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  verticalSliderHandleGradient :
    {
      stops : [['0%', '#AAAAAA', 1], ['5%' ,'#0A0A0A', 1], ['30%','#101010', 1], ['90%','#AAAAAA', 1], ['91%','#000000', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "0%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  horizontalSliderHandleGradient :
    {
      stops : [['0%', '#AAAAAA', 1], ['5%' ,'#0A0A0A', 1], ['30%','#101010', 1], ['90%','#AAAAAA', 1], ['91%','#000000', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "0%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    }
}

_f4u$t.init_prop = function(instance, options, obj, prop) {
  instance[prop] = _f4u$t.initifnull(options[prop], _f4u$t[obj+'_inits'][prop]);
}

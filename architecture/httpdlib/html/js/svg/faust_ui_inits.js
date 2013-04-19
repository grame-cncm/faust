_f4u$t.checkbox_inits = {
  mom : null,
  d : 19,
  label : '',
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  stretchable : _f4u$t.faux,
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
  stretchable : _f4u$t.faux,
  ideal_width : 80,
  ideal_height : 40,
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  fill_on : "url(#buttonDownGradient)",
  fill_off : "url(#buttonUpGradient)",
  stroke : _f4u$t.GREY,
  baseline_skip : 5,
  address : ''
};

_f4u$t.tgroup_inits = {
  stretchable : _f4u$t.vrai, // needs to be function
  fill_on : "url(#tabDownGradient)", // for now use the button gradient
  fill_off : "url(#tabUpGradient)" // for now use the button gradient
};

_f4u$t.vgroup_inits = {
  stretchable : _f4u$t.vrai // needs to be function
};

_f4u$t.hgroup_inits = {
  stretchable : _f4u$t.vrai // needs to be function
};

_f4u$t.rbutton_inits = {
  mom : null,
  //ir : 50,
  ir : 30,
  a0 : 135,
  sweep : 270,
  sp : 0.9,
  kp : 0.7,
  label : '',
  unit : null,
  min : 0,
  max : 100,
  init : 50,
  step : 1,
  integer : false,
  ndec : 0,
  stretchable : _f4u$t.faux,
  lpadding_y : _f4u$t.TEXT_HEIGHT,
  box_padding : _f4u$t.TEXT_BOX_PADDING,
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  meter_fill : 'rgb(50,50,50)',
  mgroove_fill : 'url(#rotatingButtonMeterGradient)',
  groove_fill : 'url(#rotatingButtonHandleGradient)',
  handle_fill : 'none',
  mgroove_stroke : _f4u$t.BLACK,
  groove_stroke : _f4u$t.BLACK,
  handle_stroke : _f4u$t.WHITE,
  meter_stroke : _f4u$t.BLACK,
  handle_width : 6,
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
  stretchable : _f4u$t.vrai,
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
_f4u$t.hslider_inits.meter_fill = 'url(#horizontalSliderMeterGradient)';
_f4u$t.vslider_inits = $.extend(true, {}, _f4u$t.slider_inits);
_f4u$t.vslider_inits.handle_fill = 'url(#verticalSliderHandleGradient)';
_f4u$t.vslider_inits.meter_fill = 'url(#verticalSliderMeterGradient)';

_f4u$t.bargraph_inits = $.extend(true, {}, _f4u$t.slidingobject_inits);
_f4u$t.bargraph_inits.curtain_fill = _f4u$t.BLACK;
_f4u$t.bargraph_inits.meter_fill = 'url(#barGraphMeterGradient)';
_f4u$t.bargraph_inits.curtain_stroke = _f4u$t.BLACK;
_f4u$t.bargraph_inits.meter_stroke = _f4u$t.BLACK;
_f4u$t.bargraph_inits.init = null;
_f4u$t.bargraph_inits.girth = 30;

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
  stretchable : _f4u$t.faux,
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
    },
  rotatingButtonMeterGradient :
    {
      stops : [['0%', 'rgb(255,255,0)', 1], ['100%', 'rgb(255,0,0)', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "0%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  horizontalSliderMeterGradient :
    {
      stops : [['0%', 'rgb(255,255,0)', 1], ['100%', 'rgb(255,0,0)', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "0%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  verticalSliderMeterGradient :
    {
      stops : [['0%', 'rgb(255,0,0)', 1], ['100%', 'rgb(255,255,0)', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "0%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
/*
  tabUpGradient :
    {
      stops : [['0%', '#909090', 1], ['40%' ,'#888888', 1], ['50%','#808080', 1], ['100%','#909090', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "0%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  tabDownGradient :
    {
      stops : [['0%', '#909090', 1], ['40%' ,'#888888', 1], ['50%','#808080', 1], ['100%','#909090', 1]],
      x1 : "0%",
      y1 : "100%",
      x2 : "0%",
      y2 : "0%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
*/
  tabDownGradient :
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
  tabUpGradient :
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
  numericalEntryDownGradient :
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
  numericalEntryUpGradient :
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
  horizontalBarGraphMeterGradient :
    {
      stops : [['0%', 'rgb(0, 160, 40)', 1], ['50%', 'rgb(0, 160, 40)', 1],
               ['50%', 'rgb(160, 220, 20)', 1], ['60%', 'rgb(160, 220, 20)', 1],
               ['60%', 'rgb(220, 220, 20)', 1], ['70%', 'rgb(220, 220, 20)', 1],
               ['70%', 'rgb(240, 160, 20)', 1], ['80%', 'rgb(240, 160, 20)', 1],
               ['80%', 'rgb(240, 0, 20)', 1], ['100%', 'rgb(240, 0, 20)', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "0%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  verticalBarGraphMeterGradient :
    {
      stops : [['0%', 'rgb(240, 0, 20)', 1], ['20%', 'rgb(240, 0, 20)', 1],
               ['20%', 'rgb(240, 160, 20)', 1], ['30%', 'rgb(240, 160, 20)', 1],
               ['30%', 'rgb(220, 220, 20)', 1], ['40%', 'rgb(220, 220, 20)', 1],
               ['40%', 'rgb(160, 220, 20)', 1], ['50%', 'rgb(160, 220, 20)', 1],
               ['80%', 'rgb(0, 160, 40)', 1], ['100%', 'rgb(0, 160, 40)', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "0%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    }
}

_f4u$t.radial_gradient_inits = {
  rotatingButtonHandleGradient :
    {
      stops : [['0%', 'rgb(255,255,255)', 0.8],['100%', 'rgb(110,110,110)', 1]],
      cx : "40%",
      cy : "35%",
      r : "50%",
      fx : "40%",
      fy : "20%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    }
}

_f4u$t.init_prop = function(instance, options, obj, prop) {
  instance[prop] = _f4u$t.initifnull(options[prop], _f4u$t[obj+'_inits'][prop]);
}

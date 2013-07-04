Customizing the Web UI
======================

The Web UI has a built-in customization system that allows users to specify
the look of certain objects in the interface.  This spefication can take one
of three forms:

- The inclusion of external CSS files
- The inclusion of external JavaScript files
- The specification of parameters in the URL

External CSS files
------------------

External CSS files can be used to style the Faust Web UI by setting the css
argument in the url.  For example, to include the CSS file
``http://www.ensemble101.fr/foo.css`` on the previously mentioned application,
one would use the link::

  http://www.ensemble101.fr:8000/#css=http://www.ensemble101.fr/foo.css

The css argument can be specified multiple times for multiple CSS files.

Below is a list of all customizable CSS parameters for all objects. Information
on all of these parameters, as well as information on SVG CSS, can be found on
http://www.w3.org/TR/SVG/styling.html.

* Clipping, Masking and Compositing properties

  * opacity

* Color and Painting properties

  * color-profile
  * color-rendering
  * fill
  * fill-opacity
  * fill-rule
  * stroke
  * stroke-dasharray
  * stroke-dashoffset
  * stroke-linecap
  * stroke-linejoin
  * stroke-miterlimit
  * stroke-opacity
  * stroke-width

* Font properties

  * font
  * font-family
  * font-size
  * font-size-adjust
  * font-stretch
  * font-style
  * font-variant
  * font-weight

* Text properties

  * text-rendering
  * alignment-baseline
  * baseline-shift
  * dominant-baseline
  * glyph-orientation-horizontal
  * glyph-orientation-vertical
  * kerning
  * text-anchor
  * writing-mode
  * direction
  * letter-spacing
  * text-decoration
  * unicode-bidi
  * word-spacing

None of these parameters are set by default, as all of them are set dynamically
in the DOM via JavaScript as described below. However, customized CSS will
take precedence over JavaScript when set.

Below is a list of all faust objects with sublists indicating the CSS
classes that compose the objects as well as the meaning of the class.

Rotating Button
^^^^^^^^^^^^^^^
==================================   ===================================================
Class name                           Description                        
==================================   ===================================================
faust-rbutton-joint                  The "joint" in which a rotating button rotates.
faust-rbutton-knob                   The "knob" that does the actual rotating.
==================================   ===================================================

Slider (both horizontal and vertical)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
==================================   ===================================================
Class name                           Description                        
==================================   ===================================================
faust-slider-joint                   The "joint" in which a slider slides.
faust-slider-knob                    The "knob" that does the actual sliding.
==================================   ===================================================

Bar Graph (both horizontal and vertical)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
==================================   ========================================================
Class name                           Description                        
==================================   ========================================================
faust-bargraph-joint                 The "joint" in which a bar graph moves.
faust-bargraph-knob                  The "meter" that does the actual showing of information.
==================================   ========================================================

Checkbox
^^^^^^^^
==================================   ===================================================
Class name                           Description                        
==================================   ===================================================
faust-checkbox-box                   The box of a checkbox.
faust-checkbox-check                 The check of a checkbox.
==================================   ===================================================

Button
^^^^^^
==================================   ===================================================
Class name                           Description                        
==================================   ===================================================
faust-button-box                     The box of a button.
faust-button-text                    Text of a button.
==================================   ===================================================

Numerical Entry
^^^^^^^^^^^^^^^
==================================   ===================================================
Class name                           Description                        
==================================   ===================================================
faust-nentry-operation               The operation sign (plus/minus) of a numerical entry.
faust-nentry-button                  The button on which the operation signs appear.
==================================   ===================================================

Value Box
^^^^^^^^^
==================================   ===================================================
Class name                           Description                        
==================================   ===================================================
faust-button-box                     The box of a value box.
faust-button-text                    Number of a value box.
==================================   ===================================================

Layout Manager (both horizontal and vertical)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
==================================   ===================================================
Class name                           Description                        
==================================   ===================================================
faust-group-background               The background of a layout manager.
faust-group-label                    The label of a layout manager.
==================================   ===================================================

Tab Group
^^^^^^^^^
==================================   ===================================================
Class name                           Description                        
==================================   ===================================================
faust-tgroup-tab                     A tab of a tab group.
faust-tgroup-label                   A label of a tab in a tab group.
==================================   ===================================================

Below is a model CSS file setting several of the classes above ::

  .faust-slider-joint {opacity:0.2;}
  .faust-rbutton-knob {stroke-linecap:percentage;}
  .faust-tgroup-label {font-weight:bold;}

External JS files
-----------------

As the CSS specification only allows the customization of parameters in the
specification and disallows customized parameters, faust-specific parameters
must be specified via JavaScript.  There are numerous parameters one can
control: the width of sliders, the girth of a rotating button's knob, and
the height of a button, for example, can all be controlled via JavaScript.
This is also true of more "traditional" parameters such as fill color.
Where there is overlap in things that can be specified in both JS and CSS
(fill and stroke, for example), the CSS will, if specified, take priority.

Often times, a customizable parameter can be set that will interfere with the
normal display of faust information. For example, one can specify the text
of all checkbox labels, but this would interfere with the labels specified
by the server.  Therefore, in the tables below, there is a "Touch?" parameter
that, when specified as "No", means that it should not be tinkered with.

External JS files can be used to style the Faust Web UI by setting the js
argument in the url.  For example, to include the JS file
``http://www.ensemble101.fr/foo.js`` on the previously mentioned application,
one would use the link::

  http://www.ensemble101.fr:8000/#js=http://www.ensemble101.fr/foo.js

The js argument can be specified multiple times for multiple JS files.

Below is a list of all faust objects with sublists indicating the JS
variables that may be set as well as the meaning of these variables.

Rotating Button
^^^^^^^^^^^^^^^
==================================   ==============================================   ======   ==============================
Property name                        Description                                      Touch?   Default
==================================   ==============================================   ======   ==============================
_f4u$t.rbutton_inits.mom             Parent widget of the object                      No       null
_f4u$t.rbutton_inits.label           Label of the object                              No       null
_f4u$t.rbutton_inits.ir              The ideal radius of the button                   Yes      50
_f4u$t.rbutton_inits.a0              The angle from which the button starts           Yes      180
_f4u$t.rbutton_inits.sweep           The degrees that the button sweeps               Yes      180
_f4u$t.rbutton_inits.sp              The fraction of the sweep taken up by the knob   Yes      0.1
_f4u$t.rbutton_inits.unit            Units of the button                              No       null
_f4u$t.rbutton_inits.min             Min value of the button                          No       0
_f4u$t.rbutton_inits.max             Max value of the button                          No       100
_f4u$t.rbutton_inits.init            Initial value of the button                      No       50
_f4u$t.rbutton_inits.step            Step over the range                              No       1
_f4u$t.rbutton_inits.integer         True of the initial value is an integer          No       false
_f4u$t.rbutton_inits.ndec            Number of decimal places to show                 No       0
_f4u$t.rbutton_inits.lpadding_y      Padding between text box and label               Yes      _f4u$t.TEXT_HEIGHT
_f4u$t.rbutton_inits.box_padding     Padding between object and text box              Yes      _f4u$t.TEXT_BOX_PADDING
_f4u$t.rbutton_inits.gravity         X,Y placement in the parent widget               Yes      [_f4u$t.CENTER _f4u$t.CENTER]
_f4u$t.rbutton_inits.joint_fill      Fill of the joint                                Yes      _f4u$t.PALEGREEN
_f4u$t.rbutton_inits.knob_fill       Fill of the knob                                 Yes      _f4u$t.GREY
_f4u$t.rbutton_inits.joint_stroke    Stroke of the joint                              Yes      _f4u$t.BLACK
_f4u$t.rbutton_inits.knob_stroke     Stroke of the knob                               Yes      _f4u$t.BLACK
_f4u$t.rbutton_inits.value_box_w     Width of the value box                           Yes      _f4u$t.VALUE_BOX_W
_f4u$t.rbutton_inits.value_box_h     Height of the value box                          Yes      _f4u$t.VALUE_BOX_H
_f4u$t.rbutton_inits.address         Address on the server                            No       null
==================================   ==============================================   ======   ==============================

Slider
^^^^^^
==================================   ===============================================   ======   ==============================
Property name                        Description                                       Touch?   Default
==================================   ===============================================   ======   ==============================
_f4u$t.slider_inits.mom              Parent widget of the object                       No       null
_f4u$t.slider_inits.label            Label of the object                               No       null
_f4u$t.slider_inits.axis             Orientation of the object                         No       _f4u$t.X_AXIS
_f4u$t.slider_inits.girth            Width of the object                               Yes      40
_f4u$t.slider_inits.length           Length of the object                              Yes      200
_f4u$t.slider_inits.sp               The fraction of the slider taken up by the knob   Yes      0.1
_f4u$t.slider_inits.unit             Units of the slider                               No       null
_f4u$t.slider_inits.min              Min value of the button                           No       0
_f4u$t.slider_inits.max              Max value of the button                           No       100
_f4u$t.slider_inits.init             Initial value of the button                       No       50
_f4u$t.slider_inits.step             Step over the range                               No       1
_f4u$t.slider_inits.integer          True of the initial value is an integer           No       false
_f4u$t.slider_inits.ndec             Number of decimal places to show                  No       0
_f4u$t.slider_inits.lpadding_y       Padding between text box and label                Yes      _f4u$t.TEXT_HEIGHT
_f4u$t.slider_inits.box_padding      Padding between object and text box               Yes      _f4u$t.TEXT_BOX_PADDING
_f4u$t.slider_inits.gravity          X,Y placement in the parent widget                Yes      [_f4u$t.CENTER _f4u$t.CENTER]
_f4u$t.slider_inits.joint_fill       Fill of the joint                                 Yes      _f4u$t.PALEGREEN
_f4u$t.slider_inits.knob_fill        Fill of the knob                                  Yes      _f4u$t.GREY
_f4u$t.slider_inits.joint_stroke     Stroke of the joint                               Yes      _f4u$t.BLACK
_f4u$t.slider_inits.knob_stroke      Stroke of the knob                                Yes      _f4u$t.BLACK
_f4u$t.slider_inits.value_box_w      Width of the value box                            Yes      _f4u$t.VALUE_BOX_W
_f4u$t.slider_inits.value_box_h      Height of the value box                           Yes      _f4u$t.VALUE_BOX_H
_f4u$t.slider_inits.address          Address on the server                             No       null
==================================   ===============================================   ======   ==============================

In order to customize horizontal and vertical sliders individually, the
properties above may be set by adding v or h before slider (i.e. _f4u$t.vslider_inits.joint_stroke).

Bar Graph
^^^^^^^^^
==================================     ===============================================   ======   ==============================
Property name                          Description                                       Touch?   Default
==================================     ===============================================   ======   ==============================
_f4u$t.bargraph_inits.mom              Parent widget of the object                       No       null
_f4u$t.bargraph_inits.label            Label of the object                               No       null
_f4u$t.bargraph_inits.axis             Orientation of the object                         No       _f4u$t.X_AXIS
_f4u$t.bargraph_inits.girth            Width of the object                               Yes      40
_f4u$t.bargraph_inits.length           Length of the object                              Yes      200
_f4u$t.bargraph_inits.unit             Units of the slider                               No       null
_f4u$t.bargraph_inits.min              Min value of the button                           No       0
_f4u$t.bargraph_inits.max              Max value of the button                           No       100
_f4u$t.bargraph_inits.init             Initial value of the button                       No       50
_f4u$t.bargraph_inits.step             Step over the range                               No       1
_f4u$t.bargraph_inits.integer          True of the initial value is an integer           No       false
_f4u$t.bargraph_inits.ndec             Number of decimal places to show                  No       0
_f4u$t.bargraph_inits.lpadding_y       Padding between text box and label                Yes      _f4u$t.TEXT_HEIGHT
_f4u$t.bargraph_inits.box_padding      Padding between object and text box               Yes      _f4u$t.TEXT_BOX_PADDING
_f4u$t.bargraph_inits.gravity          X,Y placement in the parent widget                Yes      [_f4u$t.CENTER _f4u$t.CENTER]
_f4u$t.bargraph_inits.joint_fill       Fill of the joint                                 Yes      _f4u$t.PALEGREEN
_f4u$t.bargraph_inits.meter_fill       Fill of the meter                                 Yes      _f4u$t.GREY
_f4u$t.bargraph_inits.joint_stroke     Stroke of the joint                               Yes      _f4u$t.BLACK
_f4u$t.bargraph_inits.meter_stroke     Stroke of the meter                               Yes      _f4u$t.BLACK
_f4u$t.bargraph_inits.value_box_w      Width of the value box                            Yes      _f4u$t.VALUE_BOX_W
_f4u$t.bargraph_inits.value_box_h      Height of the value box                           Yes      _f4u$t.VALUE_BOX_H
_f4u$t.bargraph_inits.address          Address on the server                             No       null
==================================     ===============================================   ======   ==============================

In order to customize horizontal and vertical bar graphs individually, the
properties above may be set by adding v or h before bar graph (i.e. _f4u$t.vbargraph_inits.joint_stroke).

Numerical Entry
^^^^^^^^^^^^^^^
====================================     ===============================================   ======   ==============================
Property name                            Description                                       Touch?   Default
====================================     ===============================================   ======   ==============================
_f4u$t.nentry_inits.mom                  Parent widget of the object                       No       null
_f4u$t.nentry_inits.label                Label of the object                               No       null
_f4u$t.nentry_inits.length               Length of the object                              Yes      200
_f4u$t.nentry_inits.unit                 Units of the slider                               No       null
_f4u$t.nentry_inits.min                  Min value of the button                           No       0
_f4u$t.nentry_inits.max                  Max value of the button                           No       100
_f4u$t.nentry_inits.init                 Initial value of the button                       No       50
_f4u$t.nentry_inits.step                 Step over the range                               No       1
_f4u$t.nentry_inits.integer              True of the initial value is an integer           No       false
_f4u$t.nentry_inits.ndec                 Number of decimal places to show                  No       0
_f4u$t.nentry_inits.lpadding_y           Padding between text box and label                Yes      _f4u$t.TEXT_HEIGHT
_f4u$t.nentry_inits.box_padding          Padding between object and text box               Yes      _f4u$t.TEXT_BOX_PADDING
_f4u$t.nentry_inits.padding              Padding around an operation in a button           Yes      _f4u$t.TEXT_BOX_PADDING
_f4u$t.nentry_inits.gravity              X,Y placement in the parent widget                Yes      [_f4u$t.CENTER _f4u$t.CENTER]
_f4u$t.nentry_inits.operation_fill       Fill of the operation symbol                      Yes      _f4u$t.PALEGREEN
_f4u$t.nentry_inits.button_fill          Fill of the operation button                      Yes      _f4u$t.GREY
_f4u$t.nentry_inits.operation_stroke     Stroke of the operation symbol                    Yes      _f4u$t.BLACK
_f4u$t.nentry_inits.button_stroke        Stroke of the operation button                    Yes      _f4u$t.BLACK
_f4u$t.nentry_inits.value_box_w          Width of the value box                            Yes      _f4u$t.VALUE_BOX_W
_f4u$t.nentry_inits.value_box_h          Height of the value box                           Yes      _f4u$t.VALUE_BOX_H
_f4u$t.nentry_inits.address              Address on the server                             No       null
====================================     ===============================================   ======   ==============================

Checkbox
^^^^^^^^
==================================   ===================================  ======  ==============================
Property name                        Description                          Touch?  Default
==================================   ===================================  ======  ==============================
_f4u$t.checkbox_inits.mom            Parent widget of the object          No      null
_f4u$t.checkbox_inits.label          Label of the object                  No      null
_f4u$t.checkbox_inits.d              Dimension                            Yes     19
_f4u$t.checkbox_inits.gravity        X,Y placement in the parent widget   Yes     [_f4u$t.CENTER, _f4u$t.CENTER]
_f4u$t.checkbox_inits.check_fill     Fill of the check                    Yes     _f4u$t.BLACK
_f4u$t.checkbox_inits.check_stroke   Stroke of the check                  Yes     _f4u$t.BLACK
_f4u$t.checkbox_inits.box_fill       Fill of the box                      Yes     _f4u$t.WHITE
_f4u$t.checkbox_inits.box_stroke     Stroke of the box                    Yes     _f4u$t.BLACK
_f4u$t.checkbox_inits.init           Initial value of the checkbox        No      false
_f4u$t.checkbox_inits.lpadding_y     Padding between object and label     Yes     _f4u$t.TEXT_HEIGHT
_f4u$t.checkbox_inits.address        Address on the server                No      null
==================================   ===================================  ======  ==============================

Button
^^^^^^
===================================  ======================================  ======  ==============================
Property name                        Description                             Touch?  Default
===================================  ======================================  ======  ==============================
_f4u$t.button_inits.mom              Parent widget of the object             No      null
_f4u$t.button_inits.label            Label of the object                     No      null
_f4u$t.button_inits.ideal_width      Ideal width [#f1]_                      Yes     80
_f4u$t.button_inits.ideal_height     Ideal height [#f1]_                     Yes     40
_f4u$t.button_inits.gravity          X,Y placement in the parent widget      Yes     [_f4u$t.CENTER _f4u$t.CENTER]
_f4u$t.button_inits.fill_on          Fill when the button is on              Yes     _f4u$t.PINK
_f4u$t.button_inits.fill_off         Fill when the button is off             Yes     _f4u$t.GREEN
_f4u$t.button_inits.stroke           Stroke of the button box                Yes     _f4u$t.BLACK
_f4u$t.button_inits.baseline_skip    Gap between bottom of button and label  Yes     5
_f4u$t.button_inits.address          Address on the server                   No      null
===================================  ======================================  ======  ==============================

Below is a model JS file setting several of the variables above ::

  _f4u$t.button_inits.stroke = _f4u$t.BLACK;
  _f4u$t.checkbox_inits.d = 40;
  _f4u$t.hslider_inits.sp = 0.3;

URL Parameter Specification
---------------------------

JS parameters can also be specified in the URL.  For example, the model
JS file above can be embeded in the URL as follows ::

  http://www.ensemble101.fr:8000/#button_inits.stroke=_f4u$t.BLACK&checkbox_inits.d=40&hslider_inits.sp=0.3

.. rubric:: Footnotes
.. [#f1] Ideal because it will adapt to the size of the bounded text if necessary.

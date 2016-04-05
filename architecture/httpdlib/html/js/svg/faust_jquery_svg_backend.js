// faust_jquery_svg_backend.js

_f4u$t.make_rectangle_via_rect = function(svg, parent, rf, x, y, w, h, ops) {
  return svg.rect(parent, x, y, w, h, rf, rf, ops);
}

_f4u$t.make_text = function(svg, parent, x, y, text, opts) {
  opts = opts ? opts : {};
  return svg.text(parent,x,y,text,opts);
}

_f4u$t.make_circle = function(svg, parent, cx, cy, radius, opts) {
  opts = opts ? opts : {};
  return svg.circle(parent,cx,cy,radius,opts);
}

_f4u$t.make_g = function(svg, parent, id, opts) {
  opts = opts ? opts : {};
  return svg.group(parent, id, opts);
}

_f4u$t.make_path = function(svg, parent, d, opts) {
  opts = opts ? opts : {};
  return svg.path(parent, d, opts);
}

_f4u$t.make_line = function(svg, parent, x1, y1, x2, y2, opts) {
  opts = opts ? opts : {};
  return svg.line(parent, x1, y1, x2, y2, opts);
}

_f4u$t.configure_svg = function(svg, opts, wipe) {
  svg.configure(opts, wipe ? wipe : false);
}

_f4u$t.get_svg_defs = function(svg) {
  return svg.defs();
}

_f4u$t.make_linear_gradient = function(svg, defs, gradient, stops, x1, y1, x2, y2, opts) {
  opts = opts ? opts : {};
  svg.linearGradient(defs, gradient, stops, x1, y1, x2, y2, opts);
}

_f4u$t.make_radial_gradient = function(svg, defs, gradient, stops, cx, cy, r, fx, fy, opts) {
  opts = opts ? opts : {};
  svg.radialGradient(defs, gradient, stops, cx, cy, r, fx, fy, opts);
}

_f4u$t.svg_remove = function(svg, dummy) {
  svg.remove(dummy);
}

_f4u$t.add_svg_and_onload_to_div = function(div, raw_json, width, height, hash) {
  div.svg({onLoad: function (svg) {
          _f4u$t.make_ui(svg, raw_json, width, height, hash);
          }});
}
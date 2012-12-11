// FROM http://stackoverflow.com/questions/814613/how-to-read-get-data-from-a-url-using-javascript

_f4u$t.parseURLParams = function(url) {
  //var queryStart = url.indexOf("?") + 1;
  //var queryEnd   = url.indexOf("#") + 1 || url.length + 1;
  var queryStart = url.indexOf("#") + 1;
  var queryEnd   = url.length + 1;
  var query      = url.slice(queryStart, queryEnd - 1);

  if (query === url || query === "") return;

  var params  = {};
  var nvPairs = query.replace(/\+/g, " ").split("&");

  for (var i=0; i<nvPairs.length; i++) {
    var nv = nvPairs[i].split("=");
    var n  = decodeURIComponent(nv[0]);
    var v  = decodeURIComponent(nv[1]);
    if (!(n in params)) {
      params[n] = [];
    }
    params[n].push(nv.length === 2 ? v : null);
  }
  return params;
}

_f4u$t.load_css_and_then_js_and_then_build_ui = function(css, js, svg, raw_json) {
  if (css.length == 0) {
    _f4u$t.load_js_and_then_build_ui(js, svg, raw_json);
  }
  else {
    $.ajax({
      url: css[0],
      dataType: 'css',
      success: function() {
        $('<link rel="stylesheet" type="text/css" href="'+css[0]+'" />').appendTo("head");
        _f4u$t.load_css_and_then_js_and_then_build_ui(css.slice(1), js, svg, raw_json);
      }
    });
  }
}

_f4u$t.load_js_and_then_build_ui = function(js, svg, raw_json) {
  if (js.length == 0) {
    _f4u$t.make_ui(svg, raw_json);
  }
  else {
    $.getScript(js[0], function () {
      _f4u$t.load_js_and_then_build_ui(js.slice(1), svg, raw_json);
    });
  }
}
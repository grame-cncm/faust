// FROM http://stackoverflow.com/questions/814613/how-to-read-get-data-from-a-url-using-javascript

_f4u$t.parseURLParams = function(url) {
  //var queryStart = url.indexOf("?") + 1;
  //var queryEnd   = url.indexOf("#") + 1 || url.length + 1;
  var queryStart = url.indexOf("#") + 1;
  var queryEnd   = url.length + 1;
  var query      = url.slice(queryStart, queryEnd - 1);
  var params  = {};

  if (query === url || query === "")
    return params;

  var nvPairs = query.replace(/\+/g, " ").toString().split("&");

  for (var i=0; i<nvPairs.length; i++) {
    var nv = nvPairs[i].toString().split("=");
    var n  = decodeURIComponent(nv[0]);
    var v  = decodeURIComponent(nv[1]);
    if (!(n in params)) {
      params[n] = [];
    }
    params[n].push(nv.length === 2 ? v : null);
  }
  return params;
}

_f4u$t.load_css_and_then_js = function(css, js) {
  if (!css || (css.length == 0)) {
    _f4u$t.load_js(js);
  }
  else {
    var headID = document.getElementsByTagName("head")[0];
    var cssNode = document.createElement('link');
    cssNode.type = 'text/css';
    cssNode.rel = 'stylesheet';
    cssNode.href = css[0];
    cssNode.media = 'screen';
    headID.appendChild(cssNode);
    _f4u$t.load_css_and_then_js(css.slice(1), js);
  }
}

_f4u$t.load_js = function(js) {
  if (!js || (js.length == 0)) {
    return;
  }
  else {
    $.getScript(js[0], function () {
      _f4u$t.load_js(js.slice(1));
    });
  }
}

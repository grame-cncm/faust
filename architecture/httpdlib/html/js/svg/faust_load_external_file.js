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

_f4u$t.URLParams = _f4u$t.parseURLParams(document.URL);
if (_f4u$t.URLParams) {
  if (_f4u$t.URLParams.js) {
    for (var i = 0; i < _f4u$t.URLParams.js.length; i++) {
      $.getScript(_f4u$t.URLParams.js[i]);
    }
  }
}

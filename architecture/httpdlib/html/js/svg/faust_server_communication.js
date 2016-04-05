
//-----------------------------------------------------------------------------
// handlers to send a faust 'set' message
// actually using a 'GET' method
//-----------------------------------------------------------------------------
_f4u$t.faust_server_handler = function(dest, value) {
  if (!_f4u$t.ajax_queue[dest]) {
    _f4u$t.ajax_queue[dest] = [];
  }
  _f4u$t.ajax_queue[dest].push({request : dest +"?value=" + value, time : new Date().getTime()});
}

_f4u$t.server_update_function = function(address, value) {
  // do nothing - a stub that should be overwritten in toplevel html files
}

//-----------------------------------------------------------------------------
// poll current values from the server
//-----------------------------------------------------------------------------

_f4u$t.dispatch = function(data) {
  var lines = data.toString().split('\n');
  var limit = lines.length;
  for (i=0; i < limit; i++) {
    var values = lines[i].toString().split(' ');
    if (values.length > 1) {
      var address = values[0];
      // skip things being moved to avoid interference
      if (_f4u$t.active_addresses.indexOf(address) != -1) {
        continue;
      }
      var value = Math.round(values[1]*10000)/10000;
      _f4u$t.server_update_function(address, value);
    }
  }
}

_f4u$t.ajax_queue_length = function() {
  var l = 0;
  for (var key in _f4u$t.ajax_queue) {
    for (var i = 0; i < _f4u$t.ajax_queue[key].length; i++) {
      l += 1;
    }
  }
  return l;
}

_f4u$t.ajax_queue_get_request_and_trim = function () {
  var t = Number.POSITIVE_INFINITY;
  var request = '';
  var mykey = '';
  for (var key in _f4u$t.ajax_queue) {
    for (var i = 0; i < _f4u$t.ajax_queue[key].length; i++) {
      if (_f4u$t.ajax_queue[key][i].time < t) {
        t = _f4u$t.ajax_queue[key][i].time;
        request = _f4u$t.ajax_queue[key][i].request;
        mykey = key;
      }
    }
    // always trim
    _f4u$t.ajax_queue[key] = _f4u$t.ajax_queue[key].slice(0,Math.min(5,_f4u$t.ajax_queue[key].length));
  }
  // trim first request off of successful array
  _f4u$t.ajax_queue[mykey] = _f4u$t.ajax_queue[mykey].slice(1,Math.min(5,_f4u$t.ajax_queue[key].length));
  return request;
}

// We update the user interface by polling the server every 40 ms
// But this is done only when no updates are pending for the server
_f4u$t.main_loop = function() {
  if ((_f4u$t.ajax_queue_length() > 0) || _f4u$t.ajax_queue_busy) {
    // we have pending updates to send to the server
    //_f4u$t.ajax_queue_busy = true;
    var request = _f4u$t.ajax_queue_get_request_and_trim();
    $.get(request)
      .done(function () {
        //console.log("request succeeded", request);
        _f4u$t.main_loop();
      })
      .fail(function () {
        console.log("request failed", request);
        _f4u$t.main_loop();
      });/*
      .always(function () {
        console.log("request passed", request);
      });*/
  } else {
    // regular polling
    _f4u$t.ajax_queue_busy = false;
    $.get(_f4u$t.ROOT, function(data) { _f4u$t.dispatch( data ); } );
    setTimeout ( function() { _f4u$t.main_loop(); }, 40);
  }		
}

$(document).ready(function() { _f4u$t.main_loop(); });

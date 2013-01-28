
//-----------------------------------------------------------------------------
// handlers to send a faust 'set' message
// actually using a 'GET' method
//-----------------------------------------------------------------------------
_f4u$t.fausthandler = function(dest, value) {
  if (0) {
    var msg = "$.get( " + dest +"?value=" + value + ");";
    console.log(msg);
  }
  $.get(dest +"?value=" + value);
}

//-----------------------------------------------------------------------------
// poll current values from the server
//-----------------------------------------------------------------------------

_f4u$t.update_incremental_object_value = function(address, value) {
   var id = _f4u$t.PATHS_TO_IDS[address];
  _f4u$t.dumb_label_update(_f4u$t.unique(id), value);
  _f4u$t.actualize_incremental_object(_f4u$t.unique(id));
}

_f4u$t.update_hslider_value = function(address, value) {
  _f4u$t.update_incremental_object_value(address, value);
}

_f4u$t.update_vslider_value = function(address, value) {
  _f4u$t.update_incremental_object_value(address, value);
}

_f4u$t.update_hbargraph_value = function(address, value) {
  _f4u$t.update_incremental_object_value(address, value);
}

_f4u$t.update_vbargraph_value = function(address, value) {
  _f4u$t.update_incremental_object_value(address, value);
}

_f4u$t.update_rbutton_value = function(address, value) {
  _f4u$t.update_incremental_object_value(address, value);
}

_f4u$t.update_nentry_value = function(address, value) {
   var id = _f4u$t.PATHS_TO_IDS[address];
  _f4u$t.dumb_label_update(id, value);
}

_f4u$t.update_checkbox_value = function(address, value) {
  // perhaps too much UI here?
  var id = _f4u$t.PATHS_TO_IDS[address];
  var check = document.getElementById('faust_checkbox_check_'+id);
  check.style.opacity = value;
}

_f4u$t.update_button_value = function(address, value) {
 /* do nothing */
}

_f4u$t.dispatch = function(data) {
  var lines = data.split('\n');
  var limit = lines.length;
  for (i=0; i < limit; i++) {
    var values = lines[i].split(' ');
    if (values.length > 1) {
      var address = values[0];
      var value = Math.round(values[1]*10000)/10000;
      var id = _f4u$t.PATHS_TO_IDS[address];
      var kind = _f4u$t.IDS_TO_ATTRIBUTES[id] ? _f4u$t.IDS_TO_ATTRIBUTES[id].type : null ;
      if (kind == 'vslider') { _f4u$t.update_vslider_value(address, value); }
      else if (kind == 'hslider') { _f4u$t.update_hslider_value(address, value); }
      else if (kind == 'rbutton') { _f4u$t.update_rbutton_value(address, value); }
      else if (kind == 'checkbox') { _f4u$t.update_checkbox_value(address, value); }
      else if (kind == 'button') { _f4u$t.update_button_value(address, value); }
      else if (kind == 'nentry') { _f4u$t.update_nentry_value(address, value); }
      else if (kind == 'vbargraph') { _f4u$t.update_vbargraph_value(address, value); }
      else if (kind == 'hbargraph') { _f4u$t.update_hbargraph_value(address, value); }
      else { if (0) { console.log("Unidentified Faust Object (UFO) "+id+" "+kind); }}
    }
  }
}

_f4u$t.update = function() {
  if (!_f4u$t.BUSY) {
    $.get(_f4u$t.ROOT, function(data) { _f4u$t.dispatch( data ); } );
  }
  setTimeout ( function() { _f4u$t.update(); }, 200);
}

$(document).ready(function() { _f4u$t.update(); });

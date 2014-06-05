/**
 Each audio bridge reports a callback that the listener calls with an address of
 a UI object and the value it is changing to.  The bridge is resonsible for
 using this information in a useful way (sending it to a server, to a
 JavaScript object, etc.).

@property HANDLER_CALLBACKS
@for _f4u$t
@type Array
@default []
**/
_f4u$t.HANDLER_CALLBACKS = [];

/**
 Triggers all callbacks.

@method fausthandler
@for _f4u$t
@static
@param {String} dest The destination address
@param {Number} value The value at that address.
**/

_f4u$t.fausthandler = function(dest, value) {
  for (var i = 0; i < _f4u$t.HANDLER_CALLBACKS.length; i++) {
    _f4u$t.HANDLER_CALLBACKS[i](dest, value);
  }
}

// Functions to update UI via what's happening internally in the audio
// processing.

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
  // for latency issues...seems not to do anything, so commented out
  /*if (now - _f4u$t.IDS_TO_ATTRIBUTES[id]["time"] < 2000) {
    return;
  }*/
  var check = document.getElementById('faust_checkbox_check_'+id);
  check.style.opacity = value;
}

_f4u$t.update_button_value = function(address, value) {
  var id = _f4u$t.PATHS_TO_IDS[address];
  if (value == 1) {
    _f4u$t.button_fill_changer(id, true);
  } else {
    _f4u$t.button_fill_changer(id, false);
  }
}

_f4u$t.update_value_at_address = function(address, value) {
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

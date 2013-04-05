
//-----------------------------------------------------------------------------
// handlers to send a faust 'set' message
// actually using a 'GET' method
//-----------------------------------------------------------------------------
_f4u$t.fausthandler = function(dest, value) {
  _f4u$t.ajax_queue.push(dest +"?value=" + value);
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
  var id = _f4u$t.PATHS_TO_IDS[address];
  if (value == 1) {
    _f4u$t.button_down(id);
  } else {
    _f4u$t.button_up(id);
  }
}

_f4u$t.dispatch = function(data) {
  var lines = data.split('\n');
  var limit = lines.length;
  for (i=0; i < limit; i++) {
    var values = lines[i].split(' ');
    if (values.length > 1) {
      var address = values[0];
      // skip things being moved to avoid interference
      if (_f4u$t.active_addresses.indexOf(address) != -1) {
        continue;
      }
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

// We update the user interface by polling the server every 40 ms
// But this is done only when no updates are pending for the server
_f4u$t.main_loop = function() {
	if ((_f4u$t.ajax_queue.length > 0) || _f4u$t.ajax_queue_busy) {
		// we have pending updates to send to the server
		//_f4u$t.ajax_queue_busy = true;
		var request = _f4u$t.ajax_queue[0];
		_f4u$t.ajax_queue = _f4u$t.ajax_queue.slice(1,Math.min(5,_f4u$t.ajax_queue.length));
		$.get(request).done(_f4u$t.main_loop); 
	} else {
		// regular polling
		_f4u$t.ajax_queue_busy = false;
		$.get(_f4u$t.ROOT, function(data) { _f4u$t.dispatch( data ); } );
		setTimeout ( function() { _f4u$t.main_loop(); }, 40);
	}		
}

$(document).ready(function() { _f4u$t.main_loop(); });

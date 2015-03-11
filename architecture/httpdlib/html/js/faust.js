
//-----------------------------------------------------------------------------
// handlers to send a faust 'set' message
// actually using a 'GET' method
//-----------------------------------------------------------------------------
function fausthandler(dest, value) {
	if (0) {
		var msg = "$.get( " + dest +"?value=" + value + ");";
		$("#trace").html(msg);
	}
	else $.get(dest +"?value=" + value);
}

function sliderhandler(dest, value, id) {
	fausthandler (dest, value);
	$(id).val(Math.round(value*10000)/10000);
}

//-----------------------------------------------------------------------------
// poll current values from the server
//-----------------------------------------------------------------------------
function dispatch (data) {
	var lines = data.toString().split('\n');
	var limit = lines.length;
	for (i=0; i < limit; i++) {
		var values = lines[i].toString().split(' ');
		if (values.length > 1) {
			var address = values[0];
			var value = Math.round(values[1]*10000)/10000;
			$('[name="'+address+'"]').val(value);
		}
	}
}

function update (root) {
	$.get( root, function(data) { dispatch( data ); } );
	setTimeout ( function () { update(root); }, 200);
}
$(document).ready(function() { update ($('#root').val()); });

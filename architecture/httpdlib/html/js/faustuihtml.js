
//-----------------------------------------------------------------------------
// a function to build a slider
// a faust slider is a composite object that embeds a label, a 'range' input
// and a 'text' input displaying the slider value
// slider and text value are linked together to reflect the same value.
//-----------------------------------------------------------------------------
function htmlslider(id, orientation, min, max, value, step, dest) {
	var valId="v"+id;
	var html = "<input type='range' id='" + id
		 	 + "' min=" + min + " max=" + max + " step=" + step + " value=" + value
			 + " onchange='sliderhandler(\"" + dest + "\", this.value, \"#" + valId + "\")'>";
	var text = "<input type='text' id='" + valId
			 + "' value=" + value + " size=6"
			 + " onchange='sliderhandler(\"" + dest + "\", this.value, \"#" + id + "\")'>";
	var out = new Array (html, text);
	return out;
}

//-----------------------------------------------------------------------------
// a push button
//-----------------------------------------------------------------------------
function htmlbutton(label, id, dest) {
	var html = "<button id='" + id
			 + "' onmousedown='fausthandler(\"" + dest + "\", 1)' onmouseup='fausthandler(\"" + dest + "\", 0)'>"
			 + label
			 +"</button>";
	return html;
}

//-----------------------------------------------------------------------------
// a check box
//-----------------------------------------------------------------------------
function htmlcheckbox(id, dest) {
	var html = "<input type='checkbox' id='" + id
			 + "' value=0 onchange='fausthandler(\"" + dest + "\", this.value)'>";
	return html;
}

//-----------------------------------------------------------------------------
// builds a column with an optional class name
//-----------------------------------------------------------------------------
function htmlCol (html, classname) {
	var classt = "";
	if (typeof classname != 'undefined') 
		classt = " class='" + classname + "'";
	var html = "<td" + classt + ">" + html + "</td>\n";
	return html;
}

//-----------------------------------------------------------------------------
// a simple <hr> over 'span' columns
//-----------------------------------------------------------------------------
function htmlhr (span) {
	var html = "<tr><td colspan=" + span + " class='sep'><hr/></td></tr>\n";
	return html;
}

//-----------------------------------------------------------------------------
// build a single UI element 
// the element is returned in a row
//-----------------------------------------------------------------------------
function htmlControl (elt, i, address) {
	var row 	= "<tr>";
	if (elt.type == 'button') {
		row += htmlCol ("", "label");
		row += htmlCol (htmlbutton(elt.label, "button"+i, address + elt.address), "control");
		row += htmlCol ("", "value");
	}
	else if ((elt.type == 'togglebutton') ||  (elt.type == 'checkbutton')) {
		row += htmlCol (elt.label, "label");
		row += htmlCol (htmlcheckbox("checkbox"+i, address + elt.address), "control");
		row += htmlCol ("", "value");
	}
	else if ((elt.type == 'verticalslider') ||  (elt.type == 'horizontalslider') || (elt.type == 'numentry')) {
		var slider	= htmlslider("slider"+i, 'vertical', elt.min, elt.max, elt.init, elt.step, address + elt.address);
		row += htmlCol (elt.label, "label");
		row += htmlCol (slider[0], "control");
		row += htmlCol (slider[1], "value");
 	}
 	else {
 	alert (elt.type + " " + elt.label + " " + elt.elements);
 	if (elt.elements.length > 0) {
//  		row.appendChild ( makeCol (elt.label, "group"));
// 		dest.appendChild (row);
// 		for (var j=0; j<elt.elements.length; j++) {
// 			i = htmlControl (elt.elements, i, address, dest);
// 		}
 	}
 	}
 	row += "</tr>\n";
 	var out = new Array(row, i+1);
	return out;
}

//-----------------------------------------------------------------------------
// build a faust program UI from a JSON description
//-----------------------------------------------------------------------------
function buildhtmlui (data) {
	var desc = $.parseJSON (data);
	var serial = 0;
	$("#titre").html(desc.name);
	var ui = desc.ui;
	var address = "http://"+desc.address+":"+desc.port;
	var table = "<table class='ui'>\n<tr>";
	table += htmlCol ( desc.name, "name");
	table += htmlCol ( desc.address, "url");
	table += htmlCol ( desc.port, "port");
	table += "</tr>\n" + htmlhr(3);

	for (var i=0; i<ui.length; i++) {
		var control = htmlControl (ui[i], serial, address);
		table += control[0];
		serial = control[1];
	}
	table += htmlhr(3) + "</table>\n";
//	alert(table);
	return table;
}

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
	setTimeout ( function () { update(root); }, 250);
}
$(document).ready(function() { update ($('#root').val()); });

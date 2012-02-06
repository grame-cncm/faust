
//-----------------------------------------------------------------------------
// a function to build a slider
// a faust slider is a composite object that embeds a label, a 'range' input
// and a 'text' input displaying the slider value
// slider and text value are linked together to reflect the same value.
//-----------------------------------------------------------------------------
function makeslider(id, orientation, min, max, value, step, sethandler, dest) {
	var slider = document.createElement('input');
	slider.id		= id;
	slider.type		= "range";
	slider.min		= min;
	slider.max		= max;
	slider.value 	= value;
	slider.step 	= step;

	var valId="v"+id;
	var textval = document.createElement('input');
	textval.id		= valId;
	textval.type	= "text";
	textval.value 	= value;
	textval.size	= 6;

	textval.onchange = function(){ $( "#"+id ).val( this.value ); sethandler(dest, this.value); };
	slider.onchange  = function(){ $( "#"+valId ).val( this.value ); sethandler(dest, this.value); };
	slider.fTextValue = textval;
	return slider;
}

//-----------------------------------------------------------------------------
// a push button
//-----------------------------------------------------------------------------
function makebutton(label, id, sethandler, dest) {
	var button = document.createElement('button');
	button.id		= id;
	button.type		= "button";
	button.innerHTML= label;
	button.value	= 1;
	button.onmousedown = function(){ sethandler(dest, 1); };
	button.onmouseup = function(){ sethandler(dest, 0); };
	return button;
}

//-----------------------------------------------------------------------------
// a check box
//-----------------------------------------------------------------------------
function makecheckbox(id, sethandler, dest) {
	var cbox = document.createElement('input');
	cbox.id		= id;
	cbox.type	= "checkbox";
	cbox.value	= 0;
	cbox.onchange = function(){ this.value = (this.value==1) ? 0 : 1; sethandler(dest, this.value); };
	return cbox;
}

//-----------------------------------------------------------------------------
// a handler to send a faust 'set' message
// actually using a 'GET' method
//-----------------------------------------------------------------------------
function makesethandler() {
	return function( dest, val) {
		var msg = dest+"?value="+val;
		if (0) $("#trace").html(msg);
		else $.get( dest+"?value="+val );
	};
}

function makeCol (elt, classname) {
	var col = document.createElement('td');
	if (typeof elt == 'object') {
		col.appendChild (elt);
		elt.className = classname;
	}
	else col.innerHTML = elt;
	if (typeof classname != 'undefined') 
		col.className = classname;
	return col;
}

function makehr (span) {
	var row = document.createElement('tr');
	var col = document.createElement('td');
	col.appendChild (document.createElement('hr'));
	row.appendChild (col);
	col.colSpan = span;
	return row;
}

//-----------------------------------------------------------------------------
// build a single UI element 
// the element is returned in a row
//-----------------------------------------------------------------------------
function makeControl (elt, i, address, dest) {
	var row 	= document.createElement('tr');
	if (elt.type == 'button') {
		row.appendChild ( document.createElement('td'));
		row.appendChild ( makebutton(elt.label, "button"+i, makesethandler(), address + elt.address));
		row.appendChild ( document.createElement('td'));
		dest.appendChild (row);
	}
	else if ((elt.type == 'togglebutton') ||  (elt.type == 'checkbutton')) {
		var box = makecheckbox("checkbox"+i, makesethandler(), address + elt.address);
		row.appendChild ( makeCol (elt.label, "label"));
		row.appendChild ( makeCol (box));
		row.appendChild ( document.createElement('td'));
		dest.appendChild (row);
	}
	else if ((elt.type == 'verticalslider') ||  (elt.type == 'horizontalslider') || (elt.type == 'numentry')) {
		var slider	= makeslider("slider"+i, 'vertical', elt.min, elt.max, elt.init, elt.step, 
						  makesethandler(), address + elt.address);
		row.appendChild (makeCol (elt.label, "label") );
		row.appendChild (makeCol (slider), "control" );
		row.appendChild (makeCol (slider.fTextValue), "value" );
		dest.appendChild (row);
 	}
 	else {
 	alert (elt.type + " " + elt.label + " " + elt.elements);
 	if (elt.elements.length > 0) {
 		row.appendChild ( makeCol (elt.label, "group"));
		dest.appendChild (row);
		for (var j=0; j<elt.elements.length; j++) {
			i = makeControl (elt.elements, i, address, dest);
		}
		dest.appendChild (makehr(3));
 	}
 	}
	return i+1;
}

//-----------------------------------------------------------------------------
// build a faust program UI from a JSON description
//-----------------------------------------------------------------------------
function buildui (data) {
	var desc = $.parseJSON (data);
	var serial = 0;
	$("#titre").html(desc.name);
	var ui = desc.ui;
	var address = "http://"+desc.address+":"+desc.port;
	var table = document.createElement('table');
	var row 	= document.createElement('tr');
	table.className = "ui";
	row.appendChild (makeCol (desc.name, "name") );
	row.appendChild (makeCol (desc.address, "url") );
	row.appendChild (makeCol (desc.port, "port") );
	table.appendChild (row);
	table.appendChild (makehr(3));
	for (var i=0; i<ui.length; i++) {
		serial = makeControl (ui[i], serial, address, table);
	}
	table.appendChild (makehr(3));
	return table;
}

/*				FAUSTINTERFACE.JS

	HELPER FUNCTIONS TO CREATE FAUST INTERFACES
	
	FIRST PART --> DECODE JSON ENCODED INTERFACE
	SECOND PART --> ADD GRAPHICAL OBJECTS TO INTERFACE
*/

"use strict";

/******************************************************************** 
*************************** DECODE JSON *****************************
********************************************************************/

function parse_ui(ui, node){
    for (var i = 0; i < ui.length; i++)
    	parse_group(ui[i], node);
}
    
function parse_group(group, node){ 
	if (group.items)
    	parse_items(group.items, node);
}
    
function parse_items(items, node){
	var i;
    for (i = 0; i < items.length; i++)
    	parse_item(items[i], node);
}
    
function parse_item(item, node){

	var params = node.getParams();

	if( params && params[item.address]){
		item.init = params[item.address];
	}
	
	if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup")
    	parse_items(item.items, node);

    else if (item.type === "vslider" || item.type === "hslider")
		addFaustModuleSlider(node, item.address, item.label, item.init, item.min, item.max, item.step, "", node.interfaceCallback);
		
    else if(item.type === "button")
    	addFaustButton(node, item.address, item.label, node.interfaceCallback);
    	
	else if(item.type === "checkbox")
		addFaustCheckBox(node, item.address, node.interfaceCallback);
}

function parse_items(items, node){
 	for (var i = 0; i < items.length; i++)
        parse_item(items[i], node);
}

/******************************************************************** 
********************* ADD GRAPHICAL ELEMENTS ************************
********************************************************************/

function addFaustModuleSlider( node, groupName, label, ivalue, imin, imax, stepUnits, units, onUpdate ) {

	var precision = stepUnits.toString().split('.').pop().length;

	var group = document.createElement("div");
 	group.className="control-group";
	group.label = groupName;

	var info = document.createElement("div");
	info.className="slider-info";
	info.setAttribute("min", imin );
	info.setAttribute("max", imax );
	info.setAttribute("step", stepUnits );
	info.setAttribute("precision", precision);
	var lab = document.createElement("span");
	lab.className="label";
	lab.appendChild(document.createTextNode(label));
	info.appendChild(lab);
	var val = document.createElement("span");
	val.className="value";

	var myValue = Number(ivalue).toFixed(precision);
	val.appendChild(document.createTextNode("" + myValue + " " + units));

	// cache the units type on the element for updates
	val.setAttribute("units",units);
	info.appendChild(val);

	group.appendChild(info);

	var high = (imax-imin)/stepUnits;

	var slider = document.createElement("input");
	slider.type="range";
	slider.min = 0;
	slider.max = high;
	slider.value = (ivalue-imin)/stepUnits;
	slider.step = 1;
	slider.oninput = onUpdate;
	group.appendChild(slider);

	node.getInterfaceContainer().appendChild(group);
	return slider;
}

function addFaustCheckBox( element, ivalue, onUpdate ) {
	var group = document.createElement("div");

	var checkbox = document.createElement("input");
	checkbox.type = "checkbox";
	checkbox.checked = false;
	checkbox.onchange = onUpdate;

	checkbox.id = "mycheckbox";

	var label = document.createElement('label')
	label.htmlFor = "mycheckbox";
	label.appendChild(document.createTextNode(" " + ivalue));
	
	group.appendChild(checkbox);
	group.appendChild(label);

	element.getInterfaceContainer().appendChild(group);
	return checkbox;
}

function addFaustButton( element, groupName, label, onUpdate ) {

	var group = document.createElement("div");
	group.label = groupName;

	var button = document.createElement("BUTTON");        // Create a <button> element
	button.onmouseup = onUpdate;	
	button.onmousedown = onUpdate;	
		
	var label = document.createTextNode(label);       // Create a text node
	button.appendChild(label);
	                                // Append the text to <button>
	group.appendChild(button);
	element.getInterfaceContainer().appendChild(group);
	
	return button;
}



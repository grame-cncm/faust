/*
	Faust Related Functions
		- creation/deletion of Faust Module Interface
*/

/******************************************************************** 
*******************  CREATE/DELETE FAUST INTERFACE *****************
********************************************************************/

//---- Create/Delete the interface of a DSP in the "Content" Div of the FaustDiv
function createFaustInterface(faustDiv){

	var children = faustDiv.childNodes; 
	
	var content = faustDiv;

	for(var i=0; i<children.length; i++){
		if(children && children[i].className == "content"){
			content = children[i];
			break;
		}
	}

	var title = document.createElement("h6");
	title.className = "module-title";
	title.appendChild(document.createTextNode(faustDiv.Name));
	content.appendChild(title);

	parse_ui(JSON.parse(faustDiv.DSP.json()).ui, content); 
}

//---- Delete content of a Faust Module (interface and DSP)
function deleteFaustInterface(faustDiv){
	
	var content = faustDiv;
	var children = content.childNodes;

	for(var i=0; i<children.length; i++){
		if(children && children[i].className == "content"){
			content = children[i];
			break;
		}
	}
	
	var children = content.childNodes;

	while(children.length != 0){
		content.removeChild(children[0]);
	}
}

//---- Delete Module from close button
function deleteModule() {

	var faustDiv = this.parentNode;	
	disconnectNode(faustDiv);
 	deleteFaustModule(faustDiv);	
}

/******************************************************************** 
************************  CREATE INTERFACES *************************
********************************************************************/

// INPUT AND OUTPUT CONNECTORS are placed and the more global DIV level 
function addInputOutputNodesToModule(faustDiv){
		
	if(faustDiv.DSP.getNumInputs() > 0) {
		
		var i=document.createElement("div");
		i.className="node node-input";
	    i.addEventListener( "mousedown", startDraggingConnector, true );
		i.innerHTML = "<span class='node-button'>&nbsp;</span>";
		
		faustDiv.appendChild(i);
		faustDiv.inputs = i;
	}
	
		
	if (faustDiv.DSP.getNumOutputs() > 0) {
		
		var i=document.createElement("div");
		i.className="node node-output";
	    i.addEventListener( "mousedown", startDraggingConnector, true );
		i.innerHTML = "<span class='node-button'>&nbsp;</span>";
		
		faustDiv.appendChild(i);
		faustDiv.outputs = i;
	}
    		
}

function deleteInputOutputNodesToModule(faustDiv){
	
	var children = faustDiv.childNodes;
	
	for(var i=0; i<children.length; i++){
		if(children[i].className.indexOf("node-input") >= 0)
			faustDiv.removeChild(children[i]);
		
		if(children[i].className.indexOf("node-output") >= 0)
			faustDiv.removeChild(children[i]);
	}		
}

//---- Update Slider Value
function updateFaustSlider(event, val) {
	var e = event.target;

	//TODO: yes, this is lazy coding, and fragile.
	var output = e.parentNode.children[0].children[1];

	if(output){
	// update the value text
		output.innerHTML = "" + val.toString() + " " + output.getAttribute("units");
	}

	var module = e;
	while (module && !module.classList.contains("moduleFaust"))
		module = module.parentNode;
		
	return module;
}

//---- Generic callback for Faust Interface
function faustCallback(event){

	var text = event.target.parentNode.label;
	var val = event.target.value;
	
	val = Number((event.target.value*event.target.parentNode.childNodes[0].getAttribute('step')) + Number(event.target.parentNode.childNodes[0].getAttribute('min'))).toFixed(event.target.parentNode.childNodes[0].getAttribute('precision'));

	var e = updateFaustSlider(event, val);

	if(event.target.type == "submit")
			val = window.buttonVal;

	if(window.buttonVal == 0)
		window.buttonVal = 1;
	else
		window.buttonVal = 0;

// 	Search for DSP then update the value of its parameter.
	var faustModule = event.target;
	while(faustModule && faustModule.className != "moduleFaust"){
		faustModule = faustModule.parentNode;
	}

	faustModule.DSP.setValue(text, val);
}

//-- TO DO ---> KNOW HOW TO REACT TO BUTTONS
function updateKarplus(karplus){

	karplus.update("/excitator/play", 1);

}

//------- PARSE JSON INTERFACE to create graphical interface
function parse_ui(ui, content){
    for (var i = 0; i < ui.length; i++)
    	parse_group(ui[i], content);
}
    
function parse_group(group, content){ 
	if (group.items)
    	parse_items(group.items, content);
}
    
function parse_items(items, content){
	var i;
    for (i = 0; i < items.length; i++)
    	parse_item(items[i], content);
}
    
function parse_item(item, content){

	if( content.parentNode.params && content.parentNode.params[item.address]){
		item.init = content.parentNode.params[item.address];
	}
	
	if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup")
    	parse_items(item.items, content);

    else if (item.type === "vslider" || item.type === "hslider")
		addFaustModuleSlider(content, item.address, item.label, item.init, item.min, item.max, item.step, "", faustCallback);
		
    else if(item.type === "button")
    	addFaustButton(content, item.address, item.label, faustCallback);
    	
	else if(item.type === "checkbox")
		addFaustCheckBox(content, item.address, faustCallback);
}

function parse_items(items, content){
 	for (var i = 0; i < items.length; i++)
        parse_item(items[i], content);
}

//------ CREATE GRAPHICAL ELEMENTS

function addFaustModuleSlider( element, groupName, label, ivalue, imin, imax, stepUnits, units, onUpdate ) {

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

	element.appendChild(group);
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

	element.appendChild(group);
	return checkbox;
}

function addFaustButton( element, groupName, label, onUpdate ) {

	var group = document.createElement("div");
	group.label = groupName;

	var button = document.createElement("BUTTON");        // Create a <button> element
	button.onclick = onUpdate;
// 	button.onmouseup = onUpdate;	
	
	var label = document.createTextNode(label);       // Create a text node
	button.appendChild(label);
	                                // Append the text to <button>
	group.appendChild(button);
	element.appendChild(group);
	
	return button;
}

/******************************************************************** 
****************  HANDLE SAVE AND RECALL OF DSP PARAMS **************
********************************************************************/

// Save graphical parameters of a div in an Array
function saveParams(faustDiv){

	var DSP = faustDiv.DSP;

	var paramArray = new Array();
		
	var children = faustDiv.childNodes;
		
	for(var i=0; i<children.length; i++){
		if(faustDiv.childNodes[i].className == "content"){
			
			var contentDiv = faustDiv.childNodes[i];
			var contentChildren = contentDiv.childNodes;
			
			for(var j=0; j<contentChildren.length; j++){
				if(contentDiv.childNodes[j].className == "control-group"){
				
					var text = contentDiv.childNodes[j].label;
				
					paramArray[text] = DSP.getValue(text);	
				}
			}
		}
	}
	
	faustDiv.params = paramArray;
}

function recallParams(faustDiv){

	var params = faustDiv.params;

	for (key in params)
		faustDiv.DSP.setValue(key, params[key]);
}

/******************************************************************** 
*****************  HANDLE EDITION AND RECOMPILATION *****************
********************************************************************/

function editSource(event){
	
	if(event.target){
	
		var faustDiv = event.target;

		while(faustDiv && faustDiv.className!="moduleFaust")
			faustDiv = faustDiv.parentNode;

		saveParams(faustDiv);


// REPLACING FAUST MODULE INTERFACE WITH TEXT AREA
		var content;
		
		for(var i=0; i<faustDiv.childNodes.length; i++){
			if(faustDiv.childNodes[i].className == "content"){
				 content = faustDiv.childNodes[i];
				 break;
			}
		}
		
		var children = content.childNodes;

		while(children.length != 0)
			content.removeChild(children[0]);
		
		var textArea = document.createElement("textarea");
		textArea.rows = 15;
		textArea.cols = 60;
		textArea.value = faustDiv.Source;
		content.appendChild(textArea);
				
		event.target.src = "img/enter.png";
		event.target.onclick = recompileSource;
		event.target.area = textArea;
	}
}

function recompileSource(event){

	var faustDiv = event.target;

	while(faustDiv && faustDiv.className!="moduleFaust")
		faustDiv = faustDiv.parentNode;

	var dsp_code = event.target.area.value;
	var filename = faustDiv.Name;

	updateDSPinDiv(faustDiv, filename, dsp_code);
	
	recallParams(faustDiv);
	
	event.target.src = "img/edit.png";
	event.target.onclick = editSource;
}

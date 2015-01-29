/*
	Faust Related Functions
		- creation/deletion of Faust Modules
		- creation/deletion of related interface
*/

/******************************************************************** 
**************************  DELETE ELEMENTS *************************
********************************************************************/

//---- Delete the DSP, it's connections and remove it from list
function deleteDSP(faustDiv){

	if(faustDiv)
// First disconnect the audio
		disconnectNode( faustDiv );

    var myDSP = null;             	

    for (var i = 0; i < window.myArray.length; i++) {
            				
    	if(window.myArray[i]['ID'] == faustDiv.id && window.myArray[i]['Source'] != ""){
        	
			myDSP = window.myArray[i].DSP;
            
			window.myArray.splice(i,1); // first element from index i is removed

// 	TO DO SAFELY --> FOR NOW CRASHES SOMETIMES
// 	        faust.deleteDSPInstance(myDSP);
            myDSP = null;
            				
			break;
        }	
	} 	
}

//---- Delete content of a Faust Module (interface and DSP)
function deleteFaustModuleContent(faustDiv){

	var parent = faustDiv.parentNode;

	while(parent && parent.className != "module Drop your Faust DSP in Here")
		parent = parent.parentNode;

	deleteDSP(parent);
	
	var children = faustDiv.childNodes;

	while(children.length != 0){
		faustDiv.removeChild(children[0]);
	}
}

//---- Delete an entire Faust Module (window and content)
function deleteFaustModule(faustDiv){
 
	deleteDSP(faustDiv);
	
	if(faustDiv){
	// Then delete the visual element
		faustDiv.parentNode.removeChild( faustDiv );
	}	
}

//---- Delete Module from close button
function deleteModule() {

	var faustDiv = this.parentNode;	
 	deleteFaustModule(faustDiv);	
}

//---- Delete all modules
function cleanTable(){
		    	
	while(window.myArray.length != 0)
		deleteFaustModule(document.getElementById(window.myArray[0]['ID']));
}

/******************************************************************** 
**************************  CREATE ELEMENTS *************************
********************************************************************/

//---- Create an empty Faust module
function createFaustModule(x, y){

	nodeType = 'Drop your Faust DSP in Here';
	input = true;
	output = true;

	var e=document.createElement("div");
	
	e.className="module " + nodeType;
	e.id = "module" + idX++;
	e.style.left="" + x + "px";
	e.style.top="" + y + "px";
	
	if (tempx > 700) {
		tempy += 250;
		tempx = 50;
	} else
		tempx += 250;
	if (tempy > 600)
		tempy = 100;

// 	e.setAttribute("audioNodeType", nodeType );
    e.addEventListener("mousedown", startDraggingNode,   false);
	
//	e.addEventListener( 'pointerdown', startDraggingNode, false );
	var content = document.createElement("div");
	content.className="content";
	e.appendChild(content);
	
	var title = document.createElement("h6");
	title.className = "module-title";
	title.appendChild(document.createTextNode(nodeType));
	content.appendChild(title);
	
	var close = document.createElement("a");
	close.href = "#";
	close.className = "close";
	close.onclick = deleteModule;
	e.appendChild( close );

	var header = document.createElement("footer");
	var editImg = document.createElement("img");
	editImg.src = "img/edit.png";
	editImg.onclick = editSource;

// 	var exportImg = document.createElement("img");
// 	exportImg.src = "img/export.png";
// 	exportImg.onclick = exportSource;
	
	header.appendChild(editImg);
// 	header.appendChild(exportImg);
	e.appendChild(header);

	// add the node into the soundfield
	document.getElementById("modules").appendChild(e);
	
	return(content);
}

//---- Create DSP in a specific Module (sender)
function createDSP(filename, dsp_code, sender){
			         			            
    var factory = faust.createDSPFactory(dsp_code);
	
	if (!factory) {
    	alert(faust.getErrorMessage());    
        return null;
	}
                
    var DSP = faust.createDSPInstance(factory, window.audioContext, 1024);
// 	if (DSP.getNumInputs() > 0) {
//     	activateAudioInput();
//     }
           
	_f4u$t.main_loop = function() {}

// 	Récupérer les paramètres du DSP et ajouter les bons "trucs graphiques"
	var title = document.createElement("h6");
	title.className = "module-title";
	title.appendChild(document.createTextNode(filename));
	sender.appendChild(title);
	
   	createFaustInterface(DSP, sender);
       		
// INPUT AND OUTPUT CONNECTORS are placed and the more global DIV level 
    		
    if (DSP.getNumInputs() > 0) {
		var i=document.createElement("div");
		i.className="node node-input ";
    	i.addEventListener( "mousedown", startDraggingConnector, true );
		i.innerHTML = "<span class='node-button'>&nbsp;</span>";

		sender.parentNode.appendChild(i);
		sender.parentNode.inputs = i;
	}
	
	if (DSP.getNumOutputs() > 0) {
		var i=document.createElement("div");
		i.className="node node-output";
	    i.addEventListener( "mousedown", startDraggingConnector, true );
//		i.addEventListener( 'pointerdown', startDraggingConnector, false );
		i.innerHTML = "<span class='node-button'>&nbsp;</span>";
		sender.parentNode.appendChild(i);
		sender.parentNode.outputs = i;
	}
    				                
	var myMapItem = {};
    myMapItem['ID'] = sender.parentNode.id;
    myMapItem['Name'] = filename;
   	myMapItem['DSP'] = DSP;
    myMapItem['Source'] = dsp_code;
      							
    window.myArray.push(myMapItem);

   	return DSP;		
}

/******************************************************************** 
************************  CREATE INTERFACES *************************
********************************************************************/

//---- Create the interface of a DSP in a DIV (content)
function createFaustInterface(DSP, content){

	parse_ui(JSON.parse(DSP.json()).ui, content); 
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
	while (module && !module.classList.contains("module"))
		module = module.parentNode;
		
	return module;
}

//---- Generic callback for Faust Interface
function faustCallback(event){

	var text = event.target.parentNode.label;
	var val = event.target.value;
	console.log(val);
	console.log();
	
	val = Number((event.target.value*event.target.parentNode.childNodes[0].getAttribute('step')) + Number(event.target.parentNode.childNodes[0].getAttribute('min'))).toFixed(event.target.parentNode.childNodes[0].getAttribute('precision'));
// 	console.log(val);
	var e = updateFaustSlider(event, val);

	if(event.target.type == "submit")
			val = window.buttonVal;

	if(window.buttonVal == 0)
		window.buttonVal = 1;
	else
		window.buttonVal = 0;

// 	Search for DSP then update the value of its parameter.
	for (var i = 0; i < window.myArray.length; i++) {
            			
    	if(window.myArray[i]['ID'] == e.id && window.myArray[i]['Source'] != ""){
        	window.myArray[i]['DSP'].setValue(text, val);
        	break;
        }
	}
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

	if( content.params && content.params[item.address])
		item.init = content.params[item.address];

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
***********************  HANDLE DRAG AND DROP ***********************
********************************************************************/

//-- Prevent Defaul Action of the browser from happening
function preventDefaultAction(e) {
    e.preventDefault();
}

//-- Upload content dropped on the page and create a Faust DSP with it
function uploadFile(e) {
    
	if (!e)
    	e = window.event;
	
  	preventDefaultAction(e);
  	
	var sender = e.srcElement || e.target;

	while (sender && sender.className != "content")
    	sender = sender.parentNode;

	var newContainer=false;

// In case the file is not dropped on an existing module, it is created
  	if(sender == null){
  		newContainer=true;
  		sender = createFaustModule(tempx, tempy);
 	}
 
	// Remove any existing content
    deleteFaustModuleContent(sender);
			        
    if(e.dataTransfer.getData('URL') && e.dataTransfer.getData('URL').split(':').shift() != "file"){
    	var url = e.dataTransfer.getData('URL');
		
		var filename = url.toString().split( '/' ).pop();
		filename = filename.toString().split('.').shift();
		
        var xmlhttp = new XMLHttpRequest();

	    xmlhttp.onreadystatechange=function(){
	    	if (xmlhttp.readyState==4 && xmlhttp.status==200)
    	    {
	    	    dsp_code ="process = vgroup(\"" + filename + "\",environment{" + xmlhttp.responseText + "}.process);";
//         	    dsp_code = xmlhttp.responseText;
        		// Create new DSP in div (sender)
	    		if(!createDSP(filename, dsp_code, sender) && newContainer)
	    			deleteFaustModule(sender.parentNode);
        	}
    	}
		xmlhttp.open("GET", url, false );
    	xmlhttp.send(); 
    }
    else if(e.dataTransfer.getData('URL').split(':').shift() != "file"){

		var dsp_code = e.dataTransfer.getData('text');
	
		if(dsp_code){
	    	    dsp_code ="process = vgroup(\"" + "TEXT" + "\",environment{" + dsp_code + "}.process);";
		
			// Create new DSP in div (sender)
	    	if(!createDSP("TEXT", dsp_code, sender) && newContainer)
				deleteFaustModule(sender.parentNode);
		}		
	    else{ 
			var files = e.target.files || e.dataTransfer.files;
		
        	var file = files[0];

			if (location.host.indexOf("sitepointstatic") >= 0) return

    	    var request = new XMLHttpRequest();
			if (request.upload) {

        		var reader = new FileReader();
					
			    var ext = file.name.toString().split('.').pop();

				var filename = file.name.toString().split('.').shift();

    	    	if (ext == "dsp")
        	    	reader.readAsText(file);  

	    		reader.onloadend = function(e) {
	    	    dsp_code ="process = vgroup(\"" + filename + "\",environment{" + reader.result + "}.process);";

				// Create new DSP in div (sender)
		    		if(!createDSP(filename, dsp_code, sender) && newContainer)
						deleteFaustModule(sender.parentNode);
	    		};
			}
		}
	}
	else{
		deleteFaustModule(sender.parentNode);
		
		var msg = "Drop your file : " + e.dataTransfer.getData('URL').split('/').pop() + " directly on this page\n\nOr load your HTML page on a server";
		window.alert(msg);
	}

}

//-- Init drag and drop reactions
function generalDragAndDrop(){

	window.ondragover = function () { this.className = 'hover'; return false; };
 	window.ondragend = function () { this.className = ''; return false; };

	window.ondrop = function (e) {
	
		uploadFile(e);
		return true;
	};
}

/******************************************************************** 
****************  HANDLE SAVE AND RECALL OF DSP PARAMS **************
********************************************************************/

function getDSPFromDiv(div){
						
	for (var i = 0; i < window.myArray.length; i++) {    			
		if(window.myArray[i]['ID'] == div.id && window.myArray[i]['Source'] != ""){
        	return window.myArray[i]['DSP'];
        }
	}
}

// Save graphical parameters of a div in an Array
function saveParams(faustDiv){

	var DSP = getDSPFromDiv(faustDiv);

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
	
	console.log("SAVE PARAMS FROM ");
	console.log(faustDiv);
	
	faustDiv.params = paramArray;
}

function recallParams(faustDiv, params){
	var DSP = getDSPFromDiv(faustDiv);

	for (var key in params) {
		DSP.setValue(key, params[key]);
	}
}

/******************************************************************** 
*******************  HANDLE EDITION AND EXPORTATION *****************
********************************************************************/

function editSource(event){
	
	if(event.target){
	
		var faustDiv = event.target;

		while(faustDiv && faustDiv.className!="module Drop your Faust DSP in Here")
			faustDiv = faustDiv.parentNode;

		saveParams(faustDiv);

		var dsp_code;
		var filename;
		
		for (var i = 0; i < window.myArray.length; i++) {
            			
    		if(window.myArray[i]['ID'] == faustDiv.id && window.myArray[i]['Source'] != ""){
        		dsp_code = window.myArray[i]['Source'];
        		filename = window.myArray[i]['Name'];
        		break;
        	}
		} 	
		
		faustDiv = faustDiv.children[0];	
		
		var children = faustDiv.childNodes;

		while(children.length != 0){
			faustDiv.removeChild(children[0]);
		}
		
		var textArea = document.createElement("textarea");
		textArea.rows = 15;
		textArea.cols = 60;
		textArea.value = dsp_code;
		textArea.name = filename;
		faustDiv.appendChild(textArea);
				
		event.target.src = "img/enter.png";
		event.target.onclick = recompileSource;
		event.target.area = textArea;
	}
}

function recompileSource(event){

	var dsp_code = event.target.area.value;
	var filename = event.target.area.name;

	var sender = event.target;
	
	event.target.area.parentNode.removeChild(event.target.area);
	
	var faustDiv = sender.parentNode.parentNode;
		
	var outNode = getOutputNodeFromDiv(faustDiv);

	var outputConnections;
	if(outNode)
		outputConnections = getNodeOutputConnections(outNode);

	var inNode = getInputNodeFromDiv(faustDiv);
	
	var inputConnections;
	if(inNode)
		inputConnections = getNodeInputConnections(inNode);
		
	var rect = faustDiv.getBoundingClientRect();
	var	x_pos = rect.left;
	var top_pos = rect.top;
	
	var params = faustDiv.params;
	
	deleteFaustModule(faustDiv);

	faustDiv = createFaustModule(x_pos, top_pos);
	
	// Remove any existing content
    deleteFaustModuleContent(faustDiv);	

	faustDiv.params = params;
	createDSP(filename, dsp_code, faustDiv)
		
	var parent = faustDiv;
		
	while(parent && parent.className != "module Drop your Faust DSP in Here")
		parent = parent.parentNode;

	recallParams(parent, params);
	
	inNode = getInputNodeFromDiv(parent);
	outNode = getOutputNodeFromDiv(parent);
	
	setNodeInputConnections(inNode, inputConnections);
	setNodeOutputConnections(outNode, outputConnections);
	
	event.target.src = "img/edit.png";
	event.target.onclick = editSource;
	
	console.log(parent);
}

function exportSource(){

	var footer = event.target;

	var faustDiv = event.target;
	
	while(faustDiv && faustDiv.className != "module Drop your Faust DSP in Here")
		faustDiv = faustDiv.parentNode;

	var dsp_code;
		
	for (var i = 0; i < window.myArray.length; i++) {
            			
    	if(window.myArray[i]['ID'] == faustDiv.id && window.myArray[i]['Source'] != ""){
        	dsp_code = window.myArray[i]['Source'];
        	break;
        }
	}
	
	addExporter(dsp_code, footer.parentNode);
}

/******************************************************************** 
***********************  CREATE FAUST EQUIVALENT ********************
********************************************************************/

function computeNode(node){

	var nodeInputs = node.inputConnections;

	var faustResult = "";
	
// Iterate on input Nodes to compute them
	
	if(nodeInputs){
		faustResult += "(";
		for(element in nodeInputs){

			var sourceNode = nodeInputs[element]['source'];
	
			if(sourceNode){		
				if(element != 0)
					faustResult += "),(";

				faustResult += computeNode(sourceNode);
			}
		}	
		faustResult += "):> ";
	}
	
	
	var nodeCode;
	
	for(var j = 0; j<window.myArray.length; j++){
		if(node.id == window.myArray[j]['ID']){
			nodeCode = window.myArray[j]['Source'];
			break;
		}
	}
	
	if(node.id == "output")
		nodeCode = "process=_,_;";

// vgroup(\"[" + window.index + "]component" + window.index + "\", ..... )
// stereoize()


	faustResult += "stereoize(environment{" + nodeCode + "}.process)";	
	
	// window.index++;
	
	return faustResult;
}

// To avoid sharing instances of a same factory in the resulting Faust Equivalent
function wrapSourceCodesInGroups(){

	for (var i = 0; i < window.myArray.length; i++)
		window.myArray[i]['Source'] = "process = vgroup(\"component"+ i.toString() + "\",environment{" + window.myArray[i]['Source'] + "}.process);";
}

function getFaustEquivalent(){

	if(window.myArray.length != 0){
		var dest = document.getElementById("output");
// 	dest.audioNode = audioContext.destination;
	
		faustResult = "stereoize(p) = S(inputs(p), outputs(p))\n\
				with {\n\
				  // degenerated processor with no outputs\n\
				S(n,0) = !,! : 0,0; 		// just in case, probably a rare case\n\
				\n\
				  // processors with no inputs\n\
				S(0,1) = p <: _/2,_/2; 	// add two fake inputs and split output\n\
				S(0,2) = p;\n\
				S(0,n) = p,p :> _,_;	// we are sure this will work if n is odd\n\
				 \n\
				  // processors with one input\n\
				S(1,1) = p,p; 				// add two fake inputs and split output \n\
				S(1,n) = p,p :> _/2,_/2;		// we are sure this will work if n is odd\n\
				 \n\
			  // processors with two inputs\n\
				S(2,1) = p <: _,_; 			// split the output\n\
				S(2,2) = p; 				// nothing to do, p is already stereo\n\
			 \n\
			  // processors with inputs > 2 and outputs > 2\n\
			S(n,m) = _,_ <: p,p :> _,_;	// we are sure this works if n or p are odd\n\
			};\n\
			\n\
			recursivize(p,q) = (_,_,_,_ :> stereoize(p)) ~ stereoize(q);\n\
			";

		var patchName = document.getElementById("PatchName").innerHTML;
	
		faustResult += "process = vgroup(\""+ patchName + "\"," + computeNode(dest) +");";
	
		return faustResult;
	}
	else
		return null;
}

function createFaustEquivalent(){

	var patchName = document.getElementById("PatchName").innerHTML;

// Save All Params	
// 	for (var i = 0; i < window.myArray.length; i++)		
// 		saveParams(document.getElementById(window.myArray[i]['ID']));
// 	
// // Concatenate All Params
// 	var fullParams = new Array();
// 
// 	for (var i = 0; i < window.myArray.length; i++) {
// 		
// 		var arrayParams = document.getElementById(window.myArray[i]['ID']).params;
// 		
// //   BIDOUILLE!!!!! Adding component wrapping to avoid merging of 2 instances of same factory
// 		for(key in arrayParams){
// 			var newKey = "/" + patchName + "/component" + i.toString() + key;
// 			fullParams[newKey] = arrayParams[key];
// 		}
// 	}
// 
// 	wrapSourceCodesInGroups();
	
	var faustResult = getFaustEquivalent();
	
	if(faustResult){
	
		cleanTable();
			
		var divToCreate = createFaustModule(tempx, tempy);
	
	// Remove any existing content
    	deleteFaustModuleContent(divToCreate);

// Save concatenated params in new DIV
// 		divToCreate.params = fullParams;

		createDSP(patchName, faustResult, divToCreate);
	
		var parent = divToCreate;
		
		while(parent && parent.className != "module Drop your Faust DSP in Here")
			parent = parent.parentNode;
	
// 		recallParams(parent, fullParams);

		var myoutput;
// Connect Automatically to Output
		for(var i=0; i<divToCreate.parentNode.childNodes.length; i++){
			if(divToCreate.parentNode.childNodes[i].className == "node node-output"){
		
				myoutput = divToCreate.parentNode.childNodes[i];
			
				for(var j=0 ; j<document.getElementById("output").childNodes.length; j++){
					if(document.getElementById("output").childNodes[j].className && document.getElementById("output").childNodes[j].className.indexOf("node node-input")>=0){

						startDraggingConnection(myoutput);
						stopDraggingConnection(document.getElementById("output").childNodes[j]);
					}
				}
			}
		}
	}
}

function updateKarplus(karplus){

	karplus.update("/excitator/play", 1);

}

/******************************************************************** 
***************************  TESTS SCENARIOS ************************
********************************************************************/

function addBiquad(input){
	var D1 = "process = \\(x1).(x1 : +~(-1,\\(x2).((-1.862368f,x2 : *),(0.867104f,(x2 : mem) : *) : +) : *) : \\(x3).(((0.066448f,x3 : *),(0.0f,(x3 : mem) : *) : +),(-0.066448f,(x3 : mem : mem) : *) : +));";
	var myDiv =  createFaustModule(tempx, tempy)
	var mymodule = createDSP("biquad", D1, myDiv);
	
	var toReturn;
	
	for(var i=0 ; i<myDiv.parentNode.childNodes.length; i++){
		if(myDiv.parentNode.childNodes[i].className == "node node-input "){
		
			startDraggingConnection(input);
			stopDraggingConnection(myDiv.parentNode.childNodes[i]);
		}
		else if(myDiv.parentNode.childNodes[i].className == "node node-output"){
			return myDiv.parentNode.childNodes[i];
		}
	}
}

function biquadTest(){
	
	var OSC = "process = vgroup(\"Oscillator\", ((1,16 : <<),((((_,1 : +)~_,1 : - : float),(2.0f,3.141592653589793f : *) : *),(1,16 : << : float) : / : sin),(400,(192000,(1,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \\(x1).(x1,(x1 : floor) : -))~_ : _,(1,16 : << : float) : * : int) : rdtable),(-7 : \\(x2).(10,(x2,2e+01f : /) : pow) : _,(1,0.999f : -) : * : +~(_,0.999f : *)) : *);";
// 	var OSC = "process = vgroup(\"Oscillator\", ((1,16 : <<),((((_,1 : +)~_,1 : - : float),(2.0f,3.141592653589793f : *) : *),(1,16 : << : float) : / : sin),(hslider(\"freq [unit:Hz]\", 4e+02f, 2e+01f, 2.4e+04f, 1.0f),(192000,(1,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \\(x1).(x1,(x1 : floor) : -))~_ : _,(1,16 : << : float) : * : int) : rdtable),(-7 : \\(x2).(10,(x2,2e+01f : /) : pow) : _,(1,0.999f : -) : * : +~(_,0.999f : *)) : *);";
	var oscDiv = createFaustModule(tempx, tempy);
	var oscnode = createDSP("osc", OSC, oscDiv);
	
	var myInputBiquad;
	
	for(var i=0 ; i<oscDiv.parentNode.childNodes.length; i++){
		if(oscDiv.parentNode.childNodes[i].className == "node node-output"){
			myInputBiquad = oscDiv.parentNode.childNodes[i];
		}
	}
	for(var i=0; i<100; i++){
	
		var bibi = addBiquad(myInputBiquad);
		myInputBiquad = bibi;
	}
	
			
	for(var j=0 ; j<document.getElementById("output").childNodes.length; j++){
		if(document.getElementById("output").childNodes[j].className && document.getElementById("output").childNodes[j].className.indexOf("node node-input")>=0){
		
			startDraggingConnection(myInputBiquad);
			stopDraggingConnection(document.getElementById("output").childNodes[j]);
		}
	}
}

function addDelayLine(i, input, generalOutput){
	
	var delaycode = " R(d, acc, 1) = d; R(d, acc, b) = acc * R(d, acc, b-1); process = @(int(R(22050, 0.9, "+i.toString()+"))) : *(0.99) <: _,_;";
	var div = createFaustModule(tempx, tempy);
	createDSP("delay", delaycode, div);
		
	var output = null;
		
	for(var i=0 ; i<div.parentNode.childNodes.length; i++){
		if(div.parentNode.childNodes[i].className == "node node-input "){
			startDraggingConnection(input);
			stopDraggingConnection(div.parentNode.childNodes[i]);
		}
		else if(div.parentNode.childNodes[i].className == "node node-output"){
			output = div.parentNode.childNodes[i];
			
			startDraggingConnection(output);
			stopDraggingConnection(generalOutput);
		}
	}
	
	return output;
} 

function delaylinesTest(){

	var output;

	var karplus_code = "process = vgroup(\"Oscillator\", ((1,16 : <<),((((_,1 : +)~_,1 : - : float),(2.0f,3.141592653589793f : *) : *),(1,16 : << : float) : / : sin),(hslider(\"freq [unit:Hz]\", 1e+03f, 2e+01f, 2.4e+04f, 1.0f),(192000,(1,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \\(x1).(x1,(x1 : floor) : -))~_ : _,(1,16 : << : float) : * : int) : rdtable),(hslider(\"volume [unit:dB]\", -96.0f, -96.0f, 0.0f, 0.1f) : \\(x2).(10,(x2,2e+01f : /) : pow) : _,(1,0.999f : -) : * : +~(_,0.999f : *)) : *);";
// 	var karplus_code = "process=((_,12345 : +)~(_,1103515245 : *),2147483647.0f : /), 0.5 : * : vgroup(\"excitator\", _,(button(\"play\") : \\(x1).((x1,(x1 : mem) : -),0.0f : >) : +~\\(x2).(x2,((x2,0.0f : >), 128 : /) : -) : _,0.0f : >) : *) : vgroup(\"resonator\", (+ : \\(x3).(x3,((128,1.5f : - : int),(4096,1 : -) : &) : @))~(\\(x4).((x4,(x4 : mem) : +),2 : /) : _,(1.0f, 0.1 : -) : *));";

	var karM = createFaustModule(tempx, tempy);
	var mykar = createDSP("karplus", karplus_code, karM);	
// 	mykar.start();

	for(var i=0 ; i<karM.parentNode.childNodes.length; i++){
		if(karM.parentNode.childNodes[i].className == "node node-output"){
			output = karM.parentNode.childNodes[i];

// 			for(var j=0 ; j<document.getElementById("output").childNodes.length; j++){
// 				if(document.getElementById("output").childNodes[j].className == "node node-input"){
// 				
// 					startDraggingConnection(output);
// 					stopDraggingConnection(document.getElementById("output").childNodes[j]);
// // 					connectNodes(output, document.getElementById("output").childNodes[j]);	
// 				}
// 			}
		}
	}

	var generalOutput;

	var through = "process=_:>_*hslider(\"Gain\", 1, 0, 1, 0.025);";

	var throughM = createFaustModule(tempx, tempy);
	var mythrough = createDSP("gain", through, throughM);
	
	for(var i=0 ; i<throughM.parentNode.childNodes.length; i++){
		if(throughM.parentNode.childNodes[i].className == "node node-input ")
			generalOutput = throughM.parentNode.childNodes[i];
	
		else if(throughM.parentNode.childNodes[i].className == "node node-output"){
		
			var myoutput = throughM.parentNode.childNodes[i];
			
			for(var j=0 ; j<document.getElementById("output").childNodes.length; j++){
				if(document.getElementById("output").childNodes[j].className && document.getElementById("output").childNodes[j].className.indexOf("node node-input")>=0){

					startDraggingConnection(myoutput);
					stopDraggingConnection(document.getElementById("output").childNodes[j]);
				}
			}
		}
	}

	var D1 = "process = @(int(22050)) : *(0.99) <: _,_ ;";
	var D1M = createFaustModule(tempx, tempy);
	var myD1 = createDSP("delay", D1, D1M);
		
	for(var i=0 ; i<D1M.parentNode.childNodes.length; i++){
		if(D1M.parentNode.childNodes[i].className == "node node-input "){
		
			startDraggingConnection(output);
			stopDraggingConnection(D1M.parentNode.childNodes[i]);
// 			connectNodes(output, D1M.parentNode.childNodes[i]);
		}
		else if(D1M.parentNode.childNodes[i].className == "node node-output"){
		
			output = D1M.parentNode.childNodes[i];
			startDraggingConnection(output);
			stopDraggingConnection(generalOutput);
		}
	}

	output = addDelayLine(2, output, generalOutput);
	output = addDelayLine(3, output, generalOutput);
	output = addDelayLine(4, output, generalOutput);
	output = addDelayLine(5, output, generalOutput);
	output = addDelayLine(6, output, generalOutput);
	output = addDelayLine(7, output, generalOutput);
	output = addDelayLine(8, output, generalOutput);
	output = addDelayLine(9, output, generalOutput);
	output = addDelayLine(10, output, generalOutput);
	output = addDelayLine(11, output, generalOutput);
	output = addDelayLine(12, output, generalOutput);
	output = addDelayLine(13, output, generalOutput);
	output = addDelayLine(14, output, generalOutput);
	output = addDelayLine(15, output, generalOutput);
	output = addDelayLine(16, output, generalOutput);
	output = addDelayLine(17, output, generalOutput);
	output = addDelayLine(18, output, generalOutput);
	output = addDelayLine(19, output, generalOutput);
	output = addDelayLine(20, output, generalOutput);
	output = addDelayLine(21, output, generalOutput);
	output = addDelayLine(22, output, generalOutput);
	output = addDelayLine(23, output, generalOutput);
	output = addDelayLine(24, output, generalOutput);
	output = addDelayLine(25, output, generalOutput);
	output = addDelayLine(26, output, generalOutput);
	output = addDelayLine(27, output, generalOutput);
	output = addDelayLine(28, output, generalOutput);
	output = addDelayLine(29, output, generalOutput);
	output = addDelayLine(30, output, generalOutput);
	output = addDelayLine(31, output, generalOutput);
	output = addDelayLine(32, output, generalOutput);
	output = addDelayLine(33, output, generalOutput);
	output = addDelayLine(34, output, generalOutput);
	output = addDelayLine(35, output, generalOutput);
	output = addDelayLine(36, output, generalOutput);
	output = addDelayLine(37, output, generalOutput);
	output = addDelayLine(38, output, generalOutput);
	output = addDelayLine(39, output, generalOutput);
	output = addDelayLine(40, output, generalOutput);
	output = addDelayLine(41, output, generalOutput);
	output = addDelayLine(42, output, generalOutput);
	output = addDelayLine(43, output, generalOutput);
	output = addDelayLine(44, output, generalOutput);
	output = addDelayLine(45, output, generalOutput);
	output = addDelayLine(46, output, generalOutput);
	output = addDelayLine(47, output, generalOutput);
	output = addDelayLine(48, output, generalOutput);
	output = addDelayLine(49, output, generalOutput);
	output = addDelayLine(50, output, generalOutput);



//     setTimeout(updateKarplus(mykar),500);
}

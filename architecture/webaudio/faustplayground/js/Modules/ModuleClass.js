/*				MODULECLASS.JS
	HAND-MADE JAVASCRIPT CLASS CONTAINING A FAUST MODULE AND ITS INTERFACE
	
	Interface structure
	===================
	DIV --> fModuleContainer
    H6 --> fTitle
    DIV --> fInterfaceContainer
    DIV --> fCloseButton
    DIV --> fFooter
    IMG --> fEditImg
	===================
		
	DEPENDENCIES :
		- Connect.js
		- Dragging.js
		- Main.js
		- webaudio-asm-wrapper.js
*/


"use strict";

var createModule = function (ID, x, y, name, parent, callback){
	
// ---- Capturing module instance
	var that;
	
// ----- Delete Callback was added to make sure 
// ----- the module is well deleted from the scene containing it
	var deleteCallback = callback;

//------- GRAPHICAL ELEMENTS OF MODULE
	var fModuleContainer = document.createElement("div");
	fModuleContainer.className = "moduleFaust";
	fModuleContainer.id = "module" + ID;
	fModuleContainer.style.left = "" + x + "px";
	fModuleContainer.style.top = "" + y + "px";
	
	var fTitle = document.createElement("h6");
	fTitle.className = "module-title";
	fTitle.textContent = "";
	fModuleContainer.appendChild(fTitle);
	
	var fInterfaceContainer = document.createElement("div");
	fInterfaceContainer.className="content";
	fModuleContainer.appendChild(fInterfaceContainer);
    fModuleContainer.addEventListener("mousedown", dragCallback, true);
	    
	var fCloseButton = document.createElement("a");
	fCloseButton.href = "#";
	fCloseButton.className = "close";
	fCloseButton.onclick = function(){that.deleteModule();};
	fModuleContainer.appendChild( fCloseButton );

	var fFooter = document.createElement("footer");
	fFooter.id = "moduleFooter";
	
	var fEditImg = document.createElement("img");
	fEditImg.src = window.baseImg + "edit.png";
	fEditImg.onclick = function(){that.edit();};
	
	fFooter.appendChild(fEditImg);
	fModuleContainer.appendChild(fFooter);

	// add the node into the soundfield
	parent.appendChild(fModuleContainer);

//------ FIELDS OF THE MODULE
	var fDSP;
	var fName = name;
	var fSource;
	var fTempSource;
	var fTempName;
	var fParams = new Array();
	var fInputNode;
	var fOutputNode;
	
	var fOutputConnections = null;
	var fInputConnections = null;
		
/***************  PRIVATE METHODS  ******************************/

	function dragCallback(event){
	
	
		console.log("drag Callback");
		if(event.type == "mousedown")
			startDraggingModule(event, that);
		else if(event.type == "mouseup")	
			stopDraggingModule(event, that);
		else if(event.type == "mousemove")	
			whileDraggingModule(event, that);
	};
	
	function dragCnxCallback(event){
	
		console.log("drag Cnx Callback");
	
		if(event.type == "mousedown")
			startDraggingConnector(that, event);
		else if(event.type == "mouseup")
			stopDraggingConnector(that, event);
		else if(event.type == "mousemove")	
			whileDraggingConnector(that, event);
	};


//---- Redirect drop to main.js
	fModuleContainer.ondrop = function (e) {
	
		uploadOn(that, 0, 0, e);
		return true;
	};

/*******************************  PUBLIC METHODS  **********************************/
  return {
  
    deleteModule: function() {
    	disconnectModule(that);
	 	that.deleteFaustInterface();	
    
// Then delete the visual element
    	if(fModuleContainer)
			fModuleContainer.parentNode.removeChild( fModuleContainer );
			
		that.deleteDSP(fDSP);	
		deleteCallback(that);
    },
	
/*************** ACTIONS ON IN/OUTPUT NODES ***************************/
// ------ Returns Graphical input and output Node
	getOutputNode: function(){return fOutputNode;},
	getInputNode: function(){return fInputNode;},

// ------ Returns Connection Array OR null if there are none
	getInputConnections: function(){
		return fInputConnections;
	},
	getOutputConnections: function(){
		return fOutputConnections;
	},

//-- The Creation of array is only done when a new connection is added 
//-- (to be able to return null when there are none)	
	addOutputConnection: function(connector){
		if(!fOutputConnections)
			fOutputConnections = new Array();
			
		fOutputConnections.push(connector);
	},
	addInputConnection: function(connector){
	
		if(!fInputConnections)
			fInputConnections = new Array();
			
		fInputConnections.push(connector);
	},
	
	removeOutputConnection: function(connector){
		fOutputConnections.splice(fOutputConnections.indexOf(connector), 1);
	},
	removeInputConnection: function(connector){
			
		fInputConnections.splice(fInputConnections.indexOf(connector), 1);
	},
	
/********************* SHOW/HIDE MODULE IN SCENE **********************/
	showModule: function(){fModuleContainer.style.visibility = "visible";},
	hideModule: function(){ fModuleContainer.style.visibility = "hidden";},
	
/********************** GET/SET SOURCE/NAME/DSP ***********************/
	setSource: function(code){
    	fSource = code;
	},
	getSource: function(){return fSource;},

	getName: function(){return fName;},
	
	getDSP: function(){
		return fDSP;
	},
	
//--- Create and Update are called once a source code is compiled and the factory exists
	createDSP: function(factory){
	
		that = this;
	
    	fDSP = faust.createDSPInstance(factory, window.audioContext, 1024);	
	},

//--- Update DSP in module 
	updateDSP: function(factory){
	
		var toDelete = fDSP;
	
// 	Save Cnx
		var saveOutCnx = new Array().concat(fOutputConnections);
		var saveInCnx = new Array().concat(fInputConnections);
			
// Delete old Module 
		disconnectModule(that);
	
		that.deleteFaustInterface();
 		that.deleteInputOutputNodes();	
 		
 // Create new one
 	
		that.createDSP(factory);
	 	fName = fTempName;
	 	fSource = fTempSource;
		that.createFaustInterface();
		that.addInputOutputNodes();
		
		that.deleteDSP(toDelete);

// Recall Cnx
		if(saveOutCnx && that.getOutputNode()){
		
			for(var i=0; i<saveOutCnx.length; i++){
				if(saveOutCnx[i])
					createConnection(that, that.getOutputNode(), saveOutCnx[i].destination, saveOutCnx[i].destination.getInputNode());
			}
		}
		if(saveInCnx && that.getInputNode()){
			for(var i=0; i<saveInCnx.length; i++){
				if(saveInCnx[i])	
					createConnection(saveInCnx[i].source, saveInCnx[i].source.getOutputNode(), that, that.getInputNode());
			}
		}
	},
	
	deleteDSP: function(todelete){
	// 	TO DO SAFELY --> FOR NOW CRASHES SOMETIMES
// 		if(todelete)
// 		    faust.deleteDSPInstance(todelete);
	},
/******************** EDIT SOURCE & RECOMPILE *************************/
	edit: function(){

		that.saveParams();
		
		that.deleteFaustInterface();
		
		var textArea = document.createElement("textarea");
		textArea.rows = 15;
		textArea.cols = 60;
		textArea.value = fSource;
		fInterfaceContainer.appendChild(textArea);
			
		fEditImg.src = window.baseImg + "enter.png";
		fEditImg.onclick = that.recompileSource;
		fEditImg.area = textArea;
	},

//---- Update Module with new name/code source
	update: function(name, code){
	
	
		fTempName = name;
		fTempSource = code;
	
		compileFaust(name, code, x, y, that.updateDSP);
	},
	
//---- React to recompilation triggered by click on icon
	recompileSource: function(event){
	
		var dsp_code = event.target.area.value;

		that.update(fTitle.textContent, dsp_code);
		that.recallParams();
	
		fEditImg.src = window.baseImg + "edit.png";
		fEditImg.onclick = that.edit;
	},
	
/***************** CREATE/DELETE the DSP Interface ********************/

// Fill fInterfaceContainer with the DSP's Interface (--> see FaustInterface.js)
	createFaustInterface: function(){

		fTitle.textContent = fName;
		
		parse_ui(JSON.parse(fDSP.json()).ui, that); 
	},
	deleteFaustInterface: function(){
		
		while(fInterfaceContainer.childNodes.length != 0)
			fInterfaceContainer.removeChild(fInterfaceContainer.childNodes[0]);
	},
	
	getModuleContainer: function(){
		return fModuleContainer;
	},
	getInterfaceContainer: function(){
		return fInterfaceContainer;
	},

//---- Generic callback for Faust Interface
//---- Called every time an element of the UI changes value
	interfaceCallback: function(event){
	
		var text = event.target.parentNode.label;

		var val = event.target.value;
					
		val = Number((event.target.value*event.target.parentNode.childNodes[0].getAttribute('step')) + Number(event.target.parentNode.childNodes[0].getAttribute('min'))).toFixed(event.target.parentNode.childNodes[0].getAttribute('precision'));

		if(event.type == "mousedown")
			val = 1;
		else if(event.type == "mouseup")
			val = 0;
		
//---- TODO: yes, this is lazy coding, and fragile. - Historical from Chris Web Audio Playground
		var output = event.target.parentNode.children[0].children[1];

//---- update the value text
		if(output)
			output.innerHTML = "" + val.toString() + " " + output.getAttribute("units");

		if(event.target.type == "submit")
			val = window.buttonVal;

		if(window.buttonVal == 0)
			window.buttonVal = 1;
		else
			window.buttonVal = 0;

// 	Search for DSP then update the value of its parameter.
		fDSP.setValue(text, val);
	},
	
// Save graphical parameters of a Faust Node
	saveParams : function(){
		
		var interfaceElements = fInterfaceContainer.childNodes;
			
		for(var j=0; j<interfaceElements.length; j++){
			if(interfaceElements[j].className == "control-group"){
				
				var text = interfaceElements[j].label;
				
				fParams[text] = fDSP.getValue(text);	
			}
		}
	},
	recallParams : function(){

		for (key in fParams)
			fDSP.setValue(key, fParams[key]);
	},
	getParams: function(){
		return fParams;
	},
	setParams: function(parameters){
		fParams = parameters;
	},
	addParam: function(path, value){
		fParams[path] = value;
	},
		
/******************* GET/SET INPUT/OUTPUT NODES **********************/
	addInputOutputNodes : function (){
		
		if(fDSP.getNumInputs() > 0) {
		
			fInputNode=document.createElement("div");
			fInputNode.className="node node-input";
	    	that.addCnxListener(fInputNode, "mousedown");
			fInputNode.innerHTML = "<span class='node-button'>&nbsp;</span>";
		
			fModuleContainer.appendChild(fInputNode);
		}
			
		if (fDSP.getNumOutputs() > 0) {
		
			fOutputNode=document.createElement("div");
			fOutputNode.className="node node-output";
	    	that.addCnxListener(fOutputNode, "mousedown");
			fOutputNode.innerHTML = "<span class='node-button'>&nbsp;</span>";
		
			fModuleContainer.appendChild(fOutputNode);
		}		
	},
	deleteInputOutputNodes : function(){
	
		if(fInputNode)
			fModuleContainer.removeChild(fInputNode);
	
		if(fOutputNode)
			fModuleContainer.removeChild(fOutputNode);	
	},
// Added for physical Input and Output which are create outside of ModuleClass (--> see Playground.js or Pedagogie.js)
	setInputOutputNodes : function (input, output){
		
		fInputNode = input;
		if(fInputNode)
	    	that.addCnxListener(fInputNode, "mousedown");
	    	
		fOutputNode = output;	
		if(fOutputNode)
	    	that.addCnxListener(fOutputNode, "mousedown");
	},
	
/****************** ADD/REMOVE ACTION LISTENERS **********************/
	addListener: function (type){
		document.addEventListener(type, dragCallback, true);
	},
	removeListener: function (div, type){
		div.removeEventListener(type, dragCallback, true);
	},
	addCnxListener: function (div, type){
		if(type == "mousedown")
			div.addEventListener(type, dragCnxCallback, true);
		else
			document.addEventListener(type, dragCnxCallback, true);
	},
	removeCnxListener: function (div, type){
		document.removeEventListener(type, dragCnxCallback, true);
	},
		
/**********************************************************************/
	isPointInOutput: function (x, y ){
	
		if(fOutputNode && fOutputNode.getBoundingClientRect().left < x && x < fOutputNode.getBoundingClientRect().right && fOutputNode.getBoundingClientRect().top < y && y< fOutputNode.getBoundingClientRect().bottom)
			return true;
			
		return false;
	},
	isPointInInput: function(x, y){			

		if(fInputNode && fInputNode.getBoundingClientRect().left <= x && x <= fInputNode.getBoundingClientRect().right && fInputNode.getBoundingClientRect().top <= y && y <= fInputNode.getBoundingClientRect().bottom)
			return true;
			
		return false;
	},

	isPointInNode: function (x, y ){
	
		if(fModuleContainer && fModuleContainer.getBoundingClientRect().left < x && x < fModuleContainer.getBoundingClientRect().right && fModuleContainer.getBoundingClientRect().top < y && y < fModuleContainer.getBoundingClientRect().bottom)
			return true;
			
		return false;
	}
  }
}


"use strict";

var createNode = function (ID, x, y, name, parent, callback){
	
	var that;
	
	var deleteCallback = callback;

	var container = document.createElement("div");
	container.className = "moduleFaust";
	container.id = "module" + ID;
	container.style.left = "" + x + "px";
	container.style.top = "" + y + "px";

	container.ondrop = function (e) {
	
		uploadOn(that, 0, 0, e);
		return true;
	};
	
	var title = document.createElement("h6");
	title.className = "module-title";
	title.textContent = "";
	container.appendChild(title);
	
	var content = document.createElement("div");
	content.className="content";
	container.appendChild(content);
    container.addEventListener("mousedown", dragCallback, true);
	    
	var close = document.createElement("a");
	close.href = "#";
	close.className = "close";
	close.onclick = function(){that.deleteNode();};
	container.appendChild( close );

	var footer = document.createElement("footer");
	footer.id = "moduleFooter";
	
	var editImg = document.createElement("img");
	editImg.src = "img/edit.png";
	editImg.onclick = function(){that.edit();};
	
	footer.appendChild(editImg);
	container.appendChild(footer);

	// add the node into the soundfield
	parent.appendChild(container);

	var DSP;
	var Name = name;
	var Source;
	var Params = new Array();
	var InputNode;
	var OutputNode;
	
	var outputConnections = null;
	var inputConnections = null;
		
	function dragCallback(event){
		if(event.type == "mousedown")
			startDraggingNode(event, that);
		else if(event.type == "mouseup")	
			stopDraggingNode(event, that);
		else if(event.type == "mousemove")	
			whileDraggingNode(event, that);
	};
	
	function dragCnxCallback(event){
		if(event.type == "mousedown")
			startDraggingConnector(that, event);
		else if(event.type == "mouseup")	
			stopDraggingConnector(that, event);
		else if(event.type == "mousemove")	
			whileDraggingConnector(that, event);
	};

// 	function 
  return {
/**********************************************************************/

    deleteNode: function() {
    	disconnectNode(that);
// 	deleteDSP(faustDiv.DSP);
	 	that.deleteFaustInterface();	
    
    	if(container)
	// Then delete the visual element
			container.parentNode.removeChild( container );
			
		that.deleteDSP(DSP);	
		deleteCallback();
    },
	integrateNodeInScene: function(){},
	
/*************** ACTIONS ON IN/OUTPUT NODES ***************************/
	getOutputNode: function(){return OutputNode;},
	getInputNode: function(){return InputNode;},
	
	getInputConnections: function(){
	
		return inputConnections;
	},
	getOutputConnections: function(){
		return outputConnections;
	},
	addOutputConnection: function(connector){
		if(!outputConnections)
			outputConnections = new Array();
			
		outputConnections.push(connector);
	},
	addInputConnection: function(connector){
	
		if(!inputConnections)
			inputConnections = new Array();
			
		inputConnections.push(connector);
	},
	removeOutputConnection: function(connector){
		outputConnections.splice(outputConnections.indexOf(connector), 1);
	},
	removeInputConnection: function(connector){
			
		inputConnections.splice(inputConnections.indexOf(connector), 1);
	},
/**********************************************************************/
	showNode: function(){container.style.visibility = "visible";},
	hideNode: function(){ container.style.visibility = "hidden";},
	
/**********************************************************************/
	setDSP: function(dsp_code){
		 that = this; 

		var args = ["-I", "http://faust.grame.fr/faustcode/"]; 
	 
	    var factory = faust.createDSPFactory(dsp_code, args);
	
		if (!factory) {
    		alert(faust.getErrorMessage());    
        	return false;
		}
                
    	DSP = faust.createDSPInstance(factory, window.audioContext, 1024);
    	Source = dsp_code;
    	
    	return true;
	},
	getDSP: function(){
		return DSP;
	},
	updateDSP: function(codeName, code){
	
		var toDelete = DSP;
	
		var saveOutCnx = new Array().concat(outputConnections);
		var saveInCnx = new Array().concat(inputConnections);
			
		disconnectNode(that);
	
		if(that.setDSP(code)){
		
		    that.deleteFaustInterface();
 			that.deleteInputOutputNodesToModule();	
 		
 	// Creating new interface
 	
// 	 		title.textContent = codeName;
	 		Name = codeName;
	 		Source = code;
			that.createInterface();
			that.addInputOutputNodesToModule();
		
			that.deleteDSP(toDelete);
		}

	// Recalling connections
// 		outputConnections = saveOutCnx;
// 		inputConnections =  saveInCnx;
		
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
	getSource: function(){return Source;},
	getName: function(){return Name;},
		
//---- Create/Delete the interface of a DSP in the "Content" Div of the FaustDiv	
	createInterface: function(){

		title.textContent = Name;

		parse_ui(JSON.parse(DSP.json()).ui, this); 
	},
	deleteFaustInterface: function(){
			
		var Cchildren = content.childNodes;
		
		while(Cchildren.length != 0)
			content.removeChild(Cchildren[0]);
	},
	getContainer: function(){
		return container;
	},
	getNodeContainer: function(){
		return content;
	},

//---- Generic callback for Faust Interface
	interfaceCallback: function(event){
	
		var text = event.target.parentNode.label;

		var val = event.target.value;
					
		val = Number((event.target.value*event.target.parentNode.childNodes[0].getAttribute('step')) + Number(event.target.parentNode.childNodes[0].getAttribute('min'))).toFixed(event.target.parentNode.childNodes[0].getAttribute('precision'));

		if(event.type == "mousedown")
			val = 1;
		else if(event.type == "mouseup")
			val = 0;
		
//---- TODO: yes, this is lazy coding, and fragile.
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
		DSP.setValue(text, val);
	},
	
// Save graphical parameters of a Faust Node
	saveParams : function(){
		
		var contentChildren = content.childNodes;
			
		for(var j=0; j<contentChildren.length; j++){
			if(content.childNodes[j].className == "control-group"){
				
				var text = content.childNodes[j].label;
				
				Params[text] = DSP.getValue(text);	
			}
		}
	},
	recallParams : function(){

		for (key in Params)
			DSP.setValue(key, Params[key]);
	},
	getParams: function(){
		return Params;
	},
	setParams: function(parameters){
		Params = parameters;
	},
		
/**********************************************************************/
	addInputOutputNodesToModule : function (){
		
		if(DSP.getNumInputs() > 0) {
		
			InputNode=document.createElement("div");
			InputNode.className="node node-input";
	    	that.addCnxListener(InputNode, "mousedown");
			InputNode.innerHTML = "<span class='node-button'>&nbsp;</span>";
		
			container.appendChild(InputNode);
			container.inputs = InputNode;
		}
			
		if (DSP.getNumOutputs() > 0) {
		
			OutputNode=document.createElement("div");
			OutputNode.className="node node-output";
	    	that.addCnxListener(OutputNode, "mousedown");
			OutputNode.innerHTML = "<span class='node-button'>&nbsp;</span>";
		
			container.appendChild(OutputNode);
			container.outputs = OutputNode;
		}		
	},
	deleteInputOutputNodesToModule : function(){
	
		if(InputNode)
			container.removeChild(InputNode);
	
		if(OutputNode)
			container.removeChild(OutputNode);	
	},
	setInputOutputNodes : function (input, output){
		
		InputNode = input;
		OutputNode = output;	
	},
	
/**********************************************************************/
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
		if(OutputNode && OutputNode.getClientBoundingRect().left < x && x < OutputNode.getClientBoundingRect().right && OutputNode.getClientBoundingRect().top < y && y< OutputNode.getClientBoundingRect().bottom)
			return true;
			
		return false;
	},
	isPointInInput: function(x, y){
			
		if(InputNode && InputNode.getBoundingClientRect().left < x && x < InputNode.getBoundingClientRect().right && InputNode.getBoundingClientRect().top < y && y < InputNode.getBoundingClientRect().bottom)
			return true;
			
		return false;
	},
		
	isPointInNode: function (x, y ){
	
		if(container && container.getBoundingClientRect().left < x && x < container.getBoundingClientRect().right && container.getBoundingClientRect().top < y && y < container.getBoundingClientRect().bottom)
			return true;
			
		return false;
	},

/**********************************************************************/

	edit: function(){

		that.saveParams();
		
		that.deleteFaustInterface();
		
		var textArea = document.createElement("textarea");
		textArea.rows = 15;
		textArea.cols = 60;
		textArea.value = Source;
		content.appendChild(textArea);
			
		editImg.src = "img/enter.png";
		editImg.onclick = that.recompileSource;
		editImg.area = textArea;
	},
	recompileSource: function(event){
	
		var dsp_code = event.target.area.value;

		that.updateDSP(title.textContent, dsp_code);
		that.recallParams();
	
		editImg.src = "img/edit.png";
		editImg.onclick = that.edit;
	}
  }
}

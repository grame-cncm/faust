/*				CONNECT.JS
	Handles Audio/Graphical Connection/Deconnection of modules
	This is a historical file from Chris Wilson, modified for Faust Module needs.	

	DEPENDENCIES :
		- ModuleClass.js
		- webaudio-asm-wrapper.js
		- Dragging.js
		
*/
"use strict";

/**************************************************/
/******* WEB AUDIO CONNECTION/DECONNECTION*********/
/**************************************************/

// Connect Nodes in Web Audio Graph
function connectModules( src, dst ) {

// Searching for src/dst DSP if existing
	if(dst.getDSP)
		dst = dst.getDSP();
			
	if(src.getDSP)
		src = src.getDSP();
		
	// if the source has an audio node, connect them up.  
	// AudioBufferSourceNodes may not have an audio node yet.
	if (src.audioNode ){
		
		if(dst.audioNode)
			src.audioNode.connect(dst.audioNode);
		else if(dst.getProcessor)
			src.audioNode.connect(dst.getProcessor());
			
// 		src.connect(dst.getProcessor().audioNode);
	}
	else if(src.getProcessor){
		
		if(dst.audioNode)
			src.getProcessor().connect(dst.audioNode);
		else
			src.getProcessor().connect(dst.getProcessor())

	}

	if (dst.onConnectInput)
		dst.onConnectInput();
}

// Disconnect Nodes in Web Audio Graph
function disconnectModules(src, dst){
	
	// We want to be dealing with the audio node elements from here on
	var srcCpy = src;
	
	// Searching for src/dst DSP if existing
	if(srcCpy.getDSP)
		srcCpy = srcCpy.getDSP();

	if(srcCpy.audioNode)
		srcCpy.audioNode.disconnect();
	else
		srcCpy.getProcessor().disconnect();
		
// Reconnect all disconnected connections (because disconnect API cannot break a single connection)
	if(src.getOutputConnections()){
		for(var i=0; i<src.getOutputConnections().length; i++){
			if(src.getOutputConnections()[i].destination != dst)
				connectModules(src, src.getOutputConnections()[i].destination);
		}
	}
}

/**************************************************/
/***************** Save Connection*****************/
/**************************************************/

//----- Add connection to src and dst connections structures
function saveConnection(src, dst, connector, connectorShape){

	connector.line = connectorShape;
	connector.destination = dst;
	connector.source = src;
}

/***************************************************************/
/**************** Create/Break Connection(s) *******************/
/***************************************************************/

function createConnection(src, outtarget, dst, intarget){
	startDraggingConnection(src, outtarget);
	stopDraggingConnection(src, dst);
}



function deleteConnection() {

	breakSingleInputConnection( this.source, this.destination, this.inputConnection );
}

function breakSingleInputConnection( src, dst, connector ) {

	disconnectModules(src, dst);
		
	// delete connection from src .outputConnections,
	if(src.getOutputConnections)
		src.removeOutputConnection(connector);

	// delete connection from dst .inputConnections,
	if(dst.getInputConnections)
		dst.removeInputConnection(connector);
		
	// and delete the line
	if(connector.line)
		connector.line.parentNode.removeChild( connector.line );
}

// Disconnect a node from all its connections
function disconnectModule( nodeElement) {

	//for all output nodes
	if(nodeElement.getOutputConnections && nodeElement.getOutputConnections()){
	
		while(nodeElement.getOutputConnections().length>0)
			breakSingleInputConnection(nodeElement, nodeElement.getOutputConnections()[0].destination, nodeElement.getOutputConnections()[0]);
	}
	
	//for all input nodes 
	if(nodeElement.getInputConnections && nodeElement.getInputConnections()){
		while(nodeElement.getInputConnections().length>0)
			breakSingleInputConnection(nodeElement.getInputConnections()[0].source, nodeElement, nodeElement.getInputConnections()[0]);
	}
}


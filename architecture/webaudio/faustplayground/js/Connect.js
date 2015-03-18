/***************************************************/
/***** Audio Connection/Deconnection of nodes ******/
/***************************************************/

"use strict";

// Connect Nodes in Web Audio Graph
function connectNodes( src, dst ) {

// Searching for src/dst DSP if existing
	if(dst.getDSP){
// 		dst = document.getElementById("audioOutput");
		dst = dst.getDSP();	
	}
	if(src.getDSP){
		src = src.getDSP();
	}
		
	// if the source has an audio node, connect them up.  
	// AudioBufferSourceNodes may not have an audio node yet.
	if (src.audioNode ){
		
		if(dst.audioNode)
			src.audioNode.connect(dst.audioNode);
		else if(dst.getProcessor)
			src.audioNode.connect(dst.getProcessor());
			
		src.connect(dstCpy.getProcessor().audioNode);
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
function disconnectNodes(src, dst){
	
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
				connectNodes(src, src.getOutputConnections()[i].destination);
		}
	}
}

/**************************************************/
/********* Save/Recall Connections of a node*******/
/**************************************************/

//----- Add connection to src and dst connections structures
function saveConnection(src, dst, connector, connectorShape){

	connector.line = connectorShape;
	connector.destination = dst;
	connector.source = src;
}

//************* ACCESSORS TO INPUT CONNECTIONS STRUCTURE

function getNodeInputConnections(node){
	return node.parentNode.inputConnections;	
}

function setNodeInputConnections(node, inputConnections){

	if(inputConnections && node){
		for(var j=0; j<inputConnections.length; j++)
			createConnection(inputConnections[j].source, inputConnections[j].source.getOutputNode(), node, node.getInputNode());
	}
}

//************* ACCESSORS TO OUTPUT CONNECTIONS STRUCTURE

function getNodeOutputConnections(node){
	
	return node.parentNode.outputConnections;	
}

function setNodeOutputConnections(node, outputConnections){
	
	if(outputConnections && node){
		for(var i=0; i<outputConnections.length; i++)
			createConnection(node, node.getOutputNode(), outputConnections[i].destination, outputConnections[i].destination.getInputNode());
	}
}

/***************************************************************/
/**************** Create/Break Connection(s) *******************/
/***************************************************************/

function createConnection(src, outtarget, dst, intarget){
	startDraggingConnection(src, outtarget);
	stopDraggingConnection(dst, intarget);
}

function deleteConnection() {

	breakSingleInputConnection( this.source, this.destination, this.inputConnection );
}

function breakSingleInputConnection( src, dst, connector ) {

	disconnectNodes(src, dst);
		
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
function disconnectNode( nodeElement) {

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

// Connect/Disconnect output node to physical audio output
function mute(dest){

	var out = document.getElementById("audioOutput");
	disconnectNodes(dest, out);
}

function unmute(dest){
	
	var out = document.getElementById("audioOutput");
	connectNodes(dest, out);
}

/***************************************************/
/***** Audio Connection/Deconnection of nodes ******/
/***************************************************/

// Connect Nodes in Web Audio Graph
function connectNodes( src, dst ) {

	// We want to be dealing with the audio node elements from here on
	src = src.parentNode;
	dst = dst.parentNode;

// Searching for src/dst DSP if existing
	if(dst.DSP)
		dst = dst.DSP;	
	if(src.DSP)
		src = src.DSP;
	
	// if the source has an audio node, connect them up.  
	// AudioBufferSourceNodes may not have an audio node yet.
	if (src.audioNode ){
		
		if(dst.audioNode)
			src.audioNode.connect(dst.audioNode);
		else if(dst.scriptProcessor)
			src.connect(dst.scriptProcessor);
// 		src.connect(dstCpy.scriptProcessor.audioNode);
	}
	else if(src.scriptProcessor){
		
		if(dst.scriptProcessor) 
			src.scriptProcessor.connect(dst.scriptProcessor)
		else
			src.scriptProcessor.connect(dst.audioNode);
	}

	if (dst.onConnectInput)
		dst.onConnectInput();
}

// Disconnect Nodes in Web Audio Graph
function disconnectNodes(src, dst){
	
	// We want to be dealing with the audio node elements from here on
	var srcP = src.parentNode;
	var dstP = dst.parentNode;
	
	var srcCpy = srcP;
	var dstCpy = dstP;

	if(srcCpy.DSP)
		srcCpy = srcCpy.DSP;

	if(srcCpy.audioNode)
		srcCpy.audioNode.disconnect();
	else
		srcCpy.scriptProcessor.disconnect();
		
// Reconnect all disconnected connections (because disconnect API cannot break a single connection)
	for(var i=0; i<srcP.outputConnections.length; i++){
		if(srcP.outputConnections[i].destination != dstP)
			connectNodes(src, getInputNodeFromDiv(srcP.outputConnections[i].destination));
	}
}

/**************************************************/
/********* Save/Recall Connections of a node*******/
/**************************************************/

//----- Add connection to src and dst connections structures
function saveConnection(src, dst, connector, connectorShape){

// Put an entry into the source's outputs
	if (!src.outputConnections)
		src.outputConnections = new Array();

	connector.line = connectorShape;
	connector.destination = dst;
	src.outputConnections.push(connector);

// Put an entry into the destinations's inputs
	if (!dst.inputConnections)
		dst.inputConnections = new Array();

	connector.line = connectorShape;
	connector.source = src;
	connector.destination = dst;
	dst.inputConnections.push(connector);
	
	console.log(src.outputConnections);
	console.log(dst.inputConnections);
}

//************* ACCESSORS TO INPUT CONNECTIONS STRUCTURE

function getNodeInputConnections(node){

	return node.parentNode.inputConnections;	
}

function setNodeInputConnections(node, inputConnections){

	if(inputConnections && node){
		for(var j=0; j<inputConnections.length; j++)
			createConnection(getOutputNodeFromDiv(inputConnections[j].source), node);
	}
}

//************* ACCESSORS TO OUTPUT CONNECTIONS STRUCTURE

function getNodeOutputConnections(node){
	
	return node.parentNode.outputConnections;	
}

function setNodeOutputConnections(node, outputConnections){
	
	if(outputConnections && node){
		for(var i=0; i<outputConnections.length; i++)
			createConnection(node, getInputNodeFromDiv(outputConnections[i].destination));
	}
}

/***************************************************************/
/**************** Create/Break Connection(s) *******************/
/***************************************************************/

function createConnection(src, dst){
	startDraggingConnection(src);
	stopDraggingConnection(dst);
}

function deleteConnection() {

	breakSingleInputConnection( this.source, this.destination, this.inputConnection );
}

function breakSingleInputConnection( src, dst, connector ) {

	var srcP = src.parentNode;
	var dstP = dst.parentNode;	
		
	disconnectNodes(src, dst);
		
	// delete connection from src .outputConnections,
	if(srcP.outputConnections && srcP.outputConnections.indexOf( connector ) >= 0)
		srcP.outputConnections.splice( srcP.outputConnections.indexOf( connector ), 1);

	// delete connection from dst .inputConnections,
	if(dstP.inputConnections && dstP.inputConnections.indexOf(connector) >= 0)
		dstP.inputConnections.splice( dstP.inputConnections.indexOf( connector ), 1);
		
	// and delete the line
	if(connector.line)
		connector.line.parentNode.removeChild( connector.line );
}

// Disconnect a node from all its connections
function disconnectNode( nodeElement) {

	//for all output nodes
	if(nodeElement.outputConnections){
		while(nodeElement.outputConnections.length>0)
			breakSingleInputConnection(getOutputNodeFromDiv(nodeElement), getInputNodeFromDiv(nodeElement.outputConnections[0].destination), nodeElement.outputConnections[0].line.inputConnection);
	}
	
	//for all input nodes 
	if(nodeElement.inputConnections){
		while(nodeElement.inputConnections.length>0)
			breakSingleInputConnection(getOutputNodeFromDiv(nodeElement.inputConnections[0].source), getInputNodeFromDiv(nodeElement), nodeElement.inputConnections[0].line.inputConnection);
	}
}


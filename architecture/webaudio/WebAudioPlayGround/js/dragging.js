var dragObj = new Object();
dragObj.zIndex = 0;
dragObj.lastLit = null;

// Node Dragging functions - these are used for dragging the audio modules, 
// like Destination or AudioSourceBuffer.

function skipDefault(event) {
	if ((event.target.tagName != "SELECT")&&(event.target.tagName != "INPUT"))
		event.preventDefault();
}

function startDraggingNode(event) {
 	var el;
  	var x, y;

	if (event.target.tagName == "SELECT")
		return;
	el = event.target;

	if (el.nodeType == 3) // if it's a text node
		el = el.parentNode;
	if (el.classList.contains("module-title"))
		el = el.parentNode;
	if (el.classList.contains("content"))
		el = el.parentNode;
	if (!el.classList.contains("module"))
		return;
		
    dragObj.elNode = el;
/*
    // If this is a text node, use its parent element.
    if ((dragObj.elNode.nodeType == 3)||(dragObj.elNode.className == "analyserCanvas"))
    	dragObj.elNode = dragObj.elNode.parentNode;
*/

	// Get cursor position with respect to the page.
    x = event.clientX + window.scrollX;
    y = event.clientY + window.scrollY;

  	// Save starting positions of cursor and element.
  	dragObj.cursorStartX = x;
  	dragObj.cursorStartY = y;
  	dragObj.elStartLeft  = parseInt(dragObj.elNode.style.left, 10);
  	dragObj.elStartTop   = parseInt(dragObj.elNode.style.top,  10);

  	if (isNaN(dragObj.elStartLeft)) dragObj.elStartLeft = 0;
  	if (isNaN(dragObj.elStartTop))  dragObj.elStartTop  = 0;

  	// Update element's z-index.
	dragObj.elNode.style.zIndex = ++dragObj.zIndex;

  	// Capture mousemove and mouseup events on the page.
    document.addEventListener("mousemove", whileDraggingNode,   true);
    document.addEventListener("mouseup",   stopDraggingNode, 	true);
//	document.addEventListener( 'pointermove', whileDraggingNode, true );
//	document.addEventListener( 'pointerup', stopDraggingNode, true );
//	document.addEventListener( 'pointerleave', stopDraggingNode, true );
    event.preventDefault();
}

function whileDraggingNode(event) {
	var x, y;
	var e = dragObj.elNode;

	// Get cursor position with respect to the page.
    x = event.clientX + window.scrollX;
    y = event.clientY + window.scrollY;

	// Move drag element by the same amount the cursor has moved.
  	e.style.left = (dragObj.elStartLeft + x - dragObj.cursorStartX) + "px";
  	e.style.top  = (dragObj.elStartTop  + y - dragObj.cursorStartY) + "px";

	if (e.inputConnections) {	// update any lines that point in here.
		var c;
		
		var off = e.inputs;
	    x = window.scrollX + 12;
	    y = window.scrollY + 12;

		while (off) {
			x+=off.offsetLeft;
			y+=off.offsetTop;
			off=off.offsetParent;
		}
		
		for (c=0; c<e.inputConnections.length; c++) {
			e.inputConnections[c].line.setAttributeNS(null, "x1", x);
			e.inputConnections[c].line.setAttributeNS(null, "y1", y);
		}
	}

	if (e.outputConnections) {	// update any lines that point out of here.
		var c;
		
		var off = e.outputs;
	    x = window.scrollX + 12;
	    y = window.scrollY + 12;

		while (off) {
			x+=off.offsetLeft;
			y+=off.offsetTop;
			off=off.offsetParent;
		}
		
		for (c=0; c<e.outputConnections.length; c++) {
			e.outputConnections[c].line.setAttributeNS(null, "x2", x);
			e.outputConnections[c].line.setAttributeNS(null, "y2", y);
		}
	}

    event.preventDefault();
}

function stopDraggingNode(event) {
  // Stop capturing mousemove and mouseup events.
    document.removeEventListener("mousemove", whileDraggingNode,   true);
    document.removeEventListener("mouseup",   stopDraggingNode, true);
//	document.removeEventListener( 'pointermove', whileDraggingNode, true );
//	document.removeEventListener( 'pointerup', stopDraggingNode, true );
//	document.removeEventListener( 'pointerleave', stopDraggingNode, true );
}

// Connector Dragging functions - these are used for dragging the connectors 
// between Audio nodes
function startDraggingConnection(obj){

	dragObj.elNode = obj;

	// If this is a text node, use its parent element.
    if (dragObj.elNode.nodeType == 3)
    	dragObj.elNode = dragObj.elNode.parentNode;

    // if this is the green or red button, use its parent.
    if (dragObj.elNode.classList.contains("node-button"))
    	dragObj.elNode = dragObj.elNode.parentNode;


	// Get the position of the originating connector with respect to the page.
	var off = obj;
    x = window.scrollX + 12;
    y = window.scrollY + 12;

	while (off) {
		x+=off.offsetLeft;
		y+=off.offsetTop;
		off=off.offsetParent;
	}

  	// Save starting positions of cursor and element.
  	dragObj.cursorStartX = x;
  	dragObj.cursorStartY = y;

	// remember if this is an input or output node, so we can match
	dragObj.originIsInput = dragObj.elNode.classList.contains("node-input");

	dragObj.elNode.unlitClassname = dragObj.elNode.className;
	dragObj.elNode.className += " canConnect";
	
	// Create a connector visual line
	var svgns = "http://www.w3.org/2000/svg";

	var shape = document.createElementNS(svgns, "line");
	shape.setAttributeNS(null, "x1", x);
	shape.setAttributeNS(null, "y1", y);
    shape.setAttributeNS(null, "x2", x);
    shape.setAttributeNS(null, "y2", y);
    shape.setAttributeNS(null, "stroke", "black");
	shape.setAttributeNS(null, "stroke-width", "5");
	dragObj.connectorShape=shape;

    document.getElementById("svgCanvas").appendChild(shape);
}

function startDraggingConnector(event) {
 	var el;
  	var x, y;

    startDraggingConnection(event.target);

  	// Capture mousemove and mouseup events on the page.
    document.addEventListener("mousemove", whileDraggingConnector,   true);
    document.addEventListener("mouseup",   stopDraggingConnector, 	true);
//	document.addEventListener( 'pointermove', whileDraggingConnector, true );
//	document.addEventListener( 'pointerup', stopDraggingConnector, true );
//	document.addEventListener( 'pointerleave', stopDraggingConnector, true );
    event.preventDefault();
	event.stopPropagation();
}

function whileDraggingConnector(event) {
	var x, y;
	var toElem = event.toElement;

	// Get cursor position with respect to the page.
    x = event.clientX + window.scrollX;
    y = event.clientY + window.scrollY;

	// Move connector visual line
    dragObj.connectorShape.setAttributeNS(null, "x2", x);
    dragObj.connectorShape.setAttributeNS(null, "y2", y);
	
    // If this is a text node, use its parent element.
    if (toElem.nodeType == 3)
    	toElem = toElem.parentNode;

    if (toElem.classList) {	// if we don't have class, we're not a node.
	    // if this is the green or red button, use its parent.
	    if (toElem.classList.contains("node-button"))
	    	toElem = toElem.parentNode;

	    // if we're over our originating node, do nothing.
	    if (toElem == dragObj.elemNode)
	    	return;
		
		// If we used to be lighting up a node, but we're not over it anymore,
		// unlight it.
		if (dragObj.lastLit && (dragObj.lastLit != toElem ) ) {
			dragObj.lastLit.className = dragObj.lastLit.unlitClassname;
			dragObj.lastLit = null;
		}

		// light up connector point underneath, if any
		if (toElem.classList.contains("node")) {
			if (!dragObj.lastLit || (dragObj.lastLit != toElem )) {
				if (dragObj.originIsInput) {
					if (toElem.classList.contains("node-output")) {
						toElem.unlitClassname = toElem.className;
						toElem.className += " canConnect";
						dragObj.lastLit = toElem;
					}
				} else {	// first node was an output, so we're looking for an input
					if (toElem.classList.contains("node-input")) {
						toElem.unlitClassname = toElem.className;
						toElem.className += " canConnect";
						dragObj.lastLit = toElem;
					}
				}
			}
		}
	}
    event.preventDefault();
	event.stopPropagation();
}

// Make a connection between two connection point elements.
// the src and dst params are connection point elems, NOT
// the node elems themselves.
function connectNodes( src, dst ) {

	console.log("Connecting Nodes");
	console.log(src);
	console.log(dst);

	var connectorShape = dragObj.connectorShape;
	src.className += " connected";
	dst.className += " connected";

	// We want to be dealing with the audio node elements from here on
	src = src.parentNode;
	dst = dst.parentNode;

	// Put an entry into the source's outputs
	if (!src.outputConnections)
		src.outputConnections = new Array();
		
	var connector = new Object();
	connector.line = connectorShape;
	connector.destination = dst;
	src.outputConnections.push(connector);
	
	console.log("Output Connections ====>");
	console.log(src.outputConnections);
	
	//Make sure the connector line points go from src->dest (x1->x2)
	if (!dragObj.originIsInput) { // need to flip
		var shape = connectorShape;
		var x = shape.getAttributeNS(null, "x2");
		var y = shape.getAttributeNS(null, "y2");
	    shape.setAttributeNS(null, "x2", shape.getAttributeNS(null, "x1"));
	    shape.setAttributeNS(null, "y2", shape.getAttributeNS(null, "y1"));
		shape.setAttributeNS(null, "x1", x);
		shape.setAttributeNS(null, "y1", y);
	}
	// Put an entry into the destinations's inputs
	if (!dst.inputConnections)
		dst.inputConnections = new Array();

	connector = new Object();
	connector.line = connectorShape;
	connector.source = src;
	connector.destination = dst;
	dst.inputConnections.push(connector);
	
	var dstCpy = dst;
	var srcCpy = src;

// Searching for src/dst DSP if existing
	for (var i = 0; i < window.myArray.length; i++) {    		

		if(window.myArray[i].ID == dst.id)
			dstCpy = window.myArray[i].DSP;
		
		else if(window.myArray[i].ID == src.id)
			srcCpy = window.myArray[i].DSP;
	}
	
	// if the source has an audio node, connect them up.  
	// AudioBufferSourceNodes may not have an audio node yet.
	if (srcCpy.audioNode ){
		
		if(dst.audioNode)
			srcCpy.audioNode.connect(dstCpy.audioNode);
		else if(dstCpy.scriptProcessor)
			srcCpy.connect(dstCpy.scriptProcessor);
// 		src.connect(dstCpy.scriptProcessor.audioNode);
	}
	else if(srcCpy.scriptProcessor){
		
		if(dstCpy.scriptProcessor) 
			srcCpy.scriptProcessor.connect(dstCpy.scriptProcessor)
		else
			srcCpy.scriptProcessor.connect(dstCpy.audioNode);
	}

	if (dstCpy.onConnectInput)
		dstCpy.onConnectInput();

	connectorShape.inputConnection = connector;
	connectorShape.destination = dst;
	connectorShape.onclick = deleteConnection;

	connectorShape = null;
}

function deleteConnection() {
	var connections = this.destination.inputConnections;
	breakSingleInputConnection( connections, connections.indexOf( this.inputConnection ) );
}

function breakSingleInputConnection( connections, index ) {
		var connector = connections[index];
		var src = connector.source;

		// delete us from their .outputConnections,
		if(src.outputConnections && src.outputConnections.indexOf( connector.destination ))
			src.outputConnections.splice( src.outputConnections.indexOf( connector.destination ), 1);
			
		for (var i = 0; i < window.myArray.length; i++) {    		
			if(window.myArray[i].ID == src.id){
				src = window.myArray[i].DSP;
			}
		}
		
		if (src.audioNode) {	// they may not have an audioNode, if they're a BSN or an Oscillator
			// call disconnect() on the src,
			src.audioNode.disconnect(connector.destination.audioNode);
		}
		else if(src.scriptProcessor){
			src.scriptProcessor.disconnect(connector.destination.audioNode);
		}

		// and delete the line 
		connector.line.parentNode.removeChild( connector.line );

		// finally, remove us from the line.
		if(connections && index)
			connections.splice( index, 1 );
}

// Disconnect a node from all other nodes connecting to it, or that it connects to.
function disconnectNode( nodeElement ) {

	var nodeElementCpy = nodeElement;

	//for all nodes we connect to,
	if (nodeElementCpy.outputConnections) {
	
		var faustOutput = false;
	
		for (var i=0; i<nodeElementCpy.outputConnections.length; i++) {
			var connector = nodeElementCpy.outputConnections[i];
			// find each dstElement and remove us from the dst.inputConnections,
			var connections = connector.destination.inputConnections;
	
			// Make sure connection was not deleted by other node.		
			if(connections && connections.indexOf(nodeElementCpy))
				connections.splice( connections.indexOf(nodeElementCpy), 1);

			// and delete the line
			if(connector.line.parentNode)
				connector.line.parentNode.removeChild( connector.line );
			
			if(nodeElementCpy.outputConnections[i].id == "output")
				faustOutput = true;
		}
		// empty our outputConnections
		nodeElementCpy.outputConnections = null;
		
			
		for (var i = 0; i < window.myArray.length; i++) {    		
			if(window.myArray[i].ID == nodeElementCpy.id){
				nodeElementCpy = window.myArray[i].DSP;
				nodeElementCpy.scriptProcessor.disconnect(faust.context.destination);
			}
		}
	
	// then call disconnect() on our audioNode to clear all outbound connections
	// (this is what clear the audio connection, for all outbound connections at once)
		if (nodeElementCpy.audioNode)	// we may not have an audioNode, if we're a BSN or an Oscillator
			nodeElementCpy.audioNode.disconnect();
		
		else if(nodeElementCpy.scriptProcessor)
			nodeElementCpy.scriptProcessor.disconnect();
	}
	
	//for all nodes connecting to us - (aka in us.inputConnections)
	if (nodeElement.inputConnections) {
	
		for (var i=0; i<nodeElement.inputConnections.length; i++) {
			var connector = nodeElement.inputConnections[i];
			// this is trickier, because we'll have to destroy all their outbound connections.
			// TODO: this will suck for source nodes.
			var src = connector.source;
			
			var connections = src.outputConnections;

			// delete us from their .outputConnections,
			if( connections && connections.indexOf(nodeElement))
				connections.splice( connections.indexOf(nodeElement), 1);
			
			for (var i = 0; i < window.myArray.length; i++) {    		
				 if(window.myArray[i].ID == src.id)
				 	src = window.myArray[i].DSP;
			}
			
			if (src.audioNode) {	// they may not have an audioNode, if they're a BSN or an Oscillator
				// call disconnect() on the src,
				src.audioNode.disconnect();
				// if there's anything in their outputConnections, re.connect() those nodes.
				// TODO: again, this will break due to src resetting.
				for (var j=0; j<connections.length; j++)
					src.audioNode.connect(connections[i].destination.audioNode);
			}
			else if(src.scriptProcessor){
	
				src.scriptProcessor.disconnect(nodeElementCpy.scriptProcessor);
				
// 				for (var j=0; j<connections.length; j++){
// 				
// 					var cnxDst = connections[j].destination;
// 				
// 					console.log(cnxDst);
// 				
// 					for (var i = 0; i < window.myArray.length; i++) {    		
// 						 if(window.myArray[i].ID == cnxDst.id)
// 						 	cnxDst = window.myArray[i].DSP;
// 					}
// 					
// 					src.scriptProcessor.connect(cnxDst.scriptProcessor);
// 				}
			}

			// and delete the line 
			connector.line.parentNode.removeChild( connector.line );
		}
		// empty inputConnections
		nodeElement.inputConnections = null;
	}
}

function stopDraggingConnection(obj){

		if (dragObj.lastLit) {
		dragObj.lastLit.className = dragObj.lastLit.unlitClassname;
		dragObj.lastLit = null;
	}

	dragObj.elNode.className = dragObj.elNode.unlitClassname;

	var toElem = obj;

    // If this is a text node, use its parent element.
    if (toElem.nodeType == 3)
    	toElem = toElem.parentNode;

    if (toElem.classList) {	// if we don't have class, we're not a node.
	    // if this is the green or red button, use its parent.
	    if (toElem.classList.contains("node-button"))
	    	toElem = toElem.parentNode;

		// Get the position of the originating connector with respect to the page.
		var off = toElem;
		x = window.scrollX + 12;
		y = window.scrollY + 12;

		while (off) {
			x+=off.offsetLeft;
			y+=off.offsetTop;
			off=off.offsetParent;
		}
		dragObj.connectorShape.setAttributeNS(null, "x2", x);
	    dragObj.connectorShape.setAttributeNS(null, "y2", y);

		var str=""+toElem.className;
	
		// If we're over a connection point, make the connection
		if (dragObj.originIsInput) {
		
			console.log("origin is input");
		
			if (toElem.classList.contains("node-output")) {
				// can connect!
				connectNodes(toElem, dragObj.elNode);
				return;
			}

		} else {	// first node was an output, so we're looking for an input
		
			console.log("origin is not input");
			if (toElem.classList.contains("node-input")) {
				console.log(toElem);
// 				console.log(toElem.parentNode);
				
// 				toElem.parentNod
				
				// can connect!
				// TODO: first: swap the line endpoints so they're consistently x1->x2
				// That makes updating them when we drag nodes around easier.
				connectNodes(dragObj.elNode, toElem);
				return;
			}
		}
	}

	// Otherwise, delete the line
	dragObj.connectorShape.parentNode.removeChild(dragObj.connectorShape);
	dragObj.connectorShape = null;
}

function stopDraggingConnector(event) {
  	// Stop capturing mousemove and mouseup events.
    document.removeEventListener("mousemove", whileDraggingConnector,   true);
    document.removeEventListener("mouseup",   stopDraggingConnector, true);
//	document.removeEventListener( 'pointermove', whileDraggingConnector, true );
//	document.removeEventListener( 'pointerup', stopDraggingConnector, true );
//	document.removeEventListener( 'pointerleave', stopDraggingConnector, true );


	stopDraggingConnection(event.toElement || event.target);
}

function stringifyAudio() {
	var code = "var context=null;\ntry \{\n\tcontext = window.webkitAudioContext ? " +
		"new webkitAudioContext\(\) : new audioContext\(\);\n}\ncatch(e) \{\n" +
		"\talert\('Web Audio API is not supported in this browser'\);\n\}\n";

	var nodes = document.getElementById("soundField").children;

	for (var i=0; i<nodes.length; i++) {
		if ( nodes[i].audioNode ) {
			switch ( nodes[i].audioNodeType ) {
				case "audioBufferSource":
					code += "\tvar ABSN = context.createBufferSource();\n\tABSN.gain = " + 
						nodes[i].gain + ";\n\tABSN.buffer = myBuffer;\n\tABSN.connect();\n";
					break;
			}
		}
	}
	// add the node into the soundfield
	document.getElementById("code").innerHTML = code;
}

/***********************************/
/******* GET/SET CNX OF A NODE******/
/***********************************/

function getOutputNodeFromDiv(div){

	for(var i=0 ; i<div.childNodes.length; i++){
		if(div.childNodes[i].className.indexOf("node node-output")>=0){
			return div.childNodes[i];
		}
	}
	
	return null;
}

function getInputNodeFromDiv(div){

	for(var i=0 ; i<div.childNodes.length; i++){
		if(div.childNodes[i].className && div.childNodes[i].className.indexOf("node node-input")>=0){
			return div.childNodes[i];
		}
	}
	
	return null;
}

function getNodeInputConnections(node){

	return node.parentNode.inputConnections;	
}

function getNodeOutputConnections(node){
	
	return node.parentNode.outputConnections;	
}

function setNodeInputConnections(node, inputConnections){

	if(inputConnections){
		for(var i=0; i<inputConnections.length; i++){
		
			startDraggingConnection(getOutputNodeFromDiv(inputConnections[i].source));
			stopDraggingConnection(node);
		}
	}
}

function setNodeOutputConnections(node, outputConnections){
	
	if(outputConnections){
		for(var i=0; i<outputConnections.length; i++){
			startDraggingConnection(node);
			stopDraggingConnection(getInputNodeFromDiv(outputConnections[i].destination));
		}
	}
}

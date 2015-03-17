"use strict";

var dragObj = new Object();
dragObj.zIndex = 0;
dragObj.lastLit = null;

/***********************************************************************************/
/****** Node Dragging - these are used for dragging the audio modules interface*****/
/***********************************************************************************/

function startDraggingNode(event, node) {

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
	if (!el.classList.contains("moduleFaust"))
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
  	node.addListener("mousemove");
	node.addListener("mouseup");

    event.preventDefault();
}

function whileDraggingNode(event, node) {
	var x, y;
	var e = dragObj.elNode;
	
	// Get cursor position with respect to the page.
    x = event.clientX + window.scrollX;
    y = event.clientY + window.scrollY;

	// Move drag element by the same amount the cursor has moved.
  	e.style.left = (dragObj.elStartLeft + x - dragObj.cursorStartX) + "px";
  	e.style.top  = (dragObj.elStartTop  + y - dragObj.cursorStartY) + "px";
	
	if (node.getInputConnections() != null) {	// update any lines that point in here.
		var c;
		
		var off = e.inputs;
	    x = window.scrollX + 12;
	    y = window.scrollY + 12;

		while (off) {
		
			x+=off.offsetLeft;
			y+=off.offsetTop;
			off=off.offsetParent;
		}
		
		for (c=0; c<node.getInputConnections().length; c++) {
		
			node.getInputConnections()[c].line.setAttributeNS(null, "x1", x);
			node.getInputConnections()[c].line.setAttributeNS(null, "y1", y);
		}
	}

	if (node.getOutputConnections()!= null) {	// update any lines that point out of here.
		var c;
		
		var off = e.outputs;
	    x = window.scrollX + 12;
	    y = window.scrollY + 12;

		while (off) {
			x+=off.offsetLeft;
			y+=off.offsetTop;
			off=off.offsetParent;
		}
		
		for (c=0; c<node.getOutputConnections().length; c++) {

			node.getOutputConnections()[c].line.setAttributeNS(null, "x2", x);
			node.getOutputConnections()[c].line.setAttributeNS(null, "y2", y);
		}
	}

    event.preventDefault();
}

function stopDraggingNode(event, node) {
  // Stop capturing mousemove and mouseup events.
    node.removeListener(document, "mousemove");
    node.removeListener(document, "mouseup");
}

/************************************************************************************/
/*** Connector Dragging - these are used for dragging the connectors between nodes***/
/************************************************************************************/

function startDraggingConnection(node, target){

	dragObj.elNode = node;

	// If this is a text node, use its parent element.
//     if (dragObj.elNode.getNodeContainer().nodeType == 3)
//     	dragObj.elNode = dragObj.elNode.parentNode;

    // if this is the green or red button, use its parent.
    if (target.classList.contains("node-button"))
    	target = target.parentNode; 

// 	if(!target)
// 		return;

	// Get the position of the originating connector with respect to the page.
	var off = target;
    var x = window.scrollX + 12;
    var y = window.scrollY + 12;

	while (off) {
		x+=off.offsetLeft;
		y+=off.offsetTop;
		off=off.offsetParent;
	}

  	// Save starting positions of cursor and element.
  	dragObj.cursorStartX = x;
  	dragObj.cursorStartY = y;

	// remember if this is an input or output node, so we can match
	dragObj.originIsInput = target.classList.contains("node-input");

	node.getNodeContainer().unlitClassname = dragObj.elNode.getNodeContainer().className;
	node.getNodeContainer().className += " canConnect";
	
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

function stopDraggingConnection(node, target){

	var sourceNode = dragObj.elNode;

	if (sourceNode.getNodeContainer().lastLit) {
		sourceNode.getNodeContainer().lastLit.className = sourceNode.getNodeContainer().lastLit.unlitClassname;
		sourceNode.getNodeContainer().lastLit = null;
	}

	dragObj.elNode.getNodeContainer().className = dragObj.elNode.getNodeContainer().unlitClassname;

	var toElem = target;

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
	
		var src, dst;
	
		// If connecting from output to input
		if (dragObj.originIsInput) {
		
			if (toElem.classList.contains("node-output")) {
				src = node;
				dst = sourceNode;
			}
		}		
		else {
			if (toElem.classList.contains("node-input")) {

	// Make sure the connector line points go from src->dest (x1->x2)
				var shape = dragObj.connectorShape;
				var x = shape.getAttributeNS(null, "x2");
				var y = shape.getAttributeNS(null, "y2");
			    shape.setAttributeNS(null, "x2", shape.getAttributeNS(null, "x1"));
	    		shape.setAttributeNS(null, "y2", shape.getAttributeNS(null, "y1"));
				shape.setAttributeNS(null, "x1", x);
				shape.setAttributeNS(null, "y1", y);
				
				// can connect!
				// TODO: first: swap the line endpoints so they're consistently x1->x2
				// That makes updating them when we drag nodes around easier.
// 				connectConnectors(dragObj.elNode, toElem);
// 				return;
				src = sourceNode;
				dst = node;
			}
		}
		
		if(src && dst){
		
			connectNodes(src, dst);
			
			var connector = new Object();

			saveConnection(src, dst, connector, dragObj.connectorShape);
		
			dst.addInputConnection(connector);
			src.addOutputConnection(connector);
			
			dragObj.connectorShape.inputConnection = connector;
			dragObj.connectorShape.destination = dst;
			dragObj.connectorShape.source = src;
			dragObj.connectorShape.onclick = deleteConnection;

			dragObj.connectorShape = null;
			
			if(isTooltipEnabled())
				toolTipForConnections();
	
			return;
		}
	}

	// Otherwise, delete the line
	dragObj.connectorShape.parentNode.removeChild(dragObj.connectorShape);
	dragObj.connectorShape = null;
}

function startDraggingConnector(node, event) {

    startDraggingConnection(node, event.target);

  	// Capture mousemove and mouseup events on the page.
    node.addCnxListener(event.target, "mousemove");
    node.addCnxListener(event.target, "mouseup");

    event.preventDefault();
	event.stopPropagation();
}

function whileDraggingConnector(node, event) {

// 	var toElem = event.toElement;
	var toElem = event.target;

	// Get cursor position with respect to the page.
    var x = event.clientX + window.scrollX;
    var y = event.clientY + window.scrollY;
	
	// Move connector visual line
    dragObj.connectorShape.setAttributeNS(null, "x2", x);
    dragObj.connectorShape.setAttributeNS(null, "y2", y);


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

function stopDraggingConnector(node, event) {

  	// Stop capturing mousemove and mouseup events.
    node.removeCnxListener(event.target, "mousemove");
    node.removeCnxListener(event.target, "mouseup");

// event.toElement || event.target

	var arrivingNode;

	var modules = window.scenes[window.currentScene].getModules();
// 	modules.push(window.scenes[window.currentScene].audioOutput());

	for(var i=0; i<modules.length; i++){
	
		if((dragObj.originIsInput && modules[i].isPointInOutput(event.clientX, event.clientY)) || modules[i].isPointInInput(event.clientX, event.clientY)){
			arrivingNode = modules[i];
			break;
		}
	}	

	var module = window.scenes[window.currentScene].audioOutput();
	if((dragObj.originIsInput && module.isPointInOutput(event.clientX, event.clientY)) || module.isPointInInput(event.clientX, event.clientY))
		arrivingNode = module;	

	stopDraggingConnection(arrivingNode, event.target);
}




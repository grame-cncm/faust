/*				DRAGGING.JS
	Handles Graphical Drag of Modules and Connections
	This is a historical file from Chris Wilson, modified for Faust Module needs.
	
	--> Things could probably be easier...
	
	DEPENDENCIES :
		- Connect.js
		- ModuleClass.js
		
*/

"use strict";

var dragObj = new Object();
dragObj.zIndex = 0;
dragObj.lastLit = null;

/***********************************************************************************/
/****** Node Dragging - these are used for dragging the audio modules interface*****/
/***********************************************************************************/

function startDraggingModule(event, module) {

 	var el = event.target;;
  	var x, y;
  	
//   Avoid dragging Module when it's a Connector that needs dragging
	if (el.tagName == "SELECT" || el.classList.contains("node-button"))
		return;

//   Avoid dragging Module when it's a UI element that needs dragging
	if (el.nodeType == 3) // if it's a text node
		el = el.parentNode;
	if (el.classList.contains("module-title"))
		el = el.parentNode;
	if (el.classList.contains("content"))
		el = el.parentNode;
	if (!el.classList.contains("moduleFaust"))
		return;

	var moduleContainer = module.getModuleContainer();


	// Get cursor position with respect to the page.
    x = event.clientX + window.scrollX;
    y = event.clientY + window.scrollY;

  	// Save starting positions of cursor and element.
  	dragObj.cursorStartX = x;
  	dragObj.cursorStartY = y;
  	dragObj.elStartLeft  = parseInt(moduleContainer.style.left, 10);
  	dragObj.elStartTop   = parseInt(moduleContainer.style.top,  10);

  	if (isNaN(dragObj.elStartLeft)) dragObj.elStartLeft = 0;
  	if (isNaN(dragObj.elStartTop))  dragObj.elStartTop  = 0;

  	// Update element's z-index.
	moduleContainer.style.zIndex = ++dragObj.zIndex;

  	// Capture mousemove and mouseup events on the page.
  	module.addListener("mousemove");
	module.addListener("mouseup");

    event.preventDefault();
}

function whileDraggingModule(event, module) {
	var x, y;
	
	var moduleContainer = module.getModuleContainer();
	
	// Get cursor position with respect to the page.
    x = event.clientX + window.scrollX;
    y = event.clientY + window.scrollY;

	// Move drag element by the same amount the cursor has moved.
  	moduleContainer.style.left = (dragObj.elStartLeft + x - dragObj.cursorStartX) + "px";
  	moduleContainer.style.top  = (dragObj.elStartTop  + y - dragObj.cursorStartY) + "px";
	
	if (module.getInputConnections() != null) {	// update any lines that point in here.
		var c;
		
		var off = module.getInputNode();
	    x = window.scrollX + 12;
	    y = window.scrollY + 12;

		while (off) {
		
			x+=off.offsetLeft;
			y+=off.offsetTop;
			off=off.offsetParent;
		}
		
		for (c=0; c<module.getInputConnections().length; c++) {
		
			module.getInputConnections()[c].line.setAttributeNS(null, "x1", x);
			module.getInputConnections()[c].line.setAttributeNS(null, "y1", y);
		}
	}

	if (module.getOutputConnections()!= null) {	// update any lines that point out of here.
		var c;
		
		var off = module.getOutputNode();
	    x = window.scrollX + 12;
	    y = window.scrollY + 12;

		while (off) {
			x+=off.offsetLeft;
			y+=off.offsetTop;
			off=off.offsetParent;
		}
		
		for (c=0; c<module.getOutputConnections().length; c++) {

			if(module.getOutputConnections()[c].line){
				module.getOutputConnections()[c].line.setAttributeNS(null, "x2", x);
				module.getOutputConnections()[c].line.setAttributeNS(null, "y2", y);
			}
		}
	}

    event.preventDefault();
}

function stopDraggingModule(event, module) {
  // Stop capturing mousemove and mouseup events.
    module.removeListener(document, "mousemove");
    module.removeListener(document, "mouseup");
}

/************************************************************************************/
/*** Connector Dragging - these are used for dragging the connectors between nodes***/
/************************************************************************************/

function startDraggingConnection(module, target){

    // if this is the green or red button, use its parent.
    if (target.classList.contains("node-button"))
    	target = target.parentNode; 

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

	module.getInterfaceContainer().unlitClassname = module.getInterfaceContainer().className;
	module.getInterfaceContainer().className += " canConnect";
	
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

function stopDraggingConnection(sourceModule, destination){


	if (sourceModule.getInterfaceContainer().lastLit) {
		sourceModule.getInterfaceContainer().lastLit.className = sourceModule.getInterfaceContainer().lastLit.unlitClassname;
		sourceModule.getInterfaceContainer().lastLit = null;
	}

	sourceModule.getInterfaceContainer().className = sourceModule.getInterfaceContainer().unlitClassname;


    if (destination) {	

		// Get the position of the originating connector with respect to the page.
		
		var off;
		if(!dragObj.originIsInput)
			off = destination.getInputNode();
		else
			off = destination.getOutputNode();
		
		var toElem = off;
	
		console.log(destination.getName());
		console.log(toElem);	
	// Get the position of the originating connector with respect to the page.			
		x = window.scrollX + 12;
		y = window.scrollY + 12;

		while (off) {
			x+=off.offsetLeft;
			y+=off.offsetTop;
			off=off.offsetParent;
		}
		
		dragObj.connectorShape.setAttributeNS(null, "x2", x);
	    dragObj.connectorShape.setAttributeNS(null, "y2", y);
	
		var src, dst;
	
		// If connecting from output to input
		if (dragObj.originIsInput) {
		
			if (toElem.classList.contains("node-output")) {
				src = destination;
				dst = sourceModule;
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
				
				src = sourceModule;
				dst = destination;
			}
		}
		
		if(src && dst){
		
			connectModules(src, dst);
			
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

function startDraggingConnector(module, event) {

    startDraggingConnection(module, event.target);

  	// Capture mousemove and mouseup events on the page.
    module.addCnxListener(event.target, "mousemove");
    module.addCnxListener(event.target, "mouseup");

    event.preventDefault();
	event.stopPropagation();
}

function whileDraggingConnector(module, event) {

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

function stopDraggingConnector(module, event) {

  	// Stop capturing mousemove and mouseup events.
    module.removeCnxListener(event.target, "mousemove");
    module.removeCnxListener(event.target, "mouseup");

	var arrivingNode;

	var modules = window.scenes[window.currentScene].getModules();

	for(var i=0; i<modules.length; i++){
		if((dragObj.originIsInput && modules[i].isPointInOutput(event.clientX, event.clientY)) || modules[i].isPointInInput(event.clientX, event.clientY)){
			arrivingNode = modules[i];
			break;
		}
	}	

	if(!arrivingNode){
		var outputModule = window.scenes[window.currentScene].getAudioOutput();
		if((dragObj.originIsInput && outputModule.isPointInOutput(event.clientX, event.clientY)) || outputModule.isPointInInput(event.clientX, event.clientY))
			arrivingNode = outputModule;	
	}
	stopDraggingConnection(module, arrivingNode);
}




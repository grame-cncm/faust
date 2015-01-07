function drawDialControl(e,val){
	var ctx;
	var start = (e.width / 2) + 0.5;	// The 0.5 is to kick it over half a pixel for anti-aliasing
	var arcrad = (e.width / 3 );
	var textSize = Math.floor(e.width/25);

	if (e.getContext && (ctx = e.getContext('2d'))) {
		// Clear the canvas
		ctx.clearRect(0,0,e.width,e.height);

		// Draw knob background
		ctx.lineWidth = 5 + textSize;
		ctx.strokeStyle = "#ff0000";
		ctx.lineCap = "round";
		ctx.beginPath();
		ctx.arc( start, start , arcrad,Math.PI*0.75,Math.PI*0.25,false);
		ctx.stroke();

		// Draw knob foreground
		var end = Math.PI * (0.75 + (val * 0.015));
		ctx.strokeStyle = "#0000ff";
		ctx.beginPath();
		ctx.arc(start, start , arcrad, Math.PI*0.75,end,false);
		ctx.stroke();

		// Draw the text label
		ctx.font = (10 + textSize) + "px Geneva, sans-serif";
		ctx.textAlign = "center";
		ctx.textBaseline = "center";
		ctx.fillText( Math.floor(val), start, start, 30 );
	}
}

function updateDialControl(e,val){
	e.setAttribute("val", val);
	drawDialControl(e, val);
	if (e.onUpdateDial)
		e.onUpdateDial(e);
}

function startDraggingDialControl(event) {
	dragObj.currentElement = event.target;

	// Save starting positions of cursor with respect to the page.
	dragObj.cursorStartX = event.clientX + window.scrollX;
	dragObj.cursorStartY = event.clientY + window.scrollY;
	dragObj.originalValue = parseInt( event.target.getAttribute("val"));

	// Capture mousemove and mouseup events on the page.
	document.addEventListener("mousemove", whileDraggingDialControl,   true);
	document.addEventListener("mouseup",   stopDraggingDialControl, true);
	event.stopPropagation();
	event.preventDefault();
}

function whileDraggingDialControl(event) {
	var x, y, v;

	// Get cursor position with respect to the page.
	x = event.clientX + window.scrollX;
	y = event.clientY + window.scrollY;

	// Change control value by the same amount the cursor has moved.
	v = Math.max( 0, Math.min( ((x - dragObj.cursorStartX) + dragObj.originalValue), 200));
	updateDialControl( dragObj.currentElement, v/2 );
	// Don't use y yet - but would be: 	(y - dragObj.cursorStartY);

	event.stopPropagation();
	event.preventDefault();
}

function stopDraggingDialControl(event) {
	// Stop capturing mousemove and mouseup events.
	document.removeEventListener("mousemove", whileDraggingDialControl, true);
	document.removeEventListener("mouseup", stopDraggingDialControl, true);
	event.stopPropagation();
}

// This creates and returns - but DOES NOT INSERT - a new DialControl.
function createNewDialControl( size, initialValue ) {
	var e=document.createElement("canvas");
	e.width=size;
	e.height=size;
	e.className = "dialcontrol";
	e.onmousedown=startDraggingDialControl;
	updateDialControl( e, initialValue );
	return e;
}



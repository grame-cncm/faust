
//************* GLOBALS
var audioContext = null;
var idX = 0;

window.addEventListener('load', init, false);

/******************************************************************** 
**************************  INITIALIZATION **************************
********************************************************************/

function init() {

// DISABLE THE USE OF WEB WORKERS
// 	zip.useWebWorkers = false;
// 	zip.workerScriptsPath = "WebContent/";
// 	zip.workerScripts = {
//  		 deflater: ['WebContent/z-worker.js', 'WebContent/deflate.js'],
// 		  inflater: ['WebContent/z-worker.js', 'WebContent/inflate.js']
// 	};

    try {
      window.audioContext = new AudioContext();
    } catch(e) {
      alert('The Web Audio API is apparently not supported in this browser.');
    }

	activateAudioInput();
	activateAudioOutput();

	setGeneralDragAndDrop();
	
	setClickHandler( "cfe", createFaustEquivalent);

	window.buttonVal = 0;
	
	UploadTargets();
}

function activateAudioInput(){

	if (!navigator.getUserMedia) {
		navigator.getUserMedia = navigator.webkitGetUserMedia || navigator.mozGetUserMedia;
    }
        
	if (navigator.getUserMedia) {
	
    	navigator.getUserMedia({audio:true}, getDevice, function(e) {
        alert('Error getting audio input');
//         console.log(e);
    	});
	} else {
        alert('Audio input API not available');
    }
}

function getDevice(device) {

// Create an AudioNode from the stream.
    var src = document.getElementById("input");
	src.audioNode = audioContext.createMediaStreamSource(device);
        
    var i=document.createElement("div");
	i.className="node node-output";
	i.addEventListener( "mousedown", startDraggingConnector, true );
	i.innerHTML = "<span class='node-button'>&nbsp;</span>";
	src.appendChild(i);
}

function activateAudioOutput(){
	var dest = document.getElementById("output");
	dest.audioNode = window.audioContext.destination;
	
}

//-- Init drag and drop reactions
function setGeneralDragAndDrop(){

	window.ondragover = function () { this.className = 'hover'; return false; };
 	window.ondragend = function () { this.className = ''; return false; };

	window.ondrop = function (e) {
	
		uploadFile(e);
		return true;
	};
}

function setClickHandler( id, handler ) {
    var el = document.getElementById( id );
    if (el) {
	    el.addEventListener( "mousedown", handler, true );
	}
}

/******************************************************************** 
**********************  CREATE/DELETE FAUST DIV *********************
********************************************************************/

//---- Create an empty Faust module
function createFaustModule(x, y, name){

// 	nodeType = 'Drop your Faust DSP in Here';
	var input = true;
	var output = true;

	var e=document.createElement("div");
// 	e.className="module " + nodeType;
	e.className="moduleFaust";
	e.id = "module" + idX++;
	e.style.left="" + x + "px";
	e.style.top="" + y + "px";
	
	var content = document.createElement("div");
	content.className="content";
	e.appendChild(content);
    e.addEventListener("mousedown", startDraggingNode, false);
	    
	var close = document.createElement("a");
	close.href = "#";
	close.className = "close";
	close.onclick = deleteModule;
	e.appendChild( close );

	var footer = document.createElement("footer");
	footer.id = "moduleFooter";
	var editImg = document.createElement("img");
	editImg.src = "img/edit.png";
	editImg.onclick = editSource;
	
	footer.appendChild(editImg);
	e.appendChild(footer);

	// add the node into the soundfield
	document.getElementById("modules").appendChild(e);
	
	return e;
}

//---- Delete an entire Faust Module (window and content)
function deleteFaustModule(faustDiv){
	
	if(faustDiv){
	// Then delete the visual element
		faustDiv.parentNode.removeChild( faustDiv );
	}	
}

/******************************************************************** 
***********************  HANDLE DRAG AND DROP ***********************
********************************************************************/

//-- Prevent Defaul Action of the browser from happening
function preventDefaultAction(e) {
    e.preventDefault();
}

function createDSPinNewDiv(name, sourcecode, x, y){

	// Create new DSP in div (sender)
    var DSP = createDSP(sourcecode);
					
	if(DSP){
	// In case the file is not dropped on an existing module, it is created
		var faustDiv = createFaustModule(x, y, name);	
 		
		saveModuleCharacteristics(faustDiv, name, DSP, sourcecode);
		createFaustInterface(faustDiv);
		addInputOutputNodesToModule(faustDiv);				    
	}
}

function updateDSPinDiv(faustDiv, name, sourcecode){
	
	// Create new DSP in div (sender)
    var DSP = createDSP(sourcecode);
    	
	if(DSP){
	
// 	 Saving connections
		var outNode = getOutputNodeFromDiv(faustDiv);
		var outputConnections = null;
	
		if(outNode){
			if(getNodeOutputConnections(outNode))
				outputConnections = new Array().concat(getNodeOutputConnections(outNode))
		}
		
		var inNode = getInputNodeFromDiv(faustDiv);
	
		var inputConnections = null;
		if(inNode){
			if(getNodeInputConnections(inNode))
				inputConnections = new Array().concat(getNodeInputConnections(inNode));
		}
	
	// Removing existing interface
		disconnectNode(faustDiv);
		
	    deleteFaustInterface(faustDiv);
 		deleteInputOutputNodesToModule(faustDiv);	
 		
 	// Creating new interface
		saveModuleCharacteristics(faustDiv, name, DSP, sourcecode);
		createFaustInterface(faustDiv);
		addInputOutputNodesToModule(faustDiv);

	// Recalling parameters and connections
	
		inNode = getInputNodeFromDiv(faustDiv);
		outNode = getOutputNodeFromDiv(faustDiv);

		setNodeInputConnections(inNode, inputConnections);
		setNodeOutputConnections(outNode, outputConnections);
	}
}



//-- Upload content dropped on the page and create a Faust DSP with it
function uploadFile(e) {
    
	if (!e)
    	e = window.event;
	
	var x = e.x;
	var y = e.y;
	
  	preventDefaultAction(e);
  	
	var faustDiv = e.srcElement || e.target;

	while (faustDiv && faustDiv.className != "moduleFaust")
    	faustDiv = faustDiv.parentNode;
     
// CASE 1 : THE DROPPED OBJECT IS A URL TO SOME FAUST CODE   
    if(e.dataTransfer.getData('URL') && e.dataTransfer.getData('URL').split(':').shift() != "file"){
    	var url = e.dataTransfer.getData('URL');
		
		var filename = url.toString().split( '/' ).pop();
		filename = filename.toString().split('.').shift();
		
        var xmlhttp = new XMLHttpRequest();

	    xmlhttp.onreadystatechange=function(){
	    	if (xmlhttp.readyState==4 && xmlhttp.status==200)
    	    {
	    	    var dsp_code ="process = vgroup(\"" + filename + "\",environment{" + xmlhttp.responseText + "}.process);";

				if(!faustDiv)
					createDSPinNewDiv(filename, dsp_code, e.x, e.y);
				else
					updateDSPinDiv(faustDiv, filename, dsp_code);
        	}
    	}
		xmlhttp.open("GET", url, false );
    	xmlhttp.send(); 
    }
    else if(e.dataTransfer.getData('URL').split(':').shift() != "file"){

		var dsp_code = e.dataTransfer.getData('text');
	
// CASE 2 : THE DROPPED OBJECT IS SOME FAUST CODE
		if(dsp_code){
	    	dsp_code ="process = vgroup(\"" + "TEXT" + "\",environment{" + dsp_code + "}.process);";
		
			if(!faustDiv)
				createDSPinNewDiv("TEXT", dsp_code, e.x, e.y);
			else
				updateDSPinDiv(faustDiv, "TEXT", dsp_code);
				
		}
// CASE 3 : THE DROPPED OBJECT IS A FILE CONTAINING SOME FAUST CODE		
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
        	    
//         	    if(ext == "zip"){
//         	    	console.log("HEY JE SUIS UN ZIP");
//         	    }
        	    
	    		reader.onloadend = function(e) {
	    	    	dsp_code ="process = vgroup(\"" + filename + "\",environment{" + reader.result + "}.process);";

					if(!faustDiv)
						createDSPinNewDiv(filename, dsp_code, x, y);
					else
						updateDSPinDiv(faustDiv, filename, dsp_code);
	    		};
			}
		}
	}
// CASE 4 : ANY OTHER STRANGE THING
	else{
		window.alert("THIS OBJECT IS NOT FAUST COMPILABLE");
	}

}

/******************************************************************** 
**************************  DELETE ELEMENTS *************************
********************************************************************/

function getElementsByClassName(tag, className){
    var elements = document.getElementsByTagName(tag);
    var results = new Array();
    for(var i=0; i<elements.length; i++){
        if(elements[i].className == className){
            results[results.length] = elements[i];
        }
    }
    return results;
}

//---- Delete all modules
function cleanScene(){
		    	
// 	var children = document.getElementById("modules").childNodes;
		var children = getElementsByClassName("div", "moduleFaust");
	
	for(var i=0; i<children.length; i++){
// 		if(children[i].className == "moduleFaust")
			disconnectNode(children[i]);
			deleteFaustModule(children[i]);	
	}
}



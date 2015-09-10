/*				MAIN.JS
	Entry point of the Program
	
	Create the scenes
	Navigate between scenes
	Activate Physical input/output
	Handle Drag and Drop
	Create Factories and Modules

	DEPENDENCIES :
		- Accueil.js
		- Finish.js
		- Playground.js
		- Pedagogie.js
		- SceneClass.js
		
		- ModuleClass.js
		- Connect.js
		- libfaust.js
		- webaudio-asm-wrapper.js
		- Pedagogie/Tooltips.js
		
*/

"use strict";

//************* GLOBALS
var audioContext = null;
var idX = 0;

window.addEventListener('load', init, false);

/******************************************************************** 
**************************  INITIALISATION **************************
********************************************************************/

function init() {

    try {
      window.audioContext = new AudioContext();
    } catch(e) {
      alert('The Web Audio API is apparently not supported in this browser.');
    }
    
	createAllScenes();
	showFirstScene();
}

function showFirstScene(){
	window.scenes[0].showScene();
}

function createAllScenes(){
	window.scenes = [];
	
	if(window.isPedagogie){
	
		window.scenes[0] = createScene("Accueil", function(){}, function(){});
		initWelcomeScene(window.scenes[0]);
		window.scenes[1] = createScene("Pedagogie", onloadPedagogieScene, onunloadPedagogieScene);
		initPedagogieScene(window.scenes[1]);
		window.scenes[2] = createScene("Export", onloadExportScene, onunloadExportScene);
// 		Export Page doesn't need initialization
	}
	else{
		window.scenes[0] = createScene("Normal", onloadNormalScene, onunloadNormalScene);
		initNormalScene(window.scenes[0]);
	}
	
	window.currentScene = 0;
}

/******************************************************************** 
**********************  NAVIGATION BETWEEN SCENES *******************
********************************************************************/

function nextScene(){

	var index = window.currentScene;
	
	window.scenes[index].hideScene();
	window.scenes[index].unloadScene();
	

	window.currentScene = index+1;
	
	console.log("WINDOW CURRENT SCENE");
	console.log(window.scenes[index+1].getSceneContainer());
	
	window.scenes[index+1].showScene();
	window.scenes[index+1].loadScene();
}

function previousScene(){

	var index = window.currentScene;
	
	window.scenes[index].hideScene();
	window.scenes[index].unloadScene();
	
	window.scenes[index-1].showScene();
	window.scenes[index-1].loadScene();
		
	window.currentScene = index-1;
}

/******************************************************************** 
**********************  ACTIVATE PHYSICAL IN/OUTPUT *****************
********************************************************************/

function activateAudioInput(){

	if (!navigator.getUserMedia) {
		navigator.getUserMedia = navigator.webkitGetUserMedia || navigator.mozGetUserMedia;
    }
        
	if (navigator.getUserMedia) {
	
    	navigator.getUserMedia({audio:true}, getDevice, function(e) {
        alert('Error getting audio input');
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

	connectModules(src, window.scenes[window.currentScene].audioInput());
}

function activateAudioOutput(sceneOutput){
	
	var out = document.createElement("div");
	out.id = "audioOutput";
	out.audioNode = window.audioContext.destination;
	document.body.appendChild(out);
	
	connectModules(sceneOutput, out);
}

/******************************************************************** 
****************  CREATE FAUST FACTORIES AND MODULES ****************
********************************************************************/

function compileFaust(name, sourcecode, x, y, callback){

//  Temporarily Saving parameters of compilation
	window.name = name;
	window.source = sourcecode;
	window.x = x;
	window.y = y;

	var currentScene = 	window.scenes[window.currentScene];

// To Avoid click during compilation
	if(currentScene)
		currentScene.muteScene();

	var args = ["-I", "http://faust.grame.fr/faustcode/"];		 
	var factory = faust.createDSPFactory(sourcecode, args);
    callback(factory);

	if(currentScene)
		currentScene.unmuteScene();

}

function createFaustModule(factory){
	
	if (!factory) {
    	alert(faust.getErrorMessage());    
        return null;
	}
        
	var faustModule;

// can't it be just window.scenes[window.currentScene] ???
	if(isTooltipEnabled())
		faustModule = createModule(idX++, window.x, window.y, window.name, document.getElementById("modules"), window.scenes[1].removeModule);
 	else
 		faustModule = createModule(idX++, window.x, window.y, window.name, document.getElementById("modules"), window.scenes[0].removeModule);

 	faustModule.setSource(window.source);
 	faustModule.createDSP(factory); 	
	faustModule.createFaustInterface();
 	faustModule.addInputOutputNodes();
 		
 	window.scenes[window.currentScene].addModule(faustModule);
}

/******************************************************************** 
***********************  HANDLE DRAG AND DROP ***********************
********************************************************************/

//-- Init drag and drop reactions
function setGeneralDragAndDrop(){

	window.ondragover = function () { this.className = 'hover'; return false; };
 	window.ondragend = function () { this.className = ''; return false; };

	window.ondrop = function (e) {
	
		uploadFile(e);
		return true;
	};
}

//-- Init drag and drop reactions
function resetGeneralDragAndDrop(div){

	window.ondragover = function () { return false; };
 	window.ondragend = function () { return false; };
	window.ondrop = function (e) { return false; };
}


//-- Prevent Default Action of the browser from happening
function preventDefaultAction(e) {
    e.preventDefault();
}

function terminateUpload(){	
	
	var uploadTitle = document.getElementById("upload");
	uploadTitle.textContent = ""; 
			
	if(isTooltipEnabled() && sceneHasInstrumentAndEffect())
		toolTipForConnections();
}

//-- Finds out if the drop was on an existing module or creating a new one
function uploadFile(e){

	if (!e)
    	e = window.event;
    	
    var alreadyInNode = false;
    	
	var modules = window.scenes[window.currentScene].getModules();

	for(var i=0; i<modules.length; i++){
    	if(modules[i].isPointInNode(e.clientX, e.clientY))
    		alreadyInNode = true;
    }
    
	if(!alreadyInNode){
	
		var x = e.clientX;
		var y = e.clientY;
	
		uploadOn(null, x, y, e);
	}
}

//-- Upload content dropped on the page and create a Faust DSP with it
function uploadOn(module, x, y, e) {
	
  	preventDefaultAction(e);
  	
    var uploadTitle = document.getElementById("upload");
    
    uploadTitle.textContent = "CHARGEMENT EN COURS ...";
     
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

				if(module==null)
					compileFaust(filename, dsp_code, x, y, createFaustModule);
				else
					module.update(filename, dsp_code);
        	}
        	
        	terminateUpload();
    	}
    	
		xmlhttp.open("GET", url, false );
// 	Avoid error "mal formé" on firefox
		xmlhttp.overrideMimeType('text/html');
    	xmlhttp.send(); 
    }
    else if(e.dataTransfer.getData('URL').split(':').shift() != "file"){

		var dsp_code = e.dataTransfer.getData('text');
	
// CASE 2 : THE DROPPED OBJECT IS SOME FAUST CODE
		if(dsp_code){
	    	dsp_code ="process = vgroup(\"" + "TEXT" + "\",environment{" + dsp_code + "}.process);";
		
			if(!module)
				compileFaust("TEXT", dsp_code, x, y, createFaustModule);
			else
				module.update("TEXT", dsp_code);
				
			terminateUpload();	
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
				
				var type;

    	    	if (ext == "dsp"){
    	    		type = "dsp";
        	    	reader.readAsText(file);  
        	    }
        	    else if(ext == "json"){
        	    	type = "json";
        	    	reader.readAsText(file);
        	    }
        	    else
					terminateUpload();
        	    	
	    		reader.onloadend = function(e) {
	    	    	dsp_code ="process = vgroup(\"" + filename + "\",environment{" + reader.result + "}.process);";

					if(!module && type == "dsp")
						compileFaust(filename, dsp_code, x, y, createFaustModule);
					else if(type == "dsp")
						module.update(filename, dsp_code);
					else if(type == "json")
						window.scenes[window.currentScene].recallScene(reader.result);
						
					terminateUpload();
	    		};
			}
		}
	}
// CASE 4 : ANY OTHER STRANGE THING
	else{
		terminateUpload();
		window.alert("THIS OBJECT IS NOT FAUST COMPILABLE");
	}
}





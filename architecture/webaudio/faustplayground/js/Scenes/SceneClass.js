/*				SCENECLASS.JS
	HAND-MADE JAVASCRIPT CLASS CONTAINING THE API OF A GENERIC SCENE

	DEPENDENCIES :
		- ModuleClass.js
		- Main.js
		- Connect.js
*/


"use strict";

var createScene = function (identifiant, onload, onunload){
    	
//-- Graphical Scene container
	var fSceneContainer = document.createElement("div");
	fSceneContainer.id = identifiant;

//-- Audio Input/Output
	var fAudioOutput, fAudioInput;
	
//-- Modules contained in the scene
	var fModuleList = new Array();

/*******************************  PUBLIC METHODS  **********************************/	
  return {

    deleteScene: function() {
		this.cleanModules();
    	this.hideScene();
    	this.muteScene();
    },
    
	integrateSceneInBody: function(){
		document.body.appendChild(fSceneContainer);	
	},

/*************** ACTIONS ON AUDIO IN/OUTPUT ***************************/
  	integrateInput: function(afterWork){

		fAudioInput = createModule(idX++, 0, 0, "input", fSceneContainer, this.removeModule);
		fAudioInput.hideModule();

		compileFaust("input", "process=_,_;", 0, 0, this.integrateAudioInput);
		afterWork();
	},
	integrateOutput: function(afterWork){

		fAudioOutput = createModule(idX++, 0, 0, "output", fSceneContainer, this.removeModule);
		fAudioOutput.hideModule();
		compileFaust("output", "process=_,_;", 0, 0, this.integrateAudioOutput);

		afterWork();
	},

	integrateAudioOutput : function(factory){
		if(fAudioOutput){
		 	fAudioOutput.setSource("process=_,_;");
			fAudioOutput.createDSP(factory);
			activateAudioOutput(document.getElementById("sceneOutput"));
		}
	},
	integrateAudioInput : function(factory){			
		if(fAudioInput){
		 	fAudioInput.setSource("process=_,_;");
			fAudioInput.createDSP(factory);
			activateAudioInput();
		}
	},
	
	getAudioOutput: function(){ return fAudioOutput;},
	getAudioInput: function(){ return fAudioInput;},
	
/************************* SHOW/HIDE SCENE ***************************/
	showScene: function(){ fSceneContainer.style.visibility = "visible";},
	hideScene: function(){ fSceneContainer.style.visibility = "hidden";},
	
/*********************** MUTE/UNMUTE SCENE ***************************/
	muteScene: function(){ 
		var out = document.getElementById("audioOutput");
		disconnectModules(fAudioOutput, out);
	},
	unmuteScene: function(){ 
		var out = document.getElementById("audioOutput");
		connectModules(fAudioOutput, out);
	},
	
/******************** HANDLE MODULES IN SCENE ************************/
	getModules: function(){ return fModuleList; },
	addModule: function(module){ fModuleList.push(module);},
	removeModule: function(module){ fModuleList.splice(fModuleList.indexOf(module), 1); },
	
	cleanModules: function (){
		
		for(var i=fModuleList.length-1; i>=0; i--){
		
				fModuleList[i].deleteModule();
				this.removeModule(fModuleList[i]);
		}
	},
		
/*********************** LOAD/UNLOAD SCENE ***************************/
	loadScene:function(){
		onload(this);
	},
	unloadScene: function(){
		onunload(this);
	},

/*********************** SAVE/RECALL SCENE ***************************/
	saveScene: function(){
	
	for(var i=0; i<fModuleList.length; i++){
		fModuleList[i].patchID = i+1;
	}
	
	fAudioOutput.patchID = 0;
	
	var json = '{';

	for(var i=0; i<fModuleList.length; i++){
		if(i != 0)
			json+=',';
			
		json += '"' + fModuleList[i].patchID.toString() + '":['
		
		json += '{"x":"' + fModuleList[i].getModuleContainer().getBoundingClientRect().left+ '"},';
		json += '{"y\":"' + fModuleList[i].getModuleContainer().getBoundingClientRect().top + '"},';
		json += '{"name\":"' + fModuleList[i].getName() + '"},';
		json += '{"code":' + JSON.stringify(fModuleList[i].getSource()) + '},';
		
		var inputs = fModuleList[i].getInputConnections();
		
		if(inputs){
		
			json += '{"inputs":[';
			for(var j=0; j<inputs.length; j++){
				if(j !=0)
					json+=',';		
			
				json += '{"src":"' + inputs[j].source.patchID.toString() + '"}';
			}
			json += ']},';
		}
		
		var outputs = fModuleList[i].getOutputConnections() ;
		if(outputs){
			json += '{"outputs":[';		

	
			for(var j=0; j<outputs.length; j++){
				if(j !=0)
					json+=',';		
			
				json += '{"dst":"' + outputs[j].destination.patchID.toString() +'"}';
			}		

			json += ']},';
		}
		
		var params = fModuleList[i].getDSP().controls();
		if(params){
			json += '{"params":[';		
	
			for(var j=0; j<params.length; j++){
				if(j !=0)
					json+=',';		
			
				json += '{"path":"' + params[j] +'"},';
				json += '{"value":"' + fModuleList[i].getDSP().getValue(params[j]) +'"}';
			}		

			json += ']}';
		}
		
		json += ']';
	}

	json += '}';
	
// 	console.log(json);
	return json;
},
	recallScene: function(json){

		window.currentNumberDSP = window.scenes[window.currentScene].getModules().length;

		var data = JSON.parse(json);
	
		var sel;	
		for(sel in data){
						
		    var dataCopy = data[sel];
    
			var newsel;
			var name, code, x, y;
		
			for (newsel in dataCopy) {
				var mainData = dataCopy[newsel];
        		if(mainData["name"])
					name = mainData["name"];
        		else if(mainData["code"])
        			code = mainData["code"];
        		else if(mainData["x"])
        			x = mainData["x"];
        		else if(mainData["y"])
        			y = mainData["y"];
        		else if(mainData["inputs"])
        			window.inputs = mainData["inputs"];
        		else if(mainData["outputs"])
        			window.outputs = mainData["outputs"];
        		else if(mainData["params"])
        			window.params = mainData["params"];
			}
			compileFaust(name, code, x, y, this.createModuleAndConnectIt);
		}		
	},
	
	createModuleAndConnectIt: 	function(factory){

		if (!factory) {
    		alert(faust.getErrorMessage());    
        	return null;
		}
    
		var faustModule;

		faustModule = createModule(idX++, window.x, window.y, window.name, document.getElementById("modules"), window.scenes[window.currentScene].removeModule);

 		faustModule.setSource(window.source);
	 	faustModule.createDSP(factory); 	
 	
 		if(window.params){
			for(var i=0; i<window.params.length; i++){

				if(window.params[i] && window.params[i+1]){
					faustModule.addParam(window.params[i]["path"], window.params[i+1]["value"]);
					i+1;
				}	
			}
			faustModule.recallParams();
		}
 	
 	
		faustModule.createFaustInterface();
 		faustModule.addInputOutputNodes();

		this.addModule(faustModule);
	
// WARNING!!!!! Not right in an asynchroneous call of compileFaust
		if(window.inputs){
			for(var i=0; i<window.inputs.length; i++){
		
// 		NOT WORKING WHEN OTHER DSPs IN THE SCENE !!!!! 
				var src = this.getModules()[window.inputs[i]["src"]-1 +window.currentNumberDSP];
				if(src)
					createConnection(src, src.getOutputNode(), faustModule, faustModule.getInputNode());	
			}
		}
	
		if(window.outputs){
			for(var i=0; i<window.outputs.length; i++){

// 		NOT WORKING WHEN OTHER DSPs IN THE SCENE !!!!! 
				var dst = window.scenes[window.currentScene].getModules()[window.outputs[i]["dst"]+window.currentNumberDSP-1];
			
				if(dst)
					createConnection(faustModule, faustModule.getOutputNode(), dst, dst.getInputNode());
	
				else if(window.outputs[i]["dst"] == 0)
					createConnection(faustModule, faustModule.getOutputNode(), this.fAudioOutput, this.fAudioOutput.getInputNode());
			}
		}
	},

/*********************** SElF EXPLANATORY ***************************/	
	getSceneContainer: function(){ return fSceneContainer;}
  }
}

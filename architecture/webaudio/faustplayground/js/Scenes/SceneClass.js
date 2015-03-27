"use strict";

var createScene = function (identifiant, start, stop){
    	
	var scene = document.createElement("div");
	scene.id = identifiant;

	var audioOutput;
	
	var moduleList = new Array();
	
  return {
  
    deleteScene: function() {
		this.cleanDSPs();
    	this.hideScene();
    	this.muteScene();
    },
// 	deleteScene: function(){
// 		document.body.removeChild(scene);
// 	},
	getSceneContainer: function(){ return scene;},
	integrateOutput: function(factory){
		
		if(audioOutput){
		 	audioOutput.setSource("process=_,_;");
			audioOutput.setDSP(factory);
			activateAudioOutput(document.getElementById("sceneOutput"));
// 			this.unmuteScene();
		}
	},
	integrateSceneInPage: function(afterWork){
	
		document.body.appendChild(scene);

		audioOutput = createNode(idX++, 0, 0, "output", scene, this.removeModule);
		audioOutput.hideNode();
		compileFaust("output", "process=_,_;", 0, 0, this.integrateOutput);
		afterWork();
	},
	
	showScene: function(){ scene.style.visibility = "visible";},
	hideScene: function(){ scene.style.visibility = "hidden";},
	
	muteScene: function(){ mute(audioOutput); },
	unmuteScene: function(){ unmute(audioOutput);},
	
	getModules: function(){
		return moduleList;
	},
	addModule: function(module){ moduleList.push(module);},
	removeModule: function(module){ moduleList.splice(moduleList.indexOf(module), 1); },
	
	cleanDSPs: function (){
		
		for(var i=moduleList.length-1; i>=0; i--){
		
				moduleList[i].deleteNode();
				this.removeModule(moduleList[i]);
		}
	},
		
	startScene:function(){
		start(this);
	},
	stopScene: function(){
		stop(this);
	},
	
	audioOutput: function(){ return audioOutput;}
  }
}

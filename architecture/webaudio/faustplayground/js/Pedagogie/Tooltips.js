/*				TOOLTIPS.JS
	Add tooltips for the pedagogical version of the playground
		
	DEPENDENCIES : 
		- SceneClass.js
		- ModuleClass.js
*/


/*************** ALL TOOLTIP CHOICES ***************************/
function changeSceneToolTip(toolTipNumber){

	var subtitle;

	if(document.getElementById("sceneToolTip"))
		subtitle = document.getElementById("sceneToolTip");
	else{
		subtitle = document.createElement('span');
		subtitle.id="sceneToolTip";
		document.getElementById("header").appendChild(subtitle);
	}

	if(toolTipNumber == 0){
		subtitle.textContent = "    Choisis de télécharger ton application, " + document.getElementById("PatchName").innerHTML + ", pour ton smartphone ou sous forme de page web";
	}
	else if(toolTipNumber == 1){
		subtitle.textContent = "    Glisse ta souris sur la bibliothèque Faust pour découvrir son contenu";
	}
	else if(toolTipNumber == 3){
		subtitle.textContent = "    Relie ton instrument à ton effet en connectant le noeud rouge au noeud vert";
	}
	else if(toolTipNumber == 4){
		subtitle.textContent = "    Relie ton effet à la sortie audio";
	}
	else if(toolTipNumber == 5){
		subtitle.textContent = "    Joue avec ton/tes instrument(s)";
	}
	else if(toolTipNumber == 6){
		subtitle.textContent = "    Choisis au moins un instrument";
	}
}

/*************** ACTIVATE/DISACTIVATE TOOLTIPS ****************/
function enableTooltips(){
	window.tooltips = true;
}

function disableTooltips(){
	window.tooltips = false;
}

function isTooltipEnabled(){
	return window.tooltips;
}


/******** INTERROGATE THE SCENE TO CREATE RIGHT TOOLTIP ******/
function sceneHasInstrumentAndEffect(){

	var modules = window.scenes[window.currentScene].getModules();

	if(modules.length<2)
		return false
	else{
		
		var hasInstrument = false;
		var hasEffect = false;
				
		for (var i = 0; i < modules.length; i++) {
			if(modules[i].getInputNode())
				hasEffect = true;
			else
				hasInstrument = true;
		}
	}
	
	return hasInstrument && hasEffect;
}

function isInstrumentConnected(){
				
	var modules = window.scenes[window.currentScene].getModules();
				
	for (var i = 0; i < modules.length; i++) {
		if(!modules[i].getInputNode() && modules[i].getOutputConnections() && modules[i].getOutputConnections().length > 0)
			return true;
	}
	
	return false;
}

function toolTipForLibrary(type){

	var tooltip = document.createElement("div");

	var image = document.createElement('span');
	image.className= "number";
	
	var subtitle;
			
	if(type == "instruments"){
					
		image.textContent = "1";
		subtitle = document.createTextNode( "     Glisse l'instrument de ton choix dans la scene");
	}
	else{
				
		image.textContent = "2";	
		subtitle = document.createTextNode( "     Glisse l'effet de ton choix dans la scene");
	}

	tooltip.appendChild(image);
	tooltip.appendChild(subtitle);
	return tooltip;
}

function toolTipForConnections(){

	var currentScene = window.scenes[window.currentScene];

	if(window.tooltips){
		
		var connectedNode = currentScene.getAudioOutput();
		
		while(connectedNode){
	
// 			Node is an effect
			if(connectedNode.getInputNode()){

//	 		Node is connected
				if(connectedNode.getInputConnections() && connectedNode.getInputConnections().length > 0)		
					connectedNode = connectedNode.getInputConnections()[0].source;
//	 		Node is not connected and there is everything on the scene
				else if(sceneHasInstrumentAndEffect()){
					if(!isInstrumentConnected())
						changeSceneToolTip(3);
					else
						changeSceneToolTip(4);
				
					connectedNode = null;
				}
// 			Node is not connected and there are no instruments on the scene
				else{
					changeSceneToolTip(6);
					connectedNode = null;
				}
			}
//	 		Node is an instrument
			else{
				changeSceneToolTip(5);
				connectedNode = null;
			}
		}
	}
}





function welcomePage(scene){

	scene.integrateSceneInPage();
	
	var container = scene.getSceneContainer();
	
	var title = document.createElement("div");
	title.className = "sceneTitle";
	title.appendChild(document.createTextNode("Bienvenue Sur L'Aire de Jeu\r\n FAUST"));

	container.appendChild(title);
	
	var subtitle = document.createElement("div");
	subtitle.className = "sceneSubtitle";
	subtitle.appendChild(document.createTextNode("Ici tu pourras créer ton application musicale"));
	container.appendChild(subtitle);
	
	container.appendChild(document.createElement("br"));
	container.appendChild(document.createElement("br"));
	container.appendChild(document.createElement("br"));
	
	var nametitle = document.createElement("div");
	nametitle.className = "sceneSubtitle";
	nametitle.id = "NameTag";
	nametitle.appendChild(document.createTextNode("Indique ton nom :     "));

	container.appendChild(nametitle);
	
	var nameTag = document.createElement("textarea");
	nameTag.id = "nameTag";
	nameTag.rows = "1";
	nameTag.cols = "20";
	nameTag.style.position="relative";
	nameTag.style.marginTop="auto";
	nameTag.style.contenteditable = "true";
	nameTag.style.resize = "none";

	nametitle.appendChild(nameTag);
	nameTag.focus();
	
	var startButton = document.createElement("div");
	startButton.id= "startButton";
	startButton.className= "orangeButton";
	startButton.textContent = "Démarrer";
	startButton.onclick = function(event){ startButton.style.visibility = "hidden"; nextScene();}
	startButton.style.visibility = "hidden";
	
	container.appendChild(startButton);
// 		
//  Prevent the creation of a new line in text area
	nameTag.addEventListener("keydown", function(e) {
		if (e.keyCode == 13){
			e.preventDefault(); // sometimes useful
		}
	}, false);
	
//  Hide/Show Button when text area is edited
	nameTag.addEventListener("keyup", function(e) {
   		if (!e) { 
   			var e = window.event; 
   		}
		
	    // Enter is pressed
	    if (e.keyCode == 13){
			e.preventDefault(); // sometimes useful
		
			if(nameTag.value != ""){
				startButton.style.visibility = "hidden";
				nextScene();
			}
		}
		else if(nameTag.value != ""){
	    	startButton.style.visibility = "visible";
		}
		else if( (e.keyCode == 46 || e.keyCode==8) && nameTag.value == ""){
	    	startButton.style.visibility = "hidden";
		}
	}, false);	
	
	scene.hideScene();
}
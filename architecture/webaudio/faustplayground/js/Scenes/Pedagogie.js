
// Add visual elements to Pedagogical Playground Scene
function pedagogiePage(scene){

	scene.integrateSceneInPage();
	var container = scene.getSceneContainer();
	
	var svgCanvas = document.createElementNS("http://www.w3.org/2000/svg", "svg");
	svgCanvas.id="svgCanvas";
	svgCanvas.version="1.1";
	svgCanvas.style.cssText="position:absolute; width:100%; height:100%; top:0; left:0; z-index:-1;";
	container.appendChild(svgCanvas);
	
	var head = document.createElement("header");
	head.id = "header";
	container.appendChild(head);
		
	var myScene = document.createElement("div");
	myScene.id = "PatchName";
	myScene.className = "sceneTitle";
	myScene.textContent = "Scène de " + "";
	head.appendChild(myScene);

	if(isTooltipEnabled())
		changeSceneToolTip(1);

	var uploadDiv = document.createElement("div");
	uploadDiv.id = "upload";
	uploadDiv.className = "uploading";
	head.appendChild(uploadDiv);
	
	var moduleContainer = document.createElement("section");
	moduleContainer.id = "modules";
	moduleContainer.className = "container";
	container.appendChild(moduleContainer);
	
	var footer = document.createElement("div");
	footer.id = "footer";
	container.appendChild(footer);
	
	var equButton = document.createElement("div");
	equButton.className = "grayButton";
	equButton.style.cssText = "position: relative; width: 300px; top:20%;";
	footer.appendChild(equButton);

	var equText = document.createElement("a");
	equText.id = "cfe";
	equText.textContent = "FINALISE TON APPLICATION";
	equButton.onclick = function(){nextScene();};
	equButton.appendChild(equText);
	
	var subText = document.createElement("div");		
	subText.textContent = "pour l'emmener avec toi";
	subText.style.cssText = "font-size:11px;";
	equButton.appendChild(subText);

	var linkWilson = document.createElement("div");
	linkWilson.className = "link";
	linkWilson.style.right = "10px";
	linkWilson.textContent = "Extension of the WebAudio Playground by ";
	footer.appendChild(linkWilson);

	var alink = document.createElement("a");
	alink.href = "https://github.com/cwilso/WebAudio";
	alink.textContent = "Chris Wilson";
	linkWilson.appendChild(alink);
	
	var imageLogo = document.createElement('img');
	imageLogo.className = "logoGrame";
	imageLogo.src= "img/grame.png";
	footer.appendChild(imageLogo);
	
	var destDiv = scene.audioOutput();
	
	var destDiv = document.createElement("div");
	destDiv.id = "sceneOutput";
	destDiv.className = "destination";
	container.appendChild(destDiv);
	
	var outText = document.createElement("span");
	outText.className = "text";
	outText.textContent = "SORTIE AUDIO";
	destDiv.appendChild(outText);
	
	var node = document.createElement("div");
	node.className = "node node-input";
	destDiv.appendChild(node);
	
	var nodeimg = document.createElement("span");
	nodeimg.className = "node-button";
	nodeimg.value = "&nbsp;";
	node.appendChild(nodeimg);
	
	scene.audioOutput().setInputOutputNodes(node, null);
	
	initLibrary(container);
	
	activateAudioOutput(destDiv);
	scene.hideScene();	
}

// Load And UnLoad Pedagogical Playground Scene
function startPeda(scene){
	
	document.getElementById("PatchName").textContent = "Scène de   " + document.getElementById("nameTag").value;
	document.getElementById("PatchName").style.cssText = "color:white";
	document.body.style.background = "url('img/body-bkg.gif') 0 0 repeat";
	setGeneralDragAndDrop();
	changeSceneToolTip(1);
	scene.unmuteScene();
}

function stopPeda(scene){

	scene.muteScene();
}



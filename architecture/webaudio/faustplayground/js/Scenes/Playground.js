"use strict";

/******************************************************************** 
**************************  INITIALIZATION **************************
********************************************************************/

function normalPage(scene){

		var container = scene.getSceneContainer();
	
		var svgCanvas = document.createElementNS("http://www.w3.org/2000/svg", "svg");
		svgCanvas.id="svgCanvas";
		svgCanvas.version="1.1";
		svgCanvas.style.cssText="position:absolute; width:100%; height:100%; top:0; left:0; z-index:-1;";
		container.appendChild(svgCanvas);
	
//--------- HEADER
		var head = document.createElement("header");
		head.id = "header";
		container.appendChild(head);
	
		var myScene = document.createElement("div");
		myScene.id = "PatchName";
		myScene.className = "sceneTitle";
		myScene.style.contentEditable = "true";
		myScene.textContent = "Patch";
		head.appendChild(myScene);

		var uploadDiv = document.createElement("div");
		uploadDiv.id = "upload";
		uploadDiv.className = "uploading";
		head.appendChild(uploadDiv);
	
//----------- MODULES
		var moduleContainer = document.createElement("section");
		moduleContainer.id = "modules";
		moduleContainer.className = "container";
		container.appendChild(moduleContainer);
	

//------------ INPUT/OUTPUT
		var destDiv = document.createElement("div");
		destDiv.id = "sceneOutput";
		destDiv.className = "destination";
// 	destDiv.DSP = createDSP("process=_,_;");
		container.appendChild(destDiv);

// 		var footer = document.createElement("div");
// 		footer.id = "footer";
// 		footer.style.cssText = "width:85%; height:15%; z-index:0;";
// 		container.appendChild(footer);

		var fwurl = document.createElement("input");
		fwurl.id = "faustweburl";
		fwurl.style.cssText = " border:0px; text-align:center; font-size:16px; background-color:transparent; outline: 0px solid transparent; text-align:center;";
		fwurl.onkeyup=onEnterKey;
		fwurl.value = "http://faustservice.grame.fr";
		destDiv.appendChild(fwurl);

		var subfooter = document.createElement('div');
		destDiv.appendChild(subfooter);

		var refButton = document.createElement("div");
		refButton.id = "refreshButton";
		refButton.onclick = UploadTargets;
		refButton.style.cssText = "position:absolute; left:0%; top:25px;";
		refButton.innerHTML = '<svg version="1.0" xmlns="http://www.w3.org/2000/svg" width="50.000000pt" height="50.000000pt" viewBox="0 0 50.000000 50.000000" preserveAspectRatio="xMidYMid meet"><g transform="translate(0.000000,50.000000) scale(0.100000,-0.100000)" fill="#000000" stroke="none"> <path d="M186 309 c-37 -29 -37 -89 0 -118 28 -22 69 -27 93 -12 23 15 3 30 -33 24 -29 -4 -37 -1 -51 21 -16 24 -16 28 -1 51 18 27 63 34 84 13 17 -17 15 -31 -3 -24 -20 7 -19 1 6 -28 l22 -25 18 24 c20 25 25 40 9 30 -5 -3 -16 7 -24 23 -25 47 -75 56 -120 21z"/></g></svg>';
		subfooter.appendChild(refButton);

		var selectDiv = document.createElement("div");
		selectDiv.style.cssText = "position:absolute; left:25%; top:35px";
		subfooter.appendChild(selectDiv);
	
		var selectPlatform = document.createElement("select");
		selectPlatform.id = "platforms";
		selectPlatform.style.cssText = "float:bottom; display:block; margin-bottom:5px; padding:0;";
		selectPlatform.className = "platforms";
		selectPlatform.onchange = updateArchitectures;
		selectDiv.appendChild(selectPlatform);
	
		var selectArch = document.createElement("select");
		selectArch.id = "architectures";
		selectArch.style.cssText = "float:bottom; display:block; margin-bottom:15px; padding:0;";
		selectArch.className = "architectures";
		selectDiv.appendChild(selectArch);
	
		var equButton = document.createElement("input");
		equButton.type = "submit";
		equButton.className = "grayButton";
		equButton.style.cssText = "position:absolute; top:20%; left:25%;";
		equButton.onclick = exportPatch;
		equButton.value = "Export";
		subfooter.appendChild(equButton);

		var linkWilson = document.createElement("div");
		linkWilson.className = "link";
		linkWilson.style.cssText = "left:100px; z-index:2;";
		linkWilson.textContent = "Extension of the WebAudio Playground by ";
		container.appendChild(linkWilson);

		var alink = document.createElement("a");
		alink.href = "https://github.com/cwilso/WebAudio";
		alink.textContent = "Chris Wilson";
		linkWilson.appendChild(alink);
	
		var srcDiv = document.createElement("div");
		srcDiv.id = "input";
		srcDiv.className = "source";
		container.appendChild(srcDiv);
	
		var inText = document.createElement("span");
		inText.className = "text";
		inText.style.cssText = "position:absolute; top:60%;";
		inText.textContent = "PHYSICAL INPUT";
		srcDiv.appendChild(inText);
	
		var imageDiv = document.createElement('div');
		imageDiv.style.cssText = "bottom:4px; position:absolute; margin-left:auto; margin-right : auto; ";
		srcDiv.appendChild(imageDiv);
			
		var imageLogo = document.createElement('img');
// 	imageLogo.style.cssText = "float:left; display:block; margin:12px; padding:0;";
		imageLogo.className = "logoGrame";
		imageLogo.src= "img/grame.png";
		imageDiv.appendChild(imageLogo);
	
		var outText = document.createElement("span");
		outText.className = "text";
		outText.style.cssText = "position:absolute; top:60%;";
		outText.textContent = "PHYSICAL OUTPUT";
		destDiv.appendChild(outText);
	
		var node = document.createElement("div");
		node.className = "node node-input";
		destDiv.appendChild(node);
	
		var nodeimg = document.createElement("span");
		nodeimg.className = "node-button";
		nodeimg.value = "&nbsp;";
		node.appendChild(nodeimg);
	
	scene.integrateSceneInPage(function(){
	
		scene.audioOutput().setInputOutputNodes(node, null);
		scene.audioInput().setInputOutputNodes(null, input);
			
// 		activateAudioInput();
		
		console.log("inputActivation");
// 	activateAudioOutput(destDiv);
// 	scene.hideScene();
	
		startPage(scene);
// 	setGeneralDragAndDrop();
			UploadTargets();
		});
}

function onEnterKey(e){
	if (!e) { var e = window.event; } 
	
	if (e.keyCode == 13){ 
		e.preventDefault(); 
		UploadTargets();
	}
}

function startPage(scene){

	setGeneralDragAndDrop();
	scene.unmuteScene();
}

function stopPage(scene){
	scene.muteScene();
}


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

// 		var titleDiv = document.createElement("div");
// 		titleDiv.textContent = "EXPORT PATCH : ";
// 		titleDiv.style.cssText = "position:absolute; left: 15%; top: 30%; font-size : 20px;";
// 		footer.appendChild(titleDiv);
// 	
		var subfooter = document.createElement('div');
// 		subfooter.style.cssText = "position: relative; left: 40%; top:20px;";
		destDiv.appendChild(subfooter);

		var fwurl = document.createElement("input");
		fwurl.id = "faustweburl";
		fwurl.style.cssText = " border:0px; text-align:center; font-size:16px; background-color:transparent; outline: 0px solid transparent; text-align:center;margin-bottom:30px;" 
// 		contenteditable="true" 
// 		fwurl.style.cssText = "float:left; display:block; margin-top:30px; margin-right:20px; padding:1px; background-color:transparent;";
		fwurl.value = "http://faustservice.grame.fr";
		subfooter.appendChild(fwurl);

		var selectDiv = document.createElement("div");
// 		selectDiv.style.cssText = "float:left; display:block; margin:12px; padding:0;";
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
		equButton.style.cssText = "position:absolute; top:60%; left:50px;";
// 		equButton.style.cssText = "float:left; display:block; position:absolute; bottom: 170px; left:50px;";
// 		equButton.style.cssText = "float:left; display:block; position:relative; margin-top: 20px; margin-left: 20px;";
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
		inText.style.cssText = "position:absolute; top:30%;";
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
		outText.style.cssText = "position:absolute; top:30%;";
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

function startPage(scene){

	setGeneralDragAndDrop();
	scene.unmuteScene();
}

function stopPage(scene){
	scene.muteScene();
}


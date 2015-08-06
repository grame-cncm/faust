/*				FINISH.JS
	Init Export Scene with all its graphical elements
		
	This is the final scene of the Pedagogical Playground
		
	DEPENDENCIES :
		- Scene.js
		
*/


"use strict";

/******************************************************************** 
******************* INIT/LOAD/UNLOAD EXPORT SCENE ******************
********************************************************************/

function onloadExportScene(scene)
{
// 	window.scenes[1].saveScene();

	scene.integrateSceneInBody();
	
	document.body.style.background = "url('"+window.baseImg + "output-bkg.gif') 0 0 repeat";
	var appName = prompt("Choisis le nom de ton application", "");

	if (appName == null)
		appName = "MonApplication";
			
	initExportScene(scene, appName);
}

function initExportScene(scene, name)
{
	var container = scene.getSceneContainer();

//--------- HEADER
	var head = document.createElement("header");
	head.id = "header";
	container.appendChild(head);
		
	var mySceneName = document.createElement("div");
	mySceneName.id = "exportName";
	mySceneName.className = "sceneTitle";
	mySceneName.textContent = "Télécharge " +name;
	head.appendChild(mySceneName);
	
	var mySceneSub = document.createElement("div");
	mySceneSub.id = "sceneSubtitle";
	mySceneSub.textContent = "Ton Application Android";
	head.appendChild(mySceneSub);

//--------- QRCORE ZONE
	var androidApp = document.createElement("div");
	androidApp.id= "androidButton";
	container.appendChild(androidApp);

	var androidImg = document.createElement("img");
	androidImg.id = "androidImg";
	androidImg.src = window.baseImg + "loader.gif";
	androidApp.appendChild(androidImg);

// -- Once you have been to the finish scene, you probably don't need tooltips anymore.
	if (isTooltipEnabled()) {
		changeSceneToolTip(0);
		disableTooltips();
	}
//--------- PREVIOUS SCENE BUTTON
	var backImg = document.createElement("img");
	backImg.id = "backImg";
	backImg.src = window.baseImg + "BACK.png";
	backImg.onclick = function(){ previousScene()};
	container.appendChild(backImg);

//-------- GET FAUST EQUIVALENT & LAUNCH EXPORT
	var faustSource = getFaustEquivalent(window.scenes[1], name)
	
	if (faustSource)
		getAndroidApp(name, faustSource);
}

function onunloadExportScene(scene)
{
//--- clean graphical elements
	var children = scene.getSceneContainer().childNodes;
	
	for (var i=children.length-1; i>=0; i--)
		scene.getSceneContainer().removeChild(children[i]);
}

/******************************************************************** 
***********************  EXPORT DSP ANDROID ***********************
********************************************************************/

//--- Create QrCode once precompile request has finished
function terminateAndroidMenu(sha)
{
	if (document.getElementById("androidImg"))
		document.getElementById("androidButton").removeChild(document.getElementById("androidImg"));

	var url = "http://faustservice.grame.fr";

	if (document.getElementById("androidButton")) {
	
		var qrcodeDiv = getQrCode(url, sha, "android", "android", "binary.apk", 170);
		qrcodeDiv.id = "qrcode";
	
		document.getElementById("androidButton").appendChild(qrcodeDiv);
		qrcodeDiv.onclick = getAndroidApp;
	}
}

function exportAndroidCallback(sha)
{
	sendPrecompileRequest("http://faustservice.grame.fr", sha, "android", "android", terminateAndroidMenu);
}

function getAndroidApp(name, source)
{
	getSHAKey("http://faustservice.grame.fr", name, source, exportAndroidCallback);
}

/******************************************************************** 
************************* PLUS UTILISÉ...  *************************
******************** Des tentatives graphiques  ********************
********************************************************************/

// Plus utilisé (c'était pour faire des flèches en svg)
function drawArrow(svgCanvas, x1, y1, x2, y2)
{
	// Create a connector visual line
	var svgns = "http://www.w3.org/2000/svg";
	
	var line1 = document.createElementNS(svgns, "line");
	line1.setAttributeNS(null, "x1", x1);
	line1.setAttributeNS(null, "y1", y1);
    line1.setAttributeNS(null, "x2", x2-25);
    line1.setAttributeNS(null, "y2", y1);
    line1.setAttributeNS(null, "stroke", "black");
	line1.setAttributeNS(null, "stroke-width", "10");
	dragObj.connectorShape=line1;

// 	var line2 = document.createElementNS(svgns, "line");
// 	line2.setAttributeNS(null, "x1", x2);
// 	line2.setAttributeNS(null, "y1", y1);
//     line2.setAttributeNS(null, "x2", x2);
//     line2.setAttributeNS(null, "y2", y2);
//     line2.setAttributeNS(null, "stroke", "black");
// 	line2.setAttributeNS(null, "stroke-width", "2");
// 	dragObj.connectorShape=line2;

	var baseY = y2 - 5;
	var baseX = x2 - 30;
	
	var baseXX = x2 -20;
	
	var rightY = baseY + 10;
	var rightX = baseX;

	var dOption = "M" + baseX + "," + baseY + "L" + rightX + "," + rightY + "L" + baseXX + "," + y2 + "Z";

	var triangle = document.createElementNS(svgns, "path");
	triangle.setAttributeNS(null, "d", dOption);
    triangle.setAttributeNS(null, "stroke", "black");
	triangle.setAttributeNS(null, "stroke-width", "15");
	triangle.setAttributeNS(null, "fill", "black");
	dragObj.connectorShape=triangle;

    svgCanvas.appendChild(line1);
//     svgCanvas.appendChild(line2);
    svgCanvas.appendChild(triangle);
}

// Plus utilisé (c'était pour faire l'export en page Web)
function equFaustModule(factory)
{
	if (!factory) {
    	alert(faust.getErrorMessage());    
        return null;
	}
       
    var scene = window.scenes[2];   
  	var faustModule = createNode(idX++, window.x, window.y, window.name, window.parent, scene.removeModule);

 	faustModule.setSource(window.source);
 	faustModule.setDSP(factory); 	
	faustModule.createInterface();
 	faustModule.addInputOutputNodesToModule();
 		
	faustModule.setParams(window.savedParams);
 		
 	disconnectModule(faustModule);
	faustModule.deleteInputOutputNodesToModule();
	connectModules(faustModule, scene.getAudioOutput());
	var connector = new Object();

	saveConnection(faustModule, scene.getAudioOutput(), connector, null);
		
	scene.getAudioOutput().addInputConnection(connector);
	faustModule.addOutputConnection(connector);
	
	faustModule.getContainer().style.cssText = "position:relative; margin-left:auto; margin-right:auto; top:10%; width: 170px;";
	faustModule.removeListener(faustModule.getContainer(), "mousedown");	
 	
 	scene.addModule(faustModule);
 	
 	var circle = document.getElementById("bubble");
 		
	var width = faustModule.getContainer().getBoundingClientRect().width + 70;
	var height = faustModule.getContainer().getBoundingClientRect().height + 100;
		
	circle.style.width = width.toString() + "px";
	circle.style.height = height.toString() + "px";

// 	scene.unmuteScene();
		
// 	getWebApp(faustModule);
	getAndroidApp(window.name, window.source);
}

function terminateWebMenu(sha)
{
	document.getElementById("webButton").removeChild(document.getElementById("webImg"));

	var url = "http://faustservice.grame.fr" + "/" + sha +"/web/asmjs-links/binary.zip";
    var link = document.createElement('a');
	link.href = url;
	var title = document.createElement("h6");
	title.appendChild(document.createTextNode("Télécharger page Web"));
	
	link.appendChild(title);
	document.getElementById("webButton").appendChild(link);
}

function exportWebCallback(sha)
{
	sendPrecompileRequest("http://faustservice.grame.fr", sha, "web", "asmjs", terminateWebMenu);
}	

function getWebApp(faustDiv)
{
	var shaKey = getSHAKey("http://faustservice.grame.fr", faustDiv.getName(), faustDiv.getSource(), exportWebCallback);
}



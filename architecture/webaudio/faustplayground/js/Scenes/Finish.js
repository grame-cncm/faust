function drawArrow(svgCanvas, x1, y1, x2, y2){
	// Create a connector visual line
	var svgns = "http://www.w3.org/2000/svg";
	
	var line1 = document.createElementNS(svgns, "line");
	line1.setAttributeNS(null, "x1", x1);
	line1.setAttributeNS(null, "y1", y1);
    line1.setAttributeNS(null, "x2", x2);
    line1.setAttributeNS(null, "y2", y1);
    line1.setAttributeNS(null, "stroke", "black");
	line1.setAttributeNS(null, "stroke-width", "2");
	dragObj.connectorShape=line1;

	var line2 = document.createElementNS(svgns, "line");
	line2.setAttributeNS(null, "x1", x2);
	line2.setAttributeNS(null, "y1", y1);
    line2.setAttributeNS(null, "x2", x2);
    line2.setAttributeNS(null, "y2", y2);
    line2.setAttributeNS(null, "stroke", "black");
	line2.setAttributeNS(null, "stroke-width", "2");
	dragObj.connectorShape=line2;

	var baseY = y2 - 10;
	var baseX = x2 - 5;
	
	var rightY = baseY;
	var rightX = baseX + 10;

	var dOption = "M" + baseX + "," + baseY + "L" + rightX + "," + rightY + "L" + x2 + "," + y2 + "Z";

	var triangle = document.createElementNS(svgns, "path");
	triangle.setAttributeNS(null, "d", dOption);
    triangle.setAttributeNS(null, "stroke", "black");
	triangle.setAttributeNS(null, "stroke-width", "5");
	triangle.setAttributeNS(null, "fill", "black");
	dragObj.connectorShape=triangle;

    svgCanvas.appendChild(line1);
    svgCanvas.appendChild(line2);
    svgCanvas.appendChild(triangle);
}

function setExport(scene){
	document.body.style.background = "url('img/output-bkg.gif') 0 0 repeat";
	var appName = prompt("Choisis le nom de ton application", "");

	if(appName == null)
		appName = "MonApplication";
			
	setExportPage(scene, appName);
}

function setExportPage(scene, name){

	var container = scene.getSceneContainer();

	var head = document.createElement("header");
	head.id = "header";
	container.appendChild(head);
		
	var mySceneName = document.createElement("div");
	mySceneName.id = "exportName";
	mySceneName.className = "sceneTitle";
	mySceneName.style.cssText = "color:black";
	mySceneName.textContent = name;
	head.appendChild(mySceneName);

	var svgCanvas = document.createElementNS("http://www.w3.org/2000/svg", "svg");
	svgCanvas.version="1.1";
	svgCanvas.style.cssText="position:absolute; width:100%; height:100%; top:0; left:0; z-index:-1;";
	container.appendChild(svgCanvas);

	var webPage = document.createElement("div");
	webPage.id= "webButton";
	webPage.className= "grayButton";
	webPage.style.cssText = "position:absolute; top:70%; left:5%;";
	
	var webImg = document.createElement("img");
	webImg.id = "webImg";
	webImg.src = "img/loader.gif";
	webPage.appendChild(webImg);
	
	container.appendChild(webPage);

	var androidApp = document.createElement("div");
	androidApp.id= "androidButton";
	androidApp.className= "grayButton";
	androidApp.style.cssText = "position:absolute; top:70%; right:5%;";	
// 	androidApp.onclick = getAndroidApp;
	container.appendChild(androidApp);

	var androidImg = document.createElement("img");
	androidImg.id = "androidImg";
	androidImg.src = "img/loader.gif";
	androidApp.appendChild(androidImg);

	if(isTooltipEnabled()){
		changeSceneToolTip(0);
		disableTooltips();
	}
	
	var circle = document.createElement("div");
	circle.id = "bubble";
	circle.className = "bubble";
	container.appendChild(circle);

//  DRAW ARROWS TO BUTTONS
	
	var y1 = document.body.scrollHeight/2;
	var x1 = circle.getBoundingClientRect().right;

	var y2 = androidApp.getBoundingClientRect().top - 5;
	var x2 = androidApp.getBoundingClientRect().left + androidApp.getBoundingClientRect().width/2;

	drawArrow(svgCanvas, x1, y1, x2, y2);
	
	var x3 = circle.getBoundingClientRect().left;
	var x4 = webPage.getBoundingClientRect().left + webPage.getBoundingClientRect().width/2;
	
	drawArrow(svgCanvas, x3, y1, x4, y2);	
	
	var faustModule = createMyFaustEquivalent(scene, name, circle);
	
	if(faustModule){
		faustModule.createInterface();
//  		faustModule.addInputOutputNodesToModule();
	 	faustModule.recallParams();
		scene.addModule(faustModule);
	}
	
	var width = faustModule.getContainer().getBoundingClientRect().width + 70;
	var height = faustModule.getContainer().getBoundingClientRect().height + 100;
		
	circle.style.width = width.toString() + "px";
	circle.style.height = height.toString() + "px";
	
	var backImg = document.createElement("img");
	backImg.id = "backImg";
	backImg.src = "img/BACK.png";
	backImg.style.cssText = "position:absolute; top:2%; left:2%;";
	backImg.onclick = function(){ previousScene()};
	container.appendChild(backImg);
	
	getWebApp(faustModule);
	getAndroidApp(faustModule);

	scene.unmuteScene();
}

function resetExportPage(scene){

	scene.muteScene();
	scene.cleanDSPs();
	
	var children = scene.getSceneContainer().childNodes;
	
	for(var i=children.length-1; i>=0; i--)
		scene.getSceneContainer().removeChild(children[i]);
}

function exportPage(scene){
	
	scene.integrateSceneInPage();
}

//Create Faust Equivalent Module of the Scene
function createMyFaustEquivalent(scene, patchName, parent){
	
	var faustModule = createFaustEquivalent(window.scenes[1], patchName, parent);
	
	disconnectNode(faustModule);
// 	faustModule.deleteInputOutputNodesToModule();
	connectNodes(faustModule, scene.audioOutput());
	var connector = new Object();

	saveConnection(faustModule, scene.audioOutput(), connector, null);
		
	scene.audioOutput().addInputConnection(connector);
	faustModule.addOutputConnection(connector);
	
	
	faustModule.getContainer().style.cssText = "position:relative; margin-left:auto; margin-right:auto; top:10%; ";
	faustModule.removeListener(faustModule.getContainer(), "mousedown");
	
	return 	faustModule;
}

function terminateWebMenu(sha){

	document.getElementById("webButton").removeChild(document.getElementById("webImg"));

	var url = "http://faustservice.grame.fr" + "/" + sha +"/web/asmjs-links/binary.zip";

	var link = document.createElement('a');
	link.href = url;
	var title = document.createElement("h6");
// 	title.style.cssText = "font-size:20px; color: #4c4c4c; text-transform: uppercase;";
	title.appendChild(document.createTextNode("Télécharger page Web"));
	
	link.appendChild(title);
	document.getElementById("webButton").appendChild(link);
}

function terminateAndroidMenu(sha){

	document.getElementById("androidButton").removeChild(document.getElementById("androidImg"));

	var url = "http://faustservice.grame.fr" + "/" + sha +"/android/android/binary.apk";
	
	document.getElementById("androidButton").textContent = "Télécharger application Android";
	
	var qrcodeDiv = getQrCode(url, sha, "android", "android", "binary.apk");
	
	document.getElementById("androidButton").appendChild(qrcodeDiv);
	qrcodeDiv.style.cssText = "left:20%;";
}

function exportAndroidCallback(sha){

	sendPrecompileRequest("http://faustservice.grame.fr", sha, "android", "android", terminateAndroidMenu);
}

function exportWebCallback(sha){
	
	sendPrecompileRequest("http://faustservice.grame.fr", sha, "web", "asmjs", terminateWebMenu);
}	

function getAndroidApp(faustDiv){

	var shaKey = getSHAKey("http://faustservice.grame.fr", faustDiv.getName(), faustDiv.getSource(), exportAndroidCallback);
}

function getWebApp(faustDiv){

	var shaKey = getSHAKey("http://faustservice.grame.fr", faustDiv.getName(), faustDiv.getSource(), exportWebCallback);
}

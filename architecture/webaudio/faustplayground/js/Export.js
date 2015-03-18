
function addItem(id, itemText){
	var e2=document.getElementById(id);
	var o=document.createElement('option');
	o.text=itemText;
	e2.options.add(o);
}
			
function clearComboBox(id){
	while(document.getElementById(id).childNodes.length>0) {
		document.getElementById(id).removeChild(document.getElementById(id).childNodes[0]);
	}
}

function updateArchitectures(){

	console.log("updateArch");

	clearComboBox('architectures');
		
	var data = JSON.parse(window.jsonText);
			
	var e = document.getElementById('platforms');//get the combobox
	var selPlatform = e.options[e.selectedIndex].value;
											
    var dataCopy = data[selPlatform];
	var iterator = 0;
							
	for (data in dataCopy) {
				
		if(iterator < dataCopy.length){
			var mainData = dataCopy[data];
        						
	   		addItem('architectures', mainData);
	   		iterator = iterator + 1;
	   	}	
	}
}

function exportCallback(sha){

	var exportDiv = document.getElementById("export");
	exportFaustCode(exportDiv, sha);
}
		
function exportFaustCode(shaKey){

	var xhr = new XMLHttpRequest();
				
	var e = document.getElementById("platforms");//get the combobox
	var selPlatform = e.options[e.selectedIndex].value;
			    
	e = document.getElementById("architectures");//get the combobox
	var selArch = e.options[e.selectedIndex].value;
			    
 	var serverUrl = document.getElementById("faustweburl").value;
 		
	var appType = "binary.zip";
	
	if(selArch == "android")
		appType = "binary.apk";
	
// 	var url = serverUrl + "/" + shaKey +"/"+ selPlatform + "/" + selArch + "/"+appType;
	
	var link = document.createElement('a');
	
	var title = document.createElement("h6");
	title.className = "export-title";
	title.appendChild(document.createTextNode("Download Me"));
	
	link.appendChild(title);
	link.href = serverUrl + "/" + shaKey +"/"+ selPlatform + "/" + selArch + "/"+appType;

	// 	Delete existing content if existing
	var qrcodeSpan = document.getElementById('qrcodeDiv');
	if(qrcodeSpan)
		qrcodeSpan.parentNode.removeChild(qrcodeSpan);
	
	var myWhiteDiv = getQrCode(serverUrl, shaKey, selPlatform, selArch, appType);
	document.getElementById("sceneOutput").appendChild(myWhiteDiv);
	myWhiteDiv.appendChild(link);
// 	myWhiteDiv.style.cssText = "position: relative;";
	myWhiteDiv.style.right = '15px';

}
	
function UploadTargets(){

	clearComboBox('platforms');
	
	window.exportURL = document.getElementById("faustweburl").value;
			
	var getrequest = new XMLHttpRequest();
				
	getrequest.onreadystatechange = function() {
		if(getrequest.readyState == 4 && getrequest.status == 200) {
			window.jsonText = getrequest.responseText;
				    		
			var data = JSON.parse(window.jsonText);

			for (var event in data) {
				addItem('platforms', event);
        	}
        	
        	updateArchitectures();
    	}
	}
				
	var targetsUrl = window.exportURL + "/targets";
				
	getrequest.open("GET", targetsUrl, true);
	getrequest.send(null);
}		

function exportPatch(event){

	var sceneName = document.getElementById("PatchName").innerHTML;

	getSHAKey(document.getElementById("faustweburl").value, sceneName, getFaustEquivalent(window.scenes[0], sceneName), exportFaustCode);

}





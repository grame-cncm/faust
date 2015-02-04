
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
			
function getSHAKey(){

	var sceneName = document.getElementById("PatchName").value;
	console.log(sceneName);

	var exportDiv = event.target;
	
	while(exportDiv && exportDiv.className != "export")
		exportDiv = exportDiv.parentNode;

	var file = new File([event.target.sourceCode], "freeverb.dsp");

	var newRequest = new XMLHttpRequest();

	var params = new FormData();
	params.append('file', file);

// 	var urlToTarget = "http://faustservice.grame.fr/filepost";
// 	var urlToTarget = window.exportURL + "/filepost";
	var urlToTarget = document.getElementById("faustweburl").value + "/filepost";	
	
	newRequest.open("POST", urlToTarget, true);

	newRequest.onreadystatechange = function() {
		if(newRequest.readyState == 4 && newRequest.status == 200) {
			exportFaustCode(exportDiv, newRequest.responseText);
    	}
	}
				
	newRequest.send(params);
}
			
function exportFaustCode(exportDiv, shaKey){

	console.log(exportDiv);

	var xhr = new XMLHttpRequest();
				
	var e = document.getElementById("platforms");//get the combobox
	var selPlatform = e.options[e.selectedIndex].value;
			    
	e = document.getElementById("architectures");//get the combobox
	var selArch = e.options[e.selectedIndex].value;
			    
// 	var serverUrl = document.getElementById("serverUrl").value;
// 	var	serverUrl = "http://faustservice.grame.fr";
//	var serverUrl = window.exportURL;
 	var serverUrl = document.getElementById("faustweburl").value;
 		
	var appType = "binary.zip";
	
	if(selArch == "android")
		appType = "binary.apk";
	
	var url = serverUrl + "/" + shaKey +"/"+ selPlatform + "/" + selArch + "/"+appType;
	
	var link = document.createElement('a');
	
	var title = document.createElement("h6");
	title.className = "export-title";
	title.appendChild(document.createTextNode("Download Me"));
	
	link.appendChild(title);
	link.href = url;
	
	var myWhiteDiv = document.createElement('div');
	myWhiteDiv.setAttribute('id','qrcodeDiv');
	myWhiteDiv.setAttribute('class','qrcodeDiv');
	myWhiteDiv.style.backgroundColor = 'transparent';
// 	myWhiteDiv.style.position = 'relative';
	
// 60 - La moitié de la taille du qrcode... pas terrible !
	var whiteDivLeft = exportDiv.getBoundingClientRect().width/2-60;
	
	myWhiteDiv.style.right = whiteDivLeft.toString() + 'px';
	
	var qqDiv = document.createElement('qrcode');
	
// 	var qq = new QRCode(qqDiv, url);
	var qq = new QRCode(qqDiv, {
    	text: url,
	    width: 120,
    	height: 120,
	    colorDark : "#000000",
    	colorLight : "#ffffff",
	    correctLevel : QRCode.CorrectLevel.H
	});

	myWhiteDiv.appendChild(link);
	if(selArch == "android")
		myWhiteDiv.appendChild(qqDiv);
	
	
// 	Delete existing content if existing
	var qrcodeSpan = document.getElementById('qrcodeDiv');
	if(qrcodeSpan)
		qrcodeSpan.parentNode.removeChild(qrcodeSpan);
	
	exportDiv.appendChild(myWhiteDiv);
	
	var element = document.createElement('div');
}
	
function UploadTargets(){

	clearComboBox('platforms');
	
// 	window.exportURL = "http://faustservice.grame.fr";
// 	window.exportURL = "http://192.168.1.136:8888";
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
				
// 	var targetsUrl = document.getElementById("serverUrl").value;
// 	var targetsUrl = "http://faustservice.grame.fr";
	var targetsUrl = window.exportURL + "/targets";
				
	getrequest.open("GET", targetsUrl, true);
	getrequest.send(null);
}		

function addExporter(source_code, container){
		    
	var div=document.createElement('div');
	div.setAttribute('class', 'export');
				
	var sel1=document.createElement('select');
	sel1.setAttribute('id', 'platforms');
	sel1.setAttribute('onChange', 'updateArchitectures()');
												
	var sel2=document.createElement('select');
	sel2.setAttribute('id', 'architectures');
				
	var inp2=document.createElement('input');
	inp2.setAttribute('className',"exportButton");
	inp2.setAttribute('type', 'submit');
	inp2.setAttribute('value', ' Export ');
	inp2.setAttribute('onclick', 'getSHAKey()');
	inp2.sourceCode = source_code;

	div.setAttribute('id', "export");
	
	div.appendChild(sel1);
	div.appendChild(sel2);
	div.appendChild(inp2);
		    	
	container.appendChild(div);
				
	UploadTargets();
}

function exportPatch(event){

	var sceneName = document.getElementById("PatchName").innerHTML + ".dsp";

	var exportDiv = event.target.parentNode;

	var file = new File([getFaustEquivalent()], sceneName);

	var newRequest = new XMLHttpRequest();

	var params = new FormData();
	params.append('file', file);

// 	var urlToTarget = "http://faustservice.grame.fr/filepost";				
	var urlToTarget = document.getElementById("faustweburl").value + "/filepost";
	
	newRequest.open("POST", urlToTarget, true);

	newRequest.onreadystatechange = function() {
		if(newRequest.readyState == 4 && newRequest.status == 200) {
			exportFaustCode(exportDiv, newRequest.responseText);
    	}
	}
				
	newRequest.send(params);

}


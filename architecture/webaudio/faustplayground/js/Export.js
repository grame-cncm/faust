/*				EXPORT.JS
	Handles Graphical elements for the Export Feature of the normal Playground
		
	DEPENDENCIES :
		- ExportLib.js
		- qrcode.js
*/

"use strict";

/******************************************************************** 
*********************  HANDLE FAUST WEB TARGETS *********************
********************************************************************/

//------ Handle Combo Boxes
function addItem(id, itemText)
{
	var e2 = document.getElementById(id);
	var o = document.createElement('option');
	o.text = itemText;
	e2.options.add(o);
}
			
function clearComboBox(id)
{
	while (document.getElementById(id).childNodes.length>0) {
		document.getElementById(id).removeChild(document.getElementById(id).childNodes[0]);
	}
}

//------ Update Architectures with Plateform change
function updateArchitectures()
{
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

function uploadTargets()
{
	clearComboBox('platforms');
	clearComboBox('architectures');

	window.exportURL = document.getElementById("faustweburl").value;
	
	getTargets(window.exportURL, function(json){
			window.jsonText = json;
				    		
			var data = JSON.parse(window.jsonText);

			for (var event in data) {
				addItem('platforms', event);
        	}
        	
        	updateArchitectures();
	}, function(json){
		alert('Impossible to get FaustWeb targets');
	});
}		

/******************************************************************** 
*********************  HANDLE POST TO FAUST WEB  ********************
********************************************************************/

function exportPatch(event)
{
	var sceneName = document.getElementById("PatchName").innerHTML;
	var faustCode = getFaustEquivalent(window.scenes[window.currentScene], sceneName);
	getSHAKey(document.getElementById("faustweburl").value, sceneName, faustCode, exportFaustCode);
}

/******************************************************************** 
**************  CALLBACK ONCE SHA KEY WAS CALCULATED  ***************
********************************************************************/

function exportFaustCode(shaKey)
{
	var xhr = new XMLHttpRequest();
				
	var e = document.getElementById("platforms");//get the combobox
	var selPlatform = e.options[e.selectedIndex].value;
			    
	e = document.getElementById("architectures");//get the combobox
	var selArch = e.options[e.selectedIndex].value;
			    
 	var serverUrl = document.getElementById("faustweburl").value;
 		
	var appType = "binary.zip";
	
	if (selArch == "android")
		appType = "binary.apk";
	
	// 	Delete existing content if existing
	var qrcodeSpan = document.getElementById('qrcodeDiv');
	if (qrcodeSpan)
		qrcodeSpan.parentNode.removeChild(qrcodeSpan);
			
	var qrDiv = document.createElement('div');
	qrDiv.id = "qrcodeDiv";
	document.getElementById("sceneOutput").appendChild(qrDiv);
	
	var link = document.createElement('a');
	link.href = serverUrl + "/" + shaKey +"/"+ selPlatform + "/" + selArch + "/"+appType;
	qrDiv.appendChild(link);

	var myWhiteDiv = getQrCode(serverUrl, shaKey, selPlatform, selArch, appType, 120);
	link.appendChild(myWhiteDiv);
}




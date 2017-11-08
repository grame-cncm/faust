"use strict"

/************************************************************
***************** Interface to FaustWeb *********************
************************************************************/

//--- Send asynchronous GET request to FaustWeb to get the list of available targets
// @exportUrl : url of FaustWeb service to target
// @callback : function called once request succeeded 
// 				- @param : the available targets as a JSON application
// json = {"platform1":["arch1", "arch2", ..., "archn"], ... , "platformn":["arch1", "arch2", ..., "archn"]}

function getTargets(exportUrl, callback, errCallback)
{
    var getrequest = new XMLHttpRequest();
        
    getrequest.onreadystatechange = function() {
        if (getrequest.readyState === 4 && getrequest.status === 200)
            callback(getrequest.responseText);
        else if (getrequest.readyState === 4 && getrequest.status === 400)
            errCallback(getrequest.responseText);
    }
        
    var targetsUrl = exportUrl + "/targets";
    getrequest.open("GET", targetsUrl, true);
    getrequest.send(null);
}

//--- Send asynchronous POST request to FaustWeb to compile a faust DSP
// @exportUrl : url of FaustWeb service to target
// @name : name of DSP to compile
// @source_code : Faust code to compile
// @callback : function called once request succeeded 
// 				- @param : the sha key corresponding to source_code
function getSHAKey(exportUrl, name, source_code, callback, errCallback)
{
    var filename = name + ".dsp";
    var file = new File([source_code], filename);
    var newRequest = new XMLHttpRequest();

    var params = new FormData();
    params.append('file', file);
    var urlToTarget = exportUrl + "/filepost";	
    newRequest.open("POST", urlToTarget, true);

    newRequest.onreadystatechange = function() {
        if (newRequest.readyState === 4 && newRequest.status === 200)
            callback(newRequest.responseText);
        else if (newRequest.readyState === 4 && newRequest.status === 400)
            errCallback(newRequest.responseText);
    }
        
    newRequest.send(params);
}
	
//--- Send asynchronous GET request to precompile target 
// @exportUrl : url of FaustWeb service to target
// @sha : sha key of DSP to precompile
// @platform/architecture : platform/architecture to precompile
// @callback : function called once request succeeded 
// 				- @param : the sha key 
function sendPrecompileRequest(exportUrl, sha, platform, architecture, callback)
{
    var getrequest = new XMLHttpRequest();
        
    getrequest.onreadystatechange = function() {
        if (getrequest.readyState === 4) {
            callback(sha);
        }
    }

    var compileUrl = exportUrl + "/" + sha + "/" + platform + "/" + architecture + "/precompile";
        
    getrequest.open("GET", compileUrl, true);
    getrequest.send(null);
}

//--- Transform target 
// WARNING = THIS FUNCTION REQUIRES QRCODE.JS TO BE INCLUDED IN YOUR HTML FILE
// @exportUrl : url of FaustWeb service to target
// @sha : sha key of DSP
// @platform/architecture/target : platform/architecture/target compiled
// @cote : width and height of the returned QrCode
function getQrCode(url, sha, plateform, architecture, target, size)
{
    var downloadString = url + "/" + sha + "/" + plateform + "/" + architecture + "/" + target;
    var whiteContainer = document.createElement('div');
    whiteContainer.style.cssText = "width:" + size.toString() + "px; height:" + size.toString() + "px; background-color:white; position:relative; margin-left:auto; margin-right:auto; padding:3px;";

    var qqDiv = document.createElement('qrcode');
    var qq = new QRCode(qqDiv, {
        text: downloadString,
        width: size,
        height: size,
        colorDark : "#000000",
        colorLight : "#ffffff",
        correctLevel : QRCode.CorrectLevel.H
    });

    whiteContainer.appendChild(qqDiv);
    return whiteContainer;
}

// Return the array of available platforms from the json description
function getPlatforms(json)
{
    var platforms = [];
    var data = JSON.parse(json);
    var index = 0;

    for (var p in data) {
        platforms[index] = p;
        index++;
    }

    return platforms;
}

// Return the list of available architectures for a specific platform from the json description
function getArchitectures(json, platform)
{
    var architectures = [];
    var data = JSON.parse(json);

    return data[platform];						
//  var archs = data[platform];
			
// 	for (var i =0; i<archs.length; i++)
//      architectures[i] = archs[i];
// 	
//  return architectures;
}


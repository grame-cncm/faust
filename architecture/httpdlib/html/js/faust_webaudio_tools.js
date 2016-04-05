
var context;
var source;
var faustdsp;
var code = "";
var ui;

function loadSample(url) 
{
    // Load asynchronously
    var request = new XMLHttpRequest();
    request.open("GET", url, true);
    request.responseType = "arraybuffer";

    request.onload = function() { 
        source.buffer = context.createBuffer(request.response, false);
        source.loop = true;
        source.noteOn(0);
    }

    request.send();
}

function loadDSP(url) 
{
    var request = new XMLHttpRequest();
    request.onreadystatechange = function() {
        if (request.readyState == 4) { 
            code = request.responseText; 
            buildFaustNodeSVG(code);
        }
    }
    request.open("GET", url, true);
    request.send(null);
}

function buildFaustNode(code)
{
    // Remove old connections
    if (faustdsp) {
        if (source) {
            source.disconnect(faustdsp);
        }
        faustdsp.disconnect(context.destination);
    }
    
    // Clear UI
    ui.clear();
    
    faustdsp = context.createFaustNode(code);
    var controls = faustdsp.numberOfAudioParams();
   
    console.log("numberOfAudioParams = %d", controls);    
    console.log("numberOfInputs = %d", faustdsp.numberOfInputs);
    console.log("numberOfOutputs = %d", faustdsp.numberOfOutputs);
    console.log("JSON "+ faustdsp.json);
    
    // Build simple UI
    for (var i = 0; i < controls; i++) {
        var ctrl = faustdsp.getAudioParam(i);
        console.log("getAudioParam : name = %s, min = %d, max = %d, default = %d", ctrl.name, ctrl.minValue, ctrl.maxValue, ctrl.defaultValue);
        ui.addHorizontalSlider(ctrl.name, function handler(obj) { function setval(val) { obj.value = val; } return setval; }(ctrl), ctrl.defaultValue, ctrl.minValue, ctrl.maxValue, Math.abs(ctrl.maxValue - ctrl.minValue)/100);
    }
  
    // Connection to output
    faustdsp.connect(context.destination);
}

function buildFaustNodeSVG(code)
{
    // Remove old connections
    if (faustdsp) {
        if (source) {
            source.disconnect(faustdsp);
        }
        faustdsp.disconnect(context.destination);
    }
    
    // Clear UI
    //ui.clear();
    
    faustdsp = context.createFaustNode(code);
    var controls = faustdsp.numberOfAudioParams();
   
    console.log("numberOfAudioParams = %d", controls);    
    console.log("numberOfInputs = %d", faustdsp.numberOfInputs);
    console.log("numberOfOutputs = %d", faustdsp.numberOfOutputs);
    console.log("JSON "+ faustdsp.json);
  
    // Connection to output
    faustdsp.connect(context.destination);
}

function initAudio(url) 
{
    context = new webkitAudioContext();
    ui = new JUI(document.getElementById("FaustUI"));
    loadDSP(url);
}

function initDefaultAudio() 
{
    context = new webkitAudioContext();
    ui = new JUI(document.getElementById("FaustUI"));
}

function playsound()
{
    var url = $("#sound").val();
    if (source) {
        source.noteOff(0);
        source.disconnect(0);
        source = null;
    }
    source = context.createBufferSource();
    loadSample(url);
    source.connect(faustdsp);
}

function stopsound()
{
    source.noteOff(0);
    source.disconnect(0);
}
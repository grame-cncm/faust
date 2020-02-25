'use strict';

const AudioContext = window.AudioContext || window.webkitAudioContext;

const context = new AudioContext();

let source = context.createBufferSource();
let faustdsp = null;
let ui = null;

window.addEventListener('touchstart', resume, false);
window.addEventListener('mousedown', resume, false);

// for Autoplay Policy
function resume(event) 
{
    if (context.state !== 'suspended') {
        window.removeEventListener(event.type, resume, false);

        return;
    }

    context.resume()
        .then(() => {
            console.log('Audio resumed');
        })
        .catch(console.error)
        .finally(() => {
            window.removeEventListener(event.type, resume, false);
        });
}

function loadSample(url) 
{
    // Load asynchronously
    fetch(url)
        .then((response) => {
            return response.arraybuffer();
        })
        .then((arraybuffer) => {
            context.decodeAudioData(arraybuffer, (audiobuffer) => {
                source.buffer = audiobuffer;
                source.loop = true;
                source.start(0);
            }, console.error);
        })
        .catch(console.error);
}

function loadDSP(url) 
{
    fetch(url)
        .then((response) => {
            return response.text();
        })
        .then((code) => {
            buildFaustNodeSVG(code);
        })
        .catch(console.error);
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
    const controls = faustdsp.numberOfAudioParams();

    console.log('numberOfAudioParams = %d', controls);
    console.log('numberOfInputs = %d', faustdsp.numberOfInputs);
    console.log('numberOfOutputs = %d', faustdsp.numberOfOutputs);
    console.log(`JSON ${faustdsp.json}`);

    const handler = (obj) => {
        return (val) => {
            obj.value = val;
        };
    };

    // Build simple UI
    for (let i = 0; i < controls; i++) {
        const { name, minValue, maxValue, defaultValue } = faustdsp.getAudioParam(i);

        console.log('getAudioParam : name = %s, min = %d, max = %d, default = %d', name, minValue, maxValue, defaultValue);

        ui.addHorizontalSlider(name, handler(ctrl), defaultValue, minValue, maxValue, Math.abs(maxValue - minValue) / 100);
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

    faustdsp = context.createFaustNode(code);

    const controls = faustdsp.numberOfAudioParams();

    console.log('numberOfAudioParams = %d', controls);
    console.log('numberOfInputs = %d', faustdsp.numberOfInputs);
    console.log('numberOfOutputs = %d', faustdsp.numberOfOutputs);
    console.log(`JSON ${faustdsp.json}`);

    // Connection to output
    faustdsp.connect(context.destination);
}

function initAudio(url, id = 'FaustUI') 
{
    ui = new JUI(document.getElementById(id));
    loadDSP(url);
}

function initDefaultAudio(id = 'FaustUI') 
{
    ui = new JUI(document.getElementById(id));
}

function playsound()
{
    const url = document.getElementById('sound');
    if (source) {
        source.stop(0);
        source.disconnect(0);
        source = null;
    }
    source = context.createBufferSource();
    loadSample(url);
    source.connect(faustdsp);
}

function stopsound()
{
    source.stop(0);
    source.disconnect(0);
}

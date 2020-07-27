'use strict';

// component for Faust compiler
const AudioContext = window.AudioContext || window.webkitAudioContext;
const audio_context = new AudioContext();
const buffer_size = 1024;

let audio_input = null;

function processFaust(sandBox, container) {
  console.log('processFaust');
  console.log(sandBox.value);
  console.log(container);

  // Create a DSP factory from the dsp code
  const factory = faust.createDSPFactory(sandBox.value, [], () => {});
  if (!factory) {
      alert(faust.getErrorMessage());
      return;
  }

  // Then creates one DSP instance
  const DSP = faust.createDSPInstance(factory, audio_context, buffer_size);
  if (DSP.getNumInputs() > 0) {
      activateAudioInput(DSP);
  }

  // Setup UI
  _f4u$t.main_loop = () => {}
  const handler = _f4u$t.main(DSP.json(), container.innerHTML, DSP.setParamValue);
  DSP.setHandler(handler);

  console.log(DSP.getNumInputs());
  console.log(DSP.getNumOutputs());

  DSP.start();
}

function activateAudioInput(DSP)
{
  console.log('activateAudioInput');

  if (navigator.mediaDevices && navigator.mediaDevices.getUserMedia) {
    navigator.mediaDevices.getUserMedia({ audio: { echoCancellation: false } })
      .then(getDevice(DSP))
      .catch((e) => {
        alert('Error getting audio input');
        console.log(e);
        audio_input = null;
      });
  } else {
    alert('Audio input API not available');
  }
}

function getDevice(DSP)
{
  return (device) => {
    // Create an AudioNode from the stream.
    audio_input = audio_context.createMediaStreamSource(device);
    // Connect it to the destination.
    audio_input.connect(DSP.getProcessor());
  }
}

class FaustCompiler extends HTMLElement {
  /** @override */
  constructor() {
    super();

    this.attachShadow({ mode : 'open' });
  }

  connectedCallback() {
    this.shadowRoot.appendChild(document.importNode(document.getElementById('faustTemplate').content, true));

    const sandBox = this.shadowRoot.getElementById('faustSandbox');

    // div to insert svg representation
    const container = this.shadowRoot.getElementById('container');

    // Register evenement
    sandBox.onkeyup = function(evt) {
      processFaust(sandBox, container);
    };

    // Get the text content of component
    const initCode = this.textContent;
    if (initCode) {
      sandBox.value = initCode;
      processFaust(sandBox, container);
    }

    // Read attributes and display or not the textarea
    const isFaustCode = this.getAttribute('faustCode');
    if (isFaustCode === 'false') {
      this.shadowRoot.getElementById('faustCode').style.display = 'none';
      this.shadowRoot.getElementById('container').style.width = '100%';
    }
  }

  render() {
    this.shadowRoot.innerHTML = `
      <style type="text/css">
        body {
          background-color: #000000;
        }

        /* WEBKIT */
        text {
          -webkit-touch-callout: none;
          -webkit-user-select: none;
          -khtml-user-select: none;
          -moz-user-select: none;
          -ms-user-select: none;
          user-select: none;
        }

        .faust-group-label {
          font-family: Arial, Verdana, Helvetica, sans;
          font-size: 13px;
          fill: rgba(199,190,162,0.6);
        }

        .faust-tooltip-text {
          font-family: Arial, Verdana, Helvetica, sans;
          font-size: 13px;
        }

        .faust-button-label {
          font-family: Arial, Verdana, Helvetica, sans;
          font-size: 13px;
          fill: rgba(0,182,253,0.6);
        }

        .faust-tgroup-label {
          font-family: Arial, Verdana, Helvetica, sans;
          font-size: 13px;
          fill: rgba(0,182,253,0.6);
        }

        .faust-label {
          font-family: Arial, Verdana, Helvetica, sans;
          font-size: 13px;
          fill: rgba(0,182,253,0.6);
        }

        .faust-value-text {
          font-family: Arial, Verdana, Helvetica, sans;
          font-size: 11px;
          font-weight: bold;
          fill: rgb(82,79,79);
        }

        path {
          -webkit-user-select: none;
        }

        rect {
          -webkit-user-select: none;
          -moz-user-select: none;
          user-select: none;
        }

        circle {
          -webkit-user-select: none;
        }

        text:hover {
          cursor: default;
        }

        path.faust-vbox {
          fill : white;
          stroke : black;
        }

        path.faust-rbutton-groove {
          fill : rgb(152,251,152);
          stroke : black;
        }

        path.faust-rbutton-handle {
          fill : grey;
          stroke : black;
        }

        rect.faust-hslider-meter {
          fill : url(#horizontalSliderMeterGradient);
          width : 175;
          height : 40;
        }

        rect.faust-hslider-groove {
          fill : rgba(28,126,192,0.65);
          stroke : rgba(0,182,253,0.9);
          width : 175;
          height : 40;
        }

        rect.faust-hslider-handle {
          fill : url(#horizontalSliderHandleGradient);
          stroke : black;
          width : 30;
          height : 40;
        }

        rect.faust-vslider-meter {
          fill : url(#verticalSliderMeterGradient);
          height : 175;
          width : 40;
        }

        rect.faust-vslider-groove {
          fill : rgba(28,126,192, 0.65);
          stroke : rgba(0,182,253,0.9);
          width : 40;
          height : 175;
        }

        rect.faust-vslider-handle {
          fill : url(#verticalSliderHandleGradient);
          stroke : black;
          width : 40;
          height : 30;
        }

        rect.faust-hbargraph-curtain {
          fill : rgb(20,20,20);
          stroke : black;
          width : 200;
          height : 30;
        }

        // hbargraph meters cannot be defined via CSS because their widths and
        // heights are dynamic

        rect.faust-hbargraph-meter {
          fill : url(#horizontalBarGraphMeterGradient);
          stroke : black;
        }

        rect.faust-vbargraph-curtain {
          fill : rgb(20,20,20);
          stroke : black;
          width : 30;
          height : 200;
        }

        rect.faust-vbargraph-meter {
          fill : url(#verticalBarGraphMeterGradient);
          stroke : black;
        }

        rect.faust-checkbox-box {
          fill : white;
          stroke : black;
          width : 19;
          height : 19;
        }

        path.faust-checkbox-check {
          fill : black;
          stroke : black;
        }

        rect.faust-nentry-box {
          fill : url(#numericalEntryUpGradient);
          stroke : black;
          width : 60;
          height : 20;
        }

        path.faust-nentry-operation {
          stroke : black;
        }

        rect.faust-button-box {
          fill : url(#buttonUpGradient);
          stroke : black;
          width : 80;
          height : 40;
        }

        rect.faust-tgroup-box {
          fill : url(#tabGroupUpGradient);
          stroke : black;
        }

        circle.faust-rbutton-groove {
          fill : url(#rotatingButtonHandleGradient);
        }

        circle.faust-rbutton-dot {
          fill : pink;
          stroke : black;
        }

        path.faust-rbutton-meter {
          fill : rgb(50,50,50);
        }

        path.faust-rbutton-mgroove {
          fill : url(#rotatingButtonMeterGradient);
        }

        // as all of the above rectangles could be implemented as paths, we duplicate the definitions for paths

        path.faust-hslider-groove {
          fill : red;
          stroke : black;
        }

        path.faust-hslider-handle {
          fill : url(#horizontalSliderHandleGradient);
          stroke : black;
        }

        path.faust-vslider-groove {
          fill : red;
          stroke : black;
        }

        path.faust-vslider-handle {
          fill : url(#verticalSliderHandleGradient);
          stroke : black;
        }

        path.faust-hbargraph-curtain {
          fill : rgb(0,255,255);
          stroke : black;
        }

        path.faust-hbargraph-meter {
          fill : grey;
          stroke : black;
        }

        path.faust-vbargraph-curtain {
          fill : rgb(0,255,255);
          stroke : black;
        }

        path.faust-vbargraph-meter {
          fill : grey;
          stroke : black;
        }

        path.faust-checkbox-box {
          fill : white;
          stroke : black;
        }

        path.faust-nentry-box {
          fill : url(#numericalEntryUpGradient);
          stroke : black;
        }

        path.faust-button-box {
          fill : #B0B0B0;
          stroke : black;
        }

        #filedrag {
          font-weight: bold;
          text-align: center;
          padding: 1em 0;
          margin: 1em 0;
          color: #CECECE;
          border: 8px dashed #CECECE;
          border-radius: 7px;
          cursor: default;
          font-size : 20px;
        }

        #filedrag.hover{
          color: #FF7F00;
          border-color: #FF7F00;
          border-style: solid;
        }
      </style>
    `;
  }
}

faust_module['onRuntimeInitialized'] = () => {
  window.customElements.define('faust-compiler', FaustCompiler);
};

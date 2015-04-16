/*				PEDAGOGIE.JS
	Init Pedagogical Scene with all its graphical elements

	This is the second scene of the Pedagogical Playground
		
	DEPENDENCIES :
		- Scene.js
		- Pedagogie/Tooltips.js
		- Connect.js
		- Main.js
*/



"use strict";

// Add visual elements to Pedagogical Playground Scene
function initPedagogieScene(scene){

		var container = scene.getSceneContainer();
	
		var svgCanvas = document.createElementNS("http://www.w3.org/2000/svg", "svg");
		svgCanvas.id="svgCanvas";
		svgCanvas.version="1.1";
		container.appendChild(svgCanvas);

//--------- HEADER	
		var head = document.createElement("header");
		head.id = "header";
		container.appendChild(head);
		
		var myScene = document.createElement("div");
		myScene.id = "PatchName";
		myScene.className = "sceneTitle";
		myScene.textContent = "Scène de " + "";
		head.appendChild(myScene);

		var uploadDiv = document.createElement("div");
		uploadDiv.id = "upload";
		uploadDiv.className = "uploading";
		head.appendChild(uploadDiv);
	
//--------- MODULES
		var moduleContainer = document.createElement("section");
		moduleContainer.id = "modules";
		moduleContainer.className = "container";
		container.appendChild(moduleContainer);
	
//--------- FOOTER
		var footer = document.createElement("div");
		footer.id = "footer";
		container.appendChild(footer);
	
		var equButton = document.createElement("div");
		equButton.id = "exportButton";
		equButton.className = "grayButton";
		footer.appendChild(equButton);

		var equText = document.createElement("a");
		equText.id = "cfe";
		equText.textContent = "FINALISE TON APPLICATION";
		equButton.onclick = function(){nextScene();};
		equButton.appendChild(equText);
	
		var subText = document.createElement("div");
		subText.id = "subtitleButton";		
		subText.textContent = "pour l'emmener avec toi";
		equButton.appendChild(subText);

		var linkWilson = document.createElement("div");
		linkWilson.className = "link";
		linkWilson.style.right = "10px";
		linkWilson.textContent = "Extension of the WebAudio Playground by ";
		footer.appendChild(linkWilson);

		var alink = document.createElement("a");
		alink.href = "https://github.com/cwilso/WebAudio";
		alink.textContent = "Chris Wilson";
		linkWilson.appendChild(alink);
	
		var imageLogo = document.createElement('img');
		imageLogo.className = "logoGrame";
		imageLogo.src= window.baseImg + "grame.png";
		footer.appendChild(imageLogo);
	
//------------ INPUT/OUTPUT
	
		var destDiv = document.createElement("div");
		destDiv.id = "sceneOutput";
		destDiv.className = "destination";
		container.appendChild(destDiv);
	
		var outText = document.createElement("span");
		outText.className = "text";
		outText.textContent = "SORTIE AUDIO";
		destDiv.appendChild(outText);
	
		var node = document.createElement("div");
		node.className = "node node-input";
		destDiv.appendChild(node);
	
		var nodeimg = document.createElement("span");
		nodeimg.className = "node-button";
		nodeimg.value = "&nbsp;";
		node.appendChild(nodeimg);

//Integrate Output
	scene.integrateSceneInBody();
	
	scene.integrateOutput(function(){
		
		if(isTooltipEnabled())
			changeSceneToolTip(1);
			
		scene.getAudioOutput().setInputOutputNodes(node, null);
			
		initLibrary(container);

		activateAudioOutput(destDiv);
		scene.hideScene();	
	});
}

// Load And UnLoad Pedagogical Playground Scene
function onloadPedagogieScene(scene){
	
	document.getElementById("PatchName").textContent = "Scène de   " + document.getElementById("nameTag").value;
	document.getElementById("PatchName").style.cssText = "color:white";
	document.body.style.background = "url('"+ window.baseImg + "body-bkg.gif') 0 0 repeat";
	setGeneralDragAndDrop();
	changeSceneToolTip(1);
	scene.unmuteScene();
	
	
// TU PEUX TESTER LE RAPPEL DE LA SCENE ICI
// 	var json = '{"1":[{"x":"174"},{"y":"164"},{"name":"bruitblanc"},{"code":"process = vgroup(\\"bruitblanc\\",environment{random  = +(12345)~*(1103515245);\\nnoise   = random/2147483647.0;\\n\\nprocess = noise * vslider(\\"Volume[style:knob]\\", 0, 0, 1, 0.1);\\n}.process);"},{"outputs":[{"dst":"2"},{"dst":"3"}]},{"params":[{"path":"/bruitblanc/Volume"},{"value":"0"}]}],"2":[{"x":"639"},{"y":"101"},{"name":"echo"},{"code":"process = vgroup(\\"echo\\",environment{declare name \\t\\t\\"echo\\";\\ndeclare version \\t\\"1.0\\";\\ndeclare author \\t\\t\\"Grame\\";\\ndeclare license \\t\\"BSD\\";\\ndeclare copyright \\t\\"(c)GRAME 2006\\";\\n//-----------------------------------------------\\n// \\t\\t\\t\\tA Simple Echo\\n//-----------------------------------------------\\n\\nimport(\\"music.lib\\");\\n\\nprocess = vgroup(\\"echosimple\\", echo1s);\\n}.process);"},{"inputs":[{"src":"1"}]},{"outputs":[{"dst":"0"}]},{"params":[{"path":"/echo/echosimple/echo__1000/feedback"},{"value":"81.4000015258789"},{"path":"/echo/echosimple/echo__1000/millisecond"},{"value":"464.29998779296875"}]}],"3":[{"x":"491"},{"y":"189"},{"name":"reverb"},{"code":"process = vgroup(\\"reverb\\",environment{//======================================================\\n//\\n//                      Freeverb\\n//        Faster version using fixed delays (20% gain)\\n//\\n//======================================================\\n\\n// Constant Parameters\\n\\n//--------------------\\ndeclare name \\t\\t\\"freeverb\\";\\ndeclare version \\t\\"1.0\\";\\ndeclare author \\t\\t\\"Grame\\";\\n\\n\\n\\ndeclare license \\t\\"BSD\\";\\ndeclare copyright \\t\\"(c)GRAME 2006\\";\\n\\n\\nfixedgain   = 0.015; //value of the gain of fxctrl\\nscalewet    = 3.0;\\nscaledry    = 2.0;\\nscaledamp   = 0.4;\\nscaleroom   = 0.28;\\noffsetroom  = 0.7;\\ninitialroom = 0.5;\\ninitialdamp = 0.5;\\ninitialwet  = 1.0/scalewet;\\ninitialdry  = 0;\\ninitialwidth= 1.0;\\ninitialmode = 0.0;\\nfreezemode  = 0.5;\\nstereospread= 23;\\nallpassfeed = 0.5; //feedback of the delays used in allpass filters\\n\\n\\n// Filter Parameters\\n//------------------\\n\\ncombtuningL1    = 1116;\\ncombtuningL2    = 1188;\\ncombtuningL3    = 1277;\\ncombtuningL4    = 1356;\\ncombtuningL5    = 1422;\\ncombtuningL6    = 1491;\\ncombtuningL7    = 1557;\\ncombtuningL8    = 1617;\\n\\nallpasstuningL1 = 556;\\nallpasstuningL2 = 441;\\nallpasstuningL3 = 341;\\nallpasstuningL4 = 225;\\n\\n\\n// Control Sliders\\n//--------------------\\n// Damp : filters the high frequencies of the echoes (especially active for great values of RoomSize)\\n// RoomSize : size of the reverberation room\\n// Dry : original signal\\n// Wet : reverberated signal\\n\\ndampSlider      = hslider(\\"Amortissement\\",0.5, 0, 1, 0.025)*scaledamp;\\nroomsizeSlider  = hslider(\\"TailleDeLaPiece\\", 0.5, 0, 1, 0.025)*scaleroom + offsetroom;\\nwetSlider       = hslider(\\"TauxReverberation\\", 0.3333, 0, 1, 0.025);\\ncombfeed        = roomsizeSlider;\\n\\n\\n// Comb and Allpass filters\\n//-------------------------\\n\\nallpass(dt,fb) = (_,_ <: (*(fb),_:+:@(dt)), -) ~ _ : (!,_);\\n\\ncomb(dt, fb, damp) = (+:@(dt)) ~ (*(1-damp) : (+ ~ *(damp)) : *(fb));\\n\\n\\n// Reverb components\\n//------------------\\n\\nmonoReverb(fb1, fb2, damp, spread)\\n    = _ <:  comb(combtuningL1+spread, fb1, damp),\\n            comb(combtuningL2+spread, fb1, damp),\\n            comb(combtuningL3+spread, fb1, damp),\\n            comb(combtuningL4+spread, fb1, damp),\\n            comb(combtuningL5+spread, fb1, damp),\\n            comb(combtuningL6+spread, fb1, damp),\\n            comb(combtuningL7+spread, fb1, damp),\\n            comb(combtuningL8+spread, fb1, damp)\\n        +>\\n            allpass (allpasstuningL1+spread, fb2)\\n        :   allpass (allpasstuningL2+spread, fb2)\\n        :   allpass (allpasstuningL3+spread, fb2)\\n        :   allpass (allpasstuningL4+spread, fb2)\\n        ;\\n\\nstereoReverb(fb1, fb2, damp, spread)\\n    = + <:  monoReverb(fb1, fb2, damp, 0), monoReverb(fb1, fb2, damp, spread);\\n\\n\\n// fxctrl : add an input gain and a wet-dry control to a stereo FX\\n//----------------------------------------------------------------\\n\\nfxctrl(g,w,Fx) =  _,_ <: (*(g),*(g) : Fx : *(w),*(w)), *(1-w), *(1-w) +> _,_;\\n\\n// Freeverb\\n//---------\\n\\nfreeverb = vgroup(\\"Reverb1\\", fxctrl(fixedgain, wetSlider, stereoReverb(combfeed, allpassfeed, dampSlider, stereospread)));\\n\\nprocess = freeverb;\\n}.process);"},{"inputs":[{"src":"1"}]},{"outputs":[{"dst":"0"}]},{"params":[{"path":"/reverb/Reverb1/Amortissement"},{"value":"0.125"},{"path":"/reverb/Reverb1/TailleDeLaPiece"},{"value":"0.800000011920929"},{"path":"/reverb/Reverb1/TauxReverberation"},{"value":"0.7250000238418579"}]}]}';
// 	recallScene(json);
}

function onunloadPedagogieScene(scene){

	scene.muteScene();
}



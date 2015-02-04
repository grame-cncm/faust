/******************************************************************** 
***************************  TESTS SCENARIOS ************************
********************************************************************/

function addBiquad(input){
	var D1 = "process = \\(x1).(x1 : +~(-1,\\(x2).((-1.862368f,x2 : *),(0.867104f,(x2 : mem) : *) : +) : *) : \\(x3).(((0.066448f,x3 : *),(0.0f,(x3 : mem) : *) : +),(-0.066448f,(x3 : mem : mem) : *) : +));";
	var myDiv =  createFaustModule(tempx, tempy)
	var mymodule = createDSP("biquad", D1, myDiv);
	
	var toReturn;
	
	for(var i=0 ; i<myDiv.parentNode.childNodes.length; i++){
		if(myDiv.parentNode.childNodes[i].className == "node node-input "){
		
			startDraggingConnection(input);
			stopDraggingConnection(myDiv.parentNode.childNodes[i]);
		}
		else if(myDiv.parentNode.childNodes[i].className == "node node-output"){
			return myDiv.parentNode.childNodes[i];
		}
	}
}

function biquadTest(){
	
	var OSC = "process = vgroup(\"Oscillator\", ((1,16 : <<),((((_,1 : +)~_,1 : - : float),(2.0f,3.141592653589793f : *) : *),(1,16 : << : float) : / : sin),(400,(192000,(1,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \\(x1).(x1,(x1 : floor) : -))~_ : _,(1,16 : << : float) : * : int) : rdtable),(-7 : \\(x2).(10,(x2,2e+01f : /) : pow) : _,(1,0.999f : -) : * : +~(_,0.999f : *)) : *);";
// 	var OSC = "process = vgroup(\"Oscillator\", ((1,16 : <<),((((_,1 : +)~_,1 : - : float),(2.0f,3.141592653589793f : *) : *),(1,16 : << : float) : / : sin),(hslider(\"freq [unit:Hz]\", 4e+02f, 2e+01f, 2.4e+04f, 1.0f),(192000,(1,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \\(x1).(x1,(x1 : floor) : -))~_ : _,(1,16 : << : float) : * : int) : rdtable),(-7 : \\(x2).(10,(x2,2e+01f : /) : pow) : _,(1,0.999f : -) : * : +~(_,0.999f : *)) : *);";
	var oscDiv = createFaustModule(tempx, tempy);
	var oscnode = createDSP("osc", OSC, oscDiv);
	
	var myInputBiquad;
	
	for(var i=0 ; i<oscDiv.parentNode.childNodes.length; i++){
		if(oscDiv.parentNode.childNodes[i].className == "node node-output"){
			myInputBiquad = oscDiv.parentNode.childNodes[i];
		}
	}
	for(var i=0; i<100; i++){
	
		var bibi = addBiquad(myInputBiquad);
		myInputBiquad = bibi;
	}
	
			
	for(var j=0 ; j<document.getElementById("output").childNodes.length; j++){
		if(document.getElementById("output").childNodes[j].className && document.getElementById("output").childNodes[j].className.indexOf("node node-input")>=0){
		
			startDraggingConnection(myInputBiquad);
			stopDraggingConnection(document.getElementById("output").childNodes[j]);
		}
	}
}

function addDelayLine(i, input, generalOutput){
	
	var delaycode = " R(d, acc, 1) = d; R(d, acc, b) = acc * R(d, acc, b-1); process = @(int(R(22050, 0.9, "+i.toString()+"))) : *(0.99) <: _,_;";
	var div = createFaustModule(tempx, tempy);
	createDSP("delay", delaycode, div);
		
	var output = null;
		
	for(var i=0 ; i<div.parentNode.childNodes.length; i++){
		if(div.parentNode.childNodes[i].className == "node node-input "){
			startDraggingConnection(input);
			stopDraggingConnection(div.parentNode.childNodes[i]);
		}
		else if(div.parentNode.childNodes[i].className == "node node-output"){
			output = div.parentNode.childNodes[i];
			
			startDraggingConnection(output);
			stopDraggingConnection(generalOutput);
		}
	}
	
	return output;
} 

function delaylinesTest(){

	var output;

	var karplus_code = "process = vgroup(\"Oscillator\", ((1,16 : <<),((((_,1 : +)~_,1 : - : float),(2.0f,3.141592653589793f : *) : *),(1,16 : << : float) : / : sin),(hslider(\"freq [unit:Hz]\", 1e+03f, 2e+01f, 2.4e+04f, 1.0f),(192000,(1,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \\(x1).(x1,(x1 : floor) : -))~_ : _,(1,16 : << : float) : * : int) : rdtable),(hslider(\"volume [unit:dB]\", -96.0f, -96.0f, 0.0f, 0.1f) : \\(x2).(10,(x2,2e+01f : /) : pow) : _,(1,0.999f : -) : * : +~(_,0.999f : *)) : *);";
// 	var karplus_code = "process=((_,12345 : +)~(_,1103515245 : *),2147483647.0f : /), 0.5 : * : vgroup(\"excitator\", _,(button(\"play\") : \\(x1).((x1,(x1 : mem) : -),0.0f : >) : +~\\(x2).(x2,((x2,0.0f : >), 128 : /) : -) : _,0.0f : >) : *) : vgroup(\"resonator\", (+ : \\(x3).(x3,((128,1.5f : - : int),(4096,1 : -) : &) : @))~(\\(x4).((x4,(x4 : mem) : +),2 : /) : _,(1.0f, 0.1 : -) : *));";

	var karM = createFaustModule(tempx, tempy);
	var mykar = createDSP("karplus", karplus_code, karM);	
// 	mykar.start();

	for(var i=0 ; i<karM.parentNode.childNodes.length; i++){
		if(karM.parentNode.childNodes[i].className == "node node-output"){
			output = karM.parentNode.childNodes[i];

// 			for(var j=0 ; j<document.getElementById("output").childNodes.length; j++){
// 				if(document.getElementById("output").childNodes[j].className == "node node-input"){
// 				
// 					startDraggingConnection(output);
// 					stopDraggingConnection(document.getElementById("output").childNodes[j]);
// // 					connectNodes(output, document.getElementById("output").childNodes[j]);	
// 				}
// 			}
		}
	}

	var generalOutput;

	var through = "process=_:>_*hslider(\"Gain\", 1, 0, 1, 0.025);";

	var throughM = createFaustModule(tempx, tempy);
	var mythrough = createDSP("gain", through, throughM);
	
	for(var i=0 ; i<throughM.parentNode.childNodes.length; i++){
		if(throughM.parentNode.childNodes[i].className == "node node-input ")
			generalOutput = throughM.parentNode.childNodes[i];
	
		else if(throughM.parentNode.childNodes[i].className == "node node-output"){
		
			var myoutput = throughM.parentNode.childNodes[i];
			
			for(var j=0 ; j<document.getElementById("output").childNodes.length; j++){
				if(document.getElementById("output").childNodes[j].className && document.getElementById("output").childNodes[j].className.indexOf("node node-input")>=0){

					startDraggingConnection(myoutput);
					stopDraggingConnection(document.getElementById("output").childNodes[j]);
				}
			}
		}
	}

	var D1 = "process = @(int(22050)) : *(0.99) <: _,_ ;";
	var D1M = createFaustModule(tempx, tempy);
	var myD1 = createDSP("delay", D1, D1M);
		
	for(var i=0 ; i<D1M.parentNode.childNodes.length; i++){
		if(D1M.parentNode.childNodes[i].className == "node node-input "){
		
			startDraggingConnection(output);
			stopDraggingConnection(D1M.parentNode.childNodes[i]);
// 			connectNodes(output, D1M.parentNode.childNodes[i]);
		}
		else if(D1M.parentNode.childNodes[i].className == "node node-output"){
		
			output = D1M.parentNode.childNodes[i];
			startDraggingConnection(output);
			stopDraggingConnection(generalOutput);
		}
	}

	output = addDelayLine(2, output, generalOutput);
	output = addDelayLine(3, output, generalOutput);
	output = addDelayLine(4, output, generalOutput);
	output = addDelayLine(5, output, generalOutput);
	output = addDelayLine(6, output, generalOutput);
	output = addDelayLine(7, output, generalOutput);
	output = addDelayLine(8, output, generalOutput);
	output = addDelayLine(9, output, generalOutput);
	output = addDelayLine(10, output, generalOutput);
	output = addDelayLine(11, output, generalOutput);
	output = addDelayLine(12, output, generalOutput);
	output = addDelayLine(13, output, generalOutput);
	output = addDelayLine(14, output, generalOutput);
	output = addDelayLine(15, output, generalOutput);
	output = addDelayLine(16, output, generalOutput);
	output = addDelayLine(17, output, generalOutput);
	output = addDelayLine(18, output, generalOutput);
	output = addDelayLine(19, output, generalOutput);
	output = addDelayLine(20, output, generalOutput);
	output = addDelayLine(21, output, generalOutput);
	output = addDelayLine(22, output, generalOutput);
	output = addDelayLine(23, output, generalOutput);
	output = addDelayLine(24, output, generalOutput);
	output = addDelayLine(25, output, generalOutput);
	output = addDelayLine(26, output, generalOutput);
	output = addDelayLine(27, output, generalOutput);
	output = addDelayLine(28, output, generalOutput);
	output = addDelayLine(29, output, generalOutput);
	output = addDelayLine(30, output, generalOutput);
	output = addDelayLine(31, output, generalOutput);
	output = addDelayLine(32, output, generalOutput);
	output = addDelayLine(33, output, generalOutput);
	output = addDelayLine(34, output, generalOutput);
	output = addDelayLine(35, output, generalOutput);
	output = addDelayLine(36, output, generalOutput);
	output = addDelayLine(37, output, generalOutput);
	output = addDelayLine(38, output, generalOutput);
	output = addDelayLine(39, output, generalOutput);
	output = addDelayLine(40, output, generalOutput);
	output = addDelayLine(41, output, generalOutput);
	output = addDelayLine(42, output, generalOutput);
	output = addDelayLine(43, output, generalOutput);
	output = addDelayLine(44, output, generalOutput);
	output = addDelayLine(45, output, generalOutput);
	output = addDelayLine(46, output, generalOutput);
	output = addDelayLine(47, output, generalOutput);
	output = addDelayLine(48, output, generalOutput);
	output = addDelayLine(49, output, generalOutput);
	output = addDelayLine(50, output, generalOutput);



//     setTimeout(updateKarplus(mykar),500);
}
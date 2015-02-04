/******************************************************************** 
***********************  CREATE FAUST EQUIVALENT ********************
********************************************************************/

function computeNode(node){

	var nodeInputs = node.inputConnections;

	var faustResult = "";
	
// Iterate on input Nodes to compute them
	
	if(nodeInputs){
		faustResult += "(";
		for(element in nodeInputs){

			var sourceNode = nodeInputs[element].source;
	
			console.log(sourceNode);

			if(sourceNode){		
				if(element != 0)
					faustResult += "),(";

				faustResult += computeNode(sourceNode);
			}
		}	
		faustResult += "):> ";
	}
	
	
	var nodeCode = node.Source;
	
	if(node.id == "output" || node.id == "input")
		nodeCode = "process=_,_;";

// vgroup(\"[" + window.index + "]component" + window.index + "\", ..... )
// stereoize()


	faustResult += "stereoize(environment{" + nodeCode + "}.process)";	
	
	// window.index++;
	
	return faustResult;
}

// To avoid sharing instances of a same factory in the resulting Faust Equivalent
function wrapSourceCodesInGroups(){

	var modules = getElementsByClassName("div", "moduleFaust");

	for (var i = 0; i < modules.length; i++)
		modules[i].Source = "process = vgroup(\"component"+ i.toString() + "\",environment{" + modules[i].Source + "}.process);";
}

function getFaustEquivalent(){

	if(getElementsByClassName("div", "moduleFaust").length > 0){
// 	if(window.myArray.length != 0){
		var dest = document.getElementById("output");
// 	dest.audioNode = audioContext.destination;
	
		faustResult = "stereoize(p) = S(inputs(p), outputs(p))\n\
				with {\n\
				  // degenerated processor with no outputs\n\
				S(n,0) = !,! : 0,0; 		// just in case, probably a rare case\n\
				\n\
				  // processors with no inputs\n\
				S(0,1) = p <: _/2,_/2; 	// add two fake inputs and split output\n\
				S(0,2) = p;\n\
				S(0,n) = p,p :> _,_;	// we are sure this will work if n is odd\n\
				 \n\
				  // processors with one input\n\
				S(1,1) = p,p; 				// add two fake inputs and split output \n\
				S(1,n) = p,p :> _/2,_/2;		// we are sure this will work if n is odd\n\
				 \n\
			  // processors with two inputs\n\
				S(2,1) = p <: _,_; 			// split the output\n\
				S(2,2) = p; 				// nothing to do, p is already stereo\n\
			 \n\
			  // processors with inputs > 2 and outputs > 2\n\
			S(n,m) = _,_ <: p,p :> _,_;	// we are sure this works if n or p are odd\n\
			};\n\
			\n\
			recursivize(p,q) = (_,_,_,_ :> stereoize(p)) ~ stereoize(q);\n\
			";

		var patchName = document.getElementById("PatchName").innerHTML;
	
		faustResult += "process = vgroup(\""+ patchName + "\"," + computeNode(dest) +");";
	
		return faustResult;
	}
	else
		return null;
}

function createFaustEquivalent(){

	var patchName = document.getElementById("PatchName").innerHTML;

// Save All Params	
	var modules = getElementsByClassName("div", "moduleFaust");
	
	for (var i = 0; i < modules.length; i++)		
		saveParams(modules[i]);
	
// Concatenate All Params
	var fullParams = new Array();

	for (var i = 0; i < modules.length; i++) {
		
		var arrayParams = modules[i].params;
		
//   BIDOUILLE!!!!! Adding component wrapping to avoid merging of 2 instances of same factory
		for(key in arrayParams){
			var newKey = "/" + patchName + "/component" + i.toString() + key;
			fullParams[newKey] = arrayParams[key];
		}
	}

	wrapSourceCodesInGroups();
	
	var faustResult = getFaustEquivalent();
	
	if(faustResult){

// Save concatenated params in new DIV

		var DSP = createDSP(faustResult);
		
		if(DSP){
	    	
			cleanScene();
			
			var faustDiv = createFaustModule(tempx, tempy, patchName);

			faustDiv.params = fullParams;
	    
			saveModuleCharacteristics(faustDiv, patchName, DSP, faustResult);
			createFaustInterface(faustDiv);
			addInputOutputNodesToModule(faustDiv);				    
	
// 			recallParams(parent, fullParams);

		// Connect Automatically to Output
			var myoutput;
		
			for(var i=0; i<faustDiv.childNodes.length; i++){
				if(faustDiv.childNodes[i].className == "node node-output"){
		
					myoutput = faustDiv.childNodes[i];
			
					for(var j=0 ; j<document.getElementById("output").childNodes.length; j++){
						if(document.getElementById("output").childNodes[j].className && document.getElementById("output").childNodes[j].className.indexOf("node node-input")>=0)
							createConnection(myoutput, document.getElementById("output").childNodes[j]);
					}
				}
			}
		}
	}
}


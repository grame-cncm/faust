/*				EQUIVALENTFAUST.JS

	HELPER FUNCTIONS TO CREATE FAUST EQUIVALENT EXPRESSION FROM A PATCH
	
	FIRST PART --> DERECURSIVIZE THE PATCH
	SECOND PART --> CREATE THE FAUST EQUIVALENT FROM THE "DERECURSIVIZED" PATCH
*/


"use strict";

/******************************************************************** 
*************  ALGORITHME DE DÉRECURSIVATION DU PATCH ***************
********************************************************************/

function isModuleExisting(Module){

	if(window.recursiveMap[Module.patchID])
		return true;
		
	return false;

}

function giveIdToModules(scene){
	
	var modules = scene.getModules();
	
	for(var i=0; i<modules.length; i++){
		modules[i].patchID = i+1;
	}
}

function treatRecursiveModule(Module){
			
// 	Save recursion in map and flag it
	var ModuleToReplace = getFirstOccurenceOfModuleInCourse(Module);
	
	window.recursiveMap[Module.patchID] = ModuleToReplace;
	
	ModuleToReplace.recursiveFlag = true;
}

function getFirstOccurenceOfModuleInCourse(Module){
	
	for(var i=0; i< Module.course.length; i++){
		if(Module.patchID == Module.course[i].patchID){
			return Module.course[i];
		}
	}
	
	return null;
}

function createTree(Module, parent){
	var myModule = document.createElement("div");
	myModule.patchID = Module.patchID;
	myModule.course = [];
	
	if(parent){
	
// 		COPY PARENT COURSE
		for(var k=0; k<parent.course.length; k++)
			myModule.course[k] = parent.course[k];
	}

	myModule.ModuleInputs = [];
	myModule.recursiveFlag = false;
		
	if(isModuleExisting(myModule)){
	
		var ModuleToReuse = window.recursiveMap[myModule.patchID];
		
		myModule.sourceCode = ModuleToReuse.sourceCode;
		myModule.ModuleInputs = ModuleToReuse.ModuleInputs;
		
	}
	else if(getFirstOccurenceOfModuleInCourse(myModule)){

		treatRecursiveModule(myModule);
		
// 	Stop Recursion in Tree		
		myModule = null;
	}
	else if(Module.patchID == "input"){
		myModule.sourceCode = Module.getSource();
		myModule.course[myModule.course.length] = myModule; 
	}
	else{
		myModule.sourceCode = Module.getSource();

		myModule.course[myModule.course.length] = myModule; 

		if(Module.getInputConnections()){
			for(var j=0; j<Module.getInputConnections().length; j++)
				myModule.ModuleInputs[j] = createTree(Module.getInputConnections()[j].source, myModule);
		}
	}
	
	
	return myModule;
}

/******************************************************************** 
***********************  CREATE FAUST EQUIVALENT ********************
********************************************************************/

//*** The faust equivalent of a scene is calculated following these rules:
//*** The tree starting from the output Module is computed (tree 1)
//*** Then if there are unconnected output Modules, there Modules are computed (tree 2, ..., n)
//*** All trees are composed in parallel

//*** Every Faust Expression is "Stereoized" before composition with other expressions to ensure composability

// Computing a Module is computing its entries and merging them in the Module's own faust code.
function computeModule(Module){

	var ModuleInputs = Module.ModuleInputs;	
	var faustResult = "";
	
// Iterate on input Modules to compute them
	if(ModuleInputs && ModuleInputs.length != 0){

			var inputCode = "";

			for(var i=0; i<ModuleInputs.length; i++){
				if(ModuleInputs[i]){

					if(ModuleInputs[i].sourceCode && ModuleInputs[i].sourceCode.length>0){		
						if(i != 0)
							inputCode += ",";

						inputCode += computeModule(ModuleInputs[i]);
					}
				}
			}	

			if(inputCode != ""){
				if(Module.recursiveFlag)
					faustResult += "(" + inputCode + ":> ";
				else
					faustResult += inputCode + ":> ";
			}
	}
	
	var ModuleCode = Module.sourceCode;
	
	if(Module.recursiveFlag)
		faustResult += "stereoize(environment{" + ModuleCode + "}.process))~(_,_)";
	else
		faustResult += "stereoize(environment{" + ModuleCode + "}.process)";
	

	return faustResult;
}

// Computing the trees unconnected to the output
function connectUnconnectedModules(faustModuleList, output){

	for(var i in faustModuleList){
	
		var outputNode = faustModuleList[i].getOutputNode();
		
		if(outputNode && (!faustModuleList[i].getOutputConnections || !faustModuleList[i].getOutputConnections() || faustModuleList[i].getOutputConnections().length == 0))
			createConnection(faustModuleList[i], faustModuleList[i].getOutputNode(), output, output.getInputNode());		
	}
}

//Calculate Faust Equivalent of the Scene
function getFaustEquivalent(scene, patchName){

	var faustModuleList = scene.getModules();

	if(faustModuleList.length > 0){
	
		var dest = scene.getAudioOutput();
		var src = scene.getAudioInput();
		
		if(src)
			src.patchID = "input";
				
		var faustResult = "stereoize(p) = S(inputs(p), outputs(p))\n\
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

		connectUnconnectedModules(faustModuleList, dest);
	
		window.recursiveMap = [];
		
		giveIdToModules(scene);	
		
		var destinationDIVVV = createTree(dest, null);
		
		if(dest.getInputConnections())
			faustResult += "process = vgroup(\""+ patchName + "\",(" + computeModule(destinationDIVVV) + "));";
		
// 		console.log(faustResult);
	
		return faustResult;
	}
	else
		return null;
}





//--------Plus Utilisé ---------------Create Faust Equivalent Module of the Scene

// To avoid sharing instances of a same factory in the resulting Faust Equivalent
function wrapSourceCodesInGroups(){

	var modules = getElementsByClassName("div", "moduleFaust");

	for (var i = 0; i < modules.length; i++)
		modules[i].Source = "process = vgroup(\"component"+ i.toString() + "\",environment{" + modules[i].Source + "}.process);";
}

function createFaustEquivalent(scene, patchName, parent){

// Save All Params	
	var modules = scene.getModules();
	
	for (var i = 0; i < modules.length; i++){	
		if(modules[i])
			modules[i].saveParams();
	}
	
// Concatenate All Params
	var fullParams = new Array();

	for (var i = 0; i < modules.length; i++) {
		
		if(modules[i]){
		
			var arrayParams = modules[i].getParams;
		
//   BIDOUILLE!!!!! Adding component wrapping to avoid merging of 2 instances of same factory
			for(key in arrayParams){
				var newKey = "/" + patchName /*+ "/component" + i.toString()*/ + key;
				fullParams[newKey] = arrayParams[key];
			}
		}
	}

// THIS SHOULD BE DONE BUT FOR NOW IT CAUSED A PROBLEM, I CAN'T REMEMBER WHICH... 
// 	wrapSourceCodesInGroups();
	
	var faustResult = getFaustEquivalent(scene, patchName);
	
	if(faustResult){

// Save concatenated params in new DIV

		var DSP = createDSP(faustResult);
					
		if(DSP){

			var faustModule = createModule(idX++, document.body.scrollWidth/3, document.body.scrollHeight/3, patchName, parent, window.scenes[2].removeModule);
 			faustModule.createDSP(faustResult);
 			faustModule.setParams(fullParams);

 			return faustModule;
		}
	}
	return null;
}



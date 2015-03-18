/******************************************************************** 
*************  ALGORITHME DE DÉRECURSIVATION DU PATCH ***************
********************************************************************/
"use strict";

function isNodeExisting(Node){

	if(window.recursiveMap[Node.patchID])
		return true;
		
	return false;

}

function giveIdToModules(scene){
	
	var modules = scene.getModules();
	
	for(var i=0; i<modules.length; i++){
		modules[i].patchID = i+1;
	}
}

function treatRecursiveNode(Node){
			
// 	Save recursion in map and flag it
	var nodeToReplace = getFirstOccurenceOfNodeInCourse(Node);
	
	window.recursiveMap[Node.patchID] = nodeToReplace;
	
	nodeToReplace.recursiveFlag = true;
}

function getFirstOccurenceOfNodeInCourse(Node){
	
	for(var i=0; i< Node.course.length; i++){
		if(Node.patchID == Node.course[i].patchID){
			return Node.course[i];
		}
	}
	
	return null;
}

function createTree(node, parent){
	var myNode = document.createElement("div");
	myNode.patchID = node.patchID;
	myNode.course = [];
	
	if(parent){
	
// 		COPY PARENT COURSE
		for(var k=0; k<parent.course.length; k++)
			myNode.course[k] = parent.course[k];
	}
		
	myNode.nodeInputs = [];
	myNode.recursiveFlag = false;
		
	if(isNodeExisting(myNode)){
	
		var nodeToReuse = window.recursiveMap[myNode.patchID];
		
		myNode.sourceCode = nodeToReuse.sourceCode;
		myNode.nodeInputs = nodeToReuse.nodeInputs;
		
	}
	else if(getFirstOccurenceOfNodeInCourse(myNode)){

		treatRecursiveNode(myNode);
		
// 	Stop Recursion in Tree		
		myNode = null;
	}
	else{
		myNode.sourceCode = node.getSource();

		myNode.course[myNode.course.length] = myNode; 

		if(node.getInputConnections()){
			for(var j=0; j<node.getInputConnections().length; j++)
				myNode.nodeInputs[j] = createTree(node.getInputConnections()[j].source, myNode);
		}
	}
	
	
	return myNode;
}

/******************************************************************** 
***********************  CREATE FAUST EQUIVALENT ********************
********************************************************************/

//*** The faust equivalent of a scene is calculated following these rules:
//*** The tree starting from the output node is computed (tree 1)
//*** Then if there are unconnected output nodes, there nodes are computed (tree 2, ..., n)
//*** All trees are composed in parallel

//*** Every Faust Expression is "Stereoized" before composition with other expressions to ensure composability

// Computing a node is computing its entries and merging them in the node's own faust code.
function computeNode(node){

// 	var nodeInputs = node.inputConnections;
	var nodeInputs = node.nodeInputs;
	
	var faustResult = "";
	
// Iterate on input Nodes to compute them
	if(nodeInputs && nodeInputs.length != 0){
	
// 			faustResult += "(";

			var inputCode = "";

			for(var i=0; i<nodeInputs.length; i++){
				if(nodeInputs[i]){

					if(nodeInputs[i].sourceCode && nodeInputs[i].sourceCode.length>0){		
						if(i != 0)
							inputCode += ",";
// 							inputCode += "),(";

						inputCode += computeNode(nodeInputs[i]);
					}
				}
			}	
// 			faustResult += "):> ";
			if(inputCode != ""){
				if(node.recursiveFlag)
					faustResult += "(" + inputCode + ":> ";
				else
					faustResult += inputCode + ":> ";
			}
	}
	
	var nodeCode = node.sourceCode;
	
// 	if(node.id == "output" || node.id == "input")
// 		nodeCode = "process=_,_;";

	if(node.recursiveFlag)
		faustResult += "stereoize(environment{" + nodeCode + "}.process))~(_,_)";
	else
		faustResult += "stereoize(environment{" + nodeCode + "}.process)";
	
	return faustResult;
}

// Computing the trees unconnected to the output
function computeUnconnectedNodes(faustModuleList){

	var j = 0;
	var computationString = "";

	for(var i=0 ; i<faustModuleList.length; i++){
	
		var outputNode = faustModuleList[i].getOutputNode();
		
		if(outputNode && !faustModuleList[i].getOutputConnections()){
		
			if(j != 0)
				computationString += ",";
		
			computationString += computeNode(faustModuleList[i]) + ":>_,_";
				
			j++;
		}
	}
	
	return computationString;
}

// To avoid sharing instances of a same factory in the resulting Faust Equivalent
function wrapSourceCodesInGroups(){

	var modules = getElementsByClassName("div", "moduleFaust");

	for (var i = 0; i < modules.length; i++)
		modules[i].Source = "process = vgroup(\"component"+ i.toString() + "\",environment{" + modules[i].Source + "}.process);";
}

//Calculate Faust Equivalent of the Scene
function getFaustEquivalent(scene, patchName){

	var faustModuleList = scene.getModules();

	if(faustModuleList.length > 0){
	
		var dest = scene.audioOutput();
				
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

		var unConnectedComputation = computeUnconnectedNodes(faustModuleList);
	
		window.recursiveMap = [];
// 		var destNode = document.createElement("div");
// 		dest.patchID = "0";
// 		dest.Source = "process=_,_;";
		
		giveIdToModules(scene);	
		
		var destinationDIVVV = createTree(dest, null);
		
		if(dest.getInputConnections()){
		
			faustResult += "process = vgroup(\""+ patchName + "\",(" + computeNode(destinationDIVVV);

			if(unConnectedComputation)
				faustResult += "," + unConnectedComputation;	
		
			faustResult += "));";
		}
		else
			faustResult += "process = vgroup(\""+ patchName + "\",(" + unConnectedComputation + "));";;	
		
// 		console.log(faustResult);
		
		return faustResult;
	}
	else
		return null;
}

//Create Faust Equivalent Module of the Scene
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

// 	wrapSourceCodesInGroups();
	
	var faustResult = getFaustEquivalent(scene, patchName);
	
	if(faustResult){

// Save concatenated params in new DIV

		var DSP = createDSP(faustResult);
					
		if(DSP){

			var faustModule = createNode(idX++, document.body.scrollWidth/3, document.body.scrollHeight/3, patchName, parent, window.scenes[2].removeModule);
 			faustModule.setDSP(faustResult);
 			faustModule.setParams(fullParams);

 			return faustModule;
		}
	}
	return null;
}



/*
	Faust Related Functions
		- creation/deletion of Faust Running Modules
*/

/******************************************************************** 
**************************  CREATE ELEMENT **************************
********************************************************************/

//---- Create DSP Factory/Instance
function createDSP(dsp_code){
			         			            
    var factory = faust.createDSPFactory(dsp_code);
	
	if (!factory) {
    	alert(faust.getErrorMessage());    
        return null;
	}
                
    var DSP = faust.createDSPInstance(factory, window.audioContext, 1024);
           
	_f4u$t.main_loop = function() {}

   	return DSP;		
}

/******************************************************************** 
**************************  DELETE ELEMENT **************************
********************************************************************/

//---- Delete the DSP, it's connections and remove it from list
function deleteDSP(DSP){

// 	TO DO SAFELY --> FOR NOW CRASHES SOMETIMES
	if(DSP){
	    faust.deleteDSPInstance(DSP);
	} 	
}

/******************************************************************** 
************************  SAVE CHARACTERISTICS **********************
********************************************************************/

//Mapping Div --> (Name, DSP, SourceCode)
function saveModuleCharacteristics(faustDiv, dspName, faustDSP, sourceCode){

	faustDiv.Name = dspName;
	faustDiv.DSP = faustDSP;
	faustDiv.Source = sourceCode;
}


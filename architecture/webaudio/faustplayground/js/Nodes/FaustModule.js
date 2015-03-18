/*
	Faust Related Functions
		- creation/deletion of Faust Running Modules
*/

/******************************************************************** 
**************************  CREATE ELEMENT **************************
********************************************************************/

//---- Create DSP Factory/Instance
function createDSP(dsp_code){		         			   
	         			            
	var args = ["-I", "http://faust.grame.fr/faustcode/"]; 			         			 
    var factory = faust.createDSPFactory(dsp_code, args);
	
	if (!factory) {
    	alert(faust.getErrorMessage());    
        return null;
	}
                
    var DSP = faust.createDSPInstance(factory, window.audioContext, 1024);

   	return DSP;		
}

/******************************************************************** 
**************************  DELETE ELEMENT **************************
********************************************************************/

//---- Delete the DSP, it's connections and remove it from list
// function deleteDSP(DSP){
// 
// // 	TO DO SAFELY --> FOR NOW CRASHES SOMETIMES
// 	if(DSP){
// 	    faust.deleteDSPInstance(DSP);
// 	} 	
// }

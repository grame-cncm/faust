function getElementsByClassName(tag, className){
    var elements = document.getElementsByTagName(tag);
    var results = new Array();
    for(var i=0; i<elements.length; i++){
        if(elements[i].className == className){
            results[results.length] = elements[i];
        }
    }
    return results;
}

function getOutputNodeFromDiv(div){

	for(var i=0 ; i<div.childNodes.length; i++){
		if(div.childNodes[i].className && div.childNodes[i].className.indexOf("node node-output")>=0){
			return div.childNodes[i];
		}
	}
	
	return null;
}

function getInputNodeFromDiv(div){

	for(var i=0 ; i<div.childNodes.length; i++){
		if(div.childNodes[i].className && div.childNodes[i].className.indexOf("node node-input")>=0){
			return div.childNodes[i];
		}
	}
	
	return null;
}

// function unzipBlob(blob, callback) {
// 	zip.createReader(new zip.BlobReader(blob), function(zipReader) {
// 		zipReader.getEntries(function(entries) {
// 			entries[0].getData(new zip.BlobWriter(zip.getMimeType(entries[0].filename)), function(data) {
// 				zipReader.close();
// 				callback(data);
// 			});
// 		});
// 	}, onerror);
// }

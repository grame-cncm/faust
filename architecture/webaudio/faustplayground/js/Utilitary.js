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
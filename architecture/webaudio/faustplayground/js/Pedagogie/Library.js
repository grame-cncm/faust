
function ViewFolderContent(selector){
	
	var data = JSON.parse(window.libraryContent);
		
	var selFolder = selector.section;
						
    var section = data[selFolder];
    
    var sublist=document.createElement("ul");
	sublist.className="subsections";
	selector.parentNode.appendChild(sublist);
							
	for (subsection in section) {
			
		var liElement = document.createElement("li");
		sublist.appendChild(liElement);

		var filename = section[subsection].toString().split( '/' ).pop();
		filename = filename.toString().split('.').shift();
		
		var link = document.createElement("a");
		link.className="link";
		var linkAdd = "http://faust.grame.fr/www/pedagogie/" + selFolder + "/" + filename + ".dsp";
		link.setAttribute("href", linkAdd);
		link.textContent = filename;
		link.onclick = onclickPrevent;
		link.ondrag = onLinkDrag;
		liElement.appendChild(link);
	}

}

function onLinkDrag(event){

	if(event.x > document.getElementById("library").getBoundingClientRect().width){
		var img = document.getElementById("arrow");
		img.src = "img/open.png";
		img.state = "closed";
		
		DeleteLibraryList(img);
	}
}

function onclickPrevent(event){
	event.preventDefault();
}

function DeleteFolderContent(selector){

	var liElement = selector.parentNode;
	
	for(var i=0; i<liElement.childNodes.length; i++){
	
		if(liElement.childNodes[i].className=="subsections"){
			liElement.removeChild(liElement.childNodes[i]);
			break;
		}
	}
	

}

function ChangeSectionState(event){
			
	if(event.target.state == "closed"){
		event.target.src = "img/triangleOpen.png";
		event.target.state = "opened";
			
		ViewFolderContent(event.target);
	}
	else{
		event.target.src = "img/triangleClose.png";
		event.target.state = "closed";
		
		DeleteFolderContent(event.target);
	}
}

function ViewLibraryList(selector){

	document.getElementById("libraryTitle").style.cssText = " writing-mode:lr-tb; -webkit-transform:rotate(0deg); -moz-transform:rotate(0deg); -o-transform: rotate(0deg); display:block; position: relative; top:3%; left:5px; font-family: 'Droid Serif', Georgia, serif;  font-size:20px; z-index:3; margin: 0px 0px 0px 0px; padding: 0px 0px 0px 0px;";
	document.getElementById("library").style.cssText = "width:250px;";
	document.getElementById("arrow").style.cssText = "display: block; position: absolute; left:200px; top:2%; z-index:3;";
	
	var spaceDiv = document.createElement("div");
	spaceDiv.className = "space";

	document.getElementById("library").appendChild(spaceDiv);
	
	var url = "http://faust.grame.fr/www/pedagogie/index.json";
			
	var getrequest = new XMLHttpRequest();
				
	getrequest.onreadystatechange = function() {
		if(getrequest.readyState == 4 && getrequest.status == 200) {
	
			window.libraryContent = getrequest.responseText;
	    		
			var data = JSON.parse(window.libraryContent);

			var sections = ["instruments", "effets"];

			for(var i=0; i<2; i++){
				var section = sections[i];

// 			for (section in data) {
			
				var div=document.createElement("ul");
				div.style.cssText = "padding: 0; list-style-type: none;";
				selector.parentNode.appendChild(div);
			
				if(isTooltipEnabled()){
					var tooltip = toolTipForLibrary(section);	
					div.appendChild(tooltip);
				}
			
				var sel1=document.createElement("li");
				sel1.className="sections";
				

				div.appendChild(document.createElement("br"));
			
				
				var imageNode = document.createElement('img');
				imageNode.src= "img/triangleClose.png";
				imageNode.state = "closed";
				imageNode.section = section;
				imageNode.onclick = ChangeSectionState;
				
				sel1.appendChild(imageNode);
				sel1.appendChild(document.createTextNode("  "+section));
			
				sel1.style.cssText=" padding: 0em 0em 0em 1.5em; list-style-type : none;";
				div.appendChild(sel1);	
				div.appendChild(document.createElement("br"));
				
				ViewFolderContent(imageNode);
        	}
    	}
	}
	getrequest.open("GET", url, true);
	getrequest.send(null);
	
// 	document.getElementById("library").onmouseover = function () {};
// 	document.getElementById("library").onmouseout = ChangeLibraryState;
}

function DeleteLibraryList(selector){

	var libraryDiv = selector.parentNode;

	for(var i=libraryDiv.childNodes.length-1; i>=0; i--){
	
		if(libraryDiv.childNodes[i] != selector && libraryDiv.childNodes[i] != document.getElementById("libraryTitle"))
			libraryDiv.removeChild(libraryDiv.childNodes[i]);
	}
	
	document.getElementById("libraryTitle").style.cssText =  " writing-mode:tb-rl; -webkit-transform:rotate(270deg); -moz-transform:rotate(270deg); -o-transform: rotate(270deg); display:block; position: relative; top:50%; right:250%; width:300px; font-family: 'Droid Serif', Georgia, serif;  font-size:20px; z-index:3; margin: 0px 0px 0px 0px; padding: 0px 0px 0px 0px;";
	document.getElementById("library").style.cssText = "width:50px;";
	document.getElementById("arrow").style.cssText = "display: block; margin-left: auto; margin-right: auto;";
// 	document.getElementById("library").onmouseout = function () {};
// 	document.getElementById("library").onmouseover = ChangeLibraryState;
}

function ChangeLibraryState(event){
	
// 	event.preventDefault();
	
	var libDiv = document.getElementById("library");
	
	var boudingRect = libDiv.getBoundingClientRect();

	var img = document.getElementById("arrow");
			
	if(event.type == "mouseover" && img.state == "closed"){
		img.src = "img/close.png";
		img.state = "opened";
		
		ViewLibraryList(img);
	}
	else if(event.type == "mouseout" && (event.clientX > boudingRect.right || event.clientX < boudingRect.left || event.clientY < boudingRect.top || event.clientY > boudingRect.bottom)){
	
		img.src = "img/open.png";
		img.state = "closed";
		
		DeleteLibraryList(img);
	}
}

function initLibrary(parent){

	var libraryDiv = document.createElement('div');
	libraryDiv.id = "library";
	libraryDiv.style.cssText = "width:50px;";
	
	parent.appendChild(libraryDiv);

	var libraryTitle = document.createElement('span');
	libraryTitle.id = "libraryTitle";
	libraryTitle.className = "title";
	libraryTitle.textContent="Bibliothèque Faust";
	libraryDiv.appendChild(libraryTitle);

	var imageNode = document.createElement('img');
	imageNode.id = "arrow";
	imageNode.src= "img/open.png";
	imageNode.state = "closed";
	imageNode.style.cssText = "display: block; margin-left: auto; margin-right: auto; z-index:3;";
// 	imageNode.onclick = ChangeLibraryState;
				
	libraryDiv.appendChild(imageNode);
	
	libraryDiv.onmouseover = ChangeLibraryState;
	libraryDiv.onmouseout = ChangeLibraryState;
}




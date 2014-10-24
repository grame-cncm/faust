// ui.js
// -----------------
//
// Automatically (re)generate/destroy sliders according to Faust DSP module
// By Edgar Berdahl, July 2014
// Grame, 2014
//
// Currently addHorizontalBargraph, addVerticalBargraph, declare,
// openTabBox, openHorizontalBox, openVerticalBox, and closeBox are not really handled.
//
// Started from autosurface.js by rld, 5.04
//

// inlets and outlets
inlets = 1;
outlets = 2;

// global variables and arrays
var numwidgets = -1;  // The actual number if widgets is numwidgets+1
var thevalues = new Array(128);

var widgHeight = 30;
var hBase = 150;

// Maxobj variables for scripting
var thecomments = new Array(128);
var thesliders = new Array(128);
var theMessages = new Array(128);
var thenumberBoxes = new Array(128);
var thefunnel;

var inputs_items = new Array(128);
var ouputs_items = new Array(128);

// JSON parsing
parse_ui = function(ui, patcher) 
{
    var i;
    for (i = 0; i < ui.length; i++) {
        parse_group(ui[i], patcher);
    }
}
    
parse_group = function(group, patcher) 
{
    if (group.items) {
        parse_items(group.items, patcher);
    }
}

parse_items = function(items, patcher) 
{
    var i;
    for (i = 0; i < items.length; i++) {
        parse_item(items[i], patcher);
    }
}

startsWith = function(str, prefix) 
{
    return str.lastIndexOf(prefix, 0) === 0;
}

get_faustgen = function(patcher)
{
	var obj = patcher.firstobject;
	while (obj) {
		if (startsWith(obj.varname, "faustgen-")) {
			return obj;
		}
		obj = obj.nextobject;
	}
	return null;
}

parse_item = function(item, patcher) 
{
	var msgSink = patcher.getnamed("mymsgScriptingName");
	
	//Does not work for now...
	//var msgSink = get_faustgen(patcher); 
	
    if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
	
        parse_items(item.items, patcher);

    } else if (item.type === "hbargraph" || item.type === "vbargraph") {
	
		numwidgets++;
	
		thecomments[numwidgets] = patcher.newdefault(hBase,20+widgHeight*numwidgets,"comment");
		thecomments[numwidgets].message("set","bargraph"+numwidgets);
	
		// TODO : create "meter" instead of "multiSlider" 
		
		thesliders[numwidgets] = patcher.newobject("user", "multiSlider", hBase+130, 20+widgHeight*numwidgets, 120, 20, 0., 1., 1, 2936, 15, 0, 0, 2, 0, 0, 0);
		thesliders[numwidgets].message('settype', 1);
		thesliders[numwidgets].message('contdata', 1);
		thesliders[numwidgets].message('setstyle', 0);
		thesliders[numwidgets].message('setminmax', parseFloat(item.min), parseFloat(item.max));
   		thesliders[numwidgets].message(parseFloat(item.init));  // Set initial value
        
        // Bargraph ScriptingName is set with the complete parameter path, so that faustgen~ can directly address them
		thesliders[numwidgets].message('varname', item.address);
		
		thenumberBoxes[numwidgets] = patcher.newobject("flonum",hBase+258,20+widgHeight*numwidgets,80,13);
		thenumberBoxes[numwidgets].message('min',parseFloat(item.min));
		thenumberBoxes[numwidgets].message('max',parseFloat(item.max));
			
		patcher.hiddenconnect(thesliders[numwidgets], 0, thenumberBoxes[numwidgets], 0);		
		patcher.hiddenconnect(theMessages[numwidgets], 0, msgSink, 0);
				
		// direct connection to faustgen~ does not work...
		//patcher.hiddenconnect(thenumberBoxes[numwidgets], 0, msgSink, 0);
 	
    } else if (item.type === "vslider" || item.type === "hslider" ) {
	
		numwidgets++;
	
		thecomments[numwidgets] = patcher.newdefault(hBase,20+widgHeight*numwidgets,"comment");
		thecomments[numwidgets].message("set",item.label);

		thesliders[numwidgets] = patcher.newobject("user", "multiSlider", hBase+130, 20+widgHeight*numwidgets, 120, 20, 0., 1., 1, 2936, 15, 0, 0, 2, 0, 0, 0);
		thesliders[numwidgets].message('settype', 1);
		thesliders[numwidgets].message('contdata', 1);
		thesliders[numwidgets].message('setstyle', 0);
		thesliders[numwidgets].message('setminmax', parseFloat(item.min), parseFloat(item.max));
   		thesliders[numwidgets].message(parseFloat(item.init));  // Set initial value
		thesliders[numwidgets].message('varname', item.address);
			
		thenumberBoxes[numwidgets] = patcher.newobject("flonum",hBase+258,20+widgHeight*numwidgets,80,13);
		thenumberBoxes[numwidgets].message('min',parseFloat(item.min));
		thenumberBoxes[numwidgets].message('max',parseFloat(item.max));
			
		patcher.hiddenconnect(thesliders[numwidgets], 0, thenumberBoxes[numwidgets], 0);
			
		theMessages[numwidgets] = patcher.newobject("message",hBase+345,23+widgHeight*numwidgets,350,9);
		theMessages[numwidgets].message("set",item.address,"\$1");
		
		patcher.hiddenconnect(thenumberBoxes[numwidgets], 0, theMessages[numwidgets], 0);
		patcher.hiddenconnect(theMessages[numwidgets], 0, msgSink, 0);
		
		// direct connection to faustgen~ does not work...
		//patcher.hiddenconnect(thenumberBoxes[numwidgets], 0, msgSink, 0);

	} else if (item.type === "button" || item.type === "checkbox") {
		
		numwidgets++;
		thecomments[numwidgets] = patcher.newdefault(hBase,20+widgHeight*numwidgets,"comment");
		thecomments[numwidgets].message("set",item.label);
	
		thesliders[numwidgets] = patcher.newdefault(hBase+130,20+widgHeight*numwidgets,"toggle");  // Faust says always have default of zero--even for check buttons!  Ohhhh well...
			
		thenumberBoxes[numwidgets] = patcher.newobject("number",hBase+258,20+widgHeight*numwidgets,80,13);
		thenumberBoxes[numwidgets].message('min',0);
		thenumberBoxes[numwidgets].message('max',1);
		
		patcher.hiddenconnect(thesliders[numwidgets], 0, thenumberBoxes[numwidgets], 0);
			
		theMessages[numwidgets] = patcher.newobject("message",hBase+345,23+widgHeight*numwidgets,350,9);
		theMessages[numwidgets].message("set",item.address,"\$1");
		
		patcher.hiddenconnect(thenumberBoxes[numwidgets], 0, theMessages[numwidgets], 0);
		patcher.hiddenconnect(theMessages[numwidgets], 0, msgSink, 0);
		
		// direct connection to faustgen~ does not work...
		//patcher.hiddenconnect(thenumberBoxes[numwidgets], 0, msgSink, 0)
		
 	} else if (item.type === "nentry") {
	
        
    }
}

function anything()
{	
	var args = arrayfromargs(messagename, arguments);
	
    // Remove old
    while (numwidgets >= 0) {
        this.patcher.remove(thecomments[numwidgets]);
        this.patcher.remove(thesliders[numwidgets]);
        this.patcher.remove(theMessages[numwidgets]);
        this.patcher.remove(thenumberBoxes[numwidgets]);
        numwidgets--;
    }
        
    // Get and parse JSON description of the UI
    var json = args[1];
    parse_ui(JSON.parse(json).ui, this.patcher);
}


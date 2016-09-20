// -----------------
// ui.js
// -----------------
//
// Automatically (re)generate/destroy sliders according to Faust DSP module
// By Edgar Berdahl, July 2014
// Grame, 2014-2016
//
// Currently addHorizontalBargraph, addVerticalBargraph, declare,
// openTabBox, openHorizontalBox, openVerticalBox, and closeBox are not really handled.
//
// Started from autosurface.js by rld, 5.04
//

// Global table
var dsp_ui_table = [];

var faust = faust || {};

faust.ui = function (json, patcher) {
  
    // inlets and outlets
    var inlets = 1;
    var outlets = 2;

    // global variables and arrays
    var numwidgets = -1;  // The actual number if widgets is numwidgets+1
    var theValues = new Array(128);

    var widgHeight = 30;
    var hBase = 150;

    // Maxobj variables for scripting
    var theComments = new Array(128);
    var theSliders = new Array(128);
    var theMessages = new Array(128);
    var thenumberBoxes = new Array(128);
    var theFunnel;

    var inputs_items = new Array(128);
    var ouputs_items = new Array(128);
    
    starts_with = function(str, prefix)
    {
        return (str.lastIndexOf(prefix, 0) === 0);
    }
    
    get_dsp_name = function(patcher, name)
    {
        var obj = patcher.firstobject;
        while (obj) {
            if (starts_with(obj.varname, name)) {
                return obj;
            }
            obj = obj.nextobject;
        }
        return null;
    }

    // JSON parsing
    parse_ui = function(ui, target, patcher) 
    {
        var i;
        for (i = 0; i < ui.length; i++) {
            parse_group(ui[i], target, patcher);
        }
    }
        
    parse_group = function(group, target, patcher) 
    {
        if (group.items) {
            parse_items(group.items, target, patcher);
        }
    }

    parse_items = function(items, target, patcher) 
    {
        var i;
        for (i = 0; i < items.length; i++) {
            parse_item(items[i], target, patcher);
        }
    }

    parse_item = function(item, target, patcher)
    {
        if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
        
            parse_items(item.items, target, patcher);

        } else if (item.type === "hbargraph" || item.type === "vbargraph") {
        
            numwidgets++;
        
            theComments[numwidgets] = patcher.newdefault(hBase, 20 + widgHeight * numwidgets, "comment");
            theComments[numwidgets].message("set", "bargraph" + numwidgets);
        
            // TODO : create "meter" instead of "multiSlider" 
            
            theSliders[numwidgets] = patcher.newobject("user", "multiSlider", hBase + 130, 20 + widgHeight * numwidgets, 120, 20, 0., 1., 1, 2936, 15, 0, 0, 2, 0, 0, 0);
            theSliders[numwidgets].message('settype', 1);
            theSliders[numwidgets].message('contdata', 1);
            theSliders[numwidgets].message('setstyle', 0);
            theSliders[numwidgets].message('setminmax', parseFloat(item.min), parseFloat(item.max));
            theSliders[numwidgets].message(parseFloat(item.init));  // Set initial value
            
            // Bargraph ScriptingName is set with the complete parameter path, so that faustgen~ can directly address them
            theSliders[numwidgets].message('varname', item.address);
            
            thenumberBoxes[numwidgets] = patcher.newobject("flonum", hBase + 258, 20 + widgHeight * numwidgets, 80, 13);
            thenumberBoxes[numwidgets].message('min', parseFloat(item.min));
            thenumberBoxes[numwidgets].message('max', parseFloat(item.max));
                
            patcher.hiddenconnect(theSliders[numwidgets], 0, thenumberBoxes[numwidgets], 0);		
            patcher.hiddenconnect(theMessages[numwidgets], 0, target, 0);
                    
            // direct connection to faustgen~ does not work...
            //patcher.hiddenconnect(thenumberBoxes[numwidgets], 0, target, 0);
        
        } else if (item.type === "vslider" || item.type === "hslider" ) {
        
            numwidgets++;
        
            theComments[numwidgets] = patcher.newdefault(hBase, 20 + widgHeight * numwidgets, "comment");
            theComments[numwidgets].message("set", item.label);

            theSliders[numwidgets] = patcher.newobject("user", "multiSlider", hBase + 130, 20 + widgHeight * numwidgets, 120, 20, 0., 1., 1, 2936, 15, 0, 0, 2, 0, 0, 0);
            theSliders[numwidgets].message('settype', 1);
            theSliders[numwidgets].message('contdata', 1);
            theSliders[numwidgets].message('setstyle', 0);
            theSliders[numwidgets].message('setminmax', parseFloat(item.min), parseFloat(item.max));
            theSliders[numwidgets].message(parseFloat(item.init));  // Set initial value
            theSliders[numwidgets].message('varname', item.address);
                
            thenumberBoxes[numwidgets] = patcher.newobject("flonum", hBase + 258, 20 + widgHeight * numwidgets, 80, 13);
            thenumberBoxes[numwidgets].message('min', parseFloat(item.min));
            thenumberBoxes[numwidgets].message('max', parseFloat(item.max));
                
            patcher.hiddenconnect(theSliders[numwidgets], 0, thenumberBoxes[numwidgets], 0);
                
            theMessages[numwidgets] = patcher.newobject("message", hBase + 345, 23 + widgHeight * numwidgets, 350, 9);
            theMessages[numwidgets].message("set", item.address,"\$1");
            
            patcher.hiddenconnect(thenumberBoxes[numwidgets], 0, theMessages[numwidgets], 0);
            patcher.hiddenconnect(theMessages[numwidgets], 0, target, 0);
            
            // direct connection to faustgen~ does not work...
            //patcher.hiddenconnect(thenumberBoxes[numwidgets], 0, target, 0);

        } else if (item.type === "button" || item.type === "checkbox") {
            
            numwidgets++;
            theComments[numwidgets] = patcher.newdefault(hBase, 20 + widgHeight * numwidgets,"comment");
            theComments[numwidgets].message("set",item.label);
        
            theSliders[numwidgets] = patcher.newdefault(hBase + 130, 20 + widgHeight * numwidgets,"toggle");  // Faust says always have default of zero--even for check buttons!  Ohhhh well...
                
            thenumberBoxes[numwidgets] = patcher.newobject("number", hBase + 258, 20 + widgHeight * numwidgets, 80, 13);
            thenumberBoxes[numwidgets].message('min', 0);
            thenumberBoxes[numwidgets].message('max', 1);
            
            patcher.hiddenconnect(theSliders[numwidgets], 0, thenumberBoxes[numwidgets], 0);
                
            theMessages[numwidgets] = patcher.newobject("message", hBase + 345, 23 + widgHeight * numwidgets, 350, 9);
            theMessages[numwidgets].message("set",item.address,"\$1");
            
            patcher.hiddenconnect(thenumberBoxes[numwidgets], 0, theMessages[numwidgets], 0);
            patcher.hiddenconnect(theMessages[numwidgets], 0, target, 0);
            
            // direct connection to faustgen~ does not work...
            //patcher.hiddenconnect(thenumberBoxes[numwidgets], 0, target, 0)
            
        } else if (item.type === "nentry") {
        
            
        }
    }
    
    // Remove old
    while (numwidgets >= 0) {
        patcher.remove(theComments[numwidgets]);
        patcher.remove(theSliders[numwidgets]);
        patcher.remove(theMessages[numwidgets]);
        patcher.remove(thenumberBoxes[numwidgets]);
        numwidgets--;
    }
 
    // Create new
    var parsed_json = JSON.parse(json);
    var dsp_object = patcher.getnamed(parsed_json.name + "~");

    if (dsp_object === patcher.getnamed("null_object")) {
        post("Error : missing dsp name in the patch, add a 'declare name foo' line with the DSP filename in the DSP source code\n");
    }
    parse_ui(parsed_json.ui, dsp_object, patcher);
}

function anything()
{	
	var args = arrayfromargs(messagename, arguments);
    dsp_ui_table.push(faust.ui(args[1], this.patcher));
}


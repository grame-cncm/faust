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

// global variables and arrays
faust.numwidgets = -1;

// Maxobj variables for scripting
faust.theComments = new Array(128);
faust.theSliders = new Array(128);
faust.theMessages = new Array(128);
faust.thenumberBoxes = new Array(128);

faust.ui = function (json, patcher) {
 
    var widgHeight = 30;
    var hBase = 150;
  
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
        
            faust.numwidgets++;     
            faust.theComments[faust.numwidgets] = patcher.newdefault(hBase, 20 + widgHeight * faust.numwidgets, "comment");
            faust.theComments[faust.numwidgets].message("set", "bargraph" + faust.numwidgets);
        
            // TODO : create "meter" instead of "multiSlider" 
            
            faust.theSliders[faust.numwidgets] = patcher.newobject("user", "multiSlider", hBase + 130, 20 + widgHeight * faust.numwidgets, 120, 20, 0., 1., 1, 2936, 15, 0, 0, 2, 0, 0, 0);
            faust.theSliders[faust.numwidgets].message('settype', 1);
            faust.theSliders[faust.numwidgets].message('contdata', 1);
            faust.theSliders[faust.numwidgets].message('setstyle', 0);
            faust.theSliders[faust.numwidgets].message('setminmax', parseFloat(item.min), parseFloat(item.max));
            faust.theSliders[faust.numwidgets].message(parseFloat(item.init));  // Set initial value
            
            // Bargraph ScriptingName is set with the complete parameter path, so that faustgen~ can directly address them
            faust.theSliders[faust.numwidgets].message('varname', item.address);
            
            faust.thenumberBoxes[faust.numwidgets] = patcher.newobject("flonum", hBase + 258, 20 + widgHeight * faust.numwidgets, 80, 13);
            faust.thenumberBoxes[faust.numwidgets].message('min', parseFloat(item.min));
            faust.thenumberBoxes[faust.numwidgets].message('max', parseFloat(item.max));
                
            patcher.hiddenconnect(faust.theSliders[faust.numwidgets], 0, faust.thenumberBoxes[faust.numwidgets], 0);		
            patcher.hiddenconnect(faust.theMessages[faust.numwidgets], 0, target, 0);
                    
            // direct connection to faustgen~ does not work...
            //patcher.hiddenconnect(faust.thenumberBoxes[faust.numwidgets], 0, target, 0);
        
        } else if (item.type === "vslider" || item.type === "hslider" ) {
        
            faust.numwidgets++; 
            faust.theComments[faust.numwidgets] = patcher.newdefault(hBase, 20 + widgHeight * faust.numwidgets, "comment");
            faust.theComments[faust.numwidgets].message("set", item.label);

            faust.theSliders[faust.numwidgets] = patcher.newobject("user", "multiSlider", hBase + 130, 20 + widgHeight * faust.numwidgets, 120, 20, 0., 1., 1, 2936, 15, 0, 0, 2, 0, 0, 0);
            faust.theSliders[faust.numwidgets].message('settype', 1);
            faust.theSliders[faust.numwidgets].message('contdata', 1);
            faust.theSliders[faust.numwidgets].message('setstyle', 0);
            faust.theSliders[faust.numwidgets].message('setminmax', parseFloat(item.min), parseFloat(item.max));
            faust.theSliders[faust.numwidgets].message(parseFloat(item.init));  // Set initial value
            faust.theSliders[faust.numwidgets].message('varname', item.address);
                
            faust.thenumberBoxes[faust.numwidgets] = patcher.newobject("flonum", hBase + 258, 20 + widgHeight * faust.numwidgets, 80, 13);
            faust.thenumberBoxes[faust.numwidgets].message('min', parseFloat(item.min));
            faust.thenumberBoxes[faust.numwidgets].message('max', parseFloat(item.max));
            faust.thenumberBoxes[faust.numwidgets].message(parseFloat(item.init));
                
            patcher.hiddenconnect(faust.theSliders[faust.numwidgets], 0, faust.thenumberBoxes[faust.numwidgets], 0);
                
            faust.theMessages[faust.numwidgets] = patcher.newobject("message", hBase + 345, 23 + widgHeight * faust.numwidgets, 350, 9);
            faust.theMessages[faust.numwidgets].message("set", item.address,"\$1");
            
            patcher.hiddenconnect(faust.thenumberBoxes[faust.numwidgets], 0, faust.theMessages[faust.numwidgets], 0);
            patcher.hiddenconnect(faust.theMessages[faust.numwidgets], 0, target, 0);
            
            // direct connection to faustgen~ does not work...
            //patcher.hiddenconnect(faust.thenumberBoxes[faust.numwidgets], 0, target, 0);

        } else if (item.type === "button" || item.type === "checkbox") {
            
            faust.numwidgets++;
            faust.theComments[faust.numwidgets] = patcher.newdefault(hBase, 20 + widgHeight * faust.numwidgets,"comment");
            faust.theComments[faust.numwidgets].message("set",item.label);
        
            faust.theSliders[faust.numwidgets] = patcher.newdefault(hBase + 130, 20 + widgHeight * faust.numwidgets,"toggle");  // Faust says always have default of zero--even for check buttons!  Ohhhh well...
                
            faust.thenumberBoxes[faust.numwidgets] = patcher.newobject("number", hBase + 258, 20 + widgHeight * faust.numwidgets, 80, 13);
            faust.thenumberBoxes[faust.numwidgets].message('min', 0);
            faust.thenumberBoxes[faust.numwidgets].message('max', 1);
            
            patcher.hiddenconnect(faust.theSliders[faust.numwidgets], 0, faust.thenumberBoxes[faust.numwidgets], 0);
                
            faust.theMessages[faust.numwidgets] = patcher.newobject("message", hBase + 345, 23 + widgHeight * faust.numwidgets, 350, 9);
            faust.theMessages[faust.numwidgets].message("set",item.address,"\$1");
            
            patcher.hiddenconnect(faust.thenumberBoxes[faust.numwidgets], 0, faust.theMessages[faust.numwidgets], 0);
            patcher.hiddenconnect(faust.theMessages[faust.numwidgets], 0, target, 0);
            
            // direct connection to faustgen~ does not work...
            //patcher.hiddenconnect(faust.thenumberBoxes[faust.numwidgets], 0, target, 0)
            
        } else if (item.type === "nentry") {
			
            faust.numwidgets++;
            faust.theComments[faust.numwidgets] = patcher.newdefault(hBase, 20 + widgHeight * faust.numwidgets, "comment");
            faust.theComments[faust.numwidgets].message("set", item.label);

            if (parseFloat(item.step) == 1.0)  {
                //post("integer : nentry \n");
                faust.thenumberBoxes[faust.numwidgets] = patcher.newobject("number", hBase + 258, 20 + widgHeight * faust.numwidgets, 80, 13);
            } else {
                //post("float : nentry \n");
                faust.thenumberBoxes[faust.numwidgets] = patcher.newobject("flonum", hBase + 258, 20 + widgHeight * faust.numwidgets, 80, 13);
            }

            faust.thenumberBoxes[faust.numwidgets].message('min', parseFloat(item.min));
            faust.thenumberBoxes[faust.numwidgets].message('max', parseFloat(item.max));
            faust.thenumberBoxes[faust.numwidgets].message(parseFloat(item.init));
                
            faust.theMessages[faust.numwidgets] = patcher.newobject("message", hBase + 345, 23 + widgHeight * faust.numwidgets, 350, 9);
            faust.theMessages[faust.numwidgets].message("set", item.address,"\$1");

            patcher.hiddenconnect(faust.thenumberBoxes[faust.numwidgets], 0, faust.theMessages[faust.numwidgets], 0);
            patcher.hiddenconnect(faust.theMessages[faust.numwidgets], 0, target, 0); 

            // direct connection to faustgen~ does not work...
            //patcher.hiddenconnect(faust.thenumberBoxes[faust.numwidgets], 0, target, 0);       
        }
    }
    
    // Remove old
    while (faust.numwidgets >= 0) {
        patcher.remove(faust.theComments[faust.numwidgets]);
        patcher.remove(faust.theSliders[faust.numwidgets]);
        patcher.remove(faust.theMessages[faust.numwidgets]);
        patcher.remove(faust.thenumberBoxes[faust.numwidgets]);
        faust.numwidgets--;
    }
 
    // Create new
    var parsed_json = JSON.parse(json);
    
    // Tries to find the compiled object from the "name" field in the JSON
    var dsp_object1 = patcher.getnamed(parsed_json.name + "~");
    if (dsp_object1 !== patcher.getnamed("null_object")) {
        parse_ui(parsed_json.ui, dsp_object1, patcher);
    } else {
        // Tries to find the compiled object from the "filename" field in the JSON
        var dsp_object2 = patcher.getnamed(parsed_json.filename.slice(0,-4) + "~");
        if (dsp_object2 !== patcher.getnamed("null_object")) {
            parse_ui(parsed_json.ui, dsp_object2, patcher);
        } else {
            // Tries to find the compiled object from the "name" argument (used with faustgen~)
            var dsp_object = get_dsp_name(patcher, "faustgen");
            if (dsp_object !== patcher.getnamed("null_object")) {
                parse_ui(parsed_json.ui, dsp_object, patcher);
            } else {
                post("Error : missing dsp name in the patch\n");
            }
        }
    }
}

function anything()
{	
    var args = arrayfromargs(messagename, arguments);
    dsp_ui_table.push(faust.ui(args[1], this.patcher));
}


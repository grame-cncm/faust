/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

//-----------------------------------------------------------------------------
// a function to build a slider
// a Faust slider is a composite object that embeds a label, a 'range' input
// and a 'text' input displaying the slider value
// slider and text value are linked together to reflect the same value.
//-----------------------------------------------------------------------------
function makeslider(id, orientation, handler, min, max, value, step) {
    var slider = document.createElement('input');
    slider.id = id;
    slider.type = "range";
    slider.min = min;
    slider.max = max;
    slider.value = value;
    slider.step = step;

    var valId = "v" + id;
    var textval = document.createElement('input');
    textval.id = valId;
    textval.type = "text";
    textval.value = value;
    textval.size = 6;

    textval.onchange = function () { $("#" + id).val(this.value); handler(this.value); };
    slider.onchange = function () { $("#" + valId).val(this.value); handler(this.value); };
    slider.fTextValue = textval;
    return slider;
}

function makenumentry(id, handler, min, max, value, step) {
    var valId = "n" + id;
    var textval = document.createElement('input');
    textval.id = valId;
    textval.type = "text";
    textval.value = value;
    textval.size = 6;

    textval.onchange = function () { $("#" + id).val(this.value); handler(this.value); };
    return textval;
}

//-----------------------------------------------------------------------------
// a push button
//-----------------------------------------------------------------------------
function makebutton(label, id, handler) {
    var button = document.createElement('button');
    button.id = id;
    button.type = "button";
    button.innerHTML = label;
    button.value = 1;
    button.onmousedown = function () { handler(1); };
    button.onmouseup = function () { handler(0); };
    return button;
}

//-----------------------------------------------------------------------------
// a check box
//-----------------------------------------------------------------------------
function makecheckbox(label, id, handler) {
    var cbox = document.createElement('input');
    cbox.id = id;
    cbox.type = "checkbox";
    cbox.value = 0;
    cbox.onchange = function () { this.value = (this.value == 1) ? 0 : 1; handler(this.value); };
    return cbox;
}

function makeCol(elt, classname) {
    var col = document.createElement('td');
    if (typeof elt == 'object') {
        col.appendChild(elt);
        elt.className = classname;
    } else {
        col.innerHTML = elt;
    }
    if (typeof classname != 'undefined') {
        col.className = classname;
    }
    return col;
}

//-----------------------------------------------------------------------------
// base UI builder
//-----------------------------------------------------------------------------

function DefaultJUI(div) {

    this.openTabBox = function (label) {
        console.log("openTabBox: " + label);
    }

    this.openHorizontalBox = function (label) {
        console.log("openHorizontalBox: " + label);
    }

    this.openVerticalBox = function (label) {
        console.log("openVerticalBox: " + label);
    }

    this.closeBox = function () {
        console.log("closeBox");
    }

    this.addButton = function (label, handler) {
        console.log("addButton: " + label);
    }

    this.addCheckButton = function (label, handler) {
        console.log("addCheckButton: " + label);
    }

    this.addVerticalSlider = function (label, handler, init, min, max, step) {
        console.log("addVerticalSlider: " + label);
    }

    this.addHorizontalSlider = function (label, handler, init, min, max, step) {
        console.log("addHorizontalSlider: " + label);
    }

    this.addNumEntry = function (label, handler, init, min, max, step) {
        console.log("addNumEntry: " + label);
    }

    this.addHorizontalBargraph = function (label, handler, min, max) {
        console.log("addHorizontalBargraph: " + label);
    }

    this.addVerticalBargraph = function (label, handler, min, max) {
        console.log("addVerticalBargraph: " + label);
    }

    this.declare = function (handler, key, value) {
        console.log("declare");
    }
}

function DefaultMeta(div) {

    this.declare = function (key, value) {
        iconsole.log("declare");
    }
}

//-----------------------------------------------------------------------------
// jQuery UI builder
//-----------------------------------------------------------------------------

function JUI(div) {

    this.table = document.createElement('table');
    this.table.className = "ui";
    this.table.appendChild(document.createElement('tr'));
    div.appendChild(this.table);
    this.counter = 0;

    this.openTabBox = function (label) {
        var row = document.createElement('tr');
        row.appendChild(document.createElement('td'));
        row.appendChild(document.createTextNode(label));
        this.table.appendChild(row);
    }

    this.openHorizontalBox = function (label) {
        var row = document.createElement('tr');
        row.appendChild(document.createElement('td'));
        row.appendChild(document.createTextNode(label));
        this.table.appendChild(row);
    }

    this.openVerticalBox = function (label) {
        var row = document.createElement('tr');
        row.appendChild(document.createElement('td'));
        row.appendChild(document.createTextNode(label));
        this.table.appendChild(row);
    }

    this.closeBox = function () { }

    this.addButton = function (label, handler) {
        var row = document.createElement('tr');
        row.appendChild(document.createElement('td'));
        row.appendChild(makebutton(label, "button" + this.counter++, handler));
        row.appendChild(document.createElement('td'));
        this.table.appendChild(row);
    }

    this.addCheckButton = function (label, handler) {
        var row = document.createElement('tr');
        row.appendChild(document.createElement('td'));
        row.appendChild(makeCol(label, "label"));
        row.appendChild(makecheckbox(label, "button" + this.counter++, handler));
        row.appendChild(document.createElement('td'));
        this.table.appendChild(row);
    }

    this.addVerticalSlider = function (label, handler, init, min, max, step) {
        var row = document.createElement('tr');
        var slider = makeslider("slider" + this.counter++, 'vertical', handler, min, max, init, step);
        row.appendChild(makeCol(label, "label"));
        row.appendChild(makeCol(slider), "control");
        row.appendChild(makeCol(slider.fTextValue), "value");
        this.table.appendChild(row);
    }

    this.addHorizontalSlider = function (label, handler, init, min, max, step) {
        var row = document.createElement('tr');
        var slider = makeslider("slider" + this.counter++, 'horizontal', handler, min, max, init, step);
        row.appendChild(makeCol(label, "label"));
        row.appendChild(makeCol(slider), "control");
        row.appendChild(makeCol(slider.fTextValue), "value");
        this.table.appendChild(row);
    }

    this.addNumEntry = function (label, handler, init, min, max, step) {
        var row = document.createElement('tr');
        row.appendChild(makeCol(label, "label"));
        row.appendChild(document.createElement('td'));
        row.appendChild(makenumentry("numentry" + this.counter++, handler, min, max, init, step));
        row.appendChild(document.createElement('td'));
        this.table.appendChild(row);
    }

    this.addHorizontalBargraph = function (label, handler, min, max) { }
    this.addVerticalBargraph = function (label, handler, min, max) { }
    this.declare = function (handler, key, value) { }
}

function Meta(div) {

    this.table = document.createElement('table');
    this.table.className = "ui";
    this.table.appendChild(document.createElement('tr'));
    div.appendChild(this.table);

    this.declare = function (key, value) {
        if (key == "name"
            || key == "version"
            || key == "copyright"
            || key == "author") {
            var row = document.createElement('tr');
            row.appendChild(document.createTextNode(key));
            row.appendChild(document.createElement('td'));
            row.appendChild(document.createTextNode(value));
            this.table.appendChild(row);
        }
    }
}

function FMI() {

    this.list = function ()  // ===>  "/karplus/volume",   "/karplus/pitch"
    { }

    this.set = function (param, value) { }
    this.get = function (param) { }
}
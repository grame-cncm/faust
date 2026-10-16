/*
 * Controller for the opt-in polyphonic Max bargraph runtime test.
 *
 * It starts audio, triggers the first MIDI voice, then observes the control
 * outlet. The Faust DSP emits a bargraph value above 20 only while that voice
 * is active. A proxy UI zone would instead keep reporting its reset value 0.
 */

inlets = 1;
outlets = 3;

var resultPath = jsarguments[1];
var watchdogTask = null;
var resultTask = null;
var highest = 0.0;
var finished = false;

function loadbang()
{
    watchdogTask = new Task(timeout, this);
    watchdogTask.schedule(12000);
    outlet(1, 1);
    var noteTask = new Task(playNote, this);
    noteTask.schedule(800);
}

function playNote()
{
    outlet(0, "midievent", 144, 60, 127);
    resultTask = new Task(finish, this);
    resultTask.schedule(1000);
}

function list()
{
    if (arguments.length === 4 && typeof arguments[1] === "number") {
        highest = Math.max(highest, arguments[1]);
    }
}

function finish()
{
    writeResult(highest > 20.0, highest, "");
    outlet(0, "midievent", 128, 60, 0);
    closePatch();
}

function timeout()
{
    writeResult(false, highest, "Max bargraph runtime test timed out");
    closePatch();
}

function writeResult(passed, current, error)
{
    if (finished) {
        return;
    }
    finished = true;
    if (watchdogTask !== null) {
        watchdogTask.cancel();
    }

    var file = new File(resultPath, "write", "TEXT");
    if (!file.isopen) {
        post("faust2max6 bargraph runtime test cannot open " + resultPath + "\n");
        return;
    }
    file.eof = 0;
    file.writestring(
        "{\"passed\":" + (passed ? "true" : "false") +
        ",\"current\":" + current +
        ",\"error\":\"" + error + "\"}"
    );
    file.close();
}

function closePatch()
{
    outlet(1, 0);
    outlet(2, "dispose");
}

<<includeIntrinsic>>

<<includeclass>>

import std.stdio;
import std.conv;
import core.stdc.stdio : snprintf;
import core.stdc.stdlib;

class Meta {
nothrow:
@nogc:
    void declare(string name, string value) {}
}

class UI {
nothrow:
@nogc:
    void declare(string id, string key, string value) {}
    void declare(int id, string key, string value) {}
    void declare(FAUSTFLOAT* id, string key, string value) {}

    // -- layout groups

    void openTabBox(string label) {}
    void openHorizontalBox(string label) {}
    void openVerticalBox(string label) {}
    void closeBox() {}

    // -- active widgets

    void addButton(string label, FAUSTFLOAT* val) {}
    void addCheckButton(string label, FAUSTFLOAT* val) {}
    void addVerticalSlider(string label, FAUSTFLOAT* val, float init, float min, float max, float step) {}
    void addHorizontalSlider(string label, FAUSTFLOAT* val, float init, float min, float max, float step) {}
    void addNumEntry(string label, FAUSTFLOAT* val, float init, float min, float max, float step) {}

    // -- passive display widgets

    void addHorizontalBargraph(string label, FAUSTFLOAT* val, float min, float max) {}
    void addVerticalBargraph(string label, FAUSTFLOAT* val, float min, float max) {}

}

class UIButton : UI
{
    this(FAUSTFLOAT state)
    {
        _state = state;
    }
    override void addButton(string label, FAUSTFLOAT* val) {
        *val = _state;
    }

private:
    FAUSTFLOAT _state;
}

class dsp {
nothrow:
@nogc:
public:
    int fSamplingFreq;
}

void printHeader(ref string file, mydsp dspObj, int numFrames)
{
    
    file ~= "number_of_inputs  :   " ~ to!string(dspObj.getNumInputs()) ~ "\n";
    file ~= "number_of_outputs :   " ~ to!string(dspObj.getNumOutputs()) ~ "\n";
    file ~= "number_of_frames  :  " ~ to!string(numFrames) ~ "\n";
}

void printSampleOutput(ref string file, int n, float value)
{
    ushort lineLength = value >= 0 ? 19 : 20;
    char[] line = new char[lineLength];
    snprintf(line.ptr, lineLength, "%6i :  %1.6f".ptr, n, value);

    foreach(c; line)
    {
        if(c != '\0')
            file ~= c;
    }
    file ~= '\n';
    // writeln(line);
}

void main(string[] args)
{
    if(args.length < 2)
    {
        writeln("Error: no argument provided for IR file path");
        return;
    }

    string irFilePath = args[1];
    string fileText = "";
    File irFile = File(irFilePath, "w+");
    scope(exit) 
    { 
        irFile.write(fileText); 
        irFile.close();
    }

    string debugFilePath = "/home/reker/.test/test.ir";
    File debugFile = File(debugFilePath, "w+");
    scope(exit) 
    { 
        debugFile.write(fileText); 
        debugFile.close();
    }

    immutable int sampleRate = 44_100;
    immutable int numFrames = 60_000;
    immutable int blockSize = numFrames / 4;

    mydsp dspObj = new mydsp();
    dspObj.init(sampleRate);

    printHeader(fileText, dspObj, numFrames);
    runDSP(fileText, dspObj, numFrames / 4, sampleRate, blockSize);
}

void runDSP(ref string file, mydsp dspObj, int numFrames, int sampleRate, int blockSize)
{
    long bufferSize = long.max;

    int numInputs = dspObj.getNumInputs();
    int numOutputs = dspObj.getNumOutputs();
    double*[] inputBuffers;
    double*[] outputBuffers;

    foreach(chan; 0..numInputs)
    {
        double* buffer = cast(double*)malloc(double.sizeof * numFrames);
        for(int n = 0; n < numFrames; ++n)
        {
            buffer[n] = 0;
        }
        inputBuffers ~= buffer;
    }

    foreach(chan; 0..numOutputs)
    {
        double* buffer = cast(double*)malloc(double.sizeof * numFrames);
        for(int n = 0; n < numFrames; ++n)
        {
            buffer[n] =  0.0f;
        }
        outputBuffers ~= buffer;
    }

    int cycle = 0;
    int numFramesWritten = 0;
    while(numFramesWritten < numFrames)
    {
        bufferSize = numFrames - numFramesWritten;
        foreach(chan; 0..numInputs)
        {
            foreach(j; 0..bufferSize)
            {
                inputBuffers[chan][j] = (numFramesWritten == 0 && j == 0) ? 1.0f : 0.0f;
            }
        }

        if (cycle == 0)
        {
            UIButton buttonOn = new UIButton(1.0f);
            dspObj.buildUserInterface(cast(UI*)&buttonOn);
        }
        else
        {
            UIButton buttonOff = new UIButton(0.0f);
            dspObj.buildUserInterface(cast(UI*)&buttonOff);
        }

        dspObj.compute(cast(int)bufferSize, inputBuffers, outputBuffers);

        foreach(chan; 0..numOutputs)
        {
            for(int index = 0; index < bufferSize; ++index)
            {
                double sample = outputBuffers[chan][index];
                printSampleOutput(file, cast(int)index, sample);
                numFramesWritten++;
            }
        }

        cycle++;
    }


    // scope(exit)
    // {
    //     foreach(chan; 0..numOutputs)
    //     {
    //         for(int index = 0; index < numFrames; ++index)
    //         {
    //             double sample = outputBuffers[chan][index];
    //             printSampleOutput(file, cast(int)index, sample);
    //         }
    //     }
    // }

    // dspObj.compute(numFrames, inputBuffers, outputBuffers);
}
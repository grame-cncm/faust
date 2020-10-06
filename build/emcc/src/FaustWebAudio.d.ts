/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

declare namespace Faust {

    interface OutputParamHandler { (path: string, value: number): void }
    interface MetadataHandler { (key: string, value: number): void }

    // Implementation types
    interface MonoDSP {

        setOutputParamHandler(handler: OutputParamHandler): void;
        getOutputParamHandler(): OutputParamHandler;

        getNumInputs(): number;
        getNumOutputs(): number;

        compute(inputs: Float32Array[], outputs: Float32Array[]): boolean;

        midiMessage(data: number[] | Uint8Array): void;

        ctrlChange(chan: number, ctrl: number, value: number): void;
        pitchWheel(chan: number, value: number): void;

        setParamValue(path: string, value: number): void;
        getParamValue(path: string): number;

        getParams(): string[];
        getJSON(): string;

        destroy(): void;
    }

    interface PolyDSP extends MonoDSP {
    }

    // Public API
    /*
    interface FaustAudioNode {

        setOutputParamHandler(handler: OutputParamHandler): void;
        getOutputParamHandler(): OutputParamHandler;
        metadata(handler: MetadataHandler): void;
        ctrlChange(chan: number, ctrl: number, value: number): void;
        pitchWheel(chan: number, value: number): void;
        setParamValue(path: string, value: number): void;
        getParamValue(path: string): number;
        getParams(): string[];
        getJSON(): string;
        destroy(): void; // to do: check is this function is still really needed
    }

    interface FaustAudioPolyNode extends FaustAudioNode {
        keyOn(pitch: number, velocity: number): void;
        keyOff(pitch: number, velocity: number): void;
        allNotesOff(): void;

        //midiMessage(data: number[] | Uint8Array): void;
    }
    */

    interface FaustScriptProcessorNode extends ScriptProcessorNode, MonoDSP {

        setOutputParamHandler(handler: OutputParamHandler): void;
        getOutputParamHandler(): OutputParamHandler;
        metadata(handler: MetadataHandler): void;
        ctrlChange(chan: number, ctrl: number, value: number): void;
        pitchWheel(chan: number, value: number): void;
        setParamValue(path: string, value: number): void;
        getParamValue(path: string): number;
        getParams(): string[];
        getJSON(): string;
        destroy(): void; // TODO: check is this function is still really needed
    }

    interface FaustAudioWorkletNode extends AudioWorkletNode, MonoDSP {

        setOutputParamHandler(handler: OutputParamHandler): void;
        getOutputParamHandler(): OutputParamHandler;
        metadata(handler: MetadataHandler): void;
        ctrlChange(chan: number, ctrl: number, value: number): void;
        pitchWheel(chan: number, value: number): void;
        setParamValue(path: string, value: number): void;
        getParamValue(path: string): number;
        getParams(): string[];
        getJSON(): string;
        destroy(): void; // TODO: check is this function is still really needed
    }

    //interface FaustAudioNode extends FaustScriptProcessorNode, FaustAudioWorkletNode { }
    interface AudioNodeFactory {
        compileMonoNode(context: BaseAudioContext, name: string, faust: LibFaust, dsp_content: string, args: string, scriptprocessor: boolean)
            : Promise<FaustScriptProcessorNode | FaustAudioWorkletNode>;

        // We assume that 'dsp_content' contains an integrated effect
        compilePolyNode(context: BaseAudioContext, name: string, faust: LibFaust, dsp_content: string, args: string, voices: number, scriptprocessor: boolean)
            : Promise<FaustScriptProcessorNode | FaustAudioWorkletNode>;

        // Separated 'voice' and 'effect' DSP
        compilePolyNode2(context: BaseAudioContext, name: string, faust: LibFaust, voice_dsp: string, effect_dsp: string, args: string, voices: number, scriptprocessor: boolean)
            : Promise<FaustScriptProcessorNode | FaustAudioWorkletNode>;

        createMonoNode(context: BaseAudioContext, name: string, module: Faust.Factory, scriptprocessor: boolean, bufferSize?: number)
            : Promise<FaustScriptProcessorNode | FaustAudioWorkletNode>;

        // We assume that 'dsp_content' contains an integrated effect
        createPolyNode(context: BaseAudioContext, name: string, module: Faust.Factory, voices: number, scriptprocessor: boolean, bufferSize?: number)
            : Promise<FaustScriptProcessorNode | FaustAudioWorkletNode>;

        // Separated 'voice' and 'effect' modules
        createPolyNode2(context: BaseAudioContext, name: string, voice_module: Faust.Factory, effect_module: Faust.Factory, voices: number, scriptprocessor: boolean, bufferSize?: number)
            : Promise<FaustScriptProcessorNode | FaustAudioWorkletNode>;
    }

}

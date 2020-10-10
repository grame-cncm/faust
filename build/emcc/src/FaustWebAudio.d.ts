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
    interface UIHandler { (item: TFaustUIItem): void }

    // Implementation types
    interface BaseDSP {

        setOutputParamHandler(handler: OutputParamHandler): void;
        getOutputParamHandler(): OutputParamHandler;

        getNumInputs(): number;
        getNumOutputs(): number;

        compute(inputs: Float32Array[], outputs: Float32Array[]): boolean;
        metadata(handler: MetadataHandler): void;

        midiMessage(data: number[] | Uint8Array): void;

        ctrlChange(chan: number, ctrl: number, value: number): void;
        pitchWheel(chan: number, value: number): void;

        setParamValue(path: string, value: number): void;
        getParamValue(path: string): number;

        getParams(): string[];
        getJSON(): string;
        getUI(): TFaustUI;

        destroy(): void;
    }

    interface MonoDSP extends BaseDSP { }

    interface PolyDSP extends MonoDSP {

        keyOn(channel: number, pitch: number, velocity: number): void;
        keyOff(channel: number, pitch: number, velocity: number): void;
        allNotesOff(): void;
    }

    // Public API

    // Monophonic nodes
    interface FaustScriptProcessorNode extends ScriptProcessorNode, MonoDSP { }
    interface FaustAudioWorkletNode extends AudioWorkletNode, MonoDSP { }

    // Polyphonic nodes
    interface FaustPolyScriptProcessorNode extends ScriptProcessorNode, PolyDSP { }
    interface FaustPolyAudioWorkletNode extends AudioWorkletNode, PolyDSP { }

    interface AudioNodeFactory {
        compileMonoNode(context: BaseAudioContext, name: string, compiler: Compiler, dsp_code: string, args: string, sp: boolean)
            : Promise<FaustScriptProcessorNode | FaustAudioWorkletNode>;

        createMonoNode(context: BaseAudioContext, name: string, factory: Faust.Factory, sp: boolean, buffer_size?: number)
            : Promise<FaustScriptProcessorNode | FaustAudioWorkletNode>;

        // We assume that 'dsp_code' contains an integrated effect
        compilePolyNode(context: BaseAudioContext, name: string, compiler: Compiler, dsp_code: string, args: string, voices: number, sp: boolean)
            : Promise<FaustPolyScriptProcessorNode | FaustPolyAudioWorkletNode>;

        createPolyNode(context: BaseAudioContext, name: string, voice_factory: Faust.Factory, mixer_module: WebAssembly.Module, voices: number, sp: boolean, buffer_size?: number, effect_factory?: Factory)
            : Promise<FaustPolyScriptProcessorNode | FaustPolyAudioWorkletNode>;

        // Separated 'voice' and 'effect' DSP
        // compilePolyNode2(context: BaseAudioContext, name: string, faust: LibFaust, voice_dsp: string, effect_dsp: string, args: string, voices: number, sp: boolean)
        //     : Promise<FaustPolyScriptProcessorNode | FaustPolyAudioWorkletNode>;

        // // Separated 'voice' and 'effect' factories
        // createPolyNode2(context: BaseAudioContext, name: string, voice_factory: Faust.Factory, effect_factory: Faust.Factory, voices: number, sp: boolean, buffer_size?: number)
        //     : Promise<FaustPolyScriptProcessorNode | FaustPolyAudioWorkletNode>;
    }

}

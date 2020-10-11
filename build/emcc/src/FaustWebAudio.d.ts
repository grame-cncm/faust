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

    // Public API
    interface OutputParamHandler { (path: string, value: number): void }
    interface MetadataHandler { (key: string, value: number): void }

    /**
     * DSP implementation: mimic the C++ 'dsp' class, 
     * - adding MIDI control: metadata are decoded and incoming MIDI messages will control the assocated controllers
     * - an output handler can be set to treat produced output controllers (like 'bargraphs') 
     * - regular controllers are handled using setParamValue/getParamValue
     */
    interface BaseDSP {

        /**
         * Set the parameter output handler, to  be called in the 'compute' method with output parameters (like bargraph).
         *
         * @param {OutputParamHandler} handler - the output handler
         */
        setOutputParamHandler(handler: OutputParamHandler): void;

        /**
         * Get the parameter output handler.
         *
         * @return {OutputParamHandler} the current output handler
         */
        getOutputParamHandler(): OutputParamHandler;

        /**
         * Return instance number of audio inputs.
         *
         * @return {number} the instance number of audio inputs
         */
        getNumInputs(): number;

        /**
         * Return instance number of audio outputs.
         *
         * @return {number} the instance number of audio outputs
         */
        getNumOutputs(): number;

        /**
         * DSP instance computation, to be called with successive in/out audio buffers, using their size.
         *
         * @param {Float32Array[]} inputs - the input audio buffers
         * @param {Float32Array[]} outputs - the output audio buffers
         */
        compute(inputs: Float32Array[], outputs: Float32Array[]): boolean;

        metadata(handler: MetadataHandler): void;

        /**
         * Handle untyped MIDI messages.
         *
         * @param {number[] | Uint8Array} data - and arry of MIDI bytes
         */
        midiMessage(data: number[] | Uint8Array): void;

        /**
         * Handle MIDI ctrlChange messages.
         *
         * @param {number} channel - the MIDI channel (0..15, not used for now)
         * @param {number} ctrl - the MIDI controller number (0..127)
         * @param {number} value - the MIDI controller value (0..127)
         */
        ctrlChange(chan: number, ctrl: number, value: number): void;

        /**
         * Handle MIDI pitchWheel messages.
         *
         * @param {number} channel - the MIDI channel (0..15, not used for now)
         * @param {number} value - the MIDI controller value (0..16383)
         */
        pitchWheel(chan: number, value: number): void;

        /**
         * Set parameter value.
         *
         * @param {string} path - the path to the wanted parameter (retrieved using 'getParams' method)
         * @param {number} val - the float value for the wanted control
         */
        setParamValue(path: string, value: number): void;

        /**
         * Get parameter value.
         *
         * @param {string} path - the path to the wanted parameter (retrieved using 'getParams' method)
         *
         * @return {number} the float value
         */
        getParamValue(path: string): number;

        /**
         * Get the table of all controller paths.
         *
         * @return {string[]} the table of all input parameters paths
         */
        getParams(): string[];

        /**
         * Get DSP JSON description with its UI and metadata.
         *
         * @return {string} DSP JSON description
         */
        getJSON(): string;

        /**
         * Get DSP UI description.
         *
         * @return {TFaustUI} the DSP UI description
         */
        getUI(): TFaustUI;

        /**
         * Destroy the DSP.
         *
         */
        destroy(): void;
    }

    /**
     * Monophonic DSP implementation.
     */
    // See https://www.typescriptlang.org/docs/handbook/interfaces.html
    interface MonoDSPConstructor {

        /**
         * The MonoDSP constructor.
         * 
         * @param {Instance} instance - an instance created with 'createSyncMonoDSPInstance' or 'createAsyncMonoDSPInstance'
         * @param {number} sample_rate - the sample rate in Hz
         * @param {number} buffer_size - the buffer size in frames
         * @return the created MonoDSP object 
         */
        new(instance: Faust.Instance, sample_rate: number, buffer_size: number): MonoDSP;
    }

    interface MonoDSP extends BaseDSP { }

    /**
     * Polyphonic DSP implementation.
     */
    // See https://www.typescriptlang.org/docs/handbook/interfaces.html
    interface PolyDSPConstructor {

        /**
         * The PolyDSP constructor.
         * 
         * @param {Instance} instance - an instance created with 'createSyncPolyDSPInstance' or 'createAsyncPolyDSPInstance'
         * @param {number} sample_rate - the sample rate in Hz
         * @param {number} buffer_size - the buffer size in frames
         * @return the created MonoDSP object 
         */
        new(instance: Faust.PolyInstance, sample_rate: number, buffer_size: number): PolyDSP;
    }

    interface PolyDSP extends BaseDSP {

        /**
         * Handle MIDI keyOn messages.
         *
         * @param {number} channel - the MIDI channel (0..15, not used for now)
         * @param {number} pitch - the MIDI pitch value (0..127)
         * @param {number} velocity - the MIDI velocity value (0..127)
         */
        keyOn(channel: number, pitch: number, velocity: number): void;

        /**
         * Handle MIDI keyOff messages.
         *
         * @param {number} channel - the MIDI channel (0..15, not used for now)
         * @param {number} pitch - the MIDI pitch value (0..127)
         * @param {number} velocity - the MIDI velocity value (0..127)
         */
        keyOff(channel: number, pitch: number, velocity: number): void;

        /**
         * Stop all playing notes.
         *
         * @param {boolean} hard - whether to immediately stop notes or put them in release mode
         */
        allNotesOff(hard: boolean): void;
    }

    /**
     * Monophonic ScriptProcessorNode.
     */
    interface FaustMonoScriptProcessorNode extends ScriptProcessorNode, MonoDSP { }

    /**
     * Monophonic AudioWorkletNode.
     */
    interface FaustMonoAudioWorkletNode extends AudioWorkletNode, MonoDSP { }

    /**
     * Polyphonic ScriptProcessorNode.
     */
    interface FaustPolyScriptProcessorNode extends ScriptProcessorNode, PolyDSP { }

    /**
     * Polyphonic AudioWorkletNode.
     */
    interface FaustPolyAudioWorkletNode extends AudioWorkletNode, PolyDSP { }

    /**
     * Monophonic/Polyphonic ScriptProcessorNode and AudioWorkletNode nodes creation.
     */
    interface AudioNodeFactory {

        /**
         * Compile a monophonic WebAudio node (either ScriptProcessorNode or AudioWorkletNode)
         *
         * @param {BaseAudioContext} context the WebAudio context
         * @param {string} name - the DSP name
         * @param {Compiler} compiler - the Faust compiler
         * @param {string} dsp_code - the DSP code
         * @param {string} args - the compilation parameters
         * @param {boolean} sp - whether to compile a ScriptProcessorNode or an AudioWorkletNode
         * @param {number} buffer_size - the buffer size in frames to be used, in ScriptProcessorNode only, since AudioWorkletNode always uses 128 frames
         * @preturn {Promise<FaustMonoScriptProcessorNode | FaustMonoAudioWorkletNode>} the compiled WebAudio node or 'null' if failure
         */
        compileMonoNode(context: BaseAudioContext, name: string, compiler: Compiler, dsp_code: string, args: string, sp: boolean, buffer_size?: number)
            : Promise<FaustMonoScriptProcessorNode | FaustMonoAudioWorkletNode>;

        /**
         * Create a monophonic WebAudio node (either ScriptProcessorNode or AudioWorkletNode)
         *
         * @param {BaseAudioContext} context the WebAudio context
         * @param {string} name - the DSP name
         * @param {Factory} factory - the Faust factory, either obtained with a compiler (Faust.createDSPFactory) or loaded from files (Faust.loadDSPFactory)
         * @param {boolean} sp - whether to compile a ScriptProcessorNode or an AudioWorkletNode
         * @param {number} buffer_size - the buffer size in frames to be used in ScriptProcessorNode only, since AudioWorkletNode always uses 128 frames
         * @preturn {Promise<FaustMonoScriptProcessorNode | FaustMonoAudioWorkletNode>} the compiled WebAudio node or 'null' if failure
        */
        createMonoNode(context: BaseAudioContext, name: string, factory: Faust.Factory, sp: boolean, buffer_size?: number)
            : Promise<FaustMonoScriptProcessorNode | FaustMonoAudioWorkletNode>;

        /**
         * Compile a polyphonic WebAudio node (either ScriptProcessorNode or AudioWorkletNode)
         *
         * @param {BaseAudioContext} context the WebAudio context
         * @param {string} name - the DSP name
         * @param {Compiler} compiler - the Faust compiler
         * @param {string} dsp_code - the DSP code (we assume that 'dsp_code' contains an integrated effect)
         * @param {string} args - the compilation parameters
         * @param {number} voices - the number of voices
         * @param {boolean} sp - whether to compile a ScriptProcessorNode or an AudioWorkletNode
         * @param {number} buffer_size - the buffer size in frames to be used, in ScriptProcessorNode only, since AudioWorkletNode always uses 128 frames
         * @preturn {Promise<FaustPolyScriptProcessorNode | FaustPolyAudioWorkletNode>} the compiled WebAudio node or 'null' if failure
         */
        compilePolyNode(context: BaseAudioContext, name: string, compiler: Compiler, dsp_code: string, args: string, voices: number, sp: boolean, buffer_size?: number)
            : Promise<FaustPolyScriptProcessorNode | FaustPolyAudioWorkletNode>;

        /**
         * Create a polyphonic WebAudio node (either ScriptProcessorNode or AudioWorkletNode)
         *
         * @param {BaseAudioContext} context the WebAudio context
         * @param {string} name - the DSP name
         * @param {Factory} voice_factory - the Faust factory for voices, either obtained with a compiler (Faust.createDSPFactory) or loaded from files (Faust.loadDSPFactory)
         * @param {WebAssembly.Module} mixer_module - the wasm Mixer module (loaded from 'mixer32.wasm' file)
         * @param {number} voices - the number of voices
         * @param {boolean} sp - whether to compile a ScriptProcessorNode or an AudioWorkletNode
         * @param {number} buffer_size - the buffer size in frames to be used in ScriptProcessorNode only, since AudioWorkletNode always uses 128 frames
         * @param {Factory} effect_factory - the Faust factory for the effect, either obtained with a compiler (Faust.createDSPFactory) or loaded from files (Faust.loadDSPFactory)
         * @preturn {Promise<FaustPolyScriptProcessorNode | FaustPolyAudioWorkletNode>} the compiled WebAudio node or 'null' if failure
         */
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

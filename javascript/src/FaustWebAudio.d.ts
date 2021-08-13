
///<reference path="FaustGenerator.d.ts"/>

declare namespace Faust {

    // Public API
    interface OutputParamHandler { (path: string, value: number): void }
    interface ComputeHandler { (buffer_size: number): void }
    interface PlotHandler { (plotted: Float32Array[], index: number, events?: { type: string; data: any }[]): void }
    interface MetadataHandler { (key: string, value: string): void }

    // Implementation API
    interface UIHandler { (item: TFaustUIItem): void }

    /**
     * DSP implementation: mimic the C++ 'dsp' class:
     * - adding MIDI control: metadata are decoded and incoming MIDI messages will control the associated controllers
     * - an output handler can be set to treat produced output controllers (like 'bargraph') 
     * - regular controllers are handled using setParamValue/getParamValue
     */
    interface BaseDSP {

        /**
         * Set the parameter output handler, to  be called in the 'compute' method with output parameters (like bargraph).
         *
         * @param {OutputParamHandler} handler - the output handler
         */
        setOutputParamHandler(handler: OutputParamHandler | null): void;

        /**
         * Get the parameter output handler.
         *
         * @return {OutputParamHandler} the current output handler
         */
        getOutputParamHandler(): OutputParamHandler | null;

        /**
         * Set the compute handler, to  be called in the 'compute' method with buffer size.
         *
         * @param {ComputeHandler} handler - the compute handler
         */
        setComputeHandler(handler: ComputeHandler | null): void;

        /**
         * Get the compute handler.
         *
         * @return {ComputeHandler} the current output handler
         */
        getComputeHandler(): ComputeHandler | null;

        /**
         * Set the plot handler, to  be called in the 'compute' method with various info (see PlotHandler type).
         *
         * @param {PlotHandler} handler - the plot handler
         */
        setPlotHandler(handler: PlotHandler | null): void;

        /**
         * Get the plot handler.
         *
         * @return {PlotHandler} the current plot handler
         */
        getPlotHandler(): PlotHandler | null;

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
         * DSP instance computation, to be called with successive input/output audio buffers, using their size.
         *
         * @param {Float32Array[]} inputs - the input audio buffers
         * @param {Float32Array[]} outputs - the output audio buffers
         */
        compute(inputs: Float32Array[], outputs: Float32Array[]): boolean;

        /**
         * Give a handler to be called on 'declare key value' kind of metadata.
         *
         * @param {MetadataHandler} handler - the handler to be used
         */
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
         * Get the table of all input parameters paths.
         *
         * @return {string[]} the table of all input parameters paths
         */
        getParams(): string[];

        /**
         * Get DSP JSON description with its UI and metadata.
         *
         * @return {string} the DSP JSON description
         */
        getJSON(): string;

        /**
         * Get DSP UI description.
         *
         * @return {TFaustUI} the DSP UI description
         */
        getUI(): TFaustUI;

        /**
        * Get DSP UI items description.
        *
        * @return {TFaustUIItem[]} the DSP UI items description
        */
        getDescriptors(): TFaustUIInputItem[];

        /**
         * Start the DSP.
         *
         */
        start(): void;

        /**
         * Stop the DSP.
         *
         */
        stop(): void;

        /**
         * Destroy the DSP.
         *
         */
        destroy(): void;
    }

    /**
     * Monophonic DSP implementation.
     */

    /**
     * The MonoDSP constructor.
     * 
     * @param {MonoInstance} instance - an instance created with 'createSyncMonoDSPInstance' or 'createAsyncMonoDSPInstance'
     * @param {number} sample_rate - the sample rate in Hz
     * @param {number} sample_size - the sample size in bytes
     * @param {number} buffer_size - the buffer size in frames  
     * @return the created MonoDSP object 
     */
    interface createMonoDSP { (instance: MonoInstance, sample_rate: number, sample_size: number, buffer_size: number): MonoDSP }

    interface MonoDSP extends BaseDSP { }

    /**
     * Polyphonic DSP implementation.
     */

    /**
     * The PolyDSP constructor.
     * 
     * @param {PolyInstance} instance - an instance created with 'createSyncPolyDSPInstance' or 'createAsyncPolyDSPInstance'
     * @param {number} sample_rate - the sample rate in Hz
     * @param {number} sample_size - the sample size in bytes
     * @param {number} buffer_size - the buffer size in frames 
     * @return the created PolyDSP object 
     */
    interface createPolyDSP { (instance: PolyInstance, sample_rate: number, sample_size: number, buffer_size: number): PolyDSP }

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
     * Monophonic AudioNode.
     */
    interface FaustMonoNode extends AudioNode, MonoDSP { }

    /**
     * Polyphonic AudioNode.
     */
    interface FaustPolyNode extends AudioNode, PolyDSP { }

    /**
     *  For offline rendering.
     */
    interface FaustOfflineProcessor {

        /**
         * Render frames in an array.
         *
         * @param {number} size - the number of frames to render
         * @return {number} an array of Float32Array[] with the rendered frames
         */
        plot(size: number): Float32Array[];
    }

    interface MonoFactory {

        /**
         * Compile a monophonic WebAudio node (either ScriptProcessorNode or AudioWorkletNode).
         * Note that an internal cache avoids recompilation when a same DSP program is recompiled several times.  
         * 
         * @param {BaseAudioContext} context the WebAudio context
         * @param {string} name - the DSP name
         * @param {Compiler} compiler - the Faust compiler
         * @param {string} dsp_code - the DSP code
         * @param {string} args - the compilation parameters
         * @param {boolean} sp - whether to compile a ScriptProcessorNode or an AudioWorkletNode
         * @param {number} buffer_size - the buffer size in frames to be used, in ScriptProcessorNode only, since AudioWorkletNode always uses 128 frames   
         * @preturn {Promise<FaustMonoNode | null>} the compiled WebAudio node or 'null' if failure
         */
        compileNode(
            context: BaseAudioContext,
            name: string,
            compiler: Compiler,
            dsp_code: string,
            args: string,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustMonoNode | null>;

        /**
         * Create a monophonic WebAudio node (either ScriptProcessorNode or AudioWorkletNode).
         *
         * @param {BaseAudioContext} context the WebAudio context
         * @param {string} name - the DSP name
         * @param {Factory} factory - the Faust factory, either obtained with a compiler (createDSPFactory) or loaded from files (loadDSPFactory)
         * @param {boolean} sp - whether to compile a ScriptProcessorNode or an AudioWorkletNode
         * @param {number} buffer_size - the buffer size in frames to be used in ScriptProcessorNode only, since AudioWorkletNode always uses 128 frames  
         * @preturn {Promise<FaustMonoNode | null>} the compiled WebAudio node or 'null' if failure
        */
        createNode(
            context: BaseAudioContext,
            name: string,
            factory: Factory,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustMonoNode | null>;

        /**
         * Return the internal factory.
         *
         * @preturn {Factory | null} the internal factory which can be null if compilation failed
         */
        getFactory(): Factory | null;

        /**
        * Create a monophonic Offline processor.
        *
        * @param {Factory} factory - the Faust factory, either obtained with a compiler (createDSPFactory) or loaded from files (loadDSPFactory)
        * @param {number} sample_rate - the sample rate in Hz
        * @param {number} buffer_size - the buffer size in frames   
        * @preturn {Promise<FaustOfflineProcessor | null>} the compiled processor or 'null' if failure
       */
        createOfflineProcessor(factory: Factory, sample_rate: number, buffer_size: number)
            : Promise<FaustOfflineProcessor | null>;
    }

    interface PolyFactory {

        /**
         * Compile a polyphonic WebAudio node from a single DSP file (either ScriptProcessorNode or AudioWorkletNode). 
         * Note that the an internal cache avoid recompilation when a same DSP program is recompiled several times.
         *
         * @param {BaseAudioContext} context the WebAudio context
         * @param {string} name - the DSP name
         * @param {Compiler} compiler - the Faust compiler
         * @param {string} dsp_code - the DSP code ('dsp_code' can possibly contain an integrated effect)
         * @param {string | null} effect_code - optional effect DSP code
         * @param {string} args - the compilation parameters
         * @param {number} voices - the number of voices
         * @param {boolean} sp - whether to compile a ScriptProcessorNode or an AudioWorkletNode
         * @param {number} buffer_size - the buffer size in frames to be used, in ScriptProcessorNode only, since AudioWorkletNode always uses 128 frames
         * @preturn {Promise<FaustPolyNode | null>} the compiled WebAudio node or 'null' if failure
         */
        compileNode(
            context: BaseAudioContext,
            name: string,
            compiler: Compiler,
            dsp_code: string,
            effect_code: string | null,
            args: string,
            voices: number,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustPolyNode | null>;

        /**
         * Create a polyphonic WebAudio node (either ScriptProcessorNode or AudioWorkletNode).
         *
         * @param {BaseAudioContext} context the WebAudio context
         * @param {string} name - the DSP name
         * @param {Factory} voice_factory - the Faust factory for voices, either obtained with a compiler (createDSPFactory) or loaded from files (loadDSPFactory)
         * @param {WebAssembly.Module} mixer_module - the wasm Mixer module (loaded from 'mixer32.wasm' or 'mixer64.wasm' files)
         * @param {number} voices - the number of voices
         * @param {boolean} sp - whether to compile a ScriptProcessorNode or an AudioWorkletNode
         * @param {Factory} effect_factory - the Faust factory for the effect, either obtained with a compiler (createDSPFactory) or loaded from files (loadDSPFactory) 
         * @param {number} buffer_size - the buffer size in frames to be used in ScriptProcessorNode only, since AudioWorkletNode always uses 128 frames
         * @preturn {Promise<FaustPolyNode | null>} the compiled WebAudio node or 'null' if failure
         */
        createNode(
            context: BaseAudioContext,
            name: string,
            voice_factory: Factory,
            mixer_module: WebAssembly.Module,
            voices: number,
            sp: boolean,
            effect_factory?: Factory,
            buffer_size?: number)
            : Promise<FaustPolyNode | null>;

        /**
         * Return the internal voice factory.
         *
         * @preturn {Factory | null} the internal factory which can be null if compilation failed
         */
        getVoiceFactory(): Factory | null;

        /**
        * Return the internal effect factory.
        *
        * @preturn {Factory | null} the internal factory which can be null if compilation failed or if effect is not present
        */
        getEffectFactory(): Factory | null;

    }
}

// Moved at the end of the file to please Visual Studio code completion tools.

/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 ************************************************************************
 ************************************************************************/
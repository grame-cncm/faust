

///<reference path="FaustWebAudio.d.ts"/>

declare namespace Faust {

    /**
     * WAP (Web Audio Plugins see https://github.com/micbuffa/WebAudioPlugins) API.   
     */
    interface WAP {

        fBaseURL: string;

        getMetadata(): Promise<string>;

        setParam(path: string, value: number): void;
        getParam(path: string): number;

        inputChannelCount(): number;
        outputChannelCount(): number;

        // TODO (proper typing)
        getDescriptor(): any;

        onMidi(data: number[] | Uint8Array): void;
    }

    interface FaustMonoWAPNode extends FaustMonoNode, WAP { }

    interface MonoWAPFactory {

        load(wasm_path: string, json_path: string, sp: boolean)
            : Promise<FaustMonoWAPNode | null>;
    }

    interface FaustPolyWAPNode extends FaustPolyNode, WAP { }

    interface PolyWAPFactory {

        load(voice_path: string,
            voice_json_path: string,
            effect_path: string,
            effect_json_path: string,
            mixer_path: string,
            voices: number,
            sp: boolean,
            buffer_size?: number)
            : Promise<FaustPolyWAPNode | null>;
    }
}

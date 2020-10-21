// Adaptation class
class FaustDSPPoly {

    constructor(context, voices, baseURL, sp = false) {
        this.fAudioContext = context;
        this.fBaseURL = baseURL;
        this.fVoices = voices;
        this.fSP = sp;
    }

    async load() {
        factory = Faust.createPolyWAPFactory(audioCtx, "");
        return factory.load("DSP.wasm", "DSP.json", "DSP_effect.wasm", "DSP_effect.json", "mixer32.wasm", this.fVoices, this.fSP, 1024);
    }

    async loadGui() {
        return new Promise((resolve, reject) => {
            try {
                // DO THIS ONLY ONCE. If another instance has already been added, do not add the html file again
                let real_url = (this.baseURL === "") ? "main.html" : (this.baseURL + "/main.html");
                if (!this.linkExists(real_url)) {
                    // LINK DOES NOT EXIST, let's add it to the document
                    let link = document.createElement('link');
                    link.rel = 'import';
                    link.href = real_url;
                    document.head.appendChild(link);
                    link.onload = (e) => {
                        // the file has been loaded, instanciate GUI
                        // and get back the HTML elem
                        // HERE WE COULD REMOVE THE HARD CODED NAME
                        var element = createDSPGUI(this.node);
                        resolve(element);
                    }
                } else {
                    // LINK EXIST, WE AT LEAST CREATED ONE INSTANCE PREVIOUSLY
                    // so we can create another instance
                    let element = createDSPGUI(this.node);
                    resolve(element);
                }
            } catch (e) {
                console.log(e);
                reject(e);
            }
        });
    };

    linkExists(url) {
        return document.querySelectorAll(`link[href="${url}"]`).length > 0;
    }
}
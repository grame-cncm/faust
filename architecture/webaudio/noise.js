// WAP adaptation class
class Faustnoise {

    constructor(context, baseURL, sp = false) {
        this.fAudioContext = context;
        this.fBaseURL = baseURL;
        this.fSP = sp;
        this.fNode = null;
    }

    async load() {
        const factory = Faust.createMonoWAPFactory(this.fAudioContext, this.fBaseURL);
        this.fNode = factory.load("noise.wasm", "noise.json", this.fSP);
        return this.fNode;
    }

    // A synonym creation function
    async create() {
        return this.load();
    }

    async loadGui() {
        return new Promise((resolve, reject) => {
            try {
                // Do this only once. If another instance has already been added, do not add the html file again.
                let real_url = (this.baseURL === "") ? "main.html" : (this.baseURL + "/main.html");
                if (!this.linkExists(real_url)) {
                    // Link does nos exist, let's add it to the document
                    let link = document.createElement('link');
                    link.rel = 'import';
                    link.href = real_url;
                    document.head.appendChild(link);
                    link.onload = (e) => {
                        // The file has been loaded, instanciate GUI and get back the HTML elem
                        // Here we could remove the hard coded name.
                        let element = createnoiseGUI(this.fNode);
                        resolve(element);
                    }
                } else {
                    // Link exist, we at least create one instance previously so we can create another instance.
                    let element = createnoiseGUI(this.fNode);
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


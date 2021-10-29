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

///<reference path="FaustWebAudioImp.ts"/>

namespace Faust {

    export class FaustOfflineProcessorImp implements FaustOfflineProcessor {

        private fDSPCode: MonoDSP;
        private fBufferSize: number;
        private fInputs: Float32Array[];
        private fOutputs: Float32Array[];

        constructor(instance: MonoDSP, buffer_size: number) {
            this.fDSPCode = instance;
            this.fBufferSize = buffer_size;
            this.fInputs = new Array(this.fDSPCode.getNumInputs()).fill(null).map(() => new Float32Array(buffer_size));
            this.fOutputs = new Array(this.fDSPCode.getNumOutputs()).fill(null).map(() => new Float32Array(buffer_size));
        }

        plot(size: number): Float32Array[] {
            const plotted = new Array(this.fDSPCode.getNumOutputs()).fill(null).map(() => new Float32Array(size));
            // The node has to be started before rendering
            this.fDSPCode.start();
            for (let frame = 0; frame < size; frame += this.fBufferSize) {
                // Render one buffer
                this.fDSPCode.compute(this.fInputs, this.fOutputs);
                // Copy the buffer to the output array
                for (let chan = 0; chan < plotted.length; chan++) {
                    plotted[chan].set(size - frame > this.fBufferSize ? this.fOutputs[chan] : this.fOutputs[chan].subarray(0, size - frame), frame);
                }
            }
            // The node can be stopped after rendering
            this.fDSPCode.stop();
            return plotted;
        }
    }
}

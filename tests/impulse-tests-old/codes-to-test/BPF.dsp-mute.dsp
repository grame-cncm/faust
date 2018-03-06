process = P : par(i, outputs(P), (_,(1-checkbox("fakedisable %2i")) : *) ) with { P = component("BPF.dsp"); };

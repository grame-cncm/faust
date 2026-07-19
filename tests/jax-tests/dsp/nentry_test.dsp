import("stdfaust.lib");

// Test nentry with metadata
mode = nentry("mode[tau:learnable][tau_init:0.5]", 0, 0, 3, 1);
process = _ * mode;

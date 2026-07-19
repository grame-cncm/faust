import("stdfaust.lib");

// Test nentry without metadata (should use defaults)
mode = nentry("mode", 0, 0, 3, 1);
process = _ * mode;

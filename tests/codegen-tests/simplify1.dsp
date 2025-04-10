// Should compile to:
/*
for (int i0 = 0; i0 < count; i0 = i0 + 1) {
	output0[i0] = FAUSTFLOAT(0);
}
*/

import("stdfaust.lib");
process = re.satrev :> _;


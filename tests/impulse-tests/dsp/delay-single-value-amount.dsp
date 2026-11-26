// A delay amount whose interval is a single value, delayed again (#1415)
process = _ <: (@(hslider("a", 0, 0, 0, 1)) : @(2)),
               (@(hslider("b", 3, 3, 3, 1)) : @(2)),
               ((+(1) ~ _) : @(max(0, min(0, int(hslider("c", 0, -1, 1, 1))))) : mem);

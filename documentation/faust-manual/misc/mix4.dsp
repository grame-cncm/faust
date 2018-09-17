input(v) = vgroup("input %v", *(1-checkbox("mute")) : *(vslider("level", 0, 0, 1, 0.01)));
process = hgroup("mixer", par(i, 4, input(i)) :> _);
process = select2(sel, x, y)
with {
    sel = waveform{1, 0, 0, 0} : !,_;
    x = +(1) ~ _;
    y = +(2) ~ _;
};

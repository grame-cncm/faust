// Learnable variant of soundfile_channel_wrap.dsp: the channel wrap must not copy the buffers
process = 0,_~+(1) : soundfile("wrap[param:1][url:{'channel_wrap.wav'}]",4) : !,!,_,_,_,_;

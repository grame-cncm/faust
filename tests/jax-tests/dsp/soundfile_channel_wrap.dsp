// 4 channels read from a stereo file: channels 2 and 3 are channels 0 and 1 (see TestSoundfileChannelWrap)
process = 0,_~+(1) : soundfile("wrap[url:{'channel_wrap.wav'}]",4) : !,!,_,_,_,_;

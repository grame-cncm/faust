// Requests 4 soundfile channels while the loaded file may have fewer (see
// TestSoundfileChannelWrap in test_features.py): channels beyond the
// file's real count must cyclically reuse the real channels, matching the
// reference architecture's Soundfile::shareBuffers (chan % cur_chan).
process = 0,_~+(1) : soundfile("mysound[url:{'channel_wrap.wav'}]",4) : !,!,_,_,_,_;

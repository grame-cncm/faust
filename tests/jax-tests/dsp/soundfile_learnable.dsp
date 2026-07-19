// Test learnable soundfile with new [param:1] metadata syntax
process = 0,_~+(1):soundfile("learnable[param:1][url:{'assets/sound1.wav'}]",4):!,!,_,_,_,_;

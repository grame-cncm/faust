import("multirate.lib");

//process = upsample(3)*_;

process = down(10,_) : *(5) : up(10,_);


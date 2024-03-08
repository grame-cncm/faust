import("stdfaust.lib");

process = ratelimiter (10,5);
ratelimiter(uprate, downrate) = rate_limited_sig
with{
  //---definitions
  down_delta_limit = ((downrate) / ma.SR) : *(-1);
  up_delta_limit = uprate / ma.SR;
 //---compute
  rate_limited_sig = _ : limiter ~ _
  with{
   limiter(mem_out_n,in_n) = in_n - mem_out_n :  
                             min(up_delta_limit) :
                             max(down_delta_limit) :
                             +(mem_out_n);
  };
};
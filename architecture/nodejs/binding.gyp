{
  "targets": [
    {
      "target_name": "faust",
      "include_dirs": [ "/usr/local/include" ],
      "cflags_cc!": [ "-fno-rtti","-fno-exceptions" ],
      "cflags": [ "__CFLAGS__" ],     
      "libraries": [ "-L/usr/local/lib __LIBFLAGS__" ],
      "sources": [ "faust.cpp","DspFaust.cpp","DspFaustNode.cpp" ]
    }
  ]
}
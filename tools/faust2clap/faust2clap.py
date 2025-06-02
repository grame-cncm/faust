import sys #cli arguments
import os #file path manipulation
import subprocess #run shell commands


#check for user input, which should be a .dsp file, otherwise just exit
if len(sys.argv)<2:
    print("usage: faust2clap.py <file.dsp>")
    sys.exit(1)


dsp_file= sys.argv[1]#full path to the provdded .dsp file
base=os.path.splitext(os.path.basename(dsp_file))[0] #name minus extension (.dsp)
out_cpp=f"{base}_clap.cpp" #target outpu filename

arch_file="architecture/clap/clap-arch.cpp" #future location of clap architecture file



#now call faust, tell faust which architectue to use, its input and output


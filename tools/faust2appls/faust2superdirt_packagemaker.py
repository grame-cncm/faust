import os
import sys
import os.path
from os import path
import json
from collections import ChainMap
import subprocess
import platform
import shutil


######################################
#######▄▄▄#▄▄▄▄▄▄▄#▄▄▄▄▄▄▄#▄▄####▄#### 
######█   █       █       █  █##█ █###
######█   █  ▄▄▄▄▄█   ▄   █   █▄█ █###
###▄##█   █ █▄▄▄▄▄█  █#█  █       █###
##█ █▄█   █▄▄▄▄▄  █  █▄█  █  ▄    █###
##█       █▄▄▄▄▄█ █       █ █#█   █###
##█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄█##█▄▄█###
######################################

    
    #####PARAMETERS LISTS
    
    
PARAMETER = ["hslider", "vslider", "hbargraph", "vbarbraph",
                            "nentry", "checkbox", "button"]
GROUP = ["vgroup", "hgroup", "tgroup"]

TIDALCONTROL = ["gain", "sound", "s", "delay", "setcps", "midinote", "note", "n","octave","begin","end","sustain","legato","loop","unit","length","fadeTime","fadeInTime","speed","endSpeed","gain","overgain","channel","lag","offset","sound","array","midichan","control","ccn","ccv","polyTouch","midibend","miditouch","ctlNum","frameRate","frames","hours","midicmd","minutes","progNum","seconds","songPtr","uid","val","timescale","timescalewin", "toArg", "from", "to", "accelerate", "amp", "attack", "bandf", "bandq", "begin", "legato", "clhatdecay", "crush", "coarse", "channel", "cut", "cutoff", "cutoffegint", "decay", "delay", "delayfeedback", "delaytime", "detune", "djf", "dry", "end", "fadeTime", "fadeInTime", "freq", "gain", "gate", "hatgrain", "hcutoff", "hold", "hresonance", "lagogo", "lclap", "lclaves", "lclhat", "lcrash", "leslie", "lrate", "lsize", "lfo", "lfocutoffint", "lfodelay", "lfoint", "lfopitchint", "lfoshape", "lfosync", "lhitom", "lkick", "llotom", "lock", "loop", "lophat", "lsnare","n", "note", "degree", "mtranspose", "ctranspose", "harmonic", "stepsPerOctave", "octaveR", "nudge", "octave", "offset", "ophatdecay", "orbit", "overgain", "overshape", "pan", "panspan", "pansplay", "panwidth", "panorient", "pitch1", "pitch2", "pitch3", "portamento", "rate", "release", "resonance", "room",  "sagogo", "sclap", "sclaves", "scrash", "semitone", "shape", "size", "slide", "speed",  "squiz", "stutterdepth", "stuttertime", "sustain",  "timescale", "timescalewin", "tomdecay","unit",  "velocity","vcfegint", "vcoegint",  "voice",  "vowel",  "waveloss", "dur",  "modwheel", "expression",  "sustainpedal", "tremolodepth","tremolorate", "phaserdepth", "phaserrate", "fshift", "fshiftnote","fshiftphase", "triode", "krush",  "kcutoff", "octer", "octersub", "octersubsub","ring","ringf", "ringdf", "distort", "freeze", "xsdelay", "tsdelay",  "real",  "imag", "enhance", "partials","comb","smear", "scram", "binshift", "hbrick","lbrick","midichan", "control","ccn","ccv","polyTouch","midibend", "miditouch","ctlNum", "frameRate", "frames", "hours", "midicmd", "minutes", "progNum","seconds","songPtr", "uid", "val","cps", "up", "att", "bpf", "bpq", "chdecay", "ctf", "ctfg", "delayfb", "dfb", "delayt", "dt", "det", "fadeOutTime", "gat", "hg", "hpf", "hpq","lag","ldb","lch", "lcl", "lcp", "lcr", "lfoc", "lfoi", "lfop", "lht", "llt", "loh", "lpf", "lpq", "lsn", "ohdecay", "phasdp", "phasr","pit1","pit2", "pit3", "por", "rel", "sag", "scl","scp","scr", "sz", "sld", "std", "stt", "sus", "tdecay", "tremdp", "tremr", "vcf", "vco", "voi"]


def flatten(container):
    """ Helper function to flatten arbitrarily nested lists """
    for i in container:
        if isinstance(i, (list,tuple)):
            for j in flatten(i):
                yield j
        else:
            yield i

def json_to_ui_data(json_data: dict):
    """ Return the UI part of the Faust-generated JSON """
    return json_data["ui"][0]


def flatteny(S):
    if S == []:
        return S
    if isinstance(S[0], list):
        return flatteny(S[0]) + flatteny(S[1:])
    return S[:1] + flatteny(S[1:])
#recuperateur de fin d'address
#storager of address' end
def unaddress(address: str) :
    raddress = address.rsplit('/', 2)
    raddresslast = raddress[1]+"_"+(raddress[2])
    return raddresslast

#videur de vide
#emptier of emptyness
def devideur(tuples): 
    tuples = [t for t in tuples if t] 
    return tuples 

#selectionneur    \o/        __
#selector         |\ ~ ~ o  | |
def selector(lalist : list):
    for x in range(0, (len(lalist)-1)):
        dopple = (lalist[x])
        #si le label est déjà un control de tidal
        #remplace le nom avec le label supérieur
        #If the label is already a tidal control
        #swap with a longer label address
        if dopple in TIDALCONTROL : 
            lalist[x] = ''
        elif lalist.count(dopple) > 1 :
            lalist[x] = ''
        elif lalist.count(dopple) == 1 :
            lalist[x+1] = ''
    lalist = devideur(lalist)    
    return lalist       

def item_list_processor(items_value: list):
    """ Process data contained in "items" keys """
    parameter_list = []
    # On parcourt chaque dictionnaire que l'on trouve dans la liste "items"
    for items in items_value:
        if isinstance(items, dict):
            # Si on voit que le type correspond à un param, on gagne un param
            if items["type"] in PARAMETER :
                parameter_list.append(items["label"]) 
            # Sinon, cela signifie que l'on doit 
            # continuer à descendre pour extraire
            elif items["type"] in GROUP :
                parameter_list.append(item_list_processor(items["items"]))
            #Crée une double liste de forme : ['param1' , 'group_param1',...] 
            #afin de la passer dans la fonction selector 
            #qui va décider lequel choisir
            if items["label"] in parameter_list :
                parameter_list.append(unaddress(items["address"]))
        else:
            pass
    return parameter_list

def parameter_gatherer(data):
    """ JSON Parameter extractor """
    parameter_list = []
    for key, value in data.items():
        if key == "items":
            parameter_list.append(item_list_processor(value))
        else:
            continue
    return parameter_list

    
    
    ###Files Finder

def find_file(file_name, directory_name):
    files_found = []
    for path, subdirs, files in os.walk(directory_name):
        for name in files:
            if(file_name == name):
                file_path = os.path.join(path,name)
                files_found.append(file_path)
    return files_found

    
""" 
 / \------------------, 
 \_,|                 | 
    |    Coresynths   | 
    |  ,----------------
    \_/_______________/     
    
"""

def cs_placeholder_filler(synth_name: str, c_synth_name:str, nb_inputs : int, argument_list: list):
    """ Inserting arguments in placeholder SynthDef """
    template = '''\nSynthDef(\"{synth_name}\" ++ ~dirt.numChannels, {{
        | out, {in_list},{argument_list}|
        var signal = In.ar(out, ~dirt.numChannels);
        signal = {c_synth_name}.ar({signal_beg}, {signal_argument}, out);
        ReplaceOut.ar(out, signal);}}).add;\n
    '''
    ###add one "signal" by inputs
    signal_beg="signal"
    for x in range(1, nb_inputs, 1):
        signal_beg = signal_beg+",signal"
        
    ###add in%s by inputs
    in_list = "in0"
    for x in range(1, nb_inputs, 1):
        in_list = in_list+",in%s" % x
    
    
    argument_beautify = ', '.join(argument_list)
    return template.format(synth_name=synth_name,
                           c_synth_name=c_synth_name,
                           argument_list=argument_beautify,
                           signal_argument=argument_beautify,
                           nb_inputs=nb_inputs,
                           signal_beg=signal_beg,
                           in_list=in_list)

"""
 / \------------------, 
 \_,|                 | 
    |    Coremodules  | 
    |  ,----------------
    \_/_______________/ 
"""   


def cm_placeholder_filler(synth_name: str, argument_list: list):
    """ Inserting arguments in placeholder """
    template = '''\n~dirt.addModule('{synth_name}',
        {{|dirtEvent|
            dirtEvent.sendSynth('{synth_name}' ++ ~dirt.numChannels,
            [ 
                {parameters},
                out: ~out
            ])
            }} {subparameters} }});
    \n'''
    parameters = ["{x}: ~{x}".format(x=x) for x in argument_list]
    subparameters = [",{{~{x}.notNil".format(x=argument_list[0])]
    # weird formatting to match default file
    parameters = ",\n                ".join(parameters)
    subparameters = " or:  ".join(subparameters)
    parameters = parameters.replace('"', '')
    return template.format(synth_name=synth_name, 
            parameters=parameters,
           subparameters=subparameters)

"""
 / \-----------------, 
 \_,|                | 
    |    BootTidal   | 
    |  ,---------------
    \_/______________/ 
"""
  

def bt_placeholder_filler(synth_name: str, argument_list: list):
    """ Inserting arguments in placeholder SynthDef """
    template = '''\n:{{\nlet {parameters}
    \n:}}\n'''    
    
    parameters = [" {x} = pF \"{x}\"  ".format(x=x) for x in argument_list]
    # weird formatting to match default file
    parameters = "\n     ".join(parameters)
    parameters = parameters.replace('', '')
    return template.format(synth_name=synth_name, 
            parameters=parameters)

"""
 / \-----------------, 
 \_,|                | 
    |    HelpFile    | 
    |  ,---------------
    \_/______________/ 
"""
  


def help_placeholder_filler(synth_name: str, c_synth_name: str, argument_list: list, nb_inputs : int, nb_outputs : int):
    """ Creating the help file template """
    template = '''    

░░▓░░▓░▓▓▓▓░▓░░░░▓▓▓▓░▓▓▓▓░▓░▓░░░░▓▓▓▓░
░░▓░░▓░▓░░░░▓░░░░▓░░▓░▓░░░░▓░▓░░░░▓░░░░
░░▓▓▓▓░▓▓▓░░▓░░░░▓▓▓▓░▓▓░░░▓░▓░░░░▓▓▓░░    
░░▓░░▓░▓░░░░▓░░░░▓░░░░▓░░░░▓░▓░░░░▓░░░░
░░▓░░▓░▓▓▓▓░▓▓▓▓░▓░░░░▓░░░░▓░▓▓▓▓░▓▓▓▓░


faust2superdirt.py is a python program, created to
help users of TidalCycles in the faust audio effect adding process.

faust2superdirt.py works in adequacy with faust2sc.py
It's got two arguments, the path to the jsonfile created by the faust2sc.py compiler.
And the path to your BootTidal.hs

Currently the effect you want to add is named : {c_synth_name}.
And all his parameters are : {argument_list}.
The number of inputs is : {nb_inputs}.
The number of outputs is : {nb_outputs}.

/manual_installation\

In the files2add directory, you will find three differents files :

- add2core-synth.scd 
- add2core-modules.scd 

Add this to your core-synth.scd and core-modules.scd files usually located in /home/yourusername/.local/share/SuperCollider/downloaded-quarks/SuperDirt/synths/

- add2BootTidal.scd 

Add this to your BootTidal.hs file, be careful it's never where you think it is, mine is located in /home/yourusername/.cabal/share/x86_64-linux-ghc-8.6.5/tidal-1.7.10/

/automatic_installation\

The real interesting thing is the automatic installation, 
just run the python program faust2superdirt.py with the two arguments :

- the path to jsonfile created by the faust2sc.py compiler.
- the path to your BootTidal.hs

It will automatically write the where it has to be. 



         ><]]]^>                  ><]]]^>          ><]]]^>
       ><]]]^>           ><]]]^>         ><]]]^>      ><]]]^>
              ><]]]^>      ><]]]^>                ><]]]^>
    '''
    
    argument_beautify = ', '.join(argument_list)
    return template.format(synth_name=synth_name,
                           c_synth_name=c_synth_name,
                           argument_list=argument_beautify,
                           nb_inputs=nb_inputs,
                           nb_outputs=nb_outputs)






def filecreator(filename : str, cont : str) :
    myFile = open(filename, "w+")

    myFile.write(cont)

    myFile.close()
        
    return myFile
    
    

if __name__ == "__main__":
    
    
    import argparse
    import sys
    import tempfile

    parser = argparse.ArgumentParser(
        description='PackageCreator'
    )

    parser.add_argument("inputjson", help="A Faust JSON .dsp.json file to be used, normally created in the same path as your Faust.dsp by faust2sc.py")
    


    args, unknownargs = parser.parse_known_args()

    # Flatten list of arguments to one string
    unknownargs = " ".join(unknownargs)
    faustflags = unknownargs or ""

    # Temporary folder for intermediary files
    tmp_folder = tempfile.TemporaryDirectory(prefix="faust.")


    
#json

# Opening JSON file

    with open(args.inputjson) as json_file:
        json_data = json.load(json_file)
        my_inputs = json_data['inputs']
        my_outputs = json_data['outputs']
        my_name = json_data['name']
    
    json_data = json_to_ui_data(json_data)
    param = parameter_gatherer(json_data)
    param = list(flatten(param))
    param = selector(param)
    print("the list of parameters is : ")
    print(param)
    
    
    os.mkdir(my_name + '_'+ 'PACKAGE')
    os.mkdir(my_name + '_'+ 'PACKAGE/files2add')
        
#coresynth
    new_def = cs_placeholder_filler(synth_name =  my_name,
              c_synth_name = my_name.capitalize(),
              nb_inputs = my_inputs,                  
              argument_list = param)
    filecreator(filename = my_name + '_'+ "PACKAGE/files2add/add2core-synth.scd",
                cont=new_def)

#coremodules

    #cm_FILEPATH = get_coremodules_filepath()

    new_def = cm_placeholder_filler(synth_name = my_name,
              argument_list = param)
    filecreator(filename = my_name + '_'+ "PACKAGE/files2add/add2core-modules.scd",
                cont=new_def)

#boottidal 

    #bt_FILEPATH = get_boottidal_filepath()

    new_def = bt_placeholder_filler(synth_name = my_name,
              argument_list = param)
    filecreator(filename = my_name + '_'+ "PACKAGE/files2add/add2BootTidal.hs",
                cont=new_def)
    #bt_inject_new_definition(text_content=new_def, filepath=bt_FILEPATH)
    
#HelpFile 


    new_def = help_placeholder_filler(synth_name = my_name,
              c_synth_name = my_name.capitalize(),                        
              argument_list = param,
              nb_inputs = my_inputs,
              nb_outputs = my_outputs,                       )
    filecreator(filename = my_name + '_'+ "PACKAGE/Helpfile.txt",
                cont=new_def)
    


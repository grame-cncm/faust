#!/usr/bin/env python3
# Compile a faust file as a SuperCollider help file
import os
import sys
import os.path
from os import path
import json
from collections import ChainMap
import subprocess
import platform
import shutil

###########################################
# Utils
###########################################

# TODO Is this cross platform? Does it work on Windows?
def convert_files(dsp_file, out_dir, arch):
    cpp_file = path.splitext(path.basename(dsp_file))[0] + ".cpp"
    arch_file = arch or "supercollider.cpp"

    cmd = "faust -i -a %s -json %s -o %s" % (arch_file, dsp_file, cpp_file)

    result = {
        "arch_file": arch_file,
        "dsp_file": dsp_file,
        "out_dir": out_dir,
        "cpp_file": cpp_file,
        "json_file": dsp_file + ".json"
    }

    print("Converting faust file to .json and .cpp.\nCommand:\n%s.\nc++ file:%s\njson file:%s" % (cmd, cpp_file, result["json_file"]))
    try:
        subprocess.run(cmd.split(), check = True, capture_output=False)
        # shutil.move(result["cpp_file"], path.join(out_dir, result["cpp_file"]))
        # shutil.move(result["json_file"], path.join(out_dir, result["json_file"]))
    except subprocess.CalledProcessError:
        # print(cmd)
        sys.exit('faust failed to compile json file')

    return result

def read_json(json_file):
    if path.exists(json_file):
        f = open(json_file)
        data = json.load(f)
        f.close()
        return data
    else:
        sys.exit("Could not find json file %s" % json_file)

# Some parts of the generated json file are parsed as lists of dicts -
# This flattens one of those into one dictionary
def flatten_list_of_dicts(list_of_dicts):
    return ChainMap(*list_of_dicts)

def write_file(file, contents):
    f = open(file, "w")
    f.write(contents)
    f.close()

def make_dir(dir_path):
    if not path.exists(dir_path):
        os.mkdir(dir_path)

###########################################
# Compilation
###########################################

# TODO flags/env vars not included yet:
# - DNDEBUG
# - OMP
# - FAUSTTOOLSFLAGS

# This is a slightly hackey way of including all of the environment variables found in the `faustoptflags` script, mostly because I could not find a python native way to set and access those variables otherwise
def faustoptflags():
    systemType = platform.system()
    machine = platform.machine()
    envDict = {}

    # Compilation flags for gcc and icc
    if machine == 'arm6vl':
        # Raspberry Pi
        envDict["MYGCCFLAGS"] = "-std=c++11 -O3 -march=armv6zk -mcpu=arm1176jzf-s -mtune=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -ffast-math -ftree-vectorize"

    # MacOS
    elif systemType == 'Darwin':
        envDict["EXT"] = "scx"

        # TODO: DNDEBUG
        envDict["SCFLAGS"] = "-DNO_LIBSNDFILE -DSC_DARWIN -bundle"

        if machine == 'arm64':
            # Silicon MX
            envDict["MYGCCFLAGS"] = "-std=c++11 -Ofast"
        else:
            envDict["MYGCCFLAGS"] = "-std=c++11 -Ofast -march=native"

        envDict["MYGCCFLAGSGENERIC"]="-std=c++11 -Ofast"
    else:
        envDict["MYGCCFLAGS"] = "-std=c++11 -Ofast -march=native"
        envDict["MYGCCFLAGSGENERIC"] = "-std=c++11 -Ofast"

    envDict["MYICCFLAGS"]="-std=c++11 -O3 -xHost -ftz -fno-alias -fp-model fast=2"

    if systemType != 'Darwin':
        envDict["EXT"]="so"
        # TODO DNDEBUG
        envDict["SCFLAGS"]="-DNO_LIBSNDFILE -DSC_LINUX -shared -fPIC"

    if 'CXXFLAGS' in os.environ:
        envDict["MYGCCFLAGS"] = envDict["MYGCCFLAGS"] + " " + os.environ["CXXFLAGS"]

    # Set default values for CXX and CC
    if 'CXX' not in os.environ:
        os.environ['CXX'] = "c++"

    if 'CC' not in os.environ:
        os.environ['CC'] = "cc"

    os.environ['LIPO'] = "lipo"

    return envDict

# Return the header paths if they exists.
def get_header_paths(headerpath):
    folders = [
        path.join(headerpath, "plugin_interface"),
        path.join(headerpath, "server"),
        path.join(headerpath, "common")
    ]

    if all(path.exists(folder) for folder in folders):
        print("Found SuperCollider headers: %s" % headerpath)
        return folders

# Try and find SuperCollider headers on system
def find_headers(headerpath):
    folders = get_header_paths(headerpath)
    if folders:
        return folders

    # Possible locations of SuperCollider headers
    guess = [
        "/usr/local/include/SuperCollider",
        "/usr/local/include/supercollider",
        "/usr/include/SuperCollider",
        "/usr/include/supercollider",
        "/usr/local/include/SuperCollider/",
        "/usr/share/supercollider-headers",
        path.join(os.getcwd(), "supercollider")
    ]

    if 'HOME' in os.environ:
        guess.append(path.join(os.environ['HOME'], "supercollider"))

    for headerpath in guess:
        folders = get_header_paths(headerpath)
        if folders:
            return folders

    sys.exit("Could not find SuperCollider headers")

# Generate string of include flags for the compiler command
def includeflags(header_path):
    # dspresult = subprocess.run(["faust", "-dspdir"], stdout=subprocess.PIPE)
    # dspdir = dspresult.stdout.decode('utf-8')

    # libresult = subprocess.run(["faust", "-libdir"], stdout=subprocess.PIPE)
    # libdir = libresult.stdout.decode('utf-8')

    incresult = subprocess.run(["faust", "-includedir"], stdout=subprocess.PIPE)
    includedir = incresult.stdout.decode('utf-8')
    plugin, common, server = find_headers(header_path)
    return "-I%s -I%s -I%s -I%s -I%s" % (plugin, common, server, includedir, os.getcwd())

# Generate a string of build flags for the compiler command. This includes the include flags.
def buildflags(headerpath, macos_arch):

    mac_arch=""
    if macos_arch == "x86_64":
        mac_arch = "-arch x86_64"
    elif macos_arch == "arm64":
        mac_arch = "-arch arm64"

    env = faustoptflags()
    return "-O3 %s %s %s %s" % (env["SCFLAGS"], includeflags(headerpath), env["MYGCCFLAGS"], mac_arch)

# Compile a .cpp file generated using faust to SuperCollider plugins.
# TODO: Allow additional CXX flags
def compile(out_dir, cpp_file, class_name, compile_supernova, headerpath, macos_arch):
    print("Compiling %s" % class_name)
    flags = buildflags(headerpath, macos_arch)
    env = faustoptflags()

    if path.exists(cpp_file):
        scsynth_obj = path.join(out_dir, class_name + "." + env["EXT"])
        scsynth_compile_command = "%s %s -Dmydsp=\"%s\" -o %s %s" % (os.environ["CXX"], flags, class_name, scsynth_obj, cpp_file)

        # Compile scsynth
        print("Compiling scsynth object using command:\n%s" % scsynth_compile_command)
        os.system(scsynth_compile_command.replace("\n", ""))

        if compile_supernova:
            supernova_obj = path.join(out_dir, class_name + "_supernova." + env["EXT"])
            supernova_compile_command = "%s %s -Dmydsp=\"%s\" -o %s %s" % (os.environ["CXX"], flags, class_name, supernova_obj, cpp_file)

            print("Compiling supernova object using command:\n%s" % supernova_compile_command)
            os.system(supernova_compile_command.replace("\n", ""))
    else:
        sys.exit("Could not find cpp_file")

###########################################
# Help file
###########################################

# Iterate over all UI elements to get the parameter names, values and ranges
def get_help_file_arguments(json_data):
    out_string = ""
    # The zero index is needed because it's all in the first index, or is it? @FIXME
    for ui_element in flatten_list_of_dicts(json_data["ui"])["items"]:

        param_name = ""
        if "label" in ui_element:
            # Sanitize label
            param_name = sanitize_label(ui_element["label"])

        param_min=""
        if "min" in ui_element:
            param_min = ui_element["min"]

        param_max=""
        if "max" in ui_element:
            param_max = ui_element["max"]

        # Param name
        this_argument = "ARGUMENT::%s\n" % (param_name.lower())
        if "meta" in ui_element:
            meta = flatten_list_of_dicts(ui_element["meta"])

            # Add tooltip as a description
            if "tooltip" in meta:
                this_argument = this_argument + meta["tooltip"] + "\n"

        # Add min and max values if present
        if param_min and param_max:
            this_argument = this_argument + "Minimum value: %s\nMaximum value: %s\n" % (param_min, param_max)

        out_string = out_string + "\n" + this_argument

    return out_string

# Generate the contents of a SuperCollider help file
def class_help(json_data, noprefix):

    # TODO Are the fields used from this guaranteed and what happens if they are not used?
    meta = flatten_list_of_dicts(json_data["meta"])
    class_name = get_class_name(json_data, noprefix)

    if "description" in meta:
        desc = meta["description"]
    else:
        desc = "A Faust plugin"

    if "author" in meta:
        author = meta["author"]

        authorstring = "A Faust plugin written by %s." % author
    else:
        authorstring = ""

    out_string = """CLASS::%s
SUMMARY::A Faust plugin
RELATED::Classes/UGen
CATEGORIES::Categories>Faust
DESCRIPTION::
%s
This plugin has %s inputs and %s outputs.
%s

CLASSMETHODS::
METHOD::ar,kr
%s
EXAMPLES::

code::
// TODO
::

KEYWORD::faust,plugin""" % (
            class_name,
            authorstring,
            json_data["inputs"],
            json_data["outputs"],
            # get_value_from_dict_list(json_data["meta"], "description"),
            desc,
            # json_data["meta"]["description"],
            get_help_file_arguments(json_data)
        )

    return out_string

# Create a help file in target_dir
def make_help_file(target_dir, json_data, noprefix):

    # Create directory if necessary
    out_dir = path.join(target_dir, "HelpSource")
    make_dir(out_dir)
    out_dir = path.join(out_dir, "Classes")
    make_dir(out_dir)

    # help file
    file_name = get_class_name(json_data, noprefix) + ".schelp"
    file_name = path.join(out_dir, file_name)
    write_file(file_name, class_help(json_data, noprefix))

###########################################
# Class file
###########################################
def sanitize_label(label):
    # FIXME: Does this actually work with the compiled objects?
    remove_chars = "\\-_/([^)]*)"
    for char in remove_chars:
        label = label.replace(char, "")
    return label.lower()

# Iterate over all UI elements to get the parameter names, values and ranges
def get_parameter_list(json_data, with_initialization):
    out_string = ""
    # The zero index is needed because it's all in the first index, or is it? @FIXME
    counter=0

    inputs = ""
    if json_data["inputs"] > 0:
        for i in range(json_data["inputs"]):
            if i != 0:
                inputs = inputs + ", in%s" % i
            else:
                inputs = inputs + "in%s" % i

    for ui_element in json_data["ui"][0]["items"]:

        param_name=""
        if "label" in ui_element:
            param_name = sanitize_label(ui_element["label"])

        param_default = ""
        if "init" in ui_element:
            param_default = ui_element["init"]
        else:
            param_default = "0"

        # Param name
        if with_initialization:
            this_argument =  "%s(%s)" % (param_name, param_default)
        else:
            this_argument = param_name

        if counter != 0:
            out_string = out_string + ", " + this_argument
        else:
            out_string = this_argument

        counter = counter + 1

    if json_data["inputs"] > 0:
        if out_string == "":
            out_string = inputs
        else:
            out_string = inputs + "," + out_string

    return out_string

# This sanitizes the "name" field from the faust file, makes it capitalized, removes dashes and spaces
def get_class_name(json_data, noprefix):
    # Capitalize all words in string

    name = dsp_name(json_data)

    if noprefix != 1:
        name = "Faust" + name

    # Max length of name is 31
    if len(name) > 31:
        name = name[0:30]

    return name

# This matches the normalizeClassName function in supercollider.cpp
def normalizeClassName(meta_name):
    upnext=True
    normalized=""
    for char in meta_name:
        if upnext:
            normalized = normalized + char.upper()
            upnext=False
            continue
        if char == "_" or char=="-" or char==" ":
            upnext=True
        else:
            normalized = normalized + char

    maxlen = 31
    return normalized[0:maxlen-1]

def dsp_name(json_data):
    name  = normalizeClassName(json_data["name"])
    return name

# Generate supercollider class file contents
def get_sc_class(json_data, noprefix):
    # TODO Are the fields used from this guaranteed and what happens if they are not used?
    # meta = flatten_list_of_dicts(json_data["meta"])

    class_name = get_class_name(json_data, noprefix)
    name  = dsp_name(json_data)
    # name = json_data["name"]

    # Specifics for multi channel output ugens: Needs to inherit from different class and the init function needs to be overridden
    if json_data["outputs"] > 1:
        parent_class = "MultiOutUGen"
        init = """

init { | ... theInputs |
      inputs = theInputs
      ^this.initOutputs(%s, rate)
  }

    """ % json_data["outputs"]
    else:
        parent_class = "UGen"
        init = ""

    # Input checking
    if json_data["inputs"] > 0:
        input_check = """

checkInputs {
    if (rate == 'audio', {
      %s.do({|i|
        if (inputs.at(i).rate != 'audio', {
          ^(" input at index " + i + "(" + inputs.at(i) +
            ") is not audio rate");
        });
      });
    });
    ^this.checkValidInputs
  }

""" % json_data["inputs"]

    else:
        input_check = ""

    # The final class
    return """
%s : %s {

    *ar{|%s|
      ^this.multiNew('audio', %s)
    }

    *kr{|%s|
      ^this.multiNew('control', %s)
    }

    name { ^"%s" }

    info { ^"Generated with Faust" }
    %s
    %s
}
""" % (
            class_name, parent_class,
            # *ar
            get_parameter_list(json_data, True),
            get_parameter_list(json_data, False),

            # *kr
            get_parameter_list(json_data, True),
            get_parameter_list(json_data, False),

            # FIXME: This is pretty ugly but it matches what the normalizeClassName function does in faust's supercollider.cpp
            # Ideally, this should be fixed in the supercollider.cpp
            # Because, not doing this will lead to "plugin not installed" type errors in SuperCollider
            name,
            input_check,
            init
        )

# Make Supercollider class file
def make_class_file(target_dir, json_data, noprefix):

    # Create directory if necessary
    out_dir = path.join(target_dir, "Classes")
    make_dir(out_dir)

    # help file
    file_name = get_class_name(json_data, noprefix) + ".sc"
    file_name = path.join(out_dir, file_name)
    write_file(file_name, get_sc_class(json_data, noprefix))

###########################################
# faust2sc
###########################################

# Generate SuperCollider class and help files and return a dictionary of paths to the generated files including the .cpp and .json files produced by the faust command.
def faust2sc(faustfile, target_folder, noprefix, arch):
    print("Converting faust file to SuperCollider class and help files.\nTarget dir: %s" % target_folder)
    result = convert_files(faustfile, target_folder, arch)

    data = read_json(result["json_file"])
    make_class_file(target_folder, data, noprefix)
    make_help_file(target_folder, data, noprefix)

    result["class"] = get_class_name(data, noprefix)

    return result

if __name__ == "__main__":
    import argparse
    import sys
    import tempfile

    parser = argparse.ArgumentParser(
        description='Compile faust .dsp files to SuperCollider plugins including class and help files and supernova objects'
    )

    parser.add_argument("inputfile", help="A Faust .dsp file to be converted")

    parser.add_argument("-a", "--architecture", help="Use an alternative architecture file. If not set, it will use the default supercollider.cpp file that comes with faust.")

    parser.add_argument("-m", "--macosarch", help="Enforce a macOS architecture. Can be either arm64 or x86_64 (Rosetta on Mx sillicon)")
    parser.add_argument("-t", "--targetfolder", help="Put the generated files in this folder. If not used, it will put the files in the current working directory.")
    parser.add_argument("-n", "--noprefix", help="1 == Do not prefix the SuperCollider class and object with Faust. 0 == prefix. It is 1 by default, ie not using the Faust prefix.", type=int, choices=[0,1])
    parser.add_argument("-s", "--supernova", help="Compile with supernova plugin", action="store_true")
    parser.add_argument("-c", "--cpp", help="Copy cpp file to target directory after compilation.", action="store_true")
    parser.add_argument("-p", "--headerpath", default="./include", help="Path to SuperCollider headers. If no header path is supplied, the script will try to find the headers in common locations.")
    args = parser.parse_args()

    # Temporary folder for intermediary files
    tmp_folder = tempfile.TemporaryDirectory(prefix="faust.")

    # Generate supercollider class and help file
    noprefix = args.noprefix or 1
    scresult = faust2sc(args.inputfile, tmp_folder.name, noprefix, args.architecture)

    compile_supernova = args.supernova
    header_path = args.headerpath
    macosarch = args.macosarch

    # Compile the plugin objects
    compile(tmp_folder.name, scresult["cpp_file"], scresult["class"], compile_supernova, header_path, macosarch)

    # Move files to target
    env = faustoptflags()
    target = args.targetfolder or os.getcwd()

    # Move SuperCollider files
    shutil.copytree(path.join(tmp_folder.name, "Classes"), path.join(target, "Classes"), dirs_exist_ok=True)
    shutil.copytree(path.join(tmp_folder.name, "HelpSource"), path.join(target, "HelpSource"), dirs_exist_ok=True)

    # Move object files
    for objfile in os.listdir(tmp_folder.name):
        if objfile.endswith(env["EXT"]):
            shutil.move(path.join(tmp_folder.name, objfile), path.join(target, objfile))

    # Move cpp file
    copy_cpp = args.cpp or False
    if copy_cpp:
        shutil.move(scresult["cpp_file"], path.join(target, scresult["cpp_file"]))

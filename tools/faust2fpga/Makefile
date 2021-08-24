#DSP ?= /faust/karplus.dsp
#DSP ?= /faust/bypass.ds
#mydsp ?=echo-oussama
mydsp ?=var_delay
DSP ?= faust/${mydsp}.dsp
ORIGIN_DIR=${PWD}

all: bitstream
project: build/faust_v4_project/faust_v4_project.xpr
#ip: build/faust_v4_ip/faust_v4/syn/report/faust_v4_csynth.xml
ip: vhdl/faust.vhd
bitstream: build/faust_v4_project/faust_v4_project.runs/impl_1/main_wrapper.bit
faust: build/faust_v4_ip/faust_v4.cpp

clean:
	rm -rf build
	rm -rf vivado_*
	rm -rf vivado.*
	rm -rf *~
	rm -rf vhdl/faust.vhd

build/faust_v4_ip/faust_v4.cpp: $(DSP) fpga.cpp
	mkdir -p build/faust_v4_ip
	faust -lang c -light -os -a fpga.cpp -o $@ $(DSP)

# build/faust_v4_ip/faust_v4/syn/report/faust_v4_csynth.xml: build/faust_v4_ip/faust_v4.cpp  
# 	cd build && vivado_hls -f ../run_hls_v4.tcl

vhdl/faust.vhd: ${DSP}
	cd vhdl; faust -vhdl ../${DSP} --output-dir ./
	#cd vhdl; mv ${mydsp}.dsp.vhd faust.vhd


build/faust_v4_project/faust_v4_project.xpr:  vhdl/faust.vhd project_v4.tcl
	mkdir -p build
	cd build && vivado -mode batch -source ../project_v4.tcl -tclargs --origin_dir ${ORIGIN_DIR}

build/faust_v4_project/faust_v4_project.runs/impl_1/main_wrapper.bit:  build/faust_v4_project/faust_v4_project.xpr vhdl/faust.vhd
	cd build && vivado -mode batch -source ../build.tcl
	echo -e "\a"  #produce a beep

program: build/faust_v4_project/faust_v4_project.runs/impl_1/main_wrapper.bit
	vivado -mode batch -source program.tcl



dummy:

.PHONY: all clean dependents

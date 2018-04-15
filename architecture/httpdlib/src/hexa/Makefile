#
# This makefile is intended to embed style sheets and
# javascript code into cpp code
#

HTML := ../../html
SVG  := $(HTML)/js/svg

sources = $(wildcard $(SVG)/*.js)

#.INTERMEDIATE: jsscripts stylesheet


all: stylesheet.cpp jsscripts.cpp
	
clean :
	rm -f jsscripts jsscripts.js jsscripts.cpp
	rm -f stylesheet stylesheet.cpp	

# rules to generate the cpp files 
jsscripts.cpp : jsscripts
	xxd -i $<  $@

stylesheet.cpp : stylesheet
	xxd -i $<  $@

jsscripts : $(sources) $(SVG)/jquerysvg/jquery.svg.js
	cat $(SVG)/jquery-1.7.1.min.js > $@
	echo " " >> $@
	cat $(SVG)/jquerysvg/jquery.svg.min.js >> $@
	echo " " >> $@
	cat $(SVG)/jquerysvg/jquery.svgdom.min.js >> $@
	echo " " >> $@
	cat $(SVG)/faust_proto.js >> $@
	echo " " >> $@
	cat $(SVG)/faust_jquery_svg_backend.js >> $@
	echo " " >> $@
	cat $(SVG)/faust_mobile.js >> $@
	echo " " >> $@
	cat $(SVG)/faust_ui_inits.js >> $@
	echo " " >> $@
	cat $(SVG)/faust_load_external_file.js >> $@
	echo " " >> $@
	cat $(SVG)/faust_ui_objects.js >> $@
	echo " " >> $@
	cat $(SVG)/faust_ui_builder.js >> $@
	echo " " >> $@
	cat $(SVG)/faust_ui_interact.js >> $@
	echo " " >> $@
	cat $(SVG)/faust_ui_audio_bridge.js >> $@
	echo " " >> $@
	cat $(SVG)/faust_server_communication.js >> $@

# this intermediate file is required since the output is named using the file name
stylesheet:  $(SVG)/faust_css.css
	cat  $<  > $@
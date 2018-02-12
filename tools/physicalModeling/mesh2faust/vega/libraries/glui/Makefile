ifndef GLUI
GLUI=GLUI

ifndef CLEANFOLDER
CLEANFOLDER=GLUI
endif

include ../../Makefile-headers/Makefile-header

all: ../../libraries/glui/glui-2.35/src/lib/libglui.$(DYLIB_EXT)

../../libraries/glui/glui-2.35/src/lib/libglui.$(DYLIB_EXT):
	cd ../../libraries/glui/glui-2.35/src; g++ -O2 -I./ -I./include -I/usr/X11R6/include glui_add_controls.cpp glui_string.cpp glui.cpp glui_bitmap_img_data.cpp glui_bitmaps.cpp glui_button.cpp glui_edittext.cpp glui_commandline.cpp glui_checkbox.cpp glui_node.cpp glui_radio.cpp glui_statictext.cpp glui_panel.cpp glui_separator.cpp glui_spinner.cpp glui_control.cpp glui_column.cpp glui_translation.cpp glui_rotation.cpp glui_mouse_iaction.cpp glui_listbox.cpp glui_rollout.cpp glui_window.cpp arcball.cpp algebra3.cpp quaternion.cpp viewmodel.cpp glui_treepanel.cpp glui_tree.cpp glui_textbox.cpp glui_scrollbar.cpp glui_list.cpp glui_filebrowser.cpp $(DYLIB_FLAG) -fPIC -o libglui.$(DYLIB_EXT) $(SET_GLUI_RPATH) $(OPENGL_LIBS); mv libglui.$(DYLIB_EXT) lib/

ifeq ($(CLEANFOLDER), GLUI)
clean: cleanglui
endif

deepclean: cleanglui

cleanglui:
	cd ../../libraries/glui/glui-2.35/src; $(MAKE) clean; rm lib/libglui.$(DYLIB_EXT)

endif


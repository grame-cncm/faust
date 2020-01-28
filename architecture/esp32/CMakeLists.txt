idf_component_register(SRCS "esp32.cpp"
                       INCLUDE_DIRS "include"                       # Edit following two lines to set component requirements (see docs)
                       REQUIRES jdksmidi
                       PRIV_REQUIRES )
                       
set_source_files_properties(esp32.cpp
    			    PROPERTIES COMPILE_FLAGS
        		    -frtti )               

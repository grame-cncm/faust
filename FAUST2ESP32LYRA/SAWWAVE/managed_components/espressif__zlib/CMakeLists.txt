idf_component_register(INCLUDE_DIRS zlib SRC_DIRS zlib)

target_compile_options(${COMPONENT_LIB} PRIVATE  -Wno-unused-function)
target_compile_options(${COMPONENT_LIB} PRIVATE  -Wno-implicit-int)
target_compile_options(${COMPONENT_LIB} PRIVATE  -Wno-return-type)
target_compile_options(${COMPONENT_LIB} PRIVATE  -Wno-format-extra-args)
target_compile_options(${COMPONENT_LIB} PRIVATE  -Wno-unused-parameter)
target_compile_options(${COMPONENT_LIB} PRIVATE  -Wno-unused-const-variable)
target_compile_options(${COMPONENT_LIB} PRIVATE  -Wno-implicit-fallthrough)

target_compile_definitions(${COMPONENT_LIB} PRIVATE PPM_SUPPORTED)
target_compile_definitions(${COMPONENT_LIB} PRIVATE HAVE_MATH_H)
target_compile_definitions(${COMPONENT_LIB} PRIVATE HAVE_CTYPE_H)
target_compile_definitions(${COMPONENT_LIB} PRIVATE HAVE_UNISTD_H)
target_compile_definitions(${COMPONENT_LIB} PRIVATE HAVE_ERRNO_H)


idf_component_register( SRC_DIRS "."
                        INCLUDE_DIRS "."
                        REQUIRES cmake_utilities)

include(gcc)
include(gen_compressed_ota)
include(gen_single_bin)
include(package_manager)
include(relinker)
cu_pkg_define_version(${CMAKE_CURRENT_LIST_DIR})
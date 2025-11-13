# Build the main component (C++)
set(COMPONENT_SRCS "main.cpp" "FaustSawtooth.cpp")
set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component()
# Component dependencies are handled via idf_component.yml or COMPONENT_REQUIRES
# No need for target_link_libraries for ESP-IDF components

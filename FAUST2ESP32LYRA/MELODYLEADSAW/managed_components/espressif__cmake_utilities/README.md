# Cmake utilities

[![Component Registry](https://components.espressif.com/components/espressif/cmake_utilities/badge.svg)](https://components.espressif.com/components/espressif/cmake_utilities)

This component is aiming to provide some useful CMake utilities outside of ESP-IDF.

## Use

1. Add dependency of this component in your component or project's idf_component.yml.

    ```yml
    dependencies:
      espressif/cmake_utilities: "0.*"
    ```

2. Include the CMake file you need in your component's CMakeLists.txt after `idf_component_register`, or in your project's CMakeLists.txt

    ```cmake
    // Note: should remove .cmake postfix when using include(), otherwise the requested file will not found
    // Note: should place this line after `idf_component_register` function
    // only include the one you needed.
    include(package_manager)
    ```

3. Then you can use the corresponding CMake function which is provided by the CMake file.

## Supported features

1. [relinker](https://github.com/espressif/esp-iot-solution/blob/master/tools/cmake_utilities/docs/relinker.md)
2. [gen_compressed_ota](https://github.com/espressif/esp-iot-solution/blob/master/tools/cmake_utilities/docs/gen_compressed_ota.md)
3. [GCC Optimization](https://github.com/espressif/esp-iot-solution/blob/master/tools/cmake_utilities/docs/gcc.md)

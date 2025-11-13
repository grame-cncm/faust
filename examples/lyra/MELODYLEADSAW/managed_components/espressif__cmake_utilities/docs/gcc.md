# Link Time Optimization(LTO)

Link time optimization(LTO) improves the optimization effect of GCC, such as reducing binary size, increasing performance, and so on. For more details please refer to related [GCC documents](https://gcc.gnu.org/onlinedocs/gccint/LTO.html).

## Use

To use this feature, you need to include the required CMake file in your project's CMakeLists.txt after `project(XXXX)`.

```cmake
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(XXXX)

include(gcc)
```

The LTO feature is disabled by default. To use it, you should enable the option `CU_GCC_LTO_ENABLE` in menuconfig. Then specify target components or dependencies to be optimized by LTO after `include(gcc)` as follows:

```cmake
include(gcc)

cu_gcc_lto_set(COMPONENTS component_a component_b
               DEPENDS dependence_a dependence_b)

cu_gcc_string_1byte_align(COMPONENTS component_c component_d
                          DEPENDS dependence_c dependence_d)
```

Based on your requirement, set compiling optimization level in the option `COMPILER_OPTIMIZATION`.

* Note

    ```
    1. Reducing firmware size may decrease performance
    2. Increasing performance may increase firmware size
    3. Enable LTO cause compiling time cost increases a lot
    4. Enable LTO may increase task stack cost
    5. Enable string 1-byte align may decrease string process speed
    ```

## Limitation

At the linking stage, the LTO generates new function indexes instead of the file path as follows:

- LTO 

    ```txt
    .text          0x00000000420016f4        0x6 /tmp/ccdjwYMH.ltrans51.ltrans.o
                   0x00000000420016f4                app_main
    ```

- Without LTO

    ```txt
    .text.app_main 0x00000000420016f4        0x6 esp-idf/main/libmain.a(app_main.c.obj)
                   0x00000000420016f4                app_main
    ```

So tools used to relink functions between flash and IRAM can't affect these optimized components and dependencies again. It is recommended that users had better optimize application components and dependencies than kernel and hardware driver ones.

## Example

The example applies LTO in `light` of `esp-matter` because its application code is much larger. Add LTO configuration into project script `CMakeLists.txt` as follows:

```cmake

project(light)

include(gcc)

# Add
set(app_lto_components main chip esp_matter)
# Add
set(idf_lto_components lwip wpa_supplicant nvs_flash)
# Add
set(lto_depends mbedcrypto)

# Add
cu_gcc_lto_set(COMPONENTS ${app_lto_components} ${idf_lto_components} 
               DEPENDS ${lto_depends})
```

Configure `ESP32-C2` as the target platform, enable `CU_GCC_LTO_ENABLE` and `CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_DISABLE`, set `COMPILER_OPTIMIZATION` to be `-Os`.
Increase the `main` task stack size to `5120` by option `ESP_MAIN_TASK_STACK_SIZE`.
Compile the project, and then you can see the firmware size decrease a lot:

Option | Firmware size | Stask cost
|:-:|:-:|:-:|
 -Os | 1,113,376 | 2508
 -Os + LTO | 1,020,640 | 4204

Then add `cu_gcc_string_1byte_align` after `cu_gcc_lto_set`:

```cmake
# Add
cu_gcc_lto_set(COMPONENTS ${app_lto_components} ${idf_lto_components} 
               DEPENDS ${lto_depends})

cu_gcc_string_1byte_align(COMPONENTS ${app_lto_components} ${idf_lto_components} 
                          DEPENDS ${lto_depends})
```

Build the project and the firmware size is:

Option | Firmware size |
|:-:|:-:|
 -Os + LTO | 1,020,640 |
 -Os + LTO + string 1-byte align | 1,018,340 |

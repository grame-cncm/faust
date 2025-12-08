cmake_policy(SET CMP0048 NEW)
cmake_minimum_required(VERSION 3.25)

#add_definitions(-DFILEIO_ENABLE_CSTDIO_READER)
add_definitions(-DFILEIO_ENABLE_FATFS_READER)

option(FLASH_TYPE "Type of flashing method" "FLASH")

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(LIBDAISY_PATH ${LIBDAIST_DIR})
set(DAISYSP_PATH ${DAISYSP_DIR})
set(CMSISDSP_PATH ${LIBDAISY_PATH}/Drivers/CMSIS-DSP/Source)
set(CMSISCORE ${LIBDAISY_PATH}/Drivers/CMSIS_5/CMSIS/Core)

set(C_DEFS ${C_DEFS} -DUSE_HAL_DRIVER -DSTM32H750xx -DHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -DARM_MATH_CM7 -DUSE_FULL_LL_DRIVER) 
set(CFLAGS ${C_DEFS} -g -ggdb -MMD -MP)
set(CPPFLAGS ${CFLAGS} -fno-exceptions -fasm -finline -finline-functions-called-once -fshort-enums -fno-move-loop-invariants -fno-unwind-tables -fno-rtti -Wno-register)

set(SOURCE src/main.cpp)
if(${FLASH_TYPE} STREQUAL "QSPI")
    set(LINKER_SCRIPT ${LIBDAISY_PATH}/core/STM32H750IB_qspi.lds)
    set(CPPFLAGS ${CPPFLAGS} -DBOOT_APP)
    set(SOURCE ${SOURCE} ${LIBDAISY_PATH}/core/startup_stm32h750xx.c)
elseif(${FLASH_TYPE} STREQUAL "SRAM")
    set(LINKER_SCRIPT ${LIBDAISY_PATH}/core/STM32H750IB_sram.lds)
    set(CPPFLAGS ${CPPFLAGS} -DBOOT_APP)
    set(SOURCE ${SOURCE} ${LIBDAISY_PATH}/core/startup_stm32h750xx.c)
else()
    set(LINKER_SCRIPT ${LIBDAISY_PATH}/core/STM32H750IB_flash.lds)
endif()


message(STATUS "LIBDAISY_PATH: ${LIBDAISY_PATH}")
message(STATUS "DAISYSP_PATH: ${DAISYSP_PATH}")


# IMPORTANT - CHANGE THIS PATH TO YOUR GCC INSTALLATION
set(TOOLCHAIN_PREFIX "$ENV{HOME}/Documents/Electroacoustique/daisy/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-g++")
#set(TOOLCHAIN_PREFIX "$ENV{HOME}/Documents/Electroacoustique/daisy/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc")
set(CMAKE_TOOLCHAIN_FILE ${LIBDAISY_PATH}/cmake/toolchains/stm32h750xx.cmake)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(daisy_program VERSION 0.1 LANGUAGES C CXX ASM)

# This is the target name of the firmware binary
set(FIRMWARE_NAME daisy_firmware)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# OPENOCD
set(CHIPSET stm32h7x)
set(OCD openocd)

# IMPORTANT - CHANGE THIS PATH TO YOUR OPENOCD SCRIPTS FOLDER
set(OCD_DIR "/usr/share/openocd/scripts")
set(PGM_DEVICE interface/stlink.cfg)
set(OCDFLAGS -f ${PGM_DEVICE} -f target/${CHIPSET}.cfg)
set(OCD_PROGRAM ${OCD} -s ${OCD_DIR} ${OCDFLAGS} -c "program ${FIRMWARE_NAME}.elf verify reset exit")

add_subdirectory(${LIBDAISY_PATH})

# We're compiling libDaisy with -Os to save space
target_compile_options(daisy
    PUBLIC
    -O2
)

add_subdirectory(${DAISYSP_PATH}) 

set(Q_BUILD_IO OFF CACHE BOOL "Disable IO" FORCE)
set(Q_BUILD_EXAMPLES OFF CACHE BOOL "Disable Examples" FORCE) 
set(Q_BUILD_TEST OFF CACHE BOOL "Disable Tests" FORCE)
add_subdirectory(${Q_PATH})
add_compile_definitions(Q_DONT_USE_THREADS)
target_compile_options(libq INTERFACE -fexceptions)

add_subdirectory(${CMSISDSP_PATH})

add_executable(${FIRMWARE_NAME} ${SOURCE})
target_compile_options(${FIRMWARE_NAME}
    PUBLIC 
    -O2
    -Wall
    -Wno-attributes 
    -Wno-strict-aliasing
    -Wno-maybe-uninitialized
    -Wno-missing-attributes
    -Wno-stringop-overflow
    -Wno-error=reorder
    -Wno-error=sign-compare
    #-fexceptions
    -DQ_DONT_USE_THREADS=1
    ${CPPFLAGS}
    )

target_include_directories(${FIRMWARE_NAME} PUBLIC
    src
)

target_link_libraries(${FIRMWARE_NAME}
    PUBLIC
    daisy
    DaisySP
    libq
    CMSISDSP
    c
    m
    nosys
)

set_target_properties(${FIRMWARE_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    SUFFIX ".elf"
    LINK_DEPENDS ${LINKER_SCRIPT}
)

target_link_options(${FIRMWARE_NAME} PUBLIC
    -T ${LINKER_SCRIPT}
    -Wl,-Map=${FIRMWARE_NAME}.map,--cref
    -Wl,--check-sections
    -Wl,--unresolved-symbols=report-all
    -Wl,--warn-common
    -Wl,--warn-section-align
    -Wl,--print-memory-usage
    --specs=nano.specs
    --specs=nosys.specs
    -mthumb
    -Wl,--gc-sections
    -Wl,--cref
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    -mcpu=cortex-m7
    -u _printf_float
)
#MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
#-Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -Wl,--print-memory-usage
# fpu
#FPU = -mfpu=fpv5-d16

# float-abi
#FLOAT-ABI = -mfloat-abi=hard
#CPU = -mcpu=cortex-m7

add_custom_command(TARGET ${FIRMWARE_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
    ARGS -O ihex
    -S ${FIRMWARE_NAME}.elf
    ${FIRMWARE_NAME}.hex
    BYPRODUCTS
    ${FIRMWARE_NAME}.hex
    COMMENT "Generating HEX image"
    VERBATIM)

add_custom_command(TARGET ${FIRMWARE_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
    ARGS -O binary
    -S ${FIRMWARE_NAME}.elf
    ${FIRMWARE_NAME}.bin
    BYPRODUCTS
    ${FIRMWARE_NAME}.bin
    COMMENT "Generating binary image"
    VERBATIM)

add_custom_target(flash-st-link
    COMMAND ${OCD_PROGRAM}
    DEPENDS ${FIRMWARE_NAME}
    COMMENT "Flashing ${FIRMWARE_NAME}.elf with ST-Link"
    VERBATIM
)

set(FLASH_ADDRESS 0x08000000)
set(QSPI_ADDRESS 0x90040000)
set(SRAM_ADDRESS 0x90040000)
set(TARGET_BIN ${FIRMWARE_NAME}.bin)
set(USBPID df11)
set(STMPID df11)
set(BOOT_BIN dsy_bootloader_v6_3-intdfu-2000ms.bin)

message(STATUS "Firmware name : ${FIRMWARE_NAME}")
message(STATUS "Target bin : ${TARGET_BIN}")

message(STATUS "COMMAND dfu-util -a 0 -s ${QSPI_ADDRESS}:leave -D ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_BIN} -d ,0483:${USBPID}" )

add_custom_target(flash-dfu
    COMMAND dfu-util -a 0 -s ${FLASH_ADDRESS}:leave -D ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_BIN} -d ,0483:${USBPID}
    DEPENDS ${FIRMWARE_NAME}
    COMMENT "Flashing ${FIRMWARE_NAME}.elf with DFU"
    VERBATIM
)

add_custom_target(flash-sram
    COMMAND dfu-util -a 0 -s ${SRAM_ADDRESS}:leave -D ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_BIN} -d ,0483:${USBPID}
    DEPENDS ${FIRMWARE_NAME}
    COMMENT "Flashing ${FIRMWARE_NAME}.elf with DFU"
    VERBATIM
)

message(STATUS     "dfu-util -a 0 -s ${FLASH_ADDRESS}:leave -D ${LIBDAISY_PATH}/core/${BOOT_BIN} -d ,0483:${STMPID}" )
add_custom_target(flash-bootloader
    COMMAND dfu-util -a 0 -s ${FLASH_ADDRESS}:leave -D ${LIBDAISY_PATH}/core/${BOOT_BIN} -d ,0483:${STMPID}
    DEPENDS ${FIRMWARE_NAME}
    COMMENT "Flashing ${FIRMWARE_NAME}.elf with DFU"
    VERBATIM
)

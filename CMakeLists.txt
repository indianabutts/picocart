# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/yassir/dev/utils/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(PicoCart C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(PicoCart)

pico_generate_pio_header(PicoCart ${CMAKE_CURRENT_SOURCE_DIR}/includes/address_bus/address_bus.pio)

pico_set_program_name(PicoCart "PicoCart")
pico_set_program_version(PicoCart "0.1")

pico_enable_stdio_uart(PicoCart 1)
pico_enable_stdio_usb(PicoCart 0)


# Add the standard include files to the build
target_include_directories(PicoCart PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

target_sources(PicoCart PUBLIC
  PicoCart.c
  includes/sd_hw.c
  includes/address_bus/address_bus.c
)
add_subdirectory(libs/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)

# Add any user requested libraries
target_link_libraries(PicoCart 
  pico_stdlib
  pico_multicore
  hardware_dma
  hardware_spi
  hardware_pio
  FatFs_SPI
        )

pico_add_extra_outputs(PicoCart)


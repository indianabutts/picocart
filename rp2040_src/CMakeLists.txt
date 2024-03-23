# Generated Cmake Pico project file
cmake_minimum_required(VERSION 3.12)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)


project(msx2040 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
IF(DEFINED ENV{PICO_SDK_PATH})
ELSE()
set(PICO_SDK_PATH "/home/yassir/dev/utils/pico-sdk")
ENDIF()
set(PICO_BOARD pico CACHE STRING "Board type")



if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()


set(MSX2040_PATH ${PROJECT_SOURCE_DIR})

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_compile_options(
  -Wall
  -Wno-format
#  -Wno-unused-function
)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-Wno-maybe-unitialized)
endif()

add_subdirectory(debug_board)
add_subdirectory(core)

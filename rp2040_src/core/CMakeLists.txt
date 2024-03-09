add_executable(
  core
)



pico_generate_pio_header(core ${CMAKE_CURRENT_LIST_DIR}/includes/address_bus/address_bus.pio)

pico_set_program_name(core "MSX-2040")
pico_set_program_version(core "0.1")

pico_enable_stdio_uart(core 1)
pico_enable_stdio_usb(core 0)

# Add the standard include files to the build
target_include_directories(core PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)


target_sources(core PRIVATE
  core.c
  includes/sd_hw.c
  includes/address_bus/address_bus.c
)

add_subdirectory(libs/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)


target_link_libraries(core PRIVATE
  pico_stdlib
  hardware_spi
  hardware_pio
  FatFs_SPI
)

pico_add_extra_outputs(core)

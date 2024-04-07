add_executable(
  core_pio
)



#pico_generate_pio_header(core_pio ${CMAKE_CURRENT_LIST_DIR}/includes/address_bus/address_bus.pio)

pico_set_program_name(core_pio "MSX-2040")
pico_set_program_version(core_pio "0.1")

pico_enable_stdio_uart(core_pio 1)
pico_enable_stdio_usb(core_pio 0)

# Add the standard include files to the build
target_include_directories(core_pio PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)


target_sources(core_pio PRIVATE
  core_pio.c
  includes/sd_hw.c
  includes/gpio.c
)



target_link_libraries(core_pio PRIVATE
  pico_stdlib
  hardware_spi
  hardware_pio
  FatFs_SPI
)

pico_add_extra_outputs(core_pio)

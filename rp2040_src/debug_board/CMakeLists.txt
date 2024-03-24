add_executable(
  debug_board
  debug_board.c
  includes/ssd1306.c
)

pico_enable_stdio_uart(debug_board 0)
pico_enable_stdio_usb(debug_board 1)


target_link_libraries(
  debug_board
  pico_stdlib
  hardware_i2c
)

pico_add_extra_outputs(debug_board)



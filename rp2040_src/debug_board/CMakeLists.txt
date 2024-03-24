add_executable(
  debug_board
  debug_board.c
  includes/ssd1306.c
)

target_link_libraries(
  debug_board
  pico_stdlib
  hardware_i2c
)

pico_add_extra_outputs(debug_board)



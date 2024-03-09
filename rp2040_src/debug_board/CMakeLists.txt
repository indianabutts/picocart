add_executable(
  debug_board
  debug_board.c
)

target_link_libraries(debug_board pico_stdlib)

pico_add_extra_outputs(debug_board)



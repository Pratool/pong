find_package(SFML REQUIRED COMPONENTS system window graphics)

add_executable(game
  game.cc
)

target_link_libraries(game
  config_tools
  kinematics
  sfml-graphics
)

install(
  TARGETS game
  DESTINATION bin
)

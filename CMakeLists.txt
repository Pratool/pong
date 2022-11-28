cmake_minimum_required(VERSION 3.16)

project("Pong")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wswitch-enum -Werror")

find_package(SFML REQUIRED COMPONENTS system window graphics)

add_executable(main
  main.cc
)

target_link_libraries(main
  config_tools
  kinematics
  sfml-graphics
)

install(
  TARGETS main
  DESTINATION bin
)

install(
  DIRECTORY resources/
  DESTINATION resources
)

add_subdirectory(config_tools)
add_subdirectory(kinematics)

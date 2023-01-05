cmake_minimum_required(VERSION 3.16)

project("Pong")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wswitch-enum -Werror")

install(
  DIRECTORY resources/
  DESTINATION resources
)

add_subdirectory(config_tools)
add_subdirectory(game)
add_subdirectory(kinematics)

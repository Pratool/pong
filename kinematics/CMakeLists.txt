find_package(SFML REQUIRED COMPONENTS system)

add_library(kinematics
  src/ball.cc
  src/paddle.cc
)

target_include_directories(kinematics
  PUBLIC $<INSTALL_INTERFACE:include>
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(kinematics
  PUBLIC sfml-system
)

install(
  TARGETS kinematics
  EXPORT kinematicsConfig
  DESTINATION lib
)

install(
  EXPORT kinematicsConfig
  DESTINATION share/kinematics/cmake
)

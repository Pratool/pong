add_library(config_tools
  src/config_tools.cc
)

target_include_directories(config_tools
  PUBLIC $<INSTALL_INTERFACE:include>
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(config_tools
  PRIVATE stdc++fs
)

install(
  TARGETS config_tools
  EXPORT config_toolsConfig
  DESTINATION lib
)

install(
  EXPORT config_toolsConfig
  DESTINATION share/config_tools/cmake
)

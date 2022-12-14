cmake_minimum_required(VERSION 3.6)

project("Pong 3rd Party Dependencies")

include(ExternalProject)

set(CMAKE_USER_ARGS "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE};")
list(APPEND CMAKE_USER_ARGS -DCMAKE_PREFIX_PATH=${CMAKE_INSTALL_PREFIX})
list(APPEND CMAKE_USER_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX})
list(APPEND CMAKE_USER_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER})
list(APPEND CMAKE_USER_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER})

externalproject_add(openal-soft
  DOWNLOAD_NO_PROGRESS ON
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/openal-soft
  URL "https://github.com/kcat/openal-soft/archive/refs/tags/1.22.2.tar.gz"
  URL_HASH SHA256=3e58f3d4458f5ee850039b1a6b4dac2343b3a5985a6a2e7ae2d143369c5b8135
  CMAKE_ARGS ${CMAKE_USER_ARGS}
)

# TODO Build libvorbis from source.

externalproject_add(flac
  DOWNLOAD_NO_PROGRESS ON
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/flac
  URL "https://github.com/xiph/flac/archive/refs/tags/1.4.1.tar.gz"
  URL_HASH SHA256=acbb966abaaf3f65b6f37f0f40130d061d2bfa6a0212366466a416f221567878
  CMAKE_ARGS
    ${CMAKE_USER_ARGS}
    -DINSTALL_MANPAGES=OFF
    -DBUILD_SHARED_LIBS=ON
)

externalproject_add(sfml
  DOWNLOAD_NO_PROGRESS ON
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/sfml
  URL "https://www.sfml-dev.org/files/SFML-2.5.1-sources.zip"
  URL_HASH SHA256=bf1e0643acb92369b24572b703473af60bac82caf5af61e77c063b779471bb7f
  CMAKE_ARGS
    ${CMAKE_USER_ARGS}
)
add_dependencies(sfml flac openal-soft)

externalproject_add(boost
  DOWNLOAD_NO_PROGRESS ON
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/boost
  URL "https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.bz2"
  URL_HASH SHA256=1e19565d82e43bc59209a168f5ac899d3ba471d55c7610c677d4ccf2c9c500c0
  BUILD_IN_SOURCE ON
  CONFIGURE_COMMAND
    LD_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib:$ENV{LD_LIBRARY_PATH}
    PATH=${CMAKE_INSTALL_PREFIX}/bin:$ENV{PATH}
    ./bootstrap.sh
    --prefix=${CMAKE_INSTALL_PREFIX}
    --with-python-root=${CMAKE_INSTALL_PREFIX}
    --with-python=python3
  BUILD_COMMAND ./b2 install
    --prefix=${CMAKE_INSTALL_PREFIX}
    variant=release
    runtime-link=shared
  INSTALL_COMMAND ""
)

cmake_minimum_required(VERSION 3.6)

project("Pong 3rd Party Dependencies")

include(ExternalProject)

externalproject_add(openal-soft
  DOWNLOAD_NO_PROGRESS ON
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/openal-soft
  URL "https://github.com/kcat/openal-soft/archive/refs/tags/1.22.2.tar.gz"
  URL_HASH SHA256=3e58f3d4458f5ee850039b1a6b4dac2343b3a5985a6a2e7ae2d143369c5b8135
  CMAKE_ARGS
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
    -DCMAKE_PREFIX_PATH:PATH=${CMAKE_INSTALL_PREFIX}
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
)

# TODO Build libvorbis from source.

externalproject_add(flac
  DOWNLOAD_NO_PROGRESS ON
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/flac
  URL "https://github.com/xiph/flac/archive/refs/tags/1.4.1.tar.gz"
  URL_HASH SHA256=acbb966abaaf3f65b6f37f0f40130d061d2bfa6a0212366466a416f221567878
  CMAKE_ARGS
    -DINSTALL_MANPAGES=OFF
    -DBUILD_SHARED_LIBS=ON
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
    -DCMAKE_PREFIX_PATH:PATH=${CMAKE_INSTALL_PREFIX}
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
)

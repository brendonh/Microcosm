cmake_minimum_required (VERSION 2.8)
project (Microcosm)

# XXX TODO -- FindReckoner.cmake?
set(RECKONER_DIR "${CMAKE_BINARY_DIR}/../reckoner")

set(MICROCOSM_COMMON_DIR "${Microcosm_SOURCE_DIR}/common")

set(CMAKE_MODULE_PATH ${Microcosm_SOURCE_DIR}/../cmake/modules ${CMAKE_MODULE_PATH})
include(MacroOutOfSourceBuild)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")

include_directories("${RECKONER_DIR}/include")
link_directories("${RECKONER_DIR}/lib")

set(CMAKE_INSTALL_PREFIX "dist")
set(CMAKE_INSTALL_RPATH "${RECKONER_DIR}/lib")

subdirs(common)
subdirs(client)
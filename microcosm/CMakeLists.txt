cmake_minimum_required (VERSION 2.8)
project (Microcosm)

set(MICROCOSM_COMMON_DIR "${Microcosm_SOURCE_DIR}/common")

set(CMAKE_MODULE_PATH ${Microcosm_SOURCE_DIR}/../cmake/modules ${CMAKE_MODULE_PATH})
include(MacroOutOfSourceBuild)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")

subdirs(client)
cmake_minimum_required (VERSION 2.8)
project (MicrocosmCommon)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")

file(GLOB_RECURSE MicrocosmCommon_SOURCES "${MicrocosmCommon_SOURCE_DIR}/*.cpp")

add_definitions(-Wall -Wextra -pedantic -Werror)

set(LIBS ${LIBS} reckoner-common)

add_library(microcosm-common ${MicrocosmCommon_SOURCES})
add_dependencies(microcosm-common reckoner-common reckoner-server microcosm-proto)
target_link_libraries(microcosm-common ${LIBS})

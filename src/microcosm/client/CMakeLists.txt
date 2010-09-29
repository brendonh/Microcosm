cmake_minimum_required (VERSION 2.8)
project (MicrocosmClient)

find_package(SFML REQUIRED COMPONENTS System Window Graphics)

include_directories(${SFML_INCLUDE_DIR})
set(LIBS ${LIBS} ${SFML_LIBRARY})

set(LIBS ${LIBS} GLU)

set(LIBS ${LIBS} microcosm-common)

file(GLOB_RECURSE MicrocosmClient_SOURCES "${MicrocosmClient_SOURCE_DIR}/*.cpp")

add_executable(Microcosm ${MicrocosmClient_SOURCES} ${MicrocosmCommon_SOURCES})
target_link_libraries(Microcosm ${LIBS})

install(TARGETS Microcosm RUNTIME DESTINATION "bin")

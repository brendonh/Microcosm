cmake_minimum_required (VERSION 2.8)
project (MicrocosmClient)

#SET(SFML_STATIC true)
find_package(SFML REQUIRED COMPONENTS System Window Graphics)
include_directories(${SFML_INCLUDE_DIRS})
set(LIBS ${LIBS} ${SFML_LIBRARY})

find_package(Box2D REQUIRED)
include_directories(${Box2D_INCLUDE_DIRS})
set(LIBS ${LIBS} Box2D)

set(LIBS ${LIBS} GLU)

set(LIBS ${LIBS} microcosm-common)

file(GLOB_RECURSE MicrocosmClient_SOURCES "${MicrocosmClient_SOURCE_DIR}/src/*.cpp")
include_directories("${MicrocosmCommon_SOURCE_DIR}/src")
include_directories("src")

add_definitions(-Wall -Wextra -pedantic -Werror)

add_executable(Microcosm ${MicrocosmClient_SOURCES})
target_link_libraries(Microcosm ${LIBS})

install(TARGETS Microcosm RUNTIME DESTINATION "bin")

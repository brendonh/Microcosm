cmake_minimum_required (VERSION 2.8)
project (MicrocosmClient)

find_package(SFML REQUIRED COMPONENTS Graphics Window System)
include_directories(${SFML_INCLUDE_DIRS})
set(LIBS ${LIBS} ${SFML_LIBRARY})

find_package(Box2D REQUIRED)
include_directories(${Box2D_INCLUDE_DIRS})
set(LIBS ${LIBS} Box2D)

set(LIBS ${LIBS} GLU)

file(GLOB_RECURSE MicrocosmClient_SOURCES "${MicrocosmClient_SOURCE_DIR}/src/*.cpp")
include_directories("src")

add_definitions(-Wall -Wextra -pedantic -Werror)


add_executable(Microcosm ${MicrocosmClient_SOURCES})
target_link_libraries(Microcosm ${LIBS})

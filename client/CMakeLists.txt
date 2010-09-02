cmake_minimum_required (VERSION 2.8)
project (MicrocosmClient)

set(CMAKE_MODULE_PATH ${MicrocosmClient_SOURCE_DIR}/../cmake/modules ${CMAKE_MODULE_PATH})
include(MacroOutOfSourceBuild)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")

SET(SFML_VERSION 2)
find_package(SFML REQUIRED COMPONENTS Graphics Window System)
include_directories(${SFML_INCLUDE_DIRS})
set(LIBS ${LIBS} ${SFML_LIBRARY})

find_package(Box2D REQUIRED)
include_directories(${Box2D_INCLUDE_DIRS})
set(LIBS ${LIBS} Box2D)

file(GLOB MicrocosmClient_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
include_directories(MicrocosmClient include)

add_definitions(-Wall -Wextra -pedantic -Werror)


add_executable(Microcosm ${MicrocosmClient_SOURCES})
target_link_libraries(Microcosm ${LIBS})

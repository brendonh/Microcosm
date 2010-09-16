cmake_minimum_required (VERSION 2.8)
project (Microcosm)

set(RECKONER_DIR "${CMAKE_BINARY_DIR}/../reckoner")

set(CMAKE_MODULE_PATH "${Microcosm_SOURCE_DIR}/../cmake/modules" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${RECKONER_DIR}/share/cmake/modules" ${CMAKE_MODULE_PATH})

include(MacroOutOfSourceBuild)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")


include_directories("${RECKONER_DIR}/include")
link_directories("${RECKONER_DIR}/lib")


find_package(ENet REQUIRED)
include_directories(${ENet_INCLUDE_DIR})
set(LIBS ${LIBS} enet)

find_package(Box2D REQUIRED)
include_directories(${Box2D_INCLUDE_DIRS})
set(LIBS ${LIBS} Box2D)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})
set(LIBS ${LIBS} pthread ${PROTOBUF_LIBRARY})

include_directories(${Microcosm_SOURCE_DIR})

set(CMAKE_INSTALL_PREFIX "dist")

add_subdirectory("microcosm/common")
add_subdirectory("microcosm/client")
add_subdirectory("microcosm/server")

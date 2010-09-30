cmake_minimum_required (VERSION 2.8)
project (Microcosm)

set(CMAKE_MODULE_PATH "${Microcosm_SOURCE_DIR}/../cmake/modules" ${CMAKE_MODULE_PATH})


# When using reckoner's install
# set(RECKONER_DIR "${CMAKE_BINARY_DIR}/../reckoner")
# set(CMAKE_MODULE_PATH "${RECKONER_DIR}/share/cmake/modules" ${CMAKE_MODULE_PATH})
# include_directories("${RECKONER_DIR}/include")
# link_directories("${RECKONER_DIR}/lib")

# For now
set(RECKONER_BASE_DIR "${CMAKE_BINARY_DIR}/../../reckoner")
set(RECKONER_PROTO_DIR "${RECKONER_BASE_DIR}/src/reckoner/proto")
set(RECKONER_PROTO_BIN_DIR "${RECKONER_BASE_DIR}/build/reckoner/proto")
set(CMAKE_MODULE_PATH "${RECKONER_BASE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

include_directories("${RECKONER_BASE_DIR}/src")
include_directories("${RECKONER_BASE_DIR}/build")

link_directories("${RECKONER_BASE_DIR}/build/reckoner/common")
link_directories("${RECKONER_BASE_DIR}/build/reckoner/server")
link_directories("${RECKONER_BASE_DIR}/build/reckoner/client")

# Ensure we re-link when these change
add_library(reckoner-common STATIC IMPORTED)
set_property(TARGET reckoner-common PROPERTY
  IMPORTED_LOCATION "${RECKONER_BASE_DIR}/build/reckoner/common/libreckoner-common.a")
add_library(reckoner-server STATIC IMPORTED)
set_property(TARGET reckoner-server PROPERTY
  IMPORTED_LOCATION "${RECKONER_BASE_DIR}/build/reckoner/server/libreckoner-server.a")
add_library(reckoner-client STATIC IMPORTED)
set_property(TARGET reckoner-client PROPERTY
  IMPORTED_LOCATION "${RECKONER_BASE_DIR}/build/reckoner/client/libreckoner-client.a")


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

set(CMAKE_CXX_COMPILER c++)
add_definitions(-std=c++0x -Wall -Wextra -pedantic -Winline)

add_subdirectory("microcosm/common")
add_subdirectory("microcosm/client")
add_subdirectory("microcosm/server")

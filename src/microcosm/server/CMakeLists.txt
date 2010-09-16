cmake_minimum_required (VERSION 2.8)
project (MicrocosmServer)
file(GLOB_RECURSE MicrocosmServer_SOURCES "${MicrocosmServer_SOURCE_DIR}/*.cpp")

add_definitions(-Wall -Wextra -pedantic -Werror)

set(LIBS reckoner-server reckoner-common ${LIBS})

add_executable(MicrocosmServer ${MicrocosmServer_SOURCES} ${MicrocosmCommon_SOURCES})
add_dependencies(MicrocosmServer microcosm-common reckoner-server)
target_link_libraries(MicrocosmServer ${LIBS})

install(TARGETS MicrocosmServer RUNTIME DESTINATION "bin")

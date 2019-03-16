cmake_minimum_required(VERSION 2.6)

Project(PantherExpress)

include_directories(${PantherExpress_SOURCE_DIR}/include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

file(GLOB SOURCES "src/*.cpp")

find_package(PkgConfig)
pkg_check_modules(LIBMICROHTTPD REQUIRED libmicrohttpd)

include_directories(${LIBMICROHTTPD_INCLUDE_DIRS})
link_directories(${LIBMICROHTTPD_LIBRARY_DIRS})

add_executable(PantherExpress ${SOURCES})
add_definitions(${LIBMICROHTTPD_CFLAGS_OTHER})
target_link_libraries(PantherExpress ${LIBMICROHTTPD_LIBRARIES})

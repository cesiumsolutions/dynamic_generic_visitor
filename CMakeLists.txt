cmake_minimum_required(VERSION 3.0)
project(generic_dynamic_visitor)

set( CMAKE_DEBUG_POSTFIX d )
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

find_package(
    Boost REQUIRED
    filesystem
    system
)
include_directories( ${Boost_INCLUDE_DIR} ./libs )

add_subdirectory( libs )
add_subdirectory( examples )

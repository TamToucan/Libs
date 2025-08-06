cmake_minimum_required(VERSION 3.20)
project(Libs)

set(FETCHCONTENT_QUIET OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

function(BUILD_LIB libname)
    set(options)
    set(one_value_args)
    set(multi_value_args DEPENDS)
    cmake_parse_arguments(ARG "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

    # Grab source files
    file(GLOB_RECURSE srcs CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.C"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    )

    add_library(${libname} STATIC ${srcs})

    # Always add this lib's own directory for headers
    target_include_directories(${libname} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

    # Determine Util path based on super-repo or standalone
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../Util")
	    message(STATUS "###### USE" "${CMAKE_CURRENT_SOURCE_DIR}/../Util")
        target_include_directories(${libname} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../Util")
    elseif(EXISTS "${CMAKE_SOURCE_DIR}/libs-src/lib/Util")
	    message(STATUS "###### USE " "${CMAKE_SOURCE_DIR}/libs-src/lib/Util")
        target_include_directories(${libname} PUBLIC "${CMAKE_SOURCE_DIR}/libs-src/lib/Util")
    elseif(EXISTS "${CMAKE_SOURCE_DIR}/../Util")
	    message(STATUS "###### USE " "${CMAKE_SOURCE_DIR}/../Util")
        target_include_directories(${libname} PUBLIC "${CMAKE_SOURCE_DIR}/../Util")
    else()
        message(FATAL_ERROR "Cannot locate Util directory for ${libname}")
    endif()

    # Link explicitly declared deps (excluding Util)
    foreach(dep IN LISTS ARG_DEPENDS)
        target_link_libraries(${libname} PUBLIC ${dep})
    endforeach()
endfunction()

add_subdirectory(lib)
    

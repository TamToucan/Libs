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

    # Source files
    file(GLOB_RECURSE srcs CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.C"
    )
    add_library(${libname} STATIC ${srcs})

    # Include this lib's own headers
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}")
        target_include_directories(${libname} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
	message(STATUS "------------------ ADD OWN")
    endif()

    # Always include Util headers — try both monorepo and nested FetchContent paths
    if(EXISTS "${CMAKE_SOURCE_DIR}/lib/Util")
	    message(STATUS "######################## Using mono lib/Util")
        # monorepo case
        target_include_directories(${libname} PUBLIC "${CMAKE_SOURCE_DIR}/lib/Util")
    elseif(EXISTS "${PROJECT_SOURCE_DIR}/../Util")
	    message(STATUS "######################## Using Proj Source ../Util")
        # fallback case
        target_include_directories(${libname} PUBLIC "${PROJECT_SOURCE_DIR}/../Util")
    elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../Util")
	    message(STATUS "Using CUR Source ../Util")
        target_include_directories(${libname} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../Util")
    elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../../../libs-src/lib/Util")
	    message(STATUS "######################## Using 3 UP lib-src /Util")
        # this catches FetchContent structure like:
        # _deps/libs-src/lib/MathStuff/
        target_include_directories(${libname} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../../../libs-src/lib/Util")
    else()
	    message(STATUS "######################## NOT FOUND")
        message(WARNING "Could not locate Util include path for ${libname}")
    endif()

    # Link against Util target if it exists and not self
    if(TARGET Util AND NOT "${libname}" STREQUAL "Util")
        target_link_libraries(${libname} PUBLIC Util)
    endif()

    # Add additional dependencies
    foreach(dep IN LISTS ARG_DEPENDS)
        target_link_libraries(${libname} PUBLIC ${dep})
    endforeach()
endfunction()

add_subdirectory(lib)

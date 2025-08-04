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

    # Gather source files
    file(GLOB_RECURSE srcs CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.C"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    )

    add_library(${libname} STATIC ${srcs})

    # Add own include path (headers are in same dir as sources)
    target_include_directories(${libname} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

    # Add include paths and link for declared dependencies
    foreach(dep IN LISTS ARG_DEPENDS)
        # Try to find the dep's directory relative to this library
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../${dep}")
            target_include_directories(${libname} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../${dep}")
        elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../../../libs-src/lib/${dep}")
            target_include_directories(${libname} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../../../libs-src/lib/${dep}")
        else()
            message(WARNING "Include path for dependency '${dep}' not found from ${libname}")
        endif()

        # Link against the dependency if it's a known CMake target
        if(TARGET ${dep})
            target_link_libraries(${libname} PUBLIC ${dep})
        endif()
    endforeach()
endfunction()

add_subdirectory(lib)

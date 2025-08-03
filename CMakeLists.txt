cmake_minimum_required(VERSION 3.20)

project(Libs)

set(FETCHCONTENT_QUIET OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


function(BUILD_LIB)
    if(${ARGC} GREATER 1)
        message(FATAL_ERROR "BUILD_LIB takes 0 or 1 argument")
    endif()

    if(${ARGC} EQUAL 1)
        set(libname "${ARGV0}")
    else()
        # Default to the name of the current source dir (e.g., Algo, PCG)
        get_filename_component(libname "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
    endif()

    set(lib_src_dir "${CMAKE_CURRENT_SOURCE_DIR}")
    set(lib_include_dir "${CMAKE_CURRENT_SOURCE_DIR}")

    file(GLOB_RECURSE srcs CONFIGURE_DEPENDS
	    "${lib_src_dir}/*.c"
	    "${lib_src_dir}/*.C"
	    "${lib_src_dir}/*.cpp")

    if(NOT srcs)
        message(WARNING "No source files found for ${libname} in ${lib_src_dir}")
    endif()

    add_library(${libname} STATIC ${srcs})

    target_include_directories(${libname} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/${lib}/include
        ${CMAKE_SOURCE_DIR}/lib/Util
    )

endfunction()

add_subdirectory(lib)

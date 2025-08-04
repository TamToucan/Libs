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
    )
    add_library(${libname} STATIC ${srcs})

    # Include own headers
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}")
        target_include_directories(${libname} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
    endif()

    # Always include Util headers (handle mono & FetchContent)
    if(EXISTS "${CMAKE_SOURCE_DIR}/lib/Util")
        target_include_directories(${libname} PUBLIC "${CMAKE_SOURCE_DIR}/lib/Util")
    elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../Util")
        target_include_directories(${libname} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../Util")
    elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../../../libs-src/lib/Util")
        target_include_directories(${libname} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../../../libs-src/lib/Util")
    else()
        message(WARNING "Util not found for ${libname}")
    endif()

    # Link Util (unless this is Util itself)
    if(TARGET Util AND NOT "${libname}" STREQUAL "Util")
        target_link_libraries(${libname} PUBLIC Util)
    endif()

    # Link declared deps
    foreach(dep IN LISTS ARG_DEPENDS)
        target_link_libraries(${libname} PUBLIC ${dep})
    endforeach()
endfunction()

add_subdirectory(lib)

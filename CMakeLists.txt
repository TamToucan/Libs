cmake_minimum_required(VERSION 3.20)

project(Libs)

set(FETCHCONTENT_QUIET OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


# Build lib using all sources and named same as dir (if no argv1)
#
function(BUILD_LIB)
   if (${ARGC} EQUAL 0)
      get_filename_component(lib ${CMAKE_CURRENT_SOURCE_DIR} NAME)
   else (${ARGC} EQUAL 0)
      set(lib "${ARGV0}")
   endif (${ARGC} EQUAL 0)
   file(GLOB ${lib}_SOURCES *.C *.c *.cpp)
   include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Util")
   add_library(${lib} STATIC ${${lib}_SOURCES})
endfunction(BUILD_LIB)
add_subdirectory(lib)

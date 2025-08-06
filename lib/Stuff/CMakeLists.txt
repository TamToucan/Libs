BUILD_LIB(Stuff)

if(NOT MSVC)
    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/TGA.cpp
        PROPERTIES COMPILE_FLAGS "-Wno-narrowing"
    )
endif()

project(Util)

# Grab source files
file(GLOB srcs CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.C"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
)

# Explicitly add Debug.cpp which we are about to create, 
# although GLOB would catch it, being explicit is fine or just rely on GLOB.
# reliance on GLOB is what the other libs do.

add_library(Util SHARED ${srcs})

target_compile_definitions(Util PRIVATE UTIL_EXPORTS)

target_include_directories(Util PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if(MSVC)
    target_compile_options(Util PRIVATE /wd4251) # Disable "needs to have dll-interface" warning for templates
endif()

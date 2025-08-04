set(testRandom_SOURCES testRandom.C)
add_executable(testRandom ${testRandom_SOURCES})
target_link_libraries(testRandom Random)


set(testUniversal_SOURCES testUniversal.C)
add_executable(testUniversal ${testUniversal_SOURCES})
target_link_libraries(testUniversal Random)


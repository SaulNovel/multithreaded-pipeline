set(BINARY program_test)

Set(SOURCES
    test.cpp
)

#googletest
include(FetchContent)
FetchContent_Declare(googletest
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG release-1.11.0)
FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} build)
endif()


add_executable(
    ${BINARY} 
    ${SOURCES}
)

target_link_libraries(${BINARY}
    gtest_main
    gmock_main
    pipeline
)

add_test(
    NAME ${BINARY}
    COMMAND ${BINARY}
)
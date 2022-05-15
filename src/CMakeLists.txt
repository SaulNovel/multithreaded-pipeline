project(task-pipeline)

set(BINARY program_test)

Set(SOURCES
    main.cpp
)

add_executable(
    ${BINARY} 
    ${SOURCES}
)

target_link_libraries(
    ${BINARY}
    pipeline
)
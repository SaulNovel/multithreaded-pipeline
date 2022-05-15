project(pipeline)

set(LIBRARY pipeline)

set(HEADERS
    Pipeline.h
    Task.h
    ThreadSafeQueue.h
)

find_package(Threads REQUIRED)

add_library(${LIBRARY} STATIC
    ${SOURCES}
    ${HEADERS}
)

set_target_properties(${LIBRARY} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${LIBRARY} Threads::Threads)
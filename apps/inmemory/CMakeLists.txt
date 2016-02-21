set(inmemory_SOURCES main.cpp)
add_executable(inmemory ${inmemory_SOURCES})
target_link_libraries(inmemory LINK_PUBLIC gamesource)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(${CMAKE_SOURCE_DIR}/apps/inmemory)
add_subdirectory(${CMAKE_SOURCE_DIR}/apps/client)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

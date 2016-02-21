set(jsonexample_SOURCES main.cpp)
link_directories(${LIBUV_LIBRARIES})
add_executable(jsonexample ${jsonexample_SOURCES})
target_link_libraries(jsonexample ${CMAKE_THREAD_LIBS_INIT})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

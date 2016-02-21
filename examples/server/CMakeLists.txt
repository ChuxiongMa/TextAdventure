include_directories(${LIBUV_INCLUDE_DIRS})
set(server_SOURCES main.cpp)
link_directories(${LIBUV_LIBRARIES})
add_executable(serverexample ${server_SOURCES})
target_link_libraries(
  serverexample LINK_PUBLIC
  networking
  libuv.a
  uvpp
  ${CMAKE_THREAD_LIBS_INIT}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

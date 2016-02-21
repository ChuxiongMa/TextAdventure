include_directories(${LIBUV_INCLUDE_DIRS})
set(client_SOURCES main.cpp)
link_directories(${LIBUV_LIBRARIES})
add_executable(clientexample ${client_SOURCES})
target_link_libraries(
  clientexample LINK_PUBLIC
  networking
  libuv.a
  uvpp
  ${CMAKE_THREAD_LIBS_INIT}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

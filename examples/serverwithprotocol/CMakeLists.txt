include_directories(${LIBUV_INCLUDE_DIRS})
set(serverwithprotocolexample_SOURCES main.cpp)
link_directories(${LIBUV_LIBRARIES})
add_executable(serverwithprotocolexample ${serverwithprotocolexample_SOURCES})
target_link_libraries(
  serverwithprotocolexample LINK_PUBLIC
  bufferednetworking
  bufferedprotocol
  networking
  libuv.a
  uvpp
  helpers
  ${CMAKE_THREAD_LIBS_INIT}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

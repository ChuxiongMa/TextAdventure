include_directories(${LIBUV_INCLUDE_DIRS})
set(clientwithprotocol_SOURCES main.cpp)
link_directories(${LIBUV_LIBRARIES})

add_executable(clientwithprotocolexample ${clientwithprotocol_SOURCES})
target_link_libraries(
  clientwithprotocolexample LINK_PUBLIC
  networking
  bufferedprotocol
  bufferednetworking
  libuv.a
  helpers
  ${CMAKE_THREAD_LIBS_INIT}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

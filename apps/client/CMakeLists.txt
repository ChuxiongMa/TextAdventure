set(client_SOURCES main.cpp)

link_directories(${LIBUV_LIBRARIES})

add_executable(client ${client_SOURCES})

target_link_libraries(
  client LINK_PUBLIC
  gamesource
  networking

  ${CURSES_LIBRARIES}

  uvpp
  libuv.a

  ${CMAKE_THREAD_LIBS_INIT}
)
target_include_directories(
  client PUBLIC
  ${CMAKE_SOURCE_DIR}/include
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

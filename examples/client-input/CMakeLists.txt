set(clientinput_SOURCES main.cpp)

link_directories(${LIBUV_LIBRARIES})

add_executable(clientinputexample ${clientinput_SOURCES})

target_link_libraries(
  clientinputexample LINK_PUBLIC
  networking

  ${CURSES_LIBRARIES}

  uvpp
  libuv.a

  ${CMAKE_THREAD_LIBS_INIT}
)
target_include_directories(
  clientinputexample PUBLIC
  ${CMAKE_SOURCE_DIR}/include
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

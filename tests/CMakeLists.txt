include_directories(${GTEST_INCLUDE_DIRS})

file(
  GLOB test_SOURCES_GLOB
  "*.cpp"
  "helpers/*.cpp"
  "bufferedprotocol/*.cpp"
  "yaml/*.cpp"
)
set(tests_SOURCES ${test_SOURCES_GLOB})

link_directories(${LIBUV_LIBRARIES})
link_directories(${GTEST_LIBRARIES})

add_executable(tests ${tests_SOURCES})

target_link_libraries(
  tests
  LINK_PUBLIC
  bufferedprotocol
  gamesource
  yamlinterface
  uvpp
  helpers
  libuv.a
  ${BCRYPT_LIBRARIES}/bcrypt.a
  gtest
  ${CMAKE_THREAD_LIBS_INIT}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

enable_testing()
add_test(NAME tests COMMAND test)
add_custom_target(
  check COMMAND ${PROJECT_BINARY_DIR}/bin/tests
  DEPENDS tests
)

file(GLOB bufferednetworking_SOURCE_FILES *.cpp)

add_library(
  bufferednetworking
  ${bufferednetworking_SOURCE_FILES}
  BufferedClient.cpp
)
target_include_directories(
  bufferednetworking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(
  bufferednetworking LINK_PUBLIC
  bufferedprotocol
  networking
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

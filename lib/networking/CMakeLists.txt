file(GLOB networking_SOURCE_FILES *.cpp)

include_directories(${LIBUV_INCLUDE_DIRS})
set(networking_SOURCES ${networking_SOURCE_FILES})
add_library(networking ${networking_SOURCES})
target_include_directories(networking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(
  networking LINK_PUBLIC
  uvpp
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

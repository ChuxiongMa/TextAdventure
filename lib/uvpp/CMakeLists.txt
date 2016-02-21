file(GLOB uvpp_SOURCE_FILES *.cpp)

add_library(uvpp ${uvpp_SOURCE_FILES})
target_include_directories(uvpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

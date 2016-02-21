file(GLOB helpers_SOURCE_FILES *.cpp)

add_library(helpers ${helpers_SOURCE_FILES})
target_include_directories(helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

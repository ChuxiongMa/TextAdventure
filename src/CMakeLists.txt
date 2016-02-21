file(GLOB game_SOURCE_FILES Room.cpp *.cpp helpers/*.cpp)
set(game_SOURCE ${game_SOURCE_FILES})

add_library(gamesource ${game_SOURCE})
target_include_directories(gamesource PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

PROJECT (textadventure)
cmake_minimum_required (VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(Curses REQUIRED)
find_package(Threads)
find_package(Boost REQUIRED)
find_package(LibUV REQUIRED)
find_package(GoogleTest)
find_package(Bcrypt REQUIRED)

set(Boost_INCLUDE_DIRS ${BOOST_INCLUDE_DIRS})
add_subdirectory(${CMAKE_SOURCE_DIR}/yaml)
find_package(Threads)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

include_directories(${CMAKE_SOURCE_DIR}/yaml/include)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${BOOST_INCLUDE_DIRS})
include_directories(${NCURSES_INCLUDE_DIRS})

add_subdirectory(${CMAKE_SOURCE_DIR}/examples)
add_subdirectory(${CMAKE_SOURCE_DIR}/apps)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib)

add_custom_target(clean-shared-libraries
  COMMAND ${CMAKE_COMMAND}
    -DREMOVE_FILE_GLOB=${DEPS_INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}*${CMAKE_SHARED_LIBRARY_SUFFIX}*
    -P ${PROJECT_SOURCE_DIR}/cmake/RemoveFiles.cmake
  DEPENDS ${THIRD_PARTY_DEPS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

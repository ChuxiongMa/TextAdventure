include(ExternalProject)

include(ExternalProject)
ExternalProject_Add(textadventure_gtest
  URL https://github.com/google/googletest/archive/release-1.7.0.tar.gz
  URL_HASH SHA256=f73a6546fdf9fce9ff93a5015e0333a8af3062a152a9ad6bcb772c96687016cc
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  INSTALL_COMMAND ""
)
ExternalProject_Get_Property(textadventure_gtest source_dir binary_dir)

set(GTEST_INCLUDE_DIRS ${source_dir}/include)
set(GTEST_LIBRARIES ${binary_dir})
message(STATUS ${GTEST_LIBRARIES})

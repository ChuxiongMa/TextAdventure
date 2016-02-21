file(GLOB yamlinterface_SOURCE_FILES *.cpp)

add_library(
  yamlinterface
  ${yamlinterface_SOURCE_FILES}
)

target_link_libraries(
  yamlinterface LINK_PUBLIC ${CMAKE_BINARY_DIR}/yaml/libyaml-cpp.a
  gamesource
)

set(data_SHADOW midgaard.yml smurf.yml)
set(data_DEST)

foreach(item IN LISTS data_SHADOW)
  list(APPEND data_DEST ${CMAKE_CURRENT_SOURCE_DIR}/${item})
endforeach()
add_custom_target(copy-yaml ALL COMMAND cp ${data_DEST} ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(ExternalProject)

set(_libuv_TARGET "libuv")
set(DEPS_BUILD_DIR "${CMAKE_BINARY_DIR}/build" CACHE PATH "Dependencies build directory.")
set(DEPS_DOWNLOAD_DIR "${DEPS_BUILD_DIR}/downloads" CACHE PATH "Dependencies download directory.")
set(DEPS_INSTALL_DIR "${CMAKE_BINARY_DIR}/usr" CACHE PATH "Dependencies install directory.")
set(LIBUV_URL https://github.com/libuv/libuv/archive/v1.7.3.tar.gz)
set(LIBUV_SHA256 db5d46318e18330c696d954747036e1be8e2346411d4f30236d7e2f499f0cfab)
option(USE_EXISTING_SRC_DIR "Skip download of deps sources in case of existing source directory." OFF)

set(UNIX_CFGCMD sh ${DEPS_BUILD_DIR}/src/libuv/autogen.sh &&
  ${DEPS_BUILD_DIR}/src/libuv/configure --with-pic --disable-shared
  --prefix=${DEPS_INSTALL_DIR} --libdir=${DEPS_INSTALL_DIR}/lib
  CC=${DEPS_C_COMPILER})

ExternalProject_Add(${_libuv_TARGET}
  PREFIX ${DEPS_BUILD_DIR}
  URL ${LIBUV_URL}
  DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/libuv
  DOWNLOAD_COMMAND ${CMAKE_COMMAND}
    -DPREFIX=${DEPS_BUILD_DIR}
    -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/libuv
    -DURL=${LIBUV_URL}
    -DEXPECTED_SHA256=${LIBUV_SHA256}
    -DTARGET=${_libuv_TARGET}
    -DUSE_EXISTING_SRC_DIR=${USE_EXISTING_SRC_DIR}
    -P ${PROJECT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
  CONFIGURE_COMMAND "${UNIX_CFGCMD}"
  BUILD_COMMAND "make"
  INSTALL_COMMAND make install)

list(APPEND THIRD_PARTY_DEPS libuv)

set(LIBUV_LIBRARIES ${DEPS_INSTALL_DIR}/lib)
set(LIBUV_INCLUDE_DIRS ${DEPS_INSTALL_DIR}/include)

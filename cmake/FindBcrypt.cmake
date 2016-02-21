include(ExternalProject)

set(_bcrypt_TARGET "bcrypt")
set(DEPS_BUILD_DIR "${CMAKE_BINARY_DIR}/build" CACHE PATH "Dependencies build directory.")
set(DEPS_DOWNLOAD_DIR "${DEPS_BUILD_DIR}/downloads" CACHE PATH "Dependencies download directory.")
set(DEPS_INSTALL_DIR "${CMAKE_BINARY_DIR}/usr" CACHE PATH "Dependencies install directory.")
set(BCRYPT_SRC_DIR ${DEPS_BUILD_DIR}/src/bcrypt)
set(BCRYPT_URL https://github.com/rg3/bcrypt/archive/b1e3dea0a159ac60350745c1ff1431919940e9b9.tar.gz)
set(BCRYPT_SHA256 b6d8aa55e811c9a4140a71e828cde5ac639b9585cf0a0b1c76cbcddff92a68a3)
option(USE_EXISTING_SRC_DIR "Skip download of deps sources in case of existing source directory." OFF)

set(_BCRYPT_INSTALL mkdir -p ${DEPS_INSTALL_DIR}/lib &&
  mkdir -p ${DEPS_INSTALL_DIR}/include &&
  cp ${BCRYPT_SRC_DIR}/bcrypt.a ${DEPS_INSTALL_DIR}/lib &&
  cp ${BCRYPT_SRC_DIR}/bcrypt.h ${DEPS_INSTALL_DIR}/include)

ExternalProject_Add(${_bcrypt_TARGET}
  PREFIX ${DEPS_BUILD_DIR}
  URL ${BCRYPT_URL}
  DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/bcrypt
  DOWNLOAD_COMMAND ${CMAKE_COMMAND}
    -DPREFIX=${DEPS_BUILD_DIR}
    -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/bcrypt
    -DURL=${BCRYPT_URL}
    -DEXPECTED_SHA256=${BCRYPT_SHA256}
    -DTARGET=${_bcrypt_TARGET}
    -DUSE_EXISTING_SRC_DIR=${USE_EXISTING_SRC_DIR}
    -P ${PROJECT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
  CONFIGURE_COMMAND ""
  BUILD_COMMAND make -C ${BCRYPT_SRC_DIR}
  INSTALL_COMMAND ${_BCRYPT_INSTALL})

list(APPEND THIRD_PARTY_DEPS bcrypt)

set(BCRYPT_LIBRARIES ${DEPS_INSTALL_DIR}/lib)
set(BCRYPT_INCLUDE_DIRS ${DEPS_INSTALL_DIR}/include)

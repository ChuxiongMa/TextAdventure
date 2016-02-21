if (NOT TARGET boost)
  include(ExternalProject)

  set(_boost_TARGET "boost")
  set(DEPS_BUILD_DIR "${CMAKE_BINARY_DIR}/build" CACHE PATH "Dependencies build directory.")
  set(DEPS_DOWNLOAD_DIR "${DEPS_BUILD_DIR}/downloads" CACHE PATH "Dependencies download directory.")
  set(DEPS_INSTALL_DIR "${CMAKE_BINARY_DIR}/usr" CACHE PATH "Dependencies install directory.")
  set(BOOST_SRC_DIR ${DEPS_BUILD_DIR}/src/boost)
  set(BOOST_URL http://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.tar.gz/download)
  set(BOOST_SHA256 47f11c8844e579d02691a607fbd32540104a9ac7a2534a8ddaef50daf502baac)
  option(USE_EXISTING_SRC_DIR "Skip download of deps sources in case of existing source directory." OFF)

  set(_BOOST_INSTALL mkdir -p ${DEPS_INSTALL_DIR}/include &&
    cp -r ${BOOST_SRC_DIR}/boost ${DEPS_INSTALL_DIR}/include)

  ExternalProject_Add(${_boost_TARGET}
    PREFIX ${DEPS_BUILD_DIR}
    URL ${BOOST_URL}
    DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/boost
    DOWNLOAD_COMMAND ${CMAKE_COMMAND}
      -DPREFIX=${DEPS_BUILD_DIR}
      -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/boost
      -DURL=${BOOST_URL}
      -DEXPECTED_SHA256=${BOOST_SHA256}
      -DTARGET=${_boost_TARGET}
      -DUSE_EXISTING_SRC_DIR=${USE_EXISTING_SRC_DIR}
      -P ${PROJECT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ${_BOOST_INSTALL})

  list(APPEND THIRD_PARTY_DEPS boost)

  set(BOOST_INCLUDE_DIRS ${DEPS_INSTALL_DIR}/include)
endif()

# Install script for directory: /home/bruno/paradiseo/moeo/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/bruno/paradiseo")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibrariesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/home/bruno/paradiseo/build/lib/libmoeo.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xheadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/paradiseo/moeo" TYPE FILE FILES "/home/bruno/paradiseo/moeo/src/moeo")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xheadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/paradiseo/moeo" TYPE DIRECTORY FILES
    "/home/bruno/paradiseo/moeo/src/acceptCrit"
    "/home/bruno/paradiseo/moeo/src/algo"
    "/home/bruno/paradiseo/moeo/src/archive"
    "/home/bruno/paradiseo/moeo/src/continue"
    "/home/bruno/paradiseo/moeo/src/comparator"
    "/home/bruno/paradiseo/moeo/src/core"
    "/home/bruno/paradiseo/moeo/src/distance"
    "/home/bruno/paradiseo/moeo/src/diversity"
    "/home/bruno/paradiseo/moeo/src/do"
    "/home/bruno/paradiseo/moeo/src/explorer"
    "/home/bruno/paradiseo/moeo/src/fitness"
    "/home/bruno/paradiseo/moeo/src/hybridization"
    "/home/bruno/paradiseo/moeo/src/metric"
    "/home/bruno/paradiseo/moeo/src/replacement"
    "/home/bruno/paradiseo/moeo/src/scalarStuffs"
    "/home/bruno/paradiseo/moeo/src/selection"
    "/home/bruno/paradiseo/moeo/src/utils"
    FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()


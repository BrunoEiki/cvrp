# Install script for directory: /home/bruno/paradiseo/mo/src

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xheadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/paradiseo/mo" TYPE FILE FILES
    "/home/bruno/paradiseo/mo/src/mo"
    "/home/bruno/paradiseo/mo/src/mo.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xheadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/paradiseo/mo" TYPE DIRECTORY FILES
    "/home/bruno/paradiseo/mo/src/acceptCrit"
    "/home/bruno/paradiseo/mo/src/algo"
    "/home/bruno/paradiseo/mo/src/comparator"
    "/home/bruno/paradiseo/mo/src/continuator"
    "/home/bruno/paradiseo/mo/src/coolingSchedule"
    "/home/bruno/paradiseo/mo/src/eval"
    "/home/bruno/paradiseo/mo/src/explorer"
    "/home/bruno/paradiseo/mo/src/memory"
    "/home/bruno/paradiseo/mo/src/neighborhood"
    "/home/bruno/paradiseo/mo/src/perturb"
    "/home/bruno/paradiseo/mo/src/problems"
    "/home/bruno/paradiseo/mo/src/sampling"
    FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()


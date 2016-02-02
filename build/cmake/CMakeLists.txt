#
#  Copyright (C) 2015 National Institute For Space Research (INPE) - Brazil.
#
#  This file is part of Geospatial Database Explorer (GDE) - a free and open source GIS.
#
#  TerraMA2 is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation, either version 3 of the License,
#  or (at your option) any later version.
#
#  GDE is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public License
#  along with GDE. See LICENSE. If not, write to
#  GDE Team at <gde-team@dpi.inpe.br>.
#
#
#  Description: Main CMake script for the Geospatial Database Explorer build system.
#
#  Author: Joao Vitor Chagas
#          Gilberto Ribeiro de Queiroz
#

cmake_minimum_required(VERSION 2.8.12)

project(gde)

#
# main variables for the build script
#

# variables that control the system versioning
set(GDE_VERSION_MAJOR 0)
set(GDE_VERSION_MINOR 1)
set(GDE_VERSION_PATCH 0)
set(GDE_VERSION_STATUS "alpha")
set(GDE_VERSION_STATUS_FULL "-alpha1")
set(GDE_VERSION_STRING "${GDE_VERSION_MAJOR}.${GDE_VERSION_MINOR}.${GDE_VERSION_PATCH}${GDE_VERSION_STATUS_FULL}")
set(GDE_VERSION "0x000100")

# variables storing absolute paths
set(GDE_ABSOLUTE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)

# variables that control install locations
if(NOT DEFINED GDE_DESTINATION_UNITTEST)
  set(GDE_DESTINATION_UNITTEST "${GDE_BASE_DESTINATION_DIR}share/gde/unittest")
endif()

if(NOT DEFINED GDE_DESTINATION_LIBRARY)
  set(GDE_DESTINATION_LIBRARY "${GDE_BASE_DESTINATION_DIR}lib")
endif()

if(NOT DEFINED GDE_DESTINATION_RUNTIME)
  set(GDE_DESTINATION_RUNTIME "${GDE_BASE_DESTINATION_DIR}bin")
endif()

if(NOT DEFINED GDE_DESTINATION_ARCHIVE)
  set(GDE_DESTINATION_ARCHIVE "${GDE_BASE_DESTINATION_DIR}lib")
endif()

if(NOT DEFINED GDE_DESTINATION_HEADERS)
  set(GDE_DESTINATION_HEADERS "${GDE_BASE_DESTINATION_DIR}include")
endif()

# variables that controls what is built
if(NOT DEFINED GDE_BUILD_UNITTEST_ENABLED)
  set(GDE_BUILD_UNITTEST_ENABLED ON CACHE BOOL "If on, shows the list of unit-tests to be built")
endif()


#
# global definitions and includes
#

add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_FILESYSTEM_VERSION=3 -DBOOST_UBLAS_TYPE_CHECK=0)

if(WIN32)
  #add_definitions(-D_CRT_SECURE_NO_WARNINGS)

  if(MINGW)
    add_definitions(-DTE_MINGW -D_WIN32_WINNT=0x601 -fpermissive)
  endif()

elseif(APPLE)
  add_definitions(-ftemplate-depth-1024)
endif()

# Note: automatically link executables with qtmain.lib on Windows when it has Qt dependency.
if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}" VERSION_GREATER  2.8.9)
  cmake_policy(SET CMP0020 NEW)
endif()

if(${CMAKE_MAJOR_VERSION} GREATER 2)
  cmake_policy(SET CMP0026 OLD)
  cmake_policy(SET CMP0042 NEW)
  cmake_policy(SET CMP0043 NEW)
endif()

if(${CMAKE_VERSION} VERSION_GREATER "3.1.2")
  cmake_policy(SET CMP0053 OLD)
endif()

include_directories(${CMAKE_BINARY_DIR})


#
# Build will generate files into a single folder
#
if((CMAKE_GENERATOR STREQUAL Xcode) OR MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()


#
# global configurations
#

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR (CMAKE_CXX_COMPILER MATCHES ".*clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11")
endif()

# Turn on multi process compilation
if(MSVC)
  add_definitions(/MP)
endif()

# Enable CTest
enable_testing()


#
# including CMake's auxiliary files
#

include(CMakeDependentOption)


#
# including GDE auxiliary macros and functions
#

#include(gde_macros.cmake)


#
# first check of libraries
#

#find_package(Qt5 5.2 REQUIRED COMPONENTS Core Gui Widgets Network LinguistTools Test)

#if(NOT Qt5_FOUND)
#  message(FATAL_ERROR "GDE: could not find required Qt 5 libraries!")
#endif()

#if(NOT QT_QCOLLECTIONGENERATOR_EXECUTABLE)
#  find_program(QT_QCOLLECTIONGENERATOR_EXECUTABLE
#               NAME qcollectiongenerator
#               PATHS /usr
#                     /usr/local
#                     ${Qt5_DIR}/../../..
#               PATH_SUFFIXES bin)
#endif()

#find_package(Boost 1.54.0 REQUIRED system date_time chrono log timer filesystem)

#if(NOT Boost_FOUND)
#  message(FATAL_ERROR "GDE: could not find required Boost libraries!")
#endif()

#find_package(Doxygen)

#find_package(terralib REQUIRED)

#if(NOT terralib_FOUND)
#  message(FATAL_ERROR "GDE: could not find TerraLib libraries!")
#endif()


#
# build options
#
# warning: please, do not change the order below!
#

#if(DOXYGEN_FOUND)
#  option(GDE_DOXYGEN_ENABLED  "Enable API documentation build?" ON)
#endif()

option(GDE_MOD_GEOM_ALGORITHM_ENABLED "Build geometry algorithms module?" ON)

CMAKE_DEPENDENT_OPTION(GDE_UNITTEST_GEOM_ALGORITHM_ENABLED "Build unittest for geometry algoithms module?" ON "GDE_MOD_GEOM_ALGORITHM_ENABLED;GDE_BUILD_UNITTEST_ENABLED" OFF)

CMAKE_DEPENDENT_OPTION(GDE_BENCHMARK_ENABLED "Build benchmark?" ON "GDE_MOD_GEOM_ALGORITHM_ENABLED" OFF)


#
# process GDE configuration files
#

#configure_file(${CMAKE_SOURCE_DIR}/gde-config-pkg.cmake.in
#               ${CMAKE_BINARY_DIR}/pkg/gde-config.cmake @ONLY)

#configure_file(${CMAKE_SOURCE_DIR}/gde-config-version.cmake.in
#               ${CMAKE_BINARY_DIR}/gde-config-version.cmake @ONLY)

#configure_file(${CMAKE_SOURCE_DIR}/gde-config.cmake.in
#               ${CMAKE_BINARY_DIR}/gde-config.cmake @ONLY)

#configure_file(${GDE_ABSOLUTE_ROOT_DIR}/src/gde/Config.hpp.in
#               ${CMAKE_BINARY_DIR}/gde_config.hpp @ONLY)

#configure_file(${GDE_ABSOLUTE_ROOT_DIR}/src/gde/Defines.hpp.in
#               ${CMAKE_BINARY_DIR}/gde_defines.hpp @ONLY)

#configure_file(${GDE_ABSOLUTE_ROOT_DIR}/src/gde/Version.hpp.in
#               ${CMAKE_BINARY_DIR}/gde_version.hpp @ONLY)

#configure_file(${GDE_ABSOLUTE_ROOT_DIR}/COPYING ${CMAKE_BINARY_DIR}/COPYING.txt COPYONLY)


#
# build modules
#

if(GDE_MOD_GEOM_ALGORITHM_ENABLED)
  add_subdirectory(gde_mod_geom_algorithm)
endif()

if(GDE_UNITTEST_GEOM_ALGORITHM_ENABLED)
  add_subdirectory(gde_unittest_geom_algorithm)
endif()

if(GDE_BENCHMARK_ENABLED)
  add_subdirectory(gde_benchmark)
endif()


#
# install and targets export
#

#file(GLOB GDE_HDR_FILES ${GDE_ABSOLUTE_ROOT_DIR}/src/gde/*.hpp)

#install(FILES ${CMAKE_BINARY_DIR}/gde_config.hpp
#              ${CMAKE_BINARY_DIR}/gde_version.hpp
#              ${GDE_HDR_FILES}
#        DESTINATION ${GDE_DESTINATION_HEADERS}/gde COMPONENT devel)

#install(FILES ${GDE_ABSOLUTE_ROOT_DIR}/src/gde.hpp
#        DESTINATION ${GDE_DESTINATION_HEADERS} COMPONENT devel)

#install(FILES ${GDE_BINARY_DIR}/pkg/gde-config.cmake
#              ${GDE_BINARY_DIR}/gde-config-version.cmake
#        DESTINATION ${GDE_DESTINATION_LIBRARY}/cmake/gde-${GDE_VERSION_STRING} COMPONENT devel)

#install(EXPORT gde-targets
#        DESTINATION ${GDE_DESTINATION_LIBRARY}/cmake/gde-${GDE_VERSION_STRING}
#        FILE gde-exports.cmake
#        COMPONENT devel)

#install(DIRECTORY ${GDE_ABSOLUTE_ROOT_DIR}/share/gde/config
#        DESTINATION ${GDE_DESTINATION_SHARE}/gde COMPONENT runtime)

#install(DIRECTORY ${GDE_ABSOLUTE_ROOT_DIR}/share/gde/icons
#        DESTINATION ${GDE_DESTINATION_SHARE}/gde COMPONENT runtime)




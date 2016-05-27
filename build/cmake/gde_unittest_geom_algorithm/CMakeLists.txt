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
#  Description: CMake script for GDE unit test - geometry algorithm module.
#
#  Author: Joao Vitor Chagas
#          Gilberto Ribeiro de Queiroz
#

file(GLOB GDE_SRC_FILES ${GDE_ABSOLUTE_ROOT_DIR}/src/unittest/geom/algorithm/*.cpp)
file(GLOB GDE_HDR_FILES ${GDE_ABSOLUTE_ROOT_DIR}/src/unittest/geom/algorithm/*.hpp)

include_directories (
  ${GDE_ABSOLUTE_ROOT_DIR}/src
)

source_group("Source Files"  FILES ${GDE_SRC_FILES})
source_group("Header Files"  FILES ${GDE_HDR_FILES})

add_executable(gde_unittest_geom_algorithm ${GDE_SRC_FILES} ${GDE_HDR_FILES})

target_link_libraries(gde_unittest_geom_algorithm gde_mod_geom_algorithm ${CMAKE_THREAD_LIBS_INIT})

add_test(NAME gde_unittest_geom_algorithm COMMAND gde_unittest_geom_algorithm)

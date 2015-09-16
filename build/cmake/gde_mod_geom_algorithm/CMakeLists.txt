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
#  Description: CMake script for GDE Geometry Algorithms Module.
#
#  Author: Joao Vitor Chagas
#          Gilberto Ribeiro de Queiroz
#

file(GLOB GDE_SRC_FILES ${GDE_ABSOLUTE_ROOT_DIR}/src/gde/geom/algorithm/*.cpp)
file(GLOB GDE_HDR_FILES ${GDE_ABSOLUTE_ROOT_DIR}/src/gde/geom/algorithm/*.hpp)

source_group("Source Files"  FILES ${GDE_SRC_FILES})
source_group("Header Files"  FILES ${GDE_HDR_FILES})

add_library(gde_mod_geom_algorithm STATIC ${GDE_SRC_FILES} ${GDE_HDR_FILES})

set_target_properties(gde_mod_geom_algorithm
                      PROPERTIES VERSION ${GDE_VERSION_MAJOR}.${GDE_VERSION_MINOR}
                                 SOVERSION ${GDE_VERSION_MAJOR}.${GDE_VERSION_MINOR}
                                 INSTALL_NAME_DIR "@executable_path/../lib")

install(TARGETS gde_mod_geom_algorithm
        EXPORT gde-targets
        RUNTIME DESTINATION ${GDE_DESTINATION_RUNTIME} COMPONENT runtime
        LIBRARY DESTINATION ${GDE_DESTINATION_LIBRARY} COMPONENT runtime
        ARCHIVE DESTINATION ${GDE_DESTINATION_ARCHIVE} COMPONENT runtime)

install(FILES ${GDE_HDR_FILES}
        DESTINATION ${GDE_DESTINATION_HEADERS}/gde/geom/algorithm COMPONENT devel)

export(TARGETS gde_mod_geom_algorithm APPEND FILE ${CMAKE_BINARY_DIR}/gde-exports.cmake)

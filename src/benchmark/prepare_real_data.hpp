/*
  Copyright (C) 2015 National Institute For Space Research (INPE) - Brazil.

  This file is part of Geospatial Database Explorer (GDE) - a free and open source GIS.

  GDE is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License,
  or (at your option) any later version.

  GDE is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with GDE. See LICENSE. If not, write to
  GDE Team at <gde-team@dpi.inpe.br>.
*/

/*!
  \file benchmark/prepare_real_data.hpp
 
  \brief Utility functions for preparing real data for the benchmark.
 
  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

#ifndef __GDE_BENCHMARK_PREPARE_REAL_DATA_HPP__
#define __GDE_BENCHMARK_PREPARE_REAL_DATA_HPP__

// GDE
#include <gde/geom/core/geometric_primitives.hpp>

// STL
#include <vector>
#include <string>

void StartTerraLib();

void StopTerraLib();

std::vector<gde::geom::core::line_segment>
extract_segments_from_shp(const std::string & shp_file_name);

void save_intersection_points(const std::vector<gde::geom::core::point>& ipts,
                              int initial_gid,
                              int srid,
                              const std::string& shapefile_name);


#endif // __GDE_BENCHMARK_PREPARE_REAL_DATA_HPP__

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
  \file benchmark/gen_random_data.hpp

  \brief Utility functiond for generating random data.

  \author Joao Vitor Chagas
 */


#ifndef __GDE_BENCHMARK_GEN_RANDOM_DATA_HPP__
#define __GDE_BENCHMARK_GEN_RANDOM_DATA_HPP__

// GDE
#include <gde/geom/core/geometric_primitives.hpp>

// STL
#include <vector>

/*!
  \brief Generates line segments

  This function takes receives the parameters to generate line segments , it creates segments with gen_point function and then checks with check_segment function
 */
std::vector<gde::geom::core::line_segment>
gen_segments(std::size_t num_segments,
             std::pair<double, double> x_interval,
             std::pair<double, double> y_interval,
             double min_length, double max_length);

#endif // __GDE_BENCHMARK_GEN_RANDOM_DATA_HPP__

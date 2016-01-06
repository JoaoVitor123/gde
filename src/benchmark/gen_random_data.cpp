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
  \file benchmark/gen_random_data.cpp

  \brief Utility functions for generating random data.

  \author Joao Vitor Chagas
 */

// GDE
#include "gen_random_data.hpp"

// STL
#include <algorithm>
#include <random>

//! Generates a random number between min_val and max_val.
double gen_value(double min_val, double max_val)
{
  double n = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);

  return min_val + n * (max_val - min_val);
}

std::vector<gde::geom::core::line_segment>
gen_segments(std::size_t num_segments,
             std::pair<double, double> x_interval,
             std::pair<double, double> y_interval,
             double min_length, double max_length)
{
// output segment list
  std::vector<gde::geom::core::line_segment> segments;
  
// reserve memory for #num_segments
  segments.reserve(num_segments);

// generates a variable of type line_segment
  gde::geom::core::line_segment segment;

// define the points p1 and p2 of each segment
  for(int i = 0; i < num_segments; ++i)
  {
// generates the first point of the segment in the interval
    segment.p1.x = gen_value(x_interval.first, x_interval.second - max_length);
    segment.p1.y = gen_value(y_interval.first, y_interval.second - max_length);

// the second segment point is constrained to min_length and max_length
    segment.p2.x = gen_value(segment.p1.x + min_length, segment.p1.x + max_length);
    segment.p2.y = gen_value(segment.p1.y + min_length, segment.p1.y + max_length);

    segments.push_back(segment);
  }

  return segments;
}


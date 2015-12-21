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

  \brief Utility functiond for generating random data.

  \author Joao Vitor Chagas
 */

// GDE
#include "gen_random_data.hpp"
#include <iostream>


double gen_point(double p_max, double p_min)
{
// generates a number aliatorio
  double n = (double)rand() / RAND_MAX;

// adjusts the number between p_max and p_min
  return p_min + n * (p_max - p_min);
}

bool check_segment(const gde::geom::core::line_segment& s,
                      double max, double min)
{

// check the highest and lowest point of the segment
  const auto&  minmax1 = std::minmax(s.p1.x, s.p2.x);
  const auto&  minmax2 = std::minmax(s.p1.y, s.p2.y);

// checks if the points are between the max and min value
  if((minmax1.second - minmax1.first) < min || (minmax1.second - minmax1.first) > max)
    return true;

  if((minmax2.second - minmax2.first) < min || (minmax2.second - minmax2.first) > max)
    return true;

// returns false if the segment is valid
  return false;
}

std::vector<gde::geom::core::line_segment> gen_segments(std::size_t num_segments, double max, double min,
                                                        double p_max, double p_min)
{

// output segment list
  std::vector<gde::geom::core::line_segment> segments;
  
// we can reserve memory for #num_segments
  segments.reserve(num_segments);

// generates a variable of type line_segment
  gde::geom::core::line_segment segment;

// define the points p1 and p2 of each segment
  for(int i = 0; i < num_segments; ++i)
  {

// generates the points for the segments
    segment.p1.x = gen_point(p_max, p_min);
    segment.p1.y = gen_point(p_max, p_min);

    segment.p2.x = gen_point(p_max, p_min);
    segment.p2.y = gen_point(p_max, p_min);

// checks if the segment is within the threshold, if not Repede the process for this segment
    if(check_segment(segment, max, min))
      --i;

// adds the segment to segment vector
    else{
      segments.push_back(segment);
    }
  }

// returns the vector segments
  return segments;
}


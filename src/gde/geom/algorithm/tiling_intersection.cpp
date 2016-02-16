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
  \file gde/geom/algorithm/tiling_intersection.cpp

  \brief tiling intersection algorithm.

  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

// GDE
#include "line_segments_intersection.hpp"
#include "line_segment_intersection.hpp"
#include "utils.hpp"


// STL
#include <algorithm>
#include <iostream>

std::vector<gde::geom::core::point>
gde::geom::algorithm::tiling_intersection(const std::vector<gde::geom::core::line_segment>& segments,
                                          const double& max_length, const double& max_range, const double& min_range)
{
  std::vector<gde::geom::core::point> ipts;
  std::vector<gde::geom::core::line_segment> segments_range[int(max_range/max_length)];

  double range_y;
// through all segments
  for(int i = 0;i < segments.size(); ++i)
  {
// range_y receives the maximum size of a segment
    range_y = min_range + max_length;
// through every division blocks in Y
    for(int j = 0; j < ((max_range*2)/max_length); ++j)
    {
// checks whether the segment y value is within block
      if(segments[i].p1.y < range_y || segments[i].p2.y < range_y)
      {
// adds the segment in its corresponding block
        segments_range[int(j/max_length)].push_back(segments[i]);

// checks if one of the points of this segment this the top of this block
        if(segments[i].p1.y > range_y || segments[i].p2.y > range_y &&
           segments[i].p1.y < max_range && segments[i].p2.y < max_range)
          segments_range[int(j/max_length)+1].push_back(segments[i]);
        break;
      }
      range_y += max_length;
    }
  }
// x-ordering
  std::vector<gde::geom::core::line_segment> Iter;

  for(auto& elemento: segments_range)
  {
   ipts =    gde::geom::algorithm::x_order_intersection(elemento);
   for(auto& elemento2: ipts)
     std::cout << elemento2.x << "\n";
   }

  return ipts;
}

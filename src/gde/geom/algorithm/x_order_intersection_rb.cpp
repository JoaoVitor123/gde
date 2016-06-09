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
  \file gde/geom/algorithm/tiling_intersection_rb.cpp

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

inline void
sort_transform_segments(const std::vector<gde::geom::core::line_segment>& segments,
                        std::vector<gde::geom::core::line_segment>& ordered_segments)
{
// copy the input segments and order each one them from left-right
  std::transform(segments.begin(), segments.end(), ordered_segments.begin(), gde::geom::algorithm::sort_segment_xy());

// sort all the segments from left to right
  std::sort(ordered_segments.begin(), ordered_segments.end(), gde::geom::algorithm::line_segment_xy_cmp());
}

std::vector<gde::geom::core::point>
gde::geom::algorithm::x_order_intersection_rb(const std::vector<gde::geom::core::line_segment>& red,
                                              const std::vector<gde::geom::core::line_segment>& blue,
                                              const double delimita_max, const double delimita_min)
{
 // std::cout << delimita_max << "   "  <<  delimita_min << std::endl;
// create a new segment vector with the same size as input segments
  std::vector<gde::geom::core::line_segment> ordered_segments_r(red.size());
  std::vector<gde::geom::core::line_segment> ordered_segments_b(blue.size());

// organizes segments
  sort_transform_segments(red, ordered_segments_r);
  sort_transform_segments(blue, ordered_segments_b);

// output list of intersection points
  std::vector<gde::geom::core::point> ipts;

// retain intersection points between tests
  gde::geom::core::point ip1, ip2;

// first scan ordered_segments from the first segment
  for(int i = 0; i < (ordered_segments_r.size() - 1); ++i)
  {
// scan segments from i + 1
    for (int j = i + 1; j < ordered_segments_b.size(); j++)
    {
// if beginning x-coordinate of the second is greater than the last
// x-coordinate of the first segment: stop => no more segments can intersects.
      if(ordered_segments_r[i].p2.x < ordered_segments_b[j].p1.x)
        break;

// if segments y-interval don't intersect they will not have intersection,
// let's test the next segment!
      if(!do_y_interval_intersects(ordered_segments_r[i], ordered_segments_b[j]))
        continue;

// check for intersection
      segment_relation_type result = compute_intesection_v3(ordered_segments_r[i], ordered_segments_b[j], ip1, ip2);

      if(result == DISJOINT)
        continue;

      if(ip1.y > delimita_max || ip1.y <  delimita_min)
        continue;

      ipts.push_back(ip1);

      if(result == OVERLAP)
        ipts.push_back(ip2);
    }
  }

  return std::move(ipts);
}

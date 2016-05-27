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
  \file gde/geom/algorithm/x_order_intersection.cpp

  \brief X-Order intersection algorithm.

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
gde::geom::algorithm::x_order_intersection(const std::vector<gde::geom::core::line_segment>& segments)
{
// create a new segment vector with the same size as input segments
  std::vector<gde::geom::core::line_segment> ordered_segments(segments.size());

// copy the input segments and order each one them from left-right
  std::transform(segments.begin(), segments.end(), ordered_segments.begin(), sort_segment_xy());

// sort all the segments from left to right
  std::sort(ordered_segments.begin(), ordered_segments.end(), line_segment_xy_cmp());

// output list of intersection points
  std::vector<gde::geom::core::point> ipts;
  
// retain intersection points between tests
  gde::geom::core::point ip1, ip2;

// first scan ordered_segments from the first segment
  for(int i = 0; i < (ordered_segments.size() - 1); ++i)
  {
// scan segments from i + 1
    for (int j = i + 1; j < ordered_segments.size(); j++)
    {
// if beginning x-coordinate of the second is greater than the last
// x-coordinate of the first segment: stop => no more segments can intersects.
      if(ordered_segments[i].p2.x < ordered_segments[j].p1.x)
        break;

// if segments y-interval don't intersect they will not have intersection,
// let's test the next segment!
      if(!do_y_interval_intersects(ordered_segments[i], ordered_segments[j]))
        continue;
      
// check for intersection
      segment_relation_type result = compute_intesection_v3(ordered_segments[i], ordered_segments[j], ip1, ip2);
      
      if(result == DISJOINT)
        continue;
      
      ipts.push_back(ip1);
      
      if(result == OVERLAP)
        ipts.push_back(ip2);
    }
  }

  return ipts;
}

// v2


std::vector<gde::geom::core::point>
gde::geom::algorithm::x_order_intersection(const std::vector<gde::geom::core::line_segment>& segments,
                                           const double delimita_max, const double delimita_min)
{
 // std::cout << delimita_max << "   "  <<  delimita_min << std::endl;
// create a new segment vector with the same size as input segments
  std::vector<gde::geom::core::line_segment> ordered_segments(segments.size());

// copy the input segments and order each one them from left-right
  std::transform(segments.begin(), segments.end(), ordered_segments.begin(), sort_segment_xy());

// sort all the segments from left to right
  std::sort(ordered_segments.begin(), ordered_segments.end(), line_segment_xy_cmp());

// output list of intersection points
  std::vector<gde::geom::core::point> ipts;

// retain intersection points between tests
  gde::geom::core::point ip1, ip2;

// first scan ordered_segments from the first segment
  for(int i = 0; i < (ordered_segments.size() - 1); ++i)
  {
// scan segments from i + 1
    for (int j = i + 1; j < ordered_segments.size(); j++)
    {
// if beginning x-coordinate of the second is greater than the last
// x-coordinate of the first segment: stop => no more segments can intersects.
      if(ordered_segments[i].p2.x < ordered_segments[j].p1.x)
        break;

// if segments y-interval don't intersect they will not have intersection,
// let's test the next segment!
      if(!do_y_interval_intersects(ordered_segments[i], ordered_segments[j]))
        continue;

// check for intersection
      segment_relation_type result = compute_intesection_v3(ordered_segments[i], ordered_segments[j], ip1, ip2);

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

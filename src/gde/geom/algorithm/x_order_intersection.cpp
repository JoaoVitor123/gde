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

std::vector<gde::geom::core::point>
gde::geom::algorithm::x_order_intersection(const std::vector<gde::geom::core::line_segment>& segments)
{
// output list of intersection points
  std::vector<gde::geom::core::point> ipts;
  
  const std::size_t nsegments = segments.size();

// check if we have at least two segments to scan!
  if(nsegments <= 1)
    return ipts;
  
// create a new segment vector with the same size as input segments
  std::vector<gde::geom::core::line_segment> ordered_segments(nsegments);

// copy the input segments and order each one them from left-right
  std::transform(segments.begin(), segments.end(), ordered_segments.begin(), sort_segment_xy());

// sort all the segments from left to right
  std::sort(ordered_segments.begin(), ordered_segments.end(), line_segment_xy_cmp());
  
// retain intersection points between tests
  gde::geom::core::point ip1, ip2;
  
  const std::size_t nbands = nsegments - 1;

// first scan ordered_segments from the first segment
  for(std::size_t i = 0; i < nbands; ++i)
  {
    const gde::geom::core::line_segment& current_seg = ordered_segments[i];

// scan segments from i + 1
    for(std::size_t j = i + 1; j < nsegments; ++j)
    {
      const gde::geom::core::line_segment& next_seg = ordered_segments[j];

// if beginning x-coordinate of the next-segment is greater than
// the end x-coordinate of the current-segment, they can not intersect
// and all following sgments will be out-of current segment
// interval => stop: no more segments can intersects.
      if(current_seg.p2.x < next_seg.p1.x)
        break;

// if segments y-interval don't intersect they will not have intersection,
// let's test the next segment!
      if(!do_y_interval_intersects(current_seg, next_seg))
        continue;
      
// check for intersection
      segment_relation_type result = compute_intesection_v3(current_seg, next_seg, ip1, ip2);
      
      if(result == DISJOINT)
        continue;
      
      ipts.push_back(ip1);
      
      if(result == OVERLAP)
        ipts.push_back(ip2);
    }
  }

  return ipts;
}

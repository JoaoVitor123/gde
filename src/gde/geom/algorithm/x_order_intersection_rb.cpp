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

/*!
  \struct red_blue_sort_segment_xy
       
  Given a line segment it will build a new one ordered from left to right.
 */
struct red_blue_sort_segment_xy : public std::unary_function<gde::geom::core::line_segment,
                                                             std::pair<gde::geom::core::line_segment,
                                                                       gde::geom::core::color_type> >
{
  gde::geom::core::color_type color;
  
  red_blue_sort_segment_xy(gde::geom::core::color_type c)
    : color(c)
  {
  }
  
  std::pair<gde::geom::core::line_segment,
            gde::geom::core::color_type> operator()(const gde::geom::core::line_segment& s)
  {
    if(s.p1.x < s.p2.x)
      return std::make_pair(s, color);
          
    if(s.p1.x > s.p2.x)
      return std::make_pair(gde::geom::core::line_segment(s.p2, s.p1), color);
          
    if(s.p1.y < s.p2.y)
      return std::make_pair(s, color);
          
    if(s.p1.y > s.p2.y)
      return std::make_pair(gde::geom::core::line_segment(s.p2, s.p1), color);
          
    return std::make_pair(s, color);
  }
};

struct red_blue_segment_xy_cmp : std::less<std::pair<gde::geom::core::line_segment,
                                                     gde::geom::core::color_type> >
{
  bool operator()(const std::pair<gde::geom::core::line_segment,
                                  gde::geom::core::color_type>& lhs,
                  const std::pair<gde::geom::core::line_segment,
                                  gde::geom::core::color_type>& rhs) const
  {
    if(lhs.first.p1.x < rhs.first.p1.x)
      return true;
          
    if(lhs.first.p1.x > rhs.first.p1.x)
      return false;
          
    if(lhs.first.p1.y < rhs.first.p1.y)
      return true;
    
    return false;
  }
};

std::vector<gde::geom::core::point>
gde::geom::algorithm::x_order_intersection_rb(const std::vector<gde::geom::core::line_segment>& red_segments,
                                              const std::vector<gde::geom::core::line_segment>& blue_segments)
{
// output list of intersection points
  std::vector<gde::geom::core::point> ipts;

  const std::size_t nred_segments = red_segments.size();
  
  const std::size_t nblue_segments = blue_segments.size();

// check if we have at least two segments to test!
  if((nred_segments == 0) || (nblue_segments == 0))
    return ipts;
  
  const std::size_t nsegments = nred_segments + nblue_segments;

// create new segment vectors with the same size as input ones
  std::vector<std::pair<gde::geom::core::line_segment,
                        gde::geom::core::color_type> > ordered_segments(nsegments);
  
// copy the input segments but make sure segments will be left-right ordered
  auto it = std::transform(red_segments.begin(), red_segments.end(), ordered_segments.begin(), red_blue_sort_segment_xy(gde::geom::core::RED));
  std::transform(blue_segments.begin(), blue_segments.end(), it, red_blue_sort_segment_xy(gde::geom::core::BLUE));

// sort all the segments from left to right
  std::sort(ordered_segments.begin(), ordered_segments.end(), red_blue_segment_xy_cmp());

// retain intersection points between tests
  gde::geom::core::point ip1, ip2;
  
  const std::size_t nbands = nsegments - 1;

// first scan ordered_segments from the first segment
  for(std::size_t i = 0; i < nbands; ++i)
  {
    const auto& current_seg = ordered_segments[i];

// scan segments from i + 1
    for(std::size_t j = i + 1; j < nsegments; ++j)
    {
      const auto& next_seg = ordered_segments[j];

// if beginning x-coordinate of the next-segment is greater than
// the end x-coordinate of the current-segment, they can not intersect
// and all following sgments will be out-of current segment
// interval => stop: no more segments can intersects.
      if(current_seg.first.p2.x < next_seg.first.p1.x)
        break;
      
// if segments have the same color, we don't compare!
      if(current_seg.second == next_seg.second)
        continue;

// if segments y-interval don't intersect they will not have intersection,
// let's test the next segment!
      if(!do_y_interval_intersects(current_seg.first, next_seg.first))
        continue;
      
// check for intersection
      segment_relation_type result = compute_intesection_v3(current_seg.first, next_seg.first, ip1, ip2);
      
      if(result == DISJOINT)
        continue;
      
      ipts.push_back(ip1);
      
      if(result == OVERLAP)
        ipts.push_back(ip2);
    }
  }

  return ipts;
}

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
  \file gde/geom/algorithm/lazy_line_segments_intersection.cpp

  \brief Given a set of segments compute the intersection points between each pair with O(n^2) algorithm.

  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

// GDE
#include "line_segments_intersection.hpp"
#include "line_segment_intersection.hpp"

std::vector<gde::geom::core::point>
gde::geom::algorithm::lazy_intersection(const std::vector<gde::geom::core::line_segment>& segments)
{
  std::vector<gde::geom::core::point> result;
  gde::geom::core::point ip1;
  gde::geom::core::point ip2;

  const std::size_t number_of_segments = segments.size();

  for(std::size_t i = 0; i < (number_of_segments - 1); ++i)
  {
    const gde::geom::core::line_segment& red = segments[i];

    for(std::size_t j = i + 1; j < number_of_segments; ++j)
    {
      const gde::geom::core::line_segment& blue = segments[j];
      
      if(!do_bounding_box_intersects(red, blue))
        continue;

      segment_relation_type spatial_relation = compute_intesection_v3(red, blue, ip1, ip2);

      if(spatial_relation == DISJOINT)
        continue;

      result.push_back(ip1);

      if(spatial_relation == OVERLAP)
        result.push_back(ip2);
    }
  }

  return result;
}

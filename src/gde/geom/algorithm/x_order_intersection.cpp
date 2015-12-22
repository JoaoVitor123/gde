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

// copy the input segments to ordered_segments and invert the extreme points if needed
  std::transform(segments.begin(), segments.end(), ordered_segments.begin(), sort_xy());

// sort the segments from left to right
  std::sort(ordered_segments.begin(), ordered_segments.end(), line_segment_xy_cmp());

  std::vector<gde::geom::core::point> ipts;
  
  gde::geom::core::point p1, p2;

// first scan in ordered_segments
  for (int i = 0; i < ordered_segments.size(); ++i)
  {
// segunda varredura do ponto atual em diante
    for (int j = i; j < ordered_segments.size(); j++)
    {

// verifies that the value of the first scan does not have more intersection
      if(ordered_segments[i].p2.x < ordered_segments[j].p1.x)
        break;
      else
      {
// varifica the intersection
        if(gde::geom::algorithm::do_intersects_v3(ordered_segments[i], ordered_segments[j]))
        {

// Compute the intersection point
          gde::geom::algorithm::compute_intesection_v3(ordered_segments[i], ordered_segments[j], p1, p2);
          ipts.push_back(p1);
        }
      }
    }
  }
/*
  segments_order = segments_ord(segments);
  int cont = 0, cont_aux = 0;
// X-ordering
  for(const auto& value: segments_order)
  {
    ++cont;
    //std::cout << cont << "\n";
    //std::cout << value.p1.y << "\n";
    for(const auto& value2: segments_order)
    {
      if(cont_aux > cont && value.p2.x < value2.p1.x && value.p2.y < value2.p1.y && value.p1.y > value2.p2.y)// varedura y delimitada
      {
        if(gde::geom::algorithm::do_intersects_v3(value, value2))
        {
          gde::geom::algorithm::compute_intesection_v3(value, value2, p1, p2);
          std::cout << "X ordening point:  x = "<< p1.x <<  "  y = " << p1.y  << "\n";
        }
      }
      ++cont_aux;
    }
  }*/

  return ipts;
}

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
  \file gde/geom/algorithm/line_segment_intersection.hpp

  \brief Algorithms for computing line segment intersection.

  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

// GDE
#include "line_segment_intersection.hpp"
#include "../core/geometric_primitives.hpp"

bool
gde::geom::algorithm::do_intersects(const gde::geom::core::line_segment& s1,
                                    const gde::geom::core::line_segment& s2)
{
  double ax = s1.p2.x - s1.p1.x;
  double ay = s1.p2.y - s1.p1.y;
  
  double bx = s2.p1.x - s2.p2.x;
  double by = s2.p1.y - s2.p2.y;
  
  double den = ay * bx - ax * by;
  
  if(den == 0)
  {
// they are collinear
    // do they intersect? we need a special handling
    if(s1.p2.x < s2.p1.x || s2.p2.x < s1.p1.x)
        return "D"; // Segments are disjoint

    else if (s1.p2.x == s2.p1.x)
    {
      // touch

    }

    else if (s2.p2.x == s1.p1.x)
    {
      // touch

    }

    else if( s1.p1.x == s2.p1.x || s1.p2.x == s2.p2.x)
    {
      // equal segments, overlap
      gde::geom::core::point  p1;
      gde::geom::core::point  p2;

      p1.x = s1.p1.x; p1.y = s1.p1.y;
      p2.x = s1.p2.x; p2.y = s1.p2.y;
    }

    else if(s1.p1.x < s2.p1.x || s1.p2.x > s2.p2.x)
    {
      // s2 within the s1, overlap
      gde::geom::core::point  p1;
      gde::geom::core::point  p2;

      p1.x = s2.p1.x;  p1.y = s2.p1.y;
      p2.x = s2.p2.x;  p2.y = s2.p2.y;
    }

    else if(s1.p1.x < s2.p1.x || s1.p2.x > s2.p2.x)
    {
      // s2 within the s1, overlap
      gde::geom::core::point  p1;
      gde::geom::core::point  p2;

      p1.x = s2.p1.x;  p1.y = s2.p1.y;
      p2.x = s2.p2.x;  p2.y = s2.p2.y;
    }

    else if(s2.p1.x < s1.p1.x)
    {
      // Segments overlap
      gde::geom::core::point  p1;
      gde::geom::core::point  p2;

      p1.x = s1.p1.x;  p1.y = s1.p1.y;
      p2.x = s2.p2.x;  p2.y = s2.p2.y;
    }

    else if(s1.p1.x < s2.p2.x)
    {
      // Segments overlap
      gde::geom::core::point  p1;
      gde::geom::core::point  p2;

      p1.x = s2.p1.x;  p1.y = s2.p1.y;
      p2.x = s1.p2.x;  p2.y = s1.p2.y;
    }
  }

// they are not collinear, let's see if they intersects
  double cx = s1.p1.x - s2.p1.x;
  double cy = s1.p1.y - s2.p1.y;
  
// is alpha in the range [0..1]
  double num_alpha = by * cx - bx * cy;

  if(den > 0)
  {
    
// is alpha before the range [0..1] or after it?
    if((num_alpha < 0) or (num_alpha > den))
      return false;
  }
  else // den < 0
  {
// is alpha before the range [0..1] or after it?
    if((num_alpha > 0) or (num_alpha < den))
      return false;
  }

// is beta in the range [0..1]
  double num_beta = ay * bx - ax * by;
  
  if(den > 0)
  {
// is beta before the range [0..1] or after it?
    if((num_beta < 0) or (num_beta > den))
      return false;
  }
  else // den < 0
  {
// is beta before the range [0..1] or after it?
    if((num_beta > 0) or (num_beta < den))
      return false;
  }
  
  return true;
}

gde::geom::algorithm::segment_relation_type
gde::geom::algorithm::compute_intesection(const gde::geom::core::line_segment& s1,
                                          const gde::geom::core::line_segment& s2,
                                          gde::geom::core::point& first,
                                          gde::geom::core::point& second)
{
    double ax = s1.p2.x - s1.p1.x;
    double ay = s1.p2.y - s1.p1.y;
    double bx = s2.p1.x - s2.p2.x;
    double by = s2.p1.y - s2.p2.y;

    double den = ay * bx - ax * by;
    double num_beta = ay * bx - ax * by;

    double beta = den / num_beta;

    first.x = (s1.p1.x + (beta * ax));
    first.y = (s1.p1.y + (beta * ay));

  return DISJOINT;
}


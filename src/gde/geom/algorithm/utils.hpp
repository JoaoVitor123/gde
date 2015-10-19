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
  \file gde/geom/algorithm/utils.hpp

  \brief Utility functions for geometric algorithms.

  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

#ifndef __GDE_GEOM_ALGORITHM_UTILS_HPP__
#define __GDE_GEOM_ALGORITHM_UTILS_HPP__

// GDE
#include "../core/geometric_primitives.hpp"

namespace gde
{
  namespace geom
  {
    namespace algorithm
    {
      /*!
        \brief Test if the point p collinear to the end-points of segment s is inside it or not.

        \return True if point p is between the end-points (including both) of segment s and false, otherwise.
       */
      inline bool
      is_collinear_point_on_segment(const gde::geom::core::point& p, const gde::geom::core::line_segment& s)
      {
// is p to the left of s?
        if((p.x < s.p1.x) && (p.x < s.p2.x)) 
          return false;

// is p to the right of s?
        if((p.x > s.p1.x) && (p.x > s.p2.x)) 
          return false;

// is p below s?
        if((p.y < s.p1.y) && (p.y < s.p2.y)) 
          return false;

// is p above s?
        if((p.y > s.p1.y) && (p.y > s.p2.y)) 
          return false;

        return true;
      }

      /*!
        \brief Test if point p is on segment s.

        \note This implementation is adapted from Alan Paeth's method presented in Graphics Gems I, page 49.
       */
      inline bool
      is_point_on_segment(const gde::geom::core::point& p, const gde::geom::core::line_segment& s)
      {
        double ax = s.p2.x - s.p1.x;
        double ay = s.p2.y - s.p1.y;

        double bx = p.x - s.p1.x;
        double by = p.y - s.p1.y;

        double cross_product = ax * by - ay * bx;

        if(cross_product != 0.0)
          return false;

// ok: point is on  the straight line defined by segment s
//     let's check if it is in the segment range
        return is_collinear_point_on_segment(p, s);
      }

    } // end namespace algorithm
  }   // end namespace geom
}     // end namespace gde

#endif // __GDE_GEOM_ALGORITHM_UTILS_HPP__
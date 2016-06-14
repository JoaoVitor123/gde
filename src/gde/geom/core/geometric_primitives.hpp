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
  \file gde/geom/core/geometric_primitives.hpp

  \brief Definition of basic geometric primitices: points, line segments and polylines.

  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

#ifndef __GDE_GEOM_CORE_GEOMETRIC_PRMITIVES_HPP__
#define __GDE_GEOM_CORE_GEOMETRIC_PRMITIVES_HPP__

// STL
#include <limits>

namespace gde
{
  namespace geom
  {
    namespace core
    {

      /*!
        \struct point

        \brief Defines a point in 2D space.
       */
      struct point
      {
        double x;
        double y;
        
        //bool operator==(const gde::geom::core::point& rhs) const
        //{
        //  return (x == rhs.x) && (y == rhs.y);
        //}
      };

      /*!
        \struct line_segment

        \brief Representation for line segments.
       */
      struct line_segment
      {
        point p1;
        point p2;
        
        line_segment() { }
        
        line_segment(const point& pt1, const point& pt2)
          : p1(pt1), p2(pt2)
        { }
      };
      
      inline bool operator==(const point& lhs, const point& rhs)
      {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
      }
      
      /*!
       \struct rectangle
       
       \brief Representation for rectangles.
       */
      struct rectangle
      {
        point ll;
        point ur;
        
        rectangle()
        {
          ll.x = std::numeric_limits<double>::infinity();
          ll.y = std::numeric_limits<double>::infinity();
          
          ur.x = - std::numeric_limits<double>::infinity();
          ur.y = - std::numeric_limits<double>::infinity();
        }
        
        rectangle(double llx, double lly, double urx, double ury)
        {
          ll.x = llx;
          ll.y = lly;
          
          ur.x = urx;
          ur.y = ury;
        }
        
        rectangle(const point& lower_left, const point& upper_right)
        : ll(lower_left), ur(upper_right)
        { }
      };

      
      /*!
        \enum color_type

        \brief For algorithms that must color items.
       */
      enum color_type
      {
        RED,
        BLUE
      };

    } // end namespace core
  } // end namespace geom
} // end namespace gde



#endif // __GDE_GEOM_CORE_GEOMETRIC_PRMITIVES_HPP__


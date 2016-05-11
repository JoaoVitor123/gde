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

// STL
#include <algorithm>
#include <functional>

namespace gde
{
  namespace geom
  {
    namespace algorithm
    {
      /*! \brief Test if values v1 and v2 have the same sign. */
      inline bool same_signs(double v1, double v2)
      {
        return ((v1 > 0.0 && v2 > 0.0) || (v1 < 0.0 && v2 < 0.0)) ? true : false;
      }

      /*!
        \brief Check if bounding box intersects.
       
        \note This version will not take into account the segments order.
       */
      inline bool
      do_bounding_box_intersects(const gde::geom::core::line_segment& s1,
                                 const gde::geom::core::line_segment& s2)
      {
// function that returns the largest and smallest among its parameters
        const auto&  minmax1 = std::minmax(s1.p1.x, s1.p2.x);
        const auto&  minmax2 = std::minmax(s2.p1.x, s2.p2.x);

// s1 is to right or left of s2?
        if((minmax1.first > minmax2.second) || (minmax1.second < minmax2.first))
          return false;

// function that returns the largest and smallest among its parameters
        const auto&  minmax3 = std::minmax(s1.p1.y, s1.p2.y);
        const auto&  minmax4 = std::minmax(s2.p1.y, s2.p2.y);

// s1 is to above or below of s2?
        if((minmax3.first > minmax4.second) || (minmax3.second < minmax4.first))
          return false;

        return true;
      }
      
      /*!
        \brief Check if bounding box intersects.
       
        \note This version will assume that segments are left-right ordered.
       */
      inline bool
      do_bounding_box_intersects_v2(const gde::geom::core::line_segment& s1,
                                    const gde::geom::core::line_segment& s2)
      {
// if s1 is to left of s2, they don't intersects
        if(s1.p2.x < s2.p1.x)
          return false;
        
// if s1 is to right of s2, they don't intersects
        if(s1.p1.x > s2.p2.x)
          return false;
        
// find min and max y for each segment
        const auto&  s1_minmax_y = std::minmax(s1.p1.y, s1.p2.y);
        const auto&  s2_minmax_y = std::minmax(s2.p1.y, s2.p2.y);
        
// if s1 is below s2, they don't intersects
        if(s1_minmax_y.second < s2_minmax_y.first)
          return false;

// if s1 is above s2, they don't intersects
        if(s1_minmax_y.first > s2_minmax_y.second)
          return false;
        
        return true;
      }
      
      /*!
        \brief Check if segments interval-y intersects.
       */
      inline bool
      do_y_interval_intersects(const gde::geom::core::line_segment& s1,
                               const gde::geom::core::line_segment& s2)
      {
 // find min and max y for each segment
        const auto&  s1_minmax_y = std::minmax(s1.p1.y, s1.p2.y);
        const auto&  s2_minmax_y = std::minmax(s2.p1.y, s2.p2.y);
        
// if s1 is below s2, they don't intersects
        if(s1_minmax_y.second < s2_minmax_y.first)
          return false;
        
// if s1 is above s2, they don't intersects
        if(s1_minmax_y.first > s2_minmax_y.second)
          return false;
        
        return true;
      }

      /*!
        \brief checks if the number is negative.
       */
      inline double
      return_positive_value(const double& d)
      {
        if(d < 0)
          return (d * (-1));
        else
          return d;
      }

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
      
      /*!
        \struct line_segment_xy_cmp
       
        A functor to compare two segments from left to right.
       
        \pre Both segments must be left-right ordered.
       */
      struct line_segment_xy_cmp : std::less<gde::geom::core::line_segment>
      {
        bool operator()(const gde::geom::core::line_segment& lhs,
                        const gde::geom::core::line_segment& rhs) const
        {
          if(lhs.p1.x < rhs.p1.x)
            return true;
          
          if(lhs.p1.x > rhs.p1.x)
            return false;
          
          if(lhs.p1.y < rhs.p1.y)
            return true;
          
          //if(lhs.p1.y > rhs.p1.y)
          //  return false;
          
          return false;
        }
      };
      
      /*!
        \struct point_xy_cmp
       
        A functor to compare two points: left to right.
       */
      struct point_xy_cmp : std::less<gde::geom::core::point>
      {
        bool operator()(const gde::geom::core::point& lhs,
                        const gde::geom::core::point& rhs) const
        {
          if(lhs.x < rhs.x)
            return true;
          
          if(lhs.x > rhs.x)
            return false;
          
          if(lhs.y < rhs.y)
            return true;
          
          //if(lhs.y > rhs.y)
          //  return false;
          
          return false;
        }
      };
      
      /*!
        \struct sort_segment_xy
       
        Given a line segment it will build a new one ordered from left to right.
       */
      struct sort_segment_xy : public std::unary_function<gde::geom::core::line_segment,
                                                          gde::geom::core::line_segment>
      {
        gde::geom::core::line_segment operator()(const gde::geom::core::line_segment& s)
        {
          if(s.p1.x < s.p2.x)
            return s;
          
          if(s.p1.x > s.p2.x)
            return gde::geom::core::line_segment(s.p2, s.p1);
          
          if(s.p1.y < s.p2.y)
            return s;
          
          if(s.p1.y > s.p2.y)
            return gde::geom::core::line_segment(s.p2, s.p1);
          
          return s;
        }
      };      
    } // end namespace algorithm
  }   // end namespace geom
}     // end namespace gde

#endif // __GDE_GEOM_ALGORITHM_UTILS_HPP__

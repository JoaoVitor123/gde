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
  \file gde/geom/algorithm/line_segments_intersection.hpp

  \brief Algorithms for computing intersection points between a set of line segments.

  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

#ifndef __GDE_GEOM_ALGORITHM_LINE_SEGMENTS_INTERSECTION_HPP__
#define __GDE_GEOM_ALGORITHM_LINE_SEGMENTS_INTERSECTION_HPP__

// GDE
#include "../core/geometric_primitives.hpp"

// STL
#include <vector>

namespace gde
{
  namespace geom
  {
    namespace algorithm
    {

      /*!
        \brief Given a set of segments compute the intersection points between each pair.

        This implementation uses a brute force approach. It's complexity is O(n^2).

        \note This is an O(n^2) algorithm.
       */
      std::vector<gde::geom::core::point>
      lazy_intersection(const std::vector<gde::geom::core::line_segment>& segments);

      /*!
        \brief Given two poly-lines, named red and blue, compute the intersection points between their segments.

        \note This is an O(n^2) algorithm.
       */
      //std::vector<gde::geom::core::point>
      //lazy_intersection(gde::geom::core::line_string& red_line,
      //                  gde::geom::core::line_segment& blue_line);

      /*!
        \brief Given a set of segments compute the intersection points between each pair.
        
        This algorithm is based on the Plane Sweep paradigm.

        \note This is an O(n log(n) + k log(n)) algorithm.
       */
      //std::vector<gde::geom::core::point>
      //bentley_ottman_intersection(std::vector<gde::geom::core::line_segment>& segments);

      /*!
        \brief Given two poly-lines, named red and blue, compute the intersection points between their segments.

        This algorithm is based on the plane sweep paradigm.

        \note This is an O(n log(n) + k log(n)) algorithm.
       */
      //std::vector<gde::geom::core::point>
      //bentley_ottman_intersection(gde::geom::core::line_string& red_line,
      //                            gde::geom::core::line_segment& blue_line);

      /*!
        \brief Given a set of segments compute the intersection points between each pair.

        This algorithm sorts all input segments by x-coordinate and then 
        utilizes a brute force algorithm to compute intersection points
        between segments that overlap.

        \note This algorithm has a worst-case performance of O(n^2), but in practice it is very competitive.
       */
      std::vector<gde::geom::core::point>
      x_order_intersection(const std::vector<gde::geom::core::line_segment>& segments);

      /*!
        \brief Given two poly-lines, named red and blue, compute the intersection points between their segments.

        This algorithm sorts all input segments by x-coordinate and then 
        utilizes a brute force algorithm to compute intersection points
        between segments that overlap.

        \note This algorithm has a worst-case performance of O(n^2), but in practice it is very competitive.
       */
      //std::vector<gde::geom::core::point>
      //x_order_intersection(gde::geom::core::line_string& red_line,
      //                     gde::geom::core::line_segment& blue_line);

      /*!
        \brief Given a set of segments compute the intersection points between each pair.

        This algorithm separates all the segments into blocks according to their y-coordinate , and then ,
        using an x -order algorithm to find the intersection points
        between segments of each block.

        \note ????.
       */
      std::vector<gde::geom::core::point>
      tiling_intersection(const std::vector<gde::geom::core::line_segment>& segments,
                          const double& max_length, const double& max_range, const double& min_range);

    } // end namespace algorithm
  }   // end namespace geom
}     // end namespace gde

#endif // __GDE_GEOM_ALGORITHM_LINE_SEGMENTS_INTERSECTION_HPP__


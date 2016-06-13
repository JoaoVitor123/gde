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
        \brief Given a set of segments compute the intersection points between each pair of segments.

        This implementation is based on a brute force approach.
        It's complexity is O(n^2), where n is the number of segments in the input set.

        \note This is an O(n^2) algorithm.
       */
      std::vector<gde::geom::core::point>
      lazy_intersection(const std::vector<gde::geom::core::line_segment>& segments);

      /*!
        \brief Given two set of segments, called red and blue sets, compute the intersection points
               between red and blue segments.

        This implementation is based on a brute force approach.
        It's complexity is O(n*m), where n is the number of segments in the red set and
        m is the number of segments in the blue set.

        \note This is an O(n*m) algorithm.
       */
      std::vector<gde::geom::core::point>
      lazy_intersection_rb(const std::vector<gde::geom::core::line_segment>& red_segments,
                           const std::vector<gde::geom::core::line_segment>& blue_segments);

      /*!
        \brief Given a set of segments compute the intersection points between each pair of segments.

        This implementation is based on a brute force approach. Therefore
        it will apply a given number of threads to compute the intersections.
        
        Although it uses threads, the whole complexity
        still O(n^2), where n is the number of segments in the input set.

        \note This is an O(n^2) algorithm.
       */
      void
      lazy_intersection_thread(const std::vector<gde::geom::core::line_segment>& segments,
                               std::size_t nthreads,
                               std::vector<std::vector<gde::geom::core::point> >& intersetion_pts);

      /*!
        \brief Given two set of segments, called red and blue sets, compute the intersection points
               between red and blue segments.
       
        This implementation is based on a brute force approach. Therefore
        it will apply a given number of threads to compute the intersections.
       
        Although it uses threads, the whole complexity
        still O(n*m), where n is the number of segments in the red set and
        m is the number of segments in the blue set.
       
        \note This is an O(n*m) algorithm.
       */
      void
      lazy_intersection_rb_thread(const std::vector<gde::geom::core::line_segment>& red_segments,
                                  const std::vector<gde::geom::core::line_segment>& blue_segments,
                                  std::size_t nthreads,
                                  std::vector<std::vector<gde::geom::core::point> >& intersetion_pts);

      /*!
        \brief Given a set of segments compute the intersection points between each pair.

        This algorithm sorts all input segments by x-coordinate and then 
        utilizes a brute force algorithm to compute intersection points
        between segments that overlap.
        
        This algorithm works like a plane-sweep, but it sweeps along
        only one direction.
        
        The worst-case performance is O(n^2), where n is the number of
        input segments. Therefore, the expected running time will depend
        on the number of segments in the vertical bands defined by
        the x-ordering of the segments. It will be O(n * E(n)), where E(n)
        is the average number of segments in each vertical band.

        \note This algorithm has a worst-case performance of O(n^2), but in practice it is very competitive.
       */
      std::vector<gde::geom::core::point>
      x_order_intersection(const std::vector<gde::geom::core::line_segment>& segments);

      /*!
        \brief Given two set of segments, called red and blue sets, compute the intersection points
               between red and blue segments.

        This algorithm works like a plane-sweep, but it sweeps along
        only one direction.
        
        The worst-case performance is O(n*m), where n is the number of segments
        in the red set and m is the number of segments in the blue set.
        Therefore, the expected running time will depend
        on the number of blue segments in the vertical bands defined by
        each red segment. It will be O(n * E(m)), where E(m)
        is the average number of segments in each vertical band.

        \note This algorithm has a worst-case performance of O(n*m), but in practice it is very competitive.
       */

      std::vector<gde::geom::core::point>
      x_order_intersection_rb(const std::vector<gde::geom::core::line_segment>& red_segments,
                              const std::vector<gde::geom::core::line_segment>& blue_segments);
      
      std::vector<gde::geom::core::point>
      x_order_intersection_rb2(const std::vector<gde::geom::core::line_segment>& red_segments,
                               const std::vector<gde::geom::core::line_segment>& blue_segments);

      /*!
        \brief Given a set of segments compute the intersection points between each pair.

        This algorithm sorts all input segments by x-coordinate and then 
        utilizes a brute force algorithm to compute intersection points
        between segments that overlap. Therefore
        it will apply a given number of threads to compute the intersections.
        
        This algorithm works like a plane-sweep, but it sweeps along
        only one direction.
        
        The worst-case performance is O(n^2), where n is the number of
        input segments. Therefore, the expected running time will depend
        on the number of segments in the vertical bands defined by
        the x-ordering of the segments. It will be O(n * E(n)), where E(n)
        is the average number of segments in each vertical band.

        \note This algorithm has a worst-case performance of O(n^2), but in practice it is very competitive.
       */
      void
      x_order_intersection_thread(const std::vector<gde::geom::core::line_segment>& segments,
                                  std::size_t nthreads,
                                  std::vector<std::vector<gde::geom::core::point> >& intersetion_pts);
      
      /*!
        \brief Given two set of segments, called red and blue sets, compute the intersection points
               between red and blue segments.

        This algorithm works like a plane-sweep, but it sweeps along
        only one direction.
        
        The worst-case performance is O(n*m), where n is the number of segments
        in the red set and m is the number of segments in the blue set.
        Therefore, the expected running time will depend
        on the number of blue segments in the vertical bands defined by
        each red segment. It will be O(n * E(m)), where E(m)
        is the average number of segments in each vertical band.

        \note This algorithm has a worst-case performance of O(n*m), but in practice it is very competitive.
       */
      void
      x_order_intersection_rb_thread(const std::vector<gde::geom::core::line_segment>& red_segments,
                                     const std::vector<gde::geom::core::line_segment>& blue_segments,
                                     std::size_t nthreads,
                                     std::vector<std::vector<gde::geom::core::point> >& intersection_pts);
      
      
      std::vector<gde::geom::core::point>
      fixed_grid_intersection_rb(const std::vector<gde::geom::core::line_segment>& red_segments,
                                 const std::vector<gde::geom::core::line_segment>& blue_segments,
                                 double dx, double dy, double xmin, double xmax,
                                 double ymin, double ymax);


      /*!
        \brief Given a set of segments compute the intersection points between each pair.

        This algorithm separates all the segments into blocks according to their y-coordinate , and then ,
        using an x -order algorithm to find the intersection points
        between segments of each block.

        \note ????.
       */
//      std::vector<gde::geom::core::point>
//      tiling_intersection(const std::vector<gde::geom::core::line_segment>& segments,
//                          const double& max_length, const double& max_range, const double& min_range);

      /*!
        \brief Given a set of segments red and blue compute the intersection points between each pair.

        This algorithm separates all the segments into blocks according to their y-coordinate , and then ,
        using an x -order algorithm to find the intersection points
        between segments of each block.

        \note ????.
       */

//      std::vector<gde::geom::core::point>
//      tiling_intersection_rb(const std::vector<gde::geom::core::line_segment>& red,
//                             const std::vector<gde::geom::core::line_segment>& blue,
//                             const double& max_length_r, const double& max_range_r, const double& min_range_r,
//                             const double& max_length_b, const double& max_range_b, const double& min_range_b);

      /*!
        \brief Given a set of segments compute the intersection points between each pair with thread.

        This algorithm separates all the segments into blocks according to their y-coordinate , and then ,
        using an x -order algorithm to find the intersection points
        between segments of each block.

        \note ????.
       */

//      std::size_t
//      tiling_intersection_thread(const std::vector<gde::geom::core::line_segment>& segments,
//                                 const double& max_length, const double& max_range, const double& min_range);


    } // end namespace algorithm
  }   // end namespace geom
}     // end namespace gde

#endif // __GDE_GEOM_ALGORITHM_LINE_SEGMENTS_INTERSECTION_HPP__


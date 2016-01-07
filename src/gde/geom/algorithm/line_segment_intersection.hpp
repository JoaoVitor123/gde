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

#ifndef __GDE_GEOM_ALGORITHM_LINE_SEGMENT_INTERSECTION_HPP__
#define __GDE_GEOM_ALGORITHM_LINE_SEGMENT_INTERSECTION_HPP__

// GDE
#include "utils.hpp"

namespace gde
{
  namespace geom
  {
// Forward declaration of point and line segment.
    namespace core
    {
      struct point;
      struct line_segment;
    }

    namespace algorithm
    {
      /*!
        \enum segment_relation_type

        \brief The type of spatial relation between two segments.
       */
      enum segment_relation_type
      {
        DISJOINT, //!< Segments are disjoint: they have no intersection point.
        CROSS,    //!< Segments crosses in a single inner point.
        TOUCH,    //!< Segments touches in one of their end-points.
        OVERLAP   //!< Segments overlap: their intersection is another segment.
      };
      
      /*! \brief Test if two collinear segments intersects. */
      inline bool
      do_collinear_segments_intersects(const gde::geom::core::line_segment& s1,
                                       const gde::geom::core::line_segment& s2)
      {
        if(is_collinear_point_on_segment(s1.p1, s2))
          return true;
        
        if(is_collinear_point_on_segment(s1.p2, s2))
          return true;
        
        if(is_collinear_point_on_segment(s2.p1, s1))
          return true;
        
        if(is_collinear_point_on_segment(s2.p2, s1))
          return true;
        
        return false;
      }

      /*!
        \brief Test if both segments intersects.

        \note Based on the algorithm of Mukesh Prasad (1991) in Graphics Gems II, page 7.

        \note Doesn't perform  bounding box intersect test between segments.
       */
      bool
      do_intersects_v1(const gde::geom::core::line_segment& s1,
                       const gde::geom::core::line_segment& s2);

      /*!
        \brief Test if both segments intersects.

        \note Based on the algorithm of Shaffer and Feustel (1992) in Graphics Gems III.

        \note Doesn't perform  bounding box intersect test between segments.
       */
      bool
      do_intersects_v2(const gde::geom::core::line_segment& s1,
                       const gde::geom::core::line_segment& s2);

      /*!
        \brief Test if both segments intersects.
       
        \note Based on the algorithm of Franklin Antonio (1992) in Graphics Gems III.

        \note Doesn't perform  bounding box intersect test between segments.
       */
      bool
      do_intersects_v3(const gde::geom::core::line_segment& s1,
                       const gde::geom::core::line_segment& s2);

      /*!
        \brief Compute the intersection point between two line segments, if one exists.

        \return The type of intersection between line segments.

        \note Based on the algorithm of Mukesh Prasad in Graphics Gems II, page 7.

        \note Doesn't perform bounding box intersect test between segments.
       */
      segment_relation_type
      compute_intesection_v1(const gde::geom::core::line_segment& s1,
                             const gde::geom::core::line_segment& s2,
                             gde::geom::core::point& first,
                             gde::geom::core::point& second);
      
      /*!
       \brief Compute the intersection point between two line segments, if one exists.
       
       \return The type of intersection between line segments.
       
       \note Based on the algorithm of ...

       \note Doesn't perform  bounding box intersect test between segments.
       */
      segment_relation_type
      compute_intesection_v2(const gde::geom::core::line_segment& s1,
                             const gde::geom::core::line_segment& s2,
                             gde::geom::core::point& first,
                             gde::geom::core::point& second);
      
      
      /*!
        \brief Compute the intersection point between two line segments, if one exists.
       
        \return The type of intersection between line segments.

        \note Based on the algorithm of Franklin Antonio (1992) in Graphics Gems III.

        \note Doesn't perform  bounding box intersect test between segments.
       */
      segment_relation_type
      compute_intesection_v3(const gde::geom::core::line_segment& s1,
                             const gde::geom::core::line_segment& s2,
                             gde::geom::core::point& first,
                             gde::geom::core::point& second);

    } // end namespace algorithm
  }   // end namespace geom
}     // end namespace gde

#endif // __GDE_GEOM_ALGORITHM_LINE_SEGMENT_INTERSECTION_HPP__


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

// STL
#include <algorithm>

namespace gde
{
  namespace geom
  {
    namespace algorithm
    {
      bool point_cmp(const gde::geom::core::point* p1, const gde::geom::core::point* p2)
      {
        if(p1->x < p2->x)
          return true;

        if(p1->x > p2->x)
          return false;

        if(p1->y < p2->y)
          return true;

        return false;
      }
    }
  }
}

bool
gde::geom::algorithm::do_intersects_v1(const gde::geom::core::line_segment& s1,
                                       const gde::geom::core::line_segment& s2)
{
// compute general line equation for segment s1
  double a1 = s1.p2.y - s1.p1.y;
  double b1 = s1.p1.x - s1.p2.x;
  double c1 = (s1.p2.x * s1.p1.y) - (s1.p1.x * s1.p2.y);

  double r3 = a1 * s2.p1.x + b1 * s2.p1.y + c1;
  double r4 = a1 * s2.p2.x + b1 * s2.p2.y + c1;

// if both points from segment s2 are to the sime side of line defined by segment s1,
// we are sure s2 can not intersects s1
  if((r3 != 0.0) && (r4 != 0.0) && same_signs(r3, r4))
    return false;

// compute general line equation for segment s2
  double a2 = s2.p2.y - s2.p1.y;
  double b2 = s2.p1.x - s2.p2.x;
  double c2 = (s2.p2.x * s2.p1.y) - (s2.p1.x * s2.p2.y);

  double r1 = a2 * s1.p1.x + b2 * s1.p1.y + c2;
  double r2 = a2 * s1.p2.x + b2 * s1.p2.y + c2;

// if both points from segment s1 are to the sime side of line defined by segment s2,
// we are sure s1 can not intersects s2
  if((r1 != 0.0) && (r2 != 0.0) && same_signs(r1, r2))
    return false;

// ok: we know tha segments may overlap or cross at a single point!
  return true;
}

bool
gde::geom::algorithm::do_intersects_v2(const gde::geom::core::line_segment& s1,
                                       const gde::geom::core::line_segment& s2)
{
  double a = (s2.p1.x - s1.p1.x) * (s1.p2.y - s1.p1.y) - (s2.p1.y - s1.p1.y) * (s1.p2.x - s1.p1.x);
  double b = (s2.p2.x - s1.p1.x) * (s1.p2.y - s1.p1.y) - (s2.p2.y - s1.p1.y) * (s1.p2.x - s1.p1.x);

// if the endpoints of the second segment lie on the opposite
  if((a != 0.0) && (b != 0.0) && same_signs(a, b))
    return false;

  double c = (s1.p1.x - s2.p1.x) * (s2.p2.y - s2.p1.y) - (s1.p1.y - s2.p1.y) * (s2.p2.x - s2.p1.x);
  double d = (s1.p2.x - s2.p1.x) * (s2.p2.y - s2.p1.y) - (s1.p2.y - s2.p1.y) * (s2.p2.x - s2.p1.x);

// if the endpoints of the first segment lie on the opposite
  if((c != 0.0) && (d != 0.0) && same_signs(c, d))
    return false;

// are the segments collinear?
  double det = a - b;

  if(det == 0.0)
    return do_collinear_segments_intersects(s1, s2);

// the segments intersect
  return true;
}

bool
gde::geom::algorithm::do_intersects_v3(const gde::geom::core::line_segment& s1,
                                       const gde::geom::core::line_segment& s2)
{
  double ax = s1.p2.x - s1.p1.x;
  double ay = s1.p2.y - s1.p1.y;

  double bx = s2.p1.x - s2.p2.x;
  double by = s2.p1.y - s2.p2.y;

  double den = ay * bx - ax * by;

// are they collinear?
  if(den == 0.0)
    return do_collinear_segments_intersects(s1, s2);

// they are not collinear, let's see if they intersects
  double cx = s1.p1.x - s2.p1.x;
  double cy = s1.p1.y - s2.p1.y;

// is alpha in the range [0..1]
  double num_alpha = by * cx - bx * cy;

  if(den > 0.0)
  {
// is alpha before the range [0..1] or after it?
    if((num_alpha < 0.0) || (num_alpha > den))
      return false;
  }
  else // den < 0
  {
// is alpha before the range [0..1] or after it?
    if((num_alpha > 0.0) || (num_alpha < den))
      return false;
  }

// is beta in the range [0..1]
  double num_beta = ax * cy - ay * cx;
  
  if(den > 0.0)
  {
// is beta before the range [0..1] or after it?
    if((num_beta < 0.0) || (num_beta > den))
      return false;
  }
  else // den < 0
  {
// is beta before the range [0..1] or after it?
    if((num_beta > 0.0) || (num_beta < den))
      return false;
  }

  return true;
}

gde::geom::algorithm::segment_relation_type
gde::geom::algorithm::compute_intesection_v1(const gde::geom::core::line_segment& s1,
                                             const gde::geom::core::line_segment& s2,
                                             gde::geom::core::point& first,
                                             gde::geom::core::point& second)
{
  double a1 = s1.p2.y - s1.p1.y;
  double b1 = s1.p1.x - s1.p2.x;
  double c1 = (s1.p2.x * s1.p1.y) - (s1.p1.x * s1.p2.y);

  double r3 = a1 * s2.p1.x + b1 * s2.p1.y + c1;
  double r4 = a1 * s2.p2.x + b1 * s2.p2.y + c1;

// if both points from segment s2 are to the sime side of line defined by segment s1,
// we are sure s2 can not intersects s1
  if((r3 != 0.0) && (r4 != 0.0) && same_signs(r3, r4))
    return DISJOINT;

// compute general line equation for segment s2
  double a2 = s2.p2.y - s2.p1.y;
  double b2 = s2.p1.x - s2.p2.x;
  double c2 = (s2.p2.x * s2.p1.y) - (s2.p1.x * s2.p2.y);

  double r1 = a2 * s1.p1.x + b2 * s1.p1.y + c2;
  double r2 = a2 * s1.p2.x + b2 * s1.p2.y + c2;

// if both points from segment s1 are to the sime side of line defined by segment s2,
// we are sure s1 can not intersects s2
  if((r1 != 0.0) && (r2 != 0.0) && same_signs(r1, r2))
    return DISJOINT;

// setting the denominator
  double denom = a1 * b2 - a2 * c1;

  if(denom == 0.0)  // are they collinear?
  {
    if(do_collinear_segments_intersects(s1, s2) == false)
      return DISJOINT;
// and we know they intersects: let's order the segments and find out intersection(s)
    const gde::geom::core::point* pts[4];
    pts[0] = &s1.p1;
    pts[1] = &s1.p2;
    pts[2] = &s2.p1;
    pts[3] = &s2.p2;

    std::sort(pts, pts + 4, point_cmp);

// at least they will share one point
    first = *pts[1];

// and if segments touch in a single point they are equal
    if((pts[1]->x == pts[2]->x) && (pts[1]->y == pts[2]->y))
      return TOUCH;

// otherwise, the middle points are the intesections
    second = *pts[2];

    return OVERLAP;
  }

// ok: they are not collinear!
  double offset = denom < 0.0 ? - denom / 2.0 : denom / 2.0;

// setting the numerator
// compute intersection point
  double num_alpha = b1 * c2 - b2 * c1;
  first.x = (num_alpha < 0.0 ? num_alpha - offset : num_alpha + offset) / denom;

  double num_beta = a2 * c1 - a1 * c2;
  first.y = (num_beta < 0.0 ? num_beta - offset : num_beta + offset) / denom;

  return CROSS;
}

gde::geom::algorithm::segment_relation_type
gde::geom::algorithm::compute_intesection_v2(const gde::geom::core::line_segment& s1,
                                             const gde::geom::core::line_segment& s2,
                                             gde::geom::core::point& first,
                                             gde::geom::core::point& second)
{
  double a = (s2.p1.x - s1.p1.x) * (s1.p2.y - s1.p1.y) - (s2.p1.y - s1.p1.y) * (s1.p2.x - s1.p1.x);
  double b = (s2.p2.x - s1.p1.x) * (s1.p2.y - s1.p1.y) - (s2.p2.y - s1.p1.y) * (s1.p2.x - s1.p1.x);

// if the endpoints of the second segment lie on the opposite
  if((a != 0.0) && (b != 0.0) && same_signs(a, b))
    return DISJOINT;

  double c = (s1.p1.x - s2.p1.x) * (s2.p2.y - s2.p1.y) - (s1.p1.y - s2.p1.y) * (s2.p2.x - s2.p1.x);
  double d = (s1.p2.x - s2.p1.x) * (s2.p2.y - s2.p1.y) - (s1.p2.y - s2.p1.y) * (s2.p2.x - s2.p1.x);

// if the endpoints of the first segment lie on the opposite
  if((c != 0.0) && (d != 0.0) && same_signs(c, d))
    return DISJOINT;

  double det = a - b;

  if(det == 0.0)  // are the segments collinear?
  {
    if(do_collinear_segments_intersects(s1, s2) == false)
      return DISJOINT;

// and we know they intersects: let's order the segments and find out intersection(s)
    const gde::geom::core::point* pts[4];
    pts[0] = &s1.p1;
    pts[1] = &s1.p2;
    pts[2] = &s2.p1;
    pts[3] = &s2.p2;

    std::sort(pts, pts + 4, point_cmp);

// at least they will share one point
    first = *pts[1];

// and if segments touch in a single point they are equal
    if((pts[1]->x == pts[2]->x) && (pts[1]->y == pts[2]->y))
      return TOUCH;

// otherwise, the middle points are the intesections
    second = *pts[2];

    return OVERLAP;
  }

// ok: they are not collinear!

  double tdet = -c;

// the denominator of the parameter must be positive
  if(det < 0.0)
  {
    det = -det;
    tdet = -tdet;
  }

// compute intersection point
  double alpha = tdet / det;

  first.x = s1.p1.x + alpha * (s1.p2.x - s1.p1.x);
  first.y = s1.p1.y + alpha * (s1.p2.y - s1.p1.y);

  return CROSS;
}

gde::geom::algorithm::segment_relation_type
gde::geom::algorithm::compute_intesection_v3(const gde::geom::core::line_segment& s1,
                                             const gde::geom::core::line_segment& s2,
                                             gde::geom::core::point& first,
                                             gde::geom::core::point& second)
{
  double ax = s1.p2.x - s1.p1.x;
  double ay = s1.p2.y - s1.p1.y;

  double bx = s2.p1.x - s2.p2.x;
  double by = s2.p1.y - s2.p2.y;
  
  double den = ay * bx - ax * by;

  if(den == 0.0) // are they collinear?
  {
// yes!
    if(do_collinear_segments_intersects(s1, s2) == false)
      return DISJOINT;

// and we know they intersects: let's order the segments and find out intersection(s)
    const gde::geom::core::point* pts[4];
    pts[0] = &s1.p1;
    pts[1] = &s1.p2;
    pts[2] = &s2.p1;
    pts[3] = &s2.p2;

    std::sort(pts, pts + 4, point_cmp);

// at least they will share one point
    first = *pts[1];

// and if segments touch in a single point they are equal
    if((pts[1]->x == pts[2]->x) && (pts[1]->y == pts[2]->y))
      return TOUCH;

// otherwise, the middle points are the intesections
    second = *pts[2];

    return OVERLAP;
  }
  
// they are not collinear, let's see if they intersects
  double cx = s1.p1.x - s2.p1.x;
  double cy = s1.p1.y - s2.p1.y;

// is alpha in the range [0..1]
  double num_alpha = by * cx - bx * cy;

  if(den > 0.0)
  {
// is alpha before the range [0..1] or after it?
    if((num_alpha < 0.0) || (num_alpha > den))
      return DISJOINT;
  }
  else // den < 0
  {
// is alpha before the range [0..1] or after it?
    if((num_alpha > 0.0) || (num_alpha < den))
      return DISJOINT;
  }

// is beta in the range [0..1]
  double num_beta = ax * cy - ay * cx;

  if(den > 0.0)
  {
// is beta before the range [0..1] or after it?
    if((num_beta < 0.0) || (num_beta > den))
      return DISJOINT;
  }
  else // den < 0
  {
    // is beta before the range [0..1] or after it?
    if((num_beta > 0.0) || (num_beta < den))
      return DISJOINT;
  }
  
// compute intersection point
  double alpha = num_alpha / den;
  
  first.x = s1.p1.x + alpha * (s1.p2.x - s1.p1.x);
  first.y = s1.p1.y + alpha * (s1.p2.y - s1.p1.y);

  return CROSS;
}


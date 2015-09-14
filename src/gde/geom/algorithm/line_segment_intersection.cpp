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
  return false;
}

gde::geom::algorithm::segment_relation_type
gde::geom::algorithm::compute_intesection(const gde::geom::core::line_segment& s1,
                                          const gde::geom::core::line_segment& s2,
                                          gde::geom::core::point& first,
                                          gde::geom::core::point& second)
{
  return DISJOINT;
}


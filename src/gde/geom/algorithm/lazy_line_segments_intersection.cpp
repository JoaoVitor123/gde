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
  \file gde/geom/algorithm/lazy_line_segments_intersection.cpp

  \brief Given a set of segments compute the intersection points between each pair with O(n^2) algorithm.

  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

// GDE
#include "line_segments_intersection.hpp"
#include "line_segment_intersection.hpp"

std::vector<gde::geom::core::point>
gde::geom::algorithm::lazy_intersection(std::vector<gde::geom::core::line_segment>& segments)
{
  std::vector<gde::geom::core::point> result;

  return result;
}

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
  \file unittest/geom/algorithm/main.cpp

  \brief Perform unittest on geometric algorithms.

  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

// GDE
#include <gde/geom/algorithm/line_segment_intersection.hpp>
#include <gde/geom/algorithm/line_segments_intersection.hpp>
#include <gde/geom/core/geometric_primitives.hpp>

// STL
#include <iostream>

void print(const std::vector<gde::geom::core::point>& intersections)
{
  for(const gde::geom::core::point& ip : intersections)
  {
    std::cout << ip.x << ", " << ip.y << std::endl;
  }
}

void test1()
{
  gde::geom::core::line_segment s1 = { {0, 0}, {10, 10} };
  gde::geom::core::line_segment s2 = { {0, 10}, {10, 0} };
  
  std::cout << "s1 intersects s2? " << gde::geom::algorithm::do_intersects(s1, s2) << std::endl;
}

void test_lazy_intersection()
{
  std::vector<gde::geom::core::line_segment> segments = {
    { {0, 0}, {10, 10} },
    { {1, 0}, {10, 9} },
    { {2, 0}, {10, 8} },
    { {3, 0}, {10, 7} },
    { {4, 0}, {10, 6} }
  };
  
  std::vector<gde::geom::core::point> intersections = gde::geom::algorithm::lazy_intersection(segments);
  
  print(intersections);
}


int main(int argc, char* argv[])
{
  test1();
  
  test_lazy_intersection();

  return EXIT_SUCCESS;
}

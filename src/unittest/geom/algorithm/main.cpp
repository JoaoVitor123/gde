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
#include <gde/geom/core/geometric_primitives.hpp>
#include <gde/geom/algorithm/line_segment_intersection.hpp>
#include <gde/geom/algorithm/line_segments_intersection.hpp>
#include <gde/geom/algorithm/utils.hpp>

// STL
#include <cstdlib>
#include <iostream>

void print(const std::vector<gde::geom::core::line_segment>& segments)
{
  std::cout << std::endl;
  
  for(const gde::geom::core::line_segment& s : segments)
  {
    std::cout << "[(" << s.p1.x << ", " << s.p1.y
    << "), (" << s.p2.x << ", " << s.p2.y
    << ")]" << std::endl;
  }
}

void print(const std::vector<gde::geom::core::point>& pts)
{
  std::cout << std::endl;
  
  for(const gde::geom::core::point& p : pts)
  {
    std::cout << "(" << p.x << ", "
    << p.y << ")" << std::endl;
  }
}

void do_intersects_basic_test()
{
  gde::geom::core::line_segment s1({1, 4}, {4, 4});
  gde::geom::core::line_segment s2({1, 1}, {6, 5});
  gde::geom::core::line_segment s3({5, 3}, {8, 2});
  
  gde::geom::core::line_segment s4({1, 1}, {4, 4});
  gde::geom::core::line_segment s5({2, 2}, {6, 6});
  gde::geom::core::line_segment s6({6, 6}, {8, 9});
  
  gde::geom::core::line_segment s7({4, 3}, {8, 6});
  gde::geom::core::line_segment s8({7, 2}, {1, 6});
  
  
  bool result = gde::geom::algorithm::do_intersects_v1(s1, s2);
  result = gde::geom::algorithm::do_intersects_v1(s2, s1);
  
  result = gde::geom::algorithm::do_intersects_v1(s1, s3);
  result = gde::geom::algorithm::do_intersects_v1(s3, s1);
  
  result = gde::geom::algorithm::do_intersects_v1(s2, s3);
  result = gde::geom::algorithm::do_intersects_v1(s3, s2);
  
  result = gde::geom::algorithm::do_intersects_v2(s1, s2);
  result = gde::geom::algorithm::do_intersects_v2(s2, s1);
  
  result = gde::geom::algorithm::do_intersects_v2(s1, s3);
  result = gde::geom::algorithm::do_intersects_v2(s3, s1);
  
  result = gde::geom::algorithm::do_intersects_v2(s2, s3);
  result = gde::geom::algorithm::do_intersects_v2(s3, s2);
  
  result = gde::geom::algorithm::do_intersects_v3(s1, s2);
  result = gde::geom::algorithm::do_intersects_v3(s2, s1);
  
  result = gde::geom::algorithm::do_intersects_v3(s1, s3);
  result = gde::geom::algorithm::do_intersects_v3(s3, s1);
  
  result = gde::geom::algorithm::do_intersects_v3(s2, s3);
  result = gde::geom::algorithm::do_intersects_v3(s3, s2);
  
  result = gde::geom::algorithm::do_intersects_v3(s4, s5);
  std::cout << result << std::endl;
  result = gde::geom::algorithm::do_intersects_v3(s5, s4);
  std::cout << result << std::endl;
  
  result = gde::geom::algorithm::do_intersects_v3(s6, s5);
  std::cout << result << std::endl;
  result = gde::geom::algorithm::do_intersects_v3(s5, s6);
  std::cout << result << std::endl;
  
  result = gde::geom::algorithm::do_intersects_v3(s7, s8);
  std::cout << result << std::endl;
  result = gde::geom::algorithm::do_intersects_v3(s8, s7);
  std::cout << result << std::endl;
  
  return;
}

int main(int argc, char* argv[])
{
  do_intersects_basic_test();

  return EXIT_SUCCESS;
}

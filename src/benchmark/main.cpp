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
  \file benchmark/main.cpp

  \brief Performance tests with geometric algorithms.

  \author Joao Vitor Chagas
 */

// GDE - Benchmark
#include "gen_random_data.hpp"

// GDE
#include <gde/geom/algorithm/line_segment_intersection.hpp>
#include <gde/geom/algorithm/line_segments_intersection.hpp>
#include <gde/geom/algorithm/utils.hpp>

// STL
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

void test1()
{
  gde::geom::core::line_segment s1({1, 4}, {4, 4});
  gde::geom::core::line_segment s2({1, 1}, {6, 5});
  gde::geom::core::line_segment s3({5, 3}, {8, 2});
  
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
  
  return;
}

void test2()
{
  std::vector<gde::geom::core::line_segment> segments = gen_segments(8000,
                                                                     std::make_pair(-180.0, 180.0),
                                                                     std::make_pair(-90.0, 90.0),
                                                                     20.0, 40.0);
 //print(segments);
  
  std::vector<gde::geom::core::point> ips1 = gde::geom::algorithm::x_order_intersection(segments);
  
  std::sort(ips1.begin(), ips1.end(), gde::geom::algorithm::point_xy_cmp());
  //print(ips1);
  
  std::vector<gde::geom::core::point> ips2 = gde::geom::algorithm::lazy_intersection(segments);
  
  std::sort(ips2.begin(), ips2.end(), gde::geom::algorithm::point_xy_cmp());
  //print(ips2);
  
  std::cout << "ips1 == ips2 ? " << (ips1.size() == ips2.size()) << std::endl;
  std::cout << "ips1 = "<< ips1.size() << "  ips2 = " << ips2.size() << std::endl;
}

int main(int argc, char* argv[])
{
  test1();
  
  return EXIT_SUCCESS;
}

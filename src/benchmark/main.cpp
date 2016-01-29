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
#include <gde/geom/core/geometric_primitives.hpp>
#include <gde/geom/algorithm/line_segment_intersection.hpp>
#include <gde/geom/algorithm/line_segments_intersection.hpp>
#include <gde/geom/algorithm/utils.hpp>

// STL
#include <iostream>
#include <iomanip>
#include <time.h>
#include <map>

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

double closest_number(double n,double N)
{

  return (N+n)/2;
}

void tili()
{
  std::vector<gde::geom::core::line_segment> segments = gen_segments(50,
                                                                     std::make_pair(-180.0, 180.0),
                                                                     std::make_pair(-90.0, 90.0),
                                                                     20.0, 40.0);//*/
  double range_x = 0, range_y = 0;
  int cont_x = 0, cont_y = 0;

  std::vector<gde::geom::core::line_segment> matrix[(360/40)+1][(180/40)+1];
  //std::cout << (360/40)+1 << "   " << (180/40)+1 << std::endl;
  for(int i = 0; i < (segments.size() - 1); ++i)
  {
    range_x = closest_number(segments[i].p1.x,segments[i].p2.x);
    range_y = closest_number(segments[i].p1.y,segments[i].p2.y);
   // std::cout << "rx:  " << range_x <<"  ry  " << range_y << "\n";
    for(int j = -140; j <= 220; j += 80) // 180 + 40
    {
      if (range_x < j)
      {
        for(int w = -50; w <= 130; w += 80) // 90 + 40
        {
          if(range_y < w)
          {
            matrix[cont_x][cont_y].push_back(segments[i]);//*
            cont_y = 0;
            if(range_x > ((j+j) - 20) && j < 200)
            {
              matrix[cont_x+1][cont_y].push_back(segments[i]);
            }
            if(range_y > ((w+w) - 20) && w < 150)
            {
              matrix[cont_x][cont_y+1].push_back(segments[i]);
            }
            if(range_x < (j + 20) && j > 80 && cont_x > 0)
            {
              matrix[cont_x-1][cont_y].push_back(segments[i]);
            }
            if(range_y < ( w + 20) && w > 80  && cont_y > 0)
            {
              matrix[cont_x][cont_y-1].push_back(segments[i]);
            }
            if(range_x > ((j+j) - 20) && j < 200 && range_y > ((w+w) - 20) && w < 150)
            {
              matrix[cont_x+1][cont_y +1].push_back(segments[i]);
            }
            if(range_y > ((w+w) - 20) && w < 150 && range_x < (j + 20) && j > 80 && cont_x > 0)
            {
              matrix[cont_x-1][cont_y+1].push_back(segments[i]);
            }
            if(range_x < (j + 20) && j > 80 && cont_x > 0 && range_y < ( w + 20) && w > 80  && cont_y > 0)
            {
              matrix[cont_x-1][cont_y -1].push_back(segments[i]);
            }
            if(range_x < (j + 20) && j > 80 && cont_x > 0 && range_y > ((w+w) - 20) && w < 150)
            {
              matrix[cont_x-1][cont_y+1].push_back(segments[i]);
            }
            break;
          }
          else
          {
            ++cont_y;
            continue;
          }
        }
          cont_x = 0;
          break;
      }
      else
      {
        ++cont_x;
        continue;
      }
    }
  }

  for(int j = 0; j < 10; ++j)
  {
    for(int w = 0; w < 5; ++w)
    {
      std::vector<gde::geom::core::line_segment> seg = matrix[j][w];
      if(seg.size() > 1)
      {
        std::vector<gde::geom::core::point> ips1 = gde::geom::algorithm::x_order_intersection(seg);
        print(ips1);
      }
    }
  }
}


void test2()
{
  std::vector<gde::geom::core::line_segment> segments = gen_segments(60,
                                                                     std::make_pair(-180.0, 180.0),
                                                                     std::make_pair(-90.0, 90.0),
                                                                     20.0, 40.0);
 //print(segments);

  std::vector<gde::geom::core::point> ips1 = gde::geom::algorithm::x_order_intersection(segments);

  std::sort(ips1.begin(), ips1.end(), gde::geom::algorithm::point_xy_cmp());
  print(ips1);

  std::vector<gde::geom::core::point> ips2 = gde::geom::algorithm::lazy_intersection(segments);

  std::sort(ips2.begin(), ips2.end(), gde::geom::algorithm::point_xy_cmp());
  std::cout <<"lazy";
  print(ips2);

  std::cout << "ips1 == ips2 ? " << (ips1 == ips2) << std::endl;
  std::cout << "ips1 = "<< ips1.size() << "  ips2 = " << ips2.size() << std::endl;

  typedef std::vector<gde::geom::core::point>::iterator intersection_point_it;

  std::pair<intersection_point_it, intersection_point_it> diffs = std::mismatch(ips1.begin(), ips1.end(), ips2.begin());

  std::cout << std::setprecision(18) << "v1 = " << diffs.first->x << "\tv2 = " << diffs.second->x << std::endl;
  std::cout << std::setprecision(18) << "v1 = " << diffs.first->y << "\tv2 = " << diffs.second->y << std::endl;
}

void test3()
{
  std::vector<gde::geom::core::line_segment> segments = gen_segments(1000,
                                                                     std::make_pair(-180.0, 180.0),
                                                                     std::make_pair(-90.0, 90.0),
                                                                     20.0, 40.0);

  gde::geom::core::point p1, p2;

  clock_t Ticks[2];
  Ticks[0] = clock();
  for(int i = 0; i < segments.size(); ++i )
  {
    for(int j = 0; j < segments.size(); ++j )
      gde::geom::algorithm::compute_intesection_v3(segments[i], segments[j],p1, p2);
  }
  Ticks[1] = clock();
  double Tempo = (Ticks[1] - Ticks[0]) * 1.0 / CLOCKS_PER_SEC;
  std::cout << "\n" << Tempo << "   intersects_v3" << "\n";


  //clock_t Ticks[2];
  Ticks[0] = clock();
  for(int i = 0; i < segments.size(); ++i )
  {
    for(int j = 0; j < segments.size(); ++j )
      gde::geom::algorithm::compute_intesection_v2(segments[i], segments[j],p1, p2);
  }
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1.0 / CLOCKS_PER_SEC;
  std::cout << "\n" << Tempo << "   intersects_v2" << "\n";


  //clock_t Ticks[2];
  Ticks[0] = clock();
  for(int i = 0; i < segments.size(); ++i )
  {
    for(int j = 0; j < segments.size(); ++j )
      gde::geom::algorithm::compute_intesection_v1(segments[i], segments[j],p1, p2);
  }
  Ticks[1] = clock();
  Tempo = (Ticks[1] - Ticks[0]) * 1.0 / CLOCKS_PER_SEC;
  std::cout << "\n" << Tempo << "   intersects_v1" << "\n";

}


int main(int argc, char* argv[])
{
  //test1();
 //test2();
  test3();
 // tili();

  return EXIT_SUCCESS;
}

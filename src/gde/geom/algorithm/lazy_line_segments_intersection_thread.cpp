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

// STL
#include <algorithm>
#include <thread>


std::size_t
lazy_threadg(const std::vector<gde::geom::core::line_segment>& segments, int nt)
{
  std::vector<gde::geom::core::point> result;
  gde::geom::core::point ip1;
  gde::geom::core::point ip2;

  for(int i = 0; i < nt; ++i)
  {
    if(i  >= segments.size())
      break;

    const gde::geom::core::line_segment& red = segments[i];

    for(int j = i + 1; j < nt; ++j)
    {
      if(j  >= segments.size())
        break;

      const gde::geom::core::line_segment& blue = segments[j];

      if(!gde::geom::algorithm::do_bounding_box_intersects(red, blue))
        continue;

      gde::geom::algorithm::segment_relation_type spatial_relation = gde::geom::algorithm::compute_intesection_v3(red, blue, ip1, ip2);

      if(spatial_relation == gde::geom::algorithm::DISJOINT)
        continue;

      result.push_back(ip1);

      if(spatial_relation == gde::geom::algorithm::OVERLAP)
        result.push_back(ip2);
    }
  }

  return result.size();
}

struct parameter_lz
{
    std::size_t result = 0;
};

void  task_lz(std::vector<gde::geom::core::line_segment> segments_lz, int nt, struct parameter_lz *pat_lz)
{
  pat_lz->result += lazy_threadg(segments_lz, nt);
}

std::size_t
gde::geom::algorithm::lazy_intersection_thread(const std::vector<gde::geom::core::line_segment>& segments)
{
  parameter_lz pat_lz;

 // declaring thread vector
  std::vector<std::thread> vecThread;

// check how many concurrency threads the hardware supports
  unsigned int concurrency_threads = std::thread::hardware_concurrency();

  int nt = (segments.size() / (concurrency_threads - 2))  + 1;

  for(int i = 0; i <= nt; i++)
  {
// thread adds to the vector
   // vecThread.push_back(std::thread(&task_lz, segments,nt, &pat_lz));

// if the hardware can handle the amount of threds
    if((concurrency_threads-2) == (vecThread.size()))
    {

// running thread vector
    //  for (auto& th : vecThread)
     // {
        //th.join();
    // th.detach();
     // }

// clear the threads vector
      vecThread.clear();
    }
    nt += nt;
  }
  return  pat_lz.result;
}

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
  \file gde/geom/algorithm/tiling_intersection_thread.cpp

  \brief tiling intersection algorithm.

  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

// GDE
#include "line_segments_intersection.hpp"
#include "line_segment_intersection.hpp"
#include "utils.hpp"

// STL
#include <algorithm>
#include <thread>

//struct parameter
//{
//    std::size_t size = 0;
//};
//
//void  task(std::vector<gde::geom::core::line_segment> elemento, double block, double block_size,
//            std::vector<gde::geom::core::point> ipts, struct parameter *pat)
//{
//    ipts = gde::geom::algorithm::x_order_intersection(elemento, block,(block-block_size));
//    pat->size += ipts.size();
//}
//
//std::size_t
//gde::geom::algorithm::tiling_intersection_thread(const std::vector<gde::geom::core::line_segment>& segments,
//                           const double& max_length, const double& max_range, const double& min_range)
//{
//
//  // defines scope of the blocks
//  int range = (gde::geom::algorithm::return_positive_value(max_range) / max_length) + 2;
//
//  std::vector<gde::geom::core::point> ipts;
//  std::vector<gde::geom::core::line_segment> segments_range[4];
//  double t_max;
//  double block;
//
//  t_max = max_range + gde::geom::algorithm::return_positive_value(min_range);
//
//// size of the blocks
//  double block_size = t_max/range;
//
//// current block
//  block = min_range + block_size;
//
//// through all segments
//  for(int i = 0;i < segments.size(); ++i)
//  {
//    int cont = 0;
//// through every division blocks in Y
//    for(int y = block; y <= t_max; y += block_size)
//    {
//
//// checks whether the segment y value is within block
//      if(segments[i].p1.y < y || segments[i].p2.y < y)
//      {
//
//// adds the segment in its corresponding block
//        segments_range[cont].push_back(segments[i]);
//
//// checks if one of the points of this segment this the top of this block
//        if((segments[i].p1.y > y || segments[i].p2.y > y) &&
//           y < t_max)
//          segments_range[cont+1].push_back(segments[i]);
//        break;
//      }
//      cont++;
//    }
//  }
//// x-ordering
//  parameter pat;
//
//// declaring thread vector
//  std::vector<std::thread> vecThread;
//
//// check how many concurrency threads the hardware supports
//  unsigned int concurrency_threads = std::thread::hardware_concurrency();
//
//// traversing segment list
//  for(auto& elemento: segments_range)
//  {
//
//// thread adds to the vector
//      vecThread.push_back(std::thread(&task,elemento,block,block_size,ipts,&pat));
//
//// if the hardware can handle the amount of threds
//      if((concurrency_threads-2) == (vecThread.size()))
//      {
//
//// running thread vector
//        for (auto& th : vecThread)
//        {
//          th.join();
//         // th.detach();
//        }
//
//// clear the threads vector
//      vecThread.clear();
//      }
//    block += block_size;
//  }
//
//  return pat.size;
//}

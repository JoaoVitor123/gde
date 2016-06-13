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
  \file gde/geom/algorithm/x_order_intersection.cpp

  \brief X-Order intersection algorithm.

  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

// GDE
#include "line_segments_intersection.hpp"
#include "line_segment_intersection.hpp"
#include "utils.hpp"


// STL
#include <algorithm>
#include <iostream>
#include<thread>

//struct parameter_x
//{
//  std::size_t size = 0;
//};
//
//std::vector<gde::geom::core::point> ex(std::vector<gde::geom::core::line_segment> ordered_segments, const double nt,const double aux)
//{
//    std::vector<gde::geom::core::point> ipts;
//    // retain intersection points between tests
//
//      gde::geom::core::point ip1, ip2;
//
//    // first scan ordered_segments from the first segment
//      for(double i = aux - 1; i < nt; ++i)
//      {
//        if(i >= ordered_segments.size())
//          break;
//    // scan segments from i + 1
//    for (double j = i + 1; j < ordered_segments.size(); j++)
//    {
//      if(j >= ordered_segments.size())
//          break;
//// if beginning x-coordinate of the second is greater than the last
//// x-coordinate of the first segment: stop => no more segments can intersects.
//     if(ordered_segments[i].p2.x < ordered_segments[j].p1.x)
//       break;
//
//// if segments y-interval don't intersect they will not have intersection,
//// let's test the next segment!
//     if(!gde::geom::algorithm::do_y_interval_intersects(ordered_segments[i], ordered_segments[j]))
//        continue;
//
//// check for intersection
//    gde::geom::algorithm::segment_relation_type result = gde::geom::algorithm::compute_intesection_v3(ordered_segments[i], ordered_segments[j], ip1, ip2);
//
//    if(result == gde::geom::algorithm::DISJOINT)
//      continue;
//
//      ipts.push_back(ip1);
//
//    if(result == gde::geom::algorithm::OVERLAP)
//      ipts.push_back(ip2);
//    }
//  }
//  return ipts;
//}
//
//void  task_x(const std::vector<gde::geom::core::line_segment> ordered_segments,const double nt,const double aux2, struct parameter_x *par_x)
//{
//
//    std::vector<gde::geom::core::point> aux = ex(ordered_segments,nt,aux2);
//    par_x->size += aux.size();
//}
//
//std::size_t
//gde::geom::algorithm::x_order_intersection_thread(const std::vector<gde::geom::core::line_segment>& segments)
//{
//// create a new segment vector with the same size as input segments
//  std::vector<gde::geom::core::line_segment> ordered_segments(segments.size());
//
//// copy the input segments and order each one them from left-right
//  std::transform(segments.begin(), segments.end(), ordered_segments.begin(), sort_segment_xy());
//
//// sort all the segments from left to right
//  std::sort(ordered_segments.begin(), ordered_segments.end(), line_segment_xy_cmp());
//
//  parameter_x par_x;
//
//  // declaring thread vector
//   std::vector<std::thread> vecThread;
//
// // check how many concurrency threads the hardware supports
//   unsigned int concurrency_threads = std::thread::hardware_concurrency();
//
//   double nt = (segments.size() / (concurrency_threads));
//   double aux = 1;
//  // task_x(ordered_segments, nt, &par_x);
//
//   for(int i = 0; i <= (segments.size()/nt); i++)
//   {
//     std::thread t (task_x,ordered_segments, nt, aux, &par_x);
//     t.join();
// // thread adds to the vector
//    // vecThread.push_back(std::thread(&task_x,ordered_segments,nt,&par_x));
//
// // if the hardware can handle the amount of threds
//     if((concurrency_threads-2) == (vecThread.size()))
//     {
//
// // running thread vector
//      // for (auto& th : vecThread)
//       //{
//        // th.join();
//     // th.detach();
//     // }
//
// // clear the threads vector
//       vecThread.clear();
//     }
//     aux = nt +1;
//     nt += nt;
//
//   }
//  return par_x.size;
//}

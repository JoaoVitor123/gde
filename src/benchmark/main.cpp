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
#include "prepare_real_data.hpp"

// GDE
#include <gde/geom/core/geometric_primitives.hpp>
#include <gde/geom/algorithm/line_segment_intersection.hpp>
#include <gde/geom/algorithm/line_segments_intersection.hpp>
#include <gde/geom/algorithm/utils.hpp>

// STL
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>

//struct benchmark_t
//{
//  std::string algorithm_name;                   // algorithm name
//  std::size_t num_segments;                     // number of segments
//  std::size_t num_intersections;                // number of intersections
//  std::chrono::duration<double> elapsed_time;  // miliseconds
//};
//
//void print(const std::vector<benchmark_t>& results)
//{
//  for(const benchmark_t& result : results)
//  {
//    std::cout << std::setprecision(18)
//              << result.algorithm_name << ";" << result.num_segments << ";"
//              << result.num_intersections << ";" << result.elapsed_time.count() / 5.0 << std::endl;
//  }
//}
//
//
//std::vector<gde::geom::core::point>
//lazy_intersection_v1(const std::vector<gde::geom::core::line_segment>& segments)
//{
//  std::vector<gde::geom::core::point> result;
//  gde::geom::core::point ip1;
//  gde::geom::core::point ip2;
//  
//  const std::size_t number_of_segments = segments.size();
//  
//  for(std::size_t i = 0; i < (number_of_segments - 1); ++i)
//  {
//    const gde::geom::core::line_segment& red = segments[i];
//    
//    for(std::size_t j = i + 1; j < number_of_segments; ++j)
//    {
//      const gde::geom::core::line_segment& blue = segments[j];
//      
//      if(!gde::geom::algorithm::do_bounding_box_intersects(red, blue))
//        continue;
//      
//      gde::geom::algorithm::segment_relation_type spatial_relation = gde::geom::algorithm::compute_intesection_v1(red, blue, ip1, ip2);
//      
//      if(spatial_relation == gde::geom::algorithm::DISJOINT)
//        continue;
//      
//      result.push_back(ip1);
//      
//      if(spatial_relation == gde::geom::algorithm::OVERLAP)
//        result.push_back(ip2);
//    }
//  }
//  
//  return result;
//}
//
//std::vector<gde::geom::core::point>
//lazy_intersection_v2(const std::vector<gde::geom::core::line_segment>& segments)
//{
//  std::vector<gde::geom::core::point> result;
//  gde::geom::core::point ip1;
//  gde::geom::core::point ip2;
//  
//  const std::size_t number_of_segments = segments.size();
//  
//  for(std::size_t i = 0; i < (number_of_segments - 1); ++i)
//  {
//    const gde::geom::core::line_segment& red = segments[i];
//    
//    for(std::size_t j = i + 1; j < number_of_segments; ++j)
//    {
//      const gde::geom::core::line_segment& blue = segments[j];
//      
//      if(!gde::geom::algorithm::do_bounding_box_intersects(red, blue))
//        continue;
//      
//      gde::geom::algorithm::segment_relation_type spatial_relation = gde::geom::algorithm::compute_intesection_v2(red, blue, ip1, ip2);
//      
//      if(spatial_relation == gde::geom::algorithm::DISJOINT)
//        continue;
//      
//      result.push_back(ip1);
//      
//      if(spatial_relation == gde::geom::algorithm::OVERLAP)
//        result.push_back(ip2);
//    }
//  }
//  
//  return result;
//}
//
//std::vector<gde::geom::core::point>
//lazy_intersection_v3(const std::vector<gde::geom::core::line_segment>& segments)
//{
//  std::vector<gde::geom::core::point> result;
//  gde::geom::core::point ip1;
//  gde::geom::core::point ip2;
//  
//  const std::size_t number_of_segments = segments.size();
//  
//  for(std::size_t i = 0; i < (number_of_segments - 1); ++i)
//  {
//    const gde::geom::core::line_segment& red = segments[i];
//    
//    for(std::size_t j = i + 1; j < number_of_segments; ++j)
//    {
//      const gde::geom::core::line_segment& blue = segments[j];
//      
//      if(!gde::geom::algorithm::do_bounding_box_intersects(red, blue))
//        continue;
//      
//      gde::geom::algorithm::segment_relation_type spatial_relation = gde::geom::algorithm::compute_intesection_v3(red, blue, ip1, ip2);
//      
//      if(spatial_relation == gde::geom::algorithm::DISJOINT)
//        continue;
//      
//      result.push_back(ip1);
//      
//      if(spatial_relation == gde::geom::algorithm::OVERLAP)
//        result.push_back(ip2);
//    }
//  }
//  
//  return result;
//}
//
//void do_tests()
//{
//  std::vector<benchmark_t> results;
//
//  for(std::size_t num_segments = 2; num_segments <= 32768; num_segments *= 2)
//  {
//    double min_length = 180.0;
//    double max_length = 360.0;
//    
//    std::vector<gde::geom::core::line_segment> segments = gen_segments(num_segments,
//                                                                       std::make_pair(-180.0, 180.0),
//                                                                       std::make_pair(-90.0, 90.0),
//                                                                       min_length, max_length);
//    
//    {
//      benchmark_t result;
//      result.algorithm_name = "v1";
//      result.num_segments = num_segments;
//      
//      std::chrono::time_point<std::chrono::system_clock> start, end;
//      
//      start = std::chrono::system_clock::now();
//      
//      std::size_t nips = 0;
//      
//      for(std::size_t i = 0; i < 5; ++i)
//      {
//        std::vector<gde::geom::core::point> ips = lazy_intersection_v1(segments);
//        nips = ips.size();
//      }
//      
//      end = std::chrono::system_clock::now();
//      
//      result.num_intersections = nips;
//      result.elapsed_time = end - start;
//
//      results.push_back(result);
//    }
//    
//    {
//      benchmark_t result;
//      result.algorithm_name = "v2";
//      result.num_segments = num_segments;
//      
//      std::chrono::time_point<std::chrono::system_clock> start, end;
//      
//      start = std::chrono::system_clock::now();
//
//      std::size_t nips = 0;
//
//      for(std::size_t i = 0; i < 5; ++i)
//      {
//        std::vector<gde::geom::core::point> ips = lazy_intersection_v2(segments);
//        nips = ips.size();
//      }
//
//      end = std::chrono::system_clock::now();
//      
//      result.elapsed_time = end - start;      
//      result.num_intersections = nips;
//      
//      results.push_back(result);
//    }
//    
//    {
//      benchmark_t result;
//      result.algorithm_name = "v3";
//      result.num_segments = num_segments;
//      
//      std::chrono::time_point<std::chrono::system_clock> start, end;
//      
//      start = std::chrono::system_clock::now();
//
//      std::size_t nips = 0;
//
//      for(std::size_t i = 0; i < 5; ++i)
//      {
//        std::vector<gde::geom::core::point> ips = lazy_intersection_v3(segments);
//        nips = ips.size();
//      }
//      end = std::chrono::system_clock::now();
//      
//      result.elapsed_time = end - start;
//      result.num_intersections = nips;
//      
//      results.push_back(result);
//      
//    }
//  }
//  
//  print(results);
//}
//
//std::size_t
//tiling_intersection_sequential(const std::vector<gde::geom::core::line_segment>& segments,
//                                          const double& max_length, const double& max_range, const double& min_range)
//{
//
//  // defines scope of the blocks
//  const int range = (gde::geom::algorithm::return_positive_value(max_range) / max_length);
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
//// ferifica if the segment is more than two blocks
////        if(segments[i].p1.y > y + block_size || segments[i].p2.y > y + block_size &&
////           y < t_max)
////            continue;
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
//std::size_t size = 0;
//  for(auto& elemento: segments_range)
//  {
//    ipts = gde::geom::algorithm::x_order_intersection(elemento, block,(block-block_size));
//    block += block_size;
//    size += ipts.size();
//  }
//
//  return size;
//}
//
//void do_tests2()
//{
//  double min_length = 30.0;
//  double max_length = 45.0;
//  double min_y = -180.0;
//  double max_y = 180.0;
//
//  std::vector<benchmark_t> results;
//
//  for(std::size_t num_segments = 16384; num_segments <= 32768; num_segments *= 2) // 16384 = 2
//  {
//      std::vector<gde::geom::core::line_segment> segments = gen_segments(num_segments,
//                                                                         std::make_pair(-180.0, 180.0),
//                                                                         std::make_pair(min_y, max_y),
//                                                                         min_length, max_length);
//
//      benchmark_t result;
//      std::size_t nips = 0;
//
//      result.algorithm_name = "tiling ";
//      result.num_segments = num_segments;
//
//      std::chrono::time_point<std::chrono::system_clock> start, end;
//      start = std::chrono::system_clock::now();
//      for(std::size_t i = 0; i < 5; ++i)
//      {
//      nips = tiling_intersection_sequential(segments, max_length, max_y, min_y);
//      }
//      end = std::chrono::system_clock::now();
//
//
//      result.num_intersections = nips;
//      result.elapsed_time = end - start;
//      results.push_back(result);
//
//
//      benchmark_t result2;
//      result2.algorithm_name = "X-order ";
//      result2.num_segments = num_segments;
//
//      std::chrono::time_point<std::chrono::system_clock> start2, end2;
//      start2 = std::chrono::system_clock::now();
//
//      std::vector<gde::geom::core::point> segments2;
//
//      for(std::size_t i = 0; i < 5; ++i)
//      {
//        segments2 = gde::geom::algorithm::x_order_intersection(segments);
//      }
//      end2 = std::chrono::system_clock::now();
//
//      nips = segments2.size();
//      result2.num_intersections = nips;
//      result2.elapsed_time = end2 - start2;
//      results.push_back(result2);
//
//      benchmark_t result3;
//      result3.algorithm_name = "lazy ";
//      result3.num_segments = num_segments;
//
//      std::chrono::time_point<std::chrono::system_clock> start3, end3;
//      start3 = std::chrono::system_clock::now();
//
//      std::vector<gde::geom::core::point> segments3;
//
//      for(std::size_t i = 0; i < 5; ++i)
//      {
//        segments3 = gde::geom::algorithm::lazy_intersection(segments);
//      }
//      end3 = std::chrono::system_clock::now();
//
//      nips = segments3.size();
//      result3.num_intersections = nips;
//      result3.elapsed_time = end3 - start3;
//      results.push_back(result3);
//
//  }
//
//   print(results);
//
//}
//
//
//void do_tests3()
//{
//  double min_length = 30.0;
//  double max_length = 45.0;
//  double min_y = -180.0;
//  double max_y = 180.0;
//
//  std::vector<benchmark_t> results;
//
//  for(std::size_t num_segments = 16384; num_segments <= 32768; num_segments *= 2) // num_segments = 2
//  {
//      std::vector<gde::geom::core::line_segment> segments = gen_segments(num_segments,
//                                                                         std::make_pair(-180.0, 180.0),
//                                                                         std::make_pair(min_y, max_y),
//                                                                         min_length, max_length);
//
//      benchmark_t result;
//      std::size_t nips = 0;
//
//      result.algorithm_name = "tiling_threads ";
//      result.num_segments = num_segments;
//
//      std::chrono::time_point<std::chrono::system_clock> start, end;
//      start = std::chrono::system_clock::now();
//      for(std::size_t i = 0; i < 5; ++i)
//      {
//        nips = gde::geom::algorithm::tiling_intersection_thread(segments, max_length, max_y, min_y);
//      }
//      end = std::chrono::system_clock::now();
//
//      result.num_intersections = nips;
//      result.elapsed_time = end - start;
//      results.push_back(result);
//
//
//      benchmark_t result2;
//      result2.algorithm_name = "tiling_sequential ";
//      result2.num_segments = num_segments;
//
//      std::chrono::time_point<std::chrono::system_clock> start2, end2;
//      start2 = std::chrono::system_clock::now();
//
//      std::vector<gde::geom::core::point> tili_point;
//
//      for(std::size_t i = 0; i < 5; ++i)
//      {
//         tili_point = gde::geom::algorithm::tiling_intersection(segments, max_length, max_y, min_y);
//      }
//      end = std::chrono::system_clock::now();
//
//      nips = tili_point.size();
//
//      result2.num_intersections = nips;
//      result2.elapsed_time = end2 - start2;
//      results.push_back(result2);
///*
//      benchmark_t result3;
//      result3.algorithm_name = "X-order";
//      result3.num_segments = num_segments;
//
//      std::chrono::time_point<std::chrono::system_clock> start3, end3;
//      start3 = std::chrono::system_clock::now();
//
//      std::vector<gde::geom::core::point> segments2;
//
//      for(std::size_t i = 0; i < 5; ++i)
//      {
//       // segments2 = gde::geom::algorithm::x_order_intersection(segments,0);
//      }
//      end3 = std::chrono::system_clock::now();
//
//      nips = segments2.size();
//      result3.num_intersections = nips;
//      result3.elapsed_time = end3 - start3;
//      results.push_back(result3);
//
//      benchmark_t result3;
//      result3.algorithm_name = "lazy ";
//      result3.num_segments = num_segments;
//
//      std::chrono::time_point<std::chrono::system_clock> start3, end3;
//      start3 = std::chrono::system_clock::now();
//
//
//      for(std::size_t i = 0; i < 5; ++i)
//      {
//        nips = lazy_thread(segments);
//      }
//      end3 = std::chrono::system_clock::now();
//
//      result3.num_intersections = nips;
//      result3.elapsed_time = end3 - start3;
//      results.push_back(result3);*/
//  }
//
//   print(results);
//
//}

void
test_lazy_intersection_rb_thread(const std::vector<gde::geom::core::line_segment>& red_segments,
                                 const std::vector<gde::geom::core::line_segment>& blue_segments)
{
  std::size_t num_threads = std::thread::hardware_concurrency();

  std::vector<std::vector<gde::geom::core::point> > intersetion_pts;
  
  gde::geom::algorithm::lazy_intersection_rb_thread(red_segments, blue_segments, num_threads, intersetion_pts);
  
  std::vector<gde::geom::core::point> ipts;
  
  for(const auto& vecipts : intersetion_pts)
  {
    std::copy(vecipts.begin(), vecipts.end(), std::back_inserter(ipts));
  }
  
  save_intersection_points(ipts, 0, 4674, "/Users/gribeiro/Desktop/Curso-TerraView/test_lazy_intersection_rb_thread.shp");
}

void
test_x_order_intersection_rb(const std::vector<gde::geom::core::line_segment>& red_segments,
                             const std::vector<gde::geom::core::line_segment>& blue_segments)
{
  std::vector<gde::geom::core::point> ipts = gde::geom::algorithm::x_order_intersection_rb(red_segments, blue_segments);

  save_intersection_points(ipts, 0, 4674, "/Users/gribeiro/Desktop/Curso-TerraView/test_x_order_intersection_rb.shp");
}

int main(int argc, char* argv[])
{
  StartTerraLib();
  
  std::vector<gde::geom::core::line_segment> trechos_drenagem = extract_segments_from_shp("/Users/gribeiro/Desktop/Curso-TerraView/ba_drenagem/HID_Trecho_Drenagem_L.shp");
  
  std::vector<gde::geom::core::line_segment> trechos_rodoviario = extract_segments_from_shp("/Users/gribeiro/Desktop/Curso-TerraView/trechos_rodovarios/TRA_Trecho_Rodoviario_L.shp");
  
  test_x_order_intersection_rb(trechos_drenagem, trechos_rodoviario);
                                                    
  StopTerraLib();

  return EXIT_SUCCESS;
}



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
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

struct benchmark_t
{
  std::string algorithm_name;                   // algorithm name
  std::size_t num_segments;                     // number of segments
  std::size_t num_intersections;                // number of intersections
  std::chrono::duration<double> elapsed_time;  // miliseconds
};

void print(const std::vector<benchmark_t>& results)
{
  for(const benchmark_t& result : results)
  {
    std::cout << std::setprecision(18)
              << result.algorithm_name << ";" << result.num_segments << ";"
              << result.num_intersections << ";" << result.elapsed_time.count() / 5.0 << std::endl;
  }
}


std::vector<gde::geom::core::point>
lazy_intersection_v1(const std::vector<gde::geom::core::line_segment>& segments)
{
  std::vector<gde::geom::core::point> result;
  gde::geom::core::point ip1;
  gde::geom::core::point ip2;
  
  const std::size_t number_of_segments = segments.size();
  
  for(std::size_t i = 0; i < (number_of_segments - 1); ++i)
  {
    const gde::geom::core::line_segment& red = segments[i];
    
    for(std::size_t j = i + 1; j < number_of_segments; ++j)
    {
      const gde::geom::core::line_segment& blue = segments[j];
      
      if(!gde::geom::algorithm::do_bounding_box_intersects(red, blue))
        continue;
      
      gde::geom::algorithm::segment_relation_type spatial_relation = gde::geom::algorithm::compute_intesection_v1(red, blue, ip1, ip2);
      
      if(spatial_relation == gde::geom::algorithm::DISJOINT)
        continue;
      
      result.push_back(ip1);
      
      if(spatial_relation == gde::geom::algorithm::OVERLAP)
        result.push_back(ip2);
    }
  }
  
  return std::move(result);
}

std::vector<gde::geom::core::point>
lazy_intersection_v2(const std::vector<gde::geom::core::line_segment>& segments)
{
  std::vector<gde::geom::core::point> result;
  gde::geom::core::point ip1;
  gde::geom::core::point ip2;
  
  const std::size_t number_of_segments = segments.size();
  
  for(std::size_t i = 0; i < (number_of_segments - 1); ++i)
  {
    const gde::geom::core::line_segment& red = segments[i];
    
    for(std::size_t j = i + 1; j < number_of_segments; ++j)
    {
      const gde::geom::core::line_segment& blue = segments[j];
      
      if(!gde::geom::algorithm::do_bounding_box_intersects(red, blue))
        continue;
      
      gde::geom::algorithm::segment_relation_type spatial_relation = gde::geom::algorithm::compute_intesection_v2(red, blue, ip1, ip2);
      
      if(spatial_relation == gde::geom::algorithm::DISJOINT)
        continue;
      
      result.push_back(ip1);
      
      if(spatial_relation == gde::geom::algorithm::OVERLAP)
        result.push_back(ip2);
    }
  }
  
  return std::move(result);
}

std::vector<gde::geom::core::point>
lazy_intersection_v3(const std::vector<gde::geom::core::line_segment>& segments)
{
  std::vector<gde::geom::core::point> result;
  gde::geom::core::point ip1;
  gde::geom::core::point ip2;
  
  const std::size_t number_of_segments = segments.size();
  
  for(std::size_t i = 0; i < (number_of_segments - 1); ++i)
  {
    const gde::geom::core::line_segment& red = segments[i];
    
    for(std::size_t j = i + 1; j < number_of_segments; ++j)
    {
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
  
  return std::move(result);
}

void do_tests()
{
  std::vector<benchmark_t> results;

  for(std::size_t num_segments = 2; num_segments <= 32768; num_segments *= 2)
  {
    double min_length = 180.0;
    double max_length = 360.0;
    
    std::vector<gde::geom::core::line_segment> segments = gen_segments(num_segments,
                                                                       std::make_pair(-180.0, 180.0),
                                                                       std::make_pair(-90.0, 90.0),
                                                                       min_length, max_length);
    
    {
      benchmark_t result;
      result.algorithm_name = "v1";
      result.num_segments = num_segments;
      
      std::chrono::time_point<std::chrono::system_clock> start, end;
      
      start = std::chrono::system_clock::now();
      
      std::size_t nips = 0;
      
      for(std::size_t i = 0; i < 5; ++i)
      {
        std::vector<gde::geom::core::point> ips = lazy_intersection_v1(segments);
        nips = ips.size();
      }
      
      end = std::chrono::system_clock::now();
      
      result.num_intersections = nips;
      result.elapsed_time = end - start;

      results.push_back(result);
    }
    
    {
      benchmark_t result;
      result.algorithm_name = "v2";
      result.num_segments = num_segments;
      
      std::chrono::time_point<std::chrono::system_clock> start, end;
      
      start = std::chrono::system_clock::now();

      std::size_t nips = 0;

      for(std::size_t i = 0; i < 5; ++i)
      {
        std::vector<gde::geom::core::point> ips = lazy_intersection_v2(segments);
        nips = ips.size();
      }

      end = std::chrono::system_clock::now();
      
      result.elapsed_time = end - start;      
      result.num_intersections = nips;
      
      results.push_back(result);
    }
    
    {
      benchmark_t result;
      result.algorithm_name = "v3";
      result.num_segments = num_segments;
      
      std::chrono::time_point<std::chrono::system_clock> start, end;
      
      start = std::chrono::system_clock::now();

      std::size_t nips = 0;

      for(std::size_t i = 0; i < 5; ++i)
      {
        std::vector<gde::geom::core::point> ips = lazy_intersection_v3(segments);
        nips = ips.size();
      }
      end = std::chrono::system_clock::now();
      
      result.elapsed_time = end - start;
      result.num_intersections = nips;
      
      results.push_back(result);
      
    }
  }
  
  print(results);
}

void do_tests2()
{
  double min_length = 30.0;
  double max_length = 45.0;
  std::vector<gde::geom::core::line_segment> segments = gen_segments(5000,
                                                                     std::make_pair(-180.0, 180.0),
                                                                     std::make_pair(-90.0, 90.0),
                                                                     min_length, max_length);

  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  gde::geom::algorithm::tiling_intersection(segments, max_length, 90.0, -90.0);
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> time = end - start;
  std::cout << time.count() << "  tile  \n\n\n";


  std::chrono::time_point<std::chrono::system_clock> start2, end2;
  start2 = std::chrono::system_clock::now();
  std::vector<gde::geom::core::point> segments2 = gde::geom::algorithm::x_order_intersection(segments);
  end2 = std::chrono::system_clock::now();
  time = end2 - start2;
  std::cout << time.count() << "  X \n\n";
  std::cout << segments2.size() << "  x  \n\n\n";



}

int main(int argc, char* argv[])
{
  //do_tests();
  do_tests2();
  
  return EXIT_SUCCESS;
}

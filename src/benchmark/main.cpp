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

struct benchmark_t
{
  std::string test_name;
  std::string algorithm_name;
  std::size_t red_segments;
  std::size_t blue_segments;
  std::size_t num_intersections;
  std::size_t repetitions;
  std::size_t num_threads;
  std::chrono::time_point<std::chrono::system_clock> start;
  std::chrono::time_point<std::chrono::system_clock> end;
  std::chrono::duration<double> elapsed_time;
};

std::vector<benchmark_t> performance_tests;

void print(const benchmark_t& result)
{
  std::cout << std::setprecision(10)
            << result.test_name << ";"
            << result.algorithm_name << ";"
            << result.red_segments << ";"
            << result.blue_segments << ";"
            << result.num_intersections << ";"
            << (result.elapsed_time.count() / static_cast<double>(result.repetitions)) << std::endl;
}

void
test_lazy_intersection_rb_thread(const std::string& test_name,
                                 const std::vector<gde::geom::core::line_segment>& red_segments,
                                 const std::vector<gde::geom::core::line_segment>& blue_segments,
                                 const std::string& output_shape_file,
                                 int srid)
{
  benchmark_t b;
  
  b.test_name = test_name;
  
  std::cout << "lazy_intersection_rb_thread: " << test_name << std::endl;
  
  b.num_threads = std::thread::hardware_concurrency();

  std::vector<std::vector<gde::geom::core::point> > intersetion_pts;
  
  b.start = std::chrono::system_clock::now();
  
  gde::geom::algorithm::lazy_intersection_rb_thread(red_segments, blue_segments, b.num_threads, intersetion_pts);
  
  b.end = std::chrono::system_clock::now();
  
  b.elapsed_time = b.end - b.start;
  
  b.algorithm_name = "lazy_intersection_rb_thread";
  b.red_segments = red_segments.size();
  b.blue_segments = blue_segments.size();
  b.repetitions = 1;
  
  std::vector<gde::geom::core::point> ipts;
  
  for(const auto& vecipts : intersetion_pts)
  {
    std::copy(vecipts.begin(), vecipts.end(), std::back_inserter(ipts));
  }
  
  b.num_intersections = ipts.size();
  
  print(b);
  
  //save_intersection_points(ipts, 0, srid, output_shape_file);
}

void
test_x_order_intersection_rb(const std::string& test_name,
                             const std::vector<gde::geom::core::line_segment>& red_segments,
                             const std::vector<gde::geom::core::line_segment>& blue_segments,
                             const std::string& output_shape_file,
                             int srid)
{
  benchmark_t b;
  
  b.test_name = test_name;
  
  std::cout << "x_order_intersection_rb: " << test_name << std::endl;
  
  b.start = std::chrono::system_clock::now();
  
  std::vector<gde::geom::core::point> ipts = gde::geom::algorithm::x_order_intersection_rb(red_segments, blue_segments);
  
  b.end = std::chrono::system_clock::now();
  
  b.elapsed_time = b.end - b.start;
  
  b.algorithm_name = "x_order_intersection_rb";
  b.num_intersections = ipts.size();
  b.red_segments = red_segments.size();
  b.blue_segments = blue_segments.size();
  b.repetitions = 1;
  
  print(b);

  //save_intersection_points(ipts, 0, srid, output_shape_file);
}

void
test_x_order_intersection_rb_thread(const std::string& test_name,
                                    const std::vector<gde::geom::core::line_segment>& red_segments,
                                    const std::vector<gde::geom::core::line_segment>& blue_segments,
                                    const std::string& output_shape_file,
                                    int srid)
{
  benchmark_t b;
  
  b.test_name = test_name;
  
  std::cout << "x_order_intersection_rb_thread: " << test_name << std::endl;
  
  b.num_threads = std::thread::hardware_concurrency();
  
  std::vector<std::vector<gde::geom::core::point> > intersection_pts;
  
  b.start = std::chrono::system_clock::now();
  
  gde::geom::algorithm::x_order_intersection_rb_thread(red_segments, blue_segments, b.num_threads, intersection_pts);
  
  b.end = std::chrono::system_clock::now();
  
  b.elapsed_time = b.end - b.start;
  
  b.algorithm_name = "x_order_intersection_rb_thread";
  b.red_segments = red_segments.size();
  b.blue_segments = blue_segments.size();
  b.repetitions = 1;
  
  std::vector<gde::geom::core::point> ipts;
  
  for(const auto& vecipts : intersection_pts)
  {
    std::copy(vecipts.begin(), vecipts.end(), std::back_inserter(ipts));
  }
  
  b.num_intersections = ipts.size();
  
  print(b);

  //save_intersection_points(ipts, 0, srid, output_shape_file);
}

void
test_fixed_grid_intersection_rb(const std::string& test_name,
                                const std::vector<gde::geom::core::line_segment>& red_segments,
                                const std::vector<gde::geom::core::line_segment>& blue_segments,
                                const std::string& output_shape_file,
                                int srid)
{
  benchmark_t b;
  
  b.test_name = test_name;
  
  std::cout << "fixed_grid_intersection_rb: " << test_name << std::endl;
  
  b.start = std::chrono::system_clock::now();
  
  gde::geom::core::rectangle r = gde::geom::algorithm::compute_rectangle(blue_segments.begin(), blue_segments.end());
  
  std::pair<double, double> res_x_y = gde::geom::algorithm::compute_average_length(blue_segments.begin(), blue_segments.end());
  
  std::vector<gde::geom::core::point> ipts = gde::geom::algorithm::fixed_grid_intersection_rb(red_segments, blue_segments, res_x_y.first * 4.0, res_x_y.second * 4.0, r.ll.x, r.ur.x, r.ll.y, r.ur.y);
  
  b.end = std::chrono::system_clock::now();
  
  b.elapsed_time = b.end - b.start;
  
  b.algorithm_name = "fixed_grid_intersection_rb";
  b.num_intersections = ipts.size();
  b.red_segments = red_segments.size();
  b.blue_segments = blue_segments.size();
  b.repetitions = 1;
  
  print(b);
  
  //save_intersection_points(ipts, 0, srid, output_shape_file);
}

void
test_fixed_grid_intersection_rb_thread(const std::vector<gde::geom::core::line_segment>& red_segments,
                                       const std::vector<gde::geom::core::line_segment>& blue_segments)
{
  benchmark_t b;

  std::size_t num_threads = std::thread::hardware_concurrency();

  std::cout << "test_fixed_grid_intersection_rb_thread..." << std::endl;

  gde::geom::core::rectangle r = gde::geom::algorithm::compute_rectangle(blue_segments.begin(), blue_segments.end());

  std::pair<double, double> res_x_y = gde::geom::algorithm::compute_average_length(blue_segments.begin(), blue_segments.end());

  std::vector<std::vector<gde::geom::core::point> > ipts;

  b.start = std::chrono::system_clock::now();

  gde::geom::algorithm::fixed_grid_intersection_rb_thread(red_segments, blue_segments, num_threads, res_x_y.first * 4.0, res_x_y.second * 4.0,
                                                          r.ll.x, r.ur.x, r.ll.y, r.ur.y, ipts);

  b.end = std::chrono::system_clock::now();

  b.elapsed_time = b.end - b.start;

  std::vector<gde::geom::core::point> ipt;

  for(const auto& vecipts : ipts)
  {
    std::copy(vecipts.begin(), vecipts.end(), std::back_inserter(ipt));
  }

  b.algorithm_name = "fixed_grid_intersection_rb";
  b.num_intersections = ipt.size();
  b.red_segments = red_segments.size();
  b.blue_segments = blue_segments.size();
  b.repetitions = 1;

  print(b);

  //save_intersection_points(ipts, 0, 4674, "/Users/gribeiro/Desktop/Curso-TerraView/test_fixed_grid_intersection_rb.shp");
}


void
test_tiling_intersection_rb(const std::string& test_name,
                            const std::vector<gde::geom::core::line_segment>& red_segments,
                            const std::vector<gde::geom::core::line_segment>& blue_segments,
                            const std::string& output_shape_file,
                            int srid)
{
  benchmark_t b;
  
  b.test_name = test_name;
  
  std::cout << "tiling_intersection_rb: " << test_name << std::endl;
  
  b.start = std::chrono::system_clock::now();

  gde::geom::core::rectangle rec_red = gde::geom::algorithm::compute_rectangle(red_segments.begin(), red_segments.end());
  gde::geom::core::rectangle rec_blue = gde::geom::algorithm::compute_rectangle(blue_segments.begin(), blue_segments.end());
  
  gde::geom::core::rectangle r(std::min(rec_red.ll.x, rec_blue.ll.x),
                               std::min(rec_red.ll.y, rec_blue.ll.y),
                               std::max(rec_red.ur.x, rec_blue.ur.x),
                               std::max(rec_red.ur.y, rec_blue.ur.y));
  
  std::pair<double, double> res_x_y_red = gde::geom::algorithm::compute_average_length(red_segments.begin(), red_segments.end());
  std::pair<double, double> res_x_y_blue = gde::geom::algorithm::compute_average_length(blue_segments.begin(), blue_segments.end());

  double res_y = (res_x_y_red.second * static_cast<double>(red_segments.size()) + res_x_y_blue.second * static_cast<double>(blue_segments.size())) / static_cast<double>(red_segments.size() + blue_segments.size());
  
  
  
  std::vector<gde::geom::core::point> ipts = gde::geom::algorithm::tiling_intersection_rb(red_segments, blue_segments, res_y * 4.0, r.ll.y, r.ur.y);
  
  b.end = std::chrono::system_clock::now();
  
  b.elapsed_time = b.end - b.start;
  
  b.algorithm_name = "tiling_intersection_rb";
  b.num_intersections = ipts.size();
  b.red_segments = red_segments.size();
  b.blue_segments = blue_segments.size();
  b.repetitions = 1;
  
  print(b);
  
  //save_intersection_points(ipts, 0, srid, output_shape_file);
}



void
test_tiling_intersection_rb_thread(const std::vector<gde::geom::core::line_segment>& red_segments,
                                   const std::vector<gde::geom::core::line_segment>& blue_segments)
{

  std::size_t num_threads = std::thread::hardware_concurrency();

  benchmark_t b;

  std::cout << "test_tiling_intersection_rb_thread..." << std::endl;

  gde::geom::core::rectangle rec_red = gde::geom::algorithm::compute_rectangle(red_segments.begin(), red_segments.end());
  gde::geom::core::rectangle rec_blue = gde::geom::algorithm::compute_rectangle(blue_segments.begin(), blue_segments.end());

  gde::geom::core::rectangle r(std::min(rec_red.ll.x, rec_blue.ll.x),
                               std::min(rec_red.ll.y, rec_blue.ll.y),
                               std::max(rec_red.ur.x, rec_blue.ur.x),
                               std::max(rec_red.ur.y, rec_blue.ur.y));

  std::pair<double, double> res_x_y_red = gde::geom::algorithm::compute_average_length(red_segments.begin(), red_segments.end());
  std::pair<double, double> res_x_y_blue = gde::geom::algorithm::compute_average_length(blue_segments.begin(), blue_segments.end());

  double res_y = (res_x_y_red.second * static_cast<double>(red_segments.size()) + res_x_y_blue.second * static_cast<double>(blue_segments.size())) / static_cast<double>(red_segments.size() + blue_segments.size());

  std::vector<std::vector<gde::geom::core::point> > ipts;

  b.start = std::chrono::system_clock::now();

  gde::geom::algorithm::tiling_intersection_rb_thread(red_segments, blue_segments,num_threads, res_y * 4.0, r.ll.y, r.ur.y,ipts);

  b.end = std::chrono::system_clock::now();

  b.elapsed_time = b.end - b.start;

  std::vector<gde::geom::core::point> ipt;

  for(const auto& vecipts : ipts)
  {
    std::copy(vecipts.begin(), vecipts.end(), std::back_inserter(ipt));
  }

  b.algorithm_name = "tiling_intersection_rbthread";
  b.num_intersections = ipt.size();
  b.red_segments = red_segments.size();
  b.blue_segments = blue_segments.size();
  b.repetitions = 1;

  print(b);

  //save_intersection_points(ipts, 0, 4674, "/home/joao/Desktop/RTP/intersection_rb");
}

int main(int argc, char* argv[])
{
  StartTerraLib();
  
  if(true)
  {
    //std::vector<gde::geom::core::line_segment> trechos_drenagem = extract_segments_from_shp("/Users/gribeiro/Desktop/Curso-TerraView/ba_drenagem/HID_Trecho_Drenagem_L.shp");
  
    //std::vector<gde::geom::core::line_segment> trechos_rodoviario = extract_segments_from_shp("/Users/gribeiro/Desktop/Curso-TerraView/trechos_rodovarios/TRA_Trecho_Rodoviario_L.shp");

    std::vector<gde::geom::core::line_segment> trechos_drenagem = extract_segments_from_shp("/home/joao/Desktop/ba_drenagem/ba_drenagem/HID_Trecho_Drenagem_L.shp");

    std::vector<gde::geom::core::line_segment> trechos_rodoviario = extract_segments_from_shp("/home/joao/Desktop/trechos_rodovarios/trechos_rodovarios/TRA_Trecho_Rodoviario_L.shp");
    
    //test_lazy_intersection_rb_thread("lazy_intersection_rb_thread - drenagem x trechos rodoviarios", trechos_drenagem, trechos_rodoviario, "/Users/gribeiro/Desktop/Curso-TerraView/result_lazy_intersection_rb_thread.shp", 4674);
    
 //   test_x_order_intersection_rb("x_order_intersection_rb - drenagem x trechos rodoviarios", trechos_drenagem, trechos_rodoviario, "/Users/gribeiro/Desktop/Curso-TerraView/result_x_order_intersection_rb.shp", 4674);
    
  //  test_x_order_intersection_rb_thread("x_order_intersection_rb_thread - drenagem x trechos rodoviarios", trechos_drenagem, trechos_rodoviario, "/Users/gribeiro/Desktop/Curso-TerraView/result_x_order_intersection_rb_thread.shp", 4674);

    //test_fixed_grid_intersection_rb("fixed_grid_intersection_rb - drenagem x trechos rodoviarios", trechos_drenagem, trechos_rodoviario, "/Users/gribeiro/Desktop/Curso-TerraView/result_fixed_grid_intersection_rb.shp", 4674);
    
    //test_fixed_grid_intersection_rb_thread(trechos_drenagem, trechos_rodoviario);

    test_tiling_intersection_rb("tiling_intersection_rb - drenagem x trechos rodoviarios", trechos_drenagem, trechos_rodoviario, "/Users/gribeiro/Desktop/Curso-TerraView/result_tiling_intersection_rb.shp", 4674);

    test_tiling_intersection_rb_thread(trechos_drenagem, trechos_rodoviario);
  }
  
  if(false)
  {
    std::vector<gde::geom::core::line_segment> municipios_go = extract_segments_from_shp("/Users/gribeiro/Desktop/Curso-TerraView/go_municipios/municipio.shp");
  
    std::vector<gde::geom::core::line_segment> geologia_go = extract_segments_from_shp("/Users/gribeiro/Desktop/Curso-TerraView/go_geologia/geologia.shp");
    
    //test_lazy_intersection_rb_thread("lazy_intersection_rb_thread - municipios_go x geologia_go", municipios_go, geologia_go, "/Users/gribeiro/Desktop/Curso-TerraView/result_lazy_intersection_rb_thread_geologia.shp", 4326);
    
    test_x_order_intersection_rb("x_order_intersection_rb - municipios_go x geologia_go", municipios_go, geologia_go, "/Users/gribeiro/Desktop/Curso-TerraView/result_x_order_intersection_rb_geologia.shp", 4326);
    
    test_x_order_intersection_rb_thread("x_order_intersection_rb_thread - municipios_go x geologia_go", municipios_go, geologia_go, "/Users/gribeiro/Desktop/Curso-TerraView/result_x_order_intersection_rb_thread_geologia.shp", 4326);
    
    test_fixed_grid_intersection_rb("fixed_grid_intersection_rb - municipios_go x geologia_go", municipios_go, geologia_go, "/Users/gribeiro/Desktop/Curso-TerraView/result_fixed_grid_intersection_rb_geologia.shp", 4326);
    
    test_tiling_intersection_rb("tiling_intersection_rb - municipios_go x geologia_go", municipios_go, geologia_go, "/Users/gribeiro/Desktop/Curso-TerraView/result_tiling_intersection_rb_geologia.shp", 4326);
  }
                                                    
  StopTerraLib();

  return EXIT_SUCCESS;
}


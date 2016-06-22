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
  \file gde/geom/algorithm/fixed_grid_intersection_rb_thread.cpp

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
#include <cmath>
#include <map>
#include <thread>


struct intersection_computer6
{
  std::size_t thread_pos;
  std::size_t num_threads;
  double dx;
  double dy;
  double xmin;
  double ymin;
  std::size_t nrows;
  std::vector<gde::geom::core::point>* ipts;
  std::multimap<std::size_t, std::size_t>* blue_grid;
  const std::vector<gde::geom::core::line_segment>* red_segments;
  const std::vector<gde::geom::core::line_segment>* blue_segments;

  void operator()()
  {
      gde::geom::core::point ip1;
      gde::geom::core::point ip2;

      std::size_t nred_segments = red_segments->size();

      for(std::size_t i = thread_pos; i < nred_segments; i += num_threads)
      {
        const auto& red = (*red_segments)[i];

        std::size_t first_col = (red.p1.x - xmin) / dx;
        std::size_t first_row = (red.p1.y - ymin) / dy;

        std::size_t second_col = (red.p2.x - xmin) / dx;
        std::size_t second_row = (red.p2.y - ymin) / dy;

        std::pair<std::size_t, std::size_t> min_max_col = std::minmax(first_col, second_col);
        std::pair<std::size_t, std::size_t> min_max_row = std::minmax(first_row, second_row);

        for(std::size_t col = min_max_col.first; col <= min_max_col.second; ++col)
        {
          std::size_t offset = col * nrows;

          for(std::size_t row = min_max_row.first; row <= min_max_row.second; ++row)
          {
            std::size_t k = row + offset;

            auto range = blue_grid->equal_range(k);

            while(range.first != range.second)
            {
              std::size_t blue_idx = range.first->second;

              const auto& blue = (*blue_segments)[blue_idx];

              if(gde::geom::algorithm::do_bounding_box_intersects(red, blue))
              {
                gde::geom::algorithm::segment_relation_type spatial_relation = gde::geom::algorithm::compute_intesection_v3(red, blue, ip1, ip2);

                if(spatial_relation != gde::geom::algorithm::DISJOINT)
                {
                  if(gde::geom::algorithm::is_in_cell(xmin, ymin, dx, dy, col, row, ip1.x, ip1.y))
                    ipts->push_back(ip1);

                  if(spatial_relation == gde::geom::algorithm::OVERLAP)
                  {
                    if(gde::geom::algorithm::is_in_cell(xmin, ymin, dx, dy, col, row, ip2.x, ip2.y))
                      ipts->push_back(ip2);
                  }
                }
              }
              ++(range.first);
            }
          }
        }
      }
  }
};

void
gde::geom::algorithm::fixed_grid_intersection_rb_thread(const std::vector<gde::geom::core::line_segment>& red_segments,
                                  const std::vector<gde::geom::core::line_segment>& blue_segments,
                                  std::size_t nthreads, double dx, double dy, double xmin,
                                  double xmax,double ymin, double ymax,
                                  std::vector<std::vector<gde::geom::core::point> >& intersetion_pts)
{
  std::vector<gde::geom::core::point> ipts;

  intersetion_pts.resize(nthreads);

  std::size_t nrows = std::ceil(((ymax - ymin) / dy));

  const std::size_t nblue_segments = blue_segments.size();

// index blue segments in a grid
  std::multimap<std::size_t, std::size_t> blue_grid;

  for(std::size_t i = 0; i != nblue_segments; ++i)
  {
    const gde::geom::core::line_segment& blue = blue_segments[i];

    std::size_t first_col = (blue.p1.x - xmin) / dx;
    std::size_t first_row = (blue.p1.y - ymin) / dy;

    std::size_t second_col = (blue.p2.x - xmin) / dx;
    std::size_t second_row = (blue.p2.y - ymin) / dy;

    std::pair<std::size_t, std::size_t> min_max_col = std::minmax(first_col, second_col);
    std::pair<std::size_t, std::size_t> min_max_row = std::minmax(first_row, second_row);

    for(std::size_t col = min_max_col.first; col <= min_max_col.second; ++col)
    {
      std::size_t offset = col * nrows;

      for(std::size_t row = min_max_row.first; row <= min_max_row.second; ++row)
      {
        std::size_t k = row + offset;

        blue_grid.insert(std::make_pair(k, i));
      }
    }
  }

  std::vector<std::thread> threads;

  for(std::size_t i = 0; i != nthreads; ++i)
  {
    intersection_computer6 ic = {i, nthreads,dx ,dy ,xmin ,ymin , nrows,&(intersetion_pts[i]) ,&blue_grid ,&red_segments ,&blue_segments};
    threads.push_back(std::thread(ic));
  }

  for(std::size_t i = 0; i != nthreads; ++i)
    threads[i].join();

}

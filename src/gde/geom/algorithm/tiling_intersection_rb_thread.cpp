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
  \file gde/geom/algorithm/tiling_intersection_rb_thread.cpp

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

struct tiling_computer
{
  const double dy;
  const double ymin;
  const std::vector<gde::geom::core::line_segment>* segments;
  std::vector<std::vector<gde::geom::core::line_segment> >* tile_idx;

  void operator()()
  {
      for(const auto& seg : (*segments))
      {
        std::size_t first_row = (seg.p1.y - ymin) / dy;
        std::size_t second_row = (seg.p2.y - ymin) / dy;

        std::pair<std::size_t, std::size_t> min_max_row = std::minmax(first_row, second_row);

        for(std::size_t row = min_max_row.first; row <= min_max_row.second; ++row)
        {
          (*tile_idx)[row].push_back(seg);
        }
      }
  }
};

struct intersection_computer5
{
  std::size_t thread_pos;
  std::size_t nthread;
  std::vector<gde::geom::core::point>* ipts;
  const std::size_t nrows;
  double dy;
  double ymin;
  const std::vector<std::vector<gde::geom::core::line_segment> >* red_tile_idx;
  const std::vector<std::vector<gde::geom::core::line_segment> >* blue_tile_idx;

  void operator()()
  {
      double dy;
      double ymin;

      dy = this->dy;
      ymin = this->ymin;

// compute intersections using x-order for each tile!
    for(std::size_t i = thread_pos; i <= nrows; i += nthread)
    {
      const std::vector<gde::geom::core::line_segment>& r_segs = (*red_tile_idx)[i];
      const std::vector<gde::geom::core::line_segment>& b_segs = (*blue_tile_idx)[i];

      std::vector<gde::geom::core::point> ips = gde::geom::algorithm::x_order_intersection_rb(r_segs , b_segs);

      std::copy_if(ips.begin(), ips.end(), std::back_inserter(*ipts), [&i, &dy, &ymin]
                                                                   (const gde::geom::core::point& ip)
                                                                   { return gde::geom::algorithm::is_in_tile(ymin, dy, i, ip.y); } );

    }
  }
};

void
gde::geom::algorithm::tiling_intersection_rb_thread(const std::vector<gde::geom::core::line_segment>& red_segments,
                                                    const std::vector<gde::geom::core::line_segment>& blue_segments,
                                                    std::size_t nthreads,double dy, double ymin, double ymax,
                                                    std::vector<std::vector<gde::geom::core::point> >& intersetion_pts)
{
  std::size_t nrows = std::ceil(((ymax - ymin) / dy));

// index red and blue segments in separated tile-index
  std::vector<std::vector<gde::geom::core::line_segment> > red_tile_idx(nrows + 1);
  std::vector<std::vector<gde::geom::core::line_segment> > blue_tile_idx(nrows + 1);

  intersetion_pts.resize(nthreads);

  std::vector<std::thread> threads;

  tiling_computer rt = {dy, ymin, &red_segments, &red_tile_idx};
  threads.push_back(std::thread(rt));

  tiling_computer bt = {dy, ymin, &blue_segments, &blue_tile_idx};
  threads.push_back(std::thread(bt));

  for(std::size_t i = 0; i != 2; ++i)
    threads[i].join();

  threads.clear();

  for(std::size_t i = 0; i != nthreads; ++i)
  {
    intersection_computer5 ic = {i,nthreads ,&(intersetion_pts[i]),nrows, dy, ymin, &red_tile_idx, &blue_tile_idx};
    threads.push_back(std::thread(ic));
  }

  for(std::size_t i = 0; i != nthreads; ++i)
    threads[i].join();

}

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
  \file gde/geom/algorithm/tiling_intersection_rb.cpp

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

inline
void block_segments(const std::vector<gde::geom::core::line_segment>& segments,
                    double t_max,double block_size,double block,
                    std::vector<gde::geom::core::line_segment> *segments_range)
{
// through all segments
  for(int i = 0;i < segments.size(); ++i)
  {
    int cont = 0;
// through every division blocks in Y
    for(int y = block; y <= t_max; y += block_size)
    {

// checks whether the segment y value is within block
       if(segments[i].p1.y < y || segments[i].p2.y < y)
       {

// adds the segment in its corresponding block
         segments_range[cont].push_back(segments[i]);

// checks if one of the points of this segment this the top of this block
          if((segments[i].p1.y > y || segments[i].p2.y > y) &&y < t_max)
            segments_range[cont+1].push_back(segments[i]);
            break;
        }
     cont++;
     }
   }
}

std::vector<gde::geom::core::point>
gde::geom::algorithm::tiling_intersection_rb(const std::vector<gde::geom::core::line_segment>& red,
                                          const std::vector<gde::geom::core::line_segment>& blue,
                                          const double& max_length_r, const double& max_range_r, const double& min_range_r,
                                          const double& max_length_b, const double& max_range_b, const double& min_range_b)
{
  double max_length, max_range, min_range;

// setting values ​​for building blocks
  if(max_length_r > max_length_b)
    max_length = max_length_r;
  else
    max_length = max_length_b;

  if(max_range_r > max_range_b)
    max_range = max_range_r;
  else
    max_range = max_range_b;

  if(min_range_r < min_range_b)
    min_range = min_range_r;
  else
    min_range = min_range_b;


// defines scope of the blocks
  int range = (gde::geom::algorithm::return_positive_value(max_range) / max_length) + 2;

  std::vector<gde::geom::core::point> ipts;
  std::vector<gde::geom::core::line_segment> segments_range_r[range];
  std::vector<gde::geom::core::line_segment> segments_range_b[range];

  double t_max = max_range + gde::geom::algorithm::return_positive_value(min_range);

// size of the blocks
  double block_size = t_max/range;

// current block
  double block = min_range + block_size;
   block_segments(red,t_max,block_size,block,segments_range_r);
   block_segments(blue,t_max,block_size,block,segments_range_b);
  //std::thread t1(&block_segments,red,t_max,block_size,block,*segments_range_r);
  //std::thread t2(&block_segments,blue,t_max,block_size,block,*segments_range_b);

 // t1.join();
 // t2.join();

// x-ordering
  int size = 0;
  int i = 0;
  for(auto& elemento: segments_range_r)
  {
    ipts = gde::geom::algorithm::x_order_intersection_rb(segments_range_r[i],segments_range_b[i], block,(block-block_size));
    block += block_size;
    size += ipts.size();
    i++;
  }

  return ipts;
}

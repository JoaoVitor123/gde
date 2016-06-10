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

struct intersection_computer
{
  std::size_t thread_pos;
  std::size_t num_threads;
  std::vector<gde::geom::core::point>* ipts;
  const std::vector<gde::geom::core::line_segment>* red_segments;
  const std::vector<gde::geom::core::line_segment>* blue_segments;
  
  void operator()()
  {
    gde::geom::core::point ip1;
    gde::geom::core::point ip2;
    
    std::size_t nred_segments = red_segments->size();
    std::size_t nblue_segments = blue_segments->size();
    
    for(std::size_t i = thread_pos; i < nred_segments; i += num_threads)
    {
      const gde::geom::core::line_segment& red = (*red_segments)[i];
      
      for(std::size_t j = 0; j < nblue_segments; ++j)
      {
        const gde::geom::core::line_segment& blue = (*blue_segments)[j];
        
        if(!gde::geom::algorithm::do_bounding_box_intersects(red, blue))
          continue;
        
        gde::geom::algorithm::segment_relation_type spatial_relation = gde::geom::algorithm::compute_intesection_v3(red, blue, ip1, ip2);
        
        if(spatial_relation == gde::geom::algorithm::DISJOINT)
          continue;
        
        ipts->push_back(ip1);
        
        if(spatial_relation == gde::geom::algorithm::OVERLAP)
          ipts->push_back(ip2);
      }
    }
  }
};

void
gde::geom::algorithm::lazy_intersection_rb_thread(const std::vector<gde::geom::core::line_segment>& r,
                                                  const std::vector<gde::geom::core::line_segment>& b,
                                                  std::size_t nthreads,
                                                  std::vector<std::vector<gde::geom::core::point> >& intersetion_pts)
{
  intersetion_pts.resize(nthreads);
  
  std::vector<std::thread> threads;
  
  for(std::size_t i = 0; i != nthreads; ++i)
  {
    intersection_computer ic = { i, nthreads, &(intersetion_pts[i]), &r, &b};
    threads.push_back(std::thread(ic));
  }
  
  for(std::size_t i = 0; i != nthreads; ++i)
    threads[i].join();
}

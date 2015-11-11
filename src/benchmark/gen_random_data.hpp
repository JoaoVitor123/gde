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
  \file benchmark/gen_random_data.hpp

  \brief Utility functiond for generating random data.

  \author Joao Vitor Chagas
 */


#ifndef __GDE_GEOM_ALGORITHM_LINE_SEGMENT_INTERSECTION_HPP__
#define __GDE_GEOM_ALGORITHM_LINE_SEGMENT_INTERSECTION_HPP__

// GDE
#include <gde/geom/core/geometric_primitives.hpp>

// STL
#include <vector>
#include <random>
#include <algorithm>

/*!
  \brief generates a doble between p_max and p_min

  Picks a double number between p_max and p_min using the function rand.
 */
inline
double gen_point(double p_max, double p_min);

/*!
  \brief check that the segment is between the max and min

  Using the function minmax determines the highest and lowest ponro and compares them with the values ​​and min but to validate the segment.
 */
inline
bool check_segment(const gde::geom::core::line_segment& s,
                   double max, double min);

/*!
  \brief Generates line segments

  This function takes receives the parameters to generate line segments , it creates segments with gen_point function and then checks with check_segment function
 */
std::vector<gde::geom::core::line_segment> gen_segments(std::size_t num_segments, double max, double min,
                                                        double p_max, double p_min);



#endif // __GDE_GEOM_ALGORITHM_LINE_SEGMENT_INTERSECTION_HPP__

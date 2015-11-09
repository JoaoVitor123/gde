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
  \file benchmark/gen_random_data.cpp

  \brief Utility functiond for generating random data.

  \author Joao Vitor Chagas
 */

// GDE
#include "gen_random_data.hpp"
#include <iostream>

// J
double gen_point()
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);

  std::uniform_int_distribution<int> distribution(0, 8);

  return double(distribution(generator));
}

bool check_segment(const gde::geom::core::line_segment& s,
                      double max, double min)
{
// check the highest and lowest point of the segment
  const auto&  minmax1 = std::minmax(s.p1.x, s.p2.x);
  const auto&  minmax2 = std::minmax(s.p1.y, s.p2.y);

// ...

  if((minmax1.second - minmax1.first) < min || (minmax1.second - minmax1.first) > max)
    return true;

// ...
  if((minmax2.second - minmax2.first) < min || (minmax2.second - minmax2.first) > max)
    return true;

  return false;
}
//
std::vector<gde::geom::core::line_segment> gen_segments(std::size_t num_segments, double max, double min)
{

// output segment list
  std::vector<gde::geom::core::line_segment> segments;
  
// we can reserve memory for #num_segments
  segments.reserve(num_segments);

// J

  gde::geom::core::line_segment segment;
// define the points p1 and p2 of each segment
  for(int i = 0; i < 2; ++i)
  {
// ...
   // segment = new gde::geom::core::line_segment();

    segment.p1.x = gen_point();
    segment.p1.y = gen_point();

    segment.p2.x = gen_point();
    segment.p2.y = gen_point();

// ...
    if(check_segment(segment, max, min))
      --i;
    else
      segments.push_back(segment);
    std::cout << segment.p1.x << "\n";
  }
//

// Passos do algoritmo de geracao de segmentos aleatorios
// 1 - o intervalo para geracao do segmentos sera o seguinte:
//     x [-180.0, 180.0]  => pode se tornar parametro do algoritmo
//     y [-90.0, 90.0]    => pode se tornar parametro do algoritmo
// 2 - num_segments define o numero de segmentos a ser gerado.
// 3 - estabelecer o tamanho maximo e minimo de cada segmento => pode se tornar parametro do algoritmo

  return segments;
}


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

std::vector<gde::geom::core::line_segment> gen_segments(std::size_t num_segments)
{
// output segment list
  std::vector<gde::geom::core::line_segment> segments;
  
// we can reserve memory for #num_segments
  segments.reserve(num_segments);
  

// Passos do algoritmo de geracao de segmentos aleatorios
// 1 - o intervalo para geracao do segmentos sera o seguinte:
//     x [-180.0, 180.0]  => pode se tornar parametro do algoritmo
//     y [-90.0, 90.0]    => pode se tornar parametro do algoritmo
// 2 - num_segments define o numero de segmentos a ser gerado.
// 3 - estabelecer o tamanho maximo e minimo de cada segmento => pode se tornar parametro do algoritmo
  return segments;
}


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
  \file unittest/geom/algorithm/main.cpp

  \brief Perform unittest on geometric algorithms.

  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

// GDE
/*#include <gde/geom/algorithm/line_segment_intersection.hpp>
#include <gde/geom/algorithm/line_segments_intersection.hpp>
#include <gde/geom/core/geometric_primitives.hpp>

// STL
#include <iostream>

void print(const std::vector<gde::geom::core::point>& intersections)
{
  for(const gde::geom::core::point& ip : intersections)
  {
    std::cout << ip.x << ", " << ip.y << std::endl;
  }
}

void test1()
{
  gde::geom::core::line_segment s1 = { {0, 0}, {10, 10} };
  gde::geom::core::line_segment s2 = { {0, 10}, {10, 0} };
  
  std::cout << "s1 intersects s2? " << gde::geom::algorithm::do_intersects_v1(s1, s2) << std::endl;
}

void test_lazy_intersection()
{
  std::vector<gde::geom::core::line_segment> segments = {
    { {0, 0}, {3, 3} },
    { {1, 3}, {2, 7} },
    { {4, 4}, {1, 7} },
    { {4, 5}, {7, 8} },
    { {9, 3}, {5, 8} }
  };
  
  std::vector<gde::geom::core::point> intersections = gde::geom::algorithm::lazy_intersection(segments);
  
  print(intersections);
}

int main(int argc, char* argv[])
{
  test1();

  test_lazy_intersection();


  return EXIT_SUCCESS;
}
*/

#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <thread>

int do_something(char c)
{
  std::stringstream s;
  
  s << "TID: " << std::this_thread::get_id();
  
  std::cout << s.str() << std::endl;

  std::default_random_engine dre(c);
  
  std::uniform_int_distribution<int> id(10, 1000);
  
  for(int i = 0; i < 10; ++i)
  {
    int v = id(dre);
    std::this_thread::sleep_for(std::chrono::milliseconds(v));
    
    std::cout.put(c).flush();
  }
  
  return c;
}


int func1()
{
  return do_something('.');
}

int func2()
{
  return do_something('+');
}

struct func3
{
  void operator()()
  {
    do_something('*');
    throw std::string("teste");
  }
};

int teste_future_async(int argc, char* argv[])
{
  try {
// chama func1 de forma assincrona
  std::future<int> result1(std::async(func1));

// chama func3 de forma assincrona
  std::future<void> result3(std::async(func3()));
  
// chama do_something de forma assincrona
  std::future<void> result4(std::async([]{ do_something('&');}));

  
// chama func2 de forma sincrona
  int result2 = func2();
  
// aguarda func1 terminar, soma e imprime o resultado
  int result = result1.get() + result2;
  result3.wait();
  result4.get();

  std::cout << "\nResultado: " << result << std::endl;
  }
  catch(...)
  {
    std::cout << "pulou fora" << std::endl;
  }

  return EXIT_SUCCESS;
}

int teste_thread(int argc, char* argv[])
{
  //std::thread t(do_something, 'c');
  
  std::thread t([]{ while(true) { std::cout << "." << std::endl; } });
  
  while(true);
  
  
  return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
  //teste_future_async(argc, argv);
  teste_thread(argc, argv);
 
  return EXIT_SUCCESS;
}

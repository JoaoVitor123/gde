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
  \file benchmark/prepare_real_data.cpp

  \brief Utility functions for preparing real data for the benchmark.

  \author Joao Vitor Chagas
  \author Gilberto Ribeiro de Queiroz
 */

// GDE
#include "prepare_real_data.hpp"

// TerraLib
#ifdef GDE_WITH_TERRALIB
#include <terralib/common.h>
#include <terralib/dataaccess.h>
#include <terralib/geometry.h>
#include <terralib/memory.h>
#include <terralib/plugin.h>
#endif

// STL
#include <iterator>

void StartTerraLib()
{
#ifdef GDE_WITH_TERRALIB
  TerraLib::getInstance().initialize();
  
  te::plugin::PluginInfo* info;
  
  std::string plugins_path = te::common::FindInTerraLibPath("share/terralib/plugins");
  
  info = te::plugin::GetInstalledPlugin(plugins_path + "/te.da.ogr.teplg");
  te::plugin::PluginManager::getInstance().add(info);
  
  te::plugin::PluginManager::getInstance().loadAll();
#endif
}

void StopTerraLib()
{
#ifdef GDE_WITH_TERRALIB
  te::plugin::PluginManager::getInstance().unloadAll();
  
  TerraLib::getInstance().finalize();
#endif
}

template<class OutputIterator>
void Convert2Segments(const te::gm::Geometry& geom,
                      OutputIterator result)
{
#ifdef GDE_WITH_TERRALIB
  switch(geom.getGeomTypeId())
  {
    case te::gm::LineStringType:
    case te::gm::LineStringZType:
    case te::gm::LineStringMType:
    case te::gm::LineStringZMType:
      {
        const te::gm::LineString& line = dynamic_cast<const te::gm::LineString&>(geom);
    
        std::size_t npts = line.size();
    
        if(npts == 1)
          throw std::invalid_argument("Invalid geometry: a linestring must have at least 2 vertices!");
    
        gde::geom::core::point p1;
        gde::geom::core::point p2;
    
        p1.x = line.getX(0);
        p1.y = line.getY(0);
    
        for(std::size_t i = 1; i != npts; ++i)
        {
          p2.x = line.getX(i);
          p2.y = line.getY(i);
      
          gde::geom::core::line_segment s(p1, p2);
      
          *result = s;
          ++result;
      
          p1 = p2;
        }
    
      }
      break;
    case te::gm::MultiLineStringType:
    case te::gm::MultiLineStringZType:
    case te::gm::MultiLineStringMType:
    case te::gm::MultiLineStringZMType:
      {
        const te::gm::MultiLineString& mline = dynamic_cast<const te::gm::MultiLineString&>(geom);
    
        std::size_t nlines = mline.getNumGeometries();
    
        for(std::size_t i = 0; i != nlines; ++i)
        {
          const te::gm::Geometry* geom_part = mline.getGeometryN(i);
      
          Convert2Segments(*geom_part, result);
        }
      }
      break;
      
    default:
      throw std::logic_error("Invalid geometry type!");
  }
#endif
}

std::vector<gde::geom::core::line_segment>
extract_segments_from_shp(const std::string& shp_file_name)
{
  std::vector<gde::geom::core::line_segment> segments;

#ifdef GDE_WITH_TERRALIB
  std::unique_ptr<te::da::DataSource> ds = te::da::DataSourceFactory::make("OGR");
  
  std::map<std::string, std::string> connInfo;
  connInfo["URI"] = shp_file_name;
  
  ds->setConnectionInfo(connInfo);
  
  ds->open();
  
  std::vector<std::string> dsets = ds->getDataSetNames();
  
  std::unique_ptr<te::da::DataSet> dataset = ds->getDataSet(dsets[0]);
  
  std::size_t pos = te::da::GetFirstPropertyPos(dataset.get(), te::dt::GEOMETRY_TYPE);
  
  while(dataset->moveNext())
  {
    try
    {
      std::unique_ptr<te::gm::Geometry> geom (dataset->getGeometry(pos));
    
      Convert2Segments(*geom, std::back_inserter(segments));
    }
    catch(...)
    {
    }
    
  }
  
#endif
  
  return segments;
}

te::gm::Point*
Convert2Point(const gde::geom::core::point& ip, int srid)
{
  te::gm::Point* pt = new te::gm::Point(ip.x, ip.y, srid);
  
  return pt;
}

void save_intersection_points(const std::vector<gde::geom::core::point>& ipts,
                              int initial_gid,
                              int srid,
                              const std::string& shapefile_name)
{
  std::auto_ptr<te::da::DataSetType> dt(new te::da::DataSetType("intersections"));
  
  te::dt::SimpleProperty* p1 = new te::dt::SimpleProperty("gid", te::dt::INT32_TYPE, true);
  te::gm::GeometryProperty* p2 = new te::gm::GeometryProperty("ip", srid, te::gm::PointType, true);
  
  dt->add(p1);
  dt->add(p2);
  
  std::unique_ptr<te::mem::DataSet> dataset(new te::mem::DataSet(dt.get()));
  
  for(std::size_t i = 0; i < ipts.size(); ++i)
  {
    int gid = initial_gid + i;
    
    te::gm::Point* pt = Convert2Point(ipts[i], srid);
    
    te::mem::DataSetItem* item = new te::mem::DataSetItem(dataset.get());
    item->setInt32(0, gid);
    item->setGeometry(1, pt);
    
    dataset->add(item);
  }
  
  std::map<std::string, std::string> connInfo;
  connInfo["URI"] = shapefile_name;
  connInfo["DRIVER"] = "ESRI Shapefile";
  
  std::auto_ptr<te::da::DataSource> dsOGR = te::da::DataSourceFactory::make("OGR");
  dsOGR->setConnectionInfo(connInfo);
  dsOGR->open();
  
  dataset->moveBeforeFirst();
  
  te::da::Create(dsOGR.get(), dt.get(), dataset.get());
}

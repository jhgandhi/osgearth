/* -*-c++-*- */
/* osgEarth - Dynamic map generation toolkit for OpenSceneGraph
 * Copyright 2008-2010 Pelican Mapping
 * http://osgearth.org
 *
 * osgEarth is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include <osgEarth/TileSourceFactory>
#include <osgEarth/Caching>
#include <osgEarth/Registry>

#define LC "[TileSourceFactory] "

using namespace osgEarth;

TileSource*
TileSourceFactory::create( const DriverOptions* driverOptions )
{
    TileSource* tileSource = 0L;
    if ( driverOptions )
    {
        OE_INFO << LC << "Loading tile source from driver \"" << driverOptions->driver() << "\"" << std::endl;

        std::string driverExt = std::string(".osgearth_") + driverOptions->driver();

        tileSource = dynamic_cast<TileSource*>( osgDB::readObjectFile( driverExt, driverOptions ) );
        if( !tileSource )
        {
            OE_WARN
                << "WARNING: Failed to load tile source driver for " << driverExt << std::endl;
        }
    }
    else
    {
        OE_WARN
            << "ERROR: null driver options to TileSourceFactory" << std::endl;
    }
    return tileSource;
}


TileSource*
TileSourceFactory::create( const std::string& driver,
                           const Config&      driverConf,
						   const osgDB::ReaderWriter::Options* global_options
                           )
{
    osg::ref_ptr<PluginOptions> options = global_options?
        new PluginOptions( *global_options ) :
        new PluginOptions();

    //Setup the plugin options for the source
    options->config() = driverConf;

    OE_INFO
        << "Driver " << driver << ", config =" << std::endl << driverConf.toString() << std::endl;

	//Load the source from the a plugin.  The "." prefix causes OSG to select the correct plugin.
    //For instance, the WMS plugin can be loaded by using ".osgearth_wms" as the filename
    osg::ref_ptr<TileSource> tileSource = dynamic_cast<TileSource*>(
                osgDB::readObjectFile( std::string(".osgearth_") + driver, options.get()));

	if (!tileSource.valid())
	{
		OE_NOTICE << "Warning: Could not load TileSource for driver "  << driver << std::endl;
	}

	return tileSource.release();
}
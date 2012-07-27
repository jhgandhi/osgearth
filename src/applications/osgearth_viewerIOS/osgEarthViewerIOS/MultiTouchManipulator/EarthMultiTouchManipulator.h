/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2010 Robert Osfield
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
*/

#ifndef OSGEARTHUTIL_EARTHMULTITOUCHMANIPULATOR
#define OSGEARTHUTIL_EARTHMULTITOUCHMANIPULATOR

#include <osgEarthUtil/EarthManipulator>


namespace osgEarth { namespace Util
{
    
class EarthMultiTouchManipulator : public EarthManipulator
{
public:

    EarthMultiTouchManipulator( int flags = DEFAULT_SETTINGS );
    EarthMultiTouchManipulator( const EarthMultiTouchManipulator& tm,
                          const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );


    bool handle( const GUIEventAdapter& ea, GUIActionAdapter& us );

protected:

    void handleMultiTouchDrag(GUIEventAdapter::TouchData* now, GUIEventAdapter::TouchData* last, const double eventTimeDelta);

    osg::ref_ptr<GUIEventAdapter::TouchData> _lastTouchData;
};

}
}

#endif /* OSGGA_MULTITOUCH_TRACKBALL_MANIPULATOR2 */
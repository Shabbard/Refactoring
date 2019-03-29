#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

/*
 * The main complication with this function is that it ignores all the negative differences
 * between successive route points - that is it ignores any decline in its calculation, it only
 * adds together the inclines.
 * 
 * First of all this test suite will check that two specific points return the correct 
 * value. It will also check that if there are two successive points with a decline in 
 * elevation, the function notices this and returns a value of 0 for these two points.
 * 
 * I will also check that 3 or 4 successive points return the correct total height gain, with four tests.
 *      All of the points are incline on previous points
 *      All of points are decline on previous points
 *      There is a net decline between points 
 *      There is a net incline between points
 *
 * 
 * 
 *  For this I will have to generate log files with only two, three or four points.
 *  e.g. Route twoPoints = Route(LogFiles::GPXRoutesDir + "twoPoints.gpx", isFileName);#
 *  USING GRIDWORLD
 *  Gridworld allows for curvature of the earth, then you can choose points for either a track or a route
 * 
 */


// metres TotalHeightGain() const;

BOOST_AUTO_TEST_SUITE( Route_TotalHeightGain )

const bool isFileName = true;

BOOST_AUTO_TEST_CASE ( firstTwoPositions ) {
    
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.TotalHeightGain(), 5 );
    
}




BOOST_AUTO_TEST_SUITE_END()







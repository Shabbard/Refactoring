#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

/*
 * The main complication with this function is that it ignores all the negative differences
 * between successive route points - that is it ignores any decline between two points in its calculation, it only
 * adds together the inclines.
 * 
 * First of all this test suite will check that two specific points return the correct 
 * value. It will also check that if there are two successive points with a decline in 
 * elevation, the function notices this and returns a value of 0 for these two points.
 * 
 * I will also check that 4 successive points return the correct total height gain, with four tests.
 *      All of the points are consecutive inclines in elevation.
 *      All of points are consecutive declines in elevation.
 *      There is a net decline between the points.
 *      There is a net incline between the points.
 * 
 *  For this I will have to generate log files with only two, three or four points.
 * 
 * USING GRIDWORLD
 *  Gridworld allows for curvature of the earth, then you can choose points for either a track or a route
 * 
 */


// metres totalHeightGain() const;

BOOST_AUTO_TEST_SUITE( Route_totalHeightGain )
const bool isFileName = true;

BOOST_AUTO_TEST_CASE ( twoPositionsIncline ) {
    
    Route route = Route(LogFiles::GPXRoutesDir + "twoPositionsIncline.gpx", isFileName);
    // Looking at the two points you can see what the height gain should be
    BOOST_CHECK_EQUAL( route.totalHeightGain(), 5 );
    
}

BOOST_AUTO_TEST_CASE ( twoPositionsDecline ) {
    
    Route route = Route(LogFiles::GPXRoutesDir + "twoPositionsDecline.gpx", isFileName);
    // If there is a decline between two points, the function should return 0
    BOOST_CHECK_EQUAL( route.totalHeightGain(), 0 );
    
}

BOOST_AUTO_TEST_CASE ( fourPositionsConsecutiveIncline ) {
    
    Route route = Route(LogFiles::GPXRoutesDir + "fourPositionsConsecutiveIncline.gpx", isFileName);
    // Looking at the four points you can see what the height gain should be
    BOOST_CHECK_EQUAL( route.totalHeightGain(), 15 );
    
}

BOOST_AUTO_TEST_CASE ( fourPositionsConsecutiveDecline ) {
    
    Route route = Route(LogFiles::GPXRoutesDir + "fourPositionsConsecutiveDecline.gpx", isFileName);
    // As there is four consecutive declines, the total height gain should be 0
    BOOST_CHECK_EQUAL( route.totalHeightGain(), 0 );
    
}

BOOST_AUTO_TEST_CASE ( fourPositionsNetIncline ) {
    
    Route route = Route(LogFiles::GPXRoutesDir + "fourPositionsNetIncline.gpx", isFileName);
    // Looking at the four points you can see what the height gain should be
    BOOST_CHECK_EQUAL( route.totalHeightGain(), 11 );
    
}

BOOST_AUTO_TEST_CASE ( fourPositionsNetDecline ) {
    
    Route route = Route(LogFiles::GPXRoutesDir + "fourPositionsNetDecline.gpx", isFileName);
    
    /* Looking at the four points you can see what the height gain should be.
     * Even though there is a net decline, the inclines should still be 
     * added to the total height gain. */
    
    BOOST_CHECK_EQUAL( route.totalHeightGain(), 3 );
    
}


BOOST_AUTO_TEST_SUITE_END()







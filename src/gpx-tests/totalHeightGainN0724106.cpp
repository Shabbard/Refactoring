#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

/*
 * The main complication with this function is that it ignores all the negative differences
 * between successive route points - that is it ignores any decline between two points in its calculation - it only
 * adds together the inclines.
 * 
 * First of all this test suite will check that two specific points return the correct 
 * value. It will also check that if there are two successive points with a decline in 
 * elevation, the function notices this and returns a value of 0 for these two points.
 * 
 * I will also check that successive points return the correct total height gain, with
 * four tests.
 *      Three points that are consecutive inclines in elevation.
 *      Three points that are consecutive declines in elevation.
 *      Five points with a net incline between all the points.
 *      Five points with a net incline between all the points.
 */


BOOST_AUTO_TEST_SUITE( totalHeightGain_N0724106 )
const bool isFileName = true;

BOOST_AUTO_TEST_CASE ( twoPositionsIncline ) {
    
    Route route = Route(GPS::LogFiles::GPXRoutesDir + "twoPositionsInclineN0724106.gpx", isFileName);
    // Looking at the two points you can see what the height gain should be
    BOOST_CHECK_EQUAL( route.totalHeightGain(), 50 );
    
}

BOOST_AUTO_TEST_CASE ( twoPositionsDecline ) {
    
    Route route = Route(GPS::LogFiles::GPXRoutesDir + "twoPositionsDeclineN0724106.gpx", isFileName);
    // If there is a decline between two points, the function should return 0
    BOOST_CHECK_EQUAL( route.totalHeightGain(), 0 );
    
}

BOOST_AUTO_TEST_CASE ( threePositionsConsecutiveIncline ) {
    
    Route route = Route(GPS::LogFiles::GPXRoutesDir + "threePositionsInclineN0724106.gpx", isFileName);
    // Looking at the three points you can see what the height gain should be
    BOOST_CHECK_EQUAL( route.totalHeightGain(), 100 );
    
}

BOOST_AUTO_TEST_CASE ( threePositionsConsecutiveDecline ) {
    
    Route route = Route(GPS::LogFiles::GPXRoutesDir + "threePositionsDeclineN0724106.gpx", isFileName);
    // As there is three consecutive declines, the total height gain should be 0
    BOOST_CHECK_EQUAL( route.totalHeightGain(), 0 );
    
}

BOOST_AUTO_TEST_CASE ( fivePositionsNetIncline ) {
    
    Route route = Route(GPS::LogFiles::GPXRoutesDir + "fivePositionsNetInclineN0724106.gpx", isFileName);
    // Looking at the five points you can see what the total height gain should be
    BOOST_CHECK_EQUAL( route.totalHeightGain(), 100 );
    
}

// This test checks that if there are inclines followed by declines,
// the declines are NOT subtracted from the total height gain.
BOOST_AUTO_TEST_CASE ( fivePositionsNetDecline ) {
    
    Route route = Route(GPS::LogFiles::GPXRoutesDir + "fivePositionsNetDeclineN0724106.gpx", isFileName);
    
    /* Looking at the four points you can see what the height gain should be.
     * Even though there is a net decline, the inclines should still be 
     * added to the total height gain. */
    
    BOOST_CHECK_EQUAL( route.totalHeightGain(), 50 );
    
}


BOOST_AUTO_TEST_SUITE_END()







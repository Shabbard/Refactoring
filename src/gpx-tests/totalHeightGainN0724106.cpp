#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

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







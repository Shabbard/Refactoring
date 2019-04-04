#include <boost/test/unit_test.hpp>
#include <fstream>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "earth.h"
#include "gridworld.h"
#include "gridworld_route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( minLatitude_N0743587 )


// Checks if points are mapped correctly and latitude is calculated correctly by
// starting on a point that is also the route destination.

BOOST_AUTO_TEST_CASE(SinglePointSigned){

    Route route = Route(LogFiles::GPXRoutesDir + "A.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0.17996400000000001 );

    route = Route(LogFiles::GPXRoutesDir + "Q.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.89981999999999995 );
}


// Checks if latitude will be changed to the lowest point on the route
// through using a route with multiple points

BOOST_AUTO_TEST_CASE(MultiPoint){

    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0.17996400000000001);

    route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 1.7996399999999999 );
}

// Cheks for errors when returning signed latitude
// on a route with multiple points

BOOST_AUTO_TEST_CASE(MultiPointSinged){

    Route route = Route(LogFiles::GPXRoutesDir + "NegativeLatitude-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.017996399999999999);

    route = Route(LogFiles::GPXRoutesDir + "PositiveLatitude-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0.017996399999999999 );
}

// Checks for errors thrown for 0 values in latitude and longitude
// on custom created GPX files

BOOST_AUTO_TEST_CASE(ZeroLatLon){

    Route route = Route(LogFiles::GPXRoutesDir + "ZeroLatitude-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0 );

    route = Route(LogFiles::GPXRoutesDir + "ZeroLongitude-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 90 );

    route = Route(LogFiles::GPXRoutesDir + "ZeroLatLon-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0 );
}


BOOST_AUTO_TEST_CASE(DuplicatePoint){

    Route route = Route(LogFiles::GPXRoutesDir + "DuplicatePointA-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0.017996399999999999);

    route = Route(LogFiles::GPXRoutesDir + "DuplicatePointQ-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.0089981999999999996);
}

BOOST_AUTO_TEST_CASE(PointsMeterApart){

    Route route = Route(LogFiles::GPXRoutesDir + "PointsMeterApart-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0.00017996399999999999 );
}


BOOST_AUTO_TEST_SUITE_END()

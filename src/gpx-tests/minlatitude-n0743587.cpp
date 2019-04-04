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

BOOST_AUTO_TEST_CASE(SinglePointSigned){

    //Checks if points are mapped correctly and latitude is calculated correctly

    Route route = Route(LogFiles::GPXRoutesDir + "A.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0.17996400000000001 );

    route = Route(LogFiles::GPXRoutesDir + "Q.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.89981999999999995 );
}

BOOST_AUTO_TEST_CASE(MultiPoint){

    //Checks if latitude will be changed to the lowest point on the route

    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0.17996400000000001);

    route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 1.7996399999999999 );
}

BOOST_AUTO_TEST_CASE(MultiPointSinged){

    //Cheks for errors when returning signed latitude on a route

    Route route = Route(LogFiles::GPXRoutesDir + "NegativeLatitude-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.017996399999999999);

    route = Route(LogFiles::GPXRoutesDir + "PositiveLatitude-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0.017996399999999999 );
}

BOOST_AUTO_TEST_CASE(ZeroLatLon){

    //Checks for errors thrown for 0 values in latitude and longitude

    Route route = Route(LogFiles::GPXRoutesDir + "ZeroLatitude-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0 );

    route = Route(LogFiles::GPXRoutesDir + "ZeroLongitude-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 90 );

    route = Route(LogFiles::GPXRoutesDir + "ZeroLatLon-N0743587.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0 );
}


BOOST_AUTO_TEST_CASE(InvalidFile){
//Throws exception
    //Route route = Route(LogFiles::GPXRoutesDir + "invalid.gpx", true);
    //BOOST_CHECK_EQUAL( route.minLatitude(), 5 );

    //route = Route(LogFiles::GPXRoutesDir + "invalid", true);
    //BOOST_CHECK_EQUAL( route.minLatitude(), 6 );
}

BOOST_AUTO_TEST_CASE(NullCase){
//Throws IOException
    //Route route = Route(LogFiles::GPXRoutesDir + "NullPosition-N0743587.gpx", true);
    //BOOST_CHECK_EQUAL( route.minLatitude(), false);
}


BOOST_AUTO_TEST_SUITE_END()

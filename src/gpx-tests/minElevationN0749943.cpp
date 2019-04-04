#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(minElevationN0749943)

const bool isFileName = true;

//Ensure that minElevation returns the correct result for a regular route.
BOOST_AUTO_TEST_CASE( RegularRoute )
{
    Route testRoute = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
    BOOST_CHECK_EQUAL(testRoute.minElevation(), 135);
}

//Ensure that minElevation returns the correct result with only one position.
BOOST_AUTO_TEST_CASE( SingleValue )
{
   Route testRoute = Route(LogFiles::GPXRoutesDir + "SingleValueN0749943.gpx", isFileName);
   BOOST_CHECK_EQUAL(testRoute.minElevation(), 5);
}

//Ensure that minElevation returns the correct result with 100 positions.
//BOOST_AUTO_TEST_CASE( OneHundredValues )
//{
//   Route testRoute = Route(LogFiles::GPXRoutesDir + "A.gpx", isFileName);
//   BOOST_CHECK_EQUAL(testRoute.minElevation(), 1);
//}

//Ensure that minElevation returns the correct value for routes with at least one position with a negative elevation.
BOOST_AUTO_TEST_CASE( NegativeElevation )
{
    Route testRoute = Route(LogFiles::GPXRoutesDir + "NegativeElevationN0749943.gpx", isFileName);
    BOOST_CHECK_EQUAL(testRoute.minElevation(), -3);
}

//Ensure that the minElevation is 0 when all positions have an elevation of 0.
BOOST_AUTO_TEST_CASE( AllValuesZero )
{
   Route testRoute = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_EQUAL(testRoute.minElevation(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

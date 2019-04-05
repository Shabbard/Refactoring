#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(minElevationN0749943)

const bool isFileName = true;

//Ensure that minElevation returns the correct result for typical valid routes.
BOOST_AUTO_TEST_CASE( TypicalRoute )
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

//Ensure that minElevation returns the correct result with only two positions.
BOOST_AUTO_TEST_CASE( TwoValues )
{
   Route testRoute = Route(LogFiles::GPXRoutesDir + "TwoValuesN0749943.gpx", isFileName);
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

//Ensure that minElevation returns the correct value where elevation values differ by hundreds of units.
BOOST_AUTO_TEST_CASE( HundredDifference )
{
    Route testRoute = Route(LogFiles::GPXRoutesDir + "HundredDifferenceN0749943.gpx", isFileName);
    BOOST_CHECK_EQUAL(testRoute.minElevation(), 100);
}

//Ensure that minElevation returns the correct value where elevation values differ by thousands of units.
BOOST_AUTO_TEST_CASE( ThousandDifference )
{
    Route testRoute = Route(LogFiles::GPXRoutesDir + "ThousandDifferenceN0749943.gpx", isFileName);
    BOOST_CHECK_EQUAL(testRoute.minElevation(), 3421);
}

//Ensure that minElevation returns the correct value where elvations values differ by tenths of a unit.
BOOST_AUTO_TEST_CASE( OneDecimalPlaceDifference )
{
    Route testRoute = Route(LogFiles::GPXRoutesDir + "OneDecimalDifferenceN0749943.gpx", isFileName);
    BOOST_CHECK_EQUAL(testRoute.minElevation(), 0.1);
}

//Ensure that minElevation returns the correct value where elvations values differ by hundreths of a unit.
BOOST_AUTO_TEST_CASE( TwoDecimalPlaceDifference )
{
    Route testRoute = Route(LogFiles::GPXRoutesDir + "TwoDecimalDifferenceN0749943.gpx", isFileName);
    BOOST_CHECK_EQUAL(testRoute.minElevation(), 0.18);
}

//Ensure that the minElevation is 0 when all positions have an elevation of 0.
BOOST_AUTO_TEST_CASE( AllValuesZero )
{
   Route testRoute = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_EQUAL(testRoute.minElevation(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

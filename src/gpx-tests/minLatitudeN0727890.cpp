#include <boost/test/unit_test.hpp>
#include <string>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

/**
 * Utility function meant to return the path of the respective
 * test files
 */
const std::string get_full_path(const std::string route_name) 
{
    const std::string full_path = LogFiles::GPXRoutesDir + route_name + ".gpx";

    return full_path;
}

const degrees get_min_latitude(const std::string path) {
    Route route(get_full_path(path), true);

    return route.minLatitude();
}

BOOST_AUTO_TEST_SUITE( Route_minLatitude_N0727890 )

const double accuracy = 0.0001;

/**
 * Make sure the function works correctly for single-position routes 
 */
BOOST_AUTO_TEST_CASE( RouteWithOnePositionShouldReturnItsLatitude ) 
{
    const degrees expected_latitude = -48.0513;
    BOOST_CHECK_CLOSE( get_min_latitude("Q"), expected_latitude, accuracy);
}

/**
 * Make sure the function only returns one value, even if there are multiple
 * positions having the same minimum latitude
 */
BOOST_AUTO_TEST_CASE( RouteWithMultipleMinimumLatitudesShouldReturnOneValue ) 
{
    const degrees expected_latitude = -48.0513;

    BOOST_CHECK_CLOSE( get_min_latitude("QQQQ"), expected_latitude, accuracy);
}

/**
 * Make sure the function returns the good minimum latitude for long routes with
 * very close latitudes
 */
BOOST_AUTO_TEST_CASE( RouteWithAllThePositionsOnTheGrid )
{
    const degrees expected_latitude = -48.1413;

    BOOST_CHECK_CLOSE( get_min_latitude("ABCDEFGHIJKLMNOPQRSTUVWXY"), expected_latitude, accuracy);
}

/**
 * Routes consisting of points of the same latitude should only return
 * the latitude of one of them
 */
BOOST_AUTO_TEST_CASE( RouteWithinCityCampus ) 
{
    const degrees expected_latitude = 20.9911;

    BOOST_CHECK_CLOSE( get_min_latitude("ABCDE"), expected_latitude, accuracy );
}

/**
 * Any route along the Equatorial meridian should have the latitude 0 
 */
BOOST_AUTO_TEST_CASE( RouteAlongEquatorialMeridian )
{
    const degrees expected_latitude = 0.0;
    BOOST_CHECK_CLOSE( get_min_latitude("AMYEU"), expected_latitude, accuracy );
}

BOOST_AUTO_TEST_SUITE_END()
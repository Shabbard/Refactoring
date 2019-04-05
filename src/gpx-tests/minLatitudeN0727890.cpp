#include <boost/test/unit_test.hpp>
#include <string>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_minLatitude_N0727890 )

const double accuracy = 0.00001;

BOOST_AUTO_TEST_CASE( EmptyRouteShouldThrowAnException ) 
{
    const std::string full_path = LogFiles::GPXRoutesDir + ".gpx";
    Route route(full_path, true);

    BOOST_CHECK_THROW(route.minLatitude(), std::exception);
}

BOOST_AUTO_TEST_CASE( RouteWithOnePositionShouldReturnItsLatitude ) 
{
    const degrees actual_latitude = -53.2683;
    const std::string full_path = LogFiles::GPXRoutesDir + "A.gpx";
    Route route (full_path, true);

    BOOST_CHECK_CLOSE( route.minLatitude(), actual_latitude, accuracy);
}

BOOST_AUTO_TEST_CASE( RouteWithMultipleMinimumLatitudesShouldReturnOneValue ) 
{
    const degrees actual_latitude = 67.6163;
    const std::string full_path = LogFiles::GPXRoutesDir + "AAA.gpx";
    Route route(full_path, true);

    BOOST_CHECK_CLOSE( route.minLatitude(), actual_latitude, accuracy);
}

BOOST_AUTO_TEST_CASE( RouteWithAllThePositionsOnTheGrid )
{
    const degrees actual_latitude = -89.7546;
    const std::string full_path = LogFiles::GPXRoutesDir + "ABCDEFGHIJKLMNOPQRSTUVWXY.gpx";
    Route route(full_path, true);

    BOOST_CHECK_CLOSE( route.minLatitude(), actual_latitude, accuracy);
}

BOOST_AUTO_TEST_CASE( RouteAlongTheSameLatitude ) 
{
    const degrees acual_latitude = 50.3232;
    const std::string full_path = LogFiles::GPXRoutesDir + "ABCDE.gpx";
    Route route(full_path, true);

    BOOST_CHECK_CLOSE( route.minLatitude(), acual_latitude, accuracy );
}

BOOST_AUTO_TEST_SUITE_END()
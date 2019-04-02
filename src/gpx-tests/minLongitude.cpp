#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_minLongitude )

const bool isFileName = true;

// Edge case for shortest route
BOOST_AUTO_TEST_CASE( shortest_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.minLongitude(), -0.898312, 0.0001 );
}

// Edge case for longest route
BOOST_AUTO_TEST_CASE( longest_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.minLongitude(), -1.120702028274536, 0.00000000000001 );
}

// Test returns correct longitude when all values for longitude on a route are the same
BOOST_AUTO_TEST_CASE( no_change_in_longitude )
{
    Route route = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", isFileName);
    BOOST_CHECK_CLOSE( route.minLongitude(), -1.79662, 0.0001 );
}

// Testing a small route as I can easily check when opening the .gpx file in a text
// editor what the minimum logitude is, and what the function should return
BOOST_AUTO_TEST_CASE( small_route_test )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
    BOOST_CHECK_CLOSE( route.minLongitude(), -1.79662, 0.0001 );
}


// Testing my own route from Nottingham to Stoke On Trent
BOOST_AUTO_TEST_CASE( nottingham_to_stoke_test )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Nottingham-Stoke.gpx", isFileName);
    BOOST_CHECK_CLOSE( route.minLongitude(), -2.1876320, 0.000001 );
}

// Testing my own route from Liverpool to Runcorn
BOOST_AUTO_TEST_CASE( liverpool_to_runcorn_test )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Liverpool-Runcorn.gpx", isFileName);
    // -2.9779210
    BOOST_CHECK_CLOSE( route.minLongitude(), -2.9779210, 0.000001 );
}

BOOST_AUTO_TEST_SUITE_END()

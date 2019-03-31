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
   BOOST_CHECK_EQUAL( route.minLongitude(), -0.898312 );
}

// Edge case for longest route
BOOST_AUTO_TEST_CASE( longest_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLongitude(), -1.1207020282745359 );
}

// Test returns correct longitude when all values for longitude on a route are the same
BOOST_AUTO_TEST_CASE( no_change_in_longitude )
{
    Route route = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.minLongitude(), -1.79662 );
}


BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_netLength )

const bool isFileName = true;
/*
 *This part of the test case checks the netlenght of the route with a change of direction in the
 *route along the gridlock
 */
//Check if function is able to determine netLength of ABBM.gpx
BOOST_AUTO_TEST_CASE( Route_ABBM )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABBM.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netLength(), 38.0 );
}
/*
 *This part checks the route length of a direct route without any chages to the direction
*/
//Check if function is able to determine netLength of ABCD.gpx
BOOST_AUTO_TEST_CASE( Route_ABCD )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netLength(), 30.0 );
}

/*
 *This part checks the route length of a route thats made up of stationay points
 *the route shows no change therefore the length should remain stationary being zero
*/
//Check if function is able to determine netLength of RouteStationaryPoints.gpx
BOOST_AUTO_TEST_CASE( Route_RouteStationaryPoints )
{
    Route route = Route(LogFiles::GPXRoutesDir + "StationaryPoints.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netLength(), 0.0 );
}

/*
 *This part checks the route length against a single point on the route as shown by the gpx file
 *Being a single point the length should not change.
*/
//Check if function is able to determine netLength of RouteSinglePosition.gpx
BOOST_AUTO_TEST_CASE( Route_SinglePosition )
{
    Route route = Route(LogFiles::GPXRoutesDir + "SinglePosition.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netLength(), 0.0 );
}

/*
 *This part checks the route length with a change in elevation and change in direction
 *This is a complex route and determines whether the function can determine the length
 *of the route with this variations
*/
//Check if function is able to determine netLength of Everest.gpx
BOOST_AUTO_TEST_CASE( Route_MountEverest )
{
    Route route = Route(LogFiles::GPXRoutesDir + "MountEverest.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netLength(), 141.1 );
}


/*
 *This part checks the route length of the route edge with an elevation. The outcome should be similar to that of
 *a single point route.
*/
//Check if function is able to determine netLength of Edge.gpx
BOOST_AUTO_TEST_CASE( Route_AtoG )
{
    Route route = Route(LogFiles::GPXRoutesDir + "AtoG.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netLength(), 0.0 );
}

BOOST_AUTO_TEST_SUITE_END()


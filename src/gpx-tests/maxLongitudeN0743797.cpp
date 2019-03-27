#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_maxLongitude_N0743797 )

const bool isFileName = true;

// The longitude of the most Easterly point on the Route.

/* The maxLongitude function is used to return the most easternly
 * value included in a given Route. 
 * Multiple points with the same maximum in the route should also be tested.
 * Then real values can be tested to make sure the correct maximum
 * longitude is returned.
 * And finally the function can be tested to see if the correct
 * value is returned if no easterly values are present in the route. 
 */

BOOST_AUTO_TEST_CASE( correctEasterlyValue )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 1.79662 );
}

BOOST_AUTO_TEST_CASE( sameMostEasterlyValues )
{
   Route route = Route(LogFiles::GPXRoutesDir + "sameMaximumEasterly.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), NULL );
}

BOOST_AUTO_TEST_CASE( noEasterlyValues )
{
   Route route = Route(LogFiles::GPXRoutesDir + "logitudeAbsent.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), NULL );
}

BOOST_AUTO_TEST_SUITE_END()

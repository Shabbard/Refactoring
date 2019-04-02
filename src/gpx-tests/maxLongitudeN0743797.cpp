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
 *
 * This function is very simple, it should
 * go through each point in the route, selecting the first easterly point
 * in the route as the maximum and then comparing each other easterly value
 * in the route to check if it is greater than the first point. If it is
 * larger then the maximum can be replaced. This function should loop through
 * each point in the route; doing the comparison just explained, then the
 * largest easterly value will be found and can be returned.
 *
 *
 * The first obvious test is to test real values to make sure the correct
 * maximum longitude is returned.
 *
 * The function should also make sure it accounts for signed numbers,
 * and so will be tested with negative numbers that use a high value
 * compared to postive ints with smaller values. Also signed purely negative
 * numbers should be tested too.
 *
 * Signed numbers at the edge case of 0 should also be tested
 * -0 and 0.
 *
 */

BOOST_AUTO_TEST_CASE( correctEasterlyValue )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 1.79662 );
}

BOOST_AUTO_TEST_CASE( signedMixedEasterlyValues )
{
   Route route = Route(LogFiles::GPXRoutesDir + "longitudeSigned-N0743797.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 1.12345);
}

BOOST_AUTO_TEST_CASE( signedNegativeEasterlyValues )
{
   Route route = Route(LogFiles::GPXRoutesDir + "longitudeNegative-N0743797.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 1.12345);
}


BOOST_AUTO_TEST_SUITE_END()

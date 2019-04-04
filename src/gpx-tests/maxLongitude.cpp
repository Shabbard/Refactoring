//Cameron Bowes (N0729418) - maxLongitude.cpp tests

#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

const bool isFileName = true;

BOOST_AUTO_TEST_SUITE( Route_maxLongitude_n0729418 )

// Tries whether the function can tell the difference between signed numbers
BOOST_AUTO_TEST_CASE(signed_valuie)
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0729418-signedValue.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 1.12354);
}

// Checks the function can find the most positive longitude from all negative numbers.
BOOST_AUTO_TEST_CASE(negative)
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0729418-negative.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -1.142);
}
// Checks that the function does not use rounding by using longitudes decimals places.
BOOST_AUTO_TEST_CASE(minor_difference)
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0729418-minorchange.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -1.1999999999988);
}

// To try a single point route, makes sure that the function only returns one value in the route.
BOOST_AUTO_TEST_CASE(one_value)
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0729418-oneValue.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -0.291245);
}

// Tries a route with points all having the same longitude.
BOOST_AUTO_TEST_CASE(duplicate)
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0729418-duplicate.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -0.291245);
}

BOOST_AUTO_TEST_SUITE_END()

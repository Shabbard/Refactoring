#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(Route_timesVisitedByName)

const bool isFileName = true;
const metres units = 10000;
Route route = Route(LogFiles::GPXRoutesDir + "n0753746-TimesVisitedByName.gpx", isFileName);

// Check the whole route with no errors
BOOST_AUTO_TEST_CASE(noErrors)
{
    BOOST_CHECK_EQUAL(route.timesVisited("I"), 1);
    BOOST_CHECK_EQUAL(route.timesVisited("R"), 3);
    BOOST_CHECK_EQUAL(route.timesVisited("O"), 2);
}

// Check invalid point name
BOOST_AUTO_TEST_CASE(invalidName)
{
    BOOST_CHECK_EQUAL(route.timesVisited("P"), 0);
    BOOST_CHECK_EQUAL(route.timesVisited("M"), 0);
    BOOST_CHECK_EQUAL(route.timesVisited("D"), 0);
}

// Check case sensitive
BOOST_AUTO_TEST_CASE(caseSensitive)
{
    BOOST_CHECK_EQUAL(route.timesVisited("R"), 3);
    BOOST_CHECK_EQUAL(route.timesVisited("O"), 2);
    BOOST_CHECK_EQUAL(route.timesVisited("s"), 0);
    BOOST_CHECK_EQUAL(route.timesVisited("i"), 0);
    BOOST_CHECK_EQUAL(route.timesVisited("T"), 1);
}

// Check null parameter provided
BOOST_AUTO_TEST_CASE(nullParam)
{
    BOOST_CHECK_EQUAL(route.timesVisited(""), 0);
}

// Check for weird characters
BOOST_AUTO_TEST_CASE(illegalInput)
{
    BOOST_CHECK_EQUAL( route.timesVisited("/"), 0 );
    BOOST_CHECK_EQUAL( route.timesVisited(".^"), 0 );
    BOOST_CHECK_EQUAL( route.timesVisited("?\""), 0 );
}

BOOST_AUTO_TEST_SUITE_END()

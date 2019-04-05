#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;


BOOST_AUTO_TEST_SUITE( Route_timesVisited )

const bool isFileName = true;
const metres horizontalGridUnit = 10000;

// Check the simplest shortest possible route
BOOST_AUTO_TEST_CASE( singletonRoute )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0763258-W.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.timesVisited("W"), 1 );
}

// Testing the function with an empty parameter
BOOST_AUTO_TEST_CASE( emptyString )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0763258-ABCDEABCDA.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.timesVisited(""), 0 );
}

// Check the results for illegal inputs
BOOST_AUTO_TEST_CASE( illegalInputs )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0763258-ABCDEABCDA.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.timesVisited("{}"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("/*."), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited(".$&"), 0 );
}

// Check the results for non existing points
BOOST_AUTO_TEST_CASE( nonExistingPoints )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0763258-ABCDEABCDA.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.timesVisited("F"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("Q"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("W"), 0 );
}

// Testing position names case sensitivity
BOOST_AUTO_TEST_CASE( caseSensitivity )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0763258-ABCDEABCDA.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.timesVisited("A"), 3 );
   BOOST_CHECK_EQUAL( route.timesVisited("b"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("C"), 2 );
   BOOST_CHECK_EQUAL( route.timesVisited("d"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("e"), 0 );
}

// Testing the number of visits with longer routes
BOOST_AUTO_TEST_CASE( longerRoute )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0763258-LongRoute.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.timesVisited("A"), 14 );
   BOOST_CHECK_EQUAL( route.timesVisited("E"), 14 );
   BOOST_CHECK_EQUAL( route.timesVisited("I"), 14 );
   BOOST_CHECK_EQUAL( route.timesVisited("J"), 14 );
}

// Check how many times a position has been visited if all positions are more than granularity apart
BOOST_AUTO_TEST_CASE( moreThanGranularityApart )
{
   const metres granularity = horizontalGridUnit / 5;
   Route route = Route(LogFiles::GPXRoutesDir + "N0763258-ABCDEABCDA.gpx", isFileName, granularity);
   BOOST_CHECK_EQUAL( route.timesVisited("A"), 3 );
   BOOST_CHECK_EQUAL( route.timesVisited("B"), 2 );
   BOOST_CHECK_EQUAL( route.timesVisited("C"), 2 );
   BOOST_CHECK_EQUAL( route.timesVisited("D"), 2 );
   BOOST_CHECK_EQUAL( route.timesVisited("E"), 1 );
}

// Checking the number of visits when some, but not all, points are too close to each other
BOOST_AUTO_TEST_CASE( somePointsMoreThanGranularityApart )
{
   const metres granularity = horizontalGridUnit * 1.5;
   Route route = Route(LogFiles::GPXRoutesDir + "N0763258-CDEPQR.gpx", isFileName, granularity);
   BOOST_CHECK_EQUAL( route.timesVisited("C"), 1 );
   BOOST_CHECK_EQUAL( route.timesVisited("D"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("E"), 1 );
   BOOST_CHECK_EQUAL( route.timesVisited("P"), 1 );
   BOOST_CHECK_EQUAL( route.timesVisited("Q"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("R"), 1 );
}

// Checking the number of visits when all points have a too close neighbour, 
// but not all points are too close to each other
BOOST_AUTO_TEST_CASE( allPointsHaveTooCloseNeighbours )
{
   const metres granularity = horizontalGridUnit * 1.5;
   Route route = Route(LogFiles::GPXRoutesDir + "N0763258-ABCDEABCDA.gpx", isFileName, granularity);
   BOOST_CHECK_EQUAL( route.timesVisited("A"), 3 );
   BOOST_CHECK_EQUAL( route.timesVisited("B"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("C"), 2 );
   BOOST_CHECK_EQUAL( route.timesVisited("D"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("E"), 1 );
}

// Check how many times a position has been visited if all positions are too close
BOOST_AUTO_TEST_CASE( allPointsWithinGranularity )
{
   const metres granularity = horizontalGridUnit * 6;
   Route route = Route(LogFiles::GPXRoutesDir + "N0763258-CHMRWC.gpx", isFileName, granularity);
   BOOST_CHECK_EQUAL( route.timesVisited("C"), 1 );
   BOOST_CHECK_EQUAL( route.timesVisited("H"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("M"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("R"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("W"), 0 );
}

// Checking the number of visits when positions are just beyond granularity of each other
BOOST_AUTO_TEST_CASE( pointsSlightlyMoreThanGranularity )
{
   const metres granularity = horizontalGridUnit * 0.99;
   Route route = Route(LogFiles::GPXRoutesDir + "N0763258-ABCDEABCDA.gpx", isFileName, granularity);
   BOOST_CHECK_EQUAL( route.timesVisited("A"), 3 );
   BOOST_CHECK_EQUAL( route.timesVisited("B"), 2 );
   BOOST_CHECK_EQUAL( route.timesVisited("C"), 2 );
   BOOST_CHECK_EQUAL( route.timesVisited("D"), 2 );
   BOOST_CHECK_EQUAL( route.timesVisited("E"), 1 );
}

// Checking the number of visits when positions are slightly less than granularity apart
BOOST_AUTO_TEST_CASE( pointsSlightlyLessThanGranularity )
{
   const metres granularity = horizontalGridUnit * 1.01;
   Route route = Route(LogFiles::GPXRoutesDir + "N0763258-ABCDEABCDA.gpx", isFileName, granularity);
   BOOST_CHECK_EQUAL( route.timesVisited("A"), 3 );
   BOOST_CHECK_EQUAL( route.timesVisited("B"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("C"), 2 );
   BOOST_CHECK_EQUAL( route.timesVisited("D"), 0 );
   BOOST_CHECK_EQUAL( route.timesVisited("E"), 1 );
}

BOOST_AUTO_TEST_SUITE_END()

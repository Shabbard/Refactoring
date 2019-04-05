#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include <iostream>
#include <fstream>

using namespace GPS;

BOOST_AUTO_TEST_SUITE(N0751891_minElevation)

const bool isFileName = true;

//Check for minElevation correctness in provided log files
BOOST_AUTO_TEST_CASE( PremadeRoutes )
{
   Route routeABCD = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_CLOSE(routeABCD.minElevation(), 0.0, 0.1 ); //All zero values
   Route routeABQWE = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
   BOOST_CHECK_CLOSE(routeABQWE.minElevation(), -40000.0, 0.1 ); // 0 Lattitude
   Route routeAFKPU = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", isFileName);
   BOOST_CHECK_CLOSE(routeAFKPU.minElevation(), -40000.0, 0.1 ); // 0 Longitude
   Route routeNYM = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_CLOSE(routeNYM.minElevation(), 135, 0.1 ); // Big dataset
   Route routeQ = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   BOOST_CHECK_CLOSE(routeQ.minElevation(), -20000.0, 0.1 ); // Large value with negative LongLat
}

//Check for minElevation when values are ascending
BOOST_AUTO_TEST_CASE( AscendingElevationRoutes )
{
    Route routeGA = Route(LogFiles::GPXRoutesDir + "N0751891-Ascending-Positive.gpx", isFileName);
    BOOST_CHECK_CLOSE( routeGA.minElevation(), 558.0, 0.1 ); // All positive values
    Route routeBHINM = Route(LogFiles::GPXRoutesDir + "N0751891-Ascending-Negative.gpx", isFileName);
    BOOST_CHECK_CLOSE( routeBHINM.minElevation(), -942.0, 0.1 ); //All negative values
}


//Check for minElevation when values are repeated on flat elevation
BOOST_AUTO_TEST_CASE( FlatElevationRoutes )
{
    Route routeKLM = Route(LogFiles::GPXRoutesDir + "N0751891-Flat-Positive.gpx", isFileName);
    BOOST_CHECK_CLOSE( routeKLM.minElevation(), 1058.0, 0.1 ); // All positive values
    Route routeTSR = Route(LogFiles::GPXRoutesDir + "N0751891-Flat-Negative.gpx", isFileName);
    BOOST_CHECK_CLOSE( routeTSR.minElevation(), -942.0, 0.1 ); //All negative values
}


//Check for minElevation when values are descending
BOOST_AUTO_TEST_CASE( DescendingElevationRoutes )
{
    Route routeIE = Route(LogFiles::GPXRoutesDir + "N0751891-Descending-Positive.gpx", isFileName);
    BOOST_CHECK_CLOSE( routeIE.minElevation(), 558.0, 0.1 ); // All positive values
    Route routeQU = Route(LogFiles::GPXRoutesDir + "N0751891-Descending-Negative.gpx", isFileName);
    BOOST_CHECK_CLOSE( routeQU.minElevation(), -942.0, 0.1 ); //All negative values
}


//Check for minElevation when values are positive & negative
BOOST_AUTO_TEST_CASE( PositiveNegativeRoute )
{
    Route routeIE = Route(LogFiles::GPXRoutesDir + "N0751891-Positive-Negative.gpx", isFileName);
    BOOST_CHECK_CLOSE( routeIE.minElevation(), -942.0, 0.1 ); // Both positive & negative values
}


//Check for minElevation when expected values are 0
BOOST_AUTO_TEST_CASE( ZeroValueRoutes )
{
    Route routeFGH = Route(LogFiles::GPXRoutesDir + "N0751891-Value-Zero.gpx", isFileName);
    BOOST_CHECK_CLOSE( routeFGH.minElevation(), 0, 0.1 );
}


//Check for minElevation with a large dataset
BOOST_AUTO_TEST_CASE( LargeDatasetRoute )
{
    Route routeNYM = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
    BOOST_CHECK_CLOSE(routeNYM.minElevation(), 135, 0.1 ); // Large dataset
}


//Check for minElevation with large values
BOOST_AUTO_TEST_CASE( LargeValueRoutes )
{
    Route routeAINM = Route(LogFiles::GPXRoutesDir + "N0751891-Large-Negative.gpx", isFileName);
    BOOST_CHECK_CLOSE(routeAINM.minElevation(), -20000.0, 0.1 );
    Route routeEFGH = Route(LogFiles::GPXRoutesDir + "N0751891-Large-Positive.gpx", isFileName);
    BOOST_CHECK_CLOSE(routeEFGH.minElevation(), 10000.0, 0.1 );
}

BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>

#include <fstream>
#include <stdexcept>
#include "logs.h"
#include "route.h"
#include "track.h"
#include "gridworld_route.h"
#include "xmlgenerator.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_Find_Position_N0724629 )

const bool isFileName = true;

/**
* Test case: CanGetLatitude
* Use:       Checks that it is possible to obtain a value for latitude in a GPX log file.
*/
BOOST_AUTO_TEST_CASE( CanGetLatitude )
{
   	Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("Q").latitude(), Position(-0.89982, -0.898312).latitude() );
}

/**
* Test case: CanGetLongitude
* Use:       Checks that it is possible to obtain a value for longitude in a GPX log file.
*/
BOOST_AUTO_TEST_CASE( CanGetLongitude )
{
   	Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("Q").longitude(), Position(-0.89982, -0.898312).longitude() );
}

/**
* Test case: CanGetElevation
* Use:       Checks that it is possible to obtain a value for elevation in a GPX log file.
*/
BOOST_AUTO_TEST_CASE( CanGetElevation )
{
   	Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("Q").elevation(), Position(-0.89982, -0.898312, -20000).elevation() );
}

/**
* Test case: ThrowsOutOfRangeIfNameNotFound
* Use:       Checks that the std::out_of_range exception is thrown if the specified name is not found.
*/
BOOST_AUTO_TEST_CASE ( ThrowsOutOfRangeIfNameNotFound )
{
	// Generate a GPX log file for the with default GridWorld constructor
    GridWorldRoute routeLog = GridWorldRoute("FIWA", GridWorld());

    // Converts the GridWorldRoute in to GPX format
    std::string routeGPX = routeLog.toGPX(true, "ThrowsOutOfRangeIfNameNotFound");

    std::string fileName = "ThrowsOutOfRangeIfNameNotFound-N0724629.gpx";

    std::ofstream openedFile(LogFiles::GPXRoutesDir + fileName);
    openedFile << routeGPX;
    openedFile.close();

    Route route = Route(LogFiles::GPXRoutesDir + fileName, isFileName);
   	BOOST_CHECK_THROW( route.findPosition("K").elevation(), std::out_of_range );
}

BOOST_AUTO_TEST_SUITE_END()

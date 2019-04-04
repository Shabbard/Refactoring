#include <boost/test/unit_test.hpp>

#include <fstream>
#include "logs.h"
#include "route.h"
#include "earth.h"
#include "gridworld_route.h"

using namespace GPS:

std::string createLog(std::string testName, GridWorldRoute routeInfo)
{
	// Function generates a GPX log gile using GridWorldRoute

	std::string fileName = testName + "-N0756079.gpx";
	std::ofstream openFile(LogFiles::GPXRoutesDir + fileName);
	openFile << routeData.toGPX(true, fileName);
	openFile.close();

	return fileName;	
}

BOOST_AUTO_TEST_SUITE(Route_maxLatitude_N0756079)

// Test checks that the function works on a route consisting of only one point.

BOOST_AUTO_TEST_CASE(Single_Point_Route)
{
	Route route = Route(LogFiles::GPXRoutesDir + "A.gpx", true);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 0.17996400000000001 );
}

BOOST_AUTO_TEST_SUITE_END()
// N0679817 - Tomas Blundell - netHeightGain() Boost test // 

#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "types.h"
#include "gridworld_route.h"
#include "xmlgenerator.h"

#include <fstream>

using namespace GPS;

// Will generate a GPX log file, name and location 
std::string generateTheLogs(std::string testName, GridWorldRoute route)
{

	//Creates a name based on the test name and appends my N number and .gpx onto it
	std::string name = testName + "-N0679817.gpx";
	std::ofstream fileOutput(LogFiles::GPXRoutesDir + name);
	fileOutput << route.toGPX(true, testName);
	fileOutput.close();

	return name;

}

/////////////////////////////////////////////
/////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Route_netHeightGain )

const bool isFileName = true;

// Checks that a negative/0 NetGain returns a zero.
BOOST_AUTO_TEST_CASE( checkNegativeNetGain )
{

	GridWorldRoute routeLog = GridWorldRoute("SM");
	Route route = Route(LogFiles::GPXRoutesDir + generateTheLogs("negativeNetGain", routeLog), isFileName);
	BOOST_CHECK_EQUAL( route.netHeightGain(), 0 );

}

// Checks that a single point route returns 0.
BOOST_AUTO_TEST_CASE( checkSinglePointRoute )
{

        GridWorldRoute routeLog = GridWorldRoute("A");
        Route route = Route(LogFiles::GPXRoutesDir + generateTheLogs("singlePointRoute", routeLog), isFileName);
        BOOST_CHECK_EQUAL( route.netHeightGain(), 0 );

}

// Checks that a Circluar route still returns a 0.
BOOST_AUTO_TEST_CASE( checkCircleRoute )
{

        GridWorldRoute routeLog = GridWorldRoute("ACMKA");
        Route route = Route(LogFiles::GPXRoutesDir + generateTheLogs("circleRoute", routeLog), isFileName);
        BOOST_CHECK_EQUAL( route.netHeightGain(), 0 );

}

// Checks that a longer route with negative net gain still returns 0.
BOOST_AUTO_TEST_CASE( checkLongNegativeNetGain )
{

        GridWorldRoute routeLog = GridWorldRoute("MGACEOYXUQ");
        Route route = Route(LogFiles::GPXRoutesDir + generateTheLogs("longNegativeNetGain", routeLog), isFileName);
        BOOST_CHECK_EQUAL( route.netHeightGain(), 0 );

}

// Checks that a longer route with positive net gain still works.
BOOST_AUTO_TEST_CASE( checkLongPositiveNetGain )
{

        GridWorldRoute routeLog = GridWorldRoute("ACEOYWUKLM");
        Route route = Route(LogFiles::GPXRoutesDir + generateTheLogs("longPositiveNetGain", routeLog), isFileName);
        BOOST_CHECK_EQUAL( route.netHeightGain(), 0 );

}

BOOST_AUTO_TEST_SUITE_END()


#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "types.h"
#include "earth.h"
#include "gridworld.h"
#include "gridworld_route.h"
#include "xmlgenerator.h"
#include <fstream>

using namespace GPS;

const std::string studentId("N0675532");
const metres grid_horizontal = 10000;
const metres grid_vertical = 100;

/*std::string createLogFile(std::string, GridWorldRoute route)//function to create a log file for each test
{
	std::string name = "hello";//the name of the file will be the name of the test, and my student ID will be added onto the end e.g. "isHeightNegativeN0675532"
	std::ofstream fileOutput(GPS::LogFiles::GPXRoutesDir + name);
	fileOutput << route.toGPX(true, "hello");
	fileOutput.close();

	return name;
}
*/

/* A B C D E
 * F G H I J
 * K L M N O
 * P Q R S T
 * U V W X Y
 */

//Max Hughes - N0675532
/*The netHeightGain function calculatesthe net gain of the height over a route.
*
*This is diffirent to toal height gain as net will produce the increase from the start point to the end point, 
*as opposed to total which will add all of the increases over a route together
*
*If the net height gain is nagative i.e. the end point is lower than the start then it will be disregarded
*/

BOOST_AUTO_TEST_SUITE( Route_netHeightGain )

const bool isFileName = true;

/*
*Test name: throwsOutOfRangeIfNetHeightGainNotFound
*Test: Checks that an out of range exception is thrown if netHeightGain is not found
*Type: Invalid
*/

BOOST_AUTO_TEST_CASE( throwsOutOfRangeIfNetHeightGainNotFound )
{
	Route route = Route(LogFiles::GPXRoutesDir + "throwsOutOfRangeIfNetHeightGainNotFound-N0724629.gpx", isFileName);
    BOOST_CHECK_THROW( route.netHeightGain(), std::out_of_range );
    
    
}

/*
*Test name: isNetHeightNegative
*Test: Checks that 0 will be returned if the netHeightGain is negative
*Type: Valid
*/

BOOST_AUTO_TEST_CASE( isNetHeightNegative )
{
	GridWorld space(Earth::NorthPole, grid_horizontal, grid_vertical);
    GridWorldRoute routeLog = GridWorldRoute("MR", space);
	Route route = Route(LogFiles::GPXRoutesDir + "isHeightNegative-N0675532.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netHeightGain(), 0);
}

/*
*Test name; isSingleRouteZero
*Test: checks that a route with only one point returns 0, as there can be no height gain from a single point
*Type: Valid
*/

BOOST_AUTO_TEST_CASE( isSingleRouteZero )
{
		GridWorld space(Earth::NorthPole, grid_horizontal, grid_vertical);
        GridWorldRoute routeLog = GridWorldRoute("M", space);
        Route route = Route(LogFiles::GPXRoutesDir + "singleRouteZero-N0675532.gpx", isFileName);
        BOOST_CHECK_EQUAL( route.netHeightGain(), 0 );
}

/*
*Test name; isShortRoutePositive
*Test: checks that a short route will return a postive value
*Type: Valid
*/

BOOST_AUTO_TEST_CASE( isShortRoutePositive )
{
		GridWorld space(Earth::NorthPole, grid_horizontal, grid_vertical);
        GridWorldRoute routeLog = GridWorldRoute("QJNIB", space);
        Route route = Route(LogFiles::GPXRoutesDir + "isLongRoutePositive-N0675532.gpx", isFileName);
        BOOST_CHECK_EQUAL( route.netHeightGain(), 300 );
}

/*
*Test name: isLongRoutePositive
*Test: checks that a long route will return a postive value
*Type: Valid
*/

BOOST_AUTO_TEST_CASE( isLongRoutePositive )
{
		GridWorld space(Earth::NorthPole, grid_horizontal, grid_vertical);
        GridWorldRoute routeLog = GridWorldRoute("AJNFSDIUFNSGSDFGDSGIUFNIM", space);
        Route route = Route(LogFiles::GPXRoutesDir + "isLongRoutePositive-N0675532.gpx", isFileName);
        BOOST_CHECK_EQUAL( route.netHeightGain(), 200 );
}

/*
*Test name: isRouteThatReturnsToStartPointZero
*Test: checks that a route will return a zero value if it returns to it's start point
*Type: Valid
*/

BOOST_AUTO_TEST_CASE( isRouteThatReturnsToStartPointZero )
{
		GridWorld space(Earth::NorthPole, grid_horizontal, grid_vertical);
        GridWorldRoute routeLog = GridWorldRoute("QJNIBSDFONSDFQ", space);
        Route route = Route(LogFiles::GPXRoutesDir + "isLongRoutePositive-N0675532.gpx", isFileName);
        BOOST_CHECK_EQUAL( route.netHeightGain(), 0 );
}

		




BOOST_AUTO_TEST_SUITE_END()
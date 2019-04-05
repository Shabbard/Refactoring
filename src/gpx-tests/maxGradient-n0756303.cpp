#include <boost/test/unit_test.hpp>

#include "earth.h"
#include "route.h"
#include "gridworld.h"
#include "gridworld_route.h"
#include "logs.h"
#include "types.h"


#include <fstream>
#include <string>


using namespace GPS;

const degrees TOLERANCE = 0.5;
const metres HORIZONTALGRIDUNIT = 100;
const metres VERTICLEGRIDUNIT = 100;

//Gradients were calculated by hand with help from below link + Wolfram Alpha
//https://math.stackexchange.com/questions/707673/find-angle-in-degrees-from-one-point-to-another-in-2d-space
const degrees GRADIENT = 45;
//Diagonal gradient required the use of pythag to form distance to diagonal points
const degrees DIAGONALGRADIENT = 35.26438968;

//Create or overwrite a log file containing created route, returns the path of generated log
std::string createLog(std::string logName, std::string route) {
	
	GridWorld grid(Earth::CliftonCampus, HORIZONTALGRIDUNIT, VERTICLEGRIDUNIT);
	GridWorldRoute gridRoute(route, grid);
	
	std::string path = LogFiles::GPXRoutesDir + logName + "_n0756303.gpx";
	std::ofstream file(path);
	
	file << gridRoute.toGPX(true, logName);
	file.close();
	return path;
	
}

BOOST_AUTO_TEST_SUITE( Route_maxGradient_n0756303 )

//No test case for 0 points as this is asserted in route.cpp

//Check that any route with one point returns a maxGradient of 0
BOOST_AUTO_TEST_CASE( onePoint )
{	
	std::string path = createLog("singlePointRoute", "M");
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), 0, TOLERANCE);
}

//Check that any route consisiting of only flat point returns a maxGradient of 0
BOOST_AUTO_TEST_CASE( route_flat )
{
	std::string path = createLog("flatRoute", "ABC");
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), 0, TOLERANCE);
}

//Check that a route with all accending points, returns a positive version of a pre calculated angle
BOOST_AUTO_TEST_CASE( up_route )
{
	std::string path = createLog("upRoute", "CHM");
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), GRADIENT, TOLERANCE);
}

//Check that a route with all decending points, returns a negative version of a pre calculated angle
BOOST_AUTO_TEST_CASE( down_route )
{
	std::string path = createLog("downRoute", "MHC");
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), - GRADIENT, TOLERANCE);
}

//Check that a diagonal route with all accending points, returns a positive version of pre calculated value
BOOST_AUTO_TEST_CASE( diagonal_up_route )
{
	std::string path = createLog("diagUpRoute", "EIM");
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), DIAGONALGRADIENT, TOLERANCE);
}

//Check that a diagonal route with all decending points, returns a negative version of pre calculated value
BOOST_AUTO_TEST_CASE( diagonal_down_route )
{
	std::string path = createLog("diagDownRoute", "MIE");
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), -DIAGONALGRADIENT, TOLERANCE);
}

//Check a route with an uphill and downhill section returns the gradient of uphill section
BOOST_AUTO_TEST_CASE( diagonal_up_down_route )
{
	std::string path = createLog("diagUpDownRoute", "UQMIE");
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), DIAGONALGRADIENT, TOLERANCE);
}
//Check a route containing a flat section follwoed by an uphill section
BOOST_AUTO_TEST_CASE( flat_up_route )
{
	std::string path = createLog("flatUpDownRoute", "ABCHM");
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), GRADIENT, TOLERANCE);
}

//Check a route contaning a downhill section followed by a flat section, max gradient is 0 as downhill is negative
BOOST_AUTO_TEST_CASE( down_flat_route )
{
	std::string path = createLog("downFlatRoute", "MHCBA");
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), 0, TOLERANCE);
}
//Check a route containing flat, uphill and downhill sections
BOOST_AUTO_TEST_CASE( diagonal_up_down_flat_up_route )
{
	std::string path = createLog("diagUpDownFlatUpRoute", "UQMIEDCHM");
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), GRADIENT, TOLERANCE);
}


BOOST_AUTO_TEST_SUITE_END()
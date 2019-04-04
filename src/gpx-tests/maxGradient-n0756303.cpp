#include <boost/test/unit_test.hpp>

#include <fstream>
#include <string>

#include "earth.h"
#include "gridworld.h"
#include "gridworld_route.h"
#include "logs.h"
#include "route.h"

using namespace GPS;

const degrees TOLERANCE = 0.5;
const metres HORIZONTALGRIDUNIT = 10000;
const metres VERTICLEGRIDUNIT = 1000;

//Gradients were calculated by hand with help from below link + Wolfram Alpha
//https://math.stackexchange.com/questions/707673/find-angle-in-degrees-from-one-point-to-another-in-2d-space
const degrees GRADIENT = 5.71059314;

//Diagonal gradient required the use of pythag to form distance to diagonal points
const degrees DIAGONALGRADIENT = 4.04469124;

//Create or overwrite a log file containing created route
std::string createLog(std::string logName, GridWorldRoute route) {
	
	std::string path = LogFiles::GPXRoutesDir + logName + "_n0756303.gpx";
	std::ofstream file(path);
	
	file << route.toGPX(true, logName);
	file.close();
	return path;
	
}

BOOST_AUTO_TEST_SUITE( Route_maxGradient_n0756303 )

//Check that any route with one point returns a maxGradient of 0
BOOST_AUTO_TEST_CASE(onePoint)
{
	GridWorld grid(Earth::CliftonCampus);
	GridWorldRoute gridRoute("M", grid);
	
	std::string path = createLog("singlePointRoute", gridRoute);
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), 0, TOLERANCE);
}

//Check that any route consisiting of only flat point returns a maxGradient of 0
BOOST_AUTO_TEST_CASE( route_flat )
{
	GridWorld grid(Earth::CliftonCampus, HORIZONTALGRIDUNIT, VERTICLEGRIDUNIT);
	GridWorldRoute gridRoute("ABC", grid);
	
	std::string path = createLog("flatRoute", gridRoute);
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), 0, TOLERANCE);
}

//Check that a route with all accending points, returns a positive version of a pre calculated angle
BOOST_AUTO_TEST_CASE( up_route )
{
	GridWorld grid(Earth::CliftonCampus, HORIZONTALGRIDUNIT, VERTICLEGRIDUNIT);
	GridWorldRoute gridRoute("CHM", grid);
	
	std::string path = createLog("upRoute", gridRoute);
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), GRADIENT, TOLERANCE);
}

//Check that a route with all decending points, returns a negative version of a pre calculated angle
BOOST_AUTO_TEST_CASE( down_route )
{
	GridWorld grid(Earth::CliftonCampus, HORIZONTALGRIDUNIT, VERTICLEGRIDUNIT);
	GridWorldRoute gridRoute("MHC", grid);
	
	std::string path = createLog("downRoute", gridRoute);
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), - GRADIENT, TOLERANCE);
}

//Check that a diagonal route with all accending points, returns a positive version of pre calculated value
BOOST_AUTO_TEST_CASE( diagonal_up_route )
{
	GridWorld grid(Earth::CliftonCampus, HORIZONTALGRIDUNIT, VERTICLEGRIDUNIT);
	GridWorldRoute gridRoute("EIM", grid);
	
	std::string path = createLog("diagUpRoute", gridRoute);
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), DIAGONALGRADIENT, TOLERANCE);
}

//Check that a diagonal route with all decending points, returns a negative version of pre calculated value
BOOST_AUTO_TEST_CASE( diagonal_down_route )
{
	GridWorld grid(Earth::CliftonCampus, HORIZONTALGRIDUNIT, VERTICLEGRIDUNIT);
	GridWorldRoute gridRoute("MIE", grid);
	
	std::string path = createLog("diagDownRoute", gridRoute);
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), -DIAGONALGRADIENT, TOLERANCE);
}

//Check a route with an uphill and downhill section returns the gradient of uphill section
BOOST_AUTO_TEST_CASE( diagonal_up_down_route )
{
	GridWorld grid(Earth::CliftonCampus, HORIZONTALGRIDUNIT, VERTICLEGRIDUNIT);
	GridWorldRoute gridRoute("UQMIE", grid);
	
	std::string path = createLog("diagUpDownRoute", gridRoute);
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), DIAGONALGRADIENT, TOLERANCE);
}
//Check a route containing a flat section follwoed by an uphill section
BOOST_AUTO_TEST_CASE( flat_up_route )
{
	GridWorld grid(Earth::CliftonCampus, HORIZONTALGRIDUNIT, VERTICLEGRIDUNIT);
	GridWorldRoute gridRoute("ABCHM", grid);
	
	std::string path = createLog("flatUpDownRoute", gridRoute);
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), GRADIENT, TOLERANCE);
}

//Check a route contaning a downhill section followed by a flat section, max gradient is 0 as downhill is negative
BOOST_AUTO_TEST_CASE( down_flat_route )
{
	GridWorld grid(Earth::CliftonCampus, HORIZONTALGRIDUNIT, VERTICLEGRIDUNIT);
	GridWorldRoute gridRoute("MHCBA", grid);
	
	std::string path = createLog("downFlatRoute", gridRoute);
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), 0, TOLERANCE);
}
//Check a route containing a section of diagnonally accending and decending, a flat portion, and then accending again
BOOST_AUTO_TEST_CASE( diagonal_up_down_flat_up_route )
{
	GridWorld grid(Earth::CliftonCampus, HORIZONTALGRIDUNIT, VERTICLEGRIDUNIT);
	GridWorldRoute gridRoute("UQMIEDCHM", grid);
	
	std::string path = createLog("diagUpDownFlatUpRoute", gridRoute);
	Route route(path, true);
	
	BOOST_CHECK_CLOSE(route.maxGradient(), GRADIENT, TOLERANCE);
}


BOOST_AUTO_TEST_SUITE_END()
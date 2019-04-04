#include <boost/test/unit_test.hpp>
#include <fstream>
#include <string>

#include "earth.h"
#include "logs.h"
#include "route.h"
#include "gridworld.h"
#include "gridworld_route.h"

using namespace GPS;

const bool IsFileName = true;

const degrees DegreeOfAccuracy = 0.01;
const degrees Gradient = 5.71059;
const metres HorizontalGridUnit = 10000;
const metres VerticalGridUnit = 1000;

/**
* Grid world in the layout of a 5x5 grid
* with each point denoted by a character.
*
* A B C D E
* F G H I J
* K L M N O
* P Q R S T
* U V W X Y
*/

std::string logCreation(std::string testName, GridWorldRoute route)
{
    std::string fileName = "N0826291" + testName + ".gpx";
    std::ofstream fileOutput(GPS::LogFiles::GPXRoutesDir + fileName);

    fileOutput << route.toGPX(true, testName);
    fileOutput.close();

    return fileName;
}

BOOST_AUTO_TEST_SUITE( SteepestGradientN0826291 )
/**
* Tests that a single point gradient is equal to 0
* since it is not possible to have a gradient from a single point.
*/
BOOST_AUTO_TEST_CASE( SinglePointGradientRoute )
{
    GridWorldRoute routeLog = GridWorldRoute("M", GridWorld(Earth::Nottingham, HorizontalGridUnit , VerticalGridUnit));
    Route route = Route(LogFiles::GPXRoutesDir + logCreation("SinglePointGradientRoute", routeLog), IsFileName);
    BOOST_CHECK_CLOSE( route.steepestGradient(), 0, DegreeOfAccuracy);
}
/**
* Tests that a line with points that only span the horizontal plane
* should have no gradient, since there is no change in elevation.
*/
BOOST_AUTO_TEST_CASE( NoGradientRoute )
{
    GridWorldRoute routeLog = GridWorldRoute("LMN", GridWorld(Earth::Nottingham, HorizontalGridUnit , VerticalGridUnit));
    Route route = Route(LogFiles::GPXRoutesDir + logCreation("NoGradientRoute", routeLog), IsFileName);
    BOOST_CHECK_CLOSE( route.steepestGradient(), 0, DegreeOfAccuracy);
}
/**
* Tests that a route with only negative points 
* should return a positive value.
*/
BOOST_AUTO_TEST_CASE( NegativeGradientRoute )
{
    GridWorldRoute routeLog = GridWorldRoute("EIM", GridWorld(Earth::Nottingham, HorizontalGridUnit , VerticalGridUnit));
    Route route = Route(LogFiles::GPXRoutesDir + logCreation("NegativeGradientRoute", routeLog), IsFileName);
    BOOST_CHECK_CLOSE( route.steepestGradient(), Gradient, DegreeOfAccuracy);
}
/** 
* Tests that a route with positive points
* should return a positive value.
*/
BOOST_AUTO_TEST_CASE( PositiveGradientRoute )
{
    GridWorldRoute routeLog = GridWorldRoute("UQM", GridWorld(Earth::Nottingham, HorizontalGridUnit , VerticalGridUnit));
    Route route = Route(LogFiles::GPXRoutesDir + logCreation("PositiveGradientRoute", routeLog), IsFileName);
    BOOST_CHECK_CLOSE( route.steepestGradient(), Gradient, DegreeOfAccuracy);
}
/**
* Tests that a route with both positive and negative point
* should result a positive value.
*/
BOOST_AUTO_TEST_CASE( PositiveNegativeGradientRoute )
{
    GridWorldRoute routeLog = GridWorldRoute("AGMIE", GridWorld(Earth::Nottingham, HorizontalGridUnit , VerticalGridUnit));
    Route route = Route(LogFiles::GPXRoutesDir + logCreation("PositiveNegativeGradientRoute", routeLog), IsFileName);
    BOOST_CHECK_CLOSE( route.steepestGradient(), Gradient, DegreeOfAccuracy);
}

BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>
#include <fstream>
#include "logs.h"
#include "route.h"
#include "gridworld_route.h"

using namespace GPS;

const degrees PERCENTAGE_ACCURACY = 0.01;
const metres HORIZONTAL_GRID_UNIT = 10000;
const metres VERTICAL_GRID_UNIT = 1000;
const metres GRADIENT = 5.71059; // calculated by taking the arctan of 1000/10000

/* The steepest gradient is the largest gradient by magnitude.
 * 
 * Gradient is calculated from the difference in the y values over (divided by) the
 * difference in x values between two points.
 * 
 * The key for finding the steepest gradient is that you must ignore the sign i.e the positive or negative aspect
 * of the number, taking only its absolute value. 
*/

std::string createLogs(std::string name, GridWorldRoute route)
{
    std::string fileName = name + ".gpx";

    std::ofstream fileOutput(GPS::LogFiles::GPXRoutesDir + fileName);

    fileOutput << route.toGPX(true, name);
    fileOutput.close();

    return fileName;
}

 /* GridWorld consists of a grid of points, where each point is named by a single character A-Y.
   *
   *  A B C D E
   *  F G H I J
   *  K L M N O
   *  P Q R S T
   *  U V W X Y
   *
   *  The central point M is used as the initial reference point.
   *  Up/down in the grid changes latitude relative to M.
   *  Left/right in the grid changes longitude relative to M.
   *  Note: the closer you get to a pole, the more distorted from a grid this becomes.
   */

BOOST_AUTO_TEST_SUITE( Steepest_Gradient )

const bool isFileName = true;

// You cannot calculate a gradient from just one point, the program should return 0
BOOST_AUTO_TEST_CASE( Route_with_one_point )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_CLOSE( route.steepestGradient(),  0, PERCENTAGE_ACCURACY);
}

// two points on top of each other should have a gradient of 0
BOOST_AUTO_TEST_CASE( Route_with_two_vertical_points )
{
    GridWorldRoute routeLog = GridWorldRoute("MH", GridWorld(Earth::NorthPole, 0, VERTICAL_GRID_UNIT));

    Route route = Route(LogFiles::GPXRoutesDir + createLogs("RouteWithTwoVerticalPoints", routeLog), isFileName);
    BOOST_CHECK_CLOSE( route.steepestGradient(),  0, PERCENTAGE_ACCURACY);
}

// two points with no elevation difference should have a gradient of 0
BOOST_AUTO_TEST_CASE( Route_with_two_horizontal_points )
{
    GridWorldRoute routeLog = GridWorldRoute("MH", GridWorld(Earth::NorthPole, HORIZONTAL_GRID_UNIT, 0));

    Route route = Route(LogFiles::GPXRoutesDir + createLogs("RouteWithTwoHorizontalPoints", routeLog), isFileName);
    BOOST_CHECK_CLOSE( route.steepestGradient(),  0, PERCENTAGE_ACCURACY);
}

// check values with only negative gradients, should return a positive gradient
BOOST_AUTO_TEST_CASE( Route_with_only_negative_gradients )
{
    GridWorldRoute routeLog = GridWorldRoute("MHC", GridWorld(Earth::NorthPole, HORIZONTAL_GRID_UNIT, VERTICAL_GRID_UNIT));

    Route route = Route(LogFiles::GPXRoutesDir + createLogs("RouteWithOnlyNegativeGradients", routeLog), isFileName);
    BOOST_CHECK_CLOSE( route.steepestGradient(),  GRADIENT, PERCENTAGE_ACCURACY);
}

// check different values with only positive gradients, should return a positive gradient
BOOST_AUTO_TEST_CASE( Route_with_only_positive_gradients )
{
    GridWorldRoute routeLog = GridWorldRoute("WRM", GridWorld(Earth::NorthPole, HORIZONTAL_GRID_UNIT, VERTICAL_GRID_UNIT));

    Route route = Route(LogFiles::GPXRoutesDir + createLogs("RouteWithOnlyPositiveGradients", routeLog), isFileName);
    BOOST_CHECK_CLOSE( route.steepestGradient(),  GRADIENT, PERCENTAGE_ACCURACY); // use correct macro for floating point numbers
}

// check values with both positive and negative gradients, should return a positive gradient
BOOST_AUTO_TEST_CASE( Route_with_positive_and_negative_gradients )
{
    GridWorldRoute routeLog = GridWorldRoute("HMR", GridWorld(Earth::NorthPole, HORIZONTAL_GRID_UNIT, VERTICAL_GRID_UNIT));

    Route route = Route(LogFiles::GPXRoutesDir + createLogs("RouteWithPositiveAndNegativeGradients", routeLog), isFileName);
    BOOST_CHECK_CLOSE( route.steepestGradient(),  GRADIENT, PERCENTAGE_ACCURACY);
}


// check values with the steepest gradient being at the beginning, middle and end of the list of points

BOOST_AUTO_TEST_SUITE_END()
#include <boost/test/unit_test.hpp>
#include <fstream>
#include "logs.h"
#include "route.h"
#include "gridworld_route.h"
#include "xmlgenerator.h"

using namespace GPS;

/* The steepest gradient is the largest gradient by magnitude.
 * 
 * Gradient is calculated from the difference in the y values over (divided by) the
 * difference in x values between two points.
 * 
 * The key for finding the steppest gradient is that you must ignore the sign i.e the positive or negative aspect
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

BOOST_AUTO_TEST_SUITE( Steepest_Gradient )

const bool isFileName = true;

// You cannot calculate a gradient from just one point, the program should throw an out of range exception
BOOST_AUTO_TEST_CASE( Route_with_one_point )
{
    GridWorldRoute routeLog = GridWorldRoute("A");

    Route route = Route(LogFiles::GPXRoutesDir + createLogs("RouteWithOnePoint", routeLog), isFileName);
    BOOST_CHECK_EQUAL( route.steepestGradient(),  0);
}

// two points on top of each other should have a gradient of 0

// two points with no elevation difference should have a gradient of 0

// check different values with only positive gradients

// check values with only negative gradients

// check values with both positive and negative gradients

// check values with the steepest gradient being at the beginning, middle and end of the list of points

 
BOOST_AUTO_TEST_SUITE_END()
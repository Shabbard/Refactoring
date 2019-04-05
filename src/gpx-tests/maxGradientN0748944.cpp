/* Aaron Squires - N0748944 */

#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "geometry.h"
#include "earth.h"
#include "gridworld.h"
#include "gridworld_route.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace GPS;

/* Constant Variables for BOOST CASE tests */
/* Set Variable for Gradient */
const degrees Grad = 5.71;
/* Set Variable for Diagonal Gradient */
const degrees GradDiag = 4.05;
/* Set Variable for Horizontal Grid */
const metres GradGridHori = 1000;
/* Set Variable for vertical Grid */
const metres GradGridVerti = 100;
/* Set Variable for tolerance */
const degrees GradGridTol = 0.5;


const bool isFileName = true;
/* Creating the GPX log files */
std::string MakeLogFile(std::string name, GridWorldRoute route)
{
    std::string filepath = LogFiles::GPXRoutesDir + "N0748944" + name + ".gpx";
    std::ofstream file(filepath);
    file << route.toGPX(true, name);
    file.close();
    return filepath;
}

BOOST_AUTO_TEST_SUITE( Route_maxGradient_N0748944)

/*Test number 1
 * Tesing maxgradient where there is only one value for elevation
 * the resulting value should be 0*/

BOOST_AUTO_TEST_CASE(Route_maxGradient_is0)
{
    /*GPX file Name = "ABCD.gpx"*/
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.maxGradient(), 0);
}

/*Test number 2
 * Testing that the output of the maxGradient returns 0 when elevation is flat*/

BOOST_AUTO_TEST_CASE(Route_maxGradient_flat_ABC)
{
    GridWorld GradGrid(Earth::CityCampus, GradGridHori, GradGridVerti);
    GridWorldRoute GradRoute("ABC", GradGrid);

    std::string path = MakeLogFile("Route_maxGradiant_ABC", GradRoute);
    Route route(path, true);
    BOOST_CHECK_CLOSE(route.maxGradient(), 0.0, GradGridTol);
}

/*Test number 3
 * Tests that the correct down gradient is calculated */

BOOST_AUTO_TEST_CASE( Route_maxGradient_Down_MRW )
{
    GridWorld GradGrid(Earth::CityCampus, GradGridHori, GradGridVerti);
    GridWorldRoute GradRoute("MRW", GradGrid);

    std::string path = MakeLogFile("Route_maxGradiant_MRW", GradRoute);
    Route route(path, true);
    BOOST_CHECK_CLOSE(route.maxGradient(), -Grad, GradGridTol);
}

/*Test number 4
 * Tests that the correct down gradient is calculated */

BOOST_AUTO_TEST_CASE( Route_maxGradient_Down_WRM )
{
    GridWorld GradGrid(Earth::CityCampus, GradGridHori, GradGridVerti);
    GridWorldRoute GradRoute("WRM", GradGrid);

    std::string path = MakeLogFile("Route_maxGradiant_WRM", GradRoute);
    Route route(path, true);
    BOOST_CHECK_CLOSE(route.maxGradient(), Grad, GradGridTol);
}

/*Test number 5
 * Testing that the output of the maxGradient returns 0 when elevation is flat*/

BOOST_AUTO_TEST_CASE(Route_maxGradient_flat_ABC_NorthPole)
{
    GridWorld GradGrid(Earth::NorthPole, GradGridHori, GradGridVerti);
    GridWorldRoute GradRoute("ABC", GradGrid);

    std::string path = MakeLogFile("Route_maxGradiant_ABC", GradRoute);
    Route route(path, true);
    BOOST_CHECK_CLOSE(route.maxGradient(), 0.0, GradGridTol);
}

/*Test number 6
 * Tests that the correct down gradient is calculated */

BOOST_AUTO_TEST_CASE( Route_maxGradient_Down_MRW_NorthPole )
{
    GridWorld GradGrid(Earth::NorthPole, GradGridHori, GradGridVerti);
    GridWorldRoute GradRoute("MRW", GradGrid);

    std::string path = MakeLogFile("Route_maxGradiant_MRW", GradRoute);
    Route route(path, true);
    BOOST_CHECK_CLOSE(route.maxGradient(), -Grad, GradGridTol);
}

/*Test number 7
 * Tests that the correct down gradient is calculated */

BOOST_AUTO_TEST_CASE( Route_maxGradient_Down_WRM_NorthPole )
{
    GridWorld GradGrid(Earth::NorthPole, GradGridHori, GradGridVerti);
    GridWorldRoute GradRoute("WRM", GradGrid);

    std::string path = MakeLogFile("Route_maxGradiant_WRM", GradRoute);
    Route route(path, true);
    BOOST_CHECK_CLOSE(route.maxGradient(), Grad, GradGridTol);
}
BOOST_AUTO_TEST_SUITE_END()
/* A B C D E
 * F G H I J
 * K L M N O
 * P Q R S T
 * U V W X Y
 */

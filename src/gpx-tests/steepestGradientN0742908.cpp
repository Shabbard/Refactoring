#include <boost/test/unit_test.hpp>
#include <fstream>

#include "gridworld_route.h"
#include "logs.h"
#include "route.h"

using namespace GPS;

/*
        Leon Winstanley - N0742908
*/



// function to generate a log for each file when implemented..
std::string generateLogs(std::string nameOfTest, GridWorldRoute route)
{
    std::string fileName = "N0742908" + nameOfTest + ".gpx";
    std::ofstream fileOutput(GPS::LogFiles::GPXRoutesDir + fileName);

    fileOutput << route.toGPX(true, nameOfTest);
    fileOutput.close();

    return fileName;
}
// Example of gridworld
    /* A B C D E
     * F G H I J
     * K L M N O
     * P Q R S T
     * U V W X Y
     */

BOOST_AUTO_TEST_SUITE( Steepest_Gradient_N0742908 )


    // constants to use in tests
    const bool IS_FILE_NAME = true;
    const degrees DEGREE_OF_ACCURACY = 0.1;
    const metres HORI_UNIT = 20000;
    const metres VERT_UNIT = 2000;
    

    // tests that a negative gradient is still positive.

BOOST_AUTO_TEST_CASE( is_Negative_Gradient )
{
    GridWorldRoute routeLog = GridWorldRoute("AGM", GridWorld(Earth::CityCampus, HORI_UNIT , VERT_UNIT));
    Route route = Route(LogFiles::GPXRoutesDir + generateLogs("is_Negative_Gradient", routeLog), IS_FILE_NAME);
    BOOST_CHECK_CLOSE( route.steepestGradient(), 4.0580047402710955, DEGREE_OF_ACCURACY);
}

    // tests that a positive gradient correct.

BOOST_AUTO_TEST_CASE( is_Positive_Gradient )
{
    GridWorldRoute routeLog = GridWorldRoute("MGA", GridWorld(Earth::CityCampus, HORI_UNIT , VERT_UNIT));
    Route route = Route(LogFiles::GPXRoutesDir + generateLogs("is_Positive_Gradient", routeLog), IS_FILE_NAME);
    BOOST_CHECK_CLOSE( route.steepestGradient(), 4.0580047402710955, DEGREE_OF_ACCURACY);
}

    // tests that a one point gradient equals 0.
BOOST_AUTO_TEST_CASE( is_OnePoint_Gradient )
{
    GridWorldRoute routeLog = GridWorldRoute("M", GridWorld(Earth::CityCampus, HORI_UNIT , VERT_UNIT));
    Route route = Route(LogFiles::GPXRoutesDir + generateLogs("is_OnePoint_Gradient", routeLog), IS_FILE_NAME);
    BOOST_CHECK_CLOSE( route.steepestGradient(), 0, DEGREE_OF_ACCURACY);
}

    // checks that a positive and then negitive gradient result in correct answer.
BOOST_AUTO_TEST_CASE( is_PositiveNegative_Gradient )
{
    GridWorldRoute routeLog = GridWorldRoute("UQMSY", GridWorld(Earth::CityCampus, HORI_UNIT , VERT_UNIT));
    Route route = Route(LogFiles::GPXRoutesDir + generateLogs("is_PositiveNegative_Gradient", routeLog), IS_FILE_NAME);
    BOOST_CHECK_CLOSE( route.steepestGradient(), 4.0424037169314566, DEGREE_OF_ACCURACY);
}

    // checks that a flat line equals 0 as no gradient is present.
BOOST_AUTO_TEST_CASE( is_No_Gradient )
{
    GridWorldRoute routeLog = GridWorldRoute("ABC", GridWorld(Earth::CityCampus, HORI_UNIT , VERT_UNIT));
    Route route = Route(LogFiles::GPXRoutesDir + generateLogs("is_No_Gradient", routeLog), IS_FILE_NAME);
    BOOST_CHECK_CLOSE( route.steepestGradient(), 0, DEGREE_OF_ACCURACY);
}

BOOST_AUTO_TEST_SUITE_END()

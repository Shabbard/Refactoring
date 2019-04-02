#include <boost/test/unit_test.hpp>
#include <fstream>
#include "logs.h"
#include "types.h"
#include "route.h"
#include "gridworld_route.h"
#include "xmlgenerator.h"


/*
        Leon Winstanley - N0742908
*/

using namespace GPS;

// function to generate a log for each file when implemented..
std::string generateLogs(std::string nameOfTest, GridWorldRoute route)
{
    std::string fileName = nameOfTest + ".gpx";
    std::ofstream fileOutput(GPS::LogFiles::GPXRoutesDir + fileName);

    fileOutput << route.toGPX(true, nameOfTest);
    fileOutput.close();

    return fileName;
}

    /* A B C D E
     * F G H I J
     * K L M N O
     * P Q R S T
     * U V W X Y
     */

BOOST_AUTO_TEST_SUITE( Steepest_Gradient_N0742908 )

    bool isFileName = true;

BOOST_AUTO_TEST_CASE( is_Negative_Gradient )
{
    GridWorldRoute routeLog = GridWorldRoute("AGM");
    Route route = Route(LogFiles::GPXRoutesDir + generateLogs("is_Negative_Gradient", routeLog), isFileName);
    BOOST_CHECK_EQUAL( route.steepestGradient(), -50);
}

BOOST_AUTO_TEST_CASE( is_Positive_Gradient )
{
    GridWorldRoute routeLog = GridWorldRoute("MGA");
    Route route = Route(LogFiles::GPXRoutesDir + generateLogs("is_Positive_Gradient", routeLog), isFileName);
    BOOST_CHECK_EQUAL( route.steepestGradient(), 50);
}

BOOST_AUTO_TEST_CASE( is_OnePoint_Gradient )
{
    GridWorldRoute routeLog = GridWorldRoute("M");
    Route route = Route(LogFiles::GPXRoutesDir + generateLogs("is_OnePoint_Gradient", routeLog), isFileName);
    BOOST_CHECK_EQUAL( route.steepestGradient(), 0);
}

BOOST_AUTO_TEST_CASE( is_PositiveNegative_Gradient )
{
    GridWorldRoute routeLog = GridWorldRoute("UQMSY");
    Route route = Route(LogFiles::GPXRoutesDir + generateLogs("is_OnePoint_Gradient", routeLog), isFileName);
    BOOST_CHECK_EQUAL( route.steepestGradient(), 0);
}

BOOST_AUTO_TEST_CASE( is_No_Gradient )
{
    GridWorldRoute routeLog = GridWorldRoute("ABC");
    Route route = Route(LogFiles::GPXRoutesDir + generateLogs("is_No_Gradient", routeLog), isFileName);
    BOOST_CHECK_EQUAL( route.steepestGradient(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
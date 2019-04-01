#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"
#include "gridworld_route.h"
#include "xmlgenerator.h"

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


/*
*/
BOOST_AUTO_TEST_SUITE( Steepest_Gradient_N0742908 )

    bool isFileName = true;

BOOST_AUTO_TEST_CASE( is_Negative_Gradient )
{
    GridWorldRoute routeLog = GridWorldRoute("A");
    Route route = Route(LogFiles::GPXRoutesDir + generateLogs("is_Negative_Gradient", routeLog), isFileName);
    BOOST_CHECK_EQUAL( route.steepestGradient(),  -50);
}

BOOST_AUTO_TEST_SUITE_END()
#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "gridworld_route.h"

// Used solely for GPX code generation, has no effect on functionality of test suite.
#include <fstream>

using namespace GPS;

// My GPX log generation function

void generateLog(std::string route, GridWorldRoute testType){
    std::ofstream gpxFileToWrite;
    gpxFileToWrite.open(LogFiles::GPXRoutesDir + "N0735026" + route + ".gpx");
    gpxFileToWrite << testType.toGPX(true, route);
    gpxFileToWrite.close();
    return;
}


BOOST_AUTO_TEST_SUITE( Route_minLongitude_N0735026 )

const std::string studID = "N0735026";

// Checks that the longitude value is retrieved correctly
BOOST_AUTO_TEST_CASE( single_point_route )
{
    generateLog("singlePointRoute", GridWorldRoute("M",Earth::CliftonCampus));

    Route testRoute(LogFiles::GPXRoutesDir + studID + "singlePointRoute.gpx",true);
    BOOST_CHECK_EQUAL(testRoute.minLongitude(), -1.18403);
}

// Checks the lowest longitude value is found
BOOST_AUTO_TEST_CASE( multiple_point_route )
{
    generateLog("multiplePointRoute", GridWorldRoute("NOMKL",Earth::CliftonCampus));

    Route testRoute(LogFiles::GPXRoutesDir + studID + "multiplePointRoute.gpx",true);
    BOOST_CHECK_EQUAL(testRoute.minLongitude(), -1.48196);
}

// Checks comparisons are compared to the right precision
BOOST_AUTO_TEST_CASE( two_points_close_together )
{
    //generateLog("twoPointsCloseTogether", GridWorldRoute("OMN", GridWorld(Earth::CliftonCampus,0.01,0)));

    Route testRoute(LogFiles::GPXRoutesDir + studID + "twoPointsCloseTogether.gpx",true,0);
    BOOST_CHECK_EQUAL(testRoute.minLongitude(), -1.18403);
}

// Checks comparisons aren't affected by polarity
BOOST_AUTO_TEST_CASE( route_passes_over_meridian )
{
    generateLog("routePassesOverMeridian", GridWorldRoute("NL",Earth::EquatorialMeridian));

    Route testRoute(LogFiles::GPXRoutesDir + studID + "routePassesOverMeridian.gpx",true);
    BOOST_CHECK_EQUAL(testRoute.minLongitude(), -0.0898312);
}

BOOST_AUTO_TEST_SUITE_END()

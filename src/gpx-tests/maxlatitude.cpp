#include<boost/test/unit_test.hpp>

#include "route.h"
#include "logs.h"
#include "gridworld_route.h"
#include "gridworld.h"
#include <fstream>
using namespace GPS;

// Tests created by James bray, N0731234

// create gpx log files
std::string createGPXlog(GridWorldRoute gwr, std::string fileName){
    std::string name = "maxLat_" + fileName + "_N0731234.gpx";
    // takes a grid world and returns string points
    std::string route = gwr.toGPX(true, fileName);

    // make file
    std::ofstream file(LogFiles::GPXRoutesDir + name); // create file with name
    file << route; // push route points into file
    file.close(); // close file

    return name;
}

BOOST_AUTO_TEST_SUITE(Route_maxLatitude)

BOOST_AUTO_TEST_CASE(origin_point){
    // test for just a single point located on the origin

    GridWorldRoute gwr = GridWorldRoute("M");
    Route route = Route(LogFiles::logsDir+createGPXlog(gwr,"origin_point"),true);
    BOOST_CHECK_EQUAL(route.maxLatitude(),0);
}

BOOST_AUTO_TEST_CASE(single_point){
    // test for a single point that is not the origin
    
    GridWorldRoute gwr = GridWorldRoute("A");
    Route route = Route(LogFiles::logsDir+createGPXlog(gwr,"single_point"),true);
    BOOST_CHECK_EQUAL(route.maxLatitude(),1.79964);
}

BOOST_AUTO_TEST_CASE(multiple_points){
    // test for multiple points on the gridworld

    GridWorldRoute gwr = GridWorldRoute("MHC");
    Route route = Route(LogFiles::logsDir+createGPXlog(gwr,"multiple_points"),true);
    BOOST_CHECK_EQUAL(route.maxLatitude(),1.79964);
}

BOOST_AUTO_TEST_CASE(circular_route){
    // test for max latitude on a circual route

    GridWorldRoute gwr = GridWorldRoute("PFHRP");
    Route route = Route(LogFiles::logsDir+createGPXlog(gwr,"circular_route"),true);
    BOOST_CHECK_EQUAL(route.maxLatitude(),0.89982);
}

BOOST_AUTO_TEST_SUITE_END();

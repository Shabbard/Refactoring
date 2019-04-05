#include<boost/test/unit_test.hpp>

#include "route.h"
#include "logs.h"
#include "gridworld_route.h"
#include "gridworld.h"
#include <fstream>
#include <iostream>
using namespace GPS;

// Tests created by James bray, N0731234

// create gpx log files
std::string createGPXlog(GridWorldRoute gwr, std::string name){
    // takes a grid world and returns string points
    std::string route = gwr.toGPX(true, name);

    // path of the actual file
    std::string filePath = "logs/GPX/routes/maxLatitude_" + name + "_N0731234.gpx";

    // make file
    std::ofstream file(filePath); // create file in given location
    file << route; // push route points into file
    file.close(); // close file

    return filePath; // pass path into the route function
}

BOOST_AUTO_TEST_SUITE(Route_maxLatitude)

BOOST_AUTO_TEST_CASE(origin_point){
    // test for just a single point located on the origin

    GridWorldRoute gwr = GridWorldRoute("M");
    Route route = Route(createGPXlog(gwr,"origin_point"),true);
    BOOST_CHECK_EQUAL(route.maxLatitude(),0);
}

BOOST_AUTO_TEST_CASE(single_point){
    // test for a single point that is not the origin
    
    GridWorldRoute gwr = GridWorldRoute("A");
    Route route = Route(createGPXlog(gwr,"single_point"),true);
    BOOST_CHECK_EQUAL(route.maxLatitude(),0.179964);
}

BOOST_AUTO_TEST_CASE(multiple_points){
    // test for multiple points on the gridworld

    GridWorldRoute gwr = GridWorldRoute("MHC");
    Route route = Route(createGPXlog(gwr,"multiple_points"),true);
    BOOST_CHECK_EQUAL(route.maxLatitude(),0.179964);
}

BOOST_AUTO_TEST_CASE(circular_route){
    // test for max latitude on a circual route

    GridWorldRoute gwr = GridWorldRoute("PFHRP");
    Route route = Route(createGPXlog(gwr,"circular_route"),true);
    BOOST_CHECK_EQUAL(route.maxLatitude(),0.089982);
}

BOOST_AUTO_TEST_SUITE_END();

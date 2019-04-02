#include <boost/test/unit_test.hpp>
#include "../../headers/route.h"
#include "../../headers/logs.h"
#include "../../headers/gridworld_route.h"
#include <fstream>
using namespace GPS;

// Tests created by James bray, N0731234

// create gpx log files
void createGPXlog(GridWorldRoute gwr, std::string fileName){
    // takes a grid world and returns string points
    std::string route = gwr.toGPX(true, fileName);

    // make file
    std::ofstream file;
    file.open(fileName); // create file with name
    file << route; // push route points into file
    file.close(); // close file
}

BOOST_AUTO_TEST_SUITE(Route_maxLatitude)

BOOST_AUTO_TEST_CASE(origin_point){
    // test for just a single point located on the origin

    std::string filename = "maxLat_single_point-N0731234.gpx";
    GridWorldRoute gwr = GridWorldRoute("M");
    createGPXlog(gwr,filename);
    Route route = Route(LogFiles::logsDir+filename,true);
    BOOST_CHECK_EQUAL(route.maxLatitude(),0);
}

BOOST_AUTO_TEST_CASE(single_point){
    // test for a single point that is not the origin

    std::string filename = "maxLat_single_point-N0731234.gpx";
    GridWorldRoute gwr = GridWorldRoute("A");
    createGPXlog(gwr,filename);
    Route route = Route(LogFiles::logsDir+filename,true);
    BOOST_CHECK_EQUAL(route.maxLatitude(),1.79964);
}

BOOST_AUTO_TEST_CASE(multiple_points){
    // test for multiple points on the gridworld

    std::string filename = "maxaLat_multiple_points-N0731234.gpx";
    GridWorldRoute gwr = GridWorldRoute("MHC");
    createGPXlog(gwr,filename);
    Route route = Route(LogFiles::logsDir+filename,true);
    BOOST_CHECK_EQUAL(route.maxLatitude(),1.79964);
}

BOOST_AUTO_TEST_CASE(circular_route){
    // test for max latitude on a circual route
    std::string filename = "maxLat_circular_route-N0731234.gpx";
    GridWorldRoute gwr = GridWorldRoute("PFHRP");
    createGPXlog(gwr, filename);
    Route route = Route(LogFiles::logsDir+filename,true);
    BOOST_CHECK_EQUAL(route.maxLatitude(),0.89982);
}


BOOST_AUTO_TEST_SUITE_END();

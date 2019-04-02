#include <boost/test/unit_test.hpp>
#include "position.h"
#include "../../headers/route.h"
#include "logs.h"
#include "../../headers/gridworld_route.h"
#include <fstream>
using namespace GPS;

// Tests created by James bray, N0731234

// create gpx log files
void createGPXlog(GridWorldRoute gwr, std::string fileName){
    fileName+="-N0731234.gpx";
    // takes a grid world and returns string points
    std::string route = gwr.toGPX(true, fileName);

    // make file
    std::ofstream file;
    file.open(fileName); // create file with name
    file << route; // push route points into file
    file.close(); // close file
}

BOOST_AUTO_TEST_SUITE(Route_maxLatitude)

BOOST_AUTO_TEST_CASE(expected_max){
    std::string filename = "standardRoute-N0731234.gpx";
    // create new GPX data
    GridWorldRoute gwr = GridWorldRoute("M"); // just one point on defualt earth
    createGPXlog(gwr, filename);
    Route route = Route(LogFiles::logsDir+filename,true);
    //BOOST_AUTO_TEST_CASE(route.maxLatitude(),);
}

//BOOST_AUTO_TEST_CASE(no_data){
//    std::string filename = "";
//    GridWorldRoute gwr = GridWorldRoute()
//    Route route = Route(LogFiles::logsDir+filename, true);
//    BOOST_TEST_MESSAGE(route.maxLatitude());
//}

BOOST_AUTO_TEST_CASE(null_position_list)
{
    // check to see if Null values are handled
}

BOOST_AUTO_TEST_CASE(incorrect_data)
{
    // check
}


BOOST_AUTO_TEST_SUITE_END();

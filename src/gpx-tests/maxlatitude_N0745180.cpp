#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"
#include "gridworld_route.h"
#include "gridworld.h"
#include <fstream>

using namespace GPS;

// Software Engineering Task 4 - Alexander Cain N0745180

std::string NTU_ID = "N0745180";


// GPX log file created

std::string GPX_Generated_Logs(std::string file, GridWorldRoute route)
{
    std::string fileName = "maxlatitude_"+ NTU_ID +"_" + file + ".gpx";

    std::ofstream GPXFile(GPS::LogFiles::GPXRoutesDir + file);

    GPXFile << route.toGPX(true, file);
    GPXFile.close();

    return fileName;
}


BOOST_AUTO_TEST_SUITE(Route_maxLatitude_N0745180)

const degrees current_value = 0.179964;
const degrees current_value_2 = 1.79964;
const degrees percentage_acc = 0.1;

// Test to see if the correct latitude is selected from a single point
BOOST_AUTO_TEST_CASE(single_Point)
{

    GridWorldRoute routeLog = GridWorldRoute("A");
    Route route = Route(LogFiles::GPXRoutesDir + "A.gpx", true);
    BOOST_CHECK_CLOSE(route.maxLatitude(), current_value, percentage_acc);

}


// Test to see if the correct latitude is selected from a multiple points with the same lattitude
BOOST_AUTO_TEST_CASE( matching_lat)
{

    GridWorldRoute routeLog = GridWorldRoute("MN");
    Route route = Route(LogFiles::GPXRoutesDir + "AB.gpx",true);
    BOOST_CHECK_CLOSE( route.maxLatitude(), current_value, percentage_acc);

}

// Test to see if the correct latitude is selected from a multiple points with the negative lattitude
BOOST_AUTO_TEST_CASE(negative_latitude)
{

    GridWorldRoute routeLog = GridWorldRoute("RW");
    Route route = Route(LogFiles::GPXRoutesDir + "RW.gpx",true);
    BOOST_CHECK_CLOSE( route.maxLatitude(), -current_value, percentage_acc);

}

// Test to see if the correct latitude is selected from a multiple points with the positives and negative lattitudes
BOOST_AUTO_TEST_CASE(neg_pos_latitude)
{

    GridWorldRoute routeLog = GridWorldRoute("MRH");
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx",true);
    BOOST_CHECK_CLOSE( route.maxLatitude(), current_value_2, percentage_acc);

}

// Test to see if the correct latitude is selected from a point with the zero lattitude
BOOST_AUTO_TEST_CASE(zero_latitude)
{

    GridWorldRoute routeLog = GridWorldRoute("M");
    Route route = Route(LogFiles::GPXRoutesDir + "M.gpx",true);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 0);

}

BOOST_AUTO_TEST_SUITE_END()

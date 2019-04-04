#include <boost/test/unit_test.hpp>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "logs.h"
#include "types.h"
#include "route.h"
#include "geometry.h"
#include "earth.h"
#include "gridworld_route.h"

using namespace GPS;

//A function to generate the gpx log files.
std::string generate_gpx_file(std::string fileName, GridWorldRoute routeName)
{
    std::string appendedFileName = fileName + "_N0774756.gpx";
    std::string gpxFileData = routeName.toGPX(true, fileName);
    std::ofstream gpxFile(LogFiles::GPXRoutesDir + appendedFileName);
    gpxFile << gpxFileData;
    gpxFile.close();
    return appendedFileName;
}

BOOST_AUTO_TEST_SUITE( Route_maxElevation_N0774756 )

const bool isFileName = true;

//Check for ZERO in gpx file for absent verticalGridUnit
BOOST_AUTO_TEST_CASE( max_ele_check_zero )
{
    //Missing verticalGridUnit argument take default 0 as elevation
    GridWorldRoute routeName = GridWorldRoute("AKR", GridWorld(Earth::Pontianak,3000));

    Route route = Route(LogFiles::GPXRoutesDir + generate_gpx_file("max_ele_check_zero", routeName),isFileName);

    BOOST_CHECK_EQUAL( route.maxElevation(), 0 );
}

//Check correct max ele when all values are positive
BOOST_AUTO_TEST_CASE( max_ele_all_positive )
{
    GridWorldRoute routeName = GridWorldRoute("KR", GridWorld(Earth::CityCampus,1000,-500));

    Route route = Route(LogFiles::GPXRoutesDir + generate_gpx_file("max_ele_all_positive", routeName),isFileName);

    BOOST_CHECK_EQUAL( route.maxElevation(), 1053);
}

//Check correct max ele when all values are negative
BOOST_AUTO_TEST_CASE( max_ele_all_negative )
{
    GridWorldRoute routeName = GridWorldRoute("KN", GridWorld(Earth::CityCampus,1000,500));

    Route route = Route(LogFiles::GPXRoutesDir + generate_gpx_file("max_ele_all_negative", routeName),isFileName);

    BOOST_CHECK_EQUAL( route.maxElevation(), -447);
}

//Check correct max ele when there are positive and negative values.
BOOST_AUTO_TEST_CASE( max_ele_both_positive_negative )
{
    GridWorldRoute routeName = GridWorldRoute("AMN", GridWorld(Earth::CityCampus,1000,500));

    Route route = Route(LogFiles::GPXRoutesDir + generate_gpx_file("max_ele_both_positive_negative", routeName),isFileName);

    BOOST_CHECK_EQUAL( route.maxElevation(), 53);
}

//Check for duplicate values in a file
BOOST_AUTO_TEST_CASE( max_ele_when_duplicate )
{
    GridWorldRoute routeName = GridWorldRoute("ANPS", GridWorld(Earth::CliftonCampus,1000,-250));

    Route route = Route(LogFiles::GPXRoutesDir + generate_gpx_file("max_ele_when_duplicate", routeName),isFileName);

    BOOST_CHECK_EQUAL( route.maxElevation(), 558);
}


//Check for ascending values in a file
BOOST_AUTO_TEST_CASE( max_ele_when_ascending)
{
    GridWorldRoute routeName = GridWorldRoute("MSP", GridWorld(Earth::CliftonCampus,1000,-250));

    Route route = Route(LogFiles::GPXRoutesDir + generate_gpx_file("max_ele_when_ascending", routeName),isFileName);

    BOOST_CHECK_EQUAL( route.maxElevation(), 558);
}

//Check for descending values in a file
BOOST_AUTO_TEST_CASE( max_ele_when_descending)
{
    GridWorldRoute routeName = GridWorldRoute("MSP", GridWorld(Earth::CliftonCampus,1000,450));

    Route route = Route(LogFiles::GPXRoutesDir + generate_gpx_file("max_ele_when_descending", routeName),isFileName);

    BOOST_CHECK_EQUAL( route.maxElevation(), 58);
}

//check max elevation when large dataset
BOOST_AUTO_TEST_CASE( max_ele_large_dataset )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 505);
}



BOOST_AUTO_TEST_SUITE_END()

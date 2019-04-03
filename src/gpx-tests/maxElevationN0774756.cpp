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

BOOST_AUTO_TEST_SUITE_END()

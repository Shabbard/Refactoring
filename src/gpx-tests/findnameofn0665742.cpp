#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "types.h"
#include "geometry.h"
#include "earth.h"
#include "gridworld_route.h"
#include <stdexcept>
#include <iostream>
#include <fstream>



//Function to build GPX file
std::string BuildGPXFile(std::string name, GridWorldRoute routePoint)
{
    std::string NewFile = name + "N0665742.gpx";
    std::string gpxData = routePoint.toGPX(true, name);
    std::ofstream gpxFile(LogFiles::GPXRoutesDir + NewFile);
    gpxFile << gpxData;
    gpxFile.close();
    return NewFile;
}


using namespace GPS;


BOOST_AUTO_TEST_SUITE(route_findnameofn0665742)

const bool isFileName = true;
const metres horizontalGridUnit = 100000;


// Find the name of a route point.
// Throws a std::out_of_range exception if that Position is not within "granularity" of any stored route points.


//Test to check that the fuction can find the postion of a point with all positive value of Latitude, Longitude and elevation in the GPX log file.
BOOST_AUTO_TEST_CASE(PositionWithPositiveValue)
{
    Route route = Route(LogFiles::GPXRoutesDir+ "N0665742-PositiveValue.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.findNameOf(Position(0.089982,109.232,0.000000)),"T");
}

//Test to check that the fuction can find the postion of a point with all negative value of Latitude, Longitude and elevation in the GPX log file.
BOOST_AUTO_TEST_CASE(PositionWithNegativeValue)
{
    Route route = Route(LogFiles::GPXRoutesDir+ "N0665742-NegativeValue.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.findNameOf(Position(-0.89982,-1.79662,-40000.000000)),"N");
}

//Test to check that the fuction can find the postion of a point with both Positive and Negative value in the GPX log file.
BOOST_AUTO_TEST_CASE(PositionWithPositiveAndNegativeValue)
{
    Route route = Route(LogFiles::GPXRoutesDir+ "N0665742.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.findNameOf(Position(1.79964,-1.79662,-40000.000000)),"N");
}

//Test to check the function throw out_of_range exception if that Position is not within "granularity" of any stored route points.
BOOST_AUTO_TEST_CASE(NonExistantPosition)
{
    const metres granularity = horizontalGridUnit / 10;
    Route route = Route(LogFiles::GPXRoutesDir + "N0665742.gpx", isFileName, granularity);
    BOOST_CHECK_THROW( route.findNameOf(Position(0,0,0.000000)), std::out_of_range);
}


//Test to check that the fuction can find the multiple postion with same positive value of Latitude, Longitude and elevation in the GPX log file.
BOOST_AUTO_TEST_CASE(MultiplePositionWithSamePositiveValue)
{

    GridWorldRoute routePoint = GridWorldRoute("GGI",GridWorld(Earth::CliftonCampus,horizontalGridUnit)):
    Route route = Route(LogFiles::GPXRoutesDir+ BuildGPXFile( "N0665742-SamePositiveValue", routePoint), isFileName);
    BOOST_CHECK_EQUAL(route.findNameOf(Position(0.089982,109.232,0.000000)),"I");
}

//Test to check that the fuction can find the multiple postion with same Negative value of Latitude, Longitude and elevation in the GPX log file.
BOOST_AUTO_TEST_CASE(MultiplePositionWithSameNegativeValue)
{

    GridWorldRoute routePoint = GridWorldRoute("VVX",GridWorld(Earth::CliftonCampus,horizontalGridUnit)):
    Route route = Route(LogFiles::GPXRoutesDir+ BuildGPXFile( "N0665742-SameNegativeValue", routePoint), isFileName);
    BOOST_CHECK_EQUAL(route.findNameOf(Position(-0.89982,-1.79662,-40000.000000)),"V");
}


//Test to check that the fuction can find the multiple postion with same Positive and Negative value of Latitude, Longitude and elevation in the GPX log file.
BOOST_AUTO_TEST_CASE(MultiplePositionWithSamePositiveAndNegativeValue)
{

    GridWorldRoute routePoint = GridWorldRoute("LLY",GridWorld(Earth::CliftonCampus,horizontalGridUnit)):
    Route route = Route(LogFiles::GPXRoutesDir+ BuildGPXFile( "N0665742-SamePositiveAndNegativeValue", routePoint), isFileName);
    BOOST_CHECK_EQUAL(route.findNameOf(Position(1.79964,-1.79662,-40000.000000)),"Y");
}

//Test to check the function throw out_of_range exception if that Position don't exist.
BOOST_AUTO_TEST_CASE(NonExistingGridPosition)
{
    GridWorldRoute routePoint = GridWorldRoute("DCD",GridWorld()):
    Route route = Route(LogFiles::GPXRoutesDir + "N0665742-SameZeroValue", isFileName, granularity);
    BOOST_CHECK_THROW( route.findNameOf(Position(0,0,0.000000)), std::out_of_range);
}


BOOST_AUTO_TEST_SUITE_END()

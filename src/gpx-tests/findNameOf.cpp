#include <boost/test/unit_test.hpp>

#include <fstream>
#include "logs.h"
#include "route.h"
#include "earth.h"
#include "gridworld_route.h"
#include "findNameOfGPXGenerator.cpp"

//N0741707

using namespace GPS;

BOOST_AUTO_TEST_SUITE(Route_findNameOf)

const bool isFileName = true;
const metres HORIZONTAL_GRID_UNIT = 1000;

/*
Description: Checks that the findNameOf function is able to discover the existance of a single position 
in which all values are positive within the GPX log file.
*/

BOOST_AUTO_TEST_CASE(CanFindASignularPositiveExistingPosition)
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.findNameOf(Position(0.179964, 109.142, 0.000000)), "A");
}

/*
Description: Checks that the findNameOf function is able to discover the existance of a single position 
in which all values are negative within the GPX log file.
*/

BOOST_AUTO_TEST_CASE(CanFindASignularNegativeExistingPosition)
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.findNameOf(Position(-0.89982, -0.898312, -20000.000000)), "Q");
}

/*
Description: Checks that the findNameOf function is able to discover the existance of a single position 
in which some values are positive and others are negative within the GPX log file.
*/

BOOST_AUTO_TEST_CASE(CanFindASignularMixedExistingPosition)
{
    GridWorldRoute routeData = GridWorldRoute("M", GridWorld(Earth::CliftonCampus, HORIZONTAL_GRID_UNIT));
    Route route = Route(LogFiles::GPXRoutesDir + Generator::createGPXLog("N0741707-CanFindASignularMixedExistingPosition", routeData), isFileName);

    BOOST_CHECK_EQUAL(route.findNameOf(Position(52.91249953, -1.18402513, 58)), "M");
}

/*
Description: Checks that the findNameOf function is able to discover the existance of a single position 
in which all values are zeroed within the GPX log file.
*/

BOOST_AUTO_TEST_CASE(CanFindASignularZeroExistingPosition)
{
    GridWorldRoute routeData = GridWorldRoute("A", GridWorld(Earth::EquatorialMeridian, 0, 0));
    Route route = Route(LogFiles::GPXRoutesDir + Generator::createGPXLog("N0741707-CanFindASignularZeroExistingPosition", routeData), isFileName);

    BOOST_CHECK_EQUAL(route.findNameOf(Position(0, 0, 0.0000)), "A");
}

/*
Description: Checks that the findNameOf function is able to discover the existance of a position that has multiple definitions and 
where all values are positive within the GPX log file.
*/

BOOST_AUTO_TEST_CASE(CanFindAnExistingPositivePositionWithDuplicateEntries)
{
    GridWorldRoute routeData = GridWorldRoute("BBEE", GridWorld(Earth::NorthPole, HORIZONTAL_GRID_UNIT));
    Route route = Route(LogFiles::GPXRoutesDir + Generator::createGPXLog("N0741707-CanFindAnExistingPositivePositionWithDuplicateEntries", routeData), isFileName);

    BOOST_CHECK_EQUAL(route.findNameOf(Position(89.982, 49.5625, 58.000000)), "B");
}

/*
Description: Checks that the findNameOf function is able to discover the existance of a position that has multiple definitions and 
where all values are negative within the GPX log file.
*/

BOOST_AUTO_TEST_CASE(CanFindAnExistingNegativePositionWithDuplicateEntries)
{
    GridWorldRoute routeData = GridWorldRoute("MMUU", GridWorld(Position(-1.000,-1.000,-1.000), HORIZONTAL_GRID_UNIT));
    Route route = Route(LogFiles::GPXRoutesDir + Generator::createGPXLog("N0741707-CanFindAnExistingNegativePositionWithDuplicateEntries", routeData), isFileName);

    BOOST_CHECK_EQUAL(route.findNameOf(Position(-1.000, -1.000, -1.000)), "M");
}

/*
Description: Checks that the findNameOf function is able to discover the existance of a position that has multiple definitions and 
where some values are positive and others are negative within the GPX log file.
*/

BOOST_AUTO_TEST_CASE(CanFindAnExistingMixedPositionWithDuplicateEntries)
{
    GridWorldRoute routeData = GridWorldRoute("MMUU", GridWorld(Earth::CliftonCampus, HORIZONTAL_GRID_UNIT));
    Route route = Route(LogFiles::GPXRoutesDir + Generator::createGPXLog("N0741707-CanFindAnExistingMixedPositionWithDuplicateEntries", routeData), isFileName);

    BOOST_CHECK_EQUAL(route.findNameOf(Position(52.91249953, -1.18402513, 58)), "M");
}

/*
Description: Checks that the findNameOf function is able to discover the existance of a position that has multiple definitions and 
where all values are zeroed within the GPX log file.
*/

BOOST_AUTO_TEST_CASE(CanFindAnExistingZeroPositionWithDuplicates)
{
    GridWorldRoute routeData = GridWorldRoute("AABB", GridWorld(Earth::EquatorialMeridian, 0, 0));
    Route route = Route(LogFiles::GPXRoutesDir + Generator::createGPXLog("N0741707-CanFindAnExistingZeroPositionWithDuplicates", routeData), isFileName);

    BOOST_CHECK_EQUAL(route.findNameOf(Position(0, 0, 0.0000)), "A");
}

/*
Description: Checks that the findNameOf function throws an "out_of_range" exception when a position cannot be found.
*/

BOOST_AUTO_TEST_CASE(ThrowsOutOfRangeWhenAPositionIsNotFound)
{
    GridWorldRoute routeData = GridWorldRoute("ABCD", GridWorld());
    Route route = Route(LogFiles::GPXRoutesDir + Generator::createGPXLog("N0741707-ThrowsOutOfRangeWhenAPositionIsNotFound", routeData), isFileName);

    BOOST_CHECK_THROW(route.findNameOf(Position(0.0000, 0.0000, 0.0000)), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
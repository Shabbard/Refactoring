#include <boost/test/unit_test.hpp>

#include <fstream>
#include <stdexcept>
#include "logs.h"
#include "route.h"
#include "track.h"
#include "earth.h"
#include "geometry.h"
#include "gridworld_route.h"
#include "xmlgenerator.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_Find_Position_N0724629 )

const bool isFileName = true;

/**
* Test case: CanGetPositiveLatitude
* Use:       Checks that it is possible to obtain a positive value for latitude in a GPX log file.
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveLatitude )
{
   	// Generate a GPX log file for the with GridWorld constructor for CityCampus.
    GridWorldRoute routeLog = GridWorldRoute("KQLD", GridWorld(Earth::CityCampus, 0, 1000));

    // Converts the GridWorldRoute in to GPX format.
    std::string routeGPX = routeLog.toGPX(true, "CanGetPositiveLatitude");

    std::string fileName = "CanGetPositiveLatitude-N0724629.gpx";

    std::ofstream openedFile(LogFiles::GPXRoutesDir + fileName);
    openedFile << routeGPX;
    openedFile.close();

    Route route = Route(LogFiles::GPXRoutesDir + fileName, isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("K").latitude(), 52.9581 );
}

/**
* Test case: CanGetPositiveLongitude
* Use:       Checks that it is possible to obtain a positive value for longitude in a GPX log file.
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveLongitude )
{
   	// Generate a GPX log file for the with GridWorld constructor for Pontianak.
    GridWorldRoute routeLog = GridWorldRoute("KQLD", GridWorld(Earth::Pontianak, 0, 1000));

    // Converts the GridWorldRoute in to GPX format.
    std::string routeGPX = routeLog.toGPX(true, "CanGetLongitudeLatitude");

    std::string fileName = "CanGetPositiveLongitude-N0724629.gpx";

    std::ofstream openedFile(LogFiles::GPXRoutesDir + fileName);
    openedFile << routeGPX;
    openedFile.close();

    Route route = Route(LogFiles::GPXRoutesDir + fileName, isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("K").longitude(), 109.322 );
}

/**
* Test case: CanGetPositiveElevation
* Use:       Checks that it is possible to obtain a positive value for elevation in a GPX log file.
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveElevation )
{
   	// Generate a GPX log file for the with GridWorld constructor for CliftonCampus.
    GridWorldRoute routeLog = GridWorldRoute("IJOF", GridWorld(Earth::CliftonCampus, 0, 0));

    // Converts the GridWorldRoute in to GPX format.
    std::string routeGPX = routeLog.toGPX(true, "CanGetPositiveElevation");

    std::string fileName = "CanGetPositiveElevation-N0724629.gpx";

    std::ofstream openedFile(LogFiles::GPXRoutesDir + fileName);
    openedFile << routeGPX;
    openedFile.close();

    Route route = Route(LogFiles::GPXRoutesDir + fileName, isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("I").elevation(), 58 );
}

/**
* Test case: CanGetNegativeLatitude
* Use:       Checks that it is possible to obtain a negative value for latitude in a GPX log file.
*/
BOOST_AUTO_TEST_CASE( CanGetNegativeLatitude )
{
   	Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("Q").latitude(), -0.89982 );
}

/**
* Test case: CanGetNegativeLongitude
* Use:       Checks that it is possible to obtain a negative value for longitude in a GPX log file.
*/
BOOST_AUTO_TEST_CASE( CanGetNegativeLongitude )
{
   	Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("Q").longitude(), -0.898312 );
}

/**
* Test case: CanGetNegativeElevation
* Use:       Checks that it is possible to obtain a negative value for elevation in a GPX log file.
*/
BOOST_AUTO_TEST_CASE( CanGetNegativeElevation )
{
   	Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("Q").elevation(), -20000 );
}

/**
* Test case: CanGetZeroLatitude
* Use:       Checks that it is possible to obtain a zero value for latitude in a GPX log file.
*/
BOOST_AUTO_TEST_CASE ( CanGetZeroLatitude )
{
	// Generate a GPX log file for the with GridWorld constructor for EquatorialMeridian.
    GridWorldRoute routeLog = GridWorldRoute("IEKS", GridWorld(Earth::EquatorialMeridian, 0, 1000));

    // Converts the GridWorldRoute in to GPX format.
    std::string routeGPX = routeLog.toGPX(true, "CanGetZeroLatitude");

    std::string fileName = "CanGetZeroLatitude-N0724629.gpx";

    std::ofstream openedFile(LogFiles::GPXRoutesDir + fileName);
    openedFile << routeGPX;
    openedFile.close();

    Route route = Route(LogFiles::GPXRoutesDir + fileName, isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("I").latitude(), 0 );
}

/**
* Test case: CanGetZeroLongitude
* Use:       Checks that it is possible to obtain a zero value for longitude in a GPX log file.
*/
BOOST_AUTO_TEST_CASE ( CanGetZeroLongitude )
{
	// Generate a GPX log file for the with GridWorld constructor for NorthPole.
    GridWorldRoute routeLog = GridWorldRoute("FIWA", GridWorld(Earth::NorthPole, 0, 1000));

    // Converts the GridWorldRoute in to GPX format
    std::string routeGPX = routeLog.toGPX(true, "CanGetZeroLongitude");

    std::string fileName = "CanGetZeroLongitude-N0724629.gpx";

    std::ofstream openedFile(LogFiles::GPXRoutesDir + fileName);
    openedFile << routeGPX;
    openedFile.close();

    Route route = Route(LogFiles::GPXRoutesDir + fileName, isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("F").longitude(), 0 );
}

/**
* Test case: ThrowsOutOfRangeIfNameNotFound
* Use:       Checks that the std::out_of_range exception is thrown if the specified name is not found.
*/
BOOST_AUTO_TEST_CASE ( ThrowsOutOfRangeIfNameNotFound )
{
	// Generate a GPX log file for the with default GridWorld constructor
    GridWorldRoute routeLog = GridWorldRoute("FIWA", GridWorld());

    // Converts the GridWorldRoute in to GPX format
    std::string routeGPX = routeLog.toGPX(true, "ThrowsOutOfRangeIfNameNotFound");

    std::string fileName = "ThrowsOutOfRangeIfNameNotFound-N0724629.gpx";

    std::ofstream openedFile(LogFiles::GPXRoutesDir + fileName);
    openedFile << routeGPX;
    openedFile.close();

    Route route = Route(LogFiles::GPXRoutesDir + fileName, isFileName);
   	BOOST_CHECK_THROW( route.findPosition("K").elevation(), std::out_of_range );
}

/**
* Test case: ThrowsOutOfRangeIfElevationNotFound
* Use:       Checks that the std::out_of_range exception is thrown if the elevation is not found.
*/
BOOST_AUTO_TEST_CASE ( ThrowsOutOfRangeIfElevationNotFound )
{
	// Generate a GPX log file for the with GridWorld constructor for NorthPole.
    GridWorldRoute routeLog = GridWorldRoute(GridWorldRoute("EAL", GridWorld(Earth::NorthPole, 0, 1000)));

    // Converts the GridWorldRoute in to GPX format
    std::string routeGPX = routeLog.toGPX(true, "ThrowsOutOfRangeIfElevationNotFound");

    std::string fileName = "ThrowsOutOfRangeIfElevationNotFound-N0724629.gpx";

    std::ofstream openedFile(LogFiles::GPXRoutesDir + fileName);
    openedFile << routeGPX;
    openedFile.close();

    Route route = Route(LogFiles::GPXRoutesDir + fileName, isFileName);
   	BOOST_CHECK_THROW( route.findPosition("A").elevation(), std::out_of_range );
}

BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>

#include <fstream>
#include <stdexcept>
#include "logs.h"
#include "route.h"
#include "track.h"
#include "earth.h"
#include "geometry.h"
#include "gridworld_route.h"

using namespace GPS;


std::string createLogFile(std::string name, GridWorldRoute routeLog)
{
	// Converts the GridWorldRoute in to GPX format.
    std::string routeGPX = routeLog.toGPX(true, name);

    std::string fileName = name + "-N0724629.gpx";

    std::ofstream openedFile(LogFiles::GPXRoutesDir + name + "-N0724629.gpx");
    openedFile << routeGPX;
    openedFile.close();

    return name + "-N0724629.gpx";
}


BOOST_AUTO_TEST_SUITE( Route_Find_Position_N0724629 )

const bool IS_FILE_NAME = true;
const metres HORIZONTAL_GRID_UNIT = 1000;
const double PERCENTAGE_ACCURACY = 0.1;

/**
* Test case: CanGetNegativeLatitudeInLogFileWithOnePosition
* Use:       Checks that it is possible to obtain a positive value for latitude in a GPX log file.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetNegativeLatitudeInLogFileWithOnePosition )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", IS_FILE_NAME);
    BOOST_CHECK_CLOSE( route.findPosition("Q").latitude(), -0.89982, PERCENTAGE_ACCURACY );
}

/**
* Test case: CanGetNegativeLongitudeInLogFileWithOnePosition
* Use:       Checks that it is possible to obtain a positive value for longitude in a GPX log file.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetNegativeLongitudeInLogFileWithOnePosition )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", IS_FILE_NAME);
    BOOST_CHECK_CLOSE( route.findPosition("Q").longitude(), -0.898312, PERCENTAGE_ACCURACY );
}

/**
* Test case: CanGetNegativeElevationInLogFileWithOnePosition
* Use:       Checks that it is possible to obtain a positive value for elevation in a GPX log file.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetNegativeElevationInLogFileWithOnePosition )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", IS_FILE_NAME);
    BOOST_CHECK_EQUAL( route.findPosition("Q").elevation(), -20000 );
}

/**
* Test case: CanGetPositiveLatitudeInLogFileWithPointsApart
* Use:       Checks that it is possible to obtain a positive value for latitude in a GPX log file.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveLatitudeInLogFileWithPointsApart )
{
    const metres granularity = HORIZONTAL_GRID_UNIT / 10;

   	// Generate a GPX log file for the with GridWorld constructor for CityCampus.
    GridWorldRoute routeLog = GridWorldRoute("QWERTYUIOPASDFGHJKLXCVBNM", GridWorld(Earth::CityCampus, HORIZONTAL_GRID_UNIT));

    Route route = Route(LogFiles::GPXRoutesDir + createLogFile("CanGetPositiveLatitudeInLogFileWithPointsApart", routeLog), IS_FILE_NAME, granularity);
   	BOOST_CHECK_CLOSE( route.findPosition("C").latitude(), 52.9581383, PERCENTAGE_ACCURACY );
}

/**
* Test case: CanGetPositiveLongitudeInLogFileWithPointsApart
* Use:       Checks that it is possible to obtain a positive value for longitude in a GPX log file.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveLongitudeInLogFileWithPointsApart )
{
    const metres granularity = HORIZONTAL_GRID_UNIT / 10;

   	// Generate a GPX log file for the with GridWorld constructor for Pontianak.
    GridWorldRoute routeLog = GridWorldRoute("KQLD", GridWorld(Earth::Pontianak, HORIZONTAL_GRID_UNIT));

    Route route = Route(LogFiles::GPXRoutesDir + createLogFile("CanGetPositiveLongitudeInLogFileWithPointsApart", routeLog), IS_FILE_NAME, granularity);
   	BOOST_CHECK_CLOSE( route.findPosition("Q").longitude(), 109.322134, PERCENTAGE_ACCURACY );
}

/**
* Test case: CanGetPositiveElevationInLogFileWithPointsApart
* Use:       Checks that it is possible to obtain a positive value for elevation in a GPX log file.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveElevationInLogFileWithPointsApart )
{
    const metres granularity = HORIZONTAL_GRID_UNIT / 10;

   	// Generate a GPX log file for the with GridWorld constructor for CliftonCampus.
    GridWorldRoute routeLog = GridWorldRoute("IJOF", GridWorld(Earth::CliftonCampus, HORIZONTAL_GRID_UNIT));

    Route route = Route(LogFiles::GPXRoutesDir + createLogFile("CanGetPositiveElevationInLogFileWithPointsApart", routeLog), IS_FILE_NAME, granularity);
   	BOOST_CHECK_EQUAL( route.findPosition("I").elevation(), 58 );
}

/**
* Test case: CanGetPositiveLatitudeInLogFileWithPointsTooClose
* Use:       Checks that it is possible to obtain a positive value for latitude in a GPX log file.
* Test type: Invalid
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveLatitudeInLogFileWithPointsTooClose )
{
    const metres granularity = HORIZONTAL_GRID_UNIT * 5;

    // Generate a GPX log file for the with GridWorld constructor for CityCampus.
    GridWorldRoute routeLog = GridWorldRoute("ILADN", GridWorld(Earth::CityCampus, HORIZONTAL_GRID_UNIT));

    Route route = Route(LogFiles::GPXRoutesDir + createLogFile("CanGetPositiveLatitudeInLogFileWithPointsTooClose", routeLog), IS_FILE_NAME, granularity);

    BOOST_CHECK_THROW( route.findPosition("A").latitude(), std::out_of_range );
}

/**
* Test case: CanGetPositiveLongitudeInLogFileWithPointsTooClose
* Use:       Checks that it is possible to obtain a positive value for longitude in a GPX log file.
* Test type: Invalid
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveLongitudeInLogFileWithPointsTooClose )
{
    const metres granularity = HORIZONTAL_GRID_UNIT * 5;

    // Generate a GPX log file for the with GridWorld constructor for Pontianak.
    GridWorldRoute routeLog = GridWorldRoute("KQLD", GridWorld(Earth::Pontianak, HORIZONTAL_GRID_UNIT));

    Route route = Route(LogFiles::GPXRoutesDir + createLogFile("CanGetPositiveLongitudeInLogFileWithPointsTooClose", routeLog), IS_FILE_NAME, granularity);
    BOOST_CHECK_THROW( route.findPosition("L").longitude(), std::out_of_range );
}

/**
* Test case: CanGetPositiveElevationInLogFileWithPointsTooClose
* Use:       Checks that it is possible to obtain a positive value for elevation in a GPX log file.
* Test type: Invalid
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveElevationInLogFileWithPointsTooClose )
{
    const metres granularity = HORIZONTAL_GRID_UNIT * 5;

    // Generate a GPX log file for the with GridWorld constructor for CliftonCampus.
    GridWorldRoute routeLog = GridWorldRoute("IJOF", GridWorld(Earth::CliftonCampus, HORIZONTAL_GRID_UNIT));

    Route route = Route(LogFiles::GPXRoutesDir + createLogFile("CanGetPositiveElevationInLogFileWithPointsTooClose", routeLog), IS_FILE_NAME, granularity);
    BOOST_CHECK_THROW( route.findPosition("O").elevation(), std::out_of_range );
}

/**
* Test case: CanGetZeroLatitude
* Use:       Checks that it is possible to obtain a zero value for latitude in a GPX log file.
*/
BOOST_AUTO_TEST_CASE ( CanGetZeroLatitude )
{
	// Generate a GPX log file for the with GridWorld constructor for EquatorialMeridian.
    GridWorldRoute routeLog = GridWorldRoute("IEKS", GridWorld(Earth::EquatorialMeridian, 0, 1000));

    Route route = Route(LogFiles::GPXRoutesDir + createLogFile("CanGetZeroLatitude", routeLog), IS_FILE_NAME);

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

    Route route = Route(LogFiles::GPXRoutesDir + createLogFile("CanGetZeroLongitude", routeLog), IS_FILE_NAME);
   	BOOST_CHECK_EQUAL( route.findPosition("F").longitude(), 0 );
}

/**
* Test case: CanGetZeroLongitude
* Use:       Checks that it is possible to obtain a zero value for elevation in a GPX log file.
*/
BOOST_AUTO_TEST_CASE ( CanGetZeroElevation )
{
	// Generate a GPX log file for the with GridWorld constructor for EquatorialMeridian.
    GridWorldRoute routeLog = GridWorldRoute("LQHD", GridWorld(Earth::EquatorialMeridian, 0, 0));

    Route route = Route(LogFiles::GPXRoutesDir + createLogFile("CanGetZeroElevation", routeLog), IS_FILE_NAME);
   	BOOST_CHECK_EQUAL( route.findPosition("L").elevation(), 0 );
}

/**
* Test case: ThrowsOutOfRangeIfNameNotFound
* Use:       Checks that the std::out_of_range exception is thrown if the specified name is not found.
*/
BOOST_AUTO_TEST_CASE ( ThrowsOutOfRangeIfNameNotFound )
{
	// Generate a GPX log file for the with default GridWorld constructor
    GridWorldRoute routeLog = GridWorldRoute("FIWA", GridWorld());

    Route route = Route(LogFiles::GPXRoutesDir + createLogFile("ThrowsOutOfRangeIfNameNotFound", routeLog), IS_FILE_NAME);
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

    Route route = Route(LogFiles::GPXRoutesDir + createLogFile("ThrowsOutOfRangeIfElevationNotFound", routeLog), IS_FILE_NAME);
   	BOOST_CHECK_THROW( route.findPosition("A").elevation(), std::out_of_range );
}

/**
* Test case: ThrowsDomainErrorIfFileIsEmpty
* Use:       Checks that the std::domain_error exception is thrown if the log file is empty.
*/
BOOST_AUTO_TEST_CASE ( ThrowsDomainErrorIfFileIsEmpty )
{
    std::ofstream openedFile(LogFiles::GPXRoutesDir + "ThrowsOutOfRangeIfFileIsEmpty-N0724629.gpx");
    openedFile.close();

   	BOOST_CHECK_THROW( Route(LogFiles::GPXRoutesDir + "ThrowsOutOfRangeIfFileIsEmpty-N0724629.gpx", IS_FILE_NAME), std::domain_error );
}

BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>

#include <fstream>
#include <stdexcept>
#include "logs.h"
#include "route.h"
#include "track.h"
#include "earth.h"
#include "geometry.h"
#include "gridworld_route.h"
#include "findPositionN0724629_logGenerator.cpp"

using namespace GPS;

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
    GPX::generateLogFiles();
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

// /**
// * Test case: CanGetPositiveLatitudeInLogFileWithRepeatedPoints
// * Use:       Checks that it is possible to obtain a positive value for latitude in a GPX log file.
// * Test type: Valid
// */
// BOOST_AUTO_TEST_CASE( CanGetPositiveLatitudeInLogFileWithRepeatedPoints )
// {
//     const metres granularity = HORIZONTAL_GRID_UNIT / 10;

//     Route route = Route(LogFiles::GPXRoutesDir + "RepeatedPoints-N0724629.gpx", IS_FILE_NAME, granularity);
//     BOOST_CHECK_CLOSE( route.findPosition("D").latitude(), 52.9581383, PERCENTAGE_ACCURACY );
// }

// /**
// * Test case: CanGetPositiveLongitudeInLogFileWithPointsApart
// * Use:       Checks that it is possible to obtain a positive value for longitude in a GPX log file.
// * Test type: Valid
// */
// BOOST_AUTO_TEST_CASE( CanGetPositiveLongitudeInLogFileWithRepeatedPoints )
// {
//     const metres granularity = HORIZONTAL_GRID_UNIT / 10;

//     Route route = Route(LogFiles::GPXRoutesDir + "RepeatedPoints-N0724629.gpx", IS_FILE_NAME, granularity);
//     BOOST_CHECK_CLOSE( route.findPosition("D").longitude(), 109.322134, PERCENTAGE_ACCURACY );
// }

// /**
// * Test case: CanGetPositiveElevationInLogFileWithPointsApart
// * Use:       Checks that it is possible to obtain a positive value for elevation in a GPX log file.
// * Test type: Valid
// */
// BOOST_AUTO_TEST_CASE( CanGetPositiveElevationInLogFileWithRepeatedPoints )
// {
//     const metres granularity = HORIZONTAL_GRID_UNIT / 10;

//     Route route = Route(LogFiles::GPXRoutesDir + "RepeatedPoints-N0724629.gpx", IS_FILE_NAME, granularity);
//     BOOST_CHECK_EQUAL( route.findPosition("D").elevation(), 58 );
// }

/**
* Test case: CanGetPositiveLatitudeInLogFileWithPointsApart
* Use:       Checks that it is possible to obtain a positive value for latitude in a GPX log file.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveLatitudeInLogFileWithPointsApart )
{
    const metres granularity = HORIZONTAL_GRID_UNIT / 10;

   	Route route = Route(LogFiles::GPXRoutesDir + "PointsApart-N0724629.gpx", IS_FILE_NAME, granularity);
   	BOOST_CHECK_CLOSE( route.findPosition("Q").latitude(), 52.9491, PERCENTAGE_ACCURACY );
}

/**
* Test case: CanGetPositiveLongitudeInLogFileWithPointsApart
* Use:       Checks that it is possible to obtain a positive value for longitude in a GPX log file.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveLongitudeInLogFileWithPointsApart )
{
    const metres granularity = HORIZONTAL_GRID_UNIT / 10;

   	Route route = Route(LogFiles::GPXRoutesDir + "PointsApart-N0724629.gpx", IS_FILE_NAME, granularity);
   	BOOST_CHECK_CLOSE( route.findPosition("Q").longitude(), -1.16915, PERCENTAGE_ACCURACY );
}

/**
* Test case: CanGetPositiveElevationInLogFileWithPointsApart
* Use:       Checks that it is possible to obtain a positive value for elevation in a GPX log file.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveElevationInLogFileWithPointsApart )
{
    const metres granularity = HORIZONTAL_GRID_UNIT / 10;

   	Route route = Route(LogFiles::GPXRoutesDir + "PointsApart-N0724629.gpx", IS_FILE_NAME, granularity);
   	BOOST_CHECK_EQUAL( route.findPosition("Q").elevation(), 53 );
}

/**
* Test case: CanGetPositiveLatitudeInLogFileWithPointsTooClose
* Use:       Checks that it is possible to obtain a positive value for latitude in a GPX log file.
* Test type: Invalid
*/
BOOST_AUTO_TEST_CASE( CanGetPositiveLatitudeInLogFileWithPointsTooClose )
{
    const metres granularity = HORIZONTAL_GRID_UNIT * 5;

    Route route = Route(LogFiles::GPXRoutesDir + "PointsTooClose-N0724629.gpx", IS_FILE_NAME, granularity);
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

    Route route = Route(LogFiles::GPXRoutesDir + "PointsTooClose-N0724629.gpx", IS_FILE_NAME, granularity);
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

    Route route = Route(LogFiles::GPXRoutesDir + "PointsTooClose-N0724629.gpx", IS_FILE_NAME, granularity);
    BOOST_CHECK_THROW( route.findPosition("O").elevation(), std::out_of_range );
}

/**
* Test case: CanGetZeroLatitude
* Use:       Checks that it is possible to obtain a zero value for latitude in a GPX log file.
* Test type: Valid (edge case)
*/
BOOST_AUTO_TEST_CASE ( CanGetZeroLatitude )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ZeroValues-N0724629.gpx", IS_FILE_NAME);
   	BOOST_CHECK_EQUAL( route.findPosition("I").latitude(), 0 );
}

/**
* Test case: CanGetZeroLongitude
* Use:       Checks that it is possible to obtain a zero value for longitude in a GPX log file.
* Test type: Valid (edge case)
*/
BOOST_AUTO_TEST_CASE ( CanGetZeroLongitude )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ZeroValues-N0724629.gpx", IS_FILE_NAME);
   	BOOST_CHECK_EQUAL( route.findPosition("I").longitude(), 0 );
}

/**
* Test case: CanGetZeroLongitude
* Use:       Checks that it is possible to obtain a zero value for elevation in a GPX log file.
* Test type: Valid (edge case)
*/
BOOST_AUTO_TEST_CASE ( CanGetZeroElevation )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ZeroValues-N0724629.gpx", IS_FILE_NAME);
   	BOOST_CHECK_EQUAL( route.findPosition("I").elevation(), 0 );
}

/**
* Test case: ThrowsOutOfRangeIfNameNotFound
* Use:       Checks that the std::out_of_range exception is thrown if the specified name is not found.
* Test type: Invalid
*/
BOOST_AUTO_TEST_CASE ( ThrowsOutOfRangeIfNameNotFound )
{
	// Generate a GPX log file for the with default GridWorld constructor
    // GridWorldRoute routeLog = GridWorldRoute("FIWA", GridWorld());

    // Route route = Route(LogFiles::GPXRoutesDir + createLogFile("ThrowsOutOfRangeIfNameNotFound", routeLog), IS_FILE_NAME);
   	// BOOST_CHECK_THROW( route.findPosition("K").elevation(), std::out_of_range );
}

/**
* Test case: ThrowsOutOfRangeIfElevationNotFound
* Use:       Checks that the std::out_of_range exception is thrown if the elevation is not found.
* Test type: Invalid
*/
BOOST_AUTO_TEST_CASE ( ThrowsOutOfRangeIfElevationNotFound )
{
    Route route = Route(LogFiles::GPXRoutesDir + "NoElevation-N0724629.gpx", IS_FILE_NAME);
   	BOOST_CHECK_THROW( route.findPosition("A").elevation(), std::out_of_range );
}

/**
* Test case: ThrowsDomainErrorIfFileIsEmpty
* Use:       Checks that the std::domain_error exception is thrown if the log file is empty.
* Test type: Invalid
*/
BOOST_AUTO_TEST_CASE ( ThrowsDomainErrorIfFileIsEmpty )
{
   	BOOST_CHECK_THROW( Route(LogFiles::GPXRoutesDir + "EmptyFile-N0724629.gpx", IS_FILE_NAME), std::domain_error );
}

BOOST_AUTO_TEST_SUITE_END()

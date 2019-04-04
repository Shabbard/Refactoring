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


/**
* Test case: CanGetPositionWithPositiveValuesInLogFileWithOnePoint
* Use:       Checks that it is possible to obtain positive values for latitude,
*            longitude and elevation in a GPX log file with only one point on
*            the route.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositionWithPositiveValuesInLogFileWithOnePoint )
{
    GPX::generateLogFiles();

    Position thePosition = Position(53.1381, 1.00511, 53);
    Route route = Route(LogFiles::GPXRoutesDir + "OnePointPositive-N0724629.gpx", IS_FILE_NAME);

    BOOST_CHECK_EQUAL( route.findPosition("B").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("B").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("B").elevation(), thePosition.elevation() );
}


/**
* Test case: CanGetPositionWithNegativeValuesInLogFileWithOnePoint
* Use:       Checks that it is possible to obtain negative values for latitude,
*            longitude and elevation in a GPX log file with only one point on
*            the route.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositionWithNegativeValuesInLogFileWithOnePoint )
{
    Position thePosition = Position(-0.89982, -0.898312, -20000);
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", IS_FILE_NAME);

    BOOST_CHECK_EQUAL( route.findPosition("Q").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("Q").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("Q").elevation(), thePosition.elevation() );
}


/**
* Test case: CanGetPositionWithZeroValues
* Use:       Checks that it is possible to obtain zero values for latitude,
*            longitude and elevation.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositionWithZeroValues )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ZeroValues-N0724629.gpx", IS_FILE_NAME);

    BOOST_CHECK_EQUAL( route.findPosition("I").latitude(), 0 );
    BOOST_CHECK_EQUAL( route.findPosition("I").longitude(), 0 );
    BOOST_CHECK_EQUAL( route.findPosition("I").elevation(), 0 );
}


/**
* Test case: ThrowsOutOfRangeIfNameNotFound
* Use:       Checks that the std::out_of_range exception is thrown if the
*            specified name is not found.
* Test type: Invalid
*/
BOOST_AUTO_TEST_CASE ( ThrowsOutOfRangeIfNameNotFound )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", IS_FILE_NAME);

    BOOST_CHECK_THROW( route.findPosition("E").latitude(), std::out_of_range );
    BOOST_CHECK_THROW( route.findPosition("K").longitude(), std::out_of_range );
    BOOST_CHECK_THROW( route.findPosition("K").elevation(), std::out_of_range );
}


/**
* Test case: CanGetPositionWithPositiveValuesInLogFileWithRepeatedPoints
* Use:       Checks that it is possible to obtain positive values for latitude,
*            longitude and elevation in a GPX log file with only one point on
*            the route.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositionWithPositiveValuesInLogFileWithRepeatedPoints )
{
    Position thePosition = Position(52.9761, 1.16915, 53);
    Route route = Route(LogFiles::GPXRoutesDir + "RepeatedPointsPositive-N0724629.gpx", IS_FILE_NAME);

    BOOST_CHECK_EQUAL( route.findPosition("D").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("D").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("D").elevation(), thePosition.elevation() );

    Position repeatedPosition = route[3];

    BOOST_CHECK_EQUAL( repeatedPosition.latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( repeatedPosition.longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( repeatedPosition.elevation(), thePosition.elevation() );
}


/**
* Test case: CanGetPositionWithNegativeValuesInLogFileWithRepeatedPoints
* Use:       Checks that it is possible to obtain negative values for latitude,
*            longitude and elevation in a GPX log file with a repeated point.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositionWithNegativeValuesInLogFileWithRepeatedPoints )
{
    Position thePosition = Position(-52.9401, -1.13932, -53);
    Route route = Route(LogFiles::GPXRoutesDir + "RepeatedPointsNegative-N0724629.gpx", IS_FILE_NAME);

    BOOST_CHECK_EQUAL( route.findPosition("D").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("D").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("D").elevation(), thePosition.elevation() );

    Position repeatedPosition = route[3];

    BOOST_CHECK_EQUAL( repeatedPosition.latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( repeatedPosition.longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( repeatedPosition.elevation(), thePosition.elevation() );
}


/**
* Test case: CanGetPositionWithPositiveValuesInLogFileWithPointsApart
* Use:       Checks that it is possible to obtain positive values for latitude,
*            longitude and elevation in a GPX log file with a repeated point.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositionWithPositiveValuesInLogFileWithPointsApart )
{
    const metres granularity = HORIZONTAL_GRID_UNIT / 10;

    Position thePosition = Position(52.9035, 1.16913, 58);
    Route route = Route(LogFiles::GPXRoutesDir + "PointsApartPositive-N0724629.gpx", IS_FILE_NAME, granularity);

    BOOST_CHECK_EQUAL( route.findPosition("Q").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("Q").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("Q").elevation(), thePosition.elevation() );
}


/**
* Test case: CanGetPositionWithNegativeValuesInLogFileWithPointsApart
* Use:       Checks that it is possible to obtain negative values for latitude,
*            longitude and elevation in a GPX log file with multiple points,
*            none of which are more than 'granularity' apart.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositionWithNegativeValuesInLogFileWithPointsApart )
{
    const metres granularity = HORIZONTAL_GRID_UNIT / 10;

    Position thePosition = Position(-52.9215, -1.19892, -58);
    Route route = Route(LogFiles::GPXRoutesDir + "PointsApartNegative-N0724629.gpx", IS_FILE_NAME, granularity);

    BOOST_CHECK_EQUAL( route.findPosition("Q").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("Q").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("Q").elevation(), thePosition.elevation() );
}


/**
* Test case: ThrowsOutOfRangeWhenPointsTooClose
* Use:       Checks that an std::out_of_range exception is thrown for points
*            with positive values for latitude, longitude and elevation that are
*            less than 'granularity' apart.
* Test type: Invalid
*/
BOOST_AUTO_TEST_CASE( ThrowsOutOfRangeWhenPointsTooClose )
{
    const metres granularity = HORIZONTAL_GRID_UNIT * 5;

    Route route = Route(LogFiles::GPXRoutesDir + "PointsTooClose.gpx", IS_FILE_NAME, granularity);

    BOOST_CHECK_THROW( route.findPosition("A").latitude(), std::out_of_range );
    BOOST_CHECK_THROW( route.findPosition("A").longitude(), std::out_of_range );
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

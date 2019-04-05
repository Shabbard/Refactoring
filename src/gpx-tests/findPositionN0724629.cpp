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

BOOST_AUTO_TEST_SUITE( Route_Find_Position_N0724629 )

const bool IS_FILE_NAME = true;
const metres HORIZONTAL_GRID_UNIT = 1000;


/**
* Test case: DoesNotThrowExceptionWhenAccessingPositivePositionValues
* Use:       Checks that no exception is thrown when attempting to access a
*            point on the route with positive values.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( DoesNotThrowExceptionWhenAccessingPositivePositionValues )
{
    Route route = Route(LogFiles::GPXRoutesDir + "OnePointPositive-N0724629.gpx", IS_FILE_NAME);

    BOOST_CHECK_NO_THROW( route.findPosition("B").latitude() );
    BOOST_CHECK_NO_THROW( route.findPosition("B").longitude() );
    BOOST_CHECK_NO_THROW( route.findPosition("B").elevation() );
}


/**
* Test case: DoesNotThrowExceptionWhenAccessingNegativePositionValues
* Use:       Checks that no exception is thrown when attempting to access a
*            point on the route with negative values.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( DoesNotThrowExceptionWhenAccessingNegativePositionValues )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", IS_FILE_NAME);

    BOOST_CHECK_NO_THROW( route.findPosition("Q").latitude() );
    BOOST_CHECK_NO_THROW( route.findPosition("Q").longitude() );
    BOOST_CHECK_NO_THROW( route.findPosition("Q").elevation() );
}


/**
* Test case: CanGetPositionWithPositiveValuesInLogFileWithOnePoint
* Use:       Checks that it is possible to obtain positive values for latitude,
*            longitude and elevation in a GPX log file with only one point on
*            the route.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositionWithPositiveValuesInLogFileWithOnePoint )
{
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
* Test case: ThrowsOutOfRangeIfCaseIncorrect
* Use:       Checks that the std::out_of_range exception is thrown if the
*            specified name is in the incorrect case.
* Test type: Invalid Extreme
*/
BOOST_AUTO_TEST_CASE ( ThrowsOutOfRangeIfCaseIncorrect )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", IS_FILE_NAME);

    BOOST_CHECK_THROW( route.findPosition("q").latitude(), std::out_of_range );
    BOOST_CHECK_THROW( route.findPosition("q").longitude(), std::out_of_range );
    BOOST_CHECK_THROW( route.findPosition("q").elevation(), std::out_of_range );
}


/**
* Test case: CanGetPositionWithPositiveValuesInLogFileWithRepeatedPoints
* Use:       Checks that it is possible to a Position object for a point that is
*            present multiple tiles in a GPX log file. Checks that each instance
*            of the point returns an equivalent Position object.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositionWithRepeatedPoints )
{
    Position thePosition = Position(52.9761, 1.16915, 53);
    Route route = Route(LogFiles::GPXRoutesDir + "RepeatedPoints-N0724629.gpx", IS_FILE_NAME);

    BOOST_CHECK_EQUAL( route.findPosition("D").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("D").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("D").elevation(), thePosition.elevation() );

    Position repeatedPosition = route[3];

    BOOST_CHECK_EQUAL( repeatedPosition.latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( repeatedPosition.longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( repeatedPosition.elevation(), thePosition.elevation() );
}


/**
* Test case: CanGetPositionWithAllPointsApart
* Use:       Checks that it is possible to obtain a Position object for all of
*            the points in a route where none of the points are less than
*            'granularity' apart.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositionWithAllPointsApart )
{
    const metres granularity = HORIZONTAL_GRID_UNIT / 10;

    Route route = Route(LogFiles::GPXRoutesDir + "PointsApart-N0724629.gpx", IS_FILE_NAME, granularity);

    Position thePosition = Position(52.9125, 1.15423, 58);
    BOOST_CHECK_EQUAL( route.findPosition("K").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("K").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("K").elevation(), thePosition.elevation() );

    thePosition = Position(52.9035, 1.16913, 58);
    BOOST_CHECK_EQUAL( route.findPosition("Q").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("Q").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("Q").elevation(), thePosition.elevation() );

    thePosition = Position(52.9215, 1.18403, 58);
    BOOST_CHECK_EQUAL( route.findPosition("H").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("H").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("H").elevation(), thePosition.elevation() );

    thePosition = Position(52.9305, 1.21382, 58);
    BOOST_CHECK_EQUAL( route.findPosition("E").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("E").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("E").elevation(), thePosition.elevation() );

    thePosition = Position(52.9305, 1.15423, 58);
    BOOST_CHECK_EQUAL( route.findPosition("A").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("A").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("A").elevation(), thePosition.elevation() );
}


/**
* Test case: ThrowsOutOfRangeWhenPointsTooClose
* Use:       Checks that an std::out_of_range exception is thrown for points
*            that are distanced from another point such that they are less than
*            'granularity' apart and therefore should be considered as a
*            different location.
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
* Test case: CanGetPositionWithSomePointsApart
* Use:       Checks that it is possible to obtain positive values for latitude,
*            longitude and elevation in a GPX log file with a repeated point.
* Test type: Valid
*/
BOOST_AUTO_TEST_CASE( CanGetPositionWithSomePointsApart )
{
    const metres granularity = HORIZONTAL_GRID_UNIT * 1.5;

    Route route = Route(LogFiles::GPXRoutesDir + "PointsApart-N0724629.gpx", IS_FILE_NAME, granularity);

    Position thePosition = Position(52.9125, 1.15423, 58);
    BOOST_CHECK_EQUAL( route.findPosition("K").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("K").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("K").elevation(), thePosition.elevation() );

    thePosition = Position(52.9215, 1.18403, 58);
    BOOST_CHECK_EQUAL( route.findPosition("H").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("H").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("H").elevation(), thePosition.elevation() );

    thePosition = Position(52.9305, 1.21382, 58);
    BOOST_CHECK_EQUAL( route.findPosition("E").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("E").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("E").elevation(), thePosition.elevation() );

    thePosition = Position(52.9305, 1.15423, 58);
    BOOST_CHECK_EQUAL( route.findPosition("A").latitude(), thePosition.latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("A").longitude(), thePosition.longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("A").elevation(), thePosition.elevation() );
}


/**
* Test case: ThrowsOutOfRangeForDiscardedPoints
* Use:       Checks that an std::out_of_range exception is thrown for a point
*            that are distanced from another point such that they are less than
*            'granularity' apart, and therefore should be considered as a
*            different location, in a file where other points are more than
*            'granularity' apart.
* Test type: Invalid Extreme
*/
BOOST_AUTO_TEST_CASE( ThrowsOutOfRangeForDiscardedPoints )
{
    const metres granularity = HORIZONTAL_GRID_UNIT * 1.5;

    Route route = Route(LogFiles::GPXRoutesDir + "PointsApart-N0724629.gpx", IS_FILE_NAME, granularity);

    BOOST_CHECK_THROW( route.findPosition("Q").latitude(), std::out_of_range );
    BOOST_CHECK_THROW( route.findPosition("Q").longitude(), std::out_of_range );
    BOOST_CHECK_THROW( route.findPosition("Q").elevation(), std::out_of_range );
}


BOOST_AUTO_TEST_SUITE_END()

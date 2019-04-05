#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"


//Created by Imogen Wilkinson - N0734208
//FindPosition purpose: Find the route point bearing the specified name.

using namespace GPS;

BOOST_AUTO_TEST_SUITE(find_position_N0734208)

const bool isFileName = true;


//Testing each position attribute with a negative value on a single point route
BOOST_AUTO_TEST_CASE( findLatitudeNegative )
{
    Route route = Route(LogFiles::GPXRoutesDir + "onePointNegative-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("V").latitude(), Position(-0.179964, -0.0898312,-200.000000).latitude() );
}

BOOST_AUTO_TEST_CASE( findLongitudeNegative )
{
    Route route = Route(LogFiles::GPXRoutesDir + "onePointNegative-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("V").longitude(), Position(-0.179964, -0.0898312,-200.000000).longitude() );
}

BOOST_AUTO_TEST_CASE( findElevationNegative )
{
    Route route = Route(LogFiles::GPXRoutesDir + "onePointNegative-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("V").elevation(), Position(-0.179964, -0.0898312,-200.000000).elevation() );
}



//Testing each position attribute with a positive value on a single point route
BOOST_AUTO_TEST_CASE( findLatitudePositive )
{
    Route route = Route(LogFiles::GPXRoutesDir + "onePointPositive-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("E").latitude(), Position(0.179964, 0.179662,200.000000).latitude() );
}

BOOST_AUTO_TEST_CASE( findLongitudePositive )
{
    Route route = Route(LogFiles::GPXRoutesDir + "onePointPositive-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("E").longitude(), Position(0.179964, 0.179662,200.000000).longitude() );
}

BOOST_AUTO_TEST_CASE( findElevationPositive )
{
    Route route = Route(LogFiles::GPXRoutesDir + "onePointPositive-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("E").elevation(), Position(0.179964, 0.179662,200.000000).elevation() );
}




//Testing each position attribute with a zero value on a single point route
BOOST_AUTO_TEST_CASE( findLatitudeZero)
{
    Route route = Route(LogFiles::GPXRoutesDir + "onePointZero-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("M").latitude(), Position(0, 0, 0.000000).latitude() );
}

BOOST_AUTO_TEST_CASE( findLongitudeZero )
{
    Route route = Route(LogFiles::GPXRoutesDir + "onePointZero-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("M").longitude(), Position(0, 0, 0.000000).longitude() );
}

BOOST_AUTO_TEST_CASE( findElevationZero )
{
    Route route = Route(LogFiles::GPXRoutesDir + "onePointZero-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("M").elevation(), Position(0, 0, 0.000000).elevation() );
}




//Testing the position as a whole on routes of varying length.
BOOST_AUTO_TEST_CASE( findPositionOnePoint )
{
    Route route = Route(LogFiles::GPXRoutesDir + "onePointPositive-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("E").latitude(), Position(0.179964, 0.179662,200.000000).latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("E").longitude(), Position(0.179964, 0.179662,200.000000).longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("E").elevation(), Position(0.179964, 0.179662,200.000000).elevation() );
}

BOOST_AUTO_TEST_CASE( findPositionSeveralPoints)
{
    Route route = Route(LogFiles::GPXRoutesDir + "severalPoints-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("Q").latitude(), Position(-0.089982,-0.0898312,100.000000).latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("Q").longitude(), Position(-0.089982,-0.0898312,100.000000).longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("Q").elevation(), Position(-0.089982,-0.0898312,100.000000).elevation() );
}

BOOST_AUTO_TEST_CASE( findPositionManyPoints)
{
    Route route = Route(LogFiles::GPXRoutesDir + "manyPoints-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("I").latitude(), Position(0.089982,0.0898312,100.000000).latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("I").longitude(), Position(0.089982,0.0898312,100.000000).longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("I").elevation(), Position(0.089982,0.0898312,100.000000).elevation() );
}




//Testing that the position can be retrieved regardless of its position in the route
BOOST_AUTO_TEST_CASE( findFirstPosition)
{
    Route route = Route(LogFiles::GPXRoutesDir + "manyPoints-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("A").latitude(), Position(0.179964,-0.179662,200.000000).latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("A").longitude(), Position(0.179964,-0.179662,200.000000).longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("A").elevation(), Position(0.179964,-0.179662,200.000000).elevation() );
}

BOOST_AUTO_TEST_CASE( findMiddlePosition)
{
    Route route = Route(LogFiles::GPXRoutesDir + "manyPoints-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("L").latitude(), Position(0,-0.0898312,100.000000).latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("L").longitude(), Position(0,-0.0898312,100.000000).longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("L").elevation(), Position(0,-0.0898312,100.000000).elevation() );
}

BOOST_AUTO_TEST_CASE( findLastPosition)
{
    Route route = Route(LogFiles::GPXRoutesDir + "manyPoints-n0734208.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("X").latitude(), Position(-0.179964,0.0898312,200.000000).latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("X").longitude(), Position(-0.179964,0.0898312,200.000000).longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("X").elevation(), Position(-0.179964,0.0898312,200.000000).elevation() );
}




//Testing for a position that does not exist in the route
BOOST_AUTO_TEST_CASE(nonExistantPosition)
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_THROW( route.findPosition("B"), std::out_of_range);
}



BOOST_AUTO_TEST_SUITE_END()


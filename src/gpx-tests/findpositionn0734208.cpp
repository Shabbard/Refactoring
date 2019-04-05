#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include <iostream>

//Created by Imogen Wilkinson - N0734208
// Find the route point bearing the specified name.
// Throws a std::out_of_range exception if the name is not found.

using namespace GPS;

BOOST_AUTO_TEST_SUITE(find_position_N0734208)

const bool isFileName = true;


//Testing negative values
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



//Testing positive values
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




//Testing zero values
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




//Testing bearing as a whole

BOOST_AUTO_TEST_CASE( findPositionOnePoint )
{
    Route route = Route(LogFiles::GPXRoutesDir + "A.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("A").latitude(), Position(0.179964,109.142,0).latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("A").longitude(), Position(0.179964,109.142,0).longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("A").elevation(), Position(0.179964,109.142,0).elevation() );
}

BOOST_AUTO_TEST_CASE( findPositionSeveralPoints)
{
    Route route = Route(LogFiles::GPXRoutesDir + "A.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("A").latitude(), Position(0.179964,109.142,0).latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("A").longitude(), Position(0.179964,109.142,0).longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("A").elevation(), Position(0.179964,109.142,0).elevation() );
}

BOOST_AUTO_TEST_CASE( findPositionManyPoints)
{
    Route route = Route(LogFiles::GPXRoutesDir + "A.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("A").latitude(), Position(0.179964,109.142,0).latitude() );
    BOOST_CHECK_EQUAL( route.findPosition("A").longitude(), Position(0.179964,109.142,0).longitude() );
    BOOST_CHECK_EQUAL( route.findPosition("A").elevation(), Position(0.179964,109.142,0).elevation() );
}





//Position entered that does not exist
BOOST_AUTO_TEST_CASE(nonExistantPosition)
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_THROW( route.findPosition("B"), std::out_of_range);
}

/*BOOST_AUTO_TEST_CASE(caseSensitivityPosition)
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("q").elevation(), Position(-0.89982, -0.898312, -20000).elevation() );

}*/

BOOST_AUTO_TEST_SUITE_END()

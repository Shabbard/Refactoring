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


//Testing latitude
BOOST_AUTO_TEST_CASE( findLatitudeNegative )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("Q").latitude(), Position(-0.89982, -0.898312).latitude() );

}

BOOST_AUTO_TEST_CASE( findLatitudePositive )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("E").latitude(), Position(1.79964, 1.79662).latitude() );
}

BOOST_AUTO_TEST_CASE( findLatitudeZero)
{
    Route route = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("K").latitude(), Position(0, -1.79662).latitude() );
}






//Testing Longitude
BOOST_AUTO_TEST_CASE( findLongitudeNegative )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("Q").longitude(), Position(-0.89982, -0.898312).longitude() );
}

BOOST_AUTO_TEST_CASE( findLongitudePositive )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("E").longitude(), Position(1.79964, 1.79662).longitude() );
}

BOOST_AUTO_TEST_CASE( findLongitudeZero )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("W").longitude(), Position(-1.79964, 0).longitude() );
}



//Testing Elevation
BOOST_AUTO_TEST_CASE( findElevationNegative )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("Q").elevation(), Position(-0.89982, -0.898312, -20000).elevation() );
}

BOOST_AUTO_TEST_CASE( findElevationPositive )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    //temporary make own file with a positive elevation
    BOOST_CHECK_EQUAL( route.findPosition("Q").elevation(), Position(-0.89982, -0.898312, -20000).elevation() );
}

BOOST_AUTO_TEST_CASE( findElevationZero )
{
    Route route = Route(LogFiles::GPXRoutesDir + "A.gpx", isFileName);
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

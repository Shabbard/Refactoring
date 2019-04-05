#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "position.h"
#include "earth.h"

using namespace GPS;

const bool isFileName = true;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//test large xml files
BOOST_AUTO_TEST_SUITE( NorthYorkMoor )

BOOST_AUTO_TEST_CASE( PositionCheck_Q )
{
    Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
    Position position = Position(54.42128598690033,-1.110675930976868);
    BOOST_CHECK_EQUAL(route.findNameOf(position), "");
}

BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//test files that provided
BOOST_AUTO_TEST_SUITE( TestGpxFilesThatProviode )

//Q.gpx
BOOST_AUTO_TEST_CASE( PositionCheck_Q )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    Position positionQ = Position(-0.89982,-0.898312);
    BOOST_CHECK_EQUAL(route.findNameOf(positionQ), "Q");
}

//ABCD.gpx
BOOST_AUTO_TEST_CASE( PositionCheck_ABCD )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    Position positionA = Position(0.179964,109.142);
    BOOST_CHECK_EQUAL(route.findNameOf(positionA), "A");
    Position positionB = Position(0.179964,109.232);
    BOOST_CHECK_EQUAL(route.findNameOf(positionB), "B");
    Position positionC = Position(0.179964,109.322);
    BOOST_CHECK_EQUAL(route.findNameOf(positionC), "C");
    Position positionD = Position(0.179964,109.412);
    BOOST_CHECK_EQUAL(route.findNameOf(positionD), "D");
}

//ABQWE.gpx
BOOST_AUTO_TEST_CASE( PositionCheck_ABQWE )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
    Position positionA = Position(1.79964,-1.79662);
    BOOST_CHECK_EQUAL(route.findNameOf(positionA), "A");
    Position positionB = Position(1.79964,-0.898312);
    BOOST_CHECK_EQUAL(route.findNameOf(positionB), "B");
    Position positionQ = Position(-0.89982,-0.898312);
    BOOST_CHECK_EQUAL(route.findNameOf(positionQ), "Q");
    Position positionW = Position(-1.79964,0);
    BOOST_CHECK_EQUAL(route.findNameOf(positionW), "W");
    Position positionE = Position(1.79964,1.79662);
    BOOST_CHECK_EQUAL(route.findNameOf(positionE), "E");
}

//AFKPU.gpx
BOOST_AUTO_TEST_CASE( PositionCheck_AFKPU )
{
    Route route = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", isFileName);
    Position positionA = Position(1.79964,-1.79662);
    BOOST_CHECK_EQUAL(route.findNameOf(positionA), "A");
    Position positionF = Position(0.89982,-1.79662);
    BOOST_CHECK_EQUAL(route.findNameOf(positionF), "F");
    Position positionK = Position(0,-1.79662);
    BOOST_CHECK_EQUAL(route.findNameOf(positionK), "K");
    Position positionP = Position(-0.89982,-1.79662);
    BOOST_CHECK_EQUAL(route.findNameOf(positionP), "P");
    Position positionU = Position(-1.79964,-1.79662);
    BOOST_CHECK_EQUAL(route.findNameOf(positionU), "U");
}

BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//myPosition test
BOOST_AUTO_TEST_SUITE( myPosition)

BOOST_AUTO_TEST_CASE( PositionCheck_myPosition )
{
    Route route = Route(LogFiles::GPXRoutesDir + "myPosition_t0084963.gpx", isFileName);
    //Both positive longtitude and latitude
    Position positionPP = Position(52.9123436,1.1893666);
    BOOST_CHECK_EQUAL(route.findNameOf(positionPP), "PP");
    //Both negative longtitude and latitude
    Position positionNN = Position(-52.9123436,-1.1893666);
    BOOST_CHECK_EQUAL(route.findNameOf(positionNN), "NN");
    //Positive longtitude and negative latitude
    Position positionPN = Position(52.0123436,-1.1893666);
    BOOST_CHECK_EQUAL(route.findNameOf(positionPN), "PN");
    //Negative longtitude and positive latitude
    Position positionNP = Position(-52.9123436,1.1893666);
    BOOST_CHECK_EQUAL(route.findNameOf(positionNP), "NP");
    //Test different positions have the same name
    //normal position
    Position positionClifton = Position(52.9123436,-1.1893665);
    BOOST_CHECK_EQUAL(route.findNameOf(positionClifton), "Clifton Campus");
    //nearly same
    Position positionC1 = Position(52.9588404,-1.1511104);
    BOOST_CHECK_EQUAL(route.findNameOf(positionC1), "Clifton Campus");
    //different position
    Position positionC2 = Position(3.1468059,101.6897678);
    BOOST_CHECK_EQUAL(route.findNameOf(positionC2), "Clifton Campus");
}

BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Wrong position, system throws out_of_range
BOOST_AUTO_TEST_SUITE( out_of_rangePosition)

BOOST_AUTO_TEST_CASE( ErrorLat )
{
    Route route = Route(LogFiles::GPXRoutesDir + "myPosition_t0084963.gpx", isFileName);
    Position positionClifton = Position(0,-1.1893665);
    BOOST_CHECK_THROW(route.findNameOf(positionClifton), std::out_of_range);
    Position positionC1 = Position(0,-1.1511104);
    BOOST_CHECK_THROW(route.findNameOf(positionC1), std::out_of_range);
    Position positionC2 = Position(0,101.6897678);
    BOOST_CHECK_THROW(route.findNameOf(positionC2), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( ErrorLon )
{
    Route route = Route(LogFiles::GPXRoutesDir + "myPosition_t0084963.gpx", isFileName);
    Position positionClifton = Position(52.9123436,0);
    BOOST_CHECK_THROW(route.findNameOf(positionClifton), std::out_of_range);
    Position positionC1 = Position(52.9588404,0);
    BOOST_CHECK_THROW(route.findNameOf(positionC1), std::out_of_range);
    Position positionC2 = Position(3.1468059,0);
    BOOST_CHECK_THROW(route.findNameOf(positionC2), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

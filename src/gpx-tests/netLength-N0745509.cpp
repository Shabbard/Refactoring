#include <boost/test/unit_test.hpp>

#include "gridworld_route.h"
#include <fstream>
#include "logs.h"
#include "track.h"
#include "route.h"

//N0745509

/*
A B C D E
F G H I J
K L M N O
P Q R S T
U V W X Y
*/

using namespace GPS;

std::string generateLogFile(std::string testName, GridWorldRoute routeLog)
{

    std::string GPXroute = routeLog.toGPX(true, testName); //set to true so i can add my own name to be added to the generated GPX log file

    std::string fileName = testName + "-N0745509.gpx"; //outputs my GPX log file with my custom test name + "-N0745509.gpx"

    std::ofstream openFile(LogFiles::GPXRoutesDir + fileName); //ofstreams my GPX log file to the ../GPX/routes directory
    openFile << GPXroute;
    openFile.close();

    return fileName;
}


BOOST_AUTO_TEST_SUITE( Route_netLength )

const bool IS_FILE_NAME = true;
const metres HORIZONTAL_GRID_UNIT = 10000;
const double PERCENTAGE = 0.1;

/*
 *  TEST:: netLengthWIthSamePoint
 *  USAGE:: Grid point AA
 *  PURPOSE:: To see if the netLength equals 0 when both locations are the same
 *
 *  Generates .GPX log file isSameLocation_AA-N0745509.gpx
 *
*/
BOOST_AUTO_TEST_CASE( netLengthWIthSamePoint ) {

    GridWorldRoute routeLogFile = GridWorldRoute("AA");
    Route netLengthAA = Route(LogFiles::GPXRoutesDir + generateLogFile("isSameLocation_AA", routeLogFile), IS_FILE_NAME);
    BOOST_CHECK_EQUAL(  netLengthAA.netLength(),  0);
}

/*
 *  TEST:: firstLastPointAreTheSame
 *  USAGE:: Grid points AEWUA
 *  PURPOSE:: To see if the netLength equals 0 when the first position and last posistion are the same location
 *
 *  Generates .GPX log file isSameLocationWIthMultiplePoints-N0745509.gpx
*/
BOOST_AUTO_TEST_CASE ( firstLastPointAreTheSame ) {

    GridWorldRoute routeLogFile = GridWorldRoute("AEWUA");
    Route netLengthAEWUA= Route(LogFiles::GPXRoutesDir + generateLogFile("isSameLocationWIthMultiplePoints", routeLogFile), IS_FILE_NAME);
    BOOST_CHECK_EQUAL(  netLengthAEWUA.netLength(),  0);
}

/*
 *  TEST:: netLengthWithOnePoint
 *  USAGE:: Grid Point Q
 *  PURPOSE:: To see if the netLength equals 0 when a single grid point is given
*/
BOOST_AUTO_TEST_CASE ( netLengthWithOnePoint) {

    Route netLengthQ = Route(LogFiles::GPXRoutesDir + "Q.gpx", IS_FILE_NAME);
    BOOST_CHECK_EQUAL(netLengthQ.netLength(), 0);
}

/*
 *  TEST:: verticalPointsNetLength
 *  USAGE:: Grid points AFKPU
 *  PURPOSE:: TO see the what the largest netLength can be generated:: using grid points that are the furthest away from each other
*/
BOOST_AUTO_TEST_CASE ( verticalPointsNetLength ) {

    Route verticalPointsNetLength = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", IS_FILE_NAME);
    BOOST_CHECK_EQUAL(verticalPointsNetLength.netLength(), 400222.2283829503);
}

/*
 *  TEST:: UsingMultiplePoints
 *  Usage:: Grid points ABQWE
 *  PURPOSE:: To see what netLength will be generated using points above nad below the cnetral point(that is M).
*/
BOOST_AUTO_TEST_CASE ( UsingMultiplePoints ) {

    Route netLengthABQWE = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", IS_FILE_NAME);
    BOOST_CHECK_EQUAL(netLengthABQWE.netLength(), 399353.47026921058);
}

/*
 *  Test:: horizontalPointsNetLength
 *  USAGE:: Grid points ABCD
 *  PURPOSE:: To test the netLength of a route with horizontal points
 *
*/
BOOST_AUTO_TEST_CASE( horizontalPointsNetLength ) {

    Route netLengthABCD = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", IS_FILE_NAME);
    BOOST_CHECK_EQUAL(netLengthABCD.netLength(), 30022.523566211392);
}

/*
 *  TEST:: negativeLatitude
 *  USAGE:: Grid points QVSW
 *  PURPOSE:: Test the netLength of a route that has only negative Latitude values
 *
 *  Generates GPX log file negativeLatitude-N0745509.gpx
*/
BOOST_AUTO_TEST_CASE ( negativeLatitude ) {

    GridWorldRoute routeLogFile = GridWorldRoute("QVSW");
    Route latitudeMinus = Route(LogFiles::GPXRoutesDir + generateLogFile("negativeLatitude", routeLogFile), IS_FILE_NAME);
    BOOST_CHECK_EQUAL(latitudeMinus.netLength(), 14151.387572362539  );
}

/*
 *  TEST:: negatuveLongitude
 *  USEAGE:: Grid points AFKPU + CityCampus position
 *  PURPOSE:: To test a netLength with negative Longitude values + a netLength value that is close to zero
 *
 *  Generates .GPX log file negativeLongitude-N0745509..gpx
*/
BOOST_AUTO_TEST_CASE ( negatuveLongitude ) {

    GridWorldRoute routeLogFile = GridWorldRoute("AFKPU",GridWorld(Earth::CityCampus, 10, 0));
    Route LongitudeMinus = Route(LogFiles::GPXRoutesDir + generateLogFile("negativeLongitude", routeLogFile), IS_FILE_NAME);
    BOOST_CHECK_EQUAL(LongitudeMinus.netLength(), 22.239016046931543);
}

/*
 *  TEST:: longitudeEqualsZero
 *  USAGE:: Grid points ABC + NorthPole position
 *  PURPOSE:: To test the netLength when the longitude value equals 0
 *
 *  Generates GPX log file longitudeEqualsZero-N0745509.gpx
*/

BOOST_AUTO_TEST_CASE( longitudeEqualsZero ) {

    GridWorldRoute routeLogFile = GridWorldRoute("ABC",GridWorld(Earth::NorthPole, 0, 0));
    Route longitudeZero = Route(LogFiles::GPXRoutesDir + generateLogFile("longitudeEqualsZero", routeLogFile), IS_FILE_NAME);
    BOOST_CHECK_EQUAL(longitudeZero.netLength(), 0  );
}

/*
 *  TEST:: latitudeEqualsZero
 *  USAGE:: Grid points MKO
 *  PURPOSE:: TO test the netLength when the latitude value of arep oints equal 0
 *
 *  Generates GPX log file latitudeEqualsZero-N0745509.gpx
*/

BOOST_AUTO_TEST_CASE ( latitudeEqualsZero ) {

     GridWorldRoute routeLogFile = GridWorldRoute("MKO");
     Route latitudeZero = Route(LogFiles::GPXRoutesDir + generateLogFile("latitudeEqualsZero", routeLogFile), IS_FILE_NAME);
     BOOST_CHECK_EQUAL(latitudeZero.netLength(), 20015.114442036094 );
}

/*
 *  TEST:: moreThanGranularity
 *  USAGE:: Grid points AEB + granularity value of 9,900
 *  PURPOSE:: To test the netLength when its value is greater than the granularity
 *
 *  Generates GPX log file lessThanGranularity-N0745509.gpx
*/

BOOST_AUTO_TEST_CASE( moreThanGranularity ) {

    const metres granularity = HORIZONTAL_GRID_UNIT * 0.99; //granularity = 9,900

    GridWorldRoute routeLogFile = GridWorldRoute("AEB");
    Route moreThanGranularity = Route(LogFiles::GPXRoutesDir + generateLogFile("lessThanGranularity.gpx",routeLogFile), IS_FILE_NAME, granularity);
    BOOST_CHECK_CLOSE(moreThanGranularity.netLength(), 10000, PERCENTAGE );
}

/*
 *  TEST:: lessThanGranularity
 *  USAGE:: Grid points AEB + granularity value of 10,100
 *  PURPOSE:: To test the netLength when its vlaue is less than the granularity
 *
 *  Generates GPX log file moreThanGranularity-N0745509.gpx
*/

BOOST_AUTO_TEST_CASE( lessThanGranularity ) {

    const metres granularity = HORIZONTAL_GRID_UNIT * 1.01; //granularity = 10,100

    GridWorldRoute routeLogFile = GridWorldRoute("AEB");
    Route lessThanGranularity = Route(LogFiles::GPXRoutesDir + generateLogFile("moreThanGranularity.gpx",routeLogFile), IS_FILE_NAME, granularity);
    BOOST_CHECK_EQUAL(lessThanGranularity.netLength(), 0 );
}

BOOST_AUTO_TEST_SUITE_END()

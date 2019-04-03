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

    std::string GPXroute = routeLog.toGPX(true, testName);

    std::string fileName = testName + "-N0745509.gpx";

    std::ofstream openFile(LogFiles::GPXRoutesDir + fileName);
    openFile << GPXroute;
    openFile.close();

    return fileName;
}


BOOST_AUTO_TEST_SUITE( Route_netLength )

const bool isFileName = true;
const metres horizontalGridUnit = 10000;
const double percentage = 0.1;

/*
 *  TEST:: netLengthWIthSamePoint
 *  Checks the netLength when points the first position and last position are at the same grid point.
 *  Testing to see if the netLength equals 0
 *  Generates GPX log file isameLocation_AA
 *
*/
BOOST_AUTO_TEST_CASE( netLengthWIthSamePoint ) {

    GridWorldRoute routeLogFile = GridWorldRoute("AA");
    Route netLengthAA = Route(LogFiles::GPXRoutesDir + generateLogFile("sameLocation_AA", routeLogFile), isFileName);
    BOOST_CHECK_EQUAL(  netLengthAA.netLength(),  0);
}

/*
 *  TEST:: firstLastPointAreTheSame
 *  Checks the netLength when the the first poisition and last position are at the same grid point among other grid points
 *  Testing to see if the netLength equals 0
 *  Generates gpx log file sameLocation_AEWUA.gpx
*/
BOOST_AUTO_TEST_CASE ( firstLastPointAreTheSame ) {

    GridWorldRoute routeLogFile = GridWorldRoute("AEWUA");
    Route netLengthAEWUA= Route(LogFiles::GPXRoutesDir + generateLogFile("sameLocation_AEWUA", routeLogFile), isFileName);
    BOOST_CHECK_EQUAL(  netLengthAEWUA.netLength(),  0);
}

/*
 *  TEST:: netLengthWithOnePoint
 *  Checks that an desending single grid point can generate a net length of 0
 *  Testing to see if the netLength equals 0
*/
BOOST_AUTO_TEST_CASE ( netLengthWithOnePoint) {

    Route netLengthQ = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_EQUAL(netLengthQ.netLength(), 0);
}

/*
 * TEST:: verticalPointsNetLength
 *
*/
BOOST_AUTO_TEST_CASE ( verticalPointsNetLength ) {

    Route netLengthAFKPU = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", isFileName);
    BOOST_CHECK_EQUAL(netLengthAFKPU.netLength(), 400222.2283829503);
}

BOOST_AUTO_TEST_CASE ( UsingMultiplePoints ) {

    Route netLengthABQWE = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
    BOOST_CHECK_EQUAL(netLengthABQWE.netLength(), 399353.47026921058);
}

BOOST_AUTO_TEST_CASE( horizontalPointsNetLength ) {

    Route netLengthABCD = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_EQUAL(netLengthABCD.netLength(), 30022.523566211392);
}

BOOST_AUTO_TEST_CASE ( negativeLatitude ) {

    GridWorldRoute routeLogFile = GridWorldRoute("QVSW");
    Route latitudeMinus = Route(LogFiles::GPXRoutesDir + generateLogFile("negativeLatitude", routeLogFile), isFileName);
    BOOST_CHECK_EQUAL(latitudeMinus.netLength(), 14151.387572362539  );
}

BOOST_AUTO_TEST_CASE ( negatuveLongitude ) {

    GridWorldRoute routeLogFile = GridWorldRoute("AFKPU",GridWorld(Earth::CityCampus, 10, 0));
    Route LongitudeMinus = Route(LogFiles::GPXRoutesDir + generateLogFile("negatuveLongitude", routeLogFile), isFileName);
    BOOST_CHECK_EQUAL(LongitudeMinus.netLength(), 22.239016046931543);
}

BOOST_AUTO_TEST_CASE( longitudeEqualsZero ) {

    GridWorldRoute routeLogFile = GridWorldRoute("ABC",GridWorld(Earth::NorthPole, 0, 0));
    Route longitudeZero = Route(LogFiles::GPXRoutesDir + generateLogFile("longitudeEqualsZero", routeLogFile), isFileName);
    BOOST_CHECK_EQUAL(longitudeZero.netLength(), 0  );
}

BOOST_AUTO_TEST_CASE ( latitudeEqualsZero ) {

     GridWorldRoute routeLogFile = GridWorldRoute("MKO");
     Route latitudeZero = Route(LogFiles::GPXRoutesDir + generateLogFile("latitudeEqualsZero", routeLogFile), isFileName);
     BOOST_CHECK_EQUAL(latitudeZero.netLength(), 20015.114442036094 );
}

BOOST_AUTO_TEST_CASE( moreThanGranularity ) {

    const metres granularity = horizontalGridUnit * 0.99; //granularity = 9,900

    GridWorldRoute routeLogFile = GridWorldRoute("AEB");
    Route moreThanGranularity = Route(LogFiles::GPXRoutesDir + generateLogFile("lessThanGranularity_AEB.gpx",routeLogFile), isFileName, granularity);
    BOOST_CHECK_CLOSE(moreThanGranularity.netLength(), 10000, percentage );
}

BOOST_AUTO_TEST_CASE( lessThanGranularity ) {

    const metres granularity = horizontalGridUnit * 1.01; //granularity = 10,100

    GridWorldRoute routeLogFile = GridWorldRoute("AEB");
    Route lessThanGranularity = Route(LogFiles::GPXRoutesDir + generateLogFile("moreThanGranularity_AEB.gpx",routeLogFile), isFileName, granularity);
    BOOST_CHECK_EQUAL(lessThanGranularity.netLength(), 0 );
}

BOOST_AUTO_TEST_SUITE_END()

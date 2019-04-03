#include <boost/test/unit_test.hpp>
#include <fstream>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "earth.h"
#include "gridworld.h"
#include "gridworld_route.h"

using namespace GPS;


std::string makeLogFile(std::string testCase, GridWorldRoute route) {
  std::string fileName = testCase + "-N0743587.gpx"; // Create filename
  std::string GPXRoute = route.toGPX(true, testCase); // GWR to GPX

  std::string filepath = LogFiles::GPXRoutesDir + fileName; // Create filepath
  std::ofstream newLogFile(filepath);
  newLogFile << GPXRoute; // Push data to file
  newLogFile.close();

  return fileName;
}

BOOST_AUTO_TEST_SUITE( minLatitude_N0743587 )

BOOST_AUTO_TEST_CASE(SinglePointSigned){

    Route route = Route(LogFiles::GPXRoutesDir + "A.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0.17996400000000001 );

    route = Route(LogFiles::GPXRoutesDir + "Q.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.89981999999999995 );
}

BOOST_AUTO_TEST_CASE(MultiPoint){

    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0.17996400000000001);

    route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 1.7996399999999999 );
}

BOOST_AUTO_TEST_CASE(ZeroLatitude){

    GridWorldRoute routeLog = GridWorldRoute("IEKS", GridWorld(Earth::EquatorialMeridian, 0, 1000));
    Route route = Route(LogFiles::GPXRoutesDir + makeLogFile("CanGetZeroLatitude", routeLog), true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0 );
}

BOOST_AUTO_TEST_CASE(InvalidFile){
//Throws exception
    Route route = Route(LogFiles::GPXRoutesDir + "invalid.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 5 );

    route = Route(LogFiles::GPXRoutesDir + "invalid", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 6 );
}

BOOST_AUTO_TEST_CASE(NullCase){
//Throws IOException
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), 0.17996400000000001);
}


BOOST_AUTO_TEST_SUITE_END()

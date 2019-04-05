#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "types.h"
#include "route.h"
#include "earth.h"
#include "gridworld.h"
#include "gridworld_route.h"

using namespace GPS;

std::string makeLogFile(std::string logfileName, GridWorldRoute route)
{
    std::string fileName = logfileName + ".gpx";
    std::ofstream logfile(GPS::LogFiles::GPXTracksDir + fileName);
    logfile << route.toGPX(true,logfileName);
    logfile.close();
    return fileName;
}
//make log file

BOOST_AUTO_TEST_SUITE( t0086696_minLatitude )

const bool isFileName = true;

BOOST_AUTO_TEST_CASE( single_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "single_route.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLatitude(), 0.179964 );
}
//test single route

BOOST_AUTO_TEST_CASE( zero_value )
{
   Route route = Route(LogFiles::GPXRoutesDir + "zero_value.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLatitude(), 0 );
}
//test zero

BOOST_AUTO_TEST_CASE( negative_value )
{
   Route route = Route(LogFiles::GPXRoutesDir + "negative_value.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLatitude(), -0.179964 );
}
//test negative

BOOST_AUTO_TEST_CASE( multi_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "multi_route.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLatitude(), 0.179863 );
}
//test multiple route

BOOST_AUTO_TEST_CASE( same_latitude_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "same_latitude_route.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLatitude(), 0.179964 );
}
//test same latitude for multiple route

BOOST_AUTO_TEST_CASE( northyorkmoors )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLatitude(), 54.40526783466339 );
}

BOOST_AUTO_TEST_SUITE_END()

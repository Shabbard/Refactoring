#define BOOST_TEST_DYN_LYNK
#define BOOST_TEST_MODULE_GPXTests
#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "gridworld_track.h"


using namespace GPS;
  
BOOST_AUTO_TEST_SUITE(Track_totalTime_N0751567)
	
const bool isFileName = true;
const metres horizontalGridUnit = 1000;
const GridWorld gridworld;
//

/* TotalTime function implemented in the track.cpp file is the total calculated time taken to complete a route, 
the total time is calculated by adding the resting time plus the travelling time.
The time taken will be calculated in seconds */


//test calculating the totalTime under normal cirmcunstances
BOOST_AUTO_TEST_CASE(TotalTimeNormRoute)
{
	Track track = Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName);
	BOOST_CHECK_EQUAL(track.totalTime(), 40);
}


//Test calculating the shortest totalTime possible
BOOST_AUTO_TEST_CASE( ShortTotalTime )
{
	Track track = Track(LogFiles::GPXTracksDir + "A1B0C_N0751567.gpx", isFileName);
	BOOST_CHECK_EQUAL(track.totalTime(), 10);
}


//Test to calculate no times, which means no movement from a point to another
BOOST_AUTO_TEST_CASE( NoTimeTest )
{
	Track track = Track(LogFiles::GPXTracksDir + "A0B0C_N0751567.gpx", isFileName);
	BOOST_CHECK_EQUAL(track.totalTime(), 0);
}


//test to check longest TotalTime example
BOOST_AUTO_TEST_CASE( LongTotalTime )
{
	Track track = Track(LogFiles::GPXTracksDir + "A9B35C8D14E19F_LONGTIME_N0751567.gpx", isFileName);
	BOOST_CHECK_EQUAL(track.totalTime(), 850);
}


//Test to calculate the total time when the travelling time is equal zero
BOOST_AUTO_TEST_CASE( RestingTotalTime )
{
	Track track = Track(LogFiles::GPXTracksDir + "A3A_N0751567.gpx", isFileName);
	BOOST_CHECK_EQUAL(track.totalTime(), 30);
}

//test  to check the total time when going to points on different latitudes and logintudes
BOOST_AUTO_TEST_CASE( LatLongPointsTotalTime )
{
	Track track = Track(LogFiles::GPXTracksDir + "A2B3C4D_N0751567.gpx", isFileName);
	BOOST_CHECK_EQUAL(track.totalTime(), 110 );
}

//Test to check a non existent gpx file
//throws std::empty_file when logs are not found
BOOST_AUTO_TEST_CASE ( BlankLogFile )

{
    Track track = Track(LogFiles::GPXTracksDir + "BlankLogTest_N0751567.gpx", isFileName);
    BOOST_CHECK_THROW( track.totalTime(), std::domain_error );
}


BOOST_AUTO_TEST_SUITE_END()
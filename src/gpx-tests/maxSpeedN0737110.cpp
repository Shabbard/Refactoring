#include <boost/test/unit_test.hpp>

#include <fstream>
#include "earth.h"
#include "logs.h"
#include "track.h"
#include "gridworld_track.h"

using namespace GPS;

const std::string studentId("N0737110");

//Generates a log file using the GPX XML data contained in GPXStr
//File will be overwritten if it already exists
void generateLogFileFromGPX
	(const std::string filePath, const std::string GPXStr)
{
    std::ofstream out(filePath);
	
	out << GPXStr;
	out.close();
}
	
BOOST_AUTO_TEST_SUITE( Track_maxSpeed_N0737110 )




//Verify that a stationary track returns a max speed of zero
BOOST_AUTO_TEST_CASE( stationary_track )
{
    //track str contains the grid world track sequence
    //use a sequence that stays in the same way point after a time unit has elapsed
    const std::string trackStr("M1M");
    //Log file will be created in the track logs directory (Student Id is prefixed to avoid clashes)
    const std::string testFilePath(LogFiles::GPXTracksDir + studentId + "_" + trackStr + ".gpx");

    //Create a gridworld track, use 1 minute duration for the time units
    //use 1000 metres for the horizontal and vertical units
    GridWorldTrack gwTrack = GridWorldTrack(trackStr, 60, 0,
        GridWorld(Earth::Pontianak, 1000, 1000));

   //Generate test data log in a logfile in GPX format
   generateLogFileFromGPX(testFilePath, gwTrack.toGPX(60, true, trackStr));

   //Generate a track from the test data file
   Track track = Track(testFilePath, true,0);

   //Validate the max speed is as expected
   BOOST_CHECK_EQUAL( track.maxSpeed(), 0 );
}

//Compare calculated max speed against known max speed (m/s)
BOOST_AUTO_TEST_CASE( calculated_maxSpeed_straight )
{
    //Track str contains the grid world track point sequence
    const std::string trackStr("A10B15C");
    //Log file will be created in the track logs directory (Student Id is prefixed to avoid clashes)
    const std::string testFilePath(LogFiles::GPXTracksDir + studentId + "_" + trackStr + ".gpx");
	
    //Create a gridworld track, use 1 minute duration for the time units
    //use 1000 metres for the horizontal and vertical units
    GridWorldTrack gwTrack = GridWorldTrack(trackStr, 60, 0,
        GridWorld(Earth::Pontianak, 1000, 1000));
	   
   //Generate test data log in a logfile in GPX format
   generateLogFileFromGPX(testFilePath, gwTrack.toGPX(60, true, trackStr));
			
   //Generate a track from the test data file
   Track track = Track(testFilePath, true);
   
   //Validate the max speed is as expected
   BOOST_CHECK_EQUAL( track.maxSpeed(), 1.8532512458265862 );
}


//Compare calculated max speed against known max speed (m/s)
BOOST_AUTO_TEST_CASE( calculated_maxSpeed_singleturn )
{
    //Track str contains the grid world track point sequence
    const std::string trackStr("A12B5E");
    //Log file will be created in the track logs directory (Student Id is prefixed to avoid clashes)
    const std::string testFilePath(LogFiles::GPXTracksDir + studentId + "_" + trackStr + ".gpx");
	
    //Create a gridworld track, use 1 minute duration for the time units
    //use 1000 metres for the horizontal and vertical units
    GridWorldTrack gwTrack = GridWorldTrack(trackStr, 60, 0,
        GridWorld(Earth::Pontianak, 1000, 1000));
	   
   //Generate test data log in a logfile in GPX format
   generateLogFileFromGPX(testFilePath, gwTrack.toGPX(60, true, trackStr));
			
   //Generate a track from the test data file
   Track track = Track(testFilePath, true);
   
   //Validate the max speed is as expected
   BOOST_CHECK_EQUAL( track.maxSpeed(), 11.119507474841631 );
}


//Compare calculated max speed against known max speed (m/s)
BOOST_AUTO_TEST_CASE( calculated_maxSpeed_multiturns )
{
    //Track str contains the grid world track point sequence
    const std::string trackStr("A5B2E5D3G");
    //Log file will be created in the track logs directory (Student Id is prefixed to avoid clashes)
    const std::string testFilePath(LogFiles::GPXTracksDir + studentId + "_" + trackStr + ".gpx");
	
    //Create a gridworld track, use 1 minute duration for the time units
    //use 1000 metres for the horizontal and vertical units
    GridWorldTrack gwTrack = GridWorldTrack(trackStr, 60, 0,
        GridWorld(Earth::Pontianak, 1000, 1000));
	   
   //Generate test data log in a logfile in GPX format
   generateLogFileFromGPX(testFilePath, gwTrack.toGPX(60, true, trackStr));
			
   //Generate a track from the test data file
   Track track = Track(testFilePath, true);
   
   //Validate the max speed is as expected
   BOOST_CHECK_EQUAL( track.maxSpeed(), 25.945517441265693 );
}


BOOST_AUTO_TEST_SUITE_END()

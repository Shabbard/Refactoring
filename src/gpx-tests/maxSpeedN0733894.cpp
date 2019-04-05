#include <boost/test/unit_test.hpp>
#include <fstream>
#include <iostream>
#include "logs.h"
#include "types.h"
#include "track.h"
#include "gridworld_track.h"
#include "xmlgenerator.h"

using namespace GPS;
//USED IN THE FILEPATH
const std::string studentID = "N0733894";
//USED WHEN GENERATING THE TRACK
const bool isFileName = true;

std::string testName;
std::string filePath;

BOOST_AUTO_TEST_SUITE(track_maxSpeed_N0733894)

/*
 *  A test to see that the functions returns 0 if is stationary
 *  this is needed as it is says in the header file that if it is zero it will return 0
 * */

BOOST_AUTO_TEST_CASE( IS_STATIONARY )
{
    //Test name for going in the filename to allow us to find it and make it unique so they dont get mixed up
    testName = "IS_STATIONARY";

    //The track string that gets put in the GridWorldTrack
    std::string trackString = "A1A";

    //Get the log file from the correct directory
    filePath = GPS::LogFiles::GPXTracksDir + studentID + "-" + testName + ".gpx";

    //Construct the track from gpx data
    Track track = Track(filePath, isFileName, 0);

    //CHECK THE FINAL RESULT MAKES
    BOOST_CHECK_EQUAL(track.maxSpeed(), 0);

}

//A test to check that the program returns the value that it should return
BOOST_AUTO_TEST_CASE(COMPARE_MAX_SPEED)
{
    //Test name for going in the filename to allow us to find it and make it unique so they dont get mixed up
    testName = "COMPARE_MAX_SPEED";

    //The track string that gets put in the GridWorldTrack
    std::string trackString = "A20D30C";

    //Get the log file from the correct directory
    filePath = GPS::LogFiles::GPXTracksDir + studentID + "-" + testName + ".gpx";

    //Construct the track from gpx data
    Track track = Track(filePath, isFileName, 0);

    //CHECK THE FINAL RESULT TO THE KNOWN RESULT
    BOOST_CHECK_EQUAL(track.maxSpeed(), 15.013945078867712);

}

//THIS TEST IS TO TEST IF THE SAME MAX SPEED IS GIVEN GOING FORWARD COMPARED TO THE MAX SPEED GOING IN THE OPPOSITE DIRECTION
BOOST_AUTO_TEST_CASE(CHECK_REVERSE)
{
    //Test name for going in the filename to allow us to find it and make it unique so they dont get mixed up
    testName = "CHECK_REVERSE";

    //The track string that gets put in the GridWorldTrack when the log files are generated
    std::string trackString1 = "A20D30C";
    //this is just a reverse of trackString1 to test if they produce the same output
    std::string trackString2 = "C30D20A";

    //Get the log file from the correct directory(s)
    std::string filePath1 = GPS::LogFiles::GPXTracksDir + studentID + "-" + testName + "[FORWARD].gpx";
    std::string filePath2 = GPS::LogFiles::GPXTracksDir + studentID + "-" + testName + "[REVERSE].gpx";

    //Construct the track from gpx data from the log files
    Track track1= Track(filePath1, isFileName, 0);
    Track track2= Track(filePath2, isFileName, 0);

    //CHECK THE FINAL RESULT TO MAKE SURE THAT THEY PRODUCE THE SAME OUTPUT.
    BOOST_CHECK_EQUAL(track1.maxSpeed(), track2.maxSpeed());

}




BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>
#include <fstream>
#include "logs.h"
#include "types.h"
#include "track.h"
#include "gridworld_track.h"
#include "xmlgenerator.h"

using namespace GPS;

std::string studentID = "N0733894";

// function to generate a log for each file when implemented..
std::string generateLogs(std::string nameOfTest, GridWorldTrack track)
{
    std::string fileName = GPS::LogFiles::GPXTracksDir + studentID + "_" + nameOfTest + ".gpx";
    std::ofstream fileOutput(fileName);

    fileOutput << track.toGPX(5, true, nameOfTest);
    fileOutput.close();

   return fileName;
}

BOOST_AUTO_TEST_SUITE(track_maxSpeed_N0733894)

bool isFileName = true;


//CHECK RETURNS 0 WHEN TRACK IS STATIONARY
BOOST_AUTO_TEST_CASE( IS_STATIONARY )
{
    //Test name for going in the filename
    std::string testName = "IS_STATIONARY";
    //The track string
    std::string trackString("A1A");
    GridWorldTrack trackLog = GridWorldTrack(trackString, 10, 0, GridWorld(Earth::CliftonCampus, 1000,1000));
    generateLogs(testName, trackLog);

    std::string filePath = GPS::LogFiles::GPXTracksDir + studentID + "_" + testName + ".gpx";

    Track track = Track(filePath, isFileName, 0);

    BOOST_CHECK_EQUAL(track.maxSpeed(), 0);
}




BOOST_AUTO_TEST_SUITE_END()

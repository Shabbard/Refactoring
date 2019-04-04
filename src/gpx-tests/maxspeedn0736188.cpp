#include <boost/test/unit_test.hpp>
#include <fstream>
#include "logs.h"
#include "route.h"
#include "track.h"
#include "gridworld_track.h"
#include "xmlgenerator.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(Track_maxSpeed_N0736188)

std::string generateLogFile(std::string testName, GridWorldTrack track)
{
    std::string fileName = testName + ".gpx";

    std::ofstream fileOutput(GPS::LogFiles::GPXTracksDir + fileName);
    fileOutput << track.toGPX(2,true,testName);
    fileOutput.close();

    return fileName;
}


BOOST_AUTO_TEST_CASE(stationaryTrackTest)
{
    GridWorldTrack trackLog = GridWorldTrack("A1B",3,0);
    std::string logFile  = generateLogFile("stationaryTrackTest", trackLog);
    Track track = Track(LogFiles::GPXTracksDir + logFile, true, 10);
    BOOST_CHECK_EQUAL( track.maxSpeed(), 0);




}

//need to pass position list somehow?


BOOST_AUTO_TEST_SUITE_END()

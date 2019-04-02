#include <boost/test/unit_test.hpp>
#include <fstream>
#include "logs.h"
#include "types.h"
#include "track.h"
#include "gridworld_track.h"
#include "xmlgenerator.h"

using namespace GPS;

// function to generate a log for each file when implemented..
std::string generateLogs(std::string nameOfTest, GridWorldTrack track)
{
    std::string fileName = nameOfTest + ".gpx";
    std::ofstream fileOutput(GPS::LogFiles::GPXTracksDir + fileName);

    fileOutput << track.toGPX(5, true, nameOfTest);
    fileOutput.close();

    return fileName;
}

BOOST_AUTO_TEST_SUITE(track_maxSpeed_N0733894)

bool isFileName = true;

//CHECK RETURNS 0 WHEN TRACK IS STATIONARY
BOOST_AUTO_TEST_CASE(IS_STATIONARY )
{
    GridWorldTrack trackLog = GridWorldTrack("AGM");
    Track track = Track(LogFiles::GPXRoutesDir + generateLogs("IS_STATIONARY", trackLog), isFileName);
    //BOOST_CHECK_EQUAL(track.maxSpeed(), 0);
}

//CHECK RETURNS 0 WHEN TRACK IS STATIONARY
BOOST_AUTO_TEST_CASE(DEPART_EQUAL_ARRIVED )
{
    GridWorldTrack trackLog = GridWorldTrack("AGM");
    Track track = Track(LogFiles::GPXRoutesDir + generateLogs("DEPART_EQUAL_ARRIVED", trackLog), isFileName);
    i//nt arrivedSize = track.arrived.size();
    //BOOST_CHECK_EQUAL(arrivedSize, track.departed.size());
}

//IF DEPARTED SIZE IS NNOT EQUAL TO ARRIVED SIZE

BOOST_AUTO_TEST_SUITE_END()

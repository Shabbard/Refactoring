#include <boost/test/unit_test.hpp>

#include "track.h"
#include "gridworld_track.h"
#include "logs.h"
#include "earth.h"

#include <fstream>

using namespace GPS;

const std::string StudentIDPrefix("N0747947");

void GPXImport(const std::string filepath, const std::string createGPX)
{
    std::ofstream out(filepath);

    out << createGPX;
    out.close();
}

BOOST_AUTO_TEST_SUITE( restingTime )

const bool isFileName = true;

BOOST_AUTO_TEST_CASE( NotResting )
{
    Track track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.restingTime(), 0 );
}

BOOST_AUTO_TEST_CASE( RestingAtOnePoint )
{
    const std::string GPXName("A1A");
    std::string testFilePath(LogFiles::GPXTracksDir + StudentIDPrefix + "_" + GPXName + ".gpx");

    GridWorldTrack gridworldTrack = GridWorldTrack(GPXName, 60, 0,
                                    GridWorld(Earth::CliftonCampus, 1000, 0));

    GPXImport(testFilePath, gridworldTrack.toGPX(60, true, GPXName));

    Track track = Track(testFilePath, true);

    BOOST_CHECK_EQUAL( track.restingTime(), 60 );
}

BOOST_AUTO_TEST_CASE( RestingAtTwoPoints )
{
    const std::string GPXName("B2B");
    std::string testFilePath(LogFiles::GPXTracksDir + StudentIDPrefix + "_" + GPXName + ".gpx");

    GridWorldTrack gridworldTrack = GridWorldTrack(GPXName, 60, 0,
                                    GridWorld(Earth::CliftonCampus, 1000, 0));

    GPXImport(testFilePath, gridworldTrack.toGPX(60, true, GPXName));

    Track track = Track(testFilePath, true);

    BOOST_CHECK_EQUAL( track.restingTime(), 120 );
}

BOOST_AUTO_TEST_SUITE_END()

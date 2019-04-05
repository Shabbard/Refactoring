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

BOOST_AUTO_TEST_SUITE( restingTime_N0747947 )

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
                                    GridWorld(Earth::CliftonCampus, 100, 0));

    GPXImport(testFilePath, gridworldTrack.toGPX(60, true, GPXName));

    Track track = Track(testFilePath, true);

    BOOST_CHECK_EQUAL( track.restingTime(), 60 );
}

BOOST_AUTO_TEST_CASE( RestingAtTwoPoints )
{
    const std::string GPXName("B2B");
    std::string testFilePath(LogFiles::GPXTracksDir + StudentIDPrefix + "_" + GPXName + ".gpx");

    GridWorldTrack gridworldTrack = GridWorldTrack(GPXName, 60, 0,
                                    GridWorld(Earth::CityCampus, 100, 0));

    GPXImport(testFilePath, gridworldTrack.toGPX(60, true, GPXName));

    Track track = Track(testFilePath, true);

    BOOST_CHECK_EQUAL( track.restingTime(), 120 );
}

BOOST_AUTO_TEST_CASE( SingleRestAtStart )
{
    const std::string GPXName("B1B1C1D");
    std::string testFilePath(LogFiles::GPXTracksDir + StudentIDPrefix + "_" + GPXName + ".gpx");

    GridWorldTrack gridworldTrack = GridWorldTrack(GPXName, 60, 0,
                                    GridWorld(Earth::CityCampus, 100, 0));

    GPXImport(testFilePath, gridworldTrack.toGPX(60, true, GPXName));

    Track track = Track(testFilePath, true);

    BOOST_CHECK_EQUAL( track.restingTime(), 60 );
}

BOOST_AUTO_TEST_CASE( SingleRestAtEnd )
{
    const std::string GPXName("A4B3C1C");
    std::string testFilePath(LogFiles::GPXTracksDir + StudentIDPrefix + "_" + GPXName + ".gpx");

    GridWorldTrack gridworldTrack = GridWorldTrack(GPXName, 60, 0,
                                    GridWorld(Earth::CliftonCampus, 100, 0));

    GPXImport(testFilePath, gridworldTrack.toGPX(60, true, GPXName));

    Track track = Track(testFilePath, true);

    BOOST_CHECK_EQUAL( track.restingTime(), 60 );
}

BOOST_AUTO_TEST_CASE( RestingAtMultiplePoints )
{
    const std::string GPXName("A1A3F2F3G1G");
    std::string testFilePath(LogFiles::GPXTracksDir + StudentIDPrefix + "_" + GPXName + ".gpx");

    GridWorldTrack gridworldTrack = GridWorldTrack(GPXName, 60, 0,
                                    GridWorld(Earth::NorthPole, 100, 0));

    GPXImport(testFilePath, gridworldTrack.toGPX(60, true, GPXName));

    Track track = Track(testFilePath, true);

    BOOST_CHECK_EQUAL( track.restingTime(), 240 );
}

BOOST_AUTO_TEST_SUITE_END()

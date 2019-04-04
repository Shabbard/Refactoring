#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "track.h"

#include <iostream>
#include <string>

const std::string N_NumberPrefix = "N0736563-";
const std::string dir = GPS::LogFiles::GPXTracksDir + N_NumberPrefix;

BOOST_AUTO_TEST_SUITE(restingTimeN0736563)

BOOST_AUTO_TEST_CASE(noRestingTime)
{
    GPS::Track track(GPS::LogFiles::GPXTracksDir + "A1B3C.gpx", true);

    BOOST_CHECK_EQUAL(track.restingTime(), 0);
}

BOOST_AUTO_TEST_CASE(stationary)
{
    //Tests cases where the track is completly stationary
    GPS::Track stationary(dir + "Stationary.gpx", true);
    BOOST_CHECK_EQUAL(stationary.restingTime(), 40);
}

BOOST_AUTO_TEST_CASE (singlePointTrack)
{
    //If there is not enought arguments in the gpx data to calculate resting time then the function should throw an invalid argument exception
    GPS::Track singlePointTrack(dir + "SinglePointTrack.gpx", true);
    BOOST_CHECK_THROW(singlePointTrack.restingTime(), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE (onlyElevationChanges)
{
    //Tests cases where only the elevation is changing

    GPS::Track elevationTest1(dir + "ElevationTest1.gpx", true);
    GPS::Track elevationTest2(dir + "ElevationTest2.gpx", true);

    BOOST_CHECK_EQUAL(elevationTest1.restingTime(), 0);
    BOOST_CHECK_EQUAL(elevationTest2.restingTime(), 20);

}

BOOST_AUTO_TEST_SUITE_END();



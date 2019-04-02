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

    BOOST_CHECK_EQUAL(track.restingTime(), 1);

}

BOOST_AUTO_TEST_CASE(stationary)
{
    GPS::Track stationary(dir + "Stationary.gpx", true);

    BOOST_CHECK_EQUAL(stationary.restingTime(), 40);

    GPS::Track test(dir + "ElevationTest.gpx", true);

    std::cout << test.restingTime();

    BOOST_CHECK_EQUAL(stationary.restingTime(), 41);
}

BOOST_AUTO_TEST_SUITE_END();



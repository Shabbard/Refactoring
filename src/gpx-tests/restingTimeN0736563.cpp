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

    //Loads track data which consists of only traveling to the same point(A1A3A)
    GPS::Track stationary(dir + "Stationary.gpx", true);


    BOOST_CHECK_EQUAL(stationary.restingTime(), 40);
}

BOOST_AUTO_TEST_CASE (singlePointTrack)
{
    //If there is not enought arguments in the gpx data to calculate resting time then the function should throw an invalid argument exception

    //Loads GPX data which only contains one point (A)
    GPS::Track singlePointTrack(dir + "SinglePointTrack.gpx", true);
    BOOST_CHECK_THROW(singlePointTrack.restingTime(), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(oneTravel)
{
    //Tests data where the track consists of traveling to a single point

    //Loads data where the track travels once to different point (A1B)
    GPS::Track moving(dir + "OneTravelTest1.gpx", true);
    GPS::Track stationary(dir + "OneTravelTest2.gpx", true);

    BOOST_CHECK_EQUAL(moving.restingTime(), 0);
    BOOST_CHECK_EQUAL(stationary.restingTime(), 10);


}

BOOST_AUTO_TEST_CASE (onlyElevationChanges)
{
    //Resting time is determined by the granularity value. Which only accounts for changes on the horizontal.
    //This tests case ensures that changes in elevation do effect the resting time.

    //For all of the following track data lon and lat stay the same between each point

    //Loads track data where the ele changes every time (C1H1M1R1W)
    GPS::Track elevationTest1(dir + "EleTest1.gpx", true);
    //Loads track data where ele changes twice times then travels to the same point twice (C1H1M1M1M)
    GPS::Track elevationTest2(dir + "EleTest2.gpx", true);

    BOOST_CHECK_EQUAL(elevationTest1.restingTime(), 40);
    BOOST_CHECK_EQUAL(elevationTest2.restingTime(), 40);
}

BOOST_AUTO_TEST_CASE(onlyLonChanges)
{
    //Ensures that longitude is taken into account when calculating the resting time

    //For all of the following track data lat and ele stay the same between each point

    //Loads track data where the lon changes every time (A1B1C1D1E)
    GPS::Track lonTest1(dir + "LonTest1.gpx", true);
    //Loads track data where lon changes twice then travels to the same point twice (A1B1C1C1C)
    GPS::Track lonTest2(dir + "LonTest2.gpx", true);

    BOOST_CHECK_EQUAL(lonTest1.restingTime(), 0);
    BOOST_CHECK_EQUAL(lonTest2.restingTime(), 20);
}

BOOST_AUTO_TEST_CASE(onlyLatChanges)
{
    //Ensures that latitude is taken into account when calculating the resting time

    //For all of the following track data lon and ele stay the same between each point

    //Loads track data where the lat changes every time (A1F1K1P1U)
    GPS::Track latTest1(dir + "LatTest1.gpx", true);
    //Loads track data where lat changes twice then travels to the same point twice (A1F1K1K1K)
    GPS::Track latTest2(dir + "LatTest2.gpx", true);

    BOOST_CHECK_EQUAL(latTest1.restingTime(), 0);
    BOOST_CHECK_EQUAL(latTest2.restingTime(), 20);
}

BOOST_AUTO_TEST_CASE(testGranularity)
{
    //Test cases to ensure that granularity is acounted for when calculating rest time

    //Loads a track where the distance between each point is less than the granularity (A1B1C)
    GPS::Track granTest1(dir + "GranTest1.gpx", true, 20.5);
    //Loads a track and then sets the ganularity to 0 (A1C1F)
    GPS::Track granTest2(dir + "GranTest2.gpx", true, 0);
    //Loads a track where the distance between each point is less than the granularity (A1F1K)
    GPS::Track granTest3(dir + "GranTest3.gpx", true, 20.5);
    //Loads a track where the distance between each point is greater than the granularity (A1K1U)
    GPS::Track granTest4(dir + "GranTest4.gpx", true, 20);
    //Loads a track where there is a mix of points greater than and less than furhter apart than the granularity (A1K1P1U)
    GPS::Track granTest5(dir + "GranTest5.gpx", true, 20.5);

    BOOST_CHECK_EQUAL(granTest1.restingTime(), 20);
    BOOST_CHECK_EQUAL(granTest2.restingTime(), 0);
    BOOST_CHECK_EQUAL(granTest3.restingTime(), 20);
    BOOST_CHECK_EQUAL(granTest4.restingTime(), 0);
    BOOST_CHECK_EQUAL(granTest5.restingTime(), 20);

}

BOOST_AUTO_TEST_SUITE_END();



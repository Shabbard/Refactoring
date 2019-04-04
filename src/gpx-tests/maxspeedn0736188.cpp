#include <boost/test/unit_test.hpp>
#include <fstream>
#include "logs.h"
#include "route.h"
#include "track.h"
#include "gridworld_track.h"
#include "xmlgenerator.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(Track_maxSpeed_N0736188)

//student id
std::string nNumber  = "n0736188";


BOOST_AUTO_TEST_CASE(stationaryTrackTest)
{
   //Tests if the track is stationary (1 point)
    Track track = Track(LogFiles::GPXTracksDir + nNumber + "_stationary.gpx", true, 10);
    BOOST_CHECK_EQUAL( track.maxSpeed(), 0);

}


BOOST_AUTO_TEST_CASE(maxSpeedCheck)
{
    //Tests the function with a pre generated result to test it gives the correct answer
    Track track = Track(LogFiles::GPXTracksDir + nNumber + "_maxspeed.gpx", true, 10);
    BOOST_CHECK_EQUAL( track.maxSpeed(),500.37539277557767);

}

BOOST_AUTO_TEST_CASE(normalAndReverse)
{
    //Tests if reversing a track results in the same max speed
    Track normal = Track(LogFiles::GPXTracksDir + nNumber + "_normal.gpx", true, 10);
    Track reverse = Track(LogFiles::GPXTracksDir + nNumber + "_reverse.gpx", true, 10);

    BOOST_CHECK_EQUAL( normal.maxSpeed(), reverse.maxSpeed());

}





BOOST_AUTO_TEST_SUITE_END()

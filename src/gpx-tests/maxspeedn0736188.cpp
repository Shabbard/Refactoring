#include <boost/test/unit_test.hpp>
#include <fstream>
#include "logs.h"
#include "route.h"
#include "track.h"
#include "gridworld_track.h"
#include "xmlgenerator.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(Track_maxSpeed_N0736188)


std::string nNumber  = "n0736188";

BOOST_AUTO_TEST_CASE(stationaryTrackTest)
{
    Track track = Track(LogFiles::GPXTracksDir + nNumber + "_stationary.gpx", true, 10);
    BOOST_CHECK_EQUAL( track.maxSpeed(), 0);




}

//need to pass position list somehow?


BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "track.h"

#include <iostream>

BOOST_AUTO_TEST_CASE(noRestingTime)
{
    GPS::Track track(/*GPS::LogFiles::GPXRoutesDir + */GPS::LogFiles::GPXTracksDir + "A1B3C.gpx", true);

    BOOST_CHECK_EQUAL(track.restingTime(), 0);
}


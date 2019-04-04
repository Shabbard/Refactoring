#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "route.h"
#include "track.h"
#include <iostream>

BOOST_AUTO_TEST_CASE(Route_maxGradient_n0748944)
{
    GPS::Track Track(/*GPS::LogFiles::GPXRoutesDir +*/GPS::LogFiles::GPXTrackDir + "A1B3C.gpx", true);
    
    BOOST_CHECK_EQUAL(track.maxGradient(), 0);
}

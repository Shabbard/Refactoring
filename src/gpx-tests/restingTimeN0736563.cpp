#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "track.h"


BOOST_AUTO_TEST_CASE(test)
{
    GPS::Track bigTrack(/*GPS::LogFiles::GPXRoutesDir + */GPS::LogFiles::GPXTracksDir + "A1B3C.gpx", true);
}

#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_Find_Position_N0724629 )

const bool isFileName = true;

BOOST_AUTO_TEST_CASE( CanGetLatitude )
{
   	Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("Q").latitude(), Position(-0.89982, -0.898312).latitude() );
}

BOOST_AUTO_TEST_CASE( CanGetLongitude )
{
   	Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("Q").longitude(), Position(-0.89982, -0.898312).longitude() );
}

BOOST_AUTO_TEST_CASE( CanGetElevation )
{
   	Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   	BOOST_CHECK_EQUAL( route.findPosition("Q").elevation(), Position(-0.89982, -0.898312, -20000).elevation() );
}

BOOST_AUTO_TEST_SUITE_END()

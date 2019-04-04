#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_maxLogitudeEqual )

const bool isFileName = true;
const metres horizontalGridUnit = 100000;

BOOST_AUTO_TEST_CASE( ABCD_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), 109.412, 0.0001 );
}

BOOST_AUTO_TEST_CASE( ABQWE_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), 1.79662, 0.0001 );
}

BOOST_AUTO_TEST_CASE( AFKPU_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -1.79662, 0.0001 );
}

BOOST_AUTO_TEST_CASE( ele_absent_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ele_absent.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -0.898312, 0.0001);
}

BOOST_AUTO_TEST_CASE( NorthYorkMoors_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -1.051742434501648, 0.00000000000001 );
}

BOOST_AUTO_TEST_CASE( Q_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -0.898312, 0.0001 );
}

BOOST_AUTO_TEST_CASE( NottinghamToLondon )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NottinghamToLondon.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -0.1234130, 0.00001 );
}

BOOST_AUTO_TEST_CASE( NottinghamToSheffield )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NottinghamToSheffield.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -1.151211, 0.00001 );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( Route_maxLogitudeCheckSmallest )

const bool isFileName = true;
const metres horizontalGridUnit = 100000;

BOOST_AUTO_TEST_CASE( ABCD_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK( route.maxLongitude() != 109.142 );
}

BOOST_AUTO_TEST_CASE( ABQWE_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
   BOOST_CHECK( route.maxLongitude() != -1.79662 );
}

BOOST_AUTO_TEST_CASE( NorthYorkMoors_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK( route.maxLongitude() != -1.120702028274536 );
}

BOOST_AUTO_TEST_SUITE_END()

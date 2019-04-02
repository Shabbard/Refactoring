#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

<<<<<<< HEAD:src/gpx-tests/maxElevation.cpp
using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_maxElevation_N0774756 )

BOOST_AUTO_TEST_CASE( ele_absent )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ele_absent.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), NULL );
}

BOOST_AUTO_TEST_CASE( same_ele )
{
   Route route = Route(LogFiles::GPXRoutesDir + "same_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 309 );
}
=======

//N0745509

using namespace GPS;

BOOST_AUTO_TEST_SUITE( route_netLength )

>>>>>>> 901fdab06ad0e3e089498058c792f869b42e537c:src/gpx-tests/netLength-N0745509.cpp

BOOST_AUTO_TEST_SUITE_END()

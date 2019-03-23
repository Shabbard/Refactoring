#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;





BOOST_AUTO_TEST_SUITE( Route_maxElevation_N0774756 )

BOOST_AUTO_TEST_CASE( ele_absent )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ele_absent.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), NULL );
}

BOOST_AUTO_TEST_SUITE_END()

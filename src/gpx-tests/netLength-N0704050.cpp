#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(Route_netLength_N0704050)

const bool isFileName = true;


BOOST_AUTO_TEST_CASE ( direct_from_AtoB )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0704050GPX.gpx", isFileName);
    
   BOOST_CHECK_EQUAL (route.netLength(), 1 );
        
}

BOOST_AUTO_TEST_SUITE_END()

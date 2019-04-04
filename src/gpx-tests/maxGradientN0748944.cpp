#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "route.h"
#include "geometry.h"
#include <iostream>

using namespace GPS;


const bool isFileName = true;


BOOST_AUTO_TEST_CASE(Route_maxGradient_ABCD_is0)
{
    Route Route = Route(logFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.maxGradient(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

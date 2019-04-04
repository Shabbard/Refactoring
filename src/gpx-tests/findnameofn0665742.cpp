#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include <iostream>



using namespace GPS;


BOOST_AUTO_TEST_SUITE( route_findnameofn0665742 )

const bool isFileName = true;
const metres horizontalGridUnit = 100000;


// Find the name of a route point.
// Throws a std::out_of_range exception if that Position is not within "granularity" of any stored route points.



BOOST_AUTO_TEST_CASE(nameof)
{
    Route route = Route(LogFiles::GPXRoutesDir+ "ABQWE.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.findNameOf(Position),"ABQWE");
}

BOOST_AUTO_TEST_CASE(nonExistantPosition)
{
    const metres granularity = horizontalGridUnit/10;
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName,granularity);
    BOOST_CHECK_THROW( route.findNameOf(Position), std::out_of_range);
}


BOOST_AUTO_TEST_SUITE_END()


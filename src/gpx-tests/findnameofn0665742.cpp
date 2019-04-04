#define BOOST_TEST_MODULE FindNameOf //introduces a top-level Boost UTF test suite named MyModuleName=FindNameOf
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


//Test to check that the fuction can find the postion at a point with all positive value of Latitude, Longitude and elevation in the GPX log file.
BOOST_AUTO_TEST_CASE(PositionWithPositiveValue)
{
    Route route = Route(LogFiles::GPXRoutesDir+ "N0665742-PositiveValue.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.findNameOf(Position(0.089982,109.232,0.000000)),"T");
}

//Test to check that the fuction can find the postion at a point with all negative value of Latitude, Longitude and elevation in the GPX log file.
BOOST_AUTO_TEST_CASE(PositionWithNegativeValue)
{
    Route route = Route(LogFiles::GPXRoutesDir+ "N0665742-NegativeValue.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.findNameOf(Position(-0.89982,-1.79662,-40000.000000)),"N");
}

//Test to check that the fuction can find the postion at a point with both Positive and Negative value in the GPX log file.
BOOST_AUTO_TEST_CASE(PositionWithPositiveAndNegativeValue)
{
    Route route = Route(LogFiles::GPXRoutesDir+ "N0665742.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.findNameOf(Position(1.79964,-1.79662,-40000.000000)),"N");
}

//Test to check the function throw out_of_range exception if that Position is not within "granularity" of any stored route points.
BOOST_AUTO_TEST_CASE(NonExistantPosition)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0665742.gpx", isFileName);
    BOOST_CHECK_THROW( route.findNameOf(Position(0,0,0.000000)), std::out_of_range);
}


BOOST_AUTO_TEST_SUITE_END()

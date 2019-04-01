#include <boost/test/unit_test.hpp>
#include "../../headers/position.h"
#include "../../headers/route.h"
#include "../../headers/logs.h"
using namespace GPS;

// Tests created by James bray, N0731234


BOOST_AUTO_TEST_SUITE(Route_maxLatitude)

BOOST_AUTO_TEST_CASE(expected_max)
{
    // test with just one possible outcome
    Route route1 = Route(LogFiles::logsDir+"Q.gpx", true);
    BOOST_CHECK_EQUAL(route1.maxLatitude(),Position(-0.89982, -0.898312));

    // test with multiple inputs
    Route route2 = Route(LogFiles::logsDir+"ABQWE.gpx",true);
    BOOST_CHECK_EQUAL(route2.maxLatitude(),Position(1.79964,-1.79662));

    // test with wrong input
    Route route3 = Route(LogFiles::logsDir+"Q.gpx",true);
}

BOOST_AUTO_TEST_CASE(no_data){
    Route route = Route(LogFiles::logsDir+"Q.gpx", false);
    BOOST_TEST_MESSAGE(route.maxLatitude());
}

BOOST_AUTO_TEST_CASE(null_position_list)
{
    // check to see if Null values are handled
    // Route route = Route();
    // BOOST_CHECK_THROW(route.maxLatitude(), std::is_null_pointer);
}

BOOST_AUTO_TEST_CASE(incorrect_data)
{
    // check wether 

}


BOOST_AUTO_TEST_SUITE_END();

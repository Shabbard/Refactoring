#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "position.h"
#include "route.h"
#include "gridworld.h"
#include "gridworld_track.h"
#include "gridworld_route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(Route_accessOperator)

const bool isFileName = true;

GridWorld gridWorld;

// Tests accessing a position on the route under normal circumstances.
BOOST_AUTO_TEST_CASE(ItCanAccessAPositionAtAnIndex)
{
    GridWorldTrack track = GridWorldTrack("ABCD", 10, 0, gridWorld);
    GridWorldRoute worldRoute = GridWorldRoute(track.toString(), gridWorld);
    Route route = Route(worldRoute.toGPX(), false);
    BOOST_CHECK_EQUAL(route[0].toString(), gridWorld['A'].toString());
}

BOOST_AUTO_TEST_CASE(ItReturnsEmptyWithAnEmptyRoute)
{
    // Route route = Route(generator.closeAllElementsAndExtractString(), false);
    // BOOST_CHECK_THROW(route[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ItThrowsAnExceptionWhenTryingToAccessOutOfRange)
{
    GridWorldTrack track = GridWorldTrack("A", 10, 0, gridWorld);
    GridWorldRoute worldRoute = GridWorldRoute(track.toString(), gridWorld);
    Route route = Route(worldRoute.toGPX(), false);
    BOOST_CHECK_THROW(route[1], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ItCantAccessDataOutsideOfLogicalBounds)
{
    //
}

BOOST_AUTO_TEST_CASE(ItDoesntAcceptANegativeIndex)
{
    //
}

BOOST_AUTO_TEST_SUITE_END()


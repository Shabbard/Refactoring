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

GridWorldRoute generateRoute(const GridWorldTrack & track)
{
    return GridWorldRoute(track.toString(), gridWorld);
}

// Tests accessing a position on the route under normal circumstances.
BOOST_AUTO_TEST_CASE(ItCanAccessAPositionAtAnIndex)
{
    GridWorldTrack track = GridWorldTrack("ABCD", 10, 0, gridWorld);
    GridWorldRoute worldRoute = GridWorldRoute(track.toString(), gridWorld);
    Route route = Route(worldRoute.toGPX(), false);
    BOOST_CHECK_EQUAL(route[0].toString(), gridWorld['A'].toString());
}

// Ensures that the appropriate exception is thrown when trying to 
// access a position at an index greater than the number of positions
BOOST_AUTO_TEST_CASE(ItThrowsAnExceptionWhenTryingToAccessOutOfRange)
{
    GridWorldTrack track = GridWorldTrack("A", 10, 0, gridWorld);
    Route route = Route(generateRoute(track).toGPX(), false);

    BOOST_CHECK_THROW(route[1], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(ItAccessRepeatedPointsCorrectly)
{
    GridWorldTrack track = GridWorldTrack("MHMR", 10, 0, gridWorld);
    Route route = Route(generateRoute(track).toGPX(), false);

    BOOST_CHECK_EQUAL(route[0].toString(), gridWorld['M'].toString());
    BOOST_CHECK_EQUAL(route[2].toString(), gridWorld['M'].toString());
}

BOOST_AUTO_TEST_CASE(ItDoesntAcceptANegativeIndex)
{
    GridWorldTrack track = GridWorldTrack("A", 10, 0, gridWorld);;
    Route route = Route(generateRoute(track).toGPX(), false);
    BOOST_CHECK_THROW(route[-1], std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()


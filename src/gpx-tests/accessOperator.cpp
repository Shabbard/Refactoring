#include <boost/test/unit_test.hpp>

#include <limits> 

#include "logs.h"
#include "position.h"
#include "route.h"
#include "gridworld_route.h"

#include "accessOperatorLogGenerator.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(Route_accessOperator)

const std::string singlePointFilename = "A.gpx";

// Tests accessing a position on the route under normal circumstances.
BOOST_AUTO_TEST_CASE(ItCanAccessAPositionAtAnIndex)
{
    GridWorldRoute generatedRoute = GPX::singlePositionLog(singlePointFilename);
    Route route = Route(LogFiles::GPXRoutesDir + singlePointFilename, true);

    BOOST_CHECK_NO_THROW(route[0]);
}

// Ensures that the appropriate exception is thrown when trying to 
// access a position at an index greater than the number of positions
BOOST_AUTO_TEST_CASE(ItThrowsAnExceptionWhenTryingToAccessOutOfRange)
{
    GridWorldRoute generatedRoute = GPX::singlePositionLog(singlePointFilename);
    Route route = Route(LogFiles::GPXRoutesDir + singlePointFilename, true);

    BOOST_CHECK_THROW(route[1], std::out_of_range);
}

// -1 will get implicitly converted to a large version of an unsigned integer
// which will be a large value of an unsigned int.
BOOST_AUTO_TEST_CASE(ItDoesntAcceptANegativeIndex)
{
    GridWorldRoute generatedRoute = GPX::singlePositionLog(singlePointFilename);
    Route route = Route(LogFiles::GPXRoutesDir + singlePointFilename, true);

    BOOST_CHECK_THROW(route[-1], std::out_of_range);
}

// this test will change depending on the implementation present on the
// machine running the executable.
BOOST_AUTO_TEST_CASE(ItHandlesAnIntegerOverflowWithAnOutOfRange)
{
    const unsigned int maximumUIntIndex = std::numeric_limits<unsigned int>::max();
    GridWorldRoute generatedRoute = GPX::singlePositionLog(singlePointFilename);
    Route route = Route(LogFiles::GPXRoutesDir + singlePointFilename, true);

    BOOST_CHECK_THROW(route[maximumUIntIndex], std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
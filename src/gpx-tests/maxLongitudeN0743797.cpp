#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_maxLongitude_N0743797 )

const bool isFileName = true;

/* The maxLongitude function is used to return the most easternly
 * value for a given point. Hence to test this function, first
 * the function should be tested for null values, then values beyond
 * the limits of Longitude should be tested. Multiple points with
 * the same maximum in the route should also be tested.
 * Then real values can be tested to make sure the correct maximum
 * longitude is returned.
 */

BOOST_AUTO_TEST_SUITE_END()

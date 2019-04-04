#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "route.h"

using namespace GPS;

const degrees PERCENTAGE_ACCURACY = 0.1;
const metres GRADIENT = 5.71059; // calculated by taking the arctan of 1000/10000

/* The steepest gradient is the largest gradient by magnitude.
 * 
 * Gradient is calculated from the difference in the y values over (divided by) the
 * difference in x values between two points.
 * 
 * The key for finding the steepest gradient is that you must ignore the sign i.e the positive or negative aspect
 * of the number, taking only its absolute value. 
*/

BOOST_AUTO_TEST_SUITE( Steepest_Gradient )

const bool isFileName = true;

// check if there are any points in the file

BOOST_AUTO_TEST_CASE( Route_with_no_points )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteWithNoPoints.gpx", isFileName);

    BOOST_CHECK_CLOSE( route.steepestGradient(),  0, PERCENTAGE_ACCURACY);
}

// You cannot calculate a gradient from just one point, the program should return 0
BOOST_AUTO_TEST_CASE( Route_with_one_point )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);

    BOOST_CHECK_CLOSE( route.steepestGradient(),  0, PERCENTAGE_ACCURACY);
}

// two points on top of each other should have a gradient of 0
BOOST_AUTO_TEST_CASE( Route_with_two_vertical_points )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteWithTwoVerticalPoints.gpx", isFileName);
    
    BOOST_CHECK_CLOSE( route.steepestGradient(),  0, PERCENTAGE_ACCURACY);
}

// two points with no elevation difference should have a gradient of 0
BOOST_AUTO_TEST_CASE( Route_with_two_horizontal_points )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteWithTwoHorizontalPoints.gpx", isFileName);

    BOOST_CHECK_CLOSE( route.steepestGradient(),  0, PERCENTAGE_ACCURACY);
}

// check values with only negative gradients, should return a positive gradient
BOOST_AUTO_TEST_CASE( Route_with_only_negative_gradients )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteWithOnlyNegativeGradients.gpx", isFileName);

    BOOST_CHECK_CLOSE( route.steepestGradient(),  GRADIENT, PERCENTAGE_ACCURACY);
}

// check different values with only positive gradients, should return a positive gradient
BOOST_AUTO_TEST_CASE( Route_with_only_positive_gradients )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteWithOnlyPositiveGradients.gpx", isFileName);

    BOOST_CHECK_CLOSE( route.steepestGradient(),  GRADIENT, PERCENTAGE_ACCURACY);
}

// check values with both positive and negative gradients, should return a positive gradient
BOOST_AUTO_TEST_CASE( Route_with_positive_and_negative_gradients )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteWithPositiveAndNegativeGradients.gpx", isFileName);

    BOOST_CHECK_CLOSE( route.steepestGradient(),  GRADIENT, PERCENTAGE_ACCURACY);
}

// check values with the steepest gradient being at the beginning, middle and end of the list of points

BOOST_AUTO_TEST_SUITE_END()
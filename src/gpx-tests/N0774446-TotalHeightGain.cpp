#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"

using namespace GPS;

//Test Suite to check the totalHeightGain function
BOOST_AUTO_TEST_SUITE(N0774446_TotalHeightGain)

const bool isFileName = true;

//Case to make sure the calculations are correct when subtracting negative numbers in an incline.
BOOST_AUTO_TEST_CASE(inclineBelowSeaLevel)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-InclineBelowSeaLevel.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 100);
}

//Case to make sure the the calculations of negative to positive numbers being subtracted are correct accross sea level.
BOOST_AUTO_TEST_CASE(inclineAcrossSeaLevel)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-InclineAcrossSeaLevel.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 100);
}

//Case to make sure the calculations of positive to negative are correct with changing signs and making sure it registers as a decline.
BOOST_AUTO_TEST_CASE(declineAcrossSeaLevel)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-DeclineAcrossSeaLevel.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 0);
}

//make sure that after a decline it only counts the positive incline from 0.
BOOST_AUTO_TEST_CASE(declineIncline)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-Decline-Incline.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 100);
}

//make sure that the decline that is followed doe not affect the total height gaines thus far.
BOOST_AUTO_TEST_CASE(inclineDecline)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-Incline-Decline.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 100);
}

//Checking that multiple inclines and declines changing from about and below sea level is correctly calculated.
BOOST_AUTO_TEST_CASE(changeAcrossSeaLevel)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-ChangeAcrossSeaLevel.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 60000);
}

//make sure that if there is only 1 position then it doesn't try and find a second vector and create an error so it should always be 0.
BOOST_AUTO_TEST_CASE(singlePosition)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-SinglePosition.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 0);
}

//make sure that it can handle a situation where there are multiple large in increases and that the result is correct.
BOOST_AUTO_TEST_CASE(largeIncrease)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-LargeIncrease.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 26000000000);
}

//Case to make sure the function isn't limited by data types and can handle small numbers for a tiny increase value.
BOOST_AUTO_TEST_CASE(smallIncrease)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-SmallIncrease.gpx", isFileName);
	BOOST_CHECK_CLOSE(route.totalHeightGain(), 0.00026, 0.0000000001);
}

BOOST_AUTO_TEST_SUITE_END()
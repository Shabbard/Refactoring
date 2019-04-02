#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(N0774446-TotalHeightGain)

const bool isFileName = true;

BOOST_AUTO_TEST_CASE(inclineBelowSeaLevel)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-InclineBelowSeaLevel.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 100);
}

BOOST_AUTO_TEST_CASE(inclineAcrossSeaLevel)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-InclineAcrossSeaLevel.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 100);
}

BOOST_AUTO_TEST_CASE(declineAcrossSeaLevel)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-DeclineAcrossSeaLevel.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 0);
}

BOOST_AUTO_TEST_CASE(declineIncline)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-Decline-Incline.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 100);
}

BOOST_AUTO_TEST_CASE(inclineDecline)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-Incline-Decline.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 100);
}

BOOST_AUTO_TEST_CASE(changeAcrossSeaLevel)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-ChangeAcrossSeaLevel.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 60000);
}

BOOST_AUTO_TEST_CASE(singlePosition)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-SinglePosition.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 0);
}

BOOST_AUTO_TEST_CASE(largeIncrease)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-LargeIncrease.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 26000000000);
}
BOOST_AUTO_TEST_CASE(smallIncrease)
{
	Route route = Route(LogFiles::GPXRoutesDir + "N0774446-SmallIncrease.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 0.00026, 0.0000000001);
}

BOOST_AUTO_TEST_SUITE_END()
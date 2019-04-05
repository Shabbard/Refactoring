#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(N0733719-TotalHeightGain)

const bool isFileName = true;

BOOST_AUTO_TEST_CASE(2PointDecrease){
//test if a decrease between 2 points is ignored
	Route route = Route(LogFiles::GPXRoutesDir + "2PointDesrease-N0733719.gpx",isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(), 0)//equals 0 because of no height gain
}

BOOST_AUTO_TEST_CASE(2PointIncrease){
//test if an increase between 2 points is recorded
	Route route = Route(LogFiles::GPXRoutesDir + "2PointIncrease-N0733719.gpx",isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(),88.51)//88.51 is height gained between points in test file
}

BOOST_AUTO_TEST_CASE(3PointDecrease){
//test if a decrease between 3 points is ignored
	Route route = Route(LogFiles::GPXRoutesDir + "3PointDecrease-N0733719.gpx",isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(),0)//equals 0 because of no height gain
}

BOOST_AUTO_TEST_CASE(3PointIncrease){
//test if an increse between 3 points is recorded
	Route route = Route(LogFiles::GPXRoutesDir + "3PointsIncrease-N0733719.gpx",isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(),1225.24)//1225.24 is height gained in test file
}

BOOST_AUTO_TEST_CASE(4PointIncreaseDecrease){
//test if increases are recorded and decreases are ignore within the same file
	Route route = Route(LogFiles::GPXRoutesDir + "4PointIncreaseDecrease-N0733719.gpx",isFilename);
	BOOST_CHECK_EQUAL(route.totalHeightGain(),2019.82)//2019.82 is the sum of all positive height changes, ignoring all negative changes 

}

BOOST_AUTO_TEST_CASE(largeIncrease){
//check that a large increase is recorded
	Route route = Route(LogFiles::GPXRoutesDir + "largeIncrease-N0733719.gpx",isFileName);
	BOOST_CHECK_EQUAL(route.totalHeightGain(),8804.04)//8804.04 is the height gained between the two points 
}

BOOST_AUTO_TEST_SUITE_END()

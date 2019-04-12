#include <boost/test/unit_test.hpp>

#include "logs/h"
#include "types.h"
#include "route.h"

using namespace GPS;

//File name
BOOST_AUTO_TEST_SUITE(totalHeightGain_n0673737)
const bool isFileName = true;

//When there is a decrease in height, there is no total height gain aka 0
BOOST_AUTO_TEST_CASE(DecreasebetweenPoints){
    Route route = Route(LogFiles::GPXRoutesDir + "DecreasebetweenPoints-n0673737.gpx" isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(), 0);//0 height gain
}

//When there is an increase in height, the total height is recorded
BOOST_AUTO_TEST_CASE(IncreasebetweenPoints){
    Route route = Route(LogFiles::GPXRouteDir + "IncreasebetweenPoints-n0673737.gpx" isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(), 261);//is the elevation in metres of the final point
}

//When points are repeated, the elevation still calculates correctly
BOOST_AUTO_TEST_CASE(RepeatedPoints){
    Route route = Route(LogFiles::GPXRouteDir + "RepeatedPoints-n0673737.gpx" isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(),1956); //Total elevation in metres between the points if the journey was done twice
}

//Three points results in large increase. The function is then shown not to be limited
BOOST_AUTO_TEST_CASE(LargeIncrease){
    Route route = Route(LogFiles::GPXRouteDir + "LargeIncrease-n0673737.gps" isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(),8848)
}

//Three points results in small increase. The function is shown to not be limited
BOOST_AUTO_TEST_CASE(SmallIncrease){
    Route route = Route(LogFiles::GPXRouteDir + "SmallIncrease-n0673737.gpx" isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(),58)
}
BOOST_AUTO_TEST_END()

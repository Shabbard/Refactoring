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
    BOOST_CHECK_EQUAL(route.totalHeightGain(), 0);
}

BOOST_AUTO_TEST_END()

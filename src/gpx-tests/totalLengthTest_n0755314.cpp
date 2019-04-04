#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "types.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE (Route_totalLength)

const bool isFileName = true;
const metres horizontalGridUnit = 10000;
const double percentage = 1;

//Longitude change does not result in negative change of distance, ex west to east and then east to west does not result in 0
BOOST_AUTO_TEST_CASE (negativeChangeCheck)
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABA.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.totalLength(), 20000, percentage); //BOOST_CHECK_CLOSE as distance is a floating point
}

//2 close route points == correct total length (10,000 as default horizontal distance from one grid point to another is 10,000)
BOOST_AUTO_TEST_CASE (shortDistanceCheck)
{
    Route route = Route(LogFiles::GPXRoutesDir + "AB.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.totalLength(), 10000, percentage);
}

//2 far route points == correct total length (56,568 metres)
// A B C D E
// F G H I J
//Given the previous grid, travelling from point A to G would be equal to (A^2 = G^2 + B^2) which if the distance from
//point A to point B is 10,000 and B to G 10,000. Would be equal to 14,142 metres.
BOOST_AUTO_TEST_CASE (longDistanceCheck)
{
    Route route = Route(LogFiles::GPXRoutesDir + "AY.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.totalLength(), 56568, percentage); //Point A to Y would be equal to 4 x 14,142 ~= 56568
}

//Checks the summing of 6 route points, in addition to 1 point which goes back by 4 route points
BOOST_AUTO_TEST_CASE (multipleSummingCheck)
{
    Route route = Route(LogFiles::GPXRoutesDir + "AEFLMI.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.totalLength(), 119545, percentage);//A-E (40,000), E-F (41,261), F-L (14,142), L-M (10,000), M-I (14,142)
}

//Checks if route points are slighlty more than granularity apart (first boundary check)
BOOST_AUTO_TEST_CASE (firstGranularityCheck)
{
    const metres granularity = horizontalGridUnit * 0.99;
    Route route = Route(LogFiles::GPXRoutesDir + "AB.gpx", isFileName, granularity);
    BOOST_CHECK_CLOSE(route.totalLength(), 10000, percentage);
} //Change to close

//Checks if route points are slightly less than granularity apart (second boundary check)
BOOST_AUTO_TEST_CASE (secondGranularityCheck)
{
    const metres granularity = horizontalGridUnit * 1.01;
    Route route = Route(LogFiles::GPXRoutesDir + "AB.gpx", isFileName, granularity);
    BOOST_CHECK_CLOSE(route.totalLength(), 0, percentage);
}

//Total length is == 0 if the route points are less than 'granularity' of each other
BOOST_AUTO_TEST_CASE (lessThanGranularity)
{
    Route route = Route(LogFiles::GPXRoutesDir + "AB.gpx", isFileName, 20000);
    BOOST_CHECK_EQUAL(route.totalLength(), 0);//BOOST_CHECK_EQUAL used as the total length will always be 0 if test passes
}

BOOST_AUTO_TEST_SUITE_END()

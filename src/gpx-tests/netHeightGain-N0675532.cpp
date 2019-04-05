#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "types.h"
#include "gridworld_route.h"

using namespace GPS;

const std::string studentId("N0675532");


//Max Hughes - N0675532
/*The netHeightGain function calculatesthe net gain of the height over a route.
*
*This is diffirent to toal height gain as net will produce the increase from the start point to the end point, 
*as opposed to total which will add all of the increases over a route together
*
*If the net height gain is nagative i.e. the end point is lower than the start then it will be disregarded
*/

BOOST_AUTO_TEST_SUITE( Route_netHeightGain )

const bool isFileName = true;

/*
*Test name: throwsOutOfRangeIfNetHeightGainNotFound
*Test: Checks that an out of range exception is thrown if netHeightGain is not found
*Type: Invalid
*/

BOOST_AUTO_TEST_CASE( throwsOutOfRangeIfNetHeightGainNotFound )
{
	Route route = Route(LogFiles::GPXRoutesDir + "throwsOutOfRangeIfNetHeightGainNotFound-N0724629.gpx", isFileName);
    BOOST_CHECK_THROW( route.netHeightGain(), std::out_of_range );
    
}

/*
*Test name: isNetHeightNegative
*Test: Checks that 0 will be returned if the netHeightGain is negative
*Type: Valid
*/

BOOST_AUTO_TEST_CASE( isNetHeightNegative )
{
	Route route = Route(LogFiles::GPXRoutesDir + "isHeightNegative-N0675532.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netHeightGain(), 0);
}




BOOST_AUTO_TEST_SUITE_END()
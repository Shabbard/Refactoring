// N0679817 - Tomas Blundell - netHeightGain() Boost test // 

#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "route.h"
#include "types.h"
#include "gridworld_route.h"
#include "xmlgenerator.h"

#include <fstream>


// The increase in height from the start point to the finishing point.
// Should return zero if the height difference is negative.

/*

metres Route::totalHeightGain() const
{
    assert(! positions.empty());

    metres total = 0.0;
    for (unsigned int i = 1; i < numPositions(); ++i)
    {
        metres deltaV = positions[i].elevation() - positions[i-1].elevation();
        if (deltaV > 0.0) total += deltaV; // ignore negative height differences
    }
    return total;
}

*/

using namespace GPS;

// Will generate a GPX log file 
std::string generateTheLogs(std::string testName, GridWorldRoute route)
{

	//Creates a name based on the test name and appends my N number and .gpx onto it
	std::string name = testName + "-N0679817.gpx";
	std::ofstream fileOutput(LogFiles::GPXRoutesDir + name);
	fileOutput << route.toGPX(true, testName);
	fileOutput.close();

	return name;

}

/////////////////////////////////////////////
/////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Route_netHeightGain )

const bool isFileName = true;

// Checks that a negative NetGain returns a zero.
BOOST_AUTO_TEST_CASE( checkNegativeNetGain )
{

	GridWorldRoute routeLog = GridWorldRoute("AY");
	Route route = Route(LogFiles::GPXRoutesDir + generateTheLogs("negativeNetGain", routeLog), isFileName);
	BOOST_CHECK_EQUAL( route.netHeightGain(), 0 );

}

BOOST_AUTO_TEST_SUITE_END()


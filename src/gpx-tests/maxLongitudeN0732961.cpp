#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_maxLogitudeN0732961 )

const bool isFileName = true;
const metres horizontalGridUnit = 100000;

//Testing a small route
BOOST_AUTO_TEST_CASE( Short_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), 109.412, 0.0001 );
}

//Testing A edge case for the shorest route
BOOST_AUTO_TEST_CASE( Shortest_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -0.898312, 0.0001 );
}

//Testing the other edge case as it is the longest given
BOOST_AUTO_TEST_CASE( Longest_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -1.051742434501648, 0.00000000000001 );
}

//Testing the function will give the correct output when there is no change in Longitude
BOOST_AUTO_TEST_CASE( No_Change_In_Longitude_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -1.79662, 0.0001 );
}

// Testing the fuction gives the correct output when the point has already been visited once
BOOST_AUTO_TEST_CASE( Repeated_Point_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABA.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), 109.232, 0.0001 );
}

//Testing a route that I generated that goes from north to south
BOOST_AUTO_TEST_CASE( NottinghamToLondon )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NottinghamToLondon.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -0.1234130, 0.00001 );
}

//Testing a route that I generated that goes from south to north
BOOST_AUTO_TEST_CASE( NottinghamToSheffield )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NottinghamToSheffield.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -1.151211, 0.00001 );
}

BOOST_AUTO_TEST_SUITE_END()


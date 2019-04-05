#include <boost/test/unit_test.hpp>

#include <fstream>
#include "gridworld.h"
#include "gridworld_route.h"
#include "xmlgenerator.h"

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_maxLongitude_N0743797 )

const bool isFileName = true;

// The longitude of the most Easterly point on the Route.

/* generateGPX is a auxillary function used to generate a GPX files
 * based on a given route. It uses the following GridWorld system.
 *
 * A B C D E
 * F G H I J
 * K L M N O
 * P Q R S T
 * U V W X Y
*/

std::string generateGPX(std::string logName, GridWorldRoute route)
{
    std::string fileName = logName;
    std::ofstream GPXFile(GPS::LogFiles::GPXRoutesDir + fileName);

    GPXFile << route.toGPX(true, logName);
    GPXFile.close();

    return fileName;
}

// To test a single pointed route, this checks any loops the function may have
// and makes sure that the function returns the only value in the route.
BOOST_AUTO_TEST_CASE( single_Point )
{
   GridWorldRoute routeLog = GridWorldRoute("E");
   Route route = Route(LogFiles::GPXRoutesDir + generateGPX("singlePoint-N0743797.gpx", routeLog), isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 109.502);
}

// Tests a route with points all having the same longitude values.
BOOST_AUTO_TEST_CASE( same_Longitude )
{
   GridWorldRoute routeLog = GridWorldRoute("DINS");
   Route route = Route(LogFiles::GPXRoutesDir + generateGPX("sameLongitude-N0743797.gpx", routeLog), isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 109.41200000000001);
}

// Checks that the function can differentiate between signed numbers
BOOST_AUTO_TEST_CASE( mixed_Sign_Longitude )
{
   GridWorld gridworld = GridWorld(Earth::EquatorialMeridian, 100000, 0);
   GridWorldRoute routeLog = GridWorldRoute("KLMN", gridworld);
   Route route = Route(LogFiles::GPXRoutesDir + generateGPX("longitudeSigned-N0743797", routeLog), isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 0.898312);
}

// Checks the function can find the most positive number from all negatively signed ones.
BOOST_AUTO_TEST_CASE( negative_Signed_Longitude )
{
   GridWorld gridworld = GridWorld(Earth::EquatorialMeridian, 100000, 0);
   GridWorldRoute routeLog = GridWorldRoute("PQ", gridworld);
   Route route = Route(LogFiles::GPXRoutesDir + generateGPX("longitudeNegative-N0743797.gpx", routeLog), isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -0.898312);
}

// Checks that the function does not use rounding by using longitudes to 15 decimals places.
// Set granularity to 0 to allow this to work.
BOOST_AUTO_TEST_CASE( very_Close_Longitude )
{
   Route route = Route(LogFiles::GPXRoutesDir + "closeLongitude-N0743797.gpx", isFileName, 0);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -1.199999999999998);
}

BOOST_AUTO_TEST_SUITE_END()

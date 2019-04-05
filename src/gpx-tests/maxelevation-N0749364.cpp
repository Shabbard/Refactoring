#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(Route_MaxElevation)

const bool isFileName = true;
/* This variable allows for some for flexbility when comparing floating point numbers,
 * in this case the stated max elevation and elevations of different positions from a route,
 * as floating point calculations can be inaccurate, which would lead to issues comparing elevations.
 */

float FloatAccuracyTolerance = 0.1;


/* Route.MaxElevation() tests the max elevation of each route.
 * It does this by taking the elevations from each of the positios of a route
 * and then compares them to a value that should the maximum elevation of a route.
 * If any of the elevations equal this value and none are higher than this value, then test will pass.
 * If any of the elevations are larger than the value or none of them equal the value then the test will fail.
 */


BOOST_AUTO_TEST_CASE( Zero_MaxElevation_route )
{  //Tests if the maxElevation function handle a route with the max elevation of 0
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_CLOSE(route.maxElevation(), 0.0, FloatAccuracyTolerance );
   //(test, max elevation (what your checking for), accuracy)

}

BOOST_AUTO_TEST_CASE( Positive_MaxElevation_route )
{  //Tests if the maxElevation function handle a route with a postive max elevation
   Route route = Route(LogFiles::GPXRoutesDir + "PositiveElevationN0749364.gpx", isFileName);
   BOOST_CHECK_CLOSE(route.maxElevation(), 53.0, FloatAccuracyTolerance );

}


BOOST_AUTO_TEST_CASE( Negative_MaxElevation_route )
{  //Tests if the maxElevation function handle a route with a negative max elevation
   Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
   BOOST_CHECK_CLOSE(route.maxElevation(), -20000.0, FloatAccuracyTolerance );

}


BOOST_AUTO_TEST_CASE( ShortRoutes_MaxElevation_route )
{
   //Tests if the maxElevation function can find the max elevation from GPX files which has a small route.
   Route route1 = Route(LogFiles::GPXRoutesDir + "ShortRouteN0749364.gpx", isFileName);
   BOOST_CHECK_CLOSE(route1.maxElevation(), -1200.0, FloatAccuracyTolerance );
   Route route2 = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
   BOOST_CHECK_CLOSE(route2.maxElevation(), -20000.0, FloatAccuracyTolerance );
}


BOOST_AUTO_TEST_CASE( LongRoute_MaxElevation_route )
{
   //Tests if the maxElevation function can find the max elevation from a GPX file which has a long route.
   Route route = Route(LogFiles::GPXRoutesDir + "LongRouteN0749364.gpx", isFileName);
   BOOST_CHECK_CLOSE(route.maxElevation(), 0.0, FloatAccuracyTolerance );
}


BOOST_AUTO_TEST_CASE(Uphill_MaxElevation_route)
{
   /* Tests generated routes with elevations which increase towards the end of the route,
    * the purpose of this is to check that the MaxElevation function can handle elevations increase and still find the max elevation.
    */

   Route UProute1 = Route(LogFiles::GPXRoutesDir + "UphillCityCampusN0749364.gpx", isFileName);
   BOOST_CHECK_CLOSE(UProute1.maxElevation(), 53.0, FloatAccuracyTolerance );

   Route UProute2 = Route(LogFiles::GPXRoutesDir + "UphillCliftonCampusN0749364.gpx", isFileName);
   BOOST_CHECK_CLOSE(UProute2.maxElevation(), 58.0, FloatAccuracyTolerance );

   Route UProute3 = Route(LogFiles::GPXRoutesDir + "UphillNorthPoleN0749364.gpx", isFileName);
   BOOST_CHECK_CLOSE(UProute3.maxElevation(), 0.0, FloatAccuracyTolerance );

}


BOOST_AUTO_TEST_CASE(Downhill_MaxElevation_route)
{
   /* Tests generated routes with elevations which decrease towards the end of the route,
    * the purpose of this is to check that the MaxElevation function can handle elevations decrease and still find the max elevation.
    */
   Route Downroute1 = Route(LogFiles::GPXRoutesDir + "DownhillCityCampusN0749364.gpx", isFileName);
   BOOST_CHECK_CLOSE(Downroute1.maxElevation(), 53.0, FloatAccuracyTolerance );

   Route Downroute2 = Route(LogFiles::GPXRoutesDir + "DownhillCliftonCampusN0749364.gpx", isFileName);
   BOOST_CHECK_CLOSE(Downroute2.maxElevation(), 58.0, FloatAccuracyTolerance );

   Route Downroute3 = Route(LogFiles::GPXRoutesDir + "DownhillNorthPoleN0749364.gpx", isFileName);
   BOOST_CHECK_CLOSE(Downroute3.maxElevation(), 0.0, FloatAccuracyTolerance );

}

BOOST_AUTO_TEST_CASE(Flat_MaxElevation_route)
{
    /* Tests generated routes with elevations which neither increase or decrease throughout the route,
     * the purpose of this is to check that the MaxElevation function can handle elevations which have the same value throughout and still find the max elevation.
     */
   Route Flatroute1 = Route(LogFiles::GPXRoutesDir + "FlatCityCampusN0749364.gpx", isFileName);
   BOOST_CHECK_CLOSE(Flatroute1.maxElevation(), -1747.0, FloatAccuracyTolerance );

   Route Flatroute2 = Route(LogFiles::GPXRoutesDir + "FlatCliftonCampusN0749364.gpx", isFileName);
   BOOST_CHECK_CLOSE(Flatroute2.maxElevation(), -2342.0, FloatAccuracyTolerance );

   Route Flatroute3 = Route(LogFiles::GPXRoutesDir + "FlatNorthPoleN0749364.gpx", isFileName);
   BOOST_CHECK_CLOSE(Flatroute3.maxElevation(), -1400.0, FloatAccuracyTolerance );

}


BOOST_AUTO_TEST_SUITE_END()


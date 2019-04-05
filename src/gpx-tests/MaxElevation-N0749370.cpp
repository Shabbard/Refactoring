#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

/* The Route.MaxElevation Function starts with the highest being the first elevation value in
 * a route then proceeds to compare it with further values to see if they are higher in elevation
 * value.
 *
 * The Test Suite starts with the pre-made routes to give a generalised result on if the function
 * works as intended, from there it goes into custom, and more specialised routes than have a
 * set purpose such as flat elevation, ascending elevation, desending elevation and spiking
 * elevation.
 */
BOOST_AUTO_TEST_SUITE( Max_elevation )

const bool isFileName = true;
//Variable to be applied to every test, applying a range on how close the answer can be to the true answer
float GlobalTolerance = 0.1;

BOOST_AUTO_TEST_CASE( PreMadeRandomRoute )
{
    //These tests are based on an elevation that alters throughout the route from different starting positions.
    Route route1 = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_CLOSE( route1.maxElevation(), 0.00, GlobalTolerance );
    Route route2 = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
    BOOST_CHECK_CLOSE( route2.maxElevation(), -20000.00, GlobalTolerance );
    Route route3 = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", isFileName);
    BOOST_CHECK_CLOSE( route3.maxElevation(), -40000.00, GlobalTolerance );
    Route route4 = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_CLOSE( route4.maxElevation(), -20000.00, GlobalTolerance );
}

BOOST_AUTO_TEST_CASE( FlatElevation )
{
    //These tests are based on an elevation that does not increase or decrease throughout the route from different starting positions.
    //Tests the function by making the highest Elevation constant throughout.
    Route route1 = Route(LogFiles::GPXRoutesDir + "N0749370Clifton.gpx", isFileName);
    BOOST_CHECK_CLOSE( route1.maxElevation(), -942.00, GlobalTolerance );
    Route route2 = Route(LogFiles::GPXRoutesDir + "N0749370Meridian.gpx", isFileName);
    BOOST_CHECK_CLOSE( route2.maxElevation(), -600.00, GlobalTolerance );
}

BOOST_AUTO_TEST_CASE( AscendingElevation )
{
    //These tests are based on an elevation that only increases throughout the route from different starting positions.
    //Tests the function by making the highest Elevation the last position.
    Route route1 = Route(LogFiles::GPXRoutesDir + "N0749370Pontianak.gpx", isFileName);
    BOOST_CHECK_CLOSE( route1.maxElevation(), 0.00, GlobalTolerance );
    Route route2 = Route(LogFiles::GPXRoutesDir + "N0749370City.gpx", isFileName);
    BOOST_CHECK_CLOSE( route2.maxElevation(), 53.00, GlobalTolerance );
}

BOOST_AUTO_TEST_CASE( DescendingElevation )
{
    //These tests are based on an elevation that only decreases throughout the route from different starting positions.
    //Tests the function by making the highest Elevation the first position.
    Route route1 = Route(LogFiles::GPXRoutesDir + "N0749370NorthPole.gpx", isFileName);
    BOOST_CHECK_CLOSE( route1.maxElevation(), 0.00, GlobalTolerance );
    Route route2 = Route(LogFiles::GPXRoutesDir + "N0749370AntiMeridian.gpx", isFileName);
    BOOST_CHECK_CLOSE( route2.maxElevation(), 0.00, GlobalTolerance );
}

BOOST_AUTO_TEST_CASE( SpikingElevation )
{
    //These tests are based on an elevation that increases or decreases in the middle of the route then back to starting elevation.
    //Tests the function by making the highest Elevation be in the middle or start/end positions.
    Route route1 = Route(LogFiles::GPXRoutesDir + "N0749370CliftonCampus2.gpx", isFileName);
    BOOST_CHECK_CLOSE( route1.maxElevation(), 58.00, GlobalTolerance );
    Route route2 = Route(LogFiles::GPXRoutesDir + "N0749370CityCampus2.gpx", isFileName);
    BOOST_CHECK_CLOSE( route2.maxElevation(), 53.00, GlobalTolerance );
}

BOOST_AUTO_TEST_CASE( SmallDataSet )
{
    //These tests are based on small number of elevation positions used throughout the route.
    Route route1 = Route(LogFiles::GPXRoutesDir + "N0749370AntiMeridian2.gpx", isFileName);
    BOOST_CHECK_CLOSE( route1.maxElevation(), -400.00, GlobalTolerance );
    Route route2 = Route(LogFiles::GPXRoutesDir + "N0749370Pontianak2.gpx", isFileName);
    BOOST_CHECK_CLOSE( route2.maxElevation(), 0.00, GlobalTolerance );
}

BOOST_AUTO_TEST_CASE( LargeDataSet )
{
    //These tests are based on large number of elevation positions used throughout the route.
    Route route1 = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
    BOOST_CHECK_CLOSE( route1.maxElevation(), 505.00, GlobalTolerance ); //Error says its 505?
    Route route2 = Route(LogFiles::GPXRoutesDir + "N0749370Meridian2.gpx", isFileName);
    BOOST_CHECK_CLOSE( route2.maxElevation(), 0.00, GlobalTolerance );
}

BOOST_AUTO_TEST_CASE( NegativeElevation )
{
    //These tests are based on having elevation set to a negative number instead of positive.
    Route route1 = Route(LogFiles::GPXRoutesDir + "N0749370NorthPole2.gpx", isFileName);
    BOOST_CHECK_CLOSE( route1.maxElevation(), 700.00, GlobalTolerance );
    Route route2 = Route(LogFiles::GPXRoutesDir + "N0749370CliftonCampus3.gpx", isFileName);
    BOOST_CHECK_CLOSE( route2.maxElevation(), 1558.00, GlobalTolerance );
}

BOOST_AUTO_TEST_CASE( ExtremeElevation )
{
    //These tests are based on having extreme numbers as the elevation value.
    Route route1 = Route(LogFiles::GPXRoutesDir + "N0749370Pontianak3.gpx", isFileName);
    BOOST_CHECK_CLOSE( route1.maxElevation(), 0.20, GlobalTolerance );
    Route route2 = Route(LogFiles::GPXRoutesDir + "N0749370AntiMeridian3.gpx", isFileName);
    BOOST_CHECK_CLOSE( route2.maxElevation(), 0.00, GlobalTolerance );
}


BOOST_AUTO_TEST_SUITE_END()



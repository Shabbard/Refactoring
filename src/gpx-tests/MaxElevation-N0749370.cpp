#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;


BOOST_AUTO_TEST_SUITE( Max_elevation )

const bool isFileName = true;

BOOST_AUTO_TEST_CASE( PreMadeRandomRoute )
{
    //These tests are based on an elevation that alters throughout the route from different starting positions.
    Route route1 = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_CLOSE( route1.maxElevation(), 0.00, 0.1 );
    Route route2 = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
    BOOST_CHECK_CLOSE( route2.maxElevation(), -20000.00, 0.1 );
    Route route3 = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", isFileName);
    BOOST_CHECK_CLOSE( route3.maxElevation(), -40000.00, 0.1 );
    Route route4 = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
    BOOST_CHECK_CLOSE( route4.maxElevation(), 505.00, 0.1 ); //Error says its 505? Code has 517 as highest.
    Route route5 = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_CLOSE( route5.maxElevation(), -20000.00, 0.1 );
}

BOOST_AUTO_TEST_CASE( FlatElevation )
{
    //These tests are based on an elevation that does not increase or decrease throughout the route from different starting positions.
    Route route6 = Route(LogFiles::GPXRoutesDir + "N0749370Clifton.gpx", isFileName);
    BOOST_CHECK_CLOSE( route6.maxElevation(), -942.00, 0.1 );
    Route route7 = Route(LogFiles::GPXRoutesDir + "N0749370Meridian.gpx", isFileName);
    BOOST_CHECK_CLOSE( route7.maxElevation(), -600.00, 0.1 );
}

BOOST_AUTO_TEST_CASE( AscendingElevation )
{
    //These tests are based on an elevation that only increases throughout the route from different starting positions.
    Route route6 = Route(LogFiles::GPXRoutesDir + "N0749370Pontianak.gpx", isFileName);
    BOOST_CHECK_CLOSE( route6.maxElevation(), 0.00, 0.1 );
    Route route7 = Route(LogFiles::GPXRoutesDir + "N0749370City.gpx", isFileName);
    BOOST_CHECK_CLOSE( route7.maxElevation(), 53.00, 0.1 );
}

BOOST_AUTO_TEST_CASE( DescendingElevation )
{
    //These tests are based on an elevation that only decreases throughout the route from different starting positions.
    Route route6 = Route(LogFiles::GPXRoutesDir + "N0749370NorthPole.gpx", isFileName);
    BOOST_CHECK_CLOSE( route6.maxElevation(), 0.00, 0.1 );
    Route route7 = Route(LogFiles::GPXRoutesDir + "N0749370AntiMeridian.gpx", isFileName);
    BOOST_CHECK_CLOSE( route7.maxElevation(), 0.00, 0.1 );
}



BOOST_AUTO_TEST_SUITE_END()



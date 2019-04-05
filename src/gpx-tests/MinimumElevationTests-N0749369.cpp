#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

const float toleranceAmount = 0.1;

BOOST_AUTO_TEST_SUITE( MinimumElevation )

const bool isFileName = true;

//============================================Minimum Default Elevation==================================================
//MinDefaultValueElevation tests the default made GPX files
BOOST_AUTO_TEST_CASE( MinDefaultValueElevation )
{
    Route ABCDRouteTest = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_CLOSE( ABCDRouteTest.minElevation(), 0.00, toleranceAmount );

    Route ABWQERouteTest = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
    BOOST_CHECK_CLOSE( ABWQERouteTest.minElevation(), -40000.00, toleranceAmount );

    Route AFKPURouteTest = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", isFileName);
    BOOST_CHECK_CLOSE( AFKPURouteTest.minElevation(), -40000.00, toleranceAmount );

    Route NorthYorkMoorsRouteTest = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
    BOOST_CHECK_CLOSE( NorthYorkMoorsRouteTest.minElevation(), 135.00, toleranceAmount );

    Route QRouteTest = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_CLOSE( QRouteTest.minElevation(), -20000.00, toleranceAmount );
}
//==========================================================================================================================

//============================================Minimum Flat Elevation========================================================
//checks for the bare minimum flat elevation
BOOST_AUTO_TEST_CASE( minFlatElevation )
{
    Route AEYURouteTest = Route(LogFiles::GPXRoutesDir + "NorthPole-AEYU.gpx", isFileName);
    BOOST_CHECK_CLOSE( AEYURouteTest.minElevation(), -1700.00, toleranceAmount );

    Route ACEOYWUKRouteTest = Route(LogFiles::GPXRoutesDir + "EquatorialMeridian-ACEOYWUK.gpx", isFileName);
    BOOST_CHECK_CLOSE( ACEOYWUKRouteTest.minElevation(), -2460.00, toleranceAmount );
}

//checks for the positive minimum elevation that does not exceed below zero
BOOST_AUTO_TEST_CASE( posMinFlatElevation )
{
    Route posAEYURouteTest = Route(LogFiles::GPXRoutesDir + "posNorthPole-AEYU.gpx", isFileName);
    BOOST_CHECK_CLOSE( posAEYURouteTest.minElevation(), 610.00, toleranceAmount );

    Route posACEOYWUKRouteTest = Route(LogFiles::GPXRoutesDir + "posEquatorialMeridian-ACEOYWUK.gpx", isFileName);
    BOOST_CHECK_CLOSE( posACEOYWUKRouteTest.minElevation(), 884.00, toleranceAmount );
}
//==========================================================================================================================

//============================================Minimum Descending Elevation==================================================
//check for the minimum descending elevation
BOOST_AUTO_TEST_CASE( minFallingElevation )
{
    Route MRSNOTYRouteTest = Route(LogFiles::GPXRoutesDir + "EquatorialAntiMeridian-MRSNOTY.gpx", isFileName);
    BOOST_CHECK_CLOSE( MRSNOTYRouteTest.minElevation(), -1640.00, toleranceAmount );

    Route MLGFKRouteTest = Route(LogFiles::GPXRoutesDir + "CliftonCampus-MLGFK.gpx", isFileName);
    BOOST_CHECK_CLOSE( MLGFKRouteTest.minElevation(), -802.00, toleranceAmount );
}

//same as minFallingElevation but only checks the positive
BOOST_AUTO_TEST_CASE( posMinFallingElevation )
{
    Route MRSNOTYRouteTest = Route(LogFiles::GPXRoutesDir + "posEquatorialAntiMeridian-MRSNOTY.gpx", isFileName);
    BOOST_CHECK_CLOSE( MRSNOTYRouteTest.minElevation(), 0.00, toleranceAmount );

    Route MLGFKRouteTest = Route(LogFiles::GPXRoutesDir + "posCliftonCampus-MLGFK.gpx", isFileName);
    BOOST_CHECK_CLOSE( MLGFKRouteTest.minElevation(), 58.00, toleranceAmount );
}
//==========================================================================================================================

//============================================Minimum Ascending Elevation===================================================
//tests the minimum ascending elevation
BOOST_AUTO_TEST_CASE( minRisingElevation )
{
    Route ABGHMRouteTest = Route(LogFiles::GPXRoutesDir + "CityCampus-ABGHM.gpx", isFileName);
    BOOST_CHECK_CLOSE( ABGHMRouteTest.minElevation(), -2627.00, toleranceAmount );

    Route UVWRSNMRouteTest = Route(LogFiles::GPXRoutesDir + "Pontianak-UVWRSNM.gpx", isFileName);
    BOOST_CHECK_CLOSE( UVWRSNMRouteTest.minElevation(), -1308642.00, toleranceAmount );
}

//same as the minRisingElevation but check for positive values
BOOST_AUTO_TEST_CASE( posMinRisingElevation )
{
    Route ABGHMRouteTest = Route(LogFiles::GPXRoutesDir + "posCityCampus-ABGHM.gpx", isFileName);
    BOOST_CHECK_CLOSE( ABGHMRouteTest.minElevation(), 53.00, toleranceAmount );

    Route UVWRSNMRouteTest = Route(LogFiles::GPXRoutesDir + "posPontianak-UVWRSNM.gpx", isFileName);
    BOOST_CHECK_CLOSE( UVWRSNMRouteTest.minElevation(), 0.00, toleranceAmount );
}
//===========================================================================================================================


BOOST_AUTO_TEST_SUITE_END()


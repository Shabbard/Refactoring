#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( minLatitude_N0743587 )

BOOST_AUTO_TEST_CASE(SinglePoint){

    Route route = Route(LogFiles::GPXRoutesDir + "A.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.89982 );

    route = Route(LogFiles::GPXRoutesDir + "B.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.89982 );
}

BOOST_AUTO_TEST_CASE(MultiPoint){

    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.89982 );

    route = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.89982 );
}

BOOST_AUTO_TEST_CASE(InvalidFile){
//Throws exception
    Route route = Route(LogFiles::GPXRoutesDir + "invalid.jpg", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.89982 );

    route = Route(LogFiles::GPXRoutesDir + "invalid.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.89982 );
}

BOOST_AUTO_TEST_CASE(NullCase){
//Throws IOException
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.89982 );
}

BOOST_AUTO_TEST_CASE(IsNumber){
//Throws IOException

    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", true);
    BOOST_CHECK_EQUAL( route.minLatitude(), -0.89982 );
}


BOOST_AUTO_TEST_SUITE_END()

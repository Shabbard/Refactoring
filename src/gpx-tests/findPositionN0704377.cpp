#include <boost/test/unit_test.hpp>
#include <boost/test/tools/old/interface.hpp>
#include <boost/test/test_tools.hpp>

#include "track.h"
#include "logs.h"
#include "types.h"
#include "route.h"

#include <iostream>
#include <fstream>

using namespace GPS;


//position is made up of three values lat,lon,ele test will be carryed out to ensure that
//what need to be tested is  ability to find the position of the called name 
// also needs to test to find the name that the  three positions are for

BOOST_AUTO_TEST_SUITE( Route_findPosition )

const bool isFileName = true;


//test to ensure that the latitude can be found by compering the known value with the value saved in the gpx file
//that should be the same

//test spacificly for the latitude values
//this find the value of the latitude holding normal data and compairs itto a fixed value
//that should be held by the current position
BOOST_AUTO_TEST_CASE(find_latitude)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_GenPosNum.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("T").latitude(), 89.9955);
}

//test that the latitude can hold a negative value by retiving it and compairing it against the negative value
//that it should be holding
BOOST_AUTO_TEST_CASE(find_neg_latitude)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_AFKPU.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("U").latitude(), -0.00719856);
}

//test to ensure that the value of the latitude can be less than zero
BOOST_AUTO_TEST_CASE(find_Zero_Point_latitude)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Zero_values.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("D").latitude(), 0.0089982);
}

//test value of latitude if holding a value of zero
BOOST_AUTO_TEST_CASE(find_Zero_latitude)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Zero_values.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("N").latitude(), 0);
}

//this test the accruacy of the positions latitude ensureing that it match the set value hold
BOOST_AUTO_TEST_CASE(test_acc_lat)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_GenX.gpx", isFileName);
    const double percentage = 0.1;
    BOOST_CHECK_CLOSE( route.findPosition("T").latitude() , 52.9536, percentage);
}


//longatude tests the test here are aim at the longitude spacificly


BOOST_AUTO_TEST_CASE(find_long)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Longatude.gpx", isFileName);
     BOOST_CHECK_EQUAL( route.findPosition("F").longitude(), 49.5625 );
}

//test to ensure that negative values can be used as longatude values
BOOST_AUTO_TEST_CASE(find_neg_long)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Longatude.gpx", isFileName);
     BOOST_CHECK_EQUAL( route.findPosition("J").longitude(), -49.5625 );
}

// tests to ensure that in the case that the longatude is a zero point value
BOOST_AUTO_TEST_CASE(find_ZP_long)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Longatude.gpx", isFileName);
     BOOST_CHECK_EQUAL( route.findPosition("R").longitude(), 0 );
}

//test the accracy of the data held in the longatude
BOOST_AUTO_TEST_CASE(test_acc_long)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Longatude_Ac.gpx", isFileName);
    const double percentage = 0.1;
    BOOST_CHECK_CLOSE( route.findPosition("Y").longitude() , 109.331, percentage);
}



//longatude tests the test here are aim at the longitude spacificly
BOOST_AUTO_TEST_CASE(find_long)
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
     BOOST_CHECK_EQUAL( route.findPosition("E").longitude(), 1.79662 );
}

//test to ensure that negative values can be used as longatude values
BOOST_AUTO_TEST_CASE(find_neg_long)
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
     BOOST_CHECK_EQUAL( route.findPosition("B").longitude(), -0.898312 );
}

// tests to ensure that in the case that the longatude is a zero point value
BOOST_AUTO_TEST_CASE(find_ZP_long)
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
     BOOST_CHECK_EQUAL( route.findPosition("W").longitude(), 0 );
}

//test the accracy of the data held in the longatude
BOOST_AUTO_TEST_CASE(test_acc_long)
{
    Route route = Route(LogFiles::GPXRoutesDir + "AFKPU.gpx", isFileName);
    const double percentage = 0.1;
    BOOST_CHECK_CLOSE( route.findPosition("U").longitude() , -1.79662, percentage);
}





BOOST_AUTO_TEST_SUITE_END()



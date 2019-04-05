
//#include <boost/test/unit_test.hpp>
//#include <boost/test/tools/old/interface.hpp>
//#include <boost/test/test_tools.hpp>

#include "track.h"
#include "logs.h"
#include "types.h"
#include "route.h"

#include <iostream>
#include <fstream>

using namespace GPS;

//these test are to test the ablility of the findposition function to find the position
//As a position is made up of three values latitude ,longitude,elevation
//these test will test the ablilty to find and gathere these positional data


BOOST_AUTO_TEST_SUITE( Route_findPosition )

const bool isFileName = true;

//these test are spacificly aimed at latitude, testing the functions ablilitys to find te latitude
//under a nuber of differant circumstances inorder to have confidence that the function can accurately
//retrive the latitude

//test to ensure that is possable to find the latitude
BOOST_AUTO_TEST_CASE(find_latitude)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_GenPosNum.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("T").latitude(), 89.9955);
}

//tests the latitude can hold a negative value,  and thats it can by retived
//as well as ensure that the function has no problems dealing with negative numbers
BOOST_AUTO_TEST_CASE(find_neg_latitude)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Gen_Ex.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("X").latitude(), -0.0179964);
}

//test to ensure that latitude can be a value less than zero
//
BOOST_AUTO_TEST_CASE(find_Zero_Point_latitude)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Zero_values.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("D").latitude(), 0.0089982);
}

// ensure that the latitude can hold a value of zero
BOOST_AUTO_TEST_CASE(find_Zero_latitude)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Zero_values.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("N").latitude(), 0);
}

//this test the accruacy of the positions latitude ensureing that it match the set value hold
// and that the value presented is as accurate as can be to the value in the gpx file
BOOST_AUTO_TEST_CASE(test_acc_lat)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_GenX.gpx", isFileName);
    const double percentage = 0.1;
    BOOST_CHECK_CLOSE( route.findPosition("T").latitude() , 52.9536, percentage);
}


//these test are spacificly aimed at longitude, testing the functions ablilitys to find the longitude
//under a number of differant circumstances inorder to have confidence that the function can accurately
//retrive the longatude

//testing function ablility to find the longitude
BOOST_AUTO_TEST_CASE(find_long)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Longatude.gpx", isFileName);
     BOOST_CHECK_EQUAL( route.findPosition("F").longitude(), 49.5625 );
}

//test to ensure that negative values can be used as longitude values
BOOST_AUTO_TEST_CASE(find_neg_long)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Longatude.gpx", isFileName);
     BOOST_CHECK_EQUAL( route.findPosition("J").longitude(), -49.5625 );
}

// test ensures that in the case that the longitude is holding a value of zero point
//its still able to take it in as an argurment
BOOST_AUTO_TEST_CASE(find_ZP_long)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Longatude.gpx", isFileName);
     BOOST_CHECK_EQUAL( route.findPosition("R").longitude(), 0 );
}

//test the accracy of the positions longitude ensuring that is the right value that is help by the gpx file
BOOST_AUTO_TEST_CASE(test_acc_long)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Longatude_Ac.gpx", isFileName);
    const double percentage = 0.1;
    BOOST_CHECK_CLOSE( route.findPosition("Y").longitude() , 109.331, percentage);
}



//these are a number of test that will be aim spacificly at
//the function ability to find the elevation of a position
BOOST_AUTO_TEST_CASE(find_neg_elevation)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Zero_values.gpx", isFileName);
     BOOST_CHECK_EQUAL( route.findPosition("D").elevation(), -500.000000 );
}

//testing the functions ability to pass an elevation the hold quite a large number
BOOST_AUTO_TEST_CASE(find_large_elevation)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_GenX.gpx", isFileName);
     BOOST_CHECK_EQUAL( route.findPosition("A").elevation(), -1000.000000);
}

//ensuring that the data that test is looing for perfectly match the value in the gpx file
BOOST_AUTO_TEST_CASE(test_acc_elevation)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_elevation.gpx", isFileName);
    const double percentage = 0.1;
    BOOST_CHECK_CLOSE( route.findPosition("C").elevation() , -600.000000,percentage);
}

BOOST_AUTO_TEST_CASE(test_Zero_elevation)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_elevation.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("M").elevation() , 0.000000);
}

BOOST_AUTO_TEST_CASE(test_Pos_elevation)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_GenPosNum.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("M").elevation() , 53.000000);
}

//this is an erroneous test, these test hold data that is not withing the route and are expected to fail
//so should they be accepted then there is a problem with the function

BOOST_AUTO_TEST_CASE(test_throw)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_GenX.gpx", isFileName);

    BOOST_CHECK_THROW( route.findPosition("M"), std::out_of_range  );
}

BOOST_AUTO_TEST_CASE(test_throw2)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Gen_Route.gpx", isFileName);

    BOOST_CHECK_THROW( route.findPosition("Y"), std::out_of_range  );
}


//here the test are targeted to one position  where all elements are going be tested
//all of there values to the fixed values that we know
//what they will be inorder to ensure that its pointing to the right place out doubt

BOOST_AUTO_TEST_CASE(test_position_values)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Single.gpx", isFileName);

    const double percentage = 0.1;
    BOOST_CHECK_CLOSE( route.findPosition("T").latitude() , -0.0044991,percentage);
    BOOST_CHECK_CLOSE( route.findPosition("T").longitude() , 0.00898312,percentage);
    BOOST_CHECK_CLOSE( route.findPosition("T").elevation() , -200.000000,percentage);
}

BOOST_AUTO_TEST_CASE(test_position2_values)
{
    Route route = Route(LogFiles::GPXRoutesDir + "N0704377_Single2.gpx", isFileName);

    const double percentage = 0.1;
    BOOST_CHECK_CLOSE( route.findPosition("P").latitude() , 52.9098,percentage);
    BOOST_CHECK_CLOSE( route.findPosition("P").longitude() , -1.19296,percentage);
    BOOST_CHECK_CLOSE( route.findPosition("P").elevation() , -942.000000,percentage);
}




BOOST_AUTO_TEST_SUITE_END()



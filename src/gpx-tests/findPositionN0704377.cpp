
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

//boost test to test the the function findposition
// position is made up of three values lat,lon,ele to find the position 
//what need to be tested is  ability to find the position of the called name 
// also needs to test to find the name that the  three positions point too 

BOOST_AUTO_TEST_SUITE( Route_findPosition )

const bool isFileName = true;


//test to ensure that the latitude can be found by compering the known value with the value saved in the gpx file
//the should be the same
BOOST_AUTO_TEST_CASE(find_latitude)
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.findPosition("E").latitude(), 1.79964);
}


BOOST_AUTO_TEST_CASE(find_long)
{
   //char X = E;
    
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
     BOOST_CHECK_EQUAL( route.findPosition("E").longitude(), 1.79662 );
    
}

//BOOST_AUTO_TEST_CASE(find_position)
//{
    
//    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
//    //const double percentage = 0.0001;
//    //BOOST_CHECK_EQUAL( route.findPosition("E").latitude(), -1.79964 );
//    BOOST_CHECK_EQUAL( route.findPosition("E") , Position( "1.79964" , "1.79662" ));
//}

BOOST_AUTO_TEST_CASE(test_ac_lat)
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABQWE.gpx", isFileName);
    const double percentage = 0.1;
    BOOST_CHECK_CLOSE( route.findPosition("E").latitude() , 1.79964, percentage);
}

BOOST_AUTO_TEST_SUITE_END()



#include <boost/test/unit_test.hpp>

#include "gridworld_route.h"
#include <fstream>
#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

// This function generates GPXlogfiles with the given positions
std::string GPXlogFiles(std::string RoutePath, GridWorldRoute gridw)
{
    std::string routeName = RoutePath + "_N0731739.gpx";

    std::ofstream finalroute(LogFiles::GPXRoutesDir + routeName);

    finalroute << gridw.toGPX(true, RoutePath);

    finalroute.close();

    return routeName;
}




BOOST_AUTO_TEST_SUITE( Route_netLength_No731739)

const bool isFileName = true;
const metres horizontalGridUnit = 30000;

// Single point on the gdidworld
BOOST_AUTO_TEST_CASE ( SinglePoint )
{
    Route Qroute = Route(LogFiles::GPXRoutesDir + "Q.gpx", isFileName);
    BOOST_CHECK_EQUAL( Qroute.netLength(), 0.0);
}

// First and last location are the same
BOOST_AUTO_TEST_CASE ( SameFirstLastPoint )
{
    GridWorldRoute Logroute = GridWorldRoute("LOL");
    Route LOLroute = Route(LogFiles::GPXRoutesDir + GPXlogFiles("test4",Logroute), isFileName);
    BOOST_CHECK_EQUAL( LOLroute.netLength(), 0 );
}
// Using different points
BOOST_AUTO_TEST_CASE ( differentPoints )
{
    GridWorldRoute Logroute = GridWorldRoute("VITA");
    Route VITAroute = Route(LogFiles::GPXRoutesDir + GPXlogFiles("test",Logroute), isFileName);
    BOOST_CHECK_EQUAL( VITAroute.netLength(), 41254.444525376712  );
}

// Longitude, latitude and elevation are zero
BOOST_AUTO_TEST_CASE ( lon_lat_ele_0 )
{
    GridWorldRoute Logroute = GridWorldRoute("SNHB" ,GridWorld(Earth::EquatorialMeridian,0,0));
    Route SNHBroute = Route(LogFiles::GPXRoutesDir + GPXlogFiles("test1",Logroute), isFileName);
    BOOST_CHECK_EQUAL( SNHBroute.netLength(), 0  );
}
// Only longitude is zero
BOOST_AUTO_TEST_CASE ( longitude_0 )
{
    GridWorldRoute Logroute = GridWorldRoute("QWERTYUIOP" ,GridWorld(Earth::NorthPole,0,0));
    Route QWERTYUIOProute = Route(LogFiles::GPXRoutesDir + GPXlogFiles("test2",Logroute), isFileName);
    BOOST_CHECK_EQUAL( QWERTYUIOProute.netLength(), 0  );
}

// Only latitude is zero
BOOST_AUTO_TEST_CASE ( latitude_0 )
{
    GridWorldRoute Logroute = GridWorldRoute("MNO");
    Route MNOroute = Route(LogFiles::GPXRoutesDir + GPXlogFiles("test3",Logroute), isFileName);
    BOOST_CHECK_EQUAL( MNOroute.netLength(), 20015.114442036094  );
}

// Granularity is smaler than the netLength
BOOST_AUTO_TEST_CASE( GranularityIsSmaler )
{
   const metres granularity = horizontalGridUnit * 0.99;
   Route ABCDroute = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName, granularity);
   BOOST_CHECK_EQUAL( ABCDroute.netLength(), 30022.523566211392 );
}
// Granularity is bigger than the netLength
BOOST_AUTO_TEST_CASE( GranularityIsBigger )
{
   const metres granularity = horizontalGridUnit * 1.01;
   Route ABCDroute = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName, granularity);
   BOOST_CHECK_EQUAL( ABCDroute.netLength(), 0 );
}

BOOST_AUTO_TEST_SUITE_END()





#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Track_totalTime_N0774540 )

const bool isFileName = true;

/* DESIGN:
 
 Total time = resting time + travaling time
 
The totalTime() function looks at the total time taken to complete the route, this includes the travelling time and the resting time. To test this function, we have to create challenges for the route to encounter and check the total time is what it should be once the track is finished. The first test is used to make sure the function returns valid times for a simple short route with only two points. I chose to start with this as its the simplest route possible. The second test checks to see if the correct time is given when there are multiple points with different time lengths between each point, this test checks that all the times are being added up together correctly. Following this, test 3 checks the returned time of a long track. This track uses 4 points, the time length varies between each point and makes use of high time values. Test 4 checks to see if the resting time is being included in the total time as totalTime() == restingTime() + travellingTime(). Test 5 looks to see if the totalTime() is correct on a track where there is acceleration. Test 6 checks the totalTime() on a track where there is a change in both the longitude and latitude. First the longitude then the latitude. Finally test 7 and 8 test what happens when either an empty or non-existent GPX log file are used. These test just check that the function deals with these problems correctly by throwing an std::invalid_argument.
 */

/* Test number:         1
 
 * Test name:           totalTime() on a short track
 
 * Test description:    This test check the total time between the simpilist track. Point A to point B.
 
 * Expected result:     totalTime() to be 10 seconds.
 
 */

BOOST_AUTO_CASE( shortTrack )
{
Track track = Track(LogFiles::GPXTracksDir + "A1B-N0774540.gpx", isFileName);
BOOST_CHECK_EQUAL( track.totoalTime(), "10" );
}


/* Test number:         2
 
 * Test name:           totalTime() over multiple points with diffrent times
 
 * Test description:    This test checks the time over 3 diffrent points, the length of time between each point is diffrent.
 
 * Expected result:     totalTime() to be 80 seconds
 
 */

BOOST_AUTO_CASE( multiplePointsWithDiffrentTimes )
{
    
    Track track = Track(LogFiles::GPXTracksDir + "A1B2C5D-N0774540.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.totoalTime(), "80" );
}


/* Test number:         3
 
 * Test name:           totalTime() on a long track
 
 * Test description:    This test check the total time between the simpilist track. Point A to point B.
 
 * Expected result:     totalTime() to be 300 seconds
 
 */

BOOST_AUTO_CASE( longTrack )
{
    Track track = Track(LogFiles::GPXTracksDir + "A1B19C10D-N0774540.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.totoalTime(), "300" );
}


/* Test number:         4
 
 * Test name:           Resting Time Check
 
 * Test description:    This test checks that the resting time is included in the total time
 
 * Expected result:     totalTime() to be 25 seconds
 
 */

BOOST_AUTO_CASE( restingTimeCheck )
{
    Track track = Track(LogFiles::GPXTracksDir + "A1B1C-N0774540.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.totoalTime(), "25" );
}


/* Test number:         5
 
 * Test name:           totalTime() on a track with acceleration
 
 * Test description:    Check the totalTime() on a track with acceleration.
 
 * Expected result:     totalTime() to be
 
 */

BOOST_AUTO_CASE( accelerationDuringTrack )
{
    Track track = Track(LogFiles::GPXTracksDir + "A2B-N0774540.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.totoalTime(), "20" );
}



/* Test number:         6
 
 * Test name:           totalTime() on a track where there is a change in both the longitude and latitude
 
 * Test description:    Check the totalTime() on a track where there is a change in both the longitude and latitude. First the longitude then the
                        latitude.
 
 * Expected result:     totalTime() to be 40 seconds
 
 */

BOOST_AUTO_CASE( changeInLonAndLat )
{
    Track track = Track(LogFiles::GPXTracksDir + "A1B1C1H1M-N0774540.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.totoalTime(), "40" );
}



/* Test number:         73
 
 * Test name:           Check totalTime() against an empty GPX log file.
 
 * Test description:    This test analyses an empty GPX file incorrectly.
 
 * Expected result:     Since the file is blank, and no data can be found, an std::domain_error
 
 */

BOOST_AUTO_CASE( blankFileSpecified )
{
Track track = Track(LogFiles::GPXTracksDir + "BlankTest_N0774540.gpx", isFileName);
BOOST_CHECK_THROW( route.maxGradient(), std::domain_error );
}



/* Test number:         8
 
 * Test name:           Check totalTime() on a non-existant GPX log file.
 
 * Test description:    This test attempts to inspect a non-existant GPX log file.
 
 * Expected result:     An std::invalid_argument exception should be thrown.
 
 */

BOOST_AUTO_CASE( nonExistantFileSpecified )
{
    Track track = Track(LogFiles::GPXTracksDir + "NotAFile.gpx", isFileName);
    BOOST_CHECK_THROW( route.maxGradient(), std::invalid_argument );
}

BOOST_AUTO_TEST_SUITE_END()

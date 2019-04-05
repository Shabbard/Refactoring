#include <boost/test/unit_test.hpp>

#include <iostream>
#include <fstream>
#include "gridworld_track.h"
#include "gridworld.h"
#include "logs.h"
#include "track.h"

using namespace GPS;

std::string importGPXlog(GridWorldTrack gwt, std::string name){
    //GPX file path
    std::string filePath = GPS::LogFiles::GPXTracksDir + "N0771613" + "-" + name + ".gpx";

    // Creating file
    std::ofstream GPXTrack(filePath);
    GPXTrack << gwt.toGPX(10, true, name); // writing track points to file
    GPXTrack.close();

    return filePath; // pass path into the route function
}


BOOST_AUTO_TEST_SUITE(restingTime_N0771613)

const bool isFileName = true;

BOOST_AUTO_TEST_CASE(no_rest_time_1)
{
    GPS::Track track(GPS::LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.restingTime(), 0);
}

BOOST_AUTO_TEST_CASE(no_rest_time_2)
{
    //, GridWorld(Earth::CityCampus, 1000,1000)
    GridWorldTrack trk= GridWorldTrack("A2C3E2I4G2K3M3O4S2Q2U3W4Y", 10, 0);
    
    GPS::Track track(importGPXlog(trk, "no_rest_time_2"), isFileName);
    BOOST_CHECK_EQUAL(track.restingTime(), 0);
}

BOOST_AUTO_TEST_CASE(singleStop_rest_time_mid)
{
    GridWorldTrack trk= GridWorldTrack("A4B1B3C", 10, 0);
    
    GPS::Track track(importGPXlog(trk, "singleStop_rest_time_mid"), isFileName);
    BOOST_CHECK_EQUAL(track.restingTime(), 10);
}

BOOST_AUTO_TEST_CASE(singleStop_rest_time_start)
{
    GridWorldTrack trk= GridWorldTrack("A2A4B3C", 10, 0);
    
    GPS::Track track(importGPXlog(trk, "singleStop_rest_time_start"), isFileName);
    BOOST_CHECK_EQUAL(track.restingTime(), 20);
}

BOOST_AUTO_TEST_CASE(singleStop_rest_time_end)
{
    GridWorldTrack trk= GridWorldTrack("A4B3C3C", 10, 0);
    
    GPS::Track track(importGPXlog(trk, "singleStop_rest_time_end"), isFileName);
    BOOST_CHECK_EQUAL(track.restingTime(), 30);
}

BOOST_AUTO_TEST_CASE(multipleStop_rest_time)
{
    GridWorldTrack trk= GridWorldTrack("A1A4B2B3C2C6M1M7Y2Y6U4U7A", 10, 0);
    
    GPS::Track track(importGPXlog(trk, "multipleStop_rest_time"), isFileName);
    BOOST_CHECK_EQUAL(track.restingTime(), 120);
}

BOOST_AUTO_TEST_SUITE_END();

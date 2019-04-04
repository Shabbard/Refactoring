#include <boost/test/unit_test.hpp>
#include <iostream>

#include "gridworld_route.h"
#include "logs.h"
#include "route.h"
#include "track.h"
#include <fstream>

using namespace GPS;



const bool isFileName = true;
const std::string sn = "n0701387";
double errormargin = 0.1;
const std::string logPath = LogFiles::GPXRoutesDir + "n0701387-";

void GenerateLogFile(const std::string filePath,const std::string gpxdata)
{
	std::ofstream outfile(filePath);
	outfile << gpxdata << std::endl;
	outfile.close();
}

BOOST_AUTO_TEST_SUITE ( Route_netHeightGain )


BOOST_AUTO_TEST_CASE ( no_elevation_change )
{

	GridWorldRoute gridworldroute = GridWorldRoute("MHC", GridWorld(Position(52.9581, -1.5424, 20)));
	const std::string filePath(logPath + "MHC" + ".gpx");
	GenerateLogFile(filePath, gridworldroute.toGPX(true));
	Route r1 = Route(filePath, isFileName);
	BOOST_CHECK_CLOSE( r1.netHeightGain(), 0 , errormargin);



	GridWorldRoute gridworldroute2 = GridWorldRoute("MRW", GridWorld(Position(52.9581, -1.15424, -20)));
	const std::string filePath2(logPath + "MRW" + ".gpx");
	GenerateLogFile(filePath2, gridworldroute2.toGPX(true));
	Route r2 = Route(filePath2, isFileName);
	BOOST_CHECK_CLOSE( r2.netHeightGain(), 0, errormargin);

}


BOOST_AUTO_TEST_CASE ( positive_elevation_change )
{

	GridWorldRoute gridworldroute = GridWorldRoute("MHC", GridWorld(Earth::CityCampus, 1000, -20));
	std::string filePath(LogFiles::GPXRoutesDir + sn + "-PositiveElevationChange-MHC.gpx");
	GenerateLogFile(filePath, gridworldroute.toGPX(true));
	Route r1 = Route(filePath, isFileName);
	BOOST_CHECK_CLOSE( r1.netHeightGain(), 40, errormargin);


	GridWorldRoute gridworldroute2 = GridWorldRoute("MRW", GridWorld(Earth::CityCampus, 1000, -50));
	std::string filePath2(LogFiles::GPXRoutesDir + sn + "-PositiveElevationChange-MRW.gpx");
	GenerateLogFile(filePath2, gridworldroute2.toGPX(true));
	Route r2 = Route(filePath2, isFileName);
	BOOST_CHECK_CLOSE( r2.netHeightGain(), 100, errormargin);


}

BOOST_AUTO_TEST_CASE ( negative_elevation_change )
{


	GridWorldRoute gridworldroute = GridWorldRoute("MHC", GridWorld(Earth::CityCampus, 1000, 20));
	std::string filePath(LogFiles::GPXRoutesDir + sn + "-NegativeElevationChange-MHC.gpx");
	GenerateLogFile(filePath, gridworldroute.toGPX(true));
	Route r1 = Route(filePath, isFileName);
	BOOST_CHECK_CLOSE( r1.netHeightGain(), 0, errormargin);


	GridWorldRoute gridworldroute2 = GridWorldRoute("MRW", GridWorld(Earth::CityCampus, 1000, 40));
	std::string filePath2(LogFiles::GPXRoutesDir + sn + "-NegativeElevationChange-MRW.gpx");
	GenerateLogFile(filePath2, gridworldroute2.toGPX(true));
	Route r2 = Route(filePath2, isFileName);
	BOOST_CHECK_CLOSE( r2.netHeightGain(), 0, errormargin);

}

BOOST_AUTO_TEST_CASE ( unexpected_values ) 
{
	GridWorldRoute gridworldroute = GridWorldRoute("ABC");
	std::string filePath(LogFiles::GPXRoutesDir + sn + "-NoElevationValue-ABC.gpx");
	GenerateLogFile(filePath, gridworldroute.toGPX(true));
	Route r1 = Route(filePath, isFileName);
	BOOST_CHECK_CLOSE( r1.netHeightGain(), 0, errormargin);

	GridWorldRoute gridworldroute2 = GridWorldRoute("MHC", GridWorld(Earth::CityCampus, 1000, -2000));
	std::string filePath2(LogFiles::GPXRoutesDir + sn + "-LargeElevationIncrease-MHC.gpx");
	GenerateLogFile(filePath2, gridworldroute2.toGPX(true));
	Route r2 = Route(filePath2, isFileName);
	BOOST_CHECK_CLOSE( r2.netHeightGain(), 4000, errormargin);

	GridWorldRoute gridworldroute3 = GridWorldRoute("MRW", GridWorld(Earth::CityCampus, 1000, 1000));
	std::string filePath3(LogFiles::GPXRoutesDir + sn + "-LargeElevationDecrease-MRW.gpx");
	GenerateLogFile(filePath3, gridworldroute3.toGPX(true));
	Route r3 = Route(filePath3, isFileName);
	BOOST_CHECK_CLOSE( r3.netHeightGain(), 0, errormargin);
	
}
BOOST_AUTO_TEST_SUITE_END()

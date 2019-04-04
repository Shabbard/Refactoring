#include <boost/test/unit_test.hpp>
#include "gridworld_route.h"
#include "logs.h"
#include "route.h"
#include "track.h"
#include <fstream>

using namespace GPS;

//Variables accessible for the whole file to avoid repeating lines.
const bool isFileName = true;
const std::string sn = "n0701387";
//This margin for error will be used to account for different changes in the program that could alter the way the program rounds specific numbers, specifically in cases such as division with or without remainders. Changes in calculation methods could mean in very specific situations tests will fail, despite having more or less the correct output and methodology.
double errormargin = 0.1;
const std::string logPath = LogFiles::GPXRoutesDir + "n0701387-";

//This is a simple function to generate a log file using an inputted filepath to generate to, and data to insert into the file.
void GenerateLogFile(const std::string filePath,const std::string gpxdata)
{
	std::ofstream outfile(filePath);
	outfile << gpxdata << std::endl;
	outfile.close();
}

BOOST_AUTO_TEST_SUITE ( Route_netHeightGain )


//These tests test to see that when there is no change in elevation, the function outputs 0 instead of other values, such as the first value of the elevation. 
//For example, if the elevation is 20, but stays at 20, the function should return 0, not 20.
BOOST_AUTO_TEST_CASE ( no_elevation_change )
{

	//Generating log files when the test is called to run.
	GridWorldRoute gridworldroute = GridWorldRoute("MHC", GridWorld(Position(52.9581, -1.5424, 20)));
	const std::string filePath(logPath + "MHC" + ".gpx");
	GenerateLogFile(filePath, gridworldroute.toGPX(true));

	//Generating a new route using the file generated above.
	Route r1 = Route(filePath, isFileName);
	//Checks to see that the function returns 0 instead of 20. Has a margin of error of 0.1 to account for different 	ways of calculating that could be used if the program were to change.
	BOOST_CHECK_CLOSE( r1.netHeightGain(), 0 , errormargin);


	//Generating more log files.
	GridWorldRoute gridworldroute2 = GridWorldRoute("MRW", GridWorld(Position(52.9581, -1.15424, -20)));
	const std::string filePath2(logPath + "MRW" + ".gpx");
	GenerateLogFile(filePath2, gridworldroute2.toGPX(true));

	//Generating another route using the above file.
	Route r2 = Route(filePath2, isFileName);
	//Checks to see that the function returns 0 instead of 20. Has a margin of error of 0.1 to account for different 	ways of calculating that could be used if the program were to change.
	BOOST_CHECK_CLOSE( r2.netHeightGain(), 0, errormargin);

}


//This group of tests check to see that the function correctly calculates net elevation when elevation is increasing multiple times with each point moving. 
BOOST_AUTO_TEST_CASE ( positive_elevation_change )
{

	//Generating log files when the test is called to run.
	GridWorldRoute gridworldroute = GridWorldRoute("MHC", GridWorld(Earth::CityCampus, 1000, -20));
	std::string filePath(LogFiles::GPXRoutesDir + sn + "-PositiveElevationChange-MHC.gpx");
	GenerateLogFile(filePath, gridworldroute.toGPX(true));
	Route r1 = Route(filePath, isFileName);
	//Testing to see if the function returns '40'. Because there is two point moves, and the elevation will increase by 40 each move, the function should return a net gain of 40.
	BOOST_CHECK_CLOSE( r1.netHeightGain(), 40, errormargin);

	//Generating log files when the test is called to run.
	GridWorldRoute gridworldroute2 = GridWorldRoute("MRW", GridWorld(Earth::CityCampus, 1000, -50));
	std::string filePath2(LogFiles::GPXRoutesDir + sn + "-PositiveElevationChange-MRW.gpx");
	GenerateLogFile(filePath2, gridworldroute2.toGPX(true));
	//Testing to see if the function returns '100'. This test was conducted with double digits to ensure that the function would continue to run correctly across triple digits.
	Route r2 = Route(filePath2, isFileName);
	BOOST_CHECK_CLOSE( r2.netHeightGain(), 100, errormargin);


}

//These tests ensure that when elevation is negative, the function will return 0, as the function is designed to ignore negative elevations or any negative net height calculation.
BOOST_AUTO_TEST_CASE ( negative_elevation_change )
{

	//Generating log files when the test is called to run.
	GridWorldRoute gridworldroute = GridWorldRoute("MHC", GridWorld(Earth::CityCampus, 1000, 20));
	std::string filePath(LogFiles::GPXRoutesDir + sn + "-NegativeElevationChange-MHC.gpx");
	GenerateLogFile(filePath, gridworldroute.toGPX(true));
	Route r1 = Route(filePath, isFileName);

	//As the gpx log contains negative elevations, the function should return 0 because the net elevation gain is negative.
	BOOST_CHECK_CLOSE( r1.netHeightGain(), 0, errormargin);

	//Generating log files when the test is called to run.
	GridWorldRoute gridworldroute2 = GridWorldRoute("MRW", GridWorld(Earth::CityCampus, 1000, 40));
	std::string filePath2(LogFiles::GPXRoutesDir + sn + "-NegativeElevationChange-MRW.gpx");
	GenerateLogFile(filePath2, gridworldroute2.toGPX(true));
	Route r2 = Route(filePath2, isFileName);
	//As the gpx log contains negative elevations, the function should return 0 because the net elevation gain is negative.
	BOOST_CHECK_CLOSE( r2.netHeightGain(), 0, errormargin);

}


//These tests are designed to test the function against unusual values, to ensure the function persists when given difficult or missing values.
BOOST_AUTO_TEST_CASE ( unexpected_values ) 
{
	//Generating a GPX log file that will contain blank elevation and the default city of Pontiak.
	GridWorldRoute gridworldroute = GridWorldRoute("ABC");
	std::string filePath(LogFiles::GPXRoutesDir + sn + "-NoElevationValue-ABC.gpx");
	GenerateLogFile(filePath, gridworldroute.toGPX(true));
	Route r1 = Route(filePath, isFileName);
	//This will test to see that the function returns '0', as the elevation values in this GPX log are all '0'.
	BOOST_CHECK_CLOSE( r1.netHeightGain(), 0, errormargin);

	//Generating a GPX log file that will contain a large increase in elevation, to ensure calculations persist when given large numbers of elevation.
	GridWorldRoute gridworldroute2 = GridWorldRoute("MHC", GridWorld(Earth::CityCampus, 1000, -20000));
	std::string filePath2(LogFiles::GPXRoutesDir + sn + "-LargeElevationIncrease-MHC.gpx");
	GenerateLogFile(filePath2, gridworldroute2.toGPX(true));
	Route r2 = Route(filePath2, isFileName);
	//The function should return 40000, as each step in the log will increase elevation by 20000.
	BOOST_CHECK_CLOSE( r2.netHeightGain(), 40000, errormargin);


	//Generates a GPX log with a large negative elevation drop to test large negative calculations still return 0.
	GridWorldRoute gridworldroute3 = GridWorldRoute("MRW", GridWorld(Earth::CityCampus, 1000, 10000));
	std::string filePath3(LogFiles::GPXRoutesDir + sn + "-LargeElevationDecrease-MRW.gpx");
	GenerateLogFile(filePath3, gridworldroute3.toGPX(true));
	Route r3 = Route(filePath3, isFileName);
	//The function should return 0 as the net elevation calculation is negative.
	BOOST_CHECK_CLOSE( r3.netHeightGain(), 0, errormargin);
	
}
BOOST_AUTO_TEST_SUITE_END()

#include <iostream>
#include <fstream>
#include "logs.h"
#include "route.h"
#include "track.h"
#include "earth.h"
#include "geometry.h"
#include "gridworld_route.h"


using namespace GPS;


std::string createLogFile(std::string name, GridWorldRoute routeLog)
{
    // Converts the GridWorldRoute in to GPX format.
    std::string routeGPX = routeLog.toGPX(true, name);

    std::ofstream openedFile(LogFiles::GPXRoutesDir + name + ".gpx");
    openedFile << routeGPX;
    openedFile.close();

    return name;
}


int main()
{
    const metres HORIZONTAL_GRID_UNIT = 1000;

    std::cout << "CREATING LOG FILES..." << std::endl;

    std::cout << createLogFile("OnePointPositive-N0724629", GridWorldRoute("B", Position(52.9581383, 1.1542364, 53))) << ".gpx created." << std::endl;

    std::cout << createLogFile("RepeatedPoints-N0724629", GridWorldRoute("KDLDK", GridWorld(Position(52.9581383, 1.1542364, 53), HORIZONTAL_GRID_UNIT))) << ".gpx created." << std::endl;

    std::cout << createLogFile("PointsApart-N0724629", GridWorldRoute("KQHEA", GridWorld(Position(52.91249953, 1.18402513, 58), HORIZONTAL_GRID_UNIT))) << ".gpx created." << std::endl;

    std::cout << createLogFile("PointsTooClose-N0724629", GridWorldRoute("ILADN", GridWorld(Earth::CityCampus, HORIZONTAL_GRID_UNIT))) << ".gpx created." << std::endl;

    std::cout << createLogFile("ZeroValues-N0724629", GridWorldRoute("IEKS", GridWorld(Earth::EquatorialMeridian, 0))) << ".gpx created." << std::endl;

    std::ofstream openedFile(LogFiles::GPXRoutesDir + "EmptyFile-N0724629.gpx");
    openedFile.close();
    std::cout << "EmptyFile-N0724629.gpx created." << std::endl;

    return 0;
}

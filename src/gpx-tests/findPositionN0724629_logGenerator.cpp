#include <fstream>
#include "logs.h"
#include "route.h"
#include "track.h"
#include "earth.h"
#include "geometry.h"
#include "gridworld_route.h"

using namespace GPS;

namespace GPX
{
    const metres HORIZONTAL_GRID_UNIT = 1000;

    void createLogFile(std::string name, GridWorldRoute routeLog)
    {
        // Converts the GridWorldRoute in to GPX format.
        std::string routeGPX = routeLog.toGPX(true, name);

        std::ofstream openedFile(LogFiles::GPXRoutesDir + name + ".gpx");
        openedFile << routeGPX;
        openedFile.close();
    }

    void generateLogFiles()
    {
        createLogFile("OnePointPositive-N0724629", GridWorldRoute("B", Position(52.9581383, 1.1542364, 53)));

        createLogFile("RepeatedPoints-N0724629", GridWorldRoute("KDLDDK", GridWorld(Earth::CliftonCampus, 0)));

        createLogFile("PointsApart-N0724629", GridWorldRoute("KQLD", GridWorld(Earth::CityCampus, HORIZONTAL_GRID_UNIT)));

        createLogFile("PointsTooClose-N0724629", GridWorldRoute("ILADN", GridWorld(Earth::CityCampus, HORIZONTAL_GRID_UNIT)));

        createLogFile("ZeroValues-N0724629", GridWorldRoute("IEKS", GridWorld(Earth::EquatorialMeridian, 0)));

        createLogFile("NoElevation-N0724629", GridWorldRoute("EAL", GridWorld(Earth::NorthPole, 0)));

        std::ofstream openedFile(LogFiles::GPXRoutesDir + "EmptyFile-N0724629.gpx");
        openedFile.close();
    }
}

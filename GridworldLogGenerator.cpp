#include "gridworld.h"
#include "gridworld_route.h"
#include <iostream>
#include <fstream>

using namespace GPS;

int main()
{
    std::string gridWorldString = "HMRW";
    std::string fileName = gridWorldString + "GridN0749943.gpx";
    std::string filePath = "../logs/GPX/routes/" + fileName;
    if (!GridWorldRoute::isValidRouteString(gridWorldString))
    {
        return - 1;
    }
    GridWorldRoute generatedRoute = GridWorldRoute(gridWorldString);
    std::string GPXRoute = generatedRoute.toGPX();
    std::ofstream output(filePath);
    output << GPXRoute;
    output.close();

    return 0;
}

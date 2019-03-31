#include <fstream>

#include "logs.h"
#include "gridworld_route.h"
#include "accessOperatorLogGenerator.h"

using namespace GPS;

namespace GPX {
    GridWorldRoute singlePositionLog(const std::string & fileName)
    {
        GridWorldRoute route = GridWorldRoute("A");
        std::ofstream fileOutput(LogFiles::GPXRoutesDir + fileName);
        
        fileOutput << route.toGPX();

        return route;
    }

    GridWorldRoute generateLogFile(const std::string & routeString)
    {
        GridWorldRoute route = GridWorldRoute(routeString);
        std::ofstream fileOutput(LogFiles::GPXRoutesDir + routeString);

        fileOutput << route.toGPX();

        return route;
    }
}


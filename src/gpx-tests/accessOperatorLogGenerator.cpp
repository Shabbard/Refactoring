#include <fstream>

#include "logs.h"
#include "gridworld_route.h"
#include "accessOperatorLogGenerator.h"

using namespace GPS;

namespace GPX {
    // Generates a log file based upon a gridworld route string, using that
    // as the filename.
    GridWorldRoute generateLogFile(const std::string & routeString)
    {
        GridWorldRoute route = GridWorldRoute(routeString);
        std::ofstream fileOutput(LogFiles::GPXRoutesDir + routeString + ".gpx");

        fileOutput << route.toGPX();

        return route;
    }
}


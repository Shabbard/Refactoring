#include <fstream>
#include "gridworld_route.h"
#include "logs.h"
#include "route.h"
#include "track.h"
#include "types.h"
#include "position.h"

using namespace GPS;

namespace GPSGen{ //GPX log file generator
    std::string createlogFile(std::string test, GridWorldRoute LogofRoute)
    {
        std::string trueName = test + "-n0673737.gpx";
        std::ofstream fileOutput(GPS::LogFiles::GPXRoutesDir + truename);
        fileOutput << route.toGPX();
        fileOutput.close();

        return trueName;
    }
}

#include <fstream>
#include "logs.h"
#include "gridworld_route.h"

//N0741707

using namespace GPS;

namespace Generator
{
    std::string createGPXLog(std::string name, GridWorldRoute routeData)
    {
        //Used to generate the GPX log file from the GridWorldRoute data passed to the function

        std::string fileName = name + ".gpx";

        std::ofstream file(LogFiles::GPXRoutesDir + fileName);
        file << routeData.toGPX(true, fileName);
        file.close();

        return fileName;
    }
} // namespace Generator
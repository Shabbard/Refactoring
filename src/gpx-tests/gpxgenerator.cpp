#include "logs.h"
#include "route.h"
#include "track.h"
#include "types.h"
#include "geometry.h"
#include "earth.h"
#include "gridworld_route.h"
#include <stdexcept>
#include <iostream>
#include <fstream>



using namespace GPS;

//N0665742
//Function to build GPX file
std::string BuildGPXFile(std::string name, GridWorldRoute routePoint)
{
    std::string NewFile = name + "N0665742.gpx";
    std::string gpxData = routePoint.toGPX(true, name);
    std::ofstream gpxFile(LogFiles::GPXRoutesDir + NewFile);
    gpxFile << gpxData;
    gpxFile.close();
    return NewFile;
}



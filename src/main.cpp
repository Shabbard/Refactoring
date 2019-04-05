#include <iostream>
#include <string>
#include <vector>
#include <fstream> 
#include <cstdlib>
#include <ctime>
#include <random>

#include "gridworld.h"
#include "gridworld_route.h"

using namespace GPS;

const std::string ROUTES_DIR = "../logs/GPX/routes/";
const std::string LOG_EXTENSION = ".gpx";


Position generate_random_position() {

    std::random_device random_dev;
    std::default_random_engine engine(random_dev());
    // latitude must be within [-90, 90]
    std::uniform_real_distribution<> distrib_latitude(-90, 90);
    // longitude must be within [-180, 180]
    std::uniform_real_distribution<> distrib_longitude(-180, 180);
    
    const degrees latitude = distrib_latitude(engine);
    const degrees longitude = distrib_longitude(engine);
    // elevation is not relevant for these tests
    const metres elevation = 0.0;

    return Position(latitude, longitude, elevation);
}

void gen_route(const std::string& route_path) {

    const std::string full_path = ROUTES_DIR + route_path + LOG_EXTENSION;
                                  
    GridWorld grid(Position(90.0001, 23.4225));
    GridWorldRoute grid_world_route(route_path, grid);

    std::ofstream out(full_path);
    out << grid_world_route.toGPX();
    out.close();
}

int main() {

    srand(time(nullptr));

    std::vector<std::string> paths {
        // empty route
        "",
        // unique point route
        "A", 
        // same point route
        "AAA", 
        // all points route
        "ABCDEFGHIJKLMNOPQRSTUVWXY",
        // same latitude route
        "ABCDE"
    };

    for (const std::string path : paths) {
        gen_route(path);
    }

    return 0;
}

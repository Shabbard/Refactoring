#include <iostream>
#include <string>
#include <vector>
#include <fstream> 

#include "logs.h"
#include "gridworld.h"
#include "gridworld_route.h"

using namespace GPS;

void gen_route(const Position& position, const std::string& route_path, const metres horizontal_grid_unit = 10000) {

    GridWorld grid(position, horizontal_grid_unit);    
    GridWorldRoute grid_world_route(route_path, grid);

    const std::string full_path = LogFiles::GPXRoutesDir + route_path + ".gpx";

    std::ofstream out(full_path);
    out << grid_world_route.toGPX();
    out.close();
}

int main() {

    const Position arbitrary_position(-47.961321, 3.592466, 24);

    gen_route(arbitrary_position, "Q");
    gen_route(arbitrary_position, "QQQQ");
    gen_route(arbitrary_position, "ABCDEFGHIJKLMNOPQRSTUVWXY");    
    gen_route(Earth::CityCampus, "EORU");
    gen_route(Earth::EquatorialMeridian, "AMYEU", 0);

    return 0;
}

#include <sstream>
#include <cassert>
#include <cmath>
#include <stdexcept>

#include "xmlgenerator.h"
#include "geometry.h"
#include "gridworld.h"

using namespace GPS;

const int GridWorld::gridSize = 5;

GridWorld::GridWorld(const Position & posM, metres horizontalGridUnit, metres verticalGridUnit)
{
    /* A B C D E
     * F G H I J
     * K L M N O
     * P Q R S T
     * U V W X Y
     */

    degrees deltaLat = Earth::latitudeSubtendedBy(horizontalGridUnit);
    degrees deltaLon = Earth::longitudeSubtendedBy(horizontalGridUnit,posM.latitude());

    GridWorld::Point currentPoint = 'A';
    degrees lat = posM.latitude() + 2*deltaLat;
    for (int i = 0; i < gridSize; ++i)
    {
        degrees lon = posM.longitude() - 2*deltaLon;
        for (int j = 0; j < gridSize; ++j)
        {
            metres ele = calcElevationFor(currentPoint, posM.elevation(), verticalGridUnit);
            std::pair<degrees,degrees> normLatLon = normaliseLatLon(lat,lon);
            grid.insert({currentPoint,Position(normLatLon.first,normLatLon.second,ele)});
            lon += deltaLon;
            ++currentPoint;
        }
        lat -= deltaLat;
    }
}

const Position& GridWorld::operator[](Point point) const
{
    return grid.at(point);
}

metres GridWorld::calcElevationFor(Point point, metres eleM, metres verticalGridUnit)
{
    /* "eleM" is the elevation of Point M.
     * Neighbours of M are 1 vertical grid unit lower than M.
     * All other Points are 2 vertical grid units lower than M.
     */
    switch (point)
    {
        case 'M':
            return eleM;
        case 'G': case 'H': case 'I': case 'L': case 'N': case 'Q': case 'R': case 'S':
            return eleM - verticalGridUnit;
        default:
            return eleM - (2 * verticalGridUnit);
    }
}

std::pair<degrees,degrees> GPS::normaliseLatLon(degrees lat, degrees lon)
{
    // First get latitude in (-180,180] range
    lat = normaliseDeg(lat);

    // Now ensure latitude does not pass the North Pole.
    if (lat > poleLatitude)
    {
        lat = halfRotation - lat;
        lon += halfRotation; // On the other side of the world.
    }

    // Now ensure latitude does not pass the South Pole.
    if (lat < -poleLatitude)
    {
        lat = -halfRotation - lat;
        lon += halfRotation; // On the other side of the world.
    }

    // Ensure longitude does not exceed Greenwich anti-meridian (180' E/W).
    lon = normaliseDeg(lon);

    return {lat,lon};
}

#ifndef GRIDWORLD_H_211217
#define GRIDWORLD_H_211217

#include <map>

#include "types.h"
#include "position.h"
#include "earth.h"

namespace GPS
{
  /* GridWorld consists of a grid of points, where each point is named by a single character A-Y.
   *
   *  A B C D E
   *  F G H I J
   *  K L M N O
   *  P Q R S T
   *  U V W X Y
   *
   *  The central point M is used as the initial reference point.
   *  Up/down in the grid changes latitude relative to M.
   *  Left/right in the grid changes longitude relative to M.
   *  Note: the closer you get to a pole, the more distorted from a grid this becomes.
   */

  class GridWorld
  {
    public:
      using Point = char;
      static const int gridSize;

      // Defaults to Pontianak, the only equatorial city.
      GridWorld(const Position & posM = Earth::Pontianak, // Position of the central point 'M'.
                metres horizontalGridUnit = 10000, // Horizontal distance between grid points.
                metres verticalGridUnit = 0); // Vertical distance between grid levels.

      const Position& operator[](Point) const;

    private:
      std::map<Point,Position> grid;

      /* The first parameter is the grid Point.
       * The second parameter is the elevation of Point M.
       * The third parameter is the vertical distance between grid points.
       */
      static metres calcElevationFor(Point point, metres eleM, metres verticalGridUnit);
  };

  // Ensure lat/lon are within range after local modifications.
  std::pair<degrees,degrees> normaliseLatLon(degrees lat, degrees lon);
}

#endif

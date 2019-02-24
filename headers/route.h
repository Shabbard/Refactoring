#ifndef ROUTE_H_211217
#define ROUTE_H_211217

#include <string>
#include <vector>

#include "types.h"
#include "position.h"

namespace GPS
{
  class Route
  {
    public:
      /*  Routes are constructed from GPX data.  The data can be provided as a string, or from a file.
       *  Any route points closer together than a certain minimum distance are discarded.
       */
      Route(std::string source,
            bool isFileName, // Is the first parameter a file name or a string containing GPX data?
            metres granularity = 20); // The minimum distance between successive route points.

      // Returns a report of the construction process; useful for debugging purposes.
      std::string buildReport() const;

      /* Update the granularity of the stored Route.  Any position in the Route that differs in distance
       * from its predecessor by less than the updated granularity is discarded.
       */
      virtual void setGranularity(metres);

      // Returns the name of the Route, or "Unnamed Route" if nameless.
      std::string name() const;

      // Returns the number of stored route points.
      unsigned int numPositions() const;

      // The total length of the Route; this is the sum of the distances between successive route points.
      metres totalLength() const;

      // The distance between the first and last points on the Route.
      metres netLength() const;

      // The sum of all the positive (>0) height differences between successive route points.
      // That is, downhill changes are ignored.
      metres totalHeightGain() const;

      // The increase in height from the start point to the finishing point.
      // Should return zero if the height difference is negative.
      metres netHeightGain() const;

      // The steepest uphill gradient (in degrees) between successive points on the route.
      // If the entire route is downhill, then this is the least steep downhill gradient (i.e. negative).
      degrees maxGradient() const;

      // The steepest downhill gradient (in degrees) between successive points on the Route.
      // If the entire route is uphill, then this is the least steep uphill gradient (i.e. positive).
      degrees minGradient() const;

      // The steepest gradient between successive points on the Route, whether uphill or downhill.
      degrees steepestGradient() const;

      // The latitude of the most Southerly point on the Route.
      degrees minLatitude() const;

      // The latitude of the most Northerly point on the Route.
      degrees maxLatitude() const;

      // The longitude of the most Westerly point on the Route.
      degrees minLongitude() const;

      // The longitude of the most Easterly point on the Route.
      degrees maxLongitude() const;

      // The elevation of the lowest point on the Route.
      metres minElevation() const;

      // The elevation of the highest point on the Route.
      metres maxElevation() const;

      // Return the route point at the specified index.
      // Throws a std::out_of_range exception if out-of-range.
      Position operator[](unsigned int) const;

      // Find the route point bearing the specified name.
      // Throws a std::out_of_range exception if the name is not found.
      Position findPosition(const std::string & soughtName) const;

      // Find the name of a route point.
      // Throws a std::out_of_range exception if that Position is not within "granularity" of any stored route points.
      std::string findNameOf(const Position &) const;

      // Compute how many times the specified route point is visited during the route.
      unsigned int timesVisited(const std::string & soughtName) const;
      unsigned int timesVisited(const Position &) const;

    protected:
      Route() {} // Only called by Track constructor.

      metres granularity;

      metres routeLength;
      std::string routeName;
      std::vector<Position> positions;
      std::vector<std::string> positionNames;

      std::string report;

      /* Two Positions are considered to be the same location is they are less than
       * "granularity" metres apart (horizontally).
       */
      bool areSameLocation(const Position &, const Position &) const;
  };
}

#endif

#ifndef TRACK_H_211217
#define TRACK_H_211217

#include <string>
#include <vector>

#include "types.h"
#include "position.h"
#include "route.h"

namespace GPS
{
  class Track : public Route
  {
    public:
      /*  Tracks are constructed from GPX data.  The data can be provided as a string, or from a file.
       *  Any track points closer together than a certain minimum distance are discarded.
       */
      Track(std::string source,
            bool isFileName, // Is the first parameter a file name or a string containing GPX data?
            metres granularity = 10); // The minimum distance between successive track points.

      /* Update the granularity of the stored Track.  Any position in the Track that differs in distance
       * from its predecessor by less than the updated granularity is discarded.
       */
      void setGranularity(metres) override;

      // Total elapsed time between start and finish of track.
      seconds totalTime() const;

      // Total elapsed time between start and finish of the Track that is spent moving.
      seconds travellingTime() const;

      // Total elapsed time between start and finish of the Track that is spent not moving.
      seconds restingTime() const;

      // The fastest speed between successive track points.
      // Returns 0 if the entire track is stationary.
      speed maxSpeed() const;

      // The average speed between successive track points over the course of the whole track.
      // The parameter controls whether rests should be included in the average or not.
      // Returns 0 if the entire track is stationary.
      speed averageSpeed(bool includeRests) const;

      // The fastest rate of positive elevation change between successive track points.
      // Returns 0 if the entire track is downhill or stationary.
      speed maxRateOfAscent() const;

      // The fastest rate of negative elevation change between successive track points.
      // Returns 0 if the entire track is uphill or stationary.
      speed maxRateOfDescent() const;

    protected:
      /* These vectors store the arrival time and departure time at each
       * Position in the Track.  These times are relative to the start of
       * the Track; thus arrived[0] is always 0.
       */
      std::vector<seconds> arrived;
      std::vector<seconds> departed;

      static seconds stringToTime(const std::string &);
  };
}

#endif

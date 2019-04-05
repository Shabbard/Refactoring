#ifndef GRIDWORLD_TRACK_H_120218
#define GRIDWORLD_TRACK_H_120218

#include <string>
#include <vector>

#include "gridworld.h"

namespace GPS
{
/* This class generates tracks in the form of GPX or NMEA data.
 *
 * To use this class, the user must provide a string of GridWorld::Points,
 * interspersed with time units, specifying the track path and times.
 * E.g. "A1B3C" means that it takes 1 time unit to travel from Point A to Point B,
 * then 3 time units to travel from Point B to Point C.
 *
 * The locations of these points are interpreted in a GridWorld (see GridWorld.h).
 * The user may provide a GridWorld object; if not the default GridWorld is used.
 */
  class GridWorldTrack
  {
    public:
      GridWorldTrack(std::string track, // A string containing Points and time units.
                     seconds timeUnitDuration = 10, // Duration (in seconds) of a time unit.
                     seconds absoluteStartTime = 0, // Absolute start time of the Track.
                     GridWorld gridworld = GridWorld()); // The default GridWorld can be overwritten if desired.

      // Produce a GPX representation of the track.
      std::string toGPX(seconds logInterval, // Time interval between generated tracking points.
                        bool embedName = true, // Whether a <name> element should be included in the generated GPX file.
                        const std::string& trackName = "") const; // Contents of <name> element.  If empty, defaults to the track string.

      // Produce a NMEA representation of the track.
      std::string toNMEA(seconds logInterval) const; // unimplemented

      // Produce a string representation of the track.
      std::string toString() const;

      // Check whether the argument would be a valid string for creating a GridWorldTrack.
      static bool isValidTrackString(const std::string &);

      // Convert a track string into a route string (by discarding the timing information).
      static std::string routeStringFromTrackString(const std::string &);

    private:
      const std::string trackString;
      const GridWorld gridworld;
      const seconds timeUnitDuration;
      const seconds startTime;

      std::vector<GridWorld::Point> waypoints;
      std::vector<unsigned int> timeUnitsToNextWaypoint;

      void constructWaypoints();
  };
}

#endif


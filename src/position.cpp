#include <cassert>
#include <cmath>
#include <sstream>
#include <stdexcept>

#include "geometry.h"
#include "earth.h"
#include "position.h"

namespace GPS
{
  Position::Position(degrees lat, degrees lon, metres ele)
  {
      if (std::abs(lat) > poleLatitude)
          throw std::invalid_argument("Latitude values must not exceed " + std::to_string(poleLatitude) + " degrees.");

      if (std::abs(lon) > antiMeridianLongitude)
          throw std::invalid_argument("Longitude values must not exceed " + std::to_string(antiMeridianLongitude) + " degrees.");

      this->lat = lat;
      this->lon = lon;
      this->ele = ele;
  }

  Position::Position(const std::string & latStr,
                     const std::string & lonStr,
                     const std::string & eleStr)
      : Position(std::stod(latStr), std::stod(lonStr), std::stod(eleStr)) {}

  Position::Position(const std::string & ddmLatStr, char northing,
                     const std::string & ddmLonStr, char easting,
                     const std::string & eleStr)
      : Position(ddmTodd(ddmLatStr), ddmTodd(ddmLonStr), std::stod(eleStr))
  {
      if (lat < 0)
          throw std::invalid_argument("Latitude values must be positive when accompanied by a N/S bearing.");

      if (lon < 0)
          throw std::invalid_argument("Longitude values must be positive when accompanied by an E/W bearing.");

      switch (northing)
      {
          case 'N': break;             // 'N' means positive angle, so no change
          case 'S': lat = -lat; break; // 'S' means negative angle
          default: throw std::invalid_argument(northing + std::string(" is an invalid North/South bearing character in DDM format.  Only 'N' or 'S' accepted."));
      }

      switch (easting)
      {
          case 'E': break;             // 'E' means positive angle, so no change
          case 'W': lon = -lon; break; // 'W' means negative angle
          default: throw std::invalid_argument(easting + std::string(" is an invalid East/West bearing character in DDM format.  Only 'E' or 'W' accepted."));
      }

  }

  degrees Position::latitude() const
  {
      return lat;
  }

  degrees Position::longitude() const
  {
      return lon;
  }

  metres Position::elevation() const
  {
      return ele;
  }

  std::string Position::toString(bool includeElevation) const
  {
      std::ostringstream oss;

      oss <<  "lat=\"" << lat << "\"";
      oss << " lon=\"" << lon << "\"";
      if (includeElevation) {
          oss << " ele=\"" << ele << "\"";
      }

      return oss.str();
  }

  metres Position::distanceBetween(const Position & p1, const Position & p2)
  /*
   * See: http://en.wikipedia.org/wiki/Law_of_haversines
   */
  {
      const radians lat1 = degToRad(p1.latitude());
      const radians lat2 = degToRad(p2.latitude());
      const radians lon1 = degToRad(p1.longitude());
      const radians lon2 = degToRad(p2.longitude());

      double h = sinSqr((lat2-lat1)/2) + std::cos(lat1)*std::cos(lat2)*sinSqr((lon2-lon1)/2);
      return 2 * Earth::meanRadius * std::asin(sqrt(h));
  }

  degrees ddmTodd(const std::string & ddmStr)
  {
      double ddm  = std::stod(ddmStr);
      double degs = std::floor(ddm / 100);
      double mins = ddm - 100 * degs;
      return degs + mins / 60.0; // converts minutes (1/60th) to decimal fractions of a degree
  }
}

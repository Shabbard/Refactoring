#include <cmath>

#include "geometry.h"

namespace GPS
{
  const double pi = 3.141592653589793;
  const degrees fullRotation = 360;
  const degrees halfRotation = fullRotation/2;
  const degrees poleLatitude = fullRotation/4;
  const degrees antiMeridianLongitude = fullRotation/2;

  radians degToRad(degrees d)
  {
      return d * pi / halfRotation;
  }

  degrees radToDeg(radians r)
  {
      return r * halfRotation / pi;
  }

  double sinSqr(radians x)
  {
      const double sx = std::sin(x);
      return sx * sx;
  }

  degrees normaliseDeg(degrees d)
  {
      d = fmod(d,fullRotation); // results in range (-360,360)
      if (d <= -halfRotation) d += fullRotation; // results in range (-180,360)
      if (d > halfRotation) d -= fullRotation; // results in range (-180,180]
      return d;
  }
}

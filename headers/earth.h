#ifndef EARTH_H_120218
#define EARTH_H_120218

#include "position.h"

namespace GPS
{
  namespace Earth
  {
      extern const Position NorthPole;
      extern const Position EquatorialMeridian;
      extern const Position EquatorialAntiMeridian;
      extern const Position CliftonCampus;
      extern const Position CityCampus;
      extern const Position Pontianak;

      extern const metres meanRadius;
      extern const metres equatorialCircumference;
      extern const metres polarCircumference;

      degrees latitudeSubtendedBy(metres);
      degrees longitudeSubtendedBy(metres,degrees lat);
  }
}

#endif


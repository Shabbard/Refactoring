TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    headers/earth.h \
    headers/geometry.h \
    headers/logs.h \
    headers/position.h \
    headers/route.h \
    headers/track.h \
    headers/types.h \
    headers/xmlparser.h \
    headers/xmlgenerator.h \
    headers/gridworld.h \
    headers/gridworld_route.h \
    headers/gridworld_track.h \
    headers/accessOperatorLogGenerator.h

SOURCES += \
    src/earth.cpp \
    src/gpx-tests.cpp \
    src/geometry.cpp \
    src/logs.cpp \
    src/position.cpp \
    src/route.cpp \
    src/track.cpp \
    src/xmlparser.cpp \
    src/xmlgenerator.cpp \
    src/gridworld.cpp \
    src/gridworld_route.cpp \
    src/gridworld_track.cpp \
    src/gpx-tests/name.cpp \
    src/gpx-tests/numpositions.cpp \
    src/gpx-tests/maxElevationN0774756.cpp \
    src/gpx-tests/accessOperator.cpp \
    src/gpx-tests/accessOperatorLogGenerator.cpp \
    src/gpx-tests/maxLongitudeN0743797.cpp \
    src/gpx-tests/steepestGradient.cpp \
    src/gpx-tests/steepestGradientN0742908.cpp \
    src/gpx-tests/steepestGradient-N0826291.cpp \
    src/gpx-tests/findNameOf.cpp \
    src/gpx-tests/findNameOfGPXGenerator.cpp \
    src/gpx-tests/findPositionN0724629.cpp \
    src/gpx-tests/findpositionn0734208.cpp \
    src/gpx-tests/maxSpeedN0737110.cpp \
    src/gpx-tests/maxlatitude.cpp \
    src/gpx-tests/maxSpeedN0733894.cpp \
    src/gpx-tests/N0774446-TotalHeightGain.cpp \
    src/gpx-tests/maxGradient-n0756303.cpp \
    src/gpx-tests/maxspeedn0736188.cpp \
    src/gpx-tests/totalLengthTest_n0755314.cpp \
    src/gpx-tests/netLength-N0704050.cpp\
    src/gpx-tests/restingTimeN0736563.cpp \
    # src/gpx-tests/maxlongitude.cpp \
    # src/gpx-tests/maxGradient-N0740369.cpp \
    src/gpx-tests/netHeightGain-N0679817.cpp \
    src/gpx-tests/netHeightGain-N0675532.cpp 
    src/gpx-tests/maxGradient-N0740369.cpp \
    src/gpx-tests/MaxElevation-N0749370.cpp \
    src/gpx-tests/minLongitude.cpp \
    src/gpx-tests/minlatitude-n0743587.cpp \
    src/gpx-tests/netLength-N0745509.cpp \
    src/gpx-tests/maxLongitude.cpp \
    src/gpx-tests/timesVisited-n0763258.cpp \
    src/gpx-tests/maxLongitudeN0732961.cpp \
    src/gpx-tests/netHeightGain-N0701387.cpp \
    src/gpx-tests/maxelevation-N0749364.cpp \
    src/gpx-tests/minLongitudeN0735026.cpp \
    src/gpx-tests/totalHeightGainN0724106.cpp \
    src/gpx-tests/netLength-N0731739.cpp 
    # src/gpx-tests/maxGradientN0748944.cpp \
    #src/gpx-tests/maxLatitudeN0756079.cpp \
    #src/gpx-tests/findPositionN0724629.cpp \
    #src/gpx-tests/totalTimeN0774540.cpp \

    #Breaks code:
    #src/gpx-tests/findnameofn0665742.cpp \
    #src/gpx-tests/restingTimeN0736563.cpp\
    #Please ensure the a successful build before pushing to the master. Thanks.

INCLUDEPATH += headers/

TARGET = $$_PRO_FILE_PWD_/execs/gpx-tests

LIBS += -lboost_unit_test_framework

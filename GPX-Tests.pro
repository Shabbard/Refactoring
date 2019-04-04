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
    src/gpx-tests/maxElevationN0774756.cpp \

    
    #Breaks code:
    #src/gpx-tests/maxlongitude.cpp \
    #src/gpx-tests/restingTimeN0736563.cpp\
    #Please ensure the a successful build before pushing to the master. Thanks.

INCLUDEPATH += headers/

TARGET = $$_PRO_FILE_PWD_/execs/gpx-tests

LIBS += -lboost_unit_test_framework

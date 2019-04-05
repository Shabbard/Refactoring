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
    headers/xmlparser.h \
    headers/xmlgenerator.h \
    headers/gridworld.h \
    headers/gridworld_route.h

SOURCES += \
    src/earth.cpp \
    src/geometry.cpp \
    src/logs.cpp \
    src/position.cpp \
    src/route.cpp \
    src/track.cpp \
    src/xmlparser.cpp \
    src/xmlgenerator.cpp \
    src/gridworld.cpp \
    src/gridworld_route.cpp \
    src/gpx-tests/findPositionN0724629_logGenerator.cpp

INCLUDEPATH += headers/

TARGET = $$_PRO_FILE_PWD_/execs/findPositionN0724629_logGenerator

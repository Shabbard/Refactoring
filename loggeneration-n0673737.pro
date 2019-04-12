TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    headers/earth.h \
    headers/geometry.h \
    headers/logs.h \
    headers/position.h \
    headers/types.h \
    headers/xmlparser.h \
    headers/gridworld_route.h \
    headers/gridworld_track.h \
    headers/xmlgenerator.h \
    headers/gridworld.h

SOURCES += \
    src/earth.cpp \
    src/geometry.cpp \
    src/logs.cpp \
    src/position.cpp \
    src/xmlparser.cpp \
    src/xmlgenerator.cpp \
    src/gridworld_route.cpp \
    src/gridworld_track.cpp \
    src/maingenerator.cpp \
    src/gridworld.cpp

INCLUDEPATH += headers/

TARGET = $$_PRO_FILE_PWD_/execs/gpx

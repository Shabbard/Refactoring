#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>

#include "geometry.h"
#include "xmlparser.h"
#include "track.h"

using namespace GPS;

// Note: The implementation should exploit the relationship:
//   totalTime() == restingTime() + travellingTime()

seconds Track::totalTime() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

seconds Track::restingTime() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

seconds Track::travellingTime() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

speed Track::maxSpeed() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

speed Track::averageSpeed(bool includeRests) const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

speed Track::maxRateOfAscent() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

speed Track::maxRateOfDescent() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

Track::Track(std::string source, bool isFileName, metres granularity)
{
    using namespace std;
    using namespace XML::Parser;
    string mergedTrkSegs,trkseg,lat,lon,ele,name,time,temp,temp2;
    metres deltaH,deltaV;
    seconds startTime, currentTime, timeElapsed;
    ostringstream oss,oss2;
    unsigned int num;
    this->granularity = granularity;
    if (isFileName) {
        ifstream fs = ifstream(source);
        if (! fs.good()) throw invalid_argument("Error opening source file '" + source + "'.");
        oss << "Source file '" << source << "' opened okay." << endl;
        while (fs.good()) {
            getline(fs, temp);
            oss2 << temp << endl;
        }
        source = oss2.str();
    }
    if (! elementExists(source,"gpx")) throw domain_error("No 'gpx' element.");
    temp = getElement(source, "gpx");
    source = getElementContent(temp);
    if (! elementExists(source,"trk")) throw domain_error("No 'trk' element.");
    temp = getElement(source, "trk");
    source = getElementContent(temp);
    if (elementExists(source, "name")) {
        temp = getAndEraseElement(source, "name");
        routeName = getElementContent(temp);
        oss << "Track name is: " << routeName << endl;
    }
    while (elementExists(source, "trkseg")) {
        temp = getAndEraseElement(source, "trkseg");
        trkseg = getElementContent(temp);
        getAndEraseElement(trkseg, "name");
        mergedTrkSegs += trkseg;
    }
    if (! mergedTrkSegs.empty()) source = mergedTrkSegs;
    num = 0;
    if (! elementExists(source,"trkpt")) throw domain_error("No 'trkpt' element.");
    temp = getAndEraseElement(source, "trkpt");
    if (! attributeExists(temp,"lat")) throw domain_error("No 'lat' attribute.");
    if (! attributeExists(temp,"lon")) throw domain_error("No 'lon' attribute.");
    lat = getElementAttribute(temp, "lat");
    lon = getElementAttribute(temp, "lon");
    temp = getElementContent(temp);
    if (elementExists(temp, "ele")) {
        temp2 = getElement(temp, "ele");
        ele = getElementContent(temp2);
        Position startPos = Position(lat,lon,ele);
        positions.push_back(startPos);
        oss << "Start position added: " << startPos.toString() << endl;
        ++num;
    } else {
        Position startPos = Position(lat,lon);
        positions.push_back(startPos);
        oss << "Start position added: " << startPos.toString() << endl;
        ++num;
    }
    if (elementExists(temp,"name")) {
        temp2 = getElement(temp,"name");
        name = getElementContent(temp2);
    }
    positionNames.push_back(name);
    arrived.push_back(0);
    departed.push_back(0);
    if (! elementExists(temp,"time")) throw domain_error("No 'time' element.");
    temp2 = getElement(temp,"time");
    time = getElementContent(temp2);
    startTime = currentTime = stringToTime(time);
    Position prevPos = positions.back(), nextPos = positions.back();
    while (elementExists(source, "trkpt")) {
        temp = getAndEraseElement(source, "trkpt");
        if (! attributeExists(temp,"lat")) throw domain_error("No 'lat' attribute.");
        if (! attributeExists(temp,"lon")) throw domain_error("No 'lon' attribute.");
        lat = getElementAttribute(temp, "lat");
        lon = getElementAttribute(temp, "lon");
        temp = getElementContent(temp);
        if (elementExists(temp, "ele")) {
            temp2 = getElement(temp, "ele");
            ele = getElementContent(temp2);
            nextPos = Position(lat,lon,ele);
        } else nextPos = Position(lat,lon);
        if (! elementExists(temp,"time")) throw domain_error("No 'time' element.");
        temp2 = getElement(temp,"time");
        time = getElementContent(temp2);
        currentTime = stringToTime(time);
        if (areSameLocation(nextPos, prevPos)) {
            // If we're still at the same location, then we haven't departed yet.
            departed.back() = currentTime - startTime;
            oss << "Position ignored: " << nextPos.toString() << endl;
        } else {
            if (elementExists(temp,"name")) {
                temp2 = getElement(temp,"name");
                name = getElementContent(temp2);
            } else name = ""; // Fixed bug by adding this.
            positions.push_back(nextPos);
            positionNames.push_back(name);
            timeElapsed = currentTime - startTime;
            arrived.push_back(timeElapsed);
            departed.push_back(timeElapsed);
            oss << "Position added: " << nextPos.toString() << endl;
            oss << " at time: " << to_string(timeElapsed) << endl;
            ++num;
            prevPos = nextPos;
        }
    }
    oss << num << " positions added." << endl;
    routeLength = 0;
    for (unsigned int i = 1; i < num; ++i ) {
        deltaH = Position::distanceBetween(positions[i-1], positions[i]);
        deltaV = positions[i-1].elevation() - positions[i].elevation();
        routeLength += sqrt(pow(deltaH,2) + pow(deltaV,2));
    }
    report = oss.str();
}

void Track::setGranularity(metres granularity)
{
    bool implemented = false;
    assert(implemented);
}

seconds Track::stringToTime(const std::string & timeStr)
{
    return stoull(timeStr);
}

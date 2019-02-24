#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>

#include "geometry.h"
#include "xmlparser.h"
#include "route.h"

using namespace GPS;

std::string Route::name() const
{
    return routeName.empty() ? "Unnamed Route" : routeName;
}

unsigned int Route::numPositions() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

metres Route::totalLength() const
{
    return routeLength;
}

metres Route::netLength() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

metres Route::totalHeightGain() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

metres Route::netHeightGain() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

degrees Route::minLatitude() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

degrees Route::maxLatitude() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

degrees Route::minLongitude() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

degrees Route::maxLongitude() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

metres Route::minElevation() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

metres Route::maxElevation() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

degrees Route::maxGradient() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

degrees Route::minGradient() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

degrees Route::steepestGradient() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

Position Route::operator[](unsigned int idx) const
{
    const bool implemented = false;
    assert(implemented);
    return Position(0,0);
}

Position Route::findPosition(const std::string & soughtName) const
{
    const bool implemented = false;
    assert(implemented);
    return Position(0,0);
}

std::string Route::findNameOf(const Position & soughtPos) const
{
    const bool implemented = false;
    assert(implemented);
    return "";
}

unsigned int Route::timesVisited(const std::string & soughtName) const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

unsigned int Route::timesVisited(const Position & soughtPos) const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

std::string Route::buildReport() const
{
    return report;
}

Route::Route(std::string source, bool isFileName, metres granularity)
{
    using namespace std;
    using namespace XML::Parser;
    string lat,lon,ele,name,temp,temp2;
    metres deltaH,deltaV;
    ostringstream oss,oss2;
    unsigned int num;
    this->granularity = granularity;
    if (isFileName){
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
    if (! elementExists(source,"rte")) throw domain_error("No 'rte' element.");
    temp = getElement(source, "rte");
    source = getElementContent(temp);
    if (elementExists(source, "name")) {
        temp = getAndEraseElement(source, "name");
        routeName = getElementContent(temp);
        oss << "Route name is: " << routeName << endl;
    }
    num = 0;
    if (! elementExists(source,"rtept")) throw domain_error("No 'rtept' element.");
    temp = getAndEraseElement(source, "rtept");
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
        oss << "Position added: " << startPos.toString() << endl;
        ++num;
    } else {
        Position startPos = Position(lat,lon);
        positions.push_back(startPos);
        oss << "Position added: " << startPos.toString() << endl;
        ++num;
    }
    if (elementExists(temp,"name")) {
        temp2 = getElement(temp,"name");
        name = getElementContent(temp2);
    }
    positionNames.push_back(name);
    Position prevPos = positions.back(), nextPos = positions.back();
    while (elementExists(source, "rtept")) {
        temp = getAndEraseElement(source, "rtept");
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
        if (areSameLocation(nextPos, prevPos)) oss << "Position ignored: " << nextPos.toString() << endl;
        else {
            if (elementExists(temp,"name")) {
                temp2 = getElement(temp,"name");
                name = getElementContent(temp2);
            } else name = ""; // Fixed bug by adding this.
            positions.push_back(nextPos);
            positionNames.push_back(name);
            oss << "Position added: " << nextPos.toString() << endl;
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

void Route::setGranularity(metres granularity)
{
    bool implemented = false;
    assert(implemented);
}

bool Route::areSameLocation(const Position & p1, const Position & p2) const
{
    return (Position::distanceBetween(p1,p2) < granularity);
}

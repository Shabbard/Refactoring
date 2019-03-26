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
    //const bool implemented = true;
    //assert(implemented);
    return (unsigned int)positions.size();
}

// Matt
metres Route::totalLength() const
{
    // The total length of the Route; this is the sum of the distances between successive route points.
    return routeLength;
}
 // Matt
metres Route::netLength() const
{
    Position firstPosition = positions[0];
    Position lastPosition = positions[positions.size() - 1];

    if ( areSameLocation(firstPosition, lastPosition) )
    {
        return 0;
    }
    
    return Position::distanceBetween(firstPosition, lastPosition);
}
 // Matt
metres Route::totalHeightGain() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

// Matt
metres Route::netHeightGain() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

// Callum C
degrees Route::minLatitude() const
{
    degrees lowestLatitude = positions[0].latitude();
    
    for (int i = 0; i < positions.size(); i++)
    {
        if (lowestLatitude < positions[i].latitude())
        {
            lowestLatitude = positions[i].latitude();
        }
    }
    return lowestLatitude;
}

// Callum C
degrees Route::maxLatitude() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

// Callum C
degrees Route::minLongitude() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

// Callum C
degrees Route::maxLongitude() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

// Tom
metres Route::minElevation() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

// Tom
metres Route::maxElevation() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

// Tom
degrees Route::maxGradient() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

// Tom
degrees Route::minGradient() const
{
    const bool implemented = false;
    assert(implemented);
    return 0;
}

// Callum A
degrees Route::steepestGradient() const
{
    const bool implemented = false;
    assert(implemented);

    auto firstPosition = positions.at(0);
    double initialElevation = firstPosition.elevation();

    double initialGradient{0}, currentElevation{0}, steepest{0};
    for(const auto &i: positions) {
        double difference = currentElevation - i.elevation();
        
        if (difference > steepest)
        {
            steepest = difference;
        }
    }
    
    return steepest;
}

// Callum A
Position Route::operator[](unsigned int idx) const
{
    return positions.at(idx);
}

// Callum A
Position Route::findPosition(const std::string & soughtName) const
{
    auto position = std::find(positionNames.begin(), positionNames.end(), soughtName);

    if (position == positionNames.end()) {
        throw std::out_of_range("Position not found.");
    }

    auto index = std::distance(positionNames.begin(), position);

    return positions.at(index);
}
 // Callum A
std::string Route::findNameOf(const Position & soughtPos) const
{
    const bool implemented = false;
    assert(implemented);
    return "";
}

// Callum A
unsigned int Route::timesVisited(const std::string & soughtName) const
{
    Position position = this->findPosition(soughtName);

    unsigned int timesVisited{0};

    for (const auto &i: positions)
        if (areSameLocation(i, position)) timesVisited++;

    return timesVisited;
}

// Callum A
unsigned int Route::timesVisited(const Position & soughtPos) const
{
    unsigned int timesVisited{0};

    for (const auto &i: positions)
        if (areSameLocation(i, soughtPos)) timesVisited++;

    return timesVisited;
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
        ifstream fs(source);
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

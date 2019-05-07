
#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <algorithm>

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
    return (unsigned int)positions.size();
}

metres Route::totalLength() const
{
    // The total length of the Route; this is the sum of the distances between successive route points.
    return routeLength;
}

metres Route::netLength() const
{
    Position firstPosition = positions[0];
    Position lastPosition = positions[positions.size() - 1];

    if (areSameLocation(firstPosition, lastPosition))
    {
        return 0;
    }

    return Position::distanceBetween(firstPosition, lastPosition);
}

metres Route::totalHeightGain() const
{
    assert(!positions.empty());

    metres total = 0.0;
    for (unsigned int i = 1; i < numPositions(); ++i)
    {
        metres deltaV = positions[i].elevation() - positions[i - 1].elevation();
        if (deltaV > 0.0)
            total += deltaV; // ignore negative height differences
    }
    return total;
}

metres Route::netHeightGain() const
{
    assert(!positions.empty());

    metres deltaV = positions.back().elevation() - positions.front().elevation();
    return std::max(deltaV, 0.0); // ignore negative height differences
}

degrees Route::minLatitude() const
{
    if (positions.empty())
    {
        throw std::out_of_range("Cannot get the minimum latitude of an empty route");
    }

    degrees lowestLatitude = positions[0].latitude();

    double epsilon = 0.0001;

    for (int i = 0; i < positions.size(); i++)
    {
        if ((positions[i].latitude() - lowestLatitude) < epsilon)
        {
            lowestLatitude = positions[i].latitude();
        }
    }

    return lowestLatitude;
}

degrees Route::maxLatitude() const
{
    degrees currentMax = positions[0].latitude();

    for (int i = 0; i < positions.size(); i++)
    {
        if (positions[i].latitude() > currentMax)
            currentMax = positions[i].latitude();
    }

    return currentMax;
}

degrees Route::minLongitude() const //MY FUNCTION
{
    assert(!positions.empty());

    degrees minLon = positions.front().longitude();
    for (const Position &pos : positions)
    {
        minLon = std::min(minLon, pos.longitude());
    }
    return minLon;
}

degrees Route::maxLongitude() const
{
    assert(!positions.empty());

    degrees maxLon = positions.front().longitude();
    for (const Position &pos : positions)
    {
        maxLon = std::max(maxLon, pos.longitude());
    }
    return maxLon;
}

metres Route::minElevation() const
{
    assert(!positions.empty());

    degrees minEle = positions.front().elevation();
    for (const Position &pos : positions)
    {
        minEle = std::min(minEle, pos.elevation());
    }
    return minEle;
}

metres Route::maxElevation() const
{
    assert(!positions.empty());

    degrees maxEle = positions.front().elevation();
    for (const Position &pos : positions)
    {
        maxEle = std::max(maxEle, pos.elevation());
    }
    return maxEle;
}

degrees Route::maxGradient() const
{
    assert(!positions.empty());

    if (positions.size() == 1)
        return 0.0;

    degrees maxGrad = -halfRotation / 2; // minimum possible value
    for (unsigned int i = 1; i < positions.size(); ++i)
    {
        metres deltaH = Position::distanceBetween(positions[i], positions[i - 1]);
        metres deltaV = positions[i].elevation() - positions[i - 1].elevation();
        degrees grad = radToDeg(std::atan(deltaV / deltaH));
        maxGrad = std::max(maxGrad, grad);
    }
    return maxGrad;
}

degrees Route::minGradient() const
{
    assert(!positions.empty());

    if (positions.size() == 1)
        return 0.0;

    degrees minGrad = halfRotation / 2; // maximum possible value
    for (unsigned int i = 1; i < positions.size(); ++i)
    {
        metres deltaH = Position::distanceBetween(positions[i], positions[i - 1]);
        metres deltaV = positions[i].elevation() - positions[i - 1].elevation();
        degrees grad = radToDeg(std::atan(deltaV / deltaH));
        minGrad = std::min(minGrad, grad);
    }
    return minGrad;
}

degrees Route::steepestGradient() const
{
    assert(!positions.empty());

    if (positions.size() == 1)
        return 0.0;

    degrees maxGrad = -halfRotation / 2; // minimum possible value
    for (unsigned int i = 1; i < positions.size(); ++i)
    {
        metres deltaH = Position::distanceBetween(positions[i], positions[i - 1]);
        metres deltaV = positions[i].elevation() - positions[i - 1].elevation();
        degrees grad = radToDeg(std::atan(deltaV / deltaH));
        maxGrad = std::max(maxGrad, std::abs(grad));
    }
    return maxGrad;
}

Position Route::operator[](unsigned int idx) const
{
    return positions.at(idx);
}

Position Route::findPosition(const std::string &soughtName) const
{
    auto nameIt = std::find(positionNames.begin(), positionNames.end(), soughtName);

    if (nameIt == positionNames.end())
    {
        throw std::out_of_range("No position with that name found in the route.");
    }
    else
    {
        return positions[std::distance(positionNames.begin(), nameIt)];
    }
}

std::string Route::findNameOf(const Position &soughtPos) const
{
    auto posIt = std::find_if(positions.begin(), positions.end(),
                              [&](const Position &pos) { return areSameLocation(pos, soughtPos); });

    if (posIt == positions.end())
    {
        throw std::out_of_range("Position not found in route.");
    }
    else
    {
        return positionNames[std::distance(positions.begin(), posIt)];
    }
}

unsigned int Route::timesVisited(const std::string &soughtName) const
{
    unsigned int timesVisited{0};

    try
    {

        Position position = this->findPosition(soughtName);
        for (const auto &i : positions)
            if (areSameLocation(i, position))
                timesVisited++;
    }
    catch (const std::out_of_range &e)
    {
    }

    return timesVisited;
}

unsigned int Route::timesVisited(const Position &soughtPos) const
{
    unsigned int timesVisited{0};

    for (const auto &i : positions)
        if (areSameLocation(i, soughtPos))
            timesVisited++;

    return timesVisited;
}

std::string Route::buildReport() const
{
    return report;
}

Route::Route(std::string source, bool isFileName, metres granularity)
{


    ////////////////////////////////////////////////////////////////
    //                checkAndGetElementContent()                 //
    // Function to check that each element is in the file         //
    ////////////////////////////////////////////////////////////////


    auto checkAndGetElementContent = [](std::string source, std::string type)
    {
        if (!XML::Parser::elementExists(source, type))  { throw std::domain_error("No " + type + " element."); }
        return XML::Parser::getElementContent(XML::Parser::getElement(source, type));        
    };
    

    ////////////////////////////////////////////////////////
    //           checkAndGetElementAttribute()            //
    // Function to check that each element is in the file //
    ////////////////////////////////////////////////////////


    auto checkAndGetElementAttribute = [](std::string source, std::string type)
    {
        if (!XML::Parser::attributeExists(source, type)) { throw std::domain_error("No " + type + " attribute."); }
        return XML::Parser::getElementAttribute(source, type); 
    };

    ///////////////////////////////////////////////////////
    //                  runThroughFile()                 //
    // Function to get the stream of strings from a file //
    ///////////////////////////////////////////////////////

    auto runThroughFile = [](std::string source, bool isFileName)
    {
        std::ostringstream ossPrivate, ossToReturn;
        if (isFileName)
        {
            std::ifstream fs(source);
            if (!fs.good())
                throw std::invalid_argument("Error opening source file '" + source + "'.");
            ossPrivate << "Source file '" << source << "' opened okay." << std::endl;
            while (fs.good())
            {
                std::string fileLine;
                getline(fs, fileLine);
                ossToReturn << fileLine << std::endl;
            }
            //source = oss2.str();     
            return ossToReturn.str(); 
        }
        return source;
    };


    ////////////////////////
    // Constant variables //
    ////////////////////////


    const std::string GPXSTRING = "gpx";
    const std::string RTESTRING = "rte";
    const std::string NAMESTRING = "name";
    const std::string RTEPTSTRING = "rtept";
    const std::string LATSTRING = "lat";
    const std::string LONSTRING = "lon";
    const std::string ELESTRING = "ele";

    //////////////////////////////////////////////////
    // Variables that need to be changed throughout //
    //////////////////////////////////////////////////


    std::string lat, lon, ele, name, temp, temp2;
    metres deltaH, deltaV;
    
    setGranularity(granularity);

    

    Position prevPos = positions.back(), nextPos = positions.back();
    std::ostringstream stringStream;


    //////////////////////////////////////////////////////////////////////////////////
    // numPositions is incremented to show updated position throughout the function //
    //////////////////////////////////////////////////////////////////////////////////

    unsigned int numPositions;


    source = runThroughFile(source, isFileName);
    source = checkAndGetElementContent(source, GPXSTRING);
    source = checkAndGetElementContent(source, RTESTRING);

    if (XML::Parser::elementExists(source, NAMESTRING)) 
    {    
        routeName = XML::Parser::getElementContent(XML::Parser::getAndEraseElement(source, NAMESTRING));
        stringStream << "Route name is: " << routeName << std::endl;
    }

    if (!XML::Parser::elementExists(source, RTEPTSTRING)) { throw std::domain_error("No 'rtept' element."); }

    numPositions = 0;
    
    while (XML::Parser::elementExists(source, RTEPTSTRING))
    {
        std::string routePoint = XML::Parser::getAndEraseElement(source, RTEPTSTRING);
        lat = checkAndGetElementAttribute(routePoint, LATSTRING);
        lon = checkAndGetElementAttribute(routePoint, LONSTRING);
        
        routePoint = XML::Parser::getElementContent(routePoint);

        if (XML::Parser::elementExists(routePoint, ELESTRING)) { ele = XML::Parser::getElementContent(XML::Parser::getElement(routePoint, ELESTRING)); }
        else { ele = "0"; /* default no elevation */ }

        if (areSameLocation(nextPos, prevPos)) stringStream << "Position ignored: " << nextPos.toString() << std::endl;

        if (!positions.empty())
        {
            Position startPos = Position(lat, lon, ele);
            stringStream << "Position added: " << startPos.toString() << std::endl;
            positions.push_back(startPos);   
            prevPos = positions.back();
            nextPos = positions.back();
        }
        else {
            Position startPos = Position(lat,lon);
            positions.push_back(startPos);
            stringStream << "Position added: " << startPos.toString() << std::endl;
            //++numPositions;
        }



        if (XML::Parser::elementExists(routePoint, NAMESTRING)) { name = XML::Parser::getElementContent(XML::Parser::getElement(routePoint, NAMESTRING)); }
        
        positionNames.push_back(name);
        while (XML::Parser::elementExists(source, RTEPTSTRING))
        {
            temp = XML::Parser::getAndEraseElement(source, RTEPTSTRING);
            if (! XML::Parser::attributeExists(temp,"lat")) throw std::domain_error("No 'lat' attribute.");
            if (! XML::Parser::attributeExists(temp,"lon")) throw std::domain_error("No 'lon' attribute.");
               lat = XML::Parser::getElementAttribute(temp, "lat");
            lon = XML::Parser::getElementAttribute(temp, "lon");
            temp = XML::Parser::getElementContent(temp);
            if (XML::Parser::elementExists(temp, "ele")) {
                temp2 = XML::Parser::getElement(temp, "ele");
                ele = XML::Parser::getElementContent(temp2);
                nextPos = Position(lat,lon,ele);
            } else nextPos = Position(lat,lon);
            if (areSameLocation(nextPos, prevPos)) stringStream << "Position ignored: " << nextPos.toString() << std::endl;
            else {
                if (XML::Parser::elementExists(temp,"name")) 
                {
                    temp2 = XML::Parser::getElement(temp,"name");
                    name = XML::Parser::getElementContent(temp2);
                } 
                else name = ""; // Fixed bug by adding this.
                positions.push_back(nextPos);
                positionNames.push_back(name);
                stringStream << "Position added: " << nextPos.toString() << std::endl;
                ++numPositions;
                prevPos = nextPos;
            }
        }
    }
    

    stringStream << numPositions << " positions added." << std::endl;

    routeLength = 0;

    for (unsigned int i = 1; i < numPositions; ++i)
    {
        deltaH = Position::distanceBetween(positions[i - 1], positions[i]);
        deltaV = positions[i - 1].elevation() - positions[i].elevation();
        routeLength += sqrt(pow(deltaH, 2) + pow(deltaV, 2));
    }
    
    report = stringStream.str();
    
}

void Route::setGranularity(metres granularity)
{
    bool implemented = true;
    assert(implemented);
    this->granularity = granularity;
}

bool Route::areSameLocation(const Position &p1, const Position &p2) const
{
    return (Position::distanceBetween(p1, p2) < granularity);
}

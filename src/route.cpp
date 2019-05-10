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

std::string Route::runThroughFile(std::string source, bool isFileName) // Using auto finds the correct return type. Inputs are also captured.
{
    std::ostringstream ossToReturn; // Creates local function stream of data to be returned to main stream
    if (isFileName)
    {
        std::ifstream fs(source);
        if (!fs.good()) // ensures that file is the correct one. If not error is thrown with the source name
        {
            throw std::invalid_argument("Error opening source file '" + source + "'.");
        }      
        while (fs.good())
        {
            std::string fileLine;
            getline(fs, fileLine);  // reads each line of the file
            ossToReturn << fileLine << std::endl;   // each line is then added to the local stream
        }
    }
    return ossToReturn.str();   // returns the local stream
};

std::string Route::checkAndGetElementAttribute(std::string source, std::string type)
{
    if (!XML::Parser::attributeExists(source, type)) { throw std::domain_error("No " + type + " attribute."); }
    return XML::Parser::getElementAttribute(source, type); 
};

std::string Route::checkAndGetElementContent(std::string source, std::string type)
{
    if (!XML::Parser::elementExists(source, type))  { throw std::domain_error("No " + type + " element."); }
    return XML::Parser::getElementContent(XML::Parser::getElement(source, type));        
};   

std::string Route::getAndEraseContent(std::string source, std::string type)
{
    return XML::Parser::getElementContent(XML::Parser::getAndEraseElement(source,type)); // gets the element content and erases it from the source afterwards
};

void Route::calculateRouteLength()
{
    routeLength = 0;
    metres deltaH = 0, deltaV = 0;

    for (unsigned int i = 0; i < positions.size() -1; ++i)      // using the positions created throughout a route is created.
    {
        deltaH = Position::distanceBetween(positions[i], positions[i + 1]);
        deltaV = positions[i + 1].elevation() - positions[i].elevation();
        routeLength += sqrt(pow(deltaH, 2) + pow(deltaV, 2));
    }
}

Route::Route(std::string source, bool isFileName, metres granularity)
{
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

    std::string lat, lon, pointName, routePoint; // creates strings to be changed throughout
 
    setGranularity(granularity); // sets the granulatiry from a pre defineted pointer function

    std::ostringstream stringStream;    // creates a string stream to be updated throughout and returned to the report.

    ////////////////////////
    // Computation starts //
    ////////////////////////

    source = runThroughFile(source, isFileName); // pulls the stream of data from the source file.
    stringStream << "Source file '" << source << "' opened okay." << std::endl;       // if nothing is thrown then confirmation is added to the local stream
    source = checkAndGetElementContent(source, GPXSTRING);  // checks that there is a 'gpx' string inside of source
    source = checkAndGetElementContent(source, RTESTRING);  // checks that there is a 'rtk' string inside of source

    if (XML::Parser::elementExists(source, NAMESTRING)) 
    {    
        routeName = getAndEraseContent(source, NAMESTRING);
        stringStream << "Route name is: " << routeName << std::endl;    //  inserts the name to the stream
    }

    if (!XML::Parser::elementExists(source, RTEPTSTRING)) { throw std::domain_error("No 'rtept' element."); } // if can not find 'rtept' string then error is thrown

    while (XML::Parser::elementExists(source, RTEPTSTRING))  // continues to loop is there is a 'rtept' inside of source
    {
        routePoint = XML::Parser::getAndEraseElement(source, RTEPTSTRING); // sets routePoint the the 'rtept'
        lat = checkAndGetElementAttribute(routePoint, LATSTRING);   // sets lat to the 'lat'
        lon = checkAndGetElementAttribute(routePoint, LONSTRING);   // sets lon to the 'lon'
        
        routePoint = XML::Parser::getElementContent(routePoint);    // sets routepoint to all the current content. Takes over source as a temp

        std::string ele;    // creates the elevation to be changed 
        if (XML::Parser::elementExists(routePoint, ELESTRING)) { ele = checkAndGetElementContent(routePoint, ELESTRING); }    // if there is a evevation sets ele to it
        else { ele = "0"; } // if there is no elevation found then it defaults to 0
        
        Position CurrentPos = Position(lat, lon, ele);    // combines the lat,lon,ele into a position element

        if (!positions.empty() && areSameLocation(CurrentPos, positions.back())) { stringStream << "Position ignored: " << CurrentPos.toString() << std::endl; }
        else
        {
            positions.push_back(CurrentPos); // pushes back the current position
            stringStream << "Position added: " << CurrentPos.toString() << std::endl;   // adds the current position to the string stream
            if (XML::Parser::elementExists(routePoint, NAMESTRING)) { pointName = checkAndGetElementContent(routePoint, NAMESTRING); }
            positionNames.push_back(pointName);
        }
    }

    stringStream << positions.size() << " positions added." << std::endl; // adds the positions to the stream using the size of the vector as the number of positions

    ///////////////////////////////////////////////////
    // Setting variable parameters ready for looping //
    ///////////////////////////////////////////////////

    calculateRouteLength();
    
    report = stringStream.str(); // converts the current string stream into a string to create the report
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

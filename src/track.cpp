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
    assert(! departed.empty());
    return departed.back();
}

seconds Track::restingTime() const
{
    seconds total = 0;
    assert (arrived.size() == departed.size());
    for (unsigned int i = 0; i < arrived.size(); ++i)
    {
        total += departed[i] - arrived[i];
    }
    return total;
}

seconds Track::travellingTime() const
{
    return totalTime() - restingTime();
}

speed Track::maxSpeed() const
{
    assert( positions.size() == departed.size() && positions.size() == arrived.size() );
    if (positions.size() == 1) return 0.0;

    speed ms = 0;
    for (unsigned int i = 1; i < positions.size(); ++i)
    {
        metres deltaH = Position::distanceBetween(positions[i],positions[i-1]);
        metres deltaV = positions[i].elevation() - positions[i-1].elevation();
        metres distance = std::sqrt(std::pow(deltaH,2) + std::pow(deltaV,2));
        seconds time = arrived[i] - departed[i-1];
        ms = std::max(ms,distance/time);
    }
    return ms;
}

speed Track::averageSpeed(bool includeRests) const
{
    seconds time = (includeRests ? totalTime() : travellingTime());
    if (time == 0) return 0;
    else return totalLength() / time;
}

speed Track::maxRateOfAscent() const
{
    assert( positions.size() == departed.size() && positions.size() == arrived.size() );
    if (positions.size() == 1) return 0.0;

    speed ms = 0;
    for (unsigned int i = 1; i < positions.size(); ++i)
    {
        metres height = positions[i].elevation() - positions[i-1].elevation();
        seconds time = arrived[i] - departed[i-1];
        ms = std::max(ms,height/time);
    }
    return ms;
}

speed Track::maxRateOfDescent() const
{
    assert( positions.size() == departed.size() && positions.size() == arrived.size() );
    if (positions.size() == 1) return 0.0;

    speed ms = 0;
    for (unsigned int i = 1; i < positions.size(); ++i)
    {
        metres height = positions[i-1].elevation() - positions[i].elevation();
        seconds time = arrived[i] - departed[i-1];
        ms = std::max(ms,height/time);
    }
    return ms;
}
void checkElementExistsThrow(std::string source, std::string type)
{
    if (! XML::Parser::elementExists(source,type)) throw std::domain_error("No " + type + " element.");
}
void checkAttributeExistsThrow(std::string source, std::string type)
{
    if (! XML::Parser::attributeExists(source,type)) throw std::domain_error("No " + type + " element.");
}

bool checkElementExistsBool(std::string source, std::string type)
{
    if (XML::Parser::attributeExists(source,type)) 
        {
        return true;
        }
    return true;
}

Track::Track(std::string source, bool isFileName, metres granularity)
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

    auto checkAndEraseContent = [](std::string source, std::string type)
    {
        return XML::Parser::getElementContent(XML::Parser::getAndEraseElement(source,type));
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
    //               checkAndGetElement()                 //
    //      returns the element that is requested        //
    ///////////////////////////////////////////////////////

    auto checkAndGetElement = [](std::string source, std::string type)
    {
        if (!XML::Parser::elementExists(source, type)) { throw std::domain_error("No " + type + " attribute."); }
        return XML::Parser::getElement(source, type); 
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

    auto checkAndEraseElement = [](std::string source, std::string type)
    {
        return XML::Parser::getAndEraseElement(source, type);
    };

    ////////////////////////
    // Constant variables //
    ////////////////////////

    const std::string GPXSTRING = "gpx";
    const std::string RTKSTRING = "trk";
    const std::string TRKSEGSTRING = "trkseg";
    const std::string TRKPTSTRING = "trkpt";
    const std::string NAMESTRING = "name";
    const std::string LATSTRING = "lat";
    const std::string LONSTRING = "lon";
    const std::string ELESTRING = "ele";
    const std::string TIMESTRING = "time";

    //////////////////////////////////////////
    // Variables that may change throughout //
    //////////////////////////////////////////

    std::string mergedTrkSegs,trkseg,lat,lon,ele,name,time,trackPoint;
    seconds startTime, currentTime, timeElapsed;
    std::ostringstream stringStream;
    Position startPos = Position(0,0,0), nextPos = Position(0,0,0), prevPos = Position(0,0,0);
    unsigned int numOfPosition;
    setGranularity(granularity);


    //////////////////////////////////////////////////////////////////////////
    // Uses Lambda to find source for each stringType & opening source file //
    //////////////////////////////////////////////////////////////////////////

    source = runThroughFile(source, isFileName);
    source = checkAndGetElementContent(source, GPXSTRING);
    source = checkAndGetElementContent(source, RTKSTRING);


    // if (XML::Parser::elementExists(source, NAMESTRING)) {
    //     routeName = checkAndGetElementContent(checkAndEraseElement(source,NAMESTRING), NAMESTRING);
    //     stringStream << "Track name is: " << routeName << std::endl;
    // }

    if (XML::Parser::elementExists(source, NAMESTRING)) {
        routeName = checkAndEraseContent(source, NAMESTRING);
        stringStream << "Track name is: " << routeName << std::endl;
    }

    

    while (XML::Parser::elementExists(source, TRKSEGSTRING)) {
        
        trackPoint = XML::Parser::getAndEraseElement(source, TRKSEGSTRING);
        trkseg = XML::Parser::getElementContent(trackPoint);
        XML::Parser::getAndEraseElement(trkseg, NAMESTRING);
        mergedTrkSegs += trkseg;
    }



    if (! mergedTrkSegs.empty()) source = mergedTrkSegs;
    numOfPosition = 0;

    while (XML::Parser::elementExists(source, TRKPTSTRING)) 
    {
        checkElementExistsThrow(source, TRKPTSTRING);
        trackPoint = checkAndEraseElement(source, TRKPTSTRING);
        checkAttributeExistsThrow(checkAndEraseElement(source, TRKPTSTRING), LATSTRING);
        checkAttributeExistsThrow(checkAndEraseElement(source, TRKPTSTRING), LONSTRING);

        lat = checkAndGetElementAttribute(trackPoint,LATSTRING);
        lon = checkAndGetElementAttribute(trackPoint, LONSTRING);
        trackPoint = XML::Parser::getElementContent(trackPoint);

        if (XML::Parser::elementExists(trackPoint,ELESTRING)) { ele = checkAndEraseContent(trackPoint,ELESTRING); }
        else { ele = "0"; }

        if (positions.empty())
        {
            startPos = Position(lat,lon,ele);  
            positions.push_back(startPos);

            stringStream << "Start position added: " << startPos.toString() << std::endl;
            if (XML::Parser::elementExists(trackPoint,NAMESTRING)) { name = XML::Parser::getElementContent(XML::Parser::getElement(trackPoint,NAMESTRING)); }
            positionNames.push_back(name);

            ++numOfPosition;

            prevPos = positions.back(), nextPos = positions.back();

            arrived.push_back(0);
            departed.push_back(0);

            checkElementExistsThrow(trackPoint,TIMESTRING);

            time = XML::Parser::getElementContent(XML::Parser::getElement(trackPoint,TIMESTRING));
            //time = checkAndGetElementContent(trackPoint,TIMESTRING);
            startTime = currentTime = stringToTime(time);
            // do everything related to the start position here
        }
        else
        {
            nextPos = Position(lat,lon,ele);
            if (! XML::Parser::elementExists(trackPoint,TIMESTRING)) throw std::domain_error("No 'time' element.");
            time = XML::Parser::getElementContent(XML::Parser::getElement(trackPoint,TIMESTRING));
            currentTime = stringToTime(time);
            if (areSameLocation(nextPos, prevPos)) 
            {
                departed.back() = currentTime - startTime;
                stringStream << "Position ignored: " << nextPos.toString() << std::endl;
            }
            else
            {
                //do everything for the rest of the positions
                
                stringStream << "Position added: " << nextPos.toString() << std::endl;
                if (XML::Parser::elementExists(trackPoint,NAMESTRING)) { name = XML::Parser::getElementContent(XML::Parser::getElement(trackPoint,NAMESTRING)); }
                positions.push_back(nextPos);
                positionNames.push_back(name);

                ++numOfPosition;
                timeElapsed = currentTime - startTime;
                arrived.push_back(timeElapsed);
                departed.push_back(timeElapsed);
                stringStream << " at time: " << std::to_string(timeElapsed) << std::endl;
                prevPos = nextPos;
            }
        }
    
    }
    
    
    
    // while (XML::Parser::elementExists(source, TRKPTSTRING)) {
        
    //     // trackPoint = XML::Parser::getAndEraseElement(source, TRKPTSTRING);
    //     // if (! XML::Parser::attributeExists(trackPoint,LATSTRING)) throw std::domain_error("No 'lat' attribute.");
    //     // if (! XML::Parser::attributeExists(trackPoint,LONSTRING)) throw std::domain_error("No 'lon' attribute.");
    //     // lat = checkAndGetElementAttribute(trackPoint, LATSTRING);
    //     // lon = checkAndGetElementAttribute(trackPoint, LONSTRING);
    //     // trackPoint = XML::Parser::getElementContent(trackPoint);
        

        
    //     if (XML::Parser::elementExists(trackPoint, ELESTRING)) {
    //         ele = XML::Parser::getElementContent(XML::Parser::getElement(trackPoint, ELESTRING));
    //         nextPos = Position(lat,lon,ele);
    //     } else nextPos = Position(lat,lon);
    //     if (! XML::Parser::elementExists(trackPoint,TIMESTRING)) throw std::domain_error("No 'time' element.");
    //     time = XML::Parser::getElementContent(XML::Parser::getElement(trackPoint,TIMESTRING));
    //     currentTime = stringToTime(time);
    //     if (areSameLocation(nextPos, prevPos)) {
    //         // If we're still at the same location, then we haven't departed yet.
    //         // departed.back() = currentTime - startTime;
    //         // stringStream << "Position ignored: " << nextPos.toString() << std::endl;
    //     } //else {
    //         if (XML::Parser::elementExists(trackPoint,NAMESTRING)) {

    //             //name = XML::Parser::getElementContent(XML::Parser::getElement(trackPoint,NAMESTRING));
    //         // } else name = ""; // Fixed bug by adding this.
    //         // positions.push_back(nextPos);
    //         // positionNames.push_back(name);
    //         // timeElapsed = currentTime - startTime;
    //         // arrived.push_back(timeElapsed);
    //         // departed.push_back(timeElapsed);
    //         // stringStream << "Position added: " << nextPos.toString() << std::endl;
    //         // stringStream << " at time: " << std::to_string(timeElapsed) << std::endl;
    //         // ++numOfPosition;
    //         // prevPos = nextPos;
    //     }
    //}

    stringStream << numOfPosition << " positions added." << std::endl;
    routeLength = 0;
    metres deltaH = 0, deltaV = 0;
    
    for (unsigned int i = 1; i < numOfPosition; ++i) 
    {
        deltaH = Position::distanceBetween(positions[i-1], positions[i]);
        deltaV = positions[i-1].elevation() - positions[i].elevation();
        routeLength += sqrt(pow(deltaH,2) + pow(deltaV,2));
    }
    report = stringStream.str();
    
}

void Track::setGranularity(metres granularity)
{
    bool implemented = true;
    this->granularity = granularity;
    assert(implemented);
}

seconds Track::stringToTime(const std::string & timeStr)
{
    return stoull(timeStr);
}
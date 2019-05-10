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
        if (!XML::Parser::elementExists(source, type))  { throw std::domain_error("No " + type + " element."); } // accepts the source and checks if the element exits, throws an error otherwise
        return XML::Parser::getElementContent(XML::Parser::getElement(source, type)); // if the element exists then return its content
    };

    auto checkAndEraseContent = [](std::string source, std::string type)
    {
        return XML::Parser::getElementContent(XML::Parser::getAndEraseElement(source,type)); // gets the element content and erases it from the source afterwards
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

    std::string mergedTrkSegs,trackPoint;       // creates strings to be changed

    seconds startTime, currentTime, timeElapsed;        // creates seconds to be changed

    std::ostringstream stringStream;        // creates string stream to store the stream
    
    setGranularity(granularity);        // sets the granularity from a pre defined function using a pointer


    ///////////////////////////////////////////////////////
    //                  runThroughFile()                 //
    // Function to get the stream of strings from a file //
    ///////////////////////////////////////////////////////

    auto runThroughFile = [&stringStream, source, isFileName]() // Using auto finds the correct return type. Inputs are also captured.
    {
        std::ostringstream ossPrivate, ossToReturn; // Creates local function stream of data to be returned to main stream
        if (isFileName)
        {
            std::ifstream fs(source);
            if (!fs.good())         // ensures that file is the correct one. If not error is thrown with the source name
                throw std::invalid_argument("Error opening source file '" + source + "'.");
            ossPrivate << "Source file '" << source << "' opened okay." << std::endl;       // if nothing is thrown then confirmation is added to the local stream
            while (fs.good())
            {
                std::string fileLine;
                getline(fs, fileLine);  // reads each line of the file
                ossToReturn << fileLine << std::endl;   // each line is then added to the local stream
            }
        }
        return ossToReturn.str();   // returns the local stream
    };

    source = runThroughFile();  // pulls the stream of data from the source file.
    source = checkAndGetElementContent(source, GPXSTRING);  // checks that there is a 'gpx' string inside of source
    source = checkAndGetElementContent(source, RTKSTRING);  // checks that there is a 'rtk' string inside of source

    if (XML::Parser::elementExists(source, NAMESTRING))         
    {
        routeName = checkAndEraseContent(source, NAMESTRING);
        stringStream << "Track name is: " << routeName << std::endl;        //  inserts the name to the stream
    }

    while (XML::Parser::elementExists(source, TRKSEGSTRING)) 
    {
        trackPoint = XML::Parser::getAndEraseElement(source, TRKSEGSTRING);
        std::string trkseg = XML::Parser::getElementContent(trackPoint);
        XML::Parser::getAndEraseElement(trkseg, NAMESTRING);
        mergedTrkSegs += trkseg;                                             // finds all the of 'trkseg' strings
    }

    if (! mergedTrkSegs.empty()) source = mergedTrkSegs;    // inserts the 'trkseg' strings into the stream

    currentTime =  startTime =  stringToTime(checkAndGetElementContent(trackPoint,TIMESTRING));   // sets currenttTime and startTime

    while (XML::Parser::elementExists(source, TRKPTSTRING)) // continues to loop is there is a 'trkpt' inside of source
    {
        trackPoint = XML::Parser::getAndEraseElement(source, TRKPTSTRING);  // sets trackpoint to the 'trkpt'

        std::string lat = checkAndGetElementAttribute(trackPoint, LATSTRING);   // sets lat to the 'lat'
        std::string lon = checkAndGetElementAttribute(trackPoint, LONSTRING);   // sets lon to the 'lon'
        
        trackPoint = XML::Parser::getElementContent(trackPoint);    // sets trackpoint to all of the current content. Takes over source for current content

        std::string ele;    // creates the elevation string to 

        if (XML::Parser::elementExists(trackPoint, ELESTRING)) { ele = checkAndGetElementContent(trackPoint, ELESTRING); }
        else { ele = "0"; } // if there is no elevation found then it defaults to 0

        currentTime = stringToTime(checkAndGetElementContent(trackPoint,TIMESTRING));
        
        Position CurrentPos = Position(lat, lon, ele);

        if (!positions.empty() && areSameLocation(CurrentPos, positions.back())) // if there are no positions and the positions are in the same location 
        { 
            stringStream << "Position ignored: " << CurrentPos.toString() << std::endl; // it ignores the position
            departed.back() = currentTime - startTime; // sets the departed time for the position
        }
        else
        {
            positions.push_back(CurrentPos); 

            if (XML::Parser::elementExists(trackPoint, NAMESTRING)) { trackPoint = checkAndGetElementContent(trackPoint, NAMESTRING); }
            positionNames.push_back(trackPoint);

            stringStream << "Position added: " << CurrentPos.toString() << std::endl;

            timeElapsed = currentTime - startTime;
            arrived.push_back(timeElapsed), departed.push_back(timeElapsed);

            stringStream << " at time: " << std::to_string(timeElapsed) << std::endl; 
        }
    }

    stringStream << positions.size() << " positions added." << std::endl;   // adds the positions to the stream using the size of the vector as the number of positions
    
    ///////////////////////////////////////////////////
    // Setting variable parameters ready for looping //
    ///////////////////////////////////////////////////
    
    routeLength = 0;
    metres deltaH = 0, deltaV = 0;
    

    for (unsigned int i = 0; i < positions.size() -1; ++i)      // using the positions created throughout a route is created.
    {
        deltaH = Position::distanceBetween(positions[i], positions[i + 1]);
        deltaV = positions[i + 1].elevation() - positions[i].elevation();
        routeLength += sqrt(pow(deltaH, 2) + pow(deltaV, 2));
    }
    report = stringStream.str();    // switches the current string stream into a string to create the report
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
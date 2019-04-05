#include <algorithm>
#include <stdexcept>
#include <cctype>

#include "xmlgenerator.h"
#include "gridworld_route.h"

using namespace GPS;

GridWorldRoute::GridWorldRoute(std::string routeStr, GridWorld gridworld)
  : routeString{routeStr},
    gridworld{gridworld}
{
    if (! isValidRouteString(routeStr))
        throw std::invalid_argument("Invalid point sequence, cannot construct Route.");
}

std::string GridWorldRoute::toGPX(bool embedName, const std::string& routeName) const
{
    XML::Generator gpx;

    gpx.basicXMLDeclaration();
    gpx.openBasicGPXElement();

    gpx.openElement("rte","");
    if (embedName)
    {
        std::string name = routeName.empty() ? routeString : routeName;
        gpx.element("name","",name);
    }

    const bool includeElevation = false; // For Position interface
    for (GridWorld::Point point : routeString)
    {
        const Position& pos = gridworld[point];
        gpx.openElement("rtept", pos.toString(includeElevation));
        gpx.element("name","",std::string(1,point));
        gpx.element("ele", "",std::to_string(pos.elevation()));
        gpx.closeElement(); // "rtept"
    }

    return gpx.closeAllElementsAndExtractString();
}

std::string GridWorldRoute::toString() const
{
    return routeString;
}

bool GridWorldRoute::isValidRouteString(const std::string & routeStr)
{
    // To be valid, all chars must be in the range 'A'..'Y'.
    return std::all_of(routeStr.begin(), routeStr.end(),
                       [] (char point)->bool {return point >= 'A' && point <= 'Y';});
}

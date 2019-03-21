#include "xmlgenerator.h"
#include <iostream>
#include <fstream>

using namespace XML;

int main()
{
    std::ofstream xmlFile("../logs/xx.gpx");

    Generator xmlGen;

    xmlGen.basicXMLDeclaration();
    xmlGen.openBasicGPXElement();
    xmlGen.openElement("rte", "");

    xmlGen.element("name", "", "route_name");

    xmlGen.openElement("rtept" ,"lat=\"123\" lon=\"456\"");

    xmlGen.element("name", "", "point_name");
    xmlGen.element("ele", "", "1000");

    xmlGen.closeElement();

    xmlGen.openElement("rtept" ,"lat=\"123\" lon=\"456\"");

    xmlGen.element("name", "", "point_name");
    xmlGen.element("ele", "", "1000");

    xmlGen.closeElement();

    xmlGen.openElement("rtept" ,"lat=\"123\" lon=\"456\"");

    xmlGen.element("name", "", "point_name");
    xmlGen.element("ele", "", "1000");

    xmlGen.closeElement();

    xmlFile << xmlGen.closeAllElementsAndExtractString();

    

}

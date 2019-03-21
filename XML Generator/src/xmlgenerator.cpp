#include <stdexcept>
#include <iostream>

#include "xmlgenerator.h"

namespace XML
{
  Generator::Generator(unsigned int indentationSpaces) : indentationSpaces{indentationSpaces} {}

  void Generator::basicXMLDeclaration()
  {
      xml << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" standalone=\"yes\"?>";
      newline();
  }

  void Generator::openBasicGPXElement()
  {
      std::string gpxAttributes = "version=\"1.1\" creator=\"NTU\" xmlns=\"http://www.topografix.com/GPX/1/1\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\"";
      openElement("gpx",gpxAttributes);
  }

  void Generator::element(const std::string& name, const std::string& attributes, const std::string& content)
  {
      indent();
      openingTag(name,attributes);
      xml << content;
      closingTag(name);
      newline();
  }

  void Generator::openElement(const std::string& name, const std::string& attributes)
  {
      indent();
      openingTag(name,attributes);
      unclosedTags.push(name);
      ++indentationLevel;
      newline();
  }

  void Generator::closeElement()
  {
      if (unclosedTags.empty()) throw std::domain_error("No XML element to close.");
      --indentationLevel;
      indent();
      closingTag(unclosedTags.top());
      unclosedTags.pop();
      newline();
  }

  void Generator::closeAllElements()
  {
      while (! unclosedTags.empty())
      {
          --indentationLevel;
          indent();
          closingTag(unclosedTags.top());
          unclosedTags.pop();
          newline();
      }
  }

  std::string Generator::closeAllElementsAndExtractString()
  {
      closeAllElements();
      return xml.str();
  }

  void Generator::openingTag(const std::string& name, const std::string& attributes)
  {
      xml << '<' << name;
      if (! attributes.empty())
          xml << ' ' << attributes;
      xml << '>';
  }

  void Generator::closingTag(const std::string& name)
  {
      xml << "</" << name << '>';
  }

  void Generator::indent()
  {
      xml << std::string(indentationLevel*indentationSpaces,' ');
  }

  void Generator::newline()
  {
      xml << std::endl;
  }
}

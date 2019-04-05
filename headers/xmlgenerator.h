#ifndef XMLGENERATOR_H_211217
#define XMLGENERATOR_H_211217

#include <sstream>
#include <string>
#include <stack>

namespace XML
{
  class Generator
  {
    public:
      Generator(unsigned int indentationSpaces = 4);

      void basicXMLDeclaration();
      void openBasicGPXElement();

      void element(const std::string& name, const std::string& attributes, const std::string& content);
      void openElement(const std::string& name, const std::string& attributes);
      void closeElement();
      void closeAllElements();

      std::string closeAllElementsAndExtractString();

    private:
      std::ostringstream xml;
      std::stack<std::string> unclosedTags;
      unsigned int indentationSpaces;
      unsigned int indentationLevel = 0;

      void openingTag(const std::string& name, const std::string& attributes);
      void closingTag(const std::string& name);

      void indent();
      void newline();
  };

}

#endif

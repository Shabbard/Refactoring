#ifndef XMLPARSER_H_211217
#define XMLPARSER_H_211217

#include <string>

namespace XML
{
 namespace Parser
 {

  /* Note: the current implementation is fairly crude.  In particular,
   * it does not handle nested tags of the same name.
   */

  /*  Determine whether an element exists in the source string.
   */
  bool elementExists(const std::string & source, const std::string & elementName);


  /*  Locate and return the named element (including opening/closing tags).
   *  Pre-condition: the element exists somewhere within the source string.
   */
  std::string getElement(const std::string & source, const std::string & elementName);


  /*  Locate and return the named element (including opening/closing tags).
   *  Then erase that element from teh source string.
   *  Pre-condition: the element exists somewhere within the source string.
   */
  std::string getAndEraseElement(std::string & source, const std::string & elementName);


  /*  Return the content (everything between the opening/closing tags)
   *  of an XML element.
   *  Pre-condition: the argument is a valid XML element.
   */
  std::string getElementContent(const std::string & element);

  /*  Determine whether an attribute exists in an element.
   *  Pre-condition: the argument is a valid XML element.
   */
  bool attributeExists(const std::string & element, const std::string & attributeName);

  /*  Return the value of an attribute, or an empty string if the attribute
   *  cannot be found.
   *  Pre-condition: the argument is a valid XML element.
   */
  std::string getElementAttribute(const std::string & element, const std::string & attributeName);

 }
}

#endif

#include "XMLHelpers.h"

using namespace xercesc;
using namespace std;
int getIntNodeValue(DOMNode *node)
{
	char *p = XMLString::transcode(node->getNodeValue());
    int i = atoi(p);
    XMLString::release(&p);
    return i;
}
float getFloatNodeValue(DOMNode *node)
{
	char* fl = XMLString::transcode(node->getNodeValue());
	float i = atof(fl);
	XMLString::release(&fl);
	return i;
}
std::string getStringNodeValue(DOMNode *node, bool text)
{
	
	const XMLCh *str;
    DOMNode::NodeType type = node->getNodeType();
    if (text && (type == DOMNode::TEXT_NODE)) {
        str = ((DOMText *)node)->getWholeText();
    } else {
        str = node->getNodeValue();
    }
    char *p = XMLString::transcode(str);
    if (p == NULL)
        return string();
    string s = p;
    XMLString::release(&p);
    return s;
}
std::string getTextFromElement(DOMElement *element, bool text)
{
	DOMNodeList *list = element->getChildNodes();
    if (list->getLength() > 0) {
        DOMNode *item = list->item(0);
        return getStringNodeValue(item, text);
    }
    return string();
}

std::string getElementText(DOMElement *node, const string element, bool text) {
    const int len = element.length();
    XMLCh* tempStr = new XMLCh[len + 1];
    XMLString::transcode(element.c_str(), tempStr, len);
    DOMNodeList *list = node->getElementsByTagName(tempStr);
	delete[] tempStr;
	tempStr = NULL;
    if (list->getLength() != 0) {
        DOMElement *item = (DOMElement *)list->item(0);
        return getTextFromElement(item, text);
    }
    return string();
}

bool hasChildElement(DOMElement *node, const string child) {
    const int len = child.length();
    //XMLCh tempStr[len + 1];
	XMLCh* tempStr = new XMLCh[len + 1];
    XMLString::transcode(child.c_str(), tempStr, len);
    DOMNodeList *list = node->getElementsByTagName(tempStr);
	delete[] tempStr;
	tempStr = NULL;
    return (list->getLength() != 0);
}
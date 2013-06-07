#pragma once
#ifndef _XMLHELPERS_H_
#define _XMLHELPERS_H_
#include <string>
#include <xercesc\parsers\XercesDOMParser.hpp>
#include <xercesc\dom\DOM.hpp>
#include <xercesc\sax\HandlerBase.hpp>
#include <xercesc\util\XMLString.hpp>
#include <xercesc\util\PlatformUtils.hpp>

	float getFloatNodeValue(xercesc::DOMNode *node);
	int getIntNodeValue(xercesc::DOMNode *node);
	std::string getStringNodeValue(xercesc::DOMNode *node, bool text = false);
	std::string getTextFromElement(xercesc::DOMElement *element, bool text = false);
	std::string getElementText(xercesc::DOMElement *node, const std::string element, bool text = false);
	bool hasChildElement(xercesc::DOMElement *node, const std::string child);

#endif
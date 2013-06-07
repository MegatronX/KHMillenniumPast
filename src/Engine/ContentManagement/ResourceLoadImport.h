#pragma once
#ifndef _RESOURCE_LOAD_IMPORT_H_
#define _RESOURCE_LOAD_IMPORT_H_

#include <IO/xml/pugixml.hpp>
#include <string>
#include <contentmanagement/ContentManager.h>
class Engine;

namespace Content
{
	class ResourceLoadImport
	{
	public:
		static void ProcessImports(const std::string& file, ContentManager& manager);
	};
}

#endif
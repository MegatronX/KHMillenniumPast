#pragma once
#ifndef _KVREADER_H_
#define _KVREADER_H_
#include <boost/unordered_map.hpp>
#include <string>
#include <vector>
#include <IO\xml\pugixml.hpp>
#include <iostream>
#include <boost/assign.hpp>
const std::vector<std::string> settingValues = boost::assign::list_of(std::string("configuration"))
	(std::string("settings"))
	(std::string("Settings"))
	(std::string("Configuration"))
	(std::string("pagesettings"));

boost::unordered_map<std::string, std::string> MakeKVMap(const std::string& file, const std::string& settingsParent = "")
{
	boost::unordered_map<std::string, std::string> kvSet;

	using namespace std;
	using namespace pugi;
	xml_document doc;
	xml_parse_result result = doc.load_file(file.c_str());
	if (!result)
		cerr << "Configuration Failed To Load. Error: " << result.description() << endl;
	else
	{
		xml_node parent;
		xml_node configRoot;
		
		if (settingsParent != "")
		{
			parent = doc.child(settingsParent.c_str());
			configRoot = parent.child(settingValues[0].c_str());
		}
		else
		{
			parent = doc;
			doc.child(settingValues[0].c_str());
		}
		
		for (auto it = settingValues.begin(); it != settingValues.end() && configRoot.empty(); ++it)
			configRoot = parent.child((*it).c_str());
		if (!configRoot.empty())
		{
			for (xml_node setting = configRoot.child("add"); setting; setting = setting.next_sibling("add"))
			{
				kvSet[setting.attribute("key").value()] = setting.attribute("value").value(); 
			}
		}
	}
	return kvSet;
}

#endif
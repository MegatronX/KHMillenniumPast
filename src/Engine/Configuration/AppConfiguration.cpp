#include "AppConfiguration.h"
#include <iostream>
using namespace Configuration;

AppConfiguration::AppConfiguration()
{
	InputsSet = false;
}
AppConfiguration::AppConfiguration(const std::string &configFile)
{
	using namespace std;
	using namespace pugi;
	InputsSet = false;
	xml_document doc;
	xml_parse_result result = doc.load_file(configFile.c_str());
	if (!result)
		std::cerr << "Configuration Failed To Load. Error: " << result.description();
	else
	{
		xml_node configRoot = doc.child("configuration");
		xml_node settings = configRoot.child("appSettings");
		for (xml_node setting = settings.child("add"); setting; setting = setting.next_sibling("add"))
		{
			std::string key, value;
			key = setting.attribute("key").value();
			value = setting.attribute("value").value();
			ApplicationSettings[key] = value; 
			//ConfigMappings.[key] = value;
		}
		
	}
}
void AppConfiguration::Initialize(const std::string &configFile)
{
	using namespace std;
	using namespace pugi;
	xml_document doc;
	InputsSet = false;
	if (doc.load_file(configFile.c_str()))
	{
		xml_node configRoot = doc.child("configuration");
		xml_node settings = configRoot.child("appSettings");
		for (xml_node setting = settings.child("add"); setting; setting = setting.next_sibling("add"))
		{
			std::string key, value;
			key = setting.attribute("key").value();
			value = setting.attribute("value").value();
			ApplicationSettings[key] = value;
			//ConfigMappings.[key] = value;
		}
	}
}
void AppConfiguration::WriteConfiguration(std::ostream& outstream)
{

}
void AppConfiguration::WriteConfiguration(std::string& file, bool MakeFileIfNotAvailable)
{

}
void AppConfiguration::SetApplicationSetting(const std::string& key, const std::string& value)
{
	ApplicationSettings[key] = value;
}
const std::string& AppConfiguration::GetApplicationSetting(const std::string &lookup)
{
	return ApplicationSettings[lookup];
}
const std::string& AppConfiguration::GetApplicationSetting(const char* lookup)
{
	return GetApplicationSetting(std::string(lookup));
}

const std::string AppConfiguration::GetApplicationSettingByVal(const std::string &lookup)
{
	return ApplicationSettings[lookup];
}
const std::string AppConfiguration::GetApplicationSettingByVal(const char* lookup)
{
	return GetApplicationSetting(std::string(lookup));
}

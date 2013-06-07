#pragma once
#ifndef _PYTHONSCRIPTER_H_
#define _PYTHONSCRIPTER_H_

#include <string>
#include <boost/python.hpp>
#include <boost/unordered_map.hpp>

namespace Scripting
{
	class PythonScripter
	{
	public:
		PythonScripter(const std::string& ScriptPath = "");

		template < class T >
		void AddScriptObject(const std::string &indexer, T& addobject, boost::python::object &module)
		{
			boost::python::scope(module).attr(indexer.c_str()) = boost::python::ptr(&addobject);
		}
		void RunString(const std::string &scriptString);
		/*boost::python::object RunString(const std::string &scriptString);
		template <class T> 
		T RunString(const std::string& scriptString)
		{
			auto res = RunString(scriptString);
			return boost::python::extract<T>(res);
		}*/
		boost::python::object RunFunction(const std::string& funcName);
		boost::python::object RunFunction(const std::string& funcName, boost::python::object& pythonnamespace);

		template <class T>
		T RunFunction(const std::string& file)
		{
			auto res = RunFunction(file, MainNamespace);
			return boost::python::extract<T>(res);
		}

		template <class T>
		T RunFunction(const std::string& file, boost::python::object& pythonnamespace)
		{
			auto res = RunFunction(file, pythonnamespace);
			return boost::python::extract<T>(res);
		}

		boost::python::object RunFile(const std::string &file, bool useStoredPath = true);
		boost::python::object RunFile(const std::string &file, boost::python::object& pythonnamespace, bool useStoredPath = true);

		template <class T>
		T RunFile(const std::string& file, bool useStoredPath = true)
		{
			auto res = RunFile(file, useStoredPath);
			return boost::python::extract<T>(res);
		}
		template <class T>
		T RunFile(const std::string& file, boost::python::object& pythonnamespace, bool useStoredPath = true)
		{
			auto res = RunFile(file, pythonnamespace, useStoredPath);
			return boost::python::extract<T>(res);
		}
		boost::python::object& GetMainModule();
		boost::python::object& GetSFMLModule();
		boost::python::object& GetEngineModule();
		boost::python::object& GetLibRocketModule();
		boost::python::object& GetRocketModule();
		boost::python::object& GetGraphicsModule();
		boost::python::object& GetStatusEffectsModule();
		boost::python::object& GetMappingModule();
		boost::python::object& GetModule(const std::string& name);
		void AddModule(const std::string& name, boost::python::object& module);

		~PythonScripter();
	protected:
		void SetPath(const std::string &val);
		friend class Engine;
	private:
		std::string ScriptPath;
		boost::python::object MainNamespace;
		boost::python::object MainModule;
		boost::python::object EngineModule;
		boost::python::object SFMLModule;
		boost::python::object LibRocketModule;
		boost::python::object RocketModule;
		boost::python::object GraphicsModule;
		boost::python::object ScreensModule;
		boost::python::object StatusEffectsModule;
		boost::python::object MappingModule;
		boost::python::object GameMappingModule;
		boost::unordered_map<std::string, boost::python::object> AdditionalModules;
	};
}
#endif
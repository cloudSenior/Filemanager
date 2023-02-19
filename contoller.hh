#pragma once
#include <filesystem>
#include <fstream>

#include "file.hh"

#include "string.hh"
#include "typedefs.hh"



class FAController {
public:
	FAModule ReadModule(std::string fullPath) {
		FAModule Module;
		for (auto iterator : readFileOfCommands(fullPath)) {
			if (iterator.name == "format") 
			{ 
				Module.formats = iterator.arguments; 
			}
			if (iterator.name == "where") 
			{ 
				Module.where = iterator.arguments[NULL]; 
			}
		}
		return Module;
	}


	std::string getModulePath() {
		std::string where;

		if (!std::filesystem::exists(_DIRECT_CONFIG))
			std::filesystem::create_directory(_DIRECT_CONFIG);

		if (!std::filesystem::exists(_FULLPATH_CONFIGFILE))
			std::ofstream(_FULLPATH_CONFIGFILE) << "#modules: <ROOT>\n" << "#rootfilter: ";

		for (auto iterator : readFileOfCommands(_FULLPATH_CONFIGFILE)) {
			if (iterator.name == "modules") {
				if (iterator.arguments[NULL] == "<ROOT>")
				{
					if (!std::filesystem::exists(_ROOT_DIRECT)) std::filesystem::create_directory(_ROOT_DIRECT);
					where = _ROOT_DIRECT;
				}
				else
				{
					where = iterator.arguments[NULL];
				}
			}
		}

		return where;
	}

	bool UpdatedRootFilter()
	{
		for (auto iterator : readFileOfCommands(_FULLPATH_CONFIGFILE)) {
			if (iterator.name == "update-root") {
				if (iterator.arguments[NULL] == "true")
					return true;
				return false;
			}
		}

	}


	std::string RootFilterPath()
	{
		std::string where;
		for (auto iterator : readFileOfCommands(_FULLPATH_CONFIGFILE)) {
			if (iterator.name == "rootfilter") {
				if (iterator.arguments.size() == 0)
				{
					where = "";
					break;
				}
				where = iterator.arguments[NULL];
				if (iterator.arguments[NULL] == "<ROOT>")
				{
					if (!std::filesystem::exists(_ROOT_DIRECT)) std::filesystem::create_directory(_ROOT_DIRECT);
					where = _ROOT_DIRECT;
				}
				
			}
		}
		return where;
	}


	std::vector<std::string> getListFilesOfDirect(std::string direct) {
		std::vector<std::string> list;
		for (auto item : std::filesystem::recursive_directory_iterator(direct))
		{
			if (item.path().string().find('.') != std::string::npos)
			{
				list.push_back(item.path().string());
			}
		}
		return list;
	};

	void uploadedData() {
		std::string Config = getModulePath();
		std::vector<std::string> Modules = getListFilesOfDirect(Config);
		
		if (Config == "" || Modules.size() == 0) std::cout << "Перезапустити программу | Зайдите в конфигурацию и поставьте директорию в #rootfilter: " << std::endl;

		for (auto x : Modules) {
			auto m = ReadModule(x);

			for (auto format : m.formats)
			{
				data.emplace(format, m.where);
			}
		}
	}

	std::map<std::string, std::string> data;
};



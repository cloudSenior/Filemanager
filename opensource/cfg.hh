#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <lmcons.h>
#include <Windows.h>

#include "string.hh"
#include "file.hh"



// CONFIG FUNCTION

std::string qweweq()
{
	std::vector<commandFA> Varg;
	std::string where;

	if (!std::filesystem::exists(_DIRECT_CONFIG))
		std::filesystem::create_directory(_DIRECT_CONFIG);
	
	if (!std::filesystem::exists(_FULLPATH_CONFIGFILE))
		std::ofstream(_FULLPATH_CONFIGFILE) << "#modules: <ROOT>";

	for (auto iterator: readFileOfCommands(_FULLPATH_CONFIGFILE)) {
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
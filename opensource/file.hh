#pragma once
#include <fstream>
#include <Windows.h>

#include <vector>
#include <string>

#include "typedefs.hh"
#include "string.hh"


std::string getUserName();

const std::string _DIRECT_CONFIG = { "C:/Users/" + getUserName() + "/Documents/FAConfig" };
const std::string _FULLPATH_CONFIGFILE = { _DIRECT_CONFIG + "/config.cfg" };
const std::string _ROOT_DIRECT = { _DIRECT_CONFIG + "/modules" };


std::string getUserName() {
	char name[128];
	DWORD size = 128;
	if (GetUserNameA(name, &size)) return std::string(name);
	DWORD error = GetLastError();
	if (error != ERROR_INSUFFICIENT_BUFFER) throw error;
	std::string result(size, '\0');
	if (GetUserNameA(result.data(), &size))  return result;
	throw GetLastError();
}

std::vector<FACommand> readFileOfCommands(std::string path)
{
	std::ifstream read(path);
	std::string line;
	std::vector<FACommand> listcommand;

	while (std::getline(read, line, '\n'))
	{
		switch (line[NULL])
		{
		case _CONFIG_START_PREFIX:
			std::string acc;
			FACommand request;

			for (int i = 1; i < line.size(); ++i) {
				request.name += line[i];
				if (line[i + 1] == _CONFIG_END_PREFIX) break;
			}

			for (int i = request.name.length() + 3; i < line.size(); ++i) {
				acc += line[i];
				if (line[i + 1] == '\n') break;
			}

			request.arguments = split(acc, ' ');
			listcommand.push_back(request);
			break;
		}
	}
	read.close();
	return listcommand;
}

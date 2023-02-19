#pragma once
#include <fstream>
#include <Windows.h>

#include <vector>
#include <string>

#include "typedefs.hh"
#include "string.hh"
#include <windows.h>
#include <iostream>
#include <shlobj.h>
#pragma comment(lib, "shell32.lib")


std::string getDocumentPositionDirect()
{
	char my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
	if (result != S_OK)
		return "NONE";
	else
		return my_documents;
}

const std::string _DIRECT_CONFIG = { getDocumentPositionDirect() + "/FAConfig"};
const std::string _FULLPATH_CONFIGFILE = { _DIRECT_CONFIG + "/config.cfg" };
const std::string _ROOT_DIRECT = { _DIRECT_CONFIG + "/modules" };



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

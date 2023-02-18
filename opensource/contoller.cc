#include "contoller.hh"
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct moduleFA
{
	std::vector<std::string> formats;
	std::string where;
};

std::vector<std::string> split(const std::string& s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}



moduleFA Controller::ModuleRead(std::string fullpath)
{
	std::ifstream fileContent(fullpath);
	std::string line;

	moduleFA request;

	while (std::getline(fileContent, line, '\n'))
	{
		std::string acc, accumulator;
		switch (line[0]) {
		case '#':
			for (int i = 1; i < line.length(); ++i) {
				accumulator += line[i];
				if (line[i + 1] == ':') break;
			}

			if (accumulator == "format") {
				for (int i = accumulator.length() + 4; i < line.size(); ++i)
				{
					acc += line[i];
				}

				request.formats = split(acc, ' ');
			}

			if (accumulator == "where") {
				for (int i = accumulator.length() + 3; i < line.length(); ++i)
				{
					acc += line[i];
				}

				request.where = acc;
			}
			break;
		default:
			continue;
			break;
		}
	}
	return moduleFA{};
}

std::vector<std::string> Controller::getListFilesOfDirect(std::string direct, std::string format)
{
	std::vector<std::string> list;
	for (auto item: std::filesystem::recursive_directory_iterator(direct))
	{
		if (split(item.path().string(), '.')[1] != " ")
		{
			list.push_back(item.path().string());
		}
	}

	return list;
}
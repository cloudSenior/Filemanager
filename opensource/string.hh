#pragma once

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> split(const std::string& s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::string& subES(std::string self, char start, char end)
{
	std::string acc{"0"};
	for (int i = 0; i < self.length(); ++i)
	{
		if (self[i] != start) continue;
		if (self[i] == start)
		{
			acc += self[i];
			if (self[i + 1] == end) break;
		}
	}

	return acc;
}
std::string& subES(std::string self, char end)
{
	std::string acc{ "0" };
	for (int i = 0; i < self.length(); ++i)
	{
		acc += self[i];
		if (self[i + 1] == end) break;
	}

	return acc;
}
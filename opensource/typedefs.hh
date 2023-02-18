#pragma once
#define FILE_NOT_SEARCHED "$NOTFOUNDED$"

const char _CONFIG_START_PREFIX = '#';
const char _CONFIG_END_PREFIX = ':';

struct FAModule
{
	std::vector<std::string> formats;
	std::string where;
};

struct FACommand
{
	std::string name;
	std::vector<std::string> arguments;
};

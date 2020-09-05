#pragma once
#include <string>


class FileSystem
{
	static const char bad_separators[];
	static const char separator;
	static std::string data_directory;

public:
	static std::string fullPath(const std::string&);
	static void init(const char*);
};

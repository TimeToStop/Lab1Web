#include "filesystem.h"

#if defined(_WIN32) || defined(_WIN64)
	const char FileSystem::separator = '\\';
#elif defined(unix)
	const char FileSystem::separator = '/';
#else
	#error Unsupported OS type
	#error To fix add OS system separator
#endif

const char FileSystem::bad_separators[] = {'\\', '/'};
std::string FileSystem::data_directory = "";

std::string FileSystem::fullPath(const std::string& rel)
{
	std::string r = data_directory + rel;
	
	for (std::string::iterator it = r.begin(); it != r.end(); ++it)
	{
		for (size_t i = 0; i < sizeof(bad_separators); i++)
		{
			if (*it == bad_separators[i])
			{
				*it = separator;
				break;
			}
		}
	}

	return r;
}

void FileSystem::init(const char* str)
{
	data_directory = str;

	if (data_directory[data_directory.size() - 1] != separator)
	{
		data_directory.push_back(separator);
	}
}

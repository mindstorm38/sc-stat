#ifndef FILE_UTIL_H_
#define FILE_UTIL_H_

#include "global_types.h"

namespace scs {

	#if defined( _WIN32 ) || defined( WIN32 )
		const char DIR_SEP = '\\';
	#else 
		const char DIR_SEP = '/';
	#endif
		
	void read_directory(const std::string& path, pathlist& list);
	bool is_directory(const std::string& path);
	std::string get_file_name(const std::string& path);
	std::string get_file_ext(const std::string& path);
	
}

#endif

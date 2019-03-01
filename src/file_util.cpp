#include <dirent.h>
#include <sys/stat.h>
#include <sstream>
#include "file_util.h"

using std::string;
using std::stringstream;

namespace scs {

	void read_directory(const string& path, pathlist& list) {
		
		DIR* dirp = opendir( path.c_str() );
		dirent* dp;
		
		while ( ( dp = readdir( dirp ) ) != NULL ) {
			if ( strcmp( dp->d_name, "." ) != 0 && strcmp( dp->d_name, ".." ) != 0 ) {
				stringstream ss;
				ss << path << DIR_SEP << dp->d_name;
				list.push_back( ss.str() );
			}
		}
		
		closedir( dirp );
		
	}
	
	bool is_directory(const string& path) {
		
		struct stat ds;
		return stat( path.c_str(), &ds ) == 0 && S_ISDIR( ds.st_mode);
		
	}
	
	string get_file_name(const string& path) {
		size_t i = path.rfind( DIR_SEP, path.length() );
		return i == string::npos ? "" : path.substr( i + 1, path.length() - 1 );
	}
	
	string get_file_ext(const string& path) {
		size_t i = path.find_last_of('.');
		size_t ii = path.find_last_of( DIR_SEP );
		return i == string::npos || ii > i ? "" : path.substr( i + 1 );
	}

}

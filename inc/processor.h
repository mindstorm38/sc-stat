#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "file_stat.h"
#include "file_util.h"
#include "global_types.h"

namespace scs {

	void start(const std::string& initial_dir);
	void process_file(const std::string& path);
	void process_directory(const std::string& path);
	fextension get_file_extension(const std::string& ext);
	
}

#endif

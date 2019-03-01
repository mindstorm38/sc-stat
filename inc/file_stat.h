#ifndef FILE_STAT_H_
#define FILE_STAT_H_

#include "global_types.h"

namespace scs {

	extern const strlist TEXT_EXTENSIONS;
	extern const charlist EMPTY_CHARS;
	
	const char NEW_LINE_CHAR = '\n';
	
	bool valid_text_extension(std::string& ext);
	bool is_empty_char(char& ch);
	
	class fstat {
		
		public:
		
		fstat(std::string path);
		~fstat();
		
		std::string path;
		
		std::string name;
		std::string extension;
		bool valid_text_ext;
		
		uint32_t byte_count;
		
		uint32_t char_count;
		uint32_t ne_char_count;	// Not Empty char count
		
		uint32_t line_count;
		uint32_t ne_line_count;
		
	};
	
	class fextension {
		
		public:
		
		fextension(std::string ext);
		~fextension();
		
		std::string ext;
		bool valid_text_ext;
		
		std::vector<fstat> files;
		
		uint32_t file_count;
		float file_count_r;
		
		uint32_t byte_count;
		float byte_count_r;
		
		uint32_t char_count;
		float char_count_r;
		
		uint32_t ne_char_count;
		float ne_char_count_r;			// Ratio of Non-Empty char count compared to global stats Non-Empty char count
		float ne_char_count_r_inext;	// Ratio of Non-Empty char count compared to this extension char count
		
		uint32_t line_count;
		float line_count_r;
		
		uint32_t ne_line_count;
		float ne_line_count_r;
		float ne_line_count_r_inex;
		
	};
	
	class globalstat {
		
		public:
		
		globalstat();
		~globalstat();
		
		uint32_t file_count;
		std::vector<fstat> files;
		std::vector<fextension> extensions;
		
		uint32_t byte_count;
		
		uint32_t char_count;
		uint32_t ne_char_count;	// NE = Not Empty
		float ne_char_count_r;
		
		uint32_t line_count;
		uint32_t ne_line_count;
		float ne_line_count_r;
		
		fextension* get_extension(const std::string& ext);
		void add_file_stat(fstat& file);
		void compute_ratios();
		
	};
	
}

#endif

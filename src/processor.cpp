#include <fstream>
#include <chrono>
#include <algorithm>
#include "processor.h"

using std::ifstream;
using std::vector;
using std::chrono::system_clock;
using std::chrono::duration;
using std::sort;

namespace scs {

	globalstat* global;
	
	bool extension_compare_file_count(fextension& ext1, fextension& ext2) {
		return ext1.file_count > ext2.file_count;
	}
	
	bool extension_compare_byte_count(fextension& ext1, fextension& ext2) {
		return ext1.byte_count > ext2.byte_count;
	}
	
	void start(const std::string& initial_dir) {
		
		if ( !is_directory( initial_dir ) ) {
			
			printf( "Invalid initial directory '%s'\n", initial_dir.c_str() );
			return;
			
		}
		
		global = new globalstat();
		
		// Time calculation
		system_clock::time_point start = system_clock::now();
		
		// Start processing of initial directory
		process_directory( initial_dir );
		
		printf("Computing ratios ...\n");
		global->compute_ratios();
		
		// Time calculation
		system_clock::time_point end = system_clock::now();
		duration<double> total_time = end - start;
		
		printf( "Ratios computed\n" );
		printf( "Finished in %fs\n", total_time.count() );
		printf( "File count : %d\n", global->file_count );
		printf( "Extensions :\n" );
		
		sort( global->extensions.begin(), global->extensions.end(), extension_compare_file_count );
		
		for ( size_t i = 0; i < global->extensions.size(); i++ ) {
			
			fextension* ext = &global->extensions[ i ];
			
			printf( "  - %s\n", ext->ext.c_str() );
			printf( "     File count : %d (%.2f%% of all files)\n", ext->file_count, ext->file_count_r );
			printf( "     Byte count : %d (%.2f%% of all files)\n", ext->byte_count, ext->byte_count_r );
			printf( "     Char count : %d (%.2f%% of all files)\n", ext->char_count, ext->char_count_r );
			
			if ( ext->valid_text_ext ) {
				
				printf( "     Not empty char count : %d (%.2f%% of all files) (%.2f%% of extension chars)\n", ext->ne_char_count, ext->ne_char_count_r, ext->ne_char_count_r_inext );
				printf( "     Line count : %d (%.2f%% of all files)\n", ext->line_count, ext->line_count_r );
				printf( "     Not empty line count : %d (%.2f%% of all files) (%.2f%% of extension lines)\n", ext->ne_line_count, ext->ne_line_count_r, ext->ne_line_count_r_inex );
				
			}
			
		}
		
		printf( "Byte count : %d\n", global->byte_count );
		printf( "Char count : %d\n", global->char_count );
		printf( "Not empty char count : %d (%.2f%% of all chars)\n", global->ne_char_count, global->ne_char_count_r );
		printf( "Line count : %d\n", global->line_count );
		printf( "Not empty line count : %d (%.2f%% of all lines)\n", global->ne_line_count, global->ne_line_count_r );
		
		printf( "\n" );
		
		printf( "Top file types :\n" );
		printf( " " );
		
		sort( global->extensions.begin(), global->extensions.end(), extension_compare_byte_count );
		
		for ( size_t i = 0; i < global->extensions.size(); i++ ) {
			
			fextension* ext = &global->extensions[ i ];
			if ( ( i >= 4 && ext->byte_count_r < 1.0 ) || i >= 6 ) break;
			
			if ( i != 0 ) printf(" | ");
			printf( "%s (%.2f%%)", ext->ext.c_str(), ext->byte_count_r );
			
		}
		
		printf( "\n" );
		
		delete global;
		
	}
	
	void process_file(const std::string& path) {
		
		printf( "Processing file '%s'\n", path.c_str() );
		
		ifstream stream( path );
		
		if ( !stream ) {
			
			printf( "Failed to open file '%s'\n", path.c_str() );
			return;
			
		}
		
		fstat stat( path );
		
		char c;
		uint32_t line_char_count = 0;
		bool empty = true;
		
		// Placed here to count binary file as 1 line and for first line of text file
		stat.line_count = 1;
		
		while ( stream.get( c ) ) {
			
			stat.byte_count++;
			
			stat.char_count++;
			
			if ( !is_empty_char( c ) )
				stat.ne_char_count++;
			
			if ( stat.valid_text_ext ) {
				
				if ( c == NEW_LINE_CHAR ) {
					
					stat.line_count++;
					
					if ( !empty )
						stat.ne_line_count++;
					
					empty = true;
					line_char_count = 0;
					
				} else {
					
					line_char_count++;
					
				}
				
				if ( empty && !is_empty_char( c ) ) empty = false;
				
			}
			
		}
		
		stream.close();
		
		// If end of file is not a new line
		if ( stat.valid_text_ext && line_char_count != 0 ) {
			
			if ( !empty )
				stat.ne_line_count++;
			
		}
		
		global->add_file_stat( stat );
		
	}
	
	void process_directory(const std::string& path) {
		
		printf( "Processing directory '%s'\n", path.c_str() );
		
		pathlist paths;
		
		read_directory( path, paths );
		
		for ( size_t i = 0; i < paths.size(); i++ ) {
			
			if ( is_directory( paths[ i ] ) ) {
				
				process_directory( paths[ i ] );
				
			} else {
				
				process_file( paths[ i ] );
				
			}
			
		}
		
	}

}

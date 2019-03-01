#include "file_stat.h"
#include "file_util.h"

using std::string;

namespace scs {

	const strlist TEXT_EXTENSIONS	= { "java", "txt", "json", "js", "py", "lang", "meta", "css", "html", "xml", "vs", "fs", "vsh", "fsh", "h", "hpp", "hxx", "c", "cpp", "cxx", "log", "cmd", "map", "list", "md" };
	const charlist EMPTY_CHARS		= { '\t', '\r', '\n', ' ' };
	
	bool valid_text_extension(string& ext) {
		for ( size_t i = 0; i < TEXT_EXTENSIONS.size(); i++ )
			if ( TEXT_EXTENSIONS[ i ] == ext )
				return true;
		return false;
	}
	
	bool is_empty_char(char& ch) {
		for ( size_t i = 0; i < EMPTY_CHARS.size(); i++ )
			if ( EMPTY_CHARS[ i ] == ch )
				return true;
		return false;
	}
	
	// fextension class
	
	fextension::fextension(string ext) {
		
		this->ext = ext;
		this->valid_text_ext = valid_text_extension( ext );

		this->file_count = 0;
		this->file_count_r = 0.0;
		
		this->byte_count = 0;
		this->byte_count_r = 0.0;
		
		this->char_count = 0;
		this->char_count_r = 0.0;
		
		this->ne_char_count = 0;
		this->ne_char_count_r = 0.0;
		this->ne_char_count_r_inext = 0.0;
		
		this->line_count = 0;
		this->line_count_r = 0.0;
		
		this->ne_line_count = 0;
		this->ne_line_count_r = 0.0;
		this->ne_line_count_r_inex = 0.0;
		
	}
	
	fextension::~fextension() {}
	
	// fstat class
	
	fstat::fstat(string path) {
		
		this->path = path;
		
		this->name = get_file_name( path );
		this->extension = get_file_ext( path );
		this->valid_text_ext = valid_text_extension( this->extension );
		if ( this->extension == "" ) this->extension = "No extension";
		
		this->byte_count = 0;
		
		this->char_count = 0;
		this->ne_char_count = 0;
		
		this->line_count = 0;
		this->ne_line_count = 0;
		
	}
	
	fstat::~fstat() {}
	
	// globalstat class
	
	globalstat::globalstat() {
		
		this->file_count = 0;
		
		this->byte_count = 0;
		
		this->char_count = 0;
		this->ne_char_count = 0;
		this->ne_char_count_r = 0.0;
		
		this->line_count = 0;
		this->ne_line_count = 0;
		this->ne_line_count_r = 0.0;
		
	}
	
	globalstat::~globalstat() {}
	
	fextension* globalstat::get_extension(const std::string& ext) {
		for ( size_t i = 0; i < this->extensions.size(); i++ )
			if ( this->extensions[ i ].ext == ext )
				return &this->extensions[ i ];
		fextension e( ext );
		this->extensions.push_back( e );
		return &this->extensions[ this->extensions.size() - 1 ];
	}
	
	void globalstat::add_file_stat(fstat& file) {
		
		this->file_count++;
		this->files.push_back( file );
		
		fextension* ext = this->get_extension( file.extension );
		
		ext->file_count++;
		ext->files.push_back( file );
		
		ext->byte_count += file.byte_count;
		this->byte_count += file.byte_count;
		
		ext->char_count += file.char_count;
		this->char_count += file.char_count;
		ext->ne_char_count += file.ne_char_count;
		this->ne_char_count += file.ne_char_count;
		
		ext->line_count += file.line_count;
		this->line_count += file.line_count;
		ext->ne_line_count += file.ne_line_count;
		this->ne_line_count += file.ne_line_count;
		
	}
	
	void globalstat::compute_ratios() {
		
		this->ne_char_count_r = (float) this->ne_char_count / (float) this->char_count * 100.0;
		this->ne_line_count_r = (float) this->ne_line_count / (float) this->line_count * 100.0;
		
		for ( size_t i = 0; i < this->extensions.size(); i++ ) {
			
			fextension* ext = &this->extensions[ i ];
			
			ext->file_count_r = (float) ext->file_count / (float) this->file_count * 100.0;
			ext->byte_count_r = (float) ext->byte_count / (float) this->byte_count * 100.0;
			
			ext->char_count_r = (float) ext->char_count / (float) this->char_count * 100.0;
			ext->ne_char_count_r = (float) ext->ne_char_count / (float) this->ne_char_count * 100.0;
			ext->ne_char_count_r_inext = (float) ext->ne_char_count / (float) ext->char_count * 100.0;
			
			ext->line_count_r = (float) ext->line_count / (float) this->line_count * 100.0;
			ext->ne_line_count_r = (float) ext->ne_line_count / (float) this->ne_line_count * 100.0;
			ext->ne_line_count_r_inex = (float) ext->ne_line_count / (float) ext->line_count * 100.0;
			
		}
		
	}
	
}

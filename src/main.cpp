#include "processor.h"

int main(int argc, char** argv) {
	
	if ( argc < 2 ) {
		
		printf("Invalid argument size\n");
		return 1;
		
	}
	
	scs::start( argv[ 1 ] );
	
	return 0;

}

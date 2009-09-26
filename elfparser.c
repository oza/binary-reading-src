#include <stdio.h>		// to use 
#include <stdlib.h>		// to use 
#include <assert.h>
#include <string.h>
#include "elfparser.h"

#define ELF_HEADER_SIZE 4
#define MAX_BUFFER_SIZE 4096
#define MAX_FILENAME_LEN 128

/**
 * This function distinguish a file is elf binary or not.
 * @buf 
 */
bool is_elf(FILE *file)
{
	byte buf[ELF_HEADER_SIZE];

	fread(buf,sizeof(byte),ELF_HEADER_SIZE,file);

	// FIXME: please enter how to decide wheter this file is elf or not.
	if(	buf[0] == '\177' 	&& 
		buf[1] == 'E' 		&& 
		buf[2] == 'L'		&&
		buf[3] == 'F'){
		return true;
	}

	return false;
}

/**
 * This function parse a elf binary and display the 
 * @buf 
 */
bool parse(FILE *file)
{
	
	return false;
}

/**
 * This function execute a elf binary which doesn't have
 * external library. 
 * @buf 
 */
bool execute(byte buf[])
{
	return false;
}

/**
 * Test all function
 * @buf
 */
int main(int argc,char *argv[])
{
	byte buf[MAX_BUFFER_SIZE];
	FILE *file;
	char *filename;

	// check whether the number of argument == 1 or not.
	assert( argc > 1 );

	// 
	filename = argv[1];
	assert( strlen(filename) < MAX_FILENAME_LEN-1 );

	puts(filename);

	// open the file.
	file = fopen(filename,"r");
	assert( file );

	// ok.
	assert( is_elf(file) );

	// ng.
	assert( parse(buf) );

	// ng.
	assert( execute(buf) );

	fclose( file );

	exit(0);
}

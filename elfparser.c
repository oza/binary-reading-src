#include <stdio.h>
#include <stdlib.h>		// to use exit(2)
#include <assert.h>		// to use assert
#include <string.h>
#include "elfparser.h"

#define ELF_HEADER_SIZE 4
#define MAX_BUFFER_SIZE 4096
#define MAX_FILENAME_LEN 128

struct executable_elf{
	addr entry;
};

/**
 * This function distinguish a file is elf binary or not.
 * @file A file descripter to distinguish. 
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
 * This function parse a elf binary and display the infomation.
 * @file A file descriptor to parse. 
 */
bool parse(FILE *file)
{
	unsigned int elf_entry_location;
	addr val;

	// FIXME: please enter where p_entry is.
	elf_entry_location = 0x00000000;
	fseek(file,elf_entry_location,SEEK_SET);

	fread(&val,sizeof(addr),1,file);
		
	return false;
}

/**
 * This function execute a elf binary which doesn't have
 * external library. 
 * @file A file descriptor to execute. 
 * @entry_addr  entry point which you want to execute.
 */
bool execute(byte buf[])
{
	//mmap();
	//asm ("jmp $a",entry_addr);
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
	assert( parse(file) );

	// ng.
	assert( execute(buf) );

	fclose( file );

	exit(0);
}

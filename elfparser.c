#include <stdio.h>
#include <stdlib.h>		// to use exit(2)
#include <assert.h>		// to use assert
#include <string.h>
#include <sys/mman.h>	// to use mprotect(2)

#include <linux/types.h>

#include "elfparser.h"

#define ELF_HEADER_SIZE 4
#define MAX_BUFFER_SIZE 4096
#define MAX_FILENAME_LEN 128

struct elf_info{
	u32 entry;
	u32 p_base;
	u32 s_base;
	u32 p_num;
	u32 s_num;
	u32 symbol_table_base;
};

struct program_info{
	u32 base;
	u32	vaddr;
	u32	offset;
	u32	header_num;
};

struct section_info{
	u32 base;
	u32 name_index;
	u32	vaddr;
	u32	offset;
	u32	header_num;
};


//#define TEST_EXECUTE

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
bool parse_elf_header(FILE *file, struct elf_info *e_info )
{
	// FIXME please specify the offset by reading elf binary.
	u32 entry_offset = 24;
	u32 p_off_offset = 28;
	u32 s_off_offset = 32;
	u16 p_num_offset = 44;
	u16 s_num_offset = 48;

	fseek( file, entry_offset, SEEK_SET );
	fread(&e_info->entry,sizeof(u32),1,file);

	fseek( file, p_off_offset, SEEK_SET );
	fread(&e_info->p_base,sizeof(u32),1,file);

	fseek( file, s_off_offset, SEEK_SET );
	fread(&e_info->s_base,sizeof(u32),1,file);

	fseek( file, p_num_offset, SEEK_SET );
	fread(&e_info->p_num,sizeof(u16),1,file);

	fseek( file, s_num_offset, SEEK_SET );
	fread(&e_info->s_num,sizeof(u16),1,file);

	printf("************************************\n");
	printf("entry          %lx \n",e_info->entry);
	printf("program header base %lu \n",e_info->p_base);
	printf("section header offset %lu \n",e_info->s_base);
	printf("program header num %lu \n",e_info->p_num);
	printf("section header num %lu \n",e_info->s_num);
	printf("************************************\n");

	if ( e_info->entry 
		&& e_info->p_base 
		&& e_info->s_base ){
		return true;
	}
		
	return false;
}

bool parse_program_header(FILE *file, struct program_info *p_info )
{
	int i;
	// FIXME please specify the offset.
	u32 ph_size = 32;
	u32 off_offset = 4 + p_info->base;
	u32 vaddr_offset = 8 + p_info->base;

	printf("************************************\n");
	printf("     vaddr     offset\n");
	for( i = 0 ; i < p_info->header_num ; ++i ){
		fseek( file, vaddr_offset, SEEK_SET );
		fread(&p_info->vaddr,sizeof(u32),1,file);
	
		fseek( file, off_offset, SEEK_SET );
		fread(&p_info->offset,sizeof(u32),1,file);
	
		printf("%10lx %10lx\n",
			p_info->vaddr,
			p_info->offset);

		// update
		vaddr_offset += ph_size;
		//name_index_offset += ph_size;
		off_offset += ph_size;
	}
	printf("************************************\n");

	if ( p_info->vaddr
		//&& p_info->name_index 
		&& p_info->offset ){
		return true;
	}
		
	return false;
}

bool parse_section_header(FILE *file, struct section_info *s_info )
{
	int i;
	// FIXME please specify the offset.
	u32 ph_size = 40;
	u32 name_index_offset = 0 + s_info->base;
	u32 vaddr_offset = 12 + s_info->base;
	u32 off_offset = 16 + s_info->base;

	printf("************************************\n");
	printf("     vaddr     offset\n");
	for( i = 0 ; i < s_info->header_num ; ++i ){
		fseek( file, vaddr_offset, SEEK_SET );
		fread(&s_info->vaddr,sizeof(u32),1,file);
	
		fseek( file, off_offset, SEEK_SET );
		fread(&s_info->offset,sizeof(u32),1,file);
	
		printf("%10lx %10lx\n",
			s_info->vaddr,
			s_info->offset);

		// update
		vaddr_offset += ph_size;
		//name_index_offset += ph_size;
		off_offset += ph_size;
	}
	printf("************************************\n");

	if ( s_info->vaddr
		//&& s_info->name_index 
		&& s_info->offset ){
		return true;
	}
	
	return false;
}

#if 0
struct symbol_info{
	u32 	offset;	/* A location where the symbol is. */
	size_t 	size;		/* A size of the function. */
};
/**
 * This function execute a elf binary which doesn't have
 * external library. 
 * @file A file descriptor to execute. 
 * @info A synbol infomation which you want to execute.
 */
bool execute(FILE *file, struct symbol_info *info)
{
	int ret;
	addr code;

	// copy code from binary to buffer, 
	code = (addr) malloc( info->size * sizeof(byte) );
	
	// FIXME: 
	size = 0;
	offset = 0;
	fseek( file, offset , SEEK_SET );
	fread( (void *)code, sizeof(byte), info->size, file );

	// and change the attribute to execute.
	ret = mprotect( (void *)code, info->size, PROT_READ|PROT_WRITE|PROT_EXEC );
	assert( ret == 0 );
	
	// run on heap region.
	asm (   "jmp   *%0\n\r"   		// jmp to code by absolute jump!
			::"r"    (code)			// bind code to %0
			:"%eax"                 // a register which going to destory its contents.
	);

	return true;
}
#endif

/**
 * Test all function
 * @buf
 */
int main(int argc,char *argv[])
{
	FILE *file;
	char *filename;
	struct elf_info e_info;
	struct program_info p_info;
	struct section_info s_info;

	// check whether the number of argument == 1 or not.
	assert( argc > 1 );

	filename = argv[1];
	assert( strlen(filename) < MAX_FILENAME_LEN-1 );

	puts(filename);

	// open the file.
	file = fopen(filename,"r");
	assert( file );

	// ok.
	assert( is_elf(file) );
	puts("This file is elf.\n");

	parse_elf_header( file, &e_info );

	// ok.
	p_info.base = e_info.p_base;
	p_info.header_num = e_info.p_num;
	parse_program_header( file, &p_info );

	// ng.
	s_info.base = e_info.s_base;
	s_info.header_num = e_info.s_num;
	parse_section_header( file, &s_info );
#if 0
	//execute( file, &info );
#endif

	fclose( file );
	exit(0);
}

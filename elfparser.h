#ifndef __ELF_PARSER_H__
#define __ELF_PARSER_H__

typedef unsigned char byte;
typedef unsigned long addr;

typedef enum {
	false = 0,
	true = 1
}bool;

bool is_elf(byte buf[]);

#endif //__ELF_PARSER_H__

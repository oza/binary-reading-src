#include <stdio.h>
#include "elfparser.h"

#define MAX_BUFFER_SIZE 4096

bool is_elf(byte buf[]){
	return true;
}

int main(int argc,char *argv[])
{
	byte buf[MAX_BUFFER_SIZE];

	if ( is_elf(buf) ){
		puts("This file is elf file!");
	}else {
		puts("This file is not elf file! Stop to parse.");
		exit(1);
	}

	exit(0);
}

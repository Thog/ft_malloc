#include "malloc.h"

int main(int ac , char **av)
{
	void *ptr = malloc(1024);
	ptr = realloc(ptr, 8193);
	show_alloc_mem();	
	free(ptr + 8193 + 100);
	show_alloc_mem();
	return (0);
}
#include "malloc_internal.h"

int main(void)
{
	free(malloc(32));
	show_alloc_mem();
	return (0);
}
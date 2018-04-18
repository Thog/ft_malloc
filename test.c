#include "malloc_internal.h"

int main(int ac , char **av)
{
	void *ptr = malloc(10);
	void *ptr2 = malloc(32);
	void *ptr3 = malloc(SMALL_ZONE);

	//ptr = realloc(ptr, SMALL_ZONE);
	free(ptr);
	free(ptr2);
	free(ptr3);
	return (0);
}
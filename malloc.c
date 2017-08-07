#include "malloc.h"

void	*malloc(size_t size)
{
	void	*ptr;
	ft_putstr("\n\n");
	ft_putstr("MALLOC: 0x");
	ft_putnbrbase(size, "0123456789ABCDEF");
	ft_putstr("\n\nBEFORE\n\n");
	show_alloc_mem();
	if (size <= 0)
		return (NULL);
	else if (size <= TINY_SIZE)
		ptr = alloc_tiny(size);
	else if (size <= SMALL_SIZE)
		ptr = alloc_small(size);
	else
		ptr = alloc_large(size);
	ft_putstr("\n\nAFTER\n\n");
	show_alloc_mem();
	return (ptr);
}

void	free(void *ptr)
{
	ft_putstr("\n\n");
	ft_putstr("FREE: 0x");
	ft_putnbrbase(ptr, "0123456789ABCDEF");
	ft_putstr("\n\n");
	(void)ptr;
}

#include "malloc.h"

static t_block	*block_from_ptr(void *ptr)
{
	t_block	*res;

	res = find_block_for_free(g_env.tiny, ptr);
	if (res)
		return (res);
	res = find_block_for_free(g_env.small, ptr);
	if (res)
		return (res);
	res = find_block_for_free(g_env.large, ptr);
	return (res);
}

void			*malloc(size_t size)
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
	ft_putstr("============================\n\n\n");
	return (ptr);
}

void	free(void *ptr)
{
	t_block	*block;

	block = block_from_ptr(ptr);
	ft_putstr("\n\n");
	ft_putnbrbase(block->size, "0123456789ABCDEF");
	ft_putstr("\n\nBEFORE\n\n");
	show_alloc_mem();
	if (block)
	{
		block->free = 1;
		post_free(block);
	}
	ft_putstr("\n\nAFTER\n\n");
	show_alloc_mem();
	ft_putstr("============================\n\n\n");
}

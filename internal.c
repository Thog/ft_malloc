#include "malloc_internal.h"

t_block			*block_from_ptr(void *ptr)
{
	t_block	*res;

	if (ptr == NULL)
		return (NULL);
	res = find_block_for_free(g_env.tiny, ptr);
	if (res)
		return (res);
	res = find_block_for_free(g_env.small, ptr);
	if (res)
		return (res);
	res = find_block_for_free(g_env.large, ptr);
	return (res);
}

void			*resize_block(t_block *blk, size_t size)
{
	size_t		size_fix;

	if (!blk || !blk->next || !blk->next->free)
		return (NULL);
	size_fix = size - blk->size;
	if (blk->next->size < size_fix)
		return (NULL);
	blk->size = size;
	blk->next->size -= size_fix;
	if (blk->next->size == 0)
		blk->next = blk->next->next;
	return (blk->addr);
}

void				*internal_malloc(size_t size)
{
	void	*ptr;

	ft_putstr("MALLOC 0x");
	ft_putnbrbase((uintmax_t)size, "0123456789abcdef");
	ft_putstr("\n");
	if (size <= 0)
		return (NULL);
	else if (size <= TINY_SIZE)
		ptr = alloc_tiny(size);
	else if (size <= SMALL_SIZE)
		ptr = alloc_small(size);
	else
		ptr = alloc_large(size);
	return (ptr);
}

void				internal_free(void *ptr)
{
	t_block	*block;

	ft_putstr("FREE 0x");
	ft_putnbrbase((uintmax_t)ptr, "0123456789abcdef");
	ft_putstr("\n");
	block = block_from_ptr(ptr);
	block_info(block);
	if (block)
	{
		block->free = 1;
		post_free(block);		
	}
}

void			*internal_realloc(void *ptr, size_t size)
{
	void	*ret;
	t_block	*block;

	ft_putstr("REALLOC 0x");
	ft_putnbrbase((uintmax_t)ptr, "0123456789abcdef");
	ft_putstr(" , 0x");
	ft_putnbrbase(size, BASE_16);
	ft_putstr("\n");
	if (!ptr)
		return (internal_malloc(size));
	block = block_from_ptr(ptr);
	if ((!block || block->free) && ptr)
		return (NULL);
	if (ptr && size == 0) // if size is equal to zero, and ptr is not NULL, then the call is equivalent to free(ptr).
	{
		free(ptr);
		return (NULL); // maybe?
	}
	if (block && block->size < size && block->next && block->next->free &&
			(ret = resize_block(block, size)))
		return (ret);
	if (!(ret = internal_malloc(size)))
		return (NULL);
	if (block)
	{
		ret = ft_memcpy(ret, block->addr, block->size);
		block->free = 1;
		post_free(block);
	}
	return (ret);
}
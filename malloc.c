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

static void		*resize_block(t_block *blk, size_t size)
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

void			*malloc(size_t size)
{
	void	*ptr;
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

void			free(void *ptr)
{
	t_block	*block;

	block = block_from_ptr(ptr);
	if (block)
	{
		block->free = 1;
		post_free(block);
	}
}

void			*realloc(void *ptr, size_t size)
{
	void	*ret;
	t_block	*block;

	// malloc
	if (!ptr)
		return (malloc(size));
	block = block_from_ptr(ptr);

	// not found
	if (!block && ptr)
		return (NULL);
	
	// Minimal sized realloc BSD style
	if (ptr && !size)
		size = block->size;

	// Is the next block enougth?
	if (block && block->size < size && block->next && block->next->free &&
			(ret = resize_block(block, size)))
		return (ret);
	
	// Regular realloc
	if (!(ret = malloc(size)))
		return (NULL);
	if (block)
	{
		ret = ft_memcpy(ret, block->addr, block->size);
		block->free = 1;
		post_free(block);
	}
	return (ret);
}

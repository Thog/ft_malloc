#include "malloc_internal.h"

void				internal_free(void *ptr)
{
	t_block		*block;

	block = get_block(ptr);
	if (block != NULL && block->free == 0)
		mark_block_as_free(block);
}

void				*internal_malloc(size_t size)
{
	t_block	*res;
	if (size <= 0)
		return (NULL);
	res = alloc_block(size);
	if (res != NULL)
	{
		block_check(res);
		return (res->addr);
	}
	return (NULL);
}

void				*internal_realloc(void *ptr, size_t size)
{
	t_block		*block;
	void			*ret;
	size_t			zone_size;
	
	if (ptr == NULL)
	{
		ret = internal_malloc(size);
		return (ret);
	}

	// try to get the block
	block = get_block(ptr);

	// Invalid block???
	if ((block == NULL || block->free == 1) && ptr)
		return (NULL);
	if (ptr && size == 0)
	{
		internal_free(ptr);
		return (NULL);
	}
	// FIXME: UNSURE OF IT
	zone_size = get_zone_size(block->zone_type, block->size) / ALLOC_COUNT;
	if (size <= zone_size)
	{
		mark_block_as_used(block, size);
		block_check(block);
		return (ptr);
	}

	if (!(ret = internal_malloc(size)))
	{
		return (NULL);
	}
	ret = ft_memcpy(ret, block->addr, block->size);
	mark_block_as_free(block);
	block_check(get_block(ret));
	return (ret);
}
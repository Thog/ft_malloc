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
	ft_putstr("malloc failed");
	return (NULL);
}

void				*internal_realloc(void *ptr, size_t size)
{
	t_block		*block;
	void			*ret;
	size_t			zone_size;
	
	ft_putstr("REALLOC 0x");
	ft_putnbrbase((uintmax_t)ptr, "0123456789abcdef");
	ft_putstr(" , 0x");
	ft_putnbrbase(size, BASE_16);
	ft_putstr("\n");
	if (ptr == NULL)
	{
		ft_putstr("REALLOC: ptr is null act like malloc\n");
		ret = internal_malloc(size);
		block_info(get_block(ret));
		if (!ret)
		{
			ft_putstr("REALLOC: malloc failed\n");
		}
		return (ret);
	}

	// try to get the block
	block = get_block(ptr);

	// Invalid block???
	if ((block == NULL || block->free == 1) && ptr)
	{
		ft_putstr("REALLOC: block is invalid\n");
		abort();
		return (NULL);
	}
	if (ptr && size == 0)
	{
		ft_putstr("REALLOC: Free called\n");
		internal_free(ptr);
		return (NULL);
	}
	// FIXME: UNSURE OF IT
	zone_size = get_zone_size(block->zone_type, block->size) / ALLOC_COUNT;
	if (size <= zone_size)
	{
		ft_putstr("Relloc done by size changing\n");
		mark_block_as_used(block, size);
		block_check(block);
		return (ptr);
	}

	if (!(ret = internal_malloc(size)))
	{
		ft_putstr("REALLOC: malloc failed\n");
		return (NULL);
	}
	ret = ft_memcpy(ret, block->addr, block->size);
	mark_block_as_free(block);
	ft_putstr("REALLOC: block data moved\n");	
	block_check(get_block(ret));
	return (ret);
}
#include "malloc.h"

void				*alloc_tiny(size_t size)
{
	t_block	*block;

	if (!(block = find_block(g_env.tiny, size + sizeof(t_block))))
	{
		if (!(block = alloc_block(&g_env.tiny, TINY_ZONE)))
			return (NULL);
		prepare_block(&block, size);
	}
	else
		setup_block(&block, size);
	return (block->addr);
}

void				*alloc_small(size_t size)
{
	t_block	*block;

	if (!(block = find_block(g_env.small, size + sizeof(t_block))))
	{
		if (!(block = alloc_block(&g_env.small, SMALL_ZONE)))
			return (NULL);
		prepare_block(&block, size);
	}
	else
		setup_block(&block, size);
	return (block->addr);
}

void				*alloc_large(size_t size)
{
	t_block	*block;

	if (!(block = find_block(g_env.large, size + sizeof(t_block))))
	{
		if (!(block = alloc_block(&g_env.large, size)))
			return (NULL);
		prepare_block(&block, size);
	}
	else
		setup_block(&block, size);
	return (block->addr);
}

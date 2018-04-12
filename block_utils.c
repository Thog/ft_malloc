#include "malloc_internal.h"

t_block			*get_last_block(t_block *root)
{
	while (root && root->next)
		root = root->next;
	return (root);
}

t_block			*mark_block_as_free(t_block *block)
{
	if (block)
	{
		// Restore original size
		block->size = get_zone_size(block->zone_type, block->size) / ALLOC_COUNT;
		block->free = 1;
	}
	return (block);
}

t_block			*mark_block_as_used(t_block *block, size_t size)
{
	if (block)
	{
		block->size = size;
		block->free = 0;		
	}
	return (block);
}
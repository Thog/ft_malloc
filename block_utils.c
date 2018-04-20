#include "malloc_internal.h"

t_block			*get_last_block(t_block *root)
{
	while (root && root->next)
		root = root->next;
	return (root);
}

t_block			*get_prev_block(t_block *root, t_block *next)
{
	while (root && root->next != next)
		root = root->next;
	return (root);
}

int				can_be_free(t_block *zone, int zone_id)
{
	t_block *tmp;

	tmp = zone;
	while (tmp && tmp->next)
	{
		if (tmp->zone_id == zone_id)
			if (tmp->free == 0)
				return (0);
		tmp = tmp->next;
	}
	return (1);
}


int				post_free(t_block *block)
{
	t_block	**zone;
	t_block	*tmp;
	t_block *last_block_zone;
	t_block *first_block_zone;

	zone = get_zone_by_type(block->zone_type);

	if (block->zone_type == ENV_LARGE)
	{
		tmp = get_prev_block(*zone, block);

		// The block hasn't any previous? So we need to remove the root
		if (tmp == NULL)
			*zone = block->next;
		else
			tmp->next = block->next;
		munmap(block, block->size + sizeof(t_block));
	}
	else if (block->zone_id > 1)
	{
		tmp = *zone;
		first_block_zone = NULL;
		last_block_zone = NULL;
		while (tmp && tmp->next)
		{
			if (tmp->zone_id == block->zone_id)
			{
				if (first_block_zone == NULL)
					first_block_zone = tmp;
				if (tmp->free == 0)
					return (1);
			}
			tmp = tmp->next;
		}
		if (!can_be_free(*zone, block->zone_id - 1))
			return (1);
		// if we are here, the zone can be free		
		last_block_zone = tmp;
		// Remove all the occurences
		// We know that they are all next to each others, so we just need to motifiy the prev element of the first block of a zone to remove them
		tmp = get_prev_block(*zone, first_block_zone);

		// The block hasn't any previous? So we need to remove the root
		if (tmp == NULL)
			*zone = last_block_zone->next;
		else
			tmp->next = last_block_zone->next;
	}
	return (0);
}

t_block			*mark_block_as_free(t_block *block)
{
	if (block)
	{
		// Restore original size
		block->size = get_zone_size(block->zone_type, block->size) / ALLOC_COUNT;
		block->free = 1;
		post_free(block);
	}
	return (block);
}

t_block			*mark_block_as_used(t_block *block, size_t size)
{
	uint64_t block_addr;

	if (block)
	{
		block_addr = (uint64_t)block;
		block->size = size;
		block->free = 0;
	}
	return (block);
}

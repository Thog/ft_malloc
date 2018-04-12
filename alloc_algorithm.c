#include "malloc_internal.h"

static int		get_env_type(size_t size)
{
	int env_type;

	env_type = ENV_LARGE;
	if (size <= TINY_SIZE)
		env_type = ENV_TINY;
	else if (size <= SMALL_SIZE)
		env_type = ENV_SMALL;
	return (env_type);
}

static t_block	**get_zone_by_type(int type)
{
	if (type == ENV_TINY)
		return (&g_env.tiny);
	else if (type == ENV_SMALL)
		return (&g_env.small);
	return (&g_env.large);	
}

size_t get_zone_size(int type, size_t size)
{
	if (type == ENV_TINY)
		return (TINY_ZONE);
	else if (type == ENV_SMALL)
		return (SMALL_ZONE);
	return (size);	
}

void			setup_zone(t_block *initial_block, size_t zone_size, size_t alloc_count)
{
	size_t i;
	t_block *tmp;
	uint64_t tmp_addr;
	char zone_id;
	char zone_type;

	zone_id = initial_block->zone_id;
	zone_type = initial_block->zone_type;
	tmp = initial_block;
	i = 0;
	while (i < alloc_count)
	{
			tmp_addr = (uint64_t)tmp;
			tmp->addr = (void*)(tmp_addr + sizeof(t_block));
			tmp->free = 1;
			tmp->size = zone_size / alloc_count;
			tmp->zone_id = zone_id;
			tmp->zone_type = zone_type;
			if (i == alloc_count - 1)
				tmp->next = NULL;
			else
				tmp->next = (void*)(tmp_addr + sizeof(t_block) + tmp->size);
			tmp = tmp->next;
			i++;
	}
}

t_block			*alloc_block(size_t size)
{
	int env_type;
	size_t	zone_size;
	t_block	**target_zone;
	t_block	*res;

	env_type = get_env_type(size);
	target_zone = get_zone_by_type(env_type);
	zone_size = get_zone_size(env_type, size);

	// If it' a SMALL or TINY area we can hold 100 allocations so we need to add the block size to the total size
	if (env_type != ENV_LARGE)
		zone_size += BLOCKS_ZONE_SIZE;
	else
		zone_size += sizeof(t_block); // large area = one block
	res = find_free_block_by_size(*target_zone, size);
	if (res)
	{
		mark_block_as_used(res, size);
		return (res);
	}
	res = alloc_blocks(target_zone, zone_size);
	res->zone_type = env_type;
	if (env_type != ENV_LARGE)
		setup_zone(res, zone_size - BLOCKS_ZONE_SIZE, ALLOC_COUNT);
	else
		res->size -= sizeof(t_block);
	mark_block_as_used(res, size);
	return (res);
}
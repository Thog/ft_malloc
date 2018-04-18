#include "malloc_internal.h"

static t_block	*get_block_by_zone(t_block *zone, void *ptr)
{
	uint64_t	zone_addr;
	uint64_t	ptr_addr;

	ptr_addr = (uint64_t)ptr;
	while (zone)
	{
		zone_addr = (uint64_t)zone->addr;
		if (ptr_addr >= zone_addr && ptr_addr < (zone_addr + zone->size))
			return (zone);
		zone = zone->next;
	}
	return (NULL);
}

static t_block	*find_free_block_zone(t_block *zone, size_t size)
{
	size_t zone_size;

	while (zone)
	{
		zone_size = get_zone_size(zone->zone_type, zone->size) / ALLOC_COUNT;
		if (zone_size >= size && zone->free == 1)
			return (zone);
		zone = zone->next;
	}
	return (NULL);
}

t_block			*get_block(void *ptr)
{
	t_block *res;

	if (!ptr)
		return (NULL);
	res = get_block_by_zone(g_env.tiny, ptr);
	if (!res)
		res = get_block_by_zone(g_env.small, ptr);
	if (!res)
		res = get_block_by_zone(g_env.large, ptr);
	return (res);
}

t_block			*find_free_block_by_size(t_block *zone, size_t size)
{
	return (find_free_block_zone(zone, size));
}
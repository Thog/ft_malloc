#include "malloc.h"

t_block		*alloc_block(t_block **base, size_t size)
{
	t_block		*tmp;

	if (*base)
	{
		tmp = get_last_block(*base);
		if ((tmp->next = (t_block*)mmap(0, size, PROT_RW, MAP_AP, -1, 0)) == MAP_FAILED)
			return (NULL);
		return (tmp->next);
	}
	else
	{
		if ((*base = (t_block*)mmap(0, size, PROT_RW, MAP_AP, -1, 0)) == MAP_FAILED)
			return (NULL);
		return (*base);
	}
}

t_block		*find_block(t_block *zone, size_t size)
{
	t_block	*res;

	res = NULL;
	while (zone)
	{
		if (zone->free && zone->size >= size)
		{
			if (!res || (res->size < zone->size))
				res = zone;
			if (zone->size == size)
				return (res);
		}
		zone = zone->next;
	}
	return (res);
}

t_block		*find_block_for_free(t_block *zone, void *ptr)
{
	t_block	*res;

	res = NULL;
	while (zone)
	{
		if (zone->addr >= ptr && ptr < (zone->addr + zone->size))
			return (zone);
		zone = zone->next;
	}
	return (res);
}

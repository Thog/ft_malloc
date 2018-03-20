/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 09:49:05 by tguillem          #+#    #+#             */
/*   Updated: 2018/03/20 20:56:23 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block		*alloc_block(t_block **base, size_t size)
{
	t_block		*tmp;

	if (*base)
	{
		tmp = get_last_block(*base);
		if ((tmp->next = (t_block*)mmap(0, size, PROT_RW, MAP_AP, -1, 0))
				== MAP_FAILED)
			return (NULL);
		return (tmp->next);
	}
	else
	{
		if ((*base = (t_block*)mmap(0, size, PROT_RW, MAP_AP, -1, 0))
				== MAP_FAILED)
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
	uint64_t	addr;

	while (zone)
	{
		addr = (uint64_t)zone->addr;
		if (ptr >= zone->addr && (uint64_t)ptr < (addr + zone->size))
			return (zone);
		zone = zone->next;
	}
	return (NULL);
}

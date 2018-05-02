/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_allocator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:59:52 by tguillem          #+#    #+#             */
/*   Updated: 2018/05/02 17:21:51 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

t_block			*alloc_blocks(t_block **blocks, size_t zone_size)
{
	t_block		*last_block;
	t_block		*res;
	uint64_t	block_addr;

	last_block = get_last_block(*blocks);
	res = NULL;
	if ((res = (t_block*)mmap(0, zone_size, PROT_RW, MAP_AP, -1, 0)) ==
		MAP_FAILED)
		return (NULL);
	block_addr = (uint64_t)res;
	res->addr = (void*)(block_addr + sizeof(t_block));
	res->free = 1;
	res->next = NULL;
	res->size = zone_size;
	res->zone_id = 0;
	if (last_block != NULL)
	{
		res->zone_id = last_block->zone_id + 1;
		last_block->next = res;
	}
	else
		*blocks = res;
	return (res);
}

static int		post_free_standard(t_block *block, t_block **zone)
{
	t_block	*tmp;
	t_block	*last_block_zone;
	t_block	*first_block_zone;

	tmp = *zone;
	first_block_zone = NULL;
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
	last_block_zone = tmp;
	if (!(tmp = get_prev_block(*zone, first_block_zone)))
		*zone = last_block_zone->next;
	else
		tmp->next = last_block_zone->next;
	return (0);
}

static void		post_free_large(t_block *block, t_block **zone)
{
	t_block	*tmp;

	tmp = get_prev_block(*zone, block);
	if (tmp == NULL)
		*zone = block->next;
	else
		tmp->next = block->next;
	munmap(block, block->size + sizeof(t_block));
}

int				post_free(t_block *block)
{
	t_block	**zone;
	t_block	*tmp;
	t_block	*last_block_zone;
	t_block	*first_block_zone;

	zone = get_zone_by_type(block->zone_type);
	if (block->zone_type == ENV_LARGE)
		post_free_large(block, zone);
	else if (block->zone_id > 1)
		return (post_free_standard(block, zone));
	return (0);
}

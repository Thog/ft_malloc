/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:55:01 by tguillem          #+#    #+#             */
/*   Updated: 2018/05/02 17:10:24 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_block			*mark_block_as_free(t_block *block)
{
	if (block)
	{
		block->size =
			get_zone_size(block->zone_type, block->size) / ALLOC_COUNT;
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

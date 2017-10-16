/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 09:45:43 by tguillem          #+#    #+#             */
/*   Updated: 2017/10/16 09:45:43 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				*alloc_tiny(size_t size)
{
	t_block	*block;

	if (!(block = find_block(g_env.tiny, size)))
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

	if (!(block = find_block(g_env.small, size)))
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

	if (!(block = find_block(g_env.large, size)))
	{
		if (!(block = alloc_block(&g_env.large, size + sizeof(t_block))))
			return (NULL);
		prepare_block(&block, size);
	}
	else
		setup_block(&block, size);
	return (block->addr);
}

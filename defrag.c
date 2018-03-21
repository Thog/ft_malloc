/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defrag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 09:46:02 by tguillem          #+#    #+#             */
/*   Updated: 2018/03/21 15:59:04 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		defrag_blocks(t_block *blocks, t_block *target,
		size_t page_size)
{
	t_block		*prev;
	size_t		tmp;
	size_t		total;

	prev = NULL;
	total = 0;
	while (blocks)
	{
		tmp = sizeof(t_block) + blocks->size;
		total += tmp;
		if (prev && prev == target && blocks->free && total <= page_size &&
				(prev->addr + prev->size) == blocks)
		{
			prev->size += tmp;
			prev->next = blocks->next;
		}
		if (prev != target && blocks == target)
			prev = blocks;
		if (total > page_size)
			total = 0;
		blocks = blocks->next;
	}
}

static int		free_page(t_block *blocks, t_block *target)
{
	t_block		*prev;

	prev = NULL;
	while (blocks)
	{
		if (blocks == target && blocks->free)
		{
			if (prev)
				prev->next = blocks->next;
			else
				blocks = NULL;
			munmap(target, target->size + sizeof(t_block));
			return (!prev);
		}
		prev = blocks;
		blocks = blocks->next;
	}
	return (0);
}

static size_t	get_page_size(t_block *block)
{
	if (block->size <= TINY_SIZE)
		return (TINY_SIZE);
	else if (block->size <= SMALL_SIZE)
		return (SMALL_SIZE);
	return (0);
}

t_block			*get_base(t_block *block)
{
	if (block->size <= TINY_SIZE)
		return (g_env.tiny);
	else if (block->size <= SMALL_SIZE)
		return (g_env.small);
	return (g_env.large);
}

void			post_free(t_block *target)
{
	size_t	page_size;
	t_block	*blocks;

	blocks = get_base(target);
	page_size = get_page_size(target);
	if (free_page(blocks, target))
	{
		if (blocks == g_env.tiny)
			g_env.tiny = NULL;
		else if (blocks == g_env.small)
			g_env.small = NULL;
		else if (blocks == g_env.large)
			g_env.large = NULL;
	}
}

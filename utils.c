/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 09:50:03 by tguillem          #+#    #+#             */
/*   Updated: 2018/03/21 21:47:06 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <assert.h>

void		ft_abort(char *message)
{
	ft_putstr(message);
	abort();
}

void ft_assert(int assert, const char *function, const char *file, int line)
{
	if (!assert)
	{
		ft_putstr("Asset failed: ");
		ft_putstr(file);
		ft_putstr(":");
		ft_putstr(function);
		ft_putstr(":");
		ft_putnbrbase(line, "0123456789");
		ft_putstr("\n");
		ft_abort("Aborted\n");
	}
}

t_block		*get_last_block(t_block *start)
{
	while (start->next)
		start = start->next;
	return (start);
}

void		setup_block(t_block **block, size_t size)
{
	t_block	*new;
	t_block	*prev_next;
	t_block	*next;
	size_t	rest;

	new = *block;
	prev_next = new->next;
	new->addr = new + 1;
	new->free = 0;
	new->next = NULL;

	rest = new->size - size;
	if (rest > sizeof(t_block))
	{
		next = (t_block*)((char*)new->addr + size);
		new->next = next;
		next->addr = next + 1;
		next->size = rest - sizeof(t_block);
		next->next = prev_next;
		next->free = 1;
	}
	else
		new->next = prev_next;
	new->size = size;
}

void		init_new_block(t_block **block, size_t size, size_t zone_size)
{
	t_block	*tmp;
	t_block	*rest;

	tmp = *block;

	tmp->addr = tmp + 1;
	tmp->free = 0;
	tmp->size = size;
	tmp->next = NULL;
	if (size != zone_size)
	{
		rest = (t_block*)((char*)tmp->addr + size);
		ft_putstr("REST 0x");
		ft_putnbrbase((uintmax_t)rest, "0123456789abcdef");
		ft_putstr("\n");
		rest->addr = rest + 1;
		rest->free = 1;
		rest->size = zone_size - size- BLOCKS_ZONE_SIZE;
		rest->next = NULL;
		tmp->next = rest;
	}
}

size_t		show_mem(char *name, t_block *base, int free_mode)
{
	size_t total;

	total = 0;
	ft_putstr(name);
	ft_putstr("0x");
	ft_putnbrbase((uintmax_t)base, "0123456789abcdef");
	ft_putstr("\n");
	while (base)
	{
		if (base->free == free_mode)
		{
			ft_putnbrbase((uintmax_t)base, "0123456789abcdef");
			ft_putstr(" - ");
			ft_putnbrbase(((uintmax_t)base + base->size), "0123456789abcdef");
			ft_putstr(" : ");
			ft_putnbrbase((uintmax_t)base->size, "0123456789");
			ft_putstr(" octets\n");
			total += base->size;
		}
		base = base->next;
	}
	return (total);
}

void		block_check(t_block *block)
{
	uint64_t		block_addr;

	block_addr = (uint64_t)block;
	if ((block_addr + sizeof(t_block)) != (uint64_t)block->addr)
	{
		ft_putstr("0x");
		ft_putnbrbase((uintmax_t)block_addr + sizeof(t_block), "0123456789abcdef");
		ft_putstr(" - ");
		ft_putstr("0x");
		ft_putnbrbase((uintmax_t)block->addr, "0123456789abcdef");
		ft_putstr("\n");
		ft_assert(0, __FUNCTION__, __FILE__, __LINE__);
	}
	ft_assert(block->free == 0 || block->free == 1, __FUNCTION__, __FILE__, __LINE__);
}

void		check_integrity(t_block *zone)
{
	while (zone)
	{
		block_info(zone);
		block_check(zone);
		zone = zone->next;
	}
}

void		block_info(t_block *block)
{
	if (block == NULL)
	{
		ft_putstr("(null)\n");
		return;
	}
	ft_putnbrbase((uintmax_t)block, "0123456789abcdef");
	ft_putstr(" - ");
	ft_putnbrbase((uintmax_t)block->addr, "0123456789abcdef");
	ft_putstr(" - ");
	ft_putnbrbase(((uintmax_t)block->addr + block->size), "0123456789abcdef");
	ft_putstr(" : ");
	ft_putnbrbase((uintmax_t)block->size, "0123456789");
	ft_putstr(" bytes (");
	ft_putnbrbase((uintmax_t)block->free, "0123456789");
	ft_putstr(")\n");
}

void		show_alloc_mem(void)
{
	size_t	total;

	total = show_mem("TINY : ", g_env.tiny, 0);
	total += show_mem("TINY FREE : ", g_env.tiny, 1);
	total += show_mem("SMALL : ", g_env.small, 0);
	total += show_mem("SMALL FREE : ", g_env.small, 1);
	total += show_mem("LARGE : ", g_env.large, 0);
	total += show_mem("LARGE FREE : ", g_env.large, 1);
	ft_putstr("Total : ");
	ft_putnbrbase(total, "0123456789");
	ft_putstr(" octets\n");
}

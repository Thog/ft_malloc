/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 09:50:03 by tguillem          #+#    #+#             */
/*   Updated: 2018/03/20 01:14:43 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
		next = (void*)new->addr + size;
		new->next = next;
		next->addr = next + 1;
		next->size = rest - sizeof(t_block);
		next->next = prev_next;
	}
	new->size = size;
}

void		prepare_block(t_block **block, size_t size)
{
	t_block	*tmp;

	tmp = *block;
	tmp->addr = tmp + 1;
	tmp->free = 0;
	tmp->size = size;
	tmp->next = NULL;
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

void		block_info(t_block *block)
{
	if (block == NULL)
	{
		ft_putstr("(null)\n");
		return;
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:01:13 by tguillem          #+#    #+#             */
/*   Updated: 2018/05/02 17:03:13 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

void		block_info(t_block *block)
{
	if (block == NULL)
	{
		ft_putstr("(null)\n");
		return ;
	}
	ft_putnbrbase((uintmax_t)block, BASE_16);
	ft_putstr(" - ");
	ft_putnbrbase((uintmax_t)block->addr, BASE_16);
	ft_putstr(" - ");
	ft_putnbrbase(((uintmax_t)block->addr + block->size), BASE_16);
	ft_putstr(" : ");
	ft_putnbrbase((uintmax_t)block->size, BASE_10);
	ft_putstr(" bytes (");
	ft_putnbrbase((uintmax_t)block->free, BASE_10);
	ft_putstr(")\n");
}

size_t		show_mem(char *name, t_block *base, int free_mode)
{
	size_t total;

	total = 0;
	ft_putstr(name);
	ft_putstr("0x");
	ft_putnbrbase((uintmax_t)base, BASE_16);
	ft_putstr("\n");
	while (base)
	{
		if (base->free == free_mode)
		{
			ft_putnbrbase((uintmax_t)base->addr, BASE_16);
			ft_putstr(" - ");
			ft_putnbrbase(((uintmax_t)base->addr + base->size), BASE_16);
			ft_putstr(" : ");
			ft_putnbrbase((uintmax_t)base->size, BASE_10);
			ft_putstr(" octets\n");
			total += base->size;
		}
		base = base->next;
	}
	return (total);
}

void		show_alloc_mem(void)
{
	size_t	total;

	total = show_mem("TINY : ", g_env.tiny, 0);
	total += show_mem("SMALL : ", g_env.small, 0);
	total += show_mem("LARGE : ", g_env.large, 0);
	ft_putstr("Total : ");
	ft_putnbrbase(total, "0123456789");
	ft_putstr(" octets\n");
}

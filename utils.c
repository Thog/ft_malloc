#include "malloc.h"

t_block		*get_last_block(t_block *start)
{
	while (start->next)
		start = start->next;
	return (start);
}

void		setup_block(t_block **block, size_t size)
{
	ft_putstr("SETUP_BLOCK\n");
	t_block	*new;
	t_block	*prev_next;
	t_block	*next;

	new = *block;
	prev_next = new->next;
	new->addr = new + 1;
	new->free = 0;
	next = (void*)new->addr + size;
	new->next = next;
	next->addr = next + 1;
	next->size = new->size - size - sizeof(t_block);
	new->size = size;
	next->next = prev_next;
}

void		prepare_block(t_block **block, size_t size)
{
	t_block	*tmp;
	ft_putstr("PREPARE_BLOCK\n");

	tmp = *block;
	tmp->addr = tmp + 1;
	tmp->free = 0;
	tmp->size = size;
	tmp->next = NULL;
}

size_t		show_mem(char *name, t_block *base)
{
	size_t total;

	total = 0;


	ft_putstr(name);
	ft_putstr("0x");
	ft_putnbrbase((uintmax_t)base, "0123456789abcdef");
	ft_putstr("\n");
	while(base)
	{
		ft_putnbrbase((uintmax_t)base, "0123456789abcdef");
		ft_putstr(" - ");
		ft_putnbrbase(((uintmax_t)base + base->size), "0123456789abcdef");
		ft_putstr(" : ");
		ft_putnbrbase((uintmax_t)base->size, "0123456789");
		ft_putstr(" octets\n");
		total += base->size;
		base = base->next;
	}
	return (total);
}

void		show_alloc_mem(void)
{
	size_t	total;

	total = show_mem("TINY : ", g_env.tiny);
	total += show_mem("SMALL : ", g_env.small);
	total += show_mem("LARGE : ", g_env.large);
	ft_putstr("Total : ");
	ft_putnbrbase(total, "0123456789");
	ft_putstr(" octets\n");
}

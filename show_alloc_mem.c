#include "malloc_internal.h"

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
	/*int i = 0;
	block_addr += sizeof(t_block) + block->size;
	char *data = (char*)block_addr;
	while (i < SPACING)
	{
		ft_assert(*data == 42, __FUNCTION__, __FILE__, __LINE__);
		data++;
		i++;
	}*/
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
			ft_putnbrbase((uintmax_t)base->addr, "0123456789abcdef");
			ft_putstr(" - ");
			ft_putnbrbase(((uintmax_t)base->addr + base->size), "0123456789abcdef");
			ft_putstr(" : ");
			ft_putnbrbase((uintmax_t)base->size, "0123456789");
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
	//total += show_mem("TINY FREE : ", g_env.tiny, 1);
	total += show_mem("SMALL : ", g_env.small, 0);
	//total += show_mem("SMALL FREE : ", g_env.small, 1);
	total += show_mem("LARGE : ", g_env.large, 0);
	//total += show_mem("LARGE FREE : ", g_env.large, 1);
	ft_putstr("Total : ");
	ft_putnbrbase(total, "0123456789");
	ft_putstr(" octets\n");
}
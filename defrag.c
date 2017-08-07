#include "malloc.h"

static void		defrag_blocks(t_block *blocks, t_block *target, size_t page_size)
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
		if (prev && ((prev == target && blocks->free && total <= page_size) || (target == blocks && prev->free && total <= page_size)))
		{
			prev->size += blocks->size + sizeof(t_block);
			prev->next = blocks->next;
		}
		else
			prev = blocks;
		if (total > page_size)
			total = tmp;
		blocks = blocks->next;
	}
}

static void		free_page(t_block *blocks, t_block *target)
{
	t_block		*prev;

	prev = NULL;
	while (blocks)
	{
		if (blocks == target)
		{
			if (prev)
				prev->next = blocks->next;
			munmap(target, target->size + sizeof(t_block));
			return ;
		}
		prev = blocks;
		blocks = blocks->next;
	}
}

static t_block	*get_base(t_block *block)
{
	if (block->size <= TINY_SIZE)
		return (g_env.tiny);
	else if (block->size <= SMALL_SIZE)
		return (g_env.small);
	return (g_env.large);
}

static size_t	get_page_size(t_block *block)
{
	if (block->size <= TINY_SIZE)
		return (TINY_SIZE);
	else if (block->size <= SMALL_SIZE)
		return (SMALL_SIZE);
	return (0);
}


void		post_free(t_block *target)
{
	size_t	page_size;
	t_block	*blocks;

	blocks = get_base(target);
	page_size = get_page_size(target);

	ft_putstr("\n\n YOLO \n\n");
	ft_putnbrbase(target->size, "0123456789ABCDEF");
	ft_putstr("\n\n YOLO \n\n");
	if (page_size != 0)
		defrag_blocks(blocks, target, page_size);
	else
		free_page(blocks, target);
}

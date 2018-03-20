/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 09:51:55 by tguillem          #+#    #+#             */
/*   Updated: 2018/03/20 20:55:53 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*block_from_ptr(void *ptr)
{
	t_block	*res;

	if (ptr == NULL)
		return (NULL);
	res = find_block_for_free(g_env.tiny, ptr);
	if (res)
		return (res);
	res = find_block_for_free(g_env.small, ptr);
	if (res)
		return (res);
	res = find_block_for_free(g_env.large, ptr);
	return (res);
}

static void		*resize_block(t_block *blk, size_t size)
{
	size_t		size_fix;

	if (!blk || !blk->next || !blk->next->free)
		return (NULL);
	size_fix = size - blk->size;
	if (blk->next->size < size_fix)
		return (NULL);
	blk->size = size;
	blk->next->size -= size_fix;
	if (blk->next->size == 0)
		blk->next = blk->next->next;
	return (blk->addr);
}

void *calloc(size_t nmemb, size_t size)
{
	if (nmemb == 0 || size == 0)
		return (NULL);
	return (malloc(nmemb * size));
}

void			*internal_malloc(size_t size)
{
	void	*ptr;

	ft_putstr("MALLOC 0x");
	ft_putnbrbase((uintmax_t)size, "0123456789abcdef");
	ft_putstr("\n");
	if (size <= 0)
		return (NULL);
	else if (size <= TINY_SIZE)
		ptr = alloc_tiny(size);
	else if (size <= SMALL_SIZE)
		ptr = alloc_small(size);
	else
		ptr = alloc_large(size);
	return (ptr);
}

void			*malloc(size_t size)
{
	void	*res;

	lock();
	res = internal_malloc(size);
	unlock();
	return (res);
}

void			internal_free(void *ptr)
{
	t_block	*block;

	ft_putstr("FREE 0x");
	ft_putnbrbase((uintmax_t)ptr, "0123456789abcdef");
	ft_putstr("\n");
	block = block_from_ptr(ptr);
	block_info(block);
	if (block)
	{
		block->free = 1;
		post_free(block);		
	}
}

void			free(void *ptr)
{
	lock();
	internal_free(ptr);
	unlock();
}

void			*internal_realloc(void *ptr, size_t size)
{
	void	*ret;
	t_block	*block;

	ft_putstr("REALLOC 0x");
	ft_putnbrbase((uintmax_t)ptr, "0123456789abcdef");
	ft_putstr(" , 0x");
	ft_putnbrbase(size, BASE_16);
	ft_putstr("\n");
	if (!ptr)
		return (internal_malloc(size));
	block = block_from_ptr(ptr);
	if ((!block || block->free) && ptr)
		return (NULL);
	if (ptr && !size)
		size = block->size;
	if (block && block->size < size && block->next && block->next->free &&
			(ret = resize_block(block, size)))
		return (ret);
	if (!(ret = internal_malloc(size)))
		return (NULL);
	if (block)
	{
		ret = ft_memcpy(ret, block->addr, block->size);
		block->free = 1;
		post_free(block);
	}
	return (ret);
}

void			*realloc(void *ptr, size_t size)
{
	void	*res;

	lock();
	res = internal_realloc(ptr, size);
	unlock();
	return (res);
}

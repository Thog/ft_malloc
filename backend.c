/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:52:59 by tguillem          #+#    #+#             */
/*   Updated: 2018/05/02 16:53:13 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

void				internal_free(void *ptr)
{
	t_block		*block;

	block = get_block(ptr);
	if (block != NULL && block->free == 0)
		mark_block_as_free(block);
}

void				*internal_malloc(size_t size)
{
	t_block	*res;

	if (size <= 0)
		return (NULL);
	res = alloc_block(size);
	if (res != NULL)
		return (res->addr);
	return (NULL);
}

void				*internal_realloc(void *ptr, size_t size)
{
	t_block			*block;
	void			*ret;
	size_t			zone_size;

	if (ptr == NULL)
		return (internal_malloc(size));
	block = get_block(ptr);
	if ((block == NULL || block->free == 1) && ptr)
		return (NULL);
	if (ptr && size == 0)
	{
		internal_free(ptr);
		return (NULL);
	}
	zone_size = get_zone_size(block->zone_type, block->size) / ALLOC_COUNT;
	if (size <= zone_size)
	{
		mark_block_as_used(block, size);
		return (ptr);
	}
	if (!(ret = internal_malloc(size)))
		return (NULL);
	ret = ft_memcpy(ret, block->addr, block->size);
	mark_block_as_free(block);
	return (ret);
}

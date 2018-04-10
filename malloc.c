/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 09:51:55 by tguillem          #+#    #+#             */
/*   Updated: 2018/04/10 14:47:37 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

void *calloc(size_t nmemb, size_t size)
{
	if (nmemb == 0 || size == 0)
		return (NULL);
	return (malloc(nmemb * size));
}

void			*malloc(size_t size)
{
	void	*res;

	lock();
	res = internal_malloc(size);
	ft_putstr("malloc: ");
	block_info(block_from_ptr(res));
	check_integrity(g_env.tiny);
	check_integrity(g_env.small);
	check_integrity(g_env.large);
	unlock();
	return (res);
}



void			free(void *ptr)
{
	lock();
	ft_putstr("BEFORE FREE\n");
	check_integrity(g_env.tiny);
	check_integrity(g_env.small);
	check_integrity(g_env.large);
	internal_free(ptr);
	ft_putstr("AFTER FREE\n");
	check_integrity(g_env.tiny);
	check_integrity(g_env.small);
	check_integrity(g_env.large);
	unlock();
}

void			*realloc(void *ptr, size_t size)
{
	void	*res;

	lock();
	res = internal_realloc(ptr, size);
	ft_putstr("realloc: ");
	block_info(block_from_ptr(res));
	check_integrity(g_env.tiny);
	check_integrity(g_env.small);
	check_integrity(g_env.large);
	unlock();
	return (res);
}

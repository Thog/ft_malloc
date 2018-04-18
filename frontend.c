/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 09:51:55 by tguillem          #+#    #+#             */
/*   Updated: 2018/04/12 12:40:34 by tguillem         ###   ########.fr       */
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
	unlock();
	return (res);
}

void			free(void *ptr)
{
	lock();
	internal_free(ptr);
	unlock();
}

void			*realloc(void *ptr, size_t size)
{
	void	*res;

	lock();
	res = internal_realloc(ptr, size);
	unlock();
	return (res);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	if (nmemb * size < nmemb || nmemb * size < size)
		return (NULL);
	return (realloc(ptr, nmemb * size));
}
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

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *str;

	str = (unsigned char *)b;
	while (len--)
		*str++ = c;
	return (b);
}

// FIXME: do a mul with 128 bits to avoid overflow
void	*calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*res;

	total = nmemb * size;
	res = malloc(total);
	if (!res)
		return (NULL);
	return (ft_memset(res, 0, total));
}

void		*malloc(size_t size)
{
	void	*res;

	lock();
	res = internal_malloc(size);
	unlock();
	return (res);
}

void		free(void *ptr)
{
	lock();
	internal_free(ptr);
	unlock();
}

void		*realloc(void *ptr, size_t size)
{
	void	*res;

	lock();
	res = internal_realloc(ptr, size);
	unlock();
	return (res);
}


void		*reallocf(void *ptr, size_t size)
{
	void	*res;

	res = realloc(ptr, size);
	if (!res && ptr)
		free(ptr);
	return (res);
}

void		*reallocarray(void *ptr, size_t nmemb, size_t size)
{
	if (nmemb * size < nmemb || nmemb * size < size)
		return (NULL);
	return (realloc(ptr, nmemb * size));
}

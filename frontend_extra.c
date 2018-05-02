/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:09:34 by tguillem          #+#    #+#             */
/*   Updated: 2018/05/02 17:09:34 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned char *str;

	str = (unsigned char *)b;
	while (len--)
		*str++ = c;
	return (b);
}

void		*calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*res;

	total = nmemb * size;
	res = malloc(total);
	if (!res)
		return (NULL);
	return (ft_memset(res, 0, total));
}

void		*reallocf(void *ptr, size_t size)
{
	void	*res;

	res = realloc(ptr, size);
	if (!res && ptr)
		free(ptr);
	return (res);
}

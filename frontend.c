/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 09:51:55 by tguillem          #+#    #+#             */
/*   Updated: 2018/05/02 17:09:05 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

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

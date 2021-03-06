/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:47:47 by tguillem          #+#    #+#             */
/*   Updated: 2018/05/02 16:47:47 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"
#include <errno.h>

int			init_lock(void)
{
	if (!g_env.lock_init)
	{
		if (!pthread_mutex_init(&g_env.lock, NULL))
		{
			g_env.lock_init = 1;
			return (0);
		}
		return (1);
	}
	return (0);
}

void		lock(void)
{
	if (!init_lock())
		pthread_mutex_lock(&g_env.lock);
}

void		unlock(void)
{
	if (!init_lock())
		pthread_mutex_unlock(&g_env.lock);
}

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
		return 1;
	}
	return 0;
}

void		lock(void)
{
	if (!init_lock())
	{
		//ft_putstr("LOCKING \n");
		pthread_mutex_lock(&g_env.lock);
	}
}

void		unlock(void)
{
	if (!init_lock())
	{
		//ft_putstr("UNLOCKING \n");
		pthread_mutex_unlock(&g_env.lock);
	}
}

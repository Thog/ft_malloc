/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 09:57:35 by tguillem          #+#    #+#             */
/*   Updated: 2017/10/16 10:07:50 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "malloc.h"

#define BASE_10 			"0123456789"
#define BASE_16 			"0123456789ABCDEF"
#define SMALL_SIZE			(size_t)getpagesize() * 16

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 1;
	if (!s)
		return (0);
	while (s[counter])
		counter++;
	if (!s[0])
		return (0);
	return (counter);
}

void	ft_putstr(char const *s)
{
	int		i;

	i = ft_strlen(s);
	if (i)
		write(1, s, i);
}

void	ft_putnbrbase_inner(uintmax_t nbr, char *base, size_t baselen)
{
	if (nbr >= baselen)
	{
		ft_putnbrbase_inner(nbr / baselen, base, baselen);
		ft_putnbrbase_inner(nbr % baselen, base, baselen);
	}
	else
		write(1, base + nbr, 1);
}

void	ft_putnbrbase(uintmax_t nbr, char *base)
{
	ft_putnbrbase_inner(nbr, base, ft_strlen(base));
}

void	info_free(void *ptr)
{
	ft_putstr("FREE\n");
	ft_putstr("================================\n");
	free(ptr);
	show_alloc_mem();
	ft_putstr("================================\n\n");
}

void	*info_malloc(size_t size)
{
	void	*ptr;

	ft_putstr("MALLOC ");
	ft_putnbrbase(size, BASE_10);
	ft_putstr(" bytes\n================================\n");
	ptr = malloc(size);
	show_alloc_mem();
	ft_putstr("================================\n\n");
	return (ptr);
}

void	*info_realloc(void *ptr, size_t size)
{
	ft_putstr("REALLOC ");
	ft_putnbrbase(size, BASE_10);
	ft_putstr(" bytes\n================================\n");
	ptr = realloc(ptr, size);
	show_alloc_mem();
	ft_putstr("================================\n\n");
	return (ptr);
}

void	test_realloc_simple(size_t malloc_size, size_t realloc_size)
{
	void	*ptr;

	ft_putstr("SIMPLE REALLOC TEST (");
	ft_putnbrbase(malloc_size, BASE_10);
	ft_putstr(", ");
	ft_putnbrbase(realloc_size, BASE_10);
	ft_putstr("\n");
	ptr = info_malloc(malloc_size);
	ptr = info_realloc(ptr, malloc_size);
	info_free(ptr);
}

void	test_by_zone(size_t zone_size)
{
	test_realloc_simple(zone_size, zone_size + 1);
	test_realloc_simple(zone_size, zone_size - 1);
	test_realloc_simple(zone_size, zone_size);
}

int		main(void)
{
	test_by_zone(TINY_SIZE);
	test_by_zone(SMALL_SIZE);
	test_by_zone(SMALL_ZONE + 1);
	return (0);
}

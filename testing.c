#include <stdlib.h>
#include <unistd.h>
#include "malloc.h"

# define SMALL_SIZE			(size_t)getpagesize() * 16

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

static void	ft_putnbrbase_inner(uintmax_t nbr, char *base, size_t baselen)
{
	if (nbr >= baselen)
	{
		ft_putnbrbase_inner(nbr / baselen, base, baselen);
		ft_putnbrbase_inner(nbr % baselen, base, baselen);
	}
	else
		write(1, base + nbr, 1);
}

void		ft_putnbrbase(uintmax_t nbr, char *base)
{
	ft_putnbrbase_inner(nbr, base, ft_strlen(base));
}


int main()
{
	void *ptr1;
	ft_putstr("MALLOC\n");
	malloc(1024);
	
	ft_putstr("MALLOC\n");
	malloc(1024 * 32);
	
	ft_putstr("MALLOC\n");
	malloc(1024 * 1024);
	
	ft_putstr("MALLOC\n");
	ptr1 = malloc(1024 * 1024 * 16);

	ft_putstr("MALLOC\n");
	malloc(1024 * 1024 * 128);

	show_alloc_mem();
	ft_putstr("FREE 2222222\n");
	free(ptr1);
	//show_alloc_mem();
	return (0);
}

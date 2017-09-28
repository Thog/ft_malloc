#include "malloc.h"

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

size_t		ft_strlen(const char *s)
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

void		ft_putstr(char const *s)
{
	int		i;

	i = ft_strlen(s);
	if (i)
		write(1, s, i);
}

void		ft_putnbrbase(uintmax_t nbr, char *base)
{
	ft_putnbrbase_inner(nbr, base, ft_strlen(base));
}

void		*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (n > i)
	{
		((char*)s1)[i] = ((char*)s2)[i];
		i++;
	}
	return (s1);
}

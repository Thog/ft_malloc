#ifndef MALLOC_H
# define MALLOC_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# define TINY_SIZE			(size_t)getpagesize() * 2
# define SMALL_SIZE			(size_t)getpagesize() * 16
# define TINY_ZONE			(size_t)(TINY_SIZE + sizeof(t_block)) * 100
# define SMALL_ZONE			(size_t)(SMALL_SIZE + sizeof(t_block)) * 100
# define PROT_RW			PROT_READ | PROT_WRITE
# define MAP_AP				MAP_ANON | MAP_PRIVATE

typedef struct		s_block
{
	void			*addr;
	size_t			size;
	struct s_block	*next;
	int				free;
}					t_block;

typedef struct		s_env
{
	t_block	*tiny;
	t_block	*small;
	t_block	*large;
}					t_env;

t_env				g_env;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);


void				*alloc_tiny(size_t size);
void				*alloc_small(size_t size);
void				*alloc_large(size_t size);
t_block				*alloc_block(t_block **base, size_t size);
t_block				*get_last_block(t_block *start);
void				setup_block(t_block **block, size_t size);
void				prepare_block(t_block **block, size_t size);
t_block				*find_block(t_block *zone, size_t size);
t_block				*find_block_for_free(t_block *zone, void *ptr);
void				ft_putnbrbase(uintmax_t nbr, char *base);
void				ft_putstr(char const *s);
void				show_alloc_mem(void);
#endif

#ifndef MALLOC_INTERNAL
#define MALLOC_INTERNAL

#define BASE_16 			"0123456789ABCDEF"
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/mman.h>
# include <pthread.h>

#define ENV_LARGE 0
#define ENV_TINY 1
#define ENV_SMALL 2
#define ALLOC_COUNT 100
# define TINY_SIZE			(size_t)getpagesize() * 2
# define SMALL_SIZE			(size_t)getpagesize() * 16
# define SPACING (size_t) 0
# define SPACING_SIZE (size_t)sizeof(t_block) + SPACING
# define BLOCKS_ZONE_SIZE	SPACING_SIZE* ALLOC_COUNT
# define TINY_ZONE			(size_t)(TINY_SIZE * ALLOC_COUNT)
# define SMALL_ZONE			(size_t)(SMALL_SIZE * ALLOC_COUNT)
# define PROT_RW			PROT_READ | PROT_WRITE
# define MAP_AP				MAP_ANON | MAP_PRIVATE
# define SILENT 0

typedef struct		s_block
{
	void			*addr;
	size_t			size;
	struct s_block	*next;
	short			zone_type;
	char			zone_id;
	char			free;
}					t_block;

typedef struct		s_env
{
	t_block						*tiny;
	t_block						*small;
	t_block						*large;
	pthread_mutex_t				lock;
	int										lock_init;
}					t_env;

t_env				g_env;

// Locking for internal_*
void		lock(void);
void		unlock(void);

// Printing utils
void				ft_putnbrbase(uintmax_t nbr, char *base);
void				ft_putstr(char const *s);
void				*ft_memcpy(void *s1, const void *s2, size_t n);

void				internal_free(void *ptr);
void				*internal_malloc(size_t size);
void				*internal_realloc(void *ptr, size_t size);

// get a not free block. used by free and realloc
t_block			*get_block(void *ptr);

// get the last block in the linked list
t_block			*get_last_block(t_block *root);

// call find_free_block_by_size and alloc_blocks. This function must auto find the zone type required (used by malloc and realloc in certains cases)
t_block			*alloc_block(size_t size);

// used to mmap a fresh zone and add the generated block to the global linked list
t_block			*alloc_blocks(t_block **blocks, size_t zone_size);

// mak a block as free
t_block			*mark_block_as_free(t_block *block);

// mak a block as used and assign size
t_block			*mark_block_as_used(t_block *block, size_t size);

// try to find a block that can handle the requested size
t_block			*find_free_block_by_size(t_block *zone, size_t size);

// Get Zone size by type
size_t				get_zone_size(int type, size_t size);

// Get a zone by type
t_block			**get_zone_by_type(int type);


// Get a block info
void		block_info(t_block *block);

void		show_alloc_mem(void);

void		block_check(t_block *block);

void		check_integrity(t_block *zone);

#endif
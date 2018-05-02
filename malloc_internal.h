/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:45:10 by tguillem          #+#    #+#             */
/*   Updated: 2018/05/02 17:11:47 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_INTERNAL_H
# define MALLOC_INTERNAL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/mman.h>
# include <pthread.h>

# define BASE_16 			"0123456789abcdef"
# define BASE_10			"0123456789"
# define ENV_LARGE 0
# define ENV_TINY 1
# define ENV_SMALL 2
# define ALLOC_COUNT 100
# define TINY_SIZE			(size_t)1024
# define SMALL_SIZE			TINY_SIZE * 4
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
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
	pthread_mutex_t	lock;
	int				lock_init;
}					t_env;

t_env				g_env;

void				lock(void);
void				unlock(void);

void				ft_putnbrbase(uintmax_t nbr, char *base);
void				ft_putstr(char const *s);
void				*ft_memcpy(void *s1, const void *s2, size_t n);

void				internal_free(void *ptr);
void				*internal_malloc(size_t size);
void				*internal_realloc(void *ptr, size_t size);

t_block				*get_block(void *ptr);

t_block				*get_prev_block(t_block *root, t_block *next);

t_block				*get_last_block(t_block *root);

t_block				*alloc_block(size_t size);

t_block				*alloc_blocks(t_block **blocks, size_t zone_size);

int					can_be_free(t_block *zone, int zone_id);

int					post_free(t_block *block);

t_block				*mark_block_as_free(t_block *block);

t_block				*mark_block_as_used(t_block *block, size_t size);

t_block				*find_free_block_by_size(t_block *zone, size_t size);

size_t				get_zone_size(int type, size_t size);

t_block				**get_zone_by_type(int type);

void				block_info(t_block *block);

void				show_alloc_mem(void);

#endif

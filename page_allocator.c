#include "malloc_internal.h"

t_block			*alloc_blocks(t_block **blocks, size_t zone_size)
{
	t_block	*last_block;
	t_block	*res;
	uint64_t block_addr;

	last_block = get_last_block(*blocks);
	res = NULL;
	if ((res = (t_block*)mmap(0, zone_size, PROT_RW, MAP_AP, -1, 0)) == MAP_FAILED)
		return (NULL);
	block_addr = (uint64_t)res;
	res->addr = (void*)(block_addr + sizeof(t_block));
	res->free = 1;
	res->next = NULL;
	res->size = zone_size;
	res->zone_id = 0;
	if (last_block != NULL)
	{
		res->zone_id = last_block->zone_id + 1;
		last_block->next = res;
	}
	else
		*blocks = res;
	return (res);
}

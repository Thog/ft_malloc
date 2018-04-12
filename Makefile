CFLAGS = -fPIC -pthread -g -Wextra -Wall -march=native -I./
CC = gcc

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME_NO_ARCH = libft_malloc.so
NAME = libft_malloc_$(HOSTTYPE).so

SRCS =  alloc_algorithm.c backend.c block_helpers.c block_utils.c frontend.c locking.c page_allocator.c printing_assist.c show_alloc_mem.c
OBJ = $(SRCS:.c=.o)
REMOVE = $(OBJ)

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(PRGFLAGS)
	@echo "$<"

$(NAME_NO_ARCH): $(NAME)
	@ln -sf $(NAME) $(NAME_NO_ARCH)

$(NAME): $(OBJ)
	@$(CC) -shared -g -o $@ $(OBJ)

all: $(NAME_NO_ARCH)

clean:
	@/bin/rm -f $(REMOVE)

fclean: clean
	@/bin/rm -f $(NAME) $(NAME_NO_ARCH)

.PHONY: clean fclean re

re: fclean all

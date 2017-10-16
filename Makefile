CFLAGS = -g -Wextra -Wall -march=native -I./
CC = gcc

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME_NO_ARCH = libft_malloc.so
NAME = libft_malloc_$(HOSTTYPE).so

SRCS = malloc.c allocator.c mem_map.c io.c utils.c defrag.c
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

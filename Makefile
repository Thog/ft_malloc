CFLAGS = -g -Wextra -Wall -march=native -I./
CC = gcc

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRCS = malloc.c allocator.c mem_map.c io.c utils.c defrag.c
OBJ = $(SRCS:.c=.o)
REMOVE = $(OBJ)

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(PRGFLAGS)
	@echo "$<"

$(NAME): $(OBJ)
	@$(CC) -shared -g -o $@ $(OBJ)

all: $(NAME)

clean:
	@/bin/rm -f $(REMOVE)

fclean: clean
	@/bin/rm -f $(NAME)

.PHONY: clean fclean re

re: fclean all

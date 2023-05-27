.PHONY: clean all re fclean
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = ft_malloc.a
SRC = ft_malloc.c linked_list.c
HEADER = ft_malloc.h

OBJ = $(SRC:.c=.o)

all: $(OBJ) $(HEADER) $(NAME)

$(NAME):
	@CC $(CFLAGS) -c $(SRC)
	@ar rc $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
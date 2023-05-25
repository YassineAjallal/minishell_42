.PHONY: clean all re fclean
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = expander.a
SRC = expander.c expand_var.c expand_tools.c expand_lst.c expand_no_quote.c expand_quote.c
HEADER = expander.h

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
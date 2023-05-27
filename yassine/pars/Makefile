.PHONY: clean all re fclean
CC = cc
CFLAGS = -Wunused-function #-Wall -Wextra -Werror
NAME = pars.a
SRC = pars1.c pars_tools.c syntax_error.c lexer_tools.c lexer.c\
	dup_cmd.c rederect.c xi_haga.c
# HEADER = expander.h

OBJ = $(SRC:.c=.o)

all: $(OBJ)  $(NAME)

$(NAME):
	@CC $(CFLAGS) -c $(SRC)
	@ar rc $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
.PHONY: clean all re fclean
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipes.a
SRC = pipe_tool.c pipes.c process_config.c
HEADER = pipes.h

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
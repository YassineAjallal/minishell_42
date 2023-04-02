.PHONY: clean all re fclean
CFLAGS = -Wall -Wextra -Werror -lreadline
NAME = minishell
SRC = minishell.c
LIB_PATH = ./libft/libft.a

OBJ = $(SRC:.c=.o)

all: $(OBJ) $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@CC $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@make clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all
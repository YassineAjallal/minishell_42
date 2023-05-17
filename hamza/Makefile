.PHONY: clean all re fclean
CC = gcc
CFLAGS = -lreadline  -fsanitize=address,leak -g #-Wall -Wextra -Werror
NAME = minishell
SRC = pars1.c  expand.c #leaks_check.c
LIB_PATH = ./libft/libft.a
OBJ = $(SRC:.c=.o)

%.o: %.c
	cc -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	cc $(CFLAGS) -L /lib/ $(SRC) $(LIB_PATH) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@make clean -C ./libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft

re: fclean all
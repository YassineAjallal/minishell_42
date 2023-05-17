.PHONY: clean all re fclean
CC = gcc
CFLAGS = -lreadline  #-Wall -Wextra -Werror
NAME = minishell
SRC = pars1.c  expand.c leaks_check.c
LIB_PATH = ./libft/libft.a
REDLINE=$(shell brew  --prefix readline)
OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	$(CC) $(CFLAGS) -L $(REDLINE)/lib $(LIB_PATH) $(OBJ) $(LIBFT) -o $(NAME)


clean:
	@rm -f $(OBJ)
	@make clean -C ./libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft

re: fclean all
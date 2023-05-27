.PHONY: clean all re fclean
CC = gcc
CFLAGS = -lreadline  -fsanitize=address -g #-Wall -Wextra -Werror
NAME = minishell
REDLINE=$(shell brew  --prefix readline)
SRC = pars1.c  expand.c #leaks_check.c
LIB_PATH = ./libft/libft.a
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I $(REDLINE)/include -c $< -o $@
# cc -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	$(CC) $(CFLAGS) -L $(REDLINE)/lib $(OBJ) $(LIB_PATH) -lreadline -o $(NAME)
# cc $(CFLAGS) -L /lib/ $(SRC) $(LIB_PATH) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@make clean -C ./libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft

re: fclean all
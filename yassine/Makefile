.PHONY: clean all re fclean
CC = gcc
CFLAGS = -lreadline   -Wall -Wextra -Werror
NAME = minishell
SRC = pipes.c pars1.c expander.c parsing.c ambiguous.c linked_list.c
LIB_PATH = ./libft/libft.a
BUILT_IN_PATH = ./built_in_command/built_in_command.a
CMD_EXEC_PATH = ./cmd_executer/cmd_executer.a
OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	@make -C ./built_in_command
	@make -C ./cmd_executer
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB_PATH) $(BUILT_IN_PATH) $(CMD_EXEC_PATH)


clean:
	@rm -f $(OBJ)
	@make clean -C ./libft
	@make clean -C ./built_in_command
	@make clean -C ./cmd_executer

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft
	@make fclean -C ./built_in_command
	@make fclean -C ./cmd_executer

re: fclean all
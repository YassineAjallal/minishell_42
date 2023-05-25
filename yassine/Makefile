.PHONY: clean all re fclean
CC = cc
CFLAGS = -lreadline -Wall -Wextra -Werror
NAME = minishell
SRC = minishell.c pars1.c parsing.c ambiguous.c linked_list.c
LIB_PATH = ./libft/libft.a
BUILT_IN_PATH = ./built_in_command/built_in_command.a
CMD_EXEC_PATH = ./cmd_executer/cmd_executer.a
EXPANDER_PATH = ./expander/expander.a
PIPES_PATH = ./pipes/pipes.a
OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	@make -C ./built_in_command
	@make -C ./cmd_executer
	@make -C ./expander
	@make -C ./pipes
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB_PATH) $(BUILT_IN_PATH) $(CMD_EXEC_PATH) $(EXPANDER_PATH) $(PIPES_PATH)
clean:
	@rm -f $(OBJ)
	@make clean -C ./libft
	@make clean -C ./built_in_command
	@make clean -C ./cmd_executer
	@make clean -C ./expander
	@make clean -C ./pipes

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft
	@make fclean -C ./built_in_command
	@make fclean -C ./cmd_executer
	@make fclean -C ./expander
	@make fclean -C ./pipes

re: fclean all
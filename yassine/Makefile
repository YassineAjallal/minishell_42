.PHONY: clean all re fclean
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
BUILT_IN_COMMAND_NAME = built_in_command.a
MINISHELL_SRC = minishell.c
BUILT_IN_COMMAND_SRC = built_in_command/ft_cd.c built_in_command/ft_env.c built_in_command/ft_pwd.c built_in_command/tools.c built_in_command/export_param.c built_in_command/ft_echo.c built_in_command/ft_export.c built_in_command/ft_unset.c
LIB_PATH = libft/libft.a

# MINISHELL_OBJ = $(MINISHELL_SRC:.c=.o)
BUILT_IN_COMMAND_OBJ = $(BUILT_IN_COMMAND_SRC:.c=.o)

# ./built_in_command/%.o : BUILT_IN_COMMAND_SRC
# 	@$(CC) -Wall -Wextra -Werror -c $< -o $@

all: $(NAME)
	@echo "pipex : done"

$(NAME): $(BUILT_IN_COMMAND_OBJ)
	@make -C libft
	@CC $(CFLAGS) -c $(BUILT_IN_COMMAND_SRC) -o ./built_in_command/
	@ar rc ./built_in_command/$(BUILT_IN_COMMAND_NAME) $(BUILT_IN_COMMAND_OBJ)
	@CC $(CFLAGS) -o $(NAME) $(MINISHELL_SRC) $(LIB_PATH) ./built_in_command/$(BUILT_IN_COMMAND_NAME)

clean:
	@make clean -C libft
	@rm -f $(BUILT_IN_COMMAND_OBJ)

fclean:
	@rm -f $(NAME)
	@rm -f $(BUILT_IN_COMMAND_OBJ)
	@rm -f $(BUILT_IN_COMMAND_NAME)
	@make fclean -C libft

re: fclean all
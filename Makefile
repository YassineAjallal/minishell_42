.PHONY: clean all re fclean
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
SRC =	built_in_command/env_export_tools.c \
		built_in_command/export_param.c \
		built_in_command/ft_cd.c \
		built_in_command/ft_echo.c \
		built_in_command/ft_env.c \
		built_in_command/ft_exit.c \
		built_in_command/ft_export.c \
		built_in_command/ft_pwd.c \
		built_in_command/ft_unset.c \
		built_in_command/tools.c \
		built_in_command/tools1.c \
		cmd_executer/cmd_exec.c \
		cmd_executer/cmd_tools.c \
		cmd_executer/exec_built_in.c \
		cmd_executer/file_checker.c \
		cmd_executer/redirections.c \
		cmd_executer/tools.c \
		expander/expand_lst.c \
		expander/expand_no_quote.c \
		expander/expand_quote.c \
		expander/expand_tools.c \
		expander/expand_var.c \
		expander/expander.c \
		ft_malloc/ft_malloc.c \
		ft_malloc/linked_list_malloc.c \
		pars/dup_cmd.c \
		pars/lexer.c \
		pars/lexer_tools.c \
		pars/pars1.c \
		pars/pars_tools.c \
		pars/rederect.c \
		pars/syntax_error.c \
		pars/tools.c \
		pipes/pipe_tool.c \
		pipes/pipes.c \
		pipes/process_config.c \
		ambiguous.c \
		free_infos.c \
		linked_list.c \
		minishell.c \
		minishell_tools.c

LIB_PATH = ./libft/libft.a
REDLINE= $(shell brew --prefix readline)
RDLIB = -lreadline -L $(REDLINE)/lib
RDINCLUD = -I $(REDLINE)/include
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(RDINCLUD)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB_PATH) $(RDLIB)
clean:
	@rm -f $(OBJ)
	@make clean -C ./libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft

re: fclean all
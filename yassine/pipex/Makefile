.PHONY: clean all re fclean
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
SRC = ft_cmd.c ft_printerr.c ft_pipex.c ft_files.c ft_process.c ft_family.c ft_free.c
LIB_PATH = ./libft/libft.a

all: $(NAME)
	@echo "pipex : done"
$(NAME):
	@make -C libft
	@CC $(CFLAGS) -o $(NAME) $(SRC) $(LIB_PATH)

clean:
	@make clean -C libft

fclean:
	@rm -f $(NAME)
	@make fclean -C libft
	@echo "$(NAME) deleted"

re: fclean all
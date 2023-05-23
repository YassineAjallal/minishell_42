.PHONY: clean all re fclean
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = built_in_command.a
SRC = export_param.c ft_cd.c ft_echo.c ft_env.c ft_export.c ft_pwd.c ft_unset.c tools.c ft_exit.c env_export_tools.c
HEADER = built_in_command.h

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
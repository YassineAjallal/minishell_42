.PHONY: clean all re fclean
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = cmd_executer.a
SRC =  cmd_exec.c cmd_tools.c file_checker.c redirections.c tools.c exec_built_in.c
HEADER = cmd_executer.h

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
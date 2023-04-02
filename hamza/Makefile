# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 13:26:05 by hkasbaou          #+#    #+#              #
#    Updated: 2022/10/19 18:26:39 by hkasbaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all re fclean
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
NAME = libft.a
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_strlen.c \
       ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
       ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_strdup.c \
       ft_substr.c ft_strjoin.c ft_split.c ft_itoa.c ft_strmapi.c \
       ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_isprint.c \
       ft_putnbr_fd.c ft_strtrim.c ft_memcpy.c ft_memmove.c ft_memset.c \
       ft_memcmp.c ft_memchr.c ft_bzero.c ft_calloc.c ft_striteri.c
SRCB = ft_lstnew.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
       ft_striteri.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstiter.c

OBJ = $(SRC:.c=.o) 
BOBJ = $(SRCB:.c=.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $<
all: $(NAME)

bonus: all $(BOBJ)
	@ar rcs $(NAME) $(BOBJ)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ) $(BOBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
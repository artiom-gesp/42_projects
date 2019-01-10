# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agesp <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/10 09:29:07 by agesp             #+#    #+#              #
#    Updated: 2019/01/10 17:18:44 by agesp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker

LIB = libft/libftprintf.a

SRC = main.c \
    checker.c \
    move_threw_list.c \
    swap.c \
	fill_pile.c \
	check_input.c \
	push_swap.c \
	get_smallest.c \
	quick_sort.c

OBJ = $(addsuffix .o,$(basename $(SRC)))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) checker.h
	make -C ./libft
	$(CC) -c $(SRC) $(CFLAGS)
	$(CC) -o $@ $(OBJ) $(LIB) $(CFLAGS)

clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(LIB)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

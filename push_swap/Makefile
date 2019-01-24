# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agesp <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/10 09:29:07 by agesp             #+#    #+#              #
#    Updated: 2019/01/24 15:45:01 by agesp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker

PUSH_NAME = push_swap

LIB = libft/libftprintf.a

SRC = main.c \
    checker.c \
    move_through_list.c \
    swap.c \
	fill_pile.c \
	check_input.c \
	push_swap.c \
	get_smallest.c \
	print_list.c \
	utils.c \
	nquick_sort.c

PUSH_SRC = checker.c \
    move_through_list.c \
    swap.c \
	fill_pile.c \
	check_input.c \
	push_swap.c \
	utils.c \
	get_smallest.c \
	main_push.c \
	print_list.c \
	nquick_sort.c

OBJ = $(addsuffix .o,$(basename $(SRC)))

PUSH_OBJ = $(addsuffix .o,$(basename $(PUSH_SRC)))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME) $(PUSH_NAME)

$(NAME): $(OBJ) checker.h
	make -C ./libft
	$(CC) -c $(SRC) $(CFLAGS)
	$(CC) -o $@ $(OBJ) $(LIB) $(CFLAGS) -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit 

$(PUSH_NAME): $(PUSH_OBJ) checker.h
	$(CC) -c $(PUSH_SRC) $(CFLAGS)
	$(CC) -o $@ $(PUSH_OBJ) $(LIB) $(CFLAGS) -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit 


clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(LIB)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

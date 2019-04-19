# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agesp <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/10 09:29:07 by agesp             #+#    #+#              #
#    Updated: 2019/04/19 13:09:03 by agesp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker

PUSH_NAME = push_swap

OBJDIR = obj

LIB = libft/libftprintf.a

SRC = main.c \
    checker.c \
    move_through_list.c \
    swap.c \
	fill_pile.c \
	sort_three.c \
	check_input.c \
	push_swap.c \
	get_smallest.c \
	print_list.c \
	utils.c \
	rev_rota.c \
	nquick_sort.c

PUSH_SRC = checker.c \
    move_through_list.c \
    swap.c \
	fill_pile.c \
	check_input.c \
	sort_three.c \
	push_swap.c \
	utils.c \
	get_smallest.c \
	main_push.c \
	print_list.c \
	rev_rota.c \
	nquick_sort.c

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

PUSH_OBJ = $(addprefix $(OBJDIR)/, $(PUSH_SRC:.c=.o))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME) $(PUSH_NAME)
	@printf "%b\n" "\x1b[32m All Done !\x1b[0m"

$(NAME): $(OBJ) src/checker.h
	@make -C ./libft
	@$(CC) -o $@ $(OBJ) $(LIB) $(CFLAGS) -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
	@printf "%b\n" "\x1b[32mchecker: Ok !\x1b[0m"

$(PUSH_NAME): $(PUSH_OBJ) src/checker.h
	@make -C ./libft
	@$(CC) -o $@ $(PUSH_OBJ) $(LIB) $(CFLAGS) -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
	@printf "%b\n" "\x1b[32mpush_swap: Ok !\x1b[0m"

obj/%.o : src/%.c
	@if [ ! -d "$(OBJDIR)" ] ; \
	then \
		mkdir obj ; \
	fi;
	@cd obj/ && $(CC) -c $(CFLAGS) ../$<

clean:
	@printf "%b\n" "\x1b[32mCleaning..\x1b[0m"
	@make clean -C ./libft
	@rm -rf $(OBJ)
	@rm -rf obj/
	@rm -rf $(PUSH_OBJ)

fclean: clean
	@printf "%b\n" "\x1b[32mCleaning executable..\x1b[0m"
	@rm -rf $(LIB)
	@rm -rf $(NAME)
	@rm -rf $(PUSH_NAME)

re: fclean all

.PHONY: all clean fclean re

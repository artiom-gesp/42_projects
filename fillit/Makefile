# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uroy <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/09 15:18:11 by uroy              #+#    #+#              #
#    Updated: 2018/12/10 13:49:26 by agesp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit 

LIB = libft/libft.a

SRC = main.c \
	solve.c \
	call_canplace.c \
	check_correct_tab.c \
	check_entry.c \
	create_tab.c \
	extract_tetraminos.c \
	free_tab.c \
	get_next_line.c \
	print_result.c \
	recon_tetr.c \
	canplace1.c \
	canplace2.c \
	canplace3.c \
	canplace4.c \
	canplace5.c \
	canplace6.c \
	canplace7.c \
	canplace8.c \
	canplace9.c \
	canplace10.c \
	canplace11.c \
	canplace12.c \
	canplace13.c \
	canplace14.c \
	canplace15.c \
	canplace16.c \
	canplace17.c \
	canplace18.c \
	canplace19.c

OBJ = $(addsuffix .o,$(basename $(SRC)))

CC = gcc -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(SRC) fillit.h
	make -C ./libft
	$(CC) -c $(SRC)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(LIB)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agesp <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/21 10:53:44 by agesp             #+#    #+#              #
#    Updated: 2019/01/21 13:05:01 by agesp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = main.c create_tab.c seg_print.c print_iso.c print_para.c

OBJ = $(SRC:.c=.o)

CFLAGS = -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit 

CC = gcc -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) fdf.h
	make -C ./libft
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) libft/libftprintf.a

%.o: %.c
	@$(CC) -c $<

clean:
	make clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re

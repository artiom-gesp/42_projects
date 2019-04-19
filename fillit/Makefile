# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uroy <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/09 15:18:11 by uroy              #+#    #+#              #
#    Updated: 2019/04/19 14:36:55 by agesp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit 

LIB = -L ./libft -lft

LIB_INCLUDE = ./libft/includes

INCLUDE = ./includes

SRCDIR = src

OBJDIR = obj

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

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(NAME)

$(NAME): $(OBJ) $(SRCS) $(INCLUDE) 
	@make -C ./libft
	@$(CC) $(CGLAGS) -o $(NAME) $(OBJ) $(LIB) -I$(INCLUDE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if [ ! -d "$(OBJDIR)" ] ; \
	then \
		mkdir $(OBJDIR) ; \
	fi ;
	@$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE) -I$(LIB_INCLUDE)

clean:
	@make clean -C ./libft
	@rm -rf $(OBJ)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

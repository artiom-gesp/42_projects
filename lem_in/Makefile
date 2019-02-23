# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agesp <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/10 09:29:07 by agesp             #+#    #+#              #
#    Updated: 2019/02/23 15:04:07 by agesp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

OBJDIR = obj

LIB = libft/libftprintf.a

HEAD = header/lem_in.h

SRC = main.c \
	  check_input.c \
	  check_arg.c

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
	@printf "%b\n" "\x1b[32m All Done !\x1b[0m"

$(NAME): $(OBJ) $(HEAD)
	@make -C ./libft
	@$(CC) -o $@ $(OBJ) $(LIB) $(CFLAGS) -ggdb 
	@printf "%b\n" "\x1b[32mlem-in: Ok !\x1b[0m"

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

fclean: clean
	@printf "%b\n" "\x1b[32mCleaning executable..\x1b[0m"
	@rm -rf $(LIB)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

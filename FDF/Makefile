# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agesp <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/21 10:53:44 by agesp             #+#    #+#              #
#    Updated: 2019/04/19 13:53:25 by agesp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

INCLUDE = ./includes

SRCDIR = src

LIB_INCLUDE = ./libft/includes

OBJDIR = obj

LIB = -L ./libft -lft

SRC = main.c \
	  create_tab.c \
	  seg_print.c \
	  print_iso.c \
	  print_para.c \
	  utils.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

CFLAGS = -Wall -Werror -Wextra

MLX_FLAGS = -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit 

CC = gcc

all: $(NAME)

$(NAME): $(SRCS) $(OBJ) $(INCLUDES)
	make -C ./libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) -I$(INCLUDE) $(MLX_FLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if [ ! -d "$(OBJDIR)" ] ; \
	then \
		mkdir $(OBJDIR) ; \
	fi;
	@$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE) -I$(LIB_INCLUDE)

clean:
	@make clean -C ./libft
	@rm -f $(OBJ)
	@rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agesp <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 09:52:08 by agesp             #+#    #+#              #
#    Updated: 2019/02/07 16:54:30 by agesp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc -Wall -Werror -Wextra

SRC = ft_put_long_nbr.c \
	  ft_isalpha.c \
	  ft_memcpy.c \
	  ft_strchr.c \
	  ft_strlcat.c \
	  ft_strncpy.c \
	  ft_tolower.c \
	  ft_atoi.c \
	  ft_isascii.c \
	  ft_memmove.c \
	  ft_strcmp.c \
	  ft_strlen.c \
	  ft_strnstr.c \
	  ft_toupper.c \
	  ft_bzero.c \
	  ft_isdigit.c \
	  ft_memset.c \
	  ft_strcpy.c \
	  ft_strncat.c \
	  ft_strrchr.c \
	  ft_isalnum.c \
	  ft_isprint.c \
	  ft_strcat.c \
	  ft_strdup.c \
	  ft_strncmp.c \
	  ft_strstr.c \
	  ft_memccpy.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memalloc.c \
	  ft_memdel.c \
	  ft_strnew.c \
	  ft_strdel.c \
	  ft_strclr.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strequ.c \
	  ft_strnequ.c \
	  ft_strsub.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_strsplit.c \
	  ft_putstr.c \
	  ft_putchar.c \
	  ft_putendl.c \
	  ft_putstr_fd.c \
	  ft_putchar_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr.c \
	  ft_putnbr_fd.c \
	  ft_itoa.c \
	  ft_lstnew.c \
	  ft_lstdelone.c \
	  ft_lstdel.c \
	  ft_lstadd.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_isspace.c \
	  ft_atoi_base.c \
	  ft_is_bigger.c \
	  ft_sort_nb_tab.c \
	  ft_sort_tab_param.c \
	  ft_itoa_base.c \
	  ft_pow.c \
	  complete_list.c \
	  ft_printf.c \
	  ft_printf.c \
	  get_flags.c \
	  print_list.c \
	  print_w.c \
	  test_flags.c \
	  prints.c \
	  print_u.c \
	  print_float.c \
	  print_int.c \
	  print_precision.c \
	  print_x_o_u.c \
	  sort_flags.c \
	  print_minus.c \
	  print_width.c \
	  ft_nbrlen.c \
	  complete_stars.c \
	  get_next_line.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)
	@:

$(NAME): $(OBJ) $(SRC) libft.h ft_printf.h get_next_line.h
	@ar -rc $(NAME) $(OBJ)
	@printf "%b\n" "\x1b[32mLibft: Ok !\x1b[0m"

%.o: %.c
	@$(CC) -c $<

clean:
	@printf "%b\n" "\x1b[32mCleaning Libft..\x1b[0m"
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
